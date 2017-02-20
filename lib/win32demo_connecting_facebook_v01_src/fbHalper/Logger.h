 

#ifndef LOGGER_INCLUDED
#define LOGGER_NCLUDED


#include "Poco/Foundation.h"
#include "Poco/SimpleFileChannel.h"
#include "Poco/Message.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/AutoPtr.h"

using Poco::SimpleFileChannel;
using Poco::Message;
using Poco::Path;
using Poco::File;
using Poco::DirectoryIterator;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::AutoPtr;
 

class Logger 
{
public:
	
	 static Logger* getInstance();
	~Logger();

	void testRotate();

 	void tearDown();
 	void writeToLog(std::string& str);

 

private:
    static Logger* _instance;
    Logger();
	void remove(const std::string& baseName);
	std::string filename() const;
	AutoPtr<SimpleFileChannel> pChannel;
};


#endif  
