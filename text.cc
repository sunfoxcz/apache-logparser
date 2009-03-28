
#include "text.h"

std::vector<std::string> split(const std::string &str, char separator,
                                bool includeEmpty)
{
    std::vector<std::string> elements;

    for (std::string::size_type begin = 0, stop = 0, size = str.size();
            ; begin = stop + 1) {
        // check for trailing empty string
        if (!includeEmpty && (begin == size)) break;

        // find separator
        stop = str.find(separator, begin);

        // remember element if allowed
        if ((stop > begin) || includeEmpty)
            elements.push_back(str.substr(begin, stop - begin));

        // terminate on EOS
        if (stop == std::string::npos) break;
    }

    // OK
    return elements;
}

std::string strip(const std::string &str)
{
    // compute start and end of string
    std::string::size_type start = 0;
    std::string::size_type end = str.size();

    while ((start < end) && isspace(str[start]))
        ++start;

    while ((end > start) && isspace(str[end - 1]))
        --end;

    // test for already stripped string
    if ((start == 0) && (end == str.size())) return str;

    // do the strip
    return str.substr(start, end - start);
}
