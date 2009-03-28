
#include "date.h"

std::string getYesterday()
{
    char yesterday[11];
    time_t rawTime = time(NULL);

    struct tm * timeinfo = localtime (&rawTime);
    timeinfo->tm_mday -= 1;
    mktime(timeinfo);

    strftime(yesterday, 11, "%Y-%m-%d", timeinfo);
    return std::string(yesterday);
}
