#ifndef TOKEN_MANAGER_HPP_
#define TOKEN_MANAGER_HPP_
#include <vector>
#include <string>
#include <fstream>
#include "iostream"
#include "utils/status.hpp"
#include "utils/string_util.hpp"
//  `TokenManager` holds source data inside.
//  To prevent program form `out-of-memory` wee keep
//  max size of tokens to be 1000.
constexpr size_t INITIAL_TOKENMANAGER_MAX_CAPACITY = 1000;
namespace mlcxc
{

struct TokensData
{
    struct _tokenInternalData
    {
        size_t word_start = 0;
        size_t length = 0;
    };
    std::vector<_tokenInternalData> chunkMI;
    string_t chunk;
};

class TokenManager
{
    public:
    mlcxc::ReturnStatus getFile(std::ifstream& inFile);
    // gives you lines with substituted words from input
    // Returns original lines with new words
    std::vector<string_t> getSubstitutedWords(const std::vector<string_t>& input);
    std::vector<string_t> getWords();
    private:
    mlcxc::ReturnStatus insertString(const string_t& chunk);
    std::vector<TokensData> tokens;
    size_t wordsCount = 0;
    size_t tokensMaxSize = INITIAL_TOKENMANAGER_MAX_CAPACITY;
};
} // namespace mlcxc
#endif  // TOKEN_MANAGER_HPP_