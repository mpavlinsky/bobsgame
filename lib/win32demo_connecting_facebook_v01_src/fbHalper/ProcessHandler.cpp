/*----------------------------------------------------------------------------------------
 *	
 *	project:	 
 *	author:		meiryanovich@gmail.com
 *	note:		
 *				 
 *				 
 *
  		 
 */

#include "ProcessHandler.h"
#include <vector>
#include "Poco/Process.h"
#include "Poco/Pipe.h"
#include "Poco/PipeStream.h"


using Poco::Process;
using Poco::ProcessHandle;
using Poco::Pipe;
using Poco::PipeInputStream;
using Poco::PipeOutputStream;


ProcessHandler::ProcessHandler():hChildProcess(NULL),
                                hStdIn(NULL),
                                bRunThread(TRUE),
                                szReturnedChildStdOut(""),
								FullPathToExe("")
 
{
    
}
ProcessHandler::~ProcessHandler()
{
    ;
}

bool ProcessHandler::InitProcessHandlerPoco(string& szReturnedChildStdOutValue,
                                             const string& fullPathToExe )
{
    std::vector<std::string> args;
	 
	Pipe outPipe;
	ProcessHandle ph = Process::launch(fullPathToExe, args, 0, &outPipe, 0);
	PipeInputStream istr(outPipe);
	std::string s;
	int c = istr.get();
	while (c != -1) 
	{ 
	    s += (char) c;
	    c = istr.get();
    }
	 
	int rc = ph.wait();
	szReturnedChildStdOutValue.append(s);
	if(s.size()>5)
	    return true; 
    
   return false;
}

 

