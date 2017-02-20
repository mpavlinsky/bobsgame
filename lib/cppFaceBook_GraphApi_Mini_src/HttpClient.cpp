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
			UT::getInstance()->LogToFile("NO NETWORK CONNECTION ConnectionRefusedError!! ");
			break;
		case(QNetworkReply::HostNotFoundError):
			//handle the html output is no internet connection is found
			UT::getInstance()->LogToFile("NO NETWORK CONNECTION HostNotFoundError!! ");
			break;
		}
		
}
HttpClient::HttpClient()
{
 
  networkManager = new QNetworkAccessManager(this); 
  
   
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
	UT::getInstance()->LogToFile("Args to be used");
	while (i.hasNext()) {
			 i.next();
 			 
			 UT::getInstance()->LogToFile( i.key() + "=" + i.value());
			 postArgs.append(i.key() + "=" + i.value());
			 if(i.hasNext())
			 {
				 postArgs.append("&");
			 }
	}

 	QString toPrintDebug(postArgs);
	UT::getInstance()->LogToFile( "Post Request ARGS: "+postArgs);
	return true;
}
bool HttpClient::PostRequest(QString& ApiResponse,QMap<QString,QString> paramsToPostMap,QString& BaseUrl)
 {
	 QNetworkRequest request;
	 DebugStrUrl = BaseUrl;
 	 request.setUrl(QUrl(BaseUrl));
 		 
	 QByteArray postArgs;
	 QString  ArgsAsString;
	 HandlePostRequestARGS(postArgs,paramsToPostMap,ArgsAsString);
	 QString DebugStrArgs(postArgs);
	
	 QEventLoop loop;
	 QNetworkReply *reply = networkManager->post(request,postArgs);
	 connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
     loop.exec();		
	 //return response 
	 QByteArray data=reply->readAll();
	 ApiResponse.append(data);

	 UT::getInstance()->LogToFile("####################################################");
	 UT::getInstance()->LogToFile("response data from FB: "+ApiResponse);
	 UT::getInstance()->LogToFile("####################################################");
	 delete reply;
	return true;
 }

bool HttpClient::GetRequest(QString& ApiResponse,
							QMap<QString,QString> paramsToPostMap,
							QString& BaseUrl)
 {
     QNetworkRequest request;
	 QString tmpUrlEncod;
	 QString apiUrl = "";
	 request.setRawHeader("Accept-Charset", "win1251,ISO-8859-1,utf-8;q=0.7,*;q=0.7");
     request.setRawHeader("charset","utf-8");
  	 UT::getInstance()->LogToFile("HttpClient::GetRequest: "+ BaseUrl);
	 QByteArray postArgs;
	 QString  ArgsAsString;
	 HandlePostRequestARGS(postArgs,paramsToPostMap,ArgsAsString);
	 QString DebugStrArgs(postArgs);
	 if(DebugStrArgs.length() > 2)
	 {
		apiUrl = BaseUrl+DebugStrArgs;
	 }
	 else
	 {
		 
 		 request.setRawHeader("Accept-Charset","ISO-8859-1,utf-8;q=0.7,*;q=0.7");
		 request.setRawHeader("Keep-Alive","115");
		 request.setRawHeader("Connection","keep-alive");
		 request.setUrl(QUrl(BaseUrl));
		 UT::getInstance()->LogToFile("API url to invoke: "+BaseUrl);
		 /*
			This is to prevent the FB limit 600 requests in 600 seconds
			we must put some time out
 		 */
		 QEventLoop loop2;
         QTimer::singleShot(3000, &loop2, SLOT(quit()) );
         loop2.exec();

 		 QEventLoop loop;
 		 QNetworkReply *reply = networkManager->get(request);
  		 connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		 loop.exec();
		 QByteArray data=reply->readAll();
		 ApiResponse.append(data);
		 UT::getInstance()->LogToFile("####################################################");
		 UT::getInstance()->LogToFile("response data from FB: "+ApiResponse);
		 UT::getInstance()->LogToFile("####################################################");
	 
		 delete reply;
		return true;
	 }
	 
	  
	 request.setUrl(apiUrl);
	 UT::getInstance()->LogToFile("API url to invoke: "+apiUrl);
 	 QEventLoop loop;
 	 QNetworkReply *reply = networkManager->get(request);
  	 connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
     loop.exec();
	 QByteArray data=reply->readAll();
	 ApiResponse.append(data);
	 UT::getInstance()->LogToFile("####################################################");
	 UT::getInstance()->LogToFile("response data from FB: "+ApiResponse);
	 UT::getInstance()->LogToFile("####################################################");
 
	 delete reply;
	return true;
 }
bool HttpClient::finishedNetWorkSlot(QNetworkReply* reply,
									QNetworkReply::NetworkError& networkError)
{   
     
	networkError = reply->error();
    if (networkError == QNetworkReply::NoError)
    {
       
	    QString redUrl;
	    QString FileContentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
	    if(FileContentType.contains("html"))
	    {
		    UT::getInstance()->LogToFile( "---------------------------------------------------");
		    //UT::getInstance()->LogToFile( "Replay:"+ str);
		    UT::getInstance()->LogToFile( "Item Url:" + reply->url().toString());
		    UT::getInstance()->LogToFile( "Content Type:" +  reply->header(QNetworkRequest::ContentTypeHeader).toString());
		    //UT::getInstance()->LogToFile( "File Last Modified:" +  reply->header(QNetworkRequest::LastModifiedHeader).toString());
    		 
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
					UT::getInstance()->LogToFile("finishedNetWorkSlot:AuthorizAndAuthenticatUser use are succsesfuly authorize");
					IsUserAutorized = true;
					return true;
				}
				else
				{
					UT::getInstance()->LogToFile("finishedNetWorkSlot:AuthorizAndAuthenticatUser use are NOT authorize");
					return false;
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
		    else if(strurl.contains("login_failure.html"))
			{   
			    QRegExp rx;
                rx.setMinimal(true);
	            rx.setPattern("login_failure.html$");
	            if(rx.indexIn(strurl)>0)
	            {
	                UT::getInstance()->LogToFile("finishedNetWorkSlot: login_failure!!");
	            }
				
			}


		} else if(FileContentType.contains("xml")){
			
			UT::getInstance()->LogToFile( "----------------------xml response ------------------------");
		   // UT::getInstance()->LogToFile( "Replay:"+ str);
		    UT::getInstance()->LogToFile( "Item Url:" + reply->url().toString());
		    UT::getInstance()->LogToFile( "Content Type:" +  reply->header(QNetworkRequest::ContentTypeHeader).toString());
		    UT::getInstance()->LogToFile( "File Last Modified:" +  reply->header(QNetworkRequest::LastModifiedHeader).toString());
    		 
		}
		// reply->deleteLater();
		return false;
    }
    

	
    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    //delete reply;
	// reply->deleteLater();
	return false;
}





