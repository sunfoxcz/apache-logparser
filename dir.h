
#ifndef DIR_H
#define DIR_H

#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <errno.h>

int getdir(std::string dir, std::vector<std::string> &files);

#endif /* LOGPARSE_H */
