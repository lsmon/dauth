#include "util/fio/DirectoryHelper.hpp"
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <errno.h>

DirectoryHelper::DirectoryHelper()
{
}

DirectoryHelper::~DirectoryHelper()
{
}

bool DirectoryHelper::removeDirectory(const std::string &path)
{
    if (rmdir(path.c_str()) == 0)
    {
        return true;
    }
    else
    {
        std::cerr << "Error removing directory: " << strerror(errno) << std::endl;
        return false;
    }
}

std::vector<std::string> DirectoryHelper::listFiles(const std::string &path)
{
    std::vector<std::string> files;
    DIR *dir = opendir(path.c_str());
    if (dir == nullptr)
    {
        std::cerr << "Error opening directory: " << strerror(errno) << std::endl;
        return files;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type == DT_REG)
        {
            files.push_back(entry->d_name);
        }
    }

    closedir(dir);
    return files;
}

bool DirectoryHelper::directoryExists(const std::string &path)
{
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
    {
        return false;
    }
    else if (info.st_mode & S_IFDIR)
    {
        return true;
    }
    else
    {
        return false;
    }
}

