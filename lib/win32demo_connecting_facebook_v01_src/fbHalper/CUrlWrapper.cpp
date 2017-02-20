#include "CUrlWrapper.h"

CUrlWrapper::CUrlWrapper()
{
	m_pcurl = curl_easy_init(); 
}


CUrlWrapper::~CUrlWrapper()
{
	curl_easy_cleanup(m_pcurl);
    curl_global_cleanup();
    m_pcurl = NULL;
}

/* url for the post */
void CUrlWrapper::setUrl(const std::string& url)
{
    CUrlWrapper::m_szUrl = url;
}

string CUrlWrapper::setUrl()
{
	return CUrlWrapper::m_szUrl;
}
// This is the writer call back function used by curl 
//(void *buffer, size_t sz, size_t n, void *f
void CUrlWrapper::writer(void *buffer, size_t size, size_t nmemb,void* f)
{
  // Call non-static member function.
       static_cast<CUrlWrapper*>(f)->setBuffer((char*)buffer,size,nmemb);

}

int CUrlWrapper::setBuffer(char *buffer, size_t size, size_t nmemb)
{
    // What we will return
  int result = 0;
  
  
  // Is there anything in the buffer?
  if (buffer!=NULL)
  {
    // Append the data to the buffer
    m_szbuffer.append(buffer, size * nmemb);

    // How much did we write?
    result = size * nmemb;
  }
  buffer = NULL ;   
  return result;
}

bool CUrlWrapper::InitHttpCurl( bool IsPost,
                                bool IsHttps,
								CURLcode& result,
								const std::string& url,
								std::string& szbuffer,
								std::vector<HttpPer*> httpParames)
{
    //params
    char *data;
     
    string datastd ="";
     CUrlWrapper::m_szUrl = url;
    // CURLcode result;
     
    if (m_pcurl)
    {
      // Now set up all of the curl options
      //if there is parames
      if(httpParames.size()>0)
      {
        //strcpy(data,(const char *)ConstractHttpParames(httpParames).c_str());
        if(!IsPost)
        {
            datastd.append(m_szUrl);
            datastd.append("?");
        }
         datastd.append(ConstractHttpParames(httpParames));
         data = new char[datastd.size() + 1];
        (char *)ConstractHttpParames(httpParames).c_str();
        std::copy(datastd.begin(), datastd.end(), data);
        data[datastd.size()] = '\0'; // don't forget the terminating 0

        //printf("%s\n",data);
        if(IsPost)
        {
            curl_easy_setopt(m_pcurl, CURLOPT_POST,1);
            curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDS, data);
        }
        //delete[] data;
      }
	  //ssl config
	  if(IsHttps)
	  {
		curl_easy_setopt(m_pcurl, CURLOPT_SSL_VERIFYPEER, 0L); 
		curl_easy_setopt(m_pcurl, CURLOPT_SSL_VERIFYHOST, 0L); 
	  }

      curl_easy_setopt(m_pcurl, CURLOPT_ERRORBUFFER, CUrlWrapper::m_errorBuffer);
      if(IsPost)
        curl_easy_setopt(m_pcurl, CURLOPT_URL,m_szUrl.c_str());
      else  
        curl_easy_setopt(m_pcurl, CURLOPT_URL,data);
        
      curl_easy_setopt(m_pcurl, CURLOPT_HEADER, 0);
      curl_easy_setopt(m_pcurl, CURLOPT_FOLLOWLOCATION, 1);
      curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION,CUrlWrapper::writer);
      curl_easy_setopt(m_pcurl, CURLOPT_WRITEDATA,this);

      // Attempt to retrieve the remote page
      result = curl_easy_perform(m_pcurl);
       
    }

	// Did we succeed?
      if (result != CURLE_OK)
	  {
		return false;
	  }
	   	
	  
	szbuffer = m_szbuffer;
	
	m_szbuffer.clear();
    m_szUrl.clear();
    delete[] data;
    
    /* always cleanup */
  	return true;	
}

 
const string CUrlWrapper::getBuffer()
{
	return m_szbuffer;
}
/*
constract http vaild parames (key=value&key=value)from vector
    paramesVec: key/value parames 

*/
string CUrlWrapper::ConstractHttpParames(vector<HttpPer*> paramesVec)
{
    string parames = "";
    size_t vecSize = paramesVec.size();
    
    for (size_t i=0; i < paramesVec.size(); i++)
    {
       
      string str = "";
      str.append(paramesVec[i]->key);
      str.append("=");
      str.append(paramesVec[i]->value);
      if(i < (vecSize-1)) 
        str.append("&");
      parames.append(str);
    }
    //printf("url params %s",parames.c_str());
    return parames;
}