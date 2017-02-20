//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#ifndef __FBAPI_H_
#define __FBAPI_H_


#include <QtGui>
#include "UT.h"

class FBApi
{
private: 
  static FBApi* _instance;
  FBApi();
  
  FBApi(const FBApi &);
  FBApi & operator=(const FBApi &);
  
  static QString ContentType;
  static QString FB_REST_URL;
  static QString API_KEY;
  static QString APPLICATION_ID;
  static QString FQL_QUERY_API_URL;
  static QString FQL_MULTIQUERY_API_URL;
  static QString GENERAL_API_URL;
  static QString GROUP_PING_ID;
  QString m_fbSecretKey;
  QString m_fbApiKey;
  QString m_fbuIdKey;   
  QString m_fbAccessToken;
  QString m_fbSessionKey;
  QString m_fbSigKey;

  

 
  


public:
 enum REQ_METHOD {
    GET,
    POST
  };
  static FBApi* getInstance();
  ~FBApi(){} 
  bool Users_getLoggedInUser();
  QString getRestURL(QMap<QString,QString> args);
  void SetApiKeys(const QString& fbSecretKey,
				  const QString& fbSessionKey,
				  const QString& fbuIdKey,
				  const QString& fbSigKey);

  void ParseJsonFromHTTP(const QString& http_response,QMap<QString,QString>& JsonSessionMap);
  bool AuthorizAndAuthenticatUser(const QString& json);
  bool InvokeAPI(REQ_METHOD req,
                QMap<QString,QString>& ApiArgsMap,
                QString& response,
                QString& BaseUrl);
 
  QString GetUserSigKey()
  {
	  return m_fbSigKey;
  }

  
  QString GetUserIdKey()
  {
	  return m_fbuIdKey;
  }

  QString GetUserApiKey()
  {
	  return m_fbApiKey;
  }
  QString GetUserSessionKey()
  {
	  return m_fbSessionKey;
  }
  
  
  QString GetUserSecretKey()
  {
	  return m_fbSecretKey;
  }


  QString GetServerURL()
  {
	  return FB_REST_URL;
  }

  QString GetUserAccessToken()
  {
	  return m_fbAccessToken;
  }

  QString GetAPPLICATION_ID()
  {
	  return APPLICATION_ID;
  }

  QString GetFB_REST_URL()
  {
	  return FB_REST_URL;
  }
   QString GetFAPI_KEY()
  {
	  return API_KEY;
  }

  QString GetGENERAL_API_URL()
  {
	  return GENERAL_API_URL;
  }

  QString GetGROUP_PING_ID()
  {
	  return GROUP_PING_ID;
  }

  
  
  void SetAccessToken(const QString& fbAccessToken)
  {
	 m_fbAccessToken = fbAccessToken;
  }
  QString GetFQL_QUERY_API_URL()
  {
	  return FQL_QUERY_API_URL;
  }
  QString GetFQL_MULTIQUERY_API_URL()
  {
	  return FQL_MULTIQUERY_API_URL;
  }


   
  float callId;
  QString GetNextCall() 
  {
	  return UT::getInstance()->GetCurrentDateTimeAsMiliSecounds();
  }

  struct User {
	QString User_SecretKey;
	QString User_ApiId;
    QString User_uIdKey;
  } User;
  
  
  
  
};

#endif