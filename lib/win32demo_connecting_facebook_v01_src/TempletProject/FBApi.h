//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#ifndef __FBAPI_H_
#define __FBAPI_H_


#include <QtGui>
#include "Constants.h"
#include "UT.h"
#include "json.h"


class FBApi
{
 
 
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
                QString& BaseUrl,
				int iTimeOutInterval);
 
  QString GetUserSigKey(){return m_fbSigKey;}
  QString GetUserIdKey(){return m_fbuIdKey;}
  QString GetUserApiKey(){return m_fbApiKey;}
  QString GetUserSessionKey(){return m_fbSessionKey;}
  QString GetUserSecretKey() {return m_fbSecretKey;}
  QString GetAPP_SECRET(){return APP_SECRET;}
  QString GetUserAccessToken(){return m_fbAccessToken;}
  QString GetAPPLICATION_ID(){return APPLICATION_ID;}
  QString GetFAPI_KEY(){return API_KEY;}
  QString GetGENERAL_API_URL(){return GENERAL_API_URL;}
  QString GetGROUP_PING_ID(){return GROUP_PING_ID;}
  void SetAccessToken(const QString& fbAccessToken){m_fbAccessToken = fbAccessToken;}
  QString GetFQL_QUERY_API_URL(){return FQL_QUERY_API_URL;}
  QString GetFQL_MULTIQUERY_API_URL(){return FQL_MULTIQUERY_API_URL;}
  QString GetNextCall() { return UT::getInstance()->GetCurrentDateTimeAsMiliSecounds();}
  
  QUrl GetAutonticationURL();
  void GetUserNotifications();
  bool GetUserLoggedInInfo();
  bool GetUserGroupList(const QString& UserId);
  bool GetGroupLastUpdate(const QString& GroupID);
  //bool GetBatchRequest(const QStringList batchReqList,QVector<QString>*& batchVectorResult,QHash<QString,QString>* moreParames);
  bool ExecuteBatchRequest(QString& response,const QString& BatchRequestStr);
  bool GetGroupsUpdateTime(const QStringList batchReqList,QVector <QString>*& BatchRequestStr);
  bool ValidetJson(QString& jsonResponse0,Json::Value& UserRoot0);
  bool ParseJsonGroupIds(QString& response1,QVector<StringPer>*& batchVectorResult);

  
   
private: 
  static FBApi* _instance;
  FBApi();
  
  FBApi(const FBApi &);
  FBApi & operator=(const FBApi &);
  
  static QString ContentType;
  static QString API_KEY;
  static QString APPLICATION_ID;
  static QString FQL_QUERY_API_URL;
  static QString FQL_MULTIQUERY_API_URL;
  static QString GENERAL_API_URL;
  static QString GROUP_PING_ID;
  static QString APP_SECRET;

  QString m_fbSecretKey;
  QString m_fbApiKey;
  QString m_fbuIdKey;   
  QString m_fbAccessToken;
  QString m_fbSessionKey;
  QString m_fbSigKey;

  QString m_mainUserId;

  uint m_notification_info_LastCreated_time;
  uint m_message_info_LastCreated_time;
};

#endif