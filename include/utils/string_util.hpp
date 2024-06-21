#ifndef STRING_UTIL_HPP_
#define STRING_UTIL_HPP_
#include <string.h>
#define ASTERISK_SYMBOL '*'

namespace mlcxc
{
    using string_t = std::wstring;
    using ofstream_t = std::wofstream;
    const string_t quotes_sym = L"\"";
    
    constexpr size_t string_t_size = sizeof(string_t);
#if defined(_WIN32) || defined(_WIN64)
    #if string_t_size == 1
        const char NEWLINE[] = "\r\n";
    #else
        const wchar_t NEWLINE[] = L"\r\n"; 
    #endif
#else
    #if string_t_size == 1
        const char NEWLINE[] = "\n"; 
    #else 
        const wchar_t NEWLINE[] = L"\n";
    #endif
#endif
    
namespace utils
{
    inline bool is_wildcard(const char* filePath)
    {
        if(strchr(filePath, ASTERISK_SYMBOL) != NULL)
            return true;
        return false;
    }
    inline size_t get_asterisk_position(const char* filePath)
    {
        return strchr(filePath, ASTERISK_SYMBOL) - filePath;
    }
} // namespace utils

} // namespace mlcxc

#endif  // STRING_UTIL_HPP_