//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#ifndef __HTTPCLIENT_H_
#define __HTTPCLIENT_H_
#include <QtGui>
#include <QtNetwork>
#include "Constants.h"
 
class HttpClient: public QObject

{
   Q_OBJECT
    
private: 
  static HttpClient* _instance;
  HttpClient();
  
  HttpClient(const HttpClient &);
  HttpClient & operator=(const HttpClient &);
  bool HandlePostRequestARGS(QByteArray& postArgs,
							const QMap<QString,QString>& paramsToPostMap,
							QString& ArgsAsString);
  

 
  
  int httpGetId;
  bool httpRequestAborted;
  QNetworkAccessManager* networkManager;
  
  
protected slots:
  void on_sslErr(QNetworkReply* reply,QList<QSslError> sslErrorList); 

public:
  static HttpClient* getInstance();
  ~HttpClient(){};
  bool GetRequest(QString& ApiResponse,
				  QMap<QString,QString> paramsToPostMap,
				  QString& BaseUrl,
				  int iTimeOutInterval);

  bool PostRequest( QString& ApiResponse,
					QMap<QString,QString> paramsToPostMap,
					QString& BaseUrl,
					int iTimeOutInterval);

  bool finishedNetWorkSlot(QNetworkReply* reply,
	  QNetworkReply::NetworkError& networkError,
	  FbAutoEnum& fbAutoEnum);
  QNetworkAccessManager* getQNAManager();
  void HandleNetworkError(QNetworkReply::NetworkError& networkError);
  static bool IsUserAutorized;
   
};

#endif