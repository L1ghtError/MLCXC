#ifndef FILE_MANAGER_HPP_
#define FILE_MANAGER_HPP_
#include <filesystem>
#include <functional>
#include <fstream>
#include <vector>

#include "utils/status.hpp"
#include "tokenManager/token_manager.hpp"
namespace mlcxc 
{
class FileManager
{
    public:
    // Loads file/files from `filePath`.
    // Returns `ReturnStatus`.
    mlcxc::ReturnStatus loadInput(const std::string& filePath);

    // Accessor function to get a constant reference to `source_files`
     std::vector<std::pair<std::string, std::ifstream>>& getSourceFiles() {
        return source_files;
    }
    // Saves File
    // First Arg: full file path
    // Second Arg
    mlcxc::ReturnStatus saveFile(const std::string &filePath,const std::vector<mlcxc::string_t>&fileData);
    private:
    // Checks does `filePath` is wildcard
    // Checks does `filePath` already presist in source_files
    // Returns `ReturnStatus`.
    inline bool isFileLoaded(const std::string& filePath);
    inline bool isCCXXExtention(const std::filesystem::path& fileExtension);
    inline mlcxc::ReturnStatus loadFileByPath(const std::string& filePath);
    mlcxc::ReturnStatus loadWildard(const std::string& filePath);
    std::vector<std::pair<std::string,std::ifstream>> source_files;
};
}
#endif  // FILE_MANAGER_HPP_
