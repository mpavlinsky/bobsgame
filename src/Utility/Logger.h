//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include <mutex>
class Logger;



#if defined(__WINDOWS__)
#include "windows.h"
#endif

class Logger
{
public:
	string name = "";


#if defined(__WINDOWS__)
	static HANDLE hConsole;
#endif

	static ofstream outputFile;
	static bool outputFileInit;
	static mutex log_Mutex;

	Logger();
	Logger(const string& s);
	static void initLogger();
	void log(const string& s);
	void info(const string& s);
	void warn(const string& s);
	void debug(const string& s);
	void error(const string& s);

};

