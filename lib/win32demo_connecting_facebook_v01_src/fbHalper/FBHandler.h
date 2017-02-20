#ifndef FBHANDLER_H
#define FBHANDLER_H
#include "CUrlWrapper.h"
#include "Constants.h"
#include <string>
#include "json.h"


class FBHandler 
{
	public:
		FBHandler();
		~FBHandler();
		bool InvokeHttp(bool IsPost,
		                bool IsHttps,
						CURLcode& result,
		                std::string& szResponseContent,
		                const std::string& url,
		                std::vector<HttpPer*> httpParames);
		

        bool static ValidetJson(std::string& jsonResponse0,Json::Value& UserRoot0);

	private:
		CUrlWrapper*    m_CUrlWrapper;

};

#endif