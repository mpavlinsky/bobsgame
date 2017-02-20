// fbHalper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "fbHalper.h"
#include "FBHandler.h"
#include "ProcessHandler.h"
#include "Logger.h"

using namespace std;  





 
// This is an example of an exported variable
FBHALPER_API int nfbHalper=0;
//this variable will hold the facebook token 
//@meiry
string szFBtoken ="";
//bool that indicate if the facebook token successed
//@meiry
bool bGotFBtoken = false;// This is an example of an exported function.
FBHALPER_API int fnfbHalper(void)
{
	return 42;
}
/*

const Json::Value userId = UserRoot["id"];
	const Json::Value userName = UserRoot["name"];
	const Json::Value userFirstName = UserRoot["first_name"];
	const Json::Value userLastName = UserRoot["last_name"];
	const Json::Value userLink = UserRoot["link"];
	const Json::Value UserUserName = UserRoot["username"];
*/
bool CfbHalper::getUserInfo(map<std::string,std::string>& userDate)

{
    string s("Start getting user data ");
    Logger::getInstance()->writeToLog(s);
    //check if the access token succesfull recived 	
    if(bGotFBtoken)
    {
        string szHtmlContent=""; 
	    CURLcode result;
	    FBHandler fBHandler;
	    //Graph  Api main url to invoke API's
	    string url ="https://graph.facebook.com/me";
        //the publish api parames http://developers.facebook.com/docs/reference/api/post/	  
	    vector<HttpPer*> httpParamesVec;
 	    httpParamesVec.push_back(new HttpPer("access_token",szFBtoken));
 	 
	    
	    
  	    try{
    		 //invoke the publish to wall api with https request 
		     fBHandler.InvokeHttp(false,true,result,szHtmlContent,url,httpParamesVec);
		     
		     Logger::getInstance()->writeToLog(szHtmlContent);
		     //find if the api returned Exception 
		     size_t found=szHtmlContent.find("OAuthException");
             if (found!=string::npos)
             {
                //printf("The Graph Api returned OAuthException Error");
                 string s("getting user data  Api returned OAuthException Error when sending to app wall");
                 Logger::getInstance()->writeToLog(s);
                 return false;
             }
             Json::Value UserRoot;
	         if(!FBHandler::ValidetJson(szHtmlContent,UserRoot))
	         {
		        return false;
		     }
		     else
		     {
		        const Json::Value userId = UserRoot["id"];
	            const Json::Value userName = UserRoot["name"];
	            const Json::Value userFirstName = UserRoot["first_name"];
	            const Json::Value userLastName = UserRoot["last_name"];
	            const Json::Value userLink = UserRoot["link"];
	            const Json::Value UserUserName = UserRoot["username"];
	             
                userDate["id"] = userId.asString();
                 string s("The user data that got from ");
                Logger::getInstance()->writeToLog(userDate["id"]);
        
             	userDate["name"] = userName.asString();
             	Logger::getInstance()->writeToLog(userDate["name"]);
	            userDate["first_name"] = userFirstName.asString();
	            Logger::getInstance()->writeToLog(userDate["first_name"]);
	            userDate["last_name"] = userLastName.asString();
	            Logger::getInstance()->writeToLog(userDate["last_name"]);
	            userDate["link"] = userLink.asString();
	            Logger::getInstance()->writeToLog(userDate["link"]);
	            userDate["username"] = UserUserName.asString();
	            Logger::getInstance()->writeToLog(userDate["username"]); 
		     }
		        

         } catch (exception& e)
         {
             
              //printf(e.what());
             string s(e.what());
             Logger::getInstance()->writeToLog(s);
             // cout << "exception: "<< e.what() << endl;
         }
    	    
    }
    else
    {   
        //printf("TheButtonCallback2:facebook token are invalied!!");
         string s("getting user data :facebook token are invalied!!");
         Logger::getInstance()->writeToLog(s);
    }
     string ss("Done getting user data ");
     Logger::getInstance()->writeToLog(ss);
    return true;
}



string CfbHalper::returnToken()
{
    string s("Starting to return the access token");
    Logger::getInstance()->writeToLog(s);
    ProcessHandler* processHandler = new ProcessHandler();
    string fullPathToExe =  "TempletProject.exe";//"G:\\c++\\qt\\qt4.7\\OpenGL_bridge\\09_ButtonClicks\\TempletProject.exe";
 	if(processHandler->InitProcessHandlerPoco(szFBtoken,fullPathToExe))
	{
	    //here you can add some fancy error checking of the returned value 
	    //is vailed and not containes 
	    //printf("FB token:%s\n",szFBtoken.c_str());
	    string s("Successfully got access token");
        Logger::getInstance()->writeToLog(s);
	    bGotFBtoken = true;
		 
	    
	    
	}
	else
	{
	   // printf("Error in processHandler");
	    string s("Error retrieving got access token");
        Logger::getInstance()->writeToLog(s);
	}
	
	return szFBtoken;
}
bool CfbHalper::sendToUserWall(std::string str)
{
    string s("Start sending to User Wall");
    Logger::getInstance()->writeToLog(s);
	Logger::getInstance()->writeToLog(str);

    //check if the access token succesfull recived 	
    if(bGotFBtoken)
    {
        string szHtmlContent=""; 
	    CURLcode result;
	    FBHandler fBHandler;
	    //Graph  Api main url to invoke API's
	    string url ="https://graph.facebook.com/me/feed";
        //the publish api parames http://developers.facebook.com/docs/reference/api/post/	
        /*
         userDate["id"] = userId.asString();
             	userDate["name"] = userName.asString();
	            userDate["first_name"] = userFirstName.asString();
	            userDate["last_name"] = userLastName.asString();
	            userDate["link"] = userLink.asString();
	            userDate["username"] = UserUserName.asString(); 
        */
        
       /* string msg ="Thank you ";
        msg.append(userMap["first_name"]);
        msg.append(" ");
        msg.append(userMap["last_name"]);
         msg.append(" ");
        msg.append(userMap["link"]);
        msg.append("\r\n");
        msg.append(" for using the demo");*/
        string s("The Massage String to be send");
        Logger::getInstance()->writeToLog(s);
       // Logger::getInstance()->writeToLog(msg);
	    vector<HttpPer*> httpParamesVec;
 	    httpParamesVec.push_back(new HttpPer("access_token",szFBtoken));
	    httpParamesVec.push_back(new HttpPer("message",str));
	    httpParamesVec.push_back(new HttpPer("link","http://code.google.com/p/facebook-cpp-graph-api/"));
	    //httpParamesVec.push_back(new HttpPer("picture",""));
	    httpParamesVec.push_back(new HttpPer("name","http://code.google.com/p/facebook-cpp-graph-api/"));
	    //httpParamesVec.push_back(new HttpPer("caption","3p_webb_bow.jpg caption"));
	    httpParamesVec.push_back(new HttpPer("description","Send with the help of facebook-cpp-graph-api demo"));
	    
	    
	    
  	    try{
    		 //invoke the publish to wall api with https request 
		     fBHandler.InvokeHttp(true,true,result,szHtmlContent,url,httpParamesVec);
		      
		     //find if the api returned Exception 
		     size_t found=szHtmlContent.find("OAuthException");
             if (found!=string::npos)
             {
                //printf("The Graph Api returned OAuthException Error");
                 string s("The Graph Api returned OAuthException Error when sending to user wall");
                 Logger::getInstance()->writeToLog(s);
                 return false;
             }

         } catch (exception& e)
         {
             
              //printf(e.what());
             string s(e.what());
             Logger::getInstance()->writeToLog(s);
             return false;
             // cout << "exception: "<< e.what() << endl;
         }
    	    
    }
    else
    {   
        //printf("TheButtonCallback2:facebook token are invalied!!");
         string s("facebook token are invalied!!");
         Logger::getInstance()->writeToLog(s);
         return false;
    }
     string ss("Done sending to User Wall");
     Logger::getInstance()->writeToLog(ss);
     return true;
}

bool CfbHalper::sendToAppWall(std::string str)
{
    string s("Start sending to Application Wall");
    Logger::getInstance()->writeToLog(s);
	Logger::getInstance()->writeToLog(str);
    //check if the access token succesfull recived 	
    if(bGotFBtoken)
    {
        string szHtmlContent=""; 
	    CURLcode result;
	    FBHandler fBHandler;
	    //Graph  Api main url to invoke API's
	    string url ="https://graph.facebook.com/189927794387507/feed";
        //the publish api parames http://developers.facebook.com/docs/reference/api/post/	
        /*
         userDate["id"] = userId.asString();
             	userDate["name"] = userName.asString();
	            userDate["first_name"] = userFirstName.asString();
	            userDate["last_name"] = userLastName.asString();
	            userDate["link"] = userLink.asString();
	            userDate["username"] = UserUserName.asString(); 
        */
        
       /* string msg ="Thank you ";
        msg.append(userMap["first_name"]);
        msg.append(" ");
        msg.append(userMap["last_name"]);
        msg.append(" ");
        msg.append(userMap["link"]);
        msg.append("\r\n");
        msg.append(" for using the demo");
        string s("The Massage String to be send");*/
        Logger::getInstance()->writeToLog(s);
       // Logger::getInstance()->writeToLog(msg);
        
	    vector<HttpPer*> httpParamesVec;
 	    httpParamesVec.push_back(new HttpPer("access_token",szFBtoken));
	    httpParamesVec.push_back(new HttpPer("message",str));
	    httpParamesVec.push_back(new HttpPer("link","http://code.google.com/p/facebook-cpp-graph-api/"));
	    //httpParamesVec.push_back(new HttpPer("picture",""));
	    httpParamesVec.push_back(new HttpPer("name","http://code.google.com/p/facebook-cpp-graph-api/"));
	    //httpParamesVec.push_back(new HttpPer("caption","3p_webb_bow.jpg caption"));
	    httpParamesVec.push_back(new HttpPer("description","Send with the help of facebook-cpp-graph-api demo"));
	    
	    
	    
  	    try{
    		 //invoke the publish to wall api with https request 
		     fBHandler.InvokeHttp(true,true,result,szHtmlContent,url,httpParamesVec);
		      
		     //find if the api returned Exception 
		     size_t found=szHtmlContent.find("OAuthException");
             if (found!=string::npos)
             {
                //printf("The Graph Api returned OAuthException Error");
                 string s("The Graph Api returned OAuthException Error when sending to app wall");
                 Logger::getInstance()->writeToLog(s);
                 Logger::getInstance()->writeToLog(szHtmlContent);
                 
                 return false;
             }

         } catch (exception& e)
         {
             
              //printf(e.what());
             string s(e.what());
             Logger::getInstance()->writeToLog(s);
             return false;
             // cout << "exception: "<< e.what() << endl;
         }
    	    
    }
    else
    {   
        //printf("TheButtonCallback2:facebook token are invalied!!");
         string s("facebook token are invalied!!");
         Logger::getInstance()->writeToLog(s);
         return false;
    }
     string ss("Done sending to Application Wall");
     Logger::getInstance()->writeToLog(ss);
     return true;
}



int  CfbHalper::add(int a,int b)
{
	 
	return a+b;
}
int  CfbHalper::mul(int a,int b)
{
	return a*b;
}
int  CfbHalper::sub(int a,int b)
{
	return a-b;
}

// This is the constructor of a class that has been exported.
// see fbHalper.h for the class definition
CfbHalper::CfbHalper()
{
	 
	 
	 
	return;
}
