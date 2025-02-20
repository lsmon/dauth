#ifndef DIRECTORY_HELPER_HPP
#define DIRECTORY_HELPER_HPP

#include <string>
#include <vector>


class DirectoryHelper {
public:
    // Constructor
    DirectoryHelper();

    // Destructor
    ~DirectoryHelper();

    // Method to create a directory
    bool createDirectory(const std::string& path);

    // Method to remove a directory
    bool removeDirectory(const std::string& path);

    // Method to list files in a directory
    std::vector<std::string> listFiles(const std::string& path);

private:
    // Helper method to check if a directory exists
    bool directoryExists(const std::string& path);
};

#endif // DIRECTORY_HELPER_HPP