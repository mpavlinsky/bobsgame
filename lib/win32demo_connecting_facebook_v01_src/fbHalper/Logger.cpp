 


#include "Logger.h"
 
Logger* Logger::_instance = NULL ;
Logger* Logger::getInstance()
{
    if(Logger::_instance == NULL)
    {
        Logger::_instance = new Logger();
    }
    return _instance;
}
 


Logger::Logger() 
{
        std::string name = filename();
	 
		pChannel = new SimpleFileChannel(name);
		pChannel->setProperty(SimpleFileChannel::PROP_ROTATION, "20 K");
		pChannel->open();
	 
}

void Logger::writeToLog(std::string& str)
{
    std::string date = "";
	date.append(DateTimeFormatter::format(Timestamp(),"%Y%m%d%H%M%S"));
	date.append(" ");
	date.append(str);
     Message msg("source",date, Message::PRIO_DEBUG);
    
    pChannel->log(msg);   
}
 
Logger::~Logger()
{
}

 std::string Logger::filename() const
{
	std::string name = "fbHalper";
 	name.append(".log");
	return name;
}


 