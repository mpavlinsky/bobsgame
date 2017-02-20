#ifndef PROCESSHANDLER_H
#define PROCESSHANDLER_H
#include<windows.h>
#include<string>
#pragma comment(lib, "User32.lib")
using namespace std;
class ProcessHandler
{

    public:
        ProcessHandler();
        ~ProcessHandler();
        bool InitProcessHandler(string& szReturnedChildStdOutValue,
							   const string& fullPathToExe);
	    bool InitProcessHandlerPoco(string& szReturnedChildStdOutValue,
	                            const string& fullPathToExe);

    
    private:
         bool DisplayError(char *pszAPI);
         void ReadAndHandleOutput(HANDLE hPipeRead);
         void PrepAndLaunchRedirectedChild(HANDLE hChildStdOut,
                                         HANDLE hChildStdIn,
                                         HANDLE hChildStdErr);
         static DWORD WINAPI GetAndSendInputThread(void* Param);
         DWORD ThreadStart(void);
    

         HANDLE hChildProcess;
         HANDLE hStdIn; // Handle to parents std input.
         BOOL bRunThread;
         string FullPathToExe;
         string szReturnedChildStdOut;
    

};


#endif