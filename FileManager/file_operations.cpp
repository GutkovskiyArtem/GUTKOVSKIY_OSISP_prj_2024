#include "file_operations.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void FileOperations::copy(const std::string& source, const std::string& destination) {
    fs::copy(source, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
}

void FileOperations::paste(const std::string& source, const std::string& destination) {
    copy(source, destination);
}

void FileOperations::move(const std::string& source, const std::string& destination) {
    fs::rename(source, destination);
}

void FileOperations::remove(const std::string& path) {
    if (path!="." && path!=".."){
        fs::remove_all(path);
    }

}

void FileOperations::createFile(const std::string& path) {
    std::ofstream file(path);
}

void FileOperations::createDirectory(const std::string& path) {
    fs::create_directory(path);
}

void FileOperations::rename(const std::string& oldPath, const std::string& newPath) {
    fs::rename(oldPath, newPath);
}

bool FileOperations::fileExists(const std::string& path) {
    return fs::exists(path);
}
