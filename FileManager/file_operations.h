#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <string>

namespace FileOperations {
    void copy(const std::string& source, const std::string& destination);
    void paste(const std::string& source, const std::string& destination);
    void move(const std::string& source, const std::string& destination);
    void remove(const std::string& path);
    void createFile(const std::string& path);
    void createDirectory(const std::string& path);
    void rename(const std::string& oldPath, const std::string& newPath);
    bool fileExists(const std::string& path);
}

#endif // FILE_OPERATIONS_H
