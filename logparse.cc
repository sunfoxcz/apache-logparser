
#include "logparse.h"

int main()
{
    ConfigObject_t config;

    // Getting domain list
    std::vector<std::string> domains;
    std::cout << "Getting domain list..." << std::endl;
    getdir(config.domainDir, domains);

    // MySQL
    MYSQL *resource = mysql_init(NULL);
    mysql_options(resource, MYSQL_SET_CHARSET_NAME, "utf8");
    mysql_real_connect(
            resource,
            config.dbHost.c_str(),
            config.dbUser.c_str(),
            config.dbPass.c_str(),
            config.dbName.c_str(),
            3306, NULL, 0);

    for (uint i = 0; i < domains.size(); i++)
    {
        //printf("Domain: %s\n", domains[i].c_str());

        std::string zoneDir = config.domainDir + "/" + domains[i] + "/zone";
        if (access(zoneDir.c_str(), X_OK) != 0)
        {
            printf("Domain `%s` zone directory is not accesible\n", domains[i].c_str());
            continue;
        }

        std::vector<std::string> zones;
        getdir(zoneDir, zones);

        for (uint j = 0; j < zones.size(); ++j)
        {
            //printf("\t:: %s\n", zones[j].c_str());

            std::string zoneFileName = zoneDir + "/" + zones[j];
            if (access(zoneFileName.c_str(), R_OK) != 0)
            {
                printf("Zone `%s` of domain `%s` is not accesible.\n",
                        zoneFileName.c_str(), domains[i].c_str());
                continue;
            }

            ZoneFile_t &zone = parseZone(zoneFileName);

            if (!zone.serverName.empty() && !zone.logFile.empty())
            {
                LogFile_t log = parseLog(zone.logFile);

                std::stringstream sql;
                sql << "INSERT INTO traffic (date, domain, proxy_pass, servername, logname, bytes_in, bytes_out)"
                    << "VALUES ('" << log.getDate() << "', '" << domains[i] << "', "
                    << (zone.proxyPass == true ? "1" : "0") << ", '" << zone.serverName << "', "
                    << (zone.logName == "access.log" ? "NULL" : "'" + zone.logName + "'" )
                    << ", " << log.totalIn << ", " << log.totalOut << ")";
                mysql_query(resource, sql.str().c_str());
            }
        }
    }

    mysql_close(resource);

    return 0;
}
