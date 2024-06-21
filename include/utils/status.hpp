#ifndef STATUS_HPP_
#define STATUS_HPP_
#include <locale>
#include <codecvt>
static const std::locale mlcxcLocale("uk_UA");
static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> encoding_conv;

static const char *ReturnStatusResolver[]
{
    "Ok",
    "Unknown error",
    "Not Found",
    "Already Exists"
    "Aborted"
};

namespace mlcxc
{
enum class ReturnStatus: int
{
    kOk = 0,
    kUnknown = 1,
    kNotFound = 2,
    kAlreadyExists = 3,
    kAborted = 4,
    kUnimplemented = 5
};
class StatusManager 
{
    public:
    static const char *getErrorMessage(mlcxc::ReturnStatus retStatus)
    {return ReturnStatusResolver[static_cast<int>(retStatus)];};
};
} // namespace mlcxc
#endif  // STATUS_HPP_
