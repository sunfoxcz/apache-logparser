
#include "dir.h"

int getdir(std::string dir, std::vector<std::string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if ((dp = opendir(dir.c_str())) == NULL)
    {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        std::string name = std::string(dirp->d_name);
        if (name != "." && name != "..")
        {
            files.push_back(name);
        }
    }
    closedir(dp);
    return 0;
}
