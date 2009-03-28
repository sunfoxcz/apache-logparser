
#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>

std::vector<std::string> split(const std::string &str, char separator,
                                bool includeEmpty = false);
std::string strip(const std::string &str);

#endif /* TEXT_H */
