
#include "parse.h"

ZoneFile_t &parseZone(std::string fileName)
{
    ZoneFile_t *zone = new ZoneFile_t;

    if (access(fileName.c_str(), R_OK) != 0)
    {
        printf("File `%s` is not accesible.\n", fileName.c_str());
        return *zone;
    }

    FILE * zoneFile;
    zoneFile = fopen(fileName.c_str(), "r");

    char line[512];
    while (fgets(line, 511, zoneFile))
    {
        std::string sLine = strip(std::string(line));

        if (sLine[0] == '#')
            continue;

        size_t found = sLine.find("ServerName");
        if (found != std::string::npos)
        {
            std::vector<std::string> pLine = split(sLine, ' ');

            if (pLine[0] == "ServerName")
            {
                zone->serverName = pLine[1];
            }
        }

        found = sLine.find("CustomLog");
        if (found != std::string::npos)
        {
            std::vector<std::string> pLine = split(sLine, ' ');

            if (pLine[0] == "CustomLog" && pLine[2] == "bwcombined")
            {
                zone->logFile = pLine[1];

                found =  pLine[1].rfind("/");
                if (found != std::string::npos)
                {
                    zone->logName = pLine[1].substr(found+1, pLine[1].size());

                    found = zone->logName.rfind("_");
                    if (found != std::string::npos)
                    {
                        zone->logName = zone->logName.substr(0, found);
                    }
                }
            }
        }

        found = sLine.find("ProxyPass");
        if (found != std::string::npos && found == 0)
        {
            zone->proxyPass = true;
        }
    }

    fclose(zoneFile);

    return *zone;
}

LogFile_t &parseLog(std:: string fileName)
{
    LogFile_t *log = new LogFile_t;
    std::string fileName2 = fileName + ".1";

    if (access(fileName.c_str(), R_OK) != 0)
    {
        printf("File `%s` is not accesible.\n", fileName.c_str());
        return *log;
    }

    FILE * logFile;
    logFile = fopen(fileName.c_str(), "r");
    std::string yesterday = getYesterday();
    log->date = yesterday;

    char line[4096];
    while (fgets(line, 4095, logFile))
    {
        RequestData_t reqData;
        parseLine(std::string(line), reqData);

        if (reqData.getDate() == yesterday)
        {
            log->totalIn += reqData.getInput();
            log->totalOut += reqData.getOutput();
        }
    }

    fclose(logFile);

    if (access(fileName2.c_str(), R_OK) != 0)
    {
        return *log;
    }

    logFile = fopen(fileName2.c_str(), "r");

    while (fgets(line, 4095, logFile))
    {
        RequestData_t reqData;
        parseLine(std::string(line), reqData);

        if (reqData.getDate() == yesterday)
        {
            log->totalIn += reqData.getInput();
            log->totalOut += reqData.getOutput();
        }
    }

    fclose(logFile);

    return *log;
}

void parseLine(std::string line, RequestData_t &reqData)
{
    uint wordNum = 1;
    bool inQuotes = false;
    uint datePos = 0;
    for (uint n = 0; n < line.size(); ++n)
    {
        if (line[n] == ' ' && !inQuotes)
        {
            // pokud mame mezeru, skocime na dalsi slovo,
            // pokud nejsme v uvozovkach
            ++wordNum;
        }
        else if (line[n] == '"' || line[n] == '[' || line[n] == ']')
        {
            // mame uvozovky, otevreme nebo uzavreme retezec
            inQuotes = !inQuotes;
        }
        else
        {
            // pridame znak do slova
            switch (wordNum)
            {
                case 4:
                    // 24/Jan/2009:21:01:30 +0100
                    switch (datePos)
                    {
                        case 0:
                        case 1:
                            reqData.day += line[n];
                            break;
                        case 3:
                        case 4:
                        case 5:
                            reqData.month += line[n];
                            break;
                        case 6:
                            reqData.month = getMonth(reqData.month);
                            break;
                        case 7:
                        case 8:
                        case 9:
                        case 10:
                            reqData.year += line[n];
                            break;
                    }
                    ++datePos;
                    break;
                case 10:
                    reqData.input += line[n];
                    break;
                case 11:
                    reqData.output += line[n];
                    break;
            }
        }
    }
}

std::string getMonth(std::string monthStr)
{
    if (monthStr == "Jan")
        return "01";
    if (monthStr == "Feb")
        return "02";
    if (monthStr == "Mar")
        return "03";
    if (monthStr == "Apr")
        return "04";
    if (monthStr == "May")
        return "05";
    if (monthStr == "Jun")
        return "06";
    if (monthStr == "Jul")
        return "07";
    if (monthStr == "Aug")
        return "08";
    if (monthStr == "Sep")
        return "09";
    if (monthStr == "Oct")
        return "10";
    if (monthStr == "Nov")
        return "11";
    if (monthStr == "Dec")
        return "12";

    return "00";
}
