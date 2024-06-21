#include "processCaller/process_caller_win.hpp"

#define BUFSIZE 4096 

mlcxc::ProcessCallerWin::ProcessCallerWin()
{
}

mlcxc::ProcessCallerWin::~ProcessCallerWin()
{

}

void mlcxc::ProcessCallerWin::ReadFromPipe(void) 

// Read output from the child process's pipe for STDOUT
// and write to the parent process's pipe for STDOUT. 
// Stop when there is no more data. 
{ 
   DWORD dwRead, dwWritten; 
   CHAR chBuf[BUFSIZE]; 
   BOOL bSuccess = FALSE;
   HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

   for (;;) 
   { 
      bSuccess = ReadFile( g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
      if( ! bSuccess || dwRead == 0 ) break; 

      bSuccess = WriteFile(hParentStdOut, chBuf, 
                           dwRead, &dwWritten, NULL);
      if (! bSuccess ) break; 
   } 
} 

mlcxc::ReturnStatus mlcxc::ProcessCallerWin::init()
{
    // Set the bInheritHandle flag so pipe handles are inherited. 
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // Create a pipe for the child process's STDOUT. 
    if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0))
        return ReturnStatus::kAborted;
    // Ensure the read handle to the pipe for STDOUT is not inherited.
    if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
        return ReturnStatus::kAborted;

    // Set up members of the PROCESS_INFORMATION structure.
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

    // Set up members of the STARTUPINFO structure. 
    // This structure specifies the STDIN and STDOUT handles for redirection.
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = g_hChildStd_OUT_Wr;
    siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
    // siStartInfo.hStdInput = g_hChildStd_IN_Rd;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    return ReturnStatus::kOk;
}

mlcxc::ReturnStatus mlcxc::ProcessCallerWin::call(const std::string& command )
{
    init();
    char * comm = (char*)command.c_str();
    //TCHAR szCmdline[] = command.c_str();
    BOOL bSuccess = FALSE;



    bSuccess = CreateProcess(NULL,
                             comm,    // command line
                             NULL,         // process security attributes
                             NULL,         // primary thread security attributes
                             TRUE,         // handles are inherited
                             0,            // creation flags
                             NULL,         // use parent's environment
                             NULL,         // use parent's current directory
                             &siStartInfo, // STARTUPINFO pointer
                             &piProcInfo); // receives PROCESS_INFORMATION

    if (!bSuccess)
        return ReturnStatus::kAborted;
    else
    {
        // Close handles to the child process and its primary thread.
        // Some applications might keep these handles to monitor the status
        // of the child process, for example.

        CloseHandle(piProcInfo.hProcess);
        CloseHandle(piProcInfo.hThread);

        // Close handles to the stdin and stdout pipes no longer needed by the child process.
        // If they are not explicitly closed, there is no way to recognize that the child process has ended.

        CloseHandle(g_hChildStd_OUT_Wr);
        //CloseHandle(g_hChildStd_IN_Rd);
    }
    ReadFromPipe();
    return ReturnStatus::kOk;
}