
#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <string>
#include <vector>

#include "text.h"
#include "date.h"

struct ZoneFile_t {
    std::string serverName;
    std::string logFile;
    std::string logName;
    bool proxyPass;

    ZoneFile_t()
    {
        proxyPass = false;
    };
};

struct LogFile_t {
    uint totalIn;
    uint totalOut;
    std::string date;

    LogFile_t()
    {
        totalIn = 0;
        totalOut = 0;
    };

    std::string getDate()
    {
        return date;
    };
};

struct RequestData_t {
    std::string input;
    std::string output;
    std::string day;
    std::string month;
    std::string year;

    uint getInput()
    {
        if (input != "")
        {
            return atoi(input.c_str());
        }
        return 0;
    };

    uint getOutput()
    {
        if (output != "")
        {
            return atoi(output.c_str());
        }
        return 0;
    }

    std::string getDate()
    {
        return year + "-" + month + "-" + day;
    };
};

ZoneFile_t &parseZone(std::string zoneFileName);
LogFile_t &parseLog(std::string fileName);
void parseLine(std::string line, RequestData_t &reqData);
std::string getMonth(std::string monthStr);

#endif /* PARSE_H */
