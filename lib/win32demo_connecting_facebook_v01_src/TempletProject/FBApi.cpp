//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#include "FBApi.h"
#include "UT.h"
#include "HttpClient.h"

#include "FBFqlBuilder.h"
#include "GraphApiManager.h"
#include "UserObject.h"


FBApi* FBApi::_instance = NULL ;
QString FBApi::API_KEY			= API_KEY_CONST;
QString FBApi::APPLICATION_ID	= APPLICATION_ID_CONST;
QString FBApi::APP_SECRET		= APP_SECRET_CONST;
QString FBApi::GENERAL_API_URL	= GENERAL_API_URL_CONST;
QString FBApi::FQL_MULTIQUERY_API_URL = FQL_MULTIQUERY_API_URL_CONST;

 
 
FBApi::FBApi()
{
  m_notification_info_LastCreated_time = 0;
  m_message_info_LastCreated_time = 0;
}


FBApi* FBApi::getInstance()
{
    
 	if(_instance == NULL)
    {
        _instance = new FBApi();
        
    }
    return _instance;
}

void FBApi::SetApiKeys(const QString& fbSecretKey,
					   const QString& fbSessionKey,
					   const QString& fbuIdKey,
					   const QString& fbSigKey
					   )
{
	m_fbSecretKey = fbSecretKey;
	m_fbSessionKey = fbSessionKey;
	m_fbuIdKey = fbuIdKey;
	m_fbSigKey = fbSigKey;

	 
}



bool FBApi::InvokeAPI(REQ_METHOD req,
                     QMap<QString,QString>& ApiArgsMap,
					 QString& response,
					 QString& BaseUrl,
					 int iTimeOutInterval)
{
	 
	if(req == FBApi::POST)
	{
		if(HttpClient::getInstance()->PostRequest(response,ApiArgsMap,BaseUrl,iTimeOutInterval))
    	{
			return true;
		}
	} 
	else 
	{

		if(HttpClient::getInstance()->GetRequest(response,ApiArgsMap,BaseUrl,iTimeOutInterval))
    	{
			return true;
		}
	}
	return false;
}

QUrl FBApi::GetAutonticationURL()
{
     //add Permissions here or remove
	 QStringList ScopParames;
     // ScopParames << "user_activities";
    // ScopParames << "user_groups";
    //  ScopParames << "user_interests";
    // ScopParames << "user_likes";
    // ScopParames << "user_notes";
    // ScopParames << "user_online_presence";
    // ScopParames << "user_status";
    //  ScopParames << "read_friendlists";
    // ScopParames << "read_requests";
     ScopParames << "offline_access";
    // ScopParames << "friends_activities";
    //  ScopParames << "friends_events";
     //ScopParames << "friends_groups";
    //  ScopParames << "friends_likes";
     // ScopParames << "friends_notes";
    // ScopParames << "friends_online_presence";
     ScopParames << "publish_stream";
     //ScopParames << "read_mailbox";
    //  ScopParames << "read_stream"; 
	 //ScopParames << "xmpp_login";
     
     QUrl AutonticationUrl;
     AutonticationUrl.setUrl("https://www.facebook.com/dialog/oauth");
     AutonticationUrl.addQueryItem("client_id",FBApi::getInstance()->GetAPPLICATION_ID());
     AutonticationUrl.addQueryItem("redirect_uri","http://www.facebook.com/connect/login_success.html");
     AutonticationUrl.addQueryItem("type","user_agent");
     AutonticationUrl.addQueryItem("display","popup");
     AutonticationUrl.addQueryItem("scope",ScopParames.join(","));
     AutonticationUrl.addQueryItem("response_type","token");
     
    
     WRITELOG(AutonticationUrl.toString());
	 
     return AutonticationUrl;

}
 

bool FBApi::AuthorizAndAuthenticatUser(const QString& json)
{

	QMap<QString,QString> JsonSessionMap;
	//needed to init the map for the first api call to FB 
	JsonSessionMap["access_token"] = json ;
	 
    FBApi::getInstance()->SetAccessToken(json);
	return true;
 
}

void FBApi::ParseJsonFromHTTP(const QString& http_response,QMap<QString,QString>& JsonSessionMap)
{	 
	QRegExp rx;
    rx.setMinimal(true);
	rx.setPattern("\"session_key\":\"(.*)\",");
	if(rx.indexIn(http_response)>0)
	{
		JsonSessionMap["session_key"] = rx.cap(1);
	}
	rx.setPattern("\"uid\":(.*),");
	if(rx.indexIn(http_response)>0)
	{
		JsonSessionMap["uid"] = rx.cap(1);
	}	
	rx.setPattern("\"expires\":(.*)\",");
	if(rx.indexIn(http_response)>0)
	{
		JsonSessionMap["expires"] = rx.cap(1);
	}
	rx.setPattern("\"secret\":\"(.*)\",");
	if(rx.indexIn(http_response)>0)
	{
		JsonSessionMap["secret"] = rx.cap(1);
	}	
	rx.setPattern("\"sig\":\"(.*)\"");
	if(rx.indexIn(http_response)>0)
	{
		JsonSessionMap["sig"] = rx.cap(1);
	}

}


void FBApi::GetUserNotifications()
{
     
 	QMap<QString,QString> args1;
	
	// meir need to do with this something :
	QString message_info_lastDate      = QString::number(m_message_info_LastCreated_time);              
	QString notification_info_lastDate = QString::number(m_notification_info_LastCreated_time);

    //------------------------------------------------------
	QVector <StringPer > multiFql;
	StringPer sp1,sp2,sp3,sp4,sp5,sp6,sp7;
	sp1.key = "notification_info";
	sp1.val = "SELECT notification_id,sender_id,title_html,body_html,href,title_text,body_text,app_id,created_time,updated_time "
			   "FROM notification WHERE recipient_id="+m_mainUserId+" AND is_unread = 1 AND is_hidden = 0 AND created_time > " +notification_info_lastDate;
			   
	sp2.key = "notification_user_info";
	sp2.val = "SELECT uid, name,first_name,last_name FROM user WHERE uid IN (SELECT sender_id FROM #notification_info)";

	sp3.key = "friends_request_user_info";
	sp3.val = "SELECT uid, name,first_name,last_name FROM user WHERE uid IN (SELECT uid_from FROM #friends_request_info)";
			
	sp4.key = "message_info";
	sp4.val = "SELECT message_id, thread_id,author_id,body,created_time,attachment,viewer_id FROM message WHERE thread_id IN (SELECT thread_id FROM #thread_info) AND created_time > " +message_info_lastDate+ " AND viewer_id="+m_mainUserId;
			
	sp5.key = "message_user_info";
	sp5.val = "SELECT uid, name,first_name,last_name FROM user WHERE uid IN (SELECT author_id FROM #message_info)";


	sp6.key = "thread_info";
	sp6.val = "SELECT folder_id,thread_id,subject,updated_time,snippet,snippet_author,parent_message_id FROM thread WHERE folder_id = 0 AND viewer_id="+m_mainUserId;

	sp7.key = "friends_request_info";
	sp7.val = "SELECT uid_from, uid_to FROM friend_request WHERE uid_to="+m_mainUserId;
					  						  				   
	multiFql << sp1 << sp2 << sp3 << sp4 << sp5 << sp6 << sp7;
	QString Notification_query = FBFqlBuilder::getInstance()->BuildJoinQuery(multiFql);
	WRITELOG(FBFqlBuilder::getInstance()->BuildJoinQuery(multiFql));


	args1.insert("queries",Notification_query);
	args1.insert("format","json");
	args1.insert("access_token",FBApi::getInstance()->GetUserAccessToken());
	
	QString response1;

	FBApi::getInstance()->InvokeAPI(FBApi::POST,
	                                args1,
	                                response1,
									FBApi::getInstance()->GetFQL_MULTIQUERY_API_URL(),
									API_REQUEST_TIMEOUT_INTERVAL);

	
 
    
	UT::getInstance()->LogToFile("Rerutend from API:"+response1);


}

bool FBApi::ParseJsonGroupIds(QString& response1,QVector<StringPer>*& batchVectorResult)
{
    
    Json::Value UserRoot;
	if(!ValidetJson(response1,UserRoot))
		return false;
	int code = 0;
	std::string bodyValue = "";	
	for ( unsigned int index = 0; index < UserRoot.size(); ++index )  // Iterates over the sequence elements.
	{
		 Json::Value text = UserRoot[index];
		 Json::Value code = text["code"];
		 Json::Value body = text["body"];
		 
		 if(code.type() == Json::ValueType::intValue)
		 {
		   code = text["code"].asInt();
		    
		 }
		 
		 
		 if(body.type() == Json::ValueType::stringValue)
		 {
		    bodyValue = text["body"].asString();
		    QString Qbody = QString::fromStdString(bodyValue);
		    Json::Value UserBodyRoot;
		    if(!ValidetJson(Qbody,UserBodyRoot))
		        return false;
		        
		    std::string s = UserBodyRoot.toStyledString();
		    const Json::Value datas = UserBodyRoot["data"];

		     
		    for ( unsigned int ind = 0; ind < datas.size(); ++ind )  // Iterates over the sequence elements.
	        {
		         Json::Value bodytext = datas[ind];
		         Json::Value updated_time = bodytext["updated_time"];
		         Json::Value userId = bodytext["id"];
		         QString QuserId = QString::fromStdString(userId.asString());
		         StringPer per;
		         per.key = QString::number(updated_time.asInt());
		         per.val = QuserId.split("_").at(0);
		         batchVectorResult->push_back(per);
		         break; 
		    }
		    WRITELOG(Qbody);
		   
		 }
		  
	}	
	 
  return true;
}


bool FBApi::GetUserLoggedInInfo()
{
	
	QString meurl = GetGENERAL_API_URL()+"/me";
	QMap<QString,QString> args1;
	QString response1;
  	args1.insert("access_token",GetUserAccessToken());
	FBApi::getInstance()->InvokeAPI(FBApi::GET,
	                                args1,
	                                response1,
									meurl,
									-1);

	UT::getInstance()->LogToFile("Rerutend from API:"+response1);

	//MEIR need to make api error check response ..
	Json::Value UserRoot;
	if(!ValidetJson(response1,UserRoot))
		return false;
	 
	const Json::Value userId = UserRoot["id"];
	const Json::Value userName = UserRoot["name"];
	const Json::Value userFirstName = UserRoot["first_name"];
	const Json::Value userLastName = UserRoot["last_name"];
	const Json::Value userLink = UserRoot["link"];
	const Json::Value UserUserName = UserRoot["username"];

	QString QuserId = QString::fromStdString(userId.asString());
	QString QuserName = QString::fromStdString(userName.asString());
	QString QuserFirstName = QString::fromStdString(userFirstName.asString());
	QString QuserLastName = QString::fromStdString(userLastName.asString());
	QString QuserLinkName = QString::fromStdString(userLink.asString());
	QString QuserUserName = QString::fromStdString(UserUserName.asString());

    UserObject* pUserObjec = new UserObject();
	pUserObjec->SetUserid(QuserId);
	pUserObjec->SetUserName(QuserName);
	pUserObjec->SetUserFirstName(QuserFirstName);
	pUserObjec->SetUserLastName(QuserLastName);
	pUserObjec->SetUserLink(QuserLinkName);
	pUserObjec->SetUserUserName(QuserUserName);
		
	GraphApiManager::getInstance()->SetUserByName(MAIN_USER,pUserObjec);
    m_mainUserId = GraphApiManager::getInstance()->GetUserObjByName(MAIN_USER)->GetUserid();

	return true;
}


bool FBApi::GetGroupLastUpdate(const QString& GroupID)
{
    
    QString meurl = GetGENERAL_API_URL()+"/"+GroupID+"/feed";
	QMap<QString,QString> args1;
	
	args1.insert("limit","1");
	args1.insert("fields","updated_time");
 	args1.insert("date_format","U");
	QString response1;
  	args1.insert("access_token",GetUserAccessToken());
	if(!FBApi::getInstance()->InvokeAPI(FBApi::GET,
	                                args1,
	                                response1,
									meurl,
									-1))
	    return false;

	WRITELOG("Rerutend from API:"+response1);
    //ConvertTimeStampToDateTime
    Json::Value UserRoot;
	if(!ValidetJson(response1,UserRoot))
		return false;
    
    const Json::Value GroupUpdatedTime = UserRoot["updated_time"];
    QString QGroupUpdatedTime = QString::number(GroupUpdatedTime.asInt());
    QString DateTime ="";
    UT::getInstance()->ConvertTimeStampToDateTime(QGroupUpdatedTime,DateTime);
    WRITELOG(DateTime);
	
	
	
    return true;

}

bool FBApi::GetUserGroupList(const QString& UserId)
{
	QString meurl = GetGENERAL_API_URL()+"/"+UserId+"/groups";
	QMap<QString,QString> args1;
	QString response1;
  	args1.insert("access_token",GetUserAccessToken());
	if(!FBApi::getInstance()->InvokeAPI(FBApi::GET,
	                                args1,
	                                response1,
									meurl,
									-1))
	    return false;

	WRITELOG("Rerutend from API:"+response1);
	
	Json::Value UserRoot;
	if(!ValidetJson(response1,UserRoot))
		return false;

	const Json::Value datas = UserRoot["data"];
	for ( unsigned int index = 0; index < datas.size(); ++index )  // Iterates over the sequence elements.
	{
		 Json::Value text = datas[index];
		
		 std::string sGroupName = text["name"].asString();
		 QString QGroupName = QString::fromStdString(sGroupName);
		 
 		 std::string txtGroupId = text["id"].asString();
		 QString QtxtGroupId = QString::fromStdString(txtGroupId);
		 std::string txtGroupLink = text["link"].asString();
		 QString QtxtGroupLink = QString::fromStdString(txtGroupLink);
		 WRITELOG(QGroupName +" "+QtxtGroupId+" "+QtxtGroupLink);
		 Group* pGroup = new Group();
		 pGroup->SetGroupId(QtxtGroupId);
		 pGroup->SetGroupName(QGroupName);
		 pGroup->SetGroupLink(QtxtGroupLink);
		 GraphApiManager::getInstance()->GetUserObjByName(MAIN_USER)->SetUserGroupByKey(QtxtGroupId,pGroup);
		 
		 
	}


 return true;

}


bool FBApi::GetGroupsUpdateTime(const QStringList batchReqList,QVector <QString>*& BatchRequestStr)
{
    
	
	QString response1;
	
	
	/*if(!GetBatchRequest(batchReqList,BatchRequestStr))
	{
		return false;
	}*/


	/*if(!ExecuteBatchRequest(response1,BatchRequestStr))
	{
		return false;
	}*/

	return true;
}


/*
this function will excute batch string 
fb limit the call to GetBatchRequest::iReqlimit requreds so we need to split 
the call .
the vector allready contains the spliting json calls 15 in each element 

*/
bool FBApi::ExecuteBatchRequest(QString& response1,const QString& BatchRequestStr)
{
	
	
	
	QString meurl = GetGENERAL_API_URL();
	QMap<QString,QString> args1;
	//QString response1;
	
	args1.insert("batch",BatchRequestStr);
  	args1.insert("access_token",GetUserAccessToken());
	if(!FBApi::getInstance()->InvokeAPI(FBApi::POST,
	                                args1,
	                                response1,
									meurl,
									API_GET_GROUP_REQUEST_TIMEOUT_INTERVAL))
	    return false;

	WRITELOG("Rerutend from API:"+response1);
	
	/*Json::Value UserRoot;
	if(!ValidetJson(response1,UserRoot))
		return false;
	

	 */

	return true;
}
/*

build batch api call 

*/
//bool FBApi::GetBatchRequest(const QStringList batchReqList,
//							QVector<QString>*& batchVectorResult,
//							int typeOfQuery,
//							QHash<QString,QString>* moreParames)
//{
//  
// QString jsonBatchQuery ="";
//  
// //the limit of each element in the vector
// int iReqlimit = 10;
// 
// int reqCount = 0;
// for(int i = 0 ; i < batchReqList.size();++i)
// {
//	 
//	 if(reqCount == 0)
//	 {
//		jsonBatchQuery.append("[");
//		WRITELOG(jsonBatchQuery)
//	 }
//	 jsonBatchQuery.append("{\"method\":\"GET\",\"relative_url\":\""+ batchReqList.at(i) +"/feed?date_format=U&limit=1&fields=updated_time\"}");
//	 if(reqCount < iReqlimit)
//	 {
//		jsonBatchQuery.append(",");	
//		WRITELOG(jsonBatchQuery)
//	 }
//	 if(reqCount == iReqlimit)
//	 {
//		reqCount = 0;
//		jsonBatchQuery.append("]");
//		WRITELOG(jsonBatchQuery)
//		batchVectorResult->append(jsonBatchQuery);
//		jsonBatchQuery = "";
// 
//	 }
//	 else
//	 {
//		 //end of data , under 15 
//		 if(i == (batchReqList.size()-1))
//		 {
//			 jsonBatchQuery.append("]");
//			 batchVectorResult->append(jsonBatchQuery);
//		 }
//		 ++reqCount;
//	 }
//	 
// }
//
//
// for (int i = 0; i < batchVectorResult->size(); ++i) {
//	 WRITELOG(batchVectorResult->at(i))
// }
// 
//
// return true;   
//}

bool FBApi::ValidetJson(QString& jsonResponse0,Json::Value& UserRoot0)
{
	std::string jsonResponse(jsonResponse0.toLatin1());
	//Json::Value UserRoot;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( jsonResponse, UserRoot0 );
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		std::string ss;
		ss.append("Failed to parse configuration ");
		ss.append(reader.getFormatedErrorMessages());
		QString s0 = QString::fromStdString(ss);
		WRITELOG(s0); 
		return false;
		 
	}
	return true;

}
 
