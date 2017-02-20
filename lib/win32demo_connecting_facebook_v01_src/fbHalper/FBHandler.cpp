#include "FBHandler.h"
#include "Logger.h"



FBHandler::FBHandler()
{
	//init the curl 
	m_CUrlWrapper = new CUrlWrapper();
}


FBHandler::~FBHandler()
{
}


/*
invoke http post request 
    CURLcode: returned http error codes 
    szResponseContent : http response
    url:the url to post 
    httpParames: http parames key,value per inside each vector element
	IsHttps: bool indicator to https or http request

*/

bool FBHandler::InvokeHttp(bool IsPost,
                            bool IsHttps,
							CURLcode& result,
							std::string& szResponseContent,
							const std::string& url,
							std::vector<HttpPer*> httpParames)
 {     
     if(m_CUrlWrapper->InitHttpCurl(IsPost,IsHttps,result,url,szResponseContent,httpParames))
			return true;
	 	 
    return false; 
 } 
  
bool FBHandler::ValidetJson(std::string& jsonResponse0,Json::Value& UserRoot0)
{
	std::string jsonResponse(jsonResponse0);
	//Json::Value UserRoot;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( jsonResponse, UserRoot0 );
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		std::string ss;
		ss.append("Failed to parse configuration ");
		ss.append(reader.getFormatedErrorMessages());
        Logger::getInstance()->writeToLog(ss);
		 
		return false;
		 
	}
	return true;

}

 