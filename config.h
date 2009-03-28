
#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <cfgparser.h>

struct ConfigObject_t {
    std::string domainDir;
    std::string dbName;
    std::string dbHost;
    std::string dbUser;
    std::string dbPass;

    ConfigObject_t()
    {
        ConfigParser_t cfg;
        if (cfg.readFile("/usr/local/bin/logparse.conf"))
        {
            printf("Error: Cannot open config file `logparse.conf`\n");
        }

        if (!cfg.getValue("directories", "domains", &domainDir))
        {
            printf("Section/option [directories] domain not found\n");
        }

        if (!cfg.getValue("mysql", "database", &dbName))
        {
            printf("Section/option [mysql] database not found\n");
        }

        if (!cfg.getValue("mysql", "host", &dbHost))
        {
            printf("Section/option [mysql] host not found\n");
        }

        if (!cfg.getValue("mysql", "user", &dbUser))
        {
            printf("Section/option [mysql] user not found\n");
        }

        if (!cfg.getValue("mysql", "passwd", &dbPass))
        {
            printf("Section/option [mysql] passwd not found\n");
        }
    }
};

#endif /* CONFIG_H */
