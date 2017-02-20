#ifndef CURLWRAPPER_H
#define CURLWRAPPER_H
#include <string>
#include <vector>
#include <iostream>  
#include "Constants.h"
#include "curl/curl.h"  


using namespace std;  

class CUrlWrapper 
{

public :
	CUrlWrapper();
	~CUrlWrapper();
    bool InitCurl();
	
	bool InitHttpCurl(bool IsPost,
	                  bool IsHttps,
					  CURLcode& result,
	                  const std::string& url,
	                  std::string& szbuffer,
		              std::vector<HttpPer*> httpParames);

     void setUrl(const std::string& url);
	string setUrl();
	const string getBuffer();



private:
	 static void writer(void *buffer, size_t size, size_t nmemb,void* f);
     int setBuffer(char *buffer, size_t size, size_t nmemb);
     string ConstractHttpParames(vector<HttpPer*> paramesVec);
        // Our curl objects
     CURL *m_pcurl;         
         // Write any errors in here
     char m_errorBuffer[CURL_ERROR_SIZE];
         // Write all expected data in here
     string m_szbuffer;
     string m_szUrl;



};
#endif