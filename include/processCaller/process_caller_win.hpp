#ifndef PROCESS_CALLER_WIN_HPP_
#define PROCESS_CALLER_WIN_HPP_


#include "processCaller/process_caller.hpp"
#include <windows.h>
#define MLCXC_PROC_CALLER_WIN
namespace mlcxc
{
    class ProcessCallerWin : public ProcessCaller
    {
        public:
        ProcessCallerWin();
        ~ProcessCallerWin();
        mlcxc::ReturnStatus init();
        mlcxc::ReturnStatus call(const std::string& command);
        private:
        void ReadFromPipe(void);
        SECURITY_ATTRIBUTES saAttr;
        HANDLE g_hChildStd_OUT_Rd = NULL;
        HANDLE g_hChildStd_OUT_Wr = NULL;
        PROCESS_INFORMATION piProcInfo;
        STARTUPINFO siStartInfo;
    };
}
#endif //PROCESS_CALLER_WIN_HPP_