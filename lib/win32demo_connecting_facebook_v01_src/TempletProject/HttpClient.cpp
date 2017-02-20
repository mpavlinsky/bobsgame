//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#include "HttpClient.h"
#include "UT.h"
#include "FBApi.h"


HttpClient* HttpClient::_instance = NULL;
bool HttpClient::IsUserAutorized = false;
QString DebugStrUrl ="";

HttpClient* HttpClient::getInstance()
{
    if(HttpClient::_instance == NULL)
    {
        HttpClient::_instance = new HttpClient();
    }
    return _instance;
}



void HttpClient::HandleNetworkError(QNetworkReply::NetworkError& networkError)
{
		switch(networkError)
		{
		case(QNetworkReply::ConnectionRefusedError):
			WRITELOG("NO NETWORK CONNECTION ConnectionRefusedError!! ");
			break;
		case(QNetworkReply::HostNotFoundError):
			//handle the html output is no internet connection is found
			WRITELOG("NO NETWORK CONNECTION HostNotFoundError!! ");
			break;
		case(QNetworkReply::SslHandshakeFailedError):
			//handle the html output is no internet connection is found
			WRITELOG("CONNECTION SslHandshakeFailedError!! ");
			break;
		}
		
}
HttpClient::HttpClient()
{
 
  networkManager = new QNetworkAccessManager(this); 
  connect(networkManager,SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(on_sslErr(QNetworkReply*,QList<QSslError>)));

}
QNetworkAccessManager* HttpClient::getQNAManager()
{
	return networkManager;
}

bool HttpClient::HandlePostRequestARGS(QByteArray& postArgs,
									 const QMap<QString,QString>& paramsToPostMap,
									 QString& ArgsAsString)
{
	// QMap is automatically sorted by keys
	// no use for this now ...
	ArgsAsString = "";
	QMapIterator<QString, QString> i(paramsToPostMap);
	WRITELOG("Args to be used");
	while (i.hasNext()) {
			 i.next();
 			 
			 WRITELOG( i.key() + "=" + i.value());
			 postArgs.append(i.key() + "=" + i.value());
			 if(i.hasNext())
			 {
				 postArgs.append("&");
			 }
	}

 	QString toPrintDebug(postArgs);
	WRITELOG( "Post Request ARGS: "+postArgs);
	return true;
}
bool HttpClient::PostRequest(QString& ApiResponse,
							QMap<QString,QString> paramsToPostMap,
							QString& BaseUrl,
							int iTimeOutInterval)
						 
 {
	 QNetworkRequest request;
	 
	 //DebugStrUrl = BaseUrl;
	 QUrl params;
	 QMapIterator<QString,QString> i(paramsToPostMap);
	 while (i.hasNext()) {
		i.next();
		params.addQueryItem(i.key(),i.value());
	 }
  	 request.setUrl(BaseUrl);
 		 
	 QByteArray postArgs;
	 postArgs = params.encodedQuery();
	  
	 /*
			This is to prevent the FB limit 600 requests in 600 seconds
			we must put some time out
 	 */
	 if(iTimeOutInterval != -1)
	 {
		 QEventLoop loop2;
		 QTimer::singleShot(iTimeOutInterval, &loop2, SLOT(quit()) );
		 loop2.exec();
     }
	 QEventLoop loop;
	 QNetworkReply *reply = networkManager->post(request,postArgs);
	 connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
     loop.exec();		
	 //return response 
	 QNetworkReply::NetworkError networkError = reply->error();
	 HandleNetworkError(networkError); 
	 
	 QByteArray data=reply->readAll();
	 ApiResponse.append(data);

	 WRITELOG("####################################################");
	 WRITELOG("response data from FB: "+ApiResponse);
	 WRITELOG("####################################################");
	 //delete reply;
	 reply->deleteLater();
	return true;
 }

bool HttpClient::GetRequest(QString& ApiResponse,
							QMap<QString,QString> paramsToPostMap,
							QString& BaseUrl,
							int iTimeOutInterval)
 {
     QUrl getUrl(BaseUrl);
	 QNetworkRequest request;
 

  	 WRITELOG("HttpClient::GetRequest: "+ BaseUrl);
 	  
	 QMapIterator<QString,QString> i(paramsToPostMap);
	 while (i.hasNext()) {
		i.next();
		getUrl.addQueryItem(i.key(),i.value());
	 }
	
	 request.setUrl(getUrl);
 
	 if(iTimeOutInterval != -1)
	 {
		 QEventLoop loop2;
		 QTimer::singleShot(iTimeOutInterval, &loop2, SLOT(quit()) );
		 loop2.exec();
     }
	 QEventLoop loop;
	 QNetworkReply *reply = networkManager->get(request);
	 connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
     loop.exec();		
	 //return response 
	 QByteArray data=reply->readAll();
	 ApiResponse.append(data);

	 WRITELOG("####################################################");
	 WRITELOG("response data from FB: "+ApiResponse);
	 WRITELOG("####################################################");
 
	 QNetworkReply::NetworkError networkError = reply->error();
	 HandleNetworkError(networkError); 
	 int iStatusCodeV =  reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	 QString reasonPhraseAttribute = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
		// Or the target URL if it was a redirect:
	 QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
	 QString strRedirectionTargetUrl = redirectionTargetUrl.toString();
	// int iStatusCodeV = statusCodeV.toInt();
	 if(iStatusCodeV == 302)
	 {
		WRITELOG("####################################################");
		WRITELOG("response redirect header data from FB: "+strRedirectionTargetUrl);
		WRITELOG("####################################################");
		ApiResponse.append(strRedirectionTargetUrl);
	 }
	 else
	 {
		QByteArray data=reply->readAll();
		ApiResponse.append(data);
		WRITELOG("####################################################");
		WRITELOG("response data from FB: "+ApiResponse);
		WRITELOG("####################################################");
	 }
	 
 
	  reply->deleteLater();
	return true;
 }
bool HttpClient::finishedNetWorkSlot(QNetworkReply* reply,
									QNetworkReply::NetworkError& networkError,
									FbAutoEnum& fbAutoEnum)
{   
     
	bool returnType = false;
	networkError = reply->error();
	reply->ignoreSslErrors();
    if (networkError == QNetworkReply::NoError)
    {
       
	    QString redUrl;
	    QString FileContentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
	    if(FileContentType.contains("html"))
	    {
		    WRITELOG( "---------------------------------------------------");
		    //WRITELOG( "Replay:"+ str);
		    WRITELOG( "Item Url:" + reply->url().toString());
		    WRITELOG( "Content Type:" +  reply->header(QNetworkRequest::ContentTypeHeader).toString());
		    //WRITELOG( "File Last Modified:" +  reply->header(QNetworkRequest::LastModifiedHeader).toString());
    		 
		    QVariant header_contentType  = reply->header(QNetworkRequest::ContentTypeHeader);
		    QString sHeader_contentType = header_contentType.toString();
		    QUrl url = reply->url();
		    QString strurl = url.toString();
		    QString scheme = url.scheme();
		    QString fileName = url.toLocalFile();

		     if(strurl.contains("login_success.html#access_token"))
		     {
				// the login was succesful now we going to start the application   
			    QStringList list1 = strurl.split("#access_token=");
			    QStringList list2  = list1[1].split("&");
				QString access_token;
				access_token = list2[0];
				if(FBApi::getInstance()->AuthorizAndAuthenticatUser(access_token))
				{
					WRITELOG("finishedNetWorkSlot:AuthorizAndAuthenticatUser use are succsesfuly authorize");
					IsUserAutorized = true;
					returnType = true;
				}
				else
				{
					WRITELOG("finishedNetWorkSlot:AuthorizAndAuthenticatUser use are NOT authorize");
					returnType = false;
				}
			 //some problem with the FB application 
		    } 
			else if (strurl.contains("authorize_success?") && strurl.contains("&session={"))
			{
				QStringList list1 = strurl.split("&session=");
			    QString json  = list1[1];
				
				QMap<QString,QString> JsonSessionMap;
				//needed to init the map for the first api call to FB 
				JsonSessionMap["session_key"];
				JsonSessionMap["uid"];
				JsonSessionMap["expires"];
				JsonSessionMap["secret"];
				JsonSessionMap["sig"];
				
				FBApi::getInstance()->ParseJsonFromHTTP(json,JsonSessionMap);
				//Check to see if the user are the same and vaild by checking the Auto api uid value 
				FBApi::getInstance()->SetApiKeys(JsonSessionMap["secret"],
												 JsonSessionMap["session_key"],
												 JsonSessionMap["uid"],
												 JsonSessionMap["sig"]);


			}
			//else if(strurl.contains("client_id="+FBApi::getInstance()->GetAPPLICATION_ID()+"&"))
			//{
			//	// this is bug fix , in case there is (probably cookie ) from browser previews browser login
			//	WRITELOG("there is (probably cookie ) from browser previews browser login");
			//	return true;

			//}
		    else if(strurl.contains("login_failure.html"))
			{   
			    QRegExp rx;
                rx.setMinimal(true);
	            rx.setPattern("login_failure.html$");
	            if(rx.indexIn(strurl)>0)
	            {
	                WRITELOG("finishedNetWorkSlot: login_failure!!");
	            }
				
			}
            else if(strurl.contains("http://www.facebook.com/connect/login_success.html?error_reason=user_denied") && !strurl.contains("https://www.facebook.com"))
			{   
			     
	                    WRITELOG("finishedNetWorkSlot: error_reason user_denied!!");
	                    fbAutoEnum = FbAutoEnum::NETWORK_FAIL_USER_OPERATION_CANCELED;
	                    returnType = false;
	  		}

		} else if(FileContentType.contains("xml")){
			
			WRITELOG( "----------------------xml response ------------------------");
		   // WRITELOG( "Replay:"+ str);
		    WRITELOG( "Item Url:" + reply->url().toString());
		    WRITELOG( "Content Type:" +  reply->header(QNetworkRequest::ContentTypeHeader).toString());
		    WRITELOG( "File Last Modified:" +  reply->header(QNetworkRequest::LastModifiedHeader).toString());
    		 
		}
		
		// reply->deleteLater();
		 
    }
	else
	{
		 HandleNetworkError(networkError);
	}
    

	
    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    //delete reply;
	reply->deleteLater();
	return returnType;
}

void HttpClient::on_sslErr(QNetworkReply* reply,QList<QSslError> sslErrorList)
{
	for (int i = 0; i < sslErrorList.size(); ++i) {

		WRITELOG("sslErrorList:"+sslErrorList.at(i).errorString());
          
	}
	//some times there are ssl error , ignor them (bug in facebook ??? ) 
	reply->ignoreSslErrors(sslErrorList);
}



