#ifndef WEBBROSWERDELEGET_H
#define WEBBROSWERDELEGET_H
#include <QtGui>
#include <QtWebKit>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "QCookieJar.h"
#include "Constants.h"


class WebBroswerDeleget : public QObject
{
    Q_OBJECT
 
    public :
		WebBroswerDeleget(QWebView *&webView);
		~WebBroswerDeleget();
		QWebView* GetWebBrowser(){return m_webView;}
		void load(QUrl weburl);
		void show();

    signals:
	    void GetFBAuthenticat(bool b,FbAutoEnum fbAutoEnum);

	public slots:
		void finishedSlot(QNetworkReply* reply);
		void on_sslErr(QNetworkReply* reply,QList<QSslError> sslErrorList);
	
	

	private:
		QWebView *m_webView;
		QNetworkRequest m_request;
		QNetworkAccessManager *m_manager; 
		void SetNetmanager(const QString& weburl);
		QCookieJar* m_cookieJar;
		QString m_Cookiedirectory; 

};
#endif