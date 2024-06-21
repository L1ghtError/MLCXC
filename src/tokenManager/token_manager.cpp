#include "tokenManager/token_manager.hpp"
#include "utils/string_util.hpp"

#define INVALID_POS -1

mlcxc::ReturnStatus mlcxc::TokenManager::getFile(std::ifstream& inFile)
{
    inFile.seekg(0, std::ios::end);
    int size = inFile.tellg();
    inFile.seekg(0, std::ios::beg);
    std::string word = "";
       while (std::getline(inFile,word))
       {
           insertString(encoding_conv.from_bytes(word));
       }
    std::vector<mlcxc::string_t> val = getWords();
    //delete[] word;
    return mlcxc::ReturnStatus::kOk;
}
// Receives a text chunk, then splits it on logical parts,
// collects some data and text inside tokens vector
// 
// Function requirements is: chunks should not contain not finished word like `str\r\nuct`
// all additional mutation should be preformed in function-caller,
// this function shouldn't mutate chunk, when data is saved it should be copied
// 
// Returns  `ReturnStatus`

mlcxc::ReturnStatus mlcxc::TokenManager::insertString(const mlcxc::string_t& chunk)
{
    bool isQuote = 0;
    size_t wordStart = INVALID_POS;
    size_t length = 0;
    mlcxc::TokensData tokensData;
    int i = 0;
    for(; chunk[i] != 0;i++)
    {
        if(chunk[i] == mlcxc::quotes_sym[0])
        {
            if(isQuote == 1)
            {
                isQuote = 0;
            }else
            {
                isQuote = 1;
            }
        }
        if((std::isalnum(chunk[i],mlcxcLocale)|| chunk[i] == '_') && isQuote == 0)
        {
            wordStart = wordStart == INVALID_POS ? i : wordStart;
            ++length;
            continue;
        }
        quote_skip:
        if(length != 0)
        {
            tokensData.chunkMI.push_back({ wordStart, length });
            wordStart = INVALID_POS;
            length = 0;
            wordsCount++;
        }
    }
    tokensData.chunk = chunk;
    tokens.push_back(tokensData);
    return mlcxc::ReturnStatus::kOk;
}

std::vector<mlcxc::string_t> mlcxc::TokenManager::getSubstitutedWords(const std::vector<mlcxc::string_t>& input)
{
    // @vashchyshyn-I TODO: input and tokens size validaton
    std::vector<string_t> output;
    output.reserve(tokens.size());

    int input_i = 0;
    for (int i = 0; i < tokens.size(); i++)
    {
        string_t origText = tokens[i].chunk;
        string_t processedChunk = L"";
        size_t chunk_start = 0;
        if(tokens[i].chunkMI.size() == 0)
        {
            output.push_back(origText);
            continue;
        }
        for (int j = 0; j < tokens[i].chunkMI.size(); j++)
        {
            
            size_t word_start = tokens[i].chunkMI[j].word_start;
            size_t length = tokens[i].chunkMI[j].length;
            size_t chunk_end = j + 1 == tokens[i].chunkMI.size() ? origText.size() : tokens[i].chunkMI[j + 1].word_start;

            string_t cur_pref = origText.substr(chunk_start, word_start - chunk_start);
            string_t cur_data = input[input_i];
            string_t cur_post = origText.substr(word_start + length, chunk_end - (word_start + length));
            processedChunk += cur_pref + cur_data + cur_post;
            chunk_start = chunk_end;
            input_i++;
        }
        output.push_back(processedChunk);
    }
    return output;
}

std::vector<mlcxc::string_t> mlcxc::TokenManager::getWords()
{
    std::vector<mlcxc::string_t> output;
    output.reserve(wordsCount);
    for(int i=0;i<tokens.size();i++)
    {
        for(int j=0;j<tokens[i].chunkMI.size();j++)
        {
            output.emplace_back(tokens[i].chunk.c_str() + tokens[i].chunkMI[j].word_start, tokens[i].chunkMI[j].length);
        }
    }
    return output;
}
