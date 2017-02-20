#include "WebBroswerDeleget.h"
#include "HttpClient.h"
#include "UT.h"
#include <QApplication>



WebBroswerDeleget::WebBroswerDeleget(QWebView *&webView)
{
	m_webView = webView;
	m_manager = new QNetworkAccessManager(this);
	
	 
	connect(m_manager,SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), 
						     this,
							 SLOT(on_sslErr(QNetworkReply*,QList<QSslError>)));
	
}

WebBroswerDeleget::~WebBroswerDeleget()
{
    if(USECOOKIE)
	{
		delete m_cookieJar;
	}
}

void WebBroswerDeleget::SetNetmanager(const QString& weburl)
{
 	 m_webView->page()->setNetworkAccessManager(m_manager);
	 if(USECOOKIE)
	 {
		m_Cookiedirectory  = QCoreApplication::applicationDirPath() + QLatin1String("/")+COOKIE_NAME;
		qWarning() << m_Cookiedirectory;
		m_cookieJar = new QCookieJar(m_Cookiedirectory);
 		m_webView->page()->networkAccessManager()->setCookieJar(m_cookieJar);
	 }
	 //m_manager->setCookieJar(m_cookieJar);
	 m_request = QNetworkRequest();
	 m_request.setUrl(QUrl(weburl));
	 connect(m_manager, SIGNAL(finished(QNetworkReply*)),this,
	                 SLOT(finishedSlot(QNetworkReply*)));
	 m_manager->get(m_request);
}



void WebBroswerDeleget::finishedSlot(QNetworkReply* reply)
{   
	
	QNetworkReply::NetworkError networkError = QNetworkReply::NoError;
	FbAutoEnum fbAutoEnum = FbAutoEnum::DUMMY;
	if(!HttpClient::getInstance()->finishedNetWorkSlot(reply,networkError,fbAutoEnum))
	{
		 
		switch(networkError)
		{
		case(QNetworkReply::ConnectionRefusedError):
			m_webView->setHtml(NETWORK_CONNECTION_REFUSED_ERROR);
			emit GetFBAuthenticat(false,FbAutoEnum::NETWORK_FAIL_CONNECTION_REFUSED);
			break;
		case(QNetworkReply::HostNotFoundError):
			//handle the html output is no internet connection is found
			m_webView->setHtml(NETWORK_CONNECTION_HOSTNOTFOUND_ERROR);
			emit GetFBAuthenticat(false,FbAutoEnum::NETWORK_FAIL_HOST_NOT_FOUND);
			break;
		case(QNetworkReply::OperationCanceledError):
			//handle the html output is no internet connection is found
			m_webView->setHtml(NETWORK_OPERATION_CANCELED_ERROR);
			emit GetFBAuthenticat(false,FbAutoEnum::NETWORK_FAIL_OPERATION_CANCELED);
			break;
		}
		// now handle iternal error's 
		if(fbAutoEnum == FbAutoEnum::NETWORK_FAIL_USER_OPERATION_CANCELED)
		{
		     // in case user pressed cancle 
		     m_webView->setHtml(NETWORK_OPERATION_USER_CANCELED_ERROR);
		     emit GetFBAuthenticat(false,FbAutoEnum::NETWORK_FAIL_USER_OPERATION_CANCELED);
		}
		 
		
	} 
	else 
	{
		if(HttpClient::getInstance()->IsUserAutorized)
		{
			HttpClient::getInstance()->IsUserAutorized = false;
			emit GetFBAuthenticat(true,FbAutoEnum::SUCCESS);
			 
		}
		else
		{
			WRITELOG("MainWindowContainer::finishedSlot:handle the case we need to obtain the access key for example : when we allready autonticated via browser");
			emit GetFBAuthenticat(false,FbAutoEnum::ALLREADY_AUTO);
		}
	}
}

//delegetores
void WebBroswerDeleget::load(QUrl weburl)
{
	SetNetmanager(weburl.toString());
	m_webView->load(weburl);
}
void WebBroswerDeleget::show()
{
	m_webView->show();
}

void WebBroswerDeleget::on_sslErr(QNetworkReply* reply,QList<QSslError> sslErrorList)
{
	for (int i = 0; i < sslErrorList.size(); ++i) {

		WRITELOG("sslErrorList:"+sslErrorList.at(i).errorString());
          
	}
	//some times there are ssl error , ignor them (bug in facebook ??? ) 
	reply->ignoreSslErrors(sslErrorList);
}
