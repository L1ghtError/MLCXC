#include "fileManager/file_manager.hpp"
#include "utils/string_util.hpp"

static const std::string H_FILE_EXT = ".h";
static const std::string C_FILE_EXT = ".c";
static const std::string HPP_FILE_EXT = ".hpp";
static const std::string CPP_FILE_EXT  = ".cpp";


bool mlcxc::FileManager::isFileLoaded(const std::string& filePath)
{
    for(int i = 0; i < source_files.size(); i++)
    {
        const std::pair<std::string,std::ifstream> *ptr = &source_files[i];
        if(ptr->first == filePath)
            return true;
    }
    return false;
}

inline bool mlcxc::FileManager::isCCXXExtention(const std::filesystem::path& fileExtension)
{
    return fileExtension == H_FILE_EXT || fileExtension == C_FILE_EXT 
    || fileExtension == HPP_FILE_EXT || fileExtension == CPP_FILE_EXT;
}

mlcxc::ReturnStatus mlcxc::FileManager::loadInput(const std::string& filePath)
{
    if(mlcxc::utils::is_wildcard(filePath.c_str()))
       return loadWildard(filePath);

    std::filesystem::path fPath = std::filesystem::absolute(filePath);
    return loadFileByPath(fPath.string());
}

mlcxc::ReturnStatus mlcxc::FileManager::loadWildard(const std::string& filePath)
{
    std::string directoryPath = filePath.substr(0,mlcxc::utils::get_asterisk_position(filePath.c_str()));
    for(const auto& entry : std::filesystem::directory_iterator(directoryPath))
    {
        if (entry.is_regular_file() && isCCXXExtention(entry.path().extension())) 
        {
            std::filesystem::path fPath = entry.path();
            mlcxc::ReturnStatus status = loadFileByPath(fPath.string());
            if(status != mlcxc::ReturnStatus::kOk)
                return status;
        }
    }
    return mlcxc::ReturnStatus::kOk;
}

mlcxc::ReturnStatus mlcxc::FileManager::loadFileByPath(const std::string& filePath)
{
    std::ifstream file(filePath,std::ios_base::in);
    if(!file)
    {
        return mlcxc::ReturnStatus::kNotFound;
    }
    source_files.emplace_back(filePath, std::move(file));
    return mlcxc::ReturnStatus::kOk;
}

mlcxc::ReturnStatus mlcxc::FileManager::saveFile(const std::string &filePath,const std::vector<mlcxc::string_t>&fileData)
{
    mlcxc::ofstream_t outFile(filePath);
    outFile.imbue(mlcxcLocale);
    if (!outFile.is_open()) {
        return mlcxc::ReturnStatus::kAborted;
    }
    for (const auto& line : fileData) {
        outFile << line << std::endl;
    }
    outFile.close();
    return mlcxc::ReturnStatus::kOk;
}