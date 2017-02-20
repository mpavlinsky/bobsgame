//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################
#ifndef __MAINWINDOWCONTAINER_H_
#define __MAINWINDOWCONTAINER_H_


#include "ui_fbapi_gui.h"
#include <QtGui>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "FBApi.h"
 
 


//========================
#define IO_ReadOnly QIODevice::ReadOnly
#define IO_WriteOnly QIODevice::WriteOnly
#define IO_ReadWrite QIODevice::ReadWrite
#define IO_Append QIODevice::Append
#define IO_Truncate QIODevice::Truncate
#define IO_Translate QIODevice::Text
#define IO_ModeMask 0x00ff
//========================



class MainWindowContainer : public QMainWindow 
{
    Q_OBJECT

public:
    MainWindowContainer(QWidget *parent = 0);
     void setSourceModel(QAbstractItemModel *model);
  	
 	QString GetApiRequest(bool firstTimeCall,QString prevLink);	
	QString GetGroupWallFeeds(QString strWallFeeds);

public slots:
	void adjustLocation();
    void changeLocation();
    void adjustTitle();
    void setProgress(int p);
    void finishLoading(bool);
	void finishedSlot(QNetworkReply* reply);
	void linkClicked(const QUrl& url);
  	void CloseApp();
  

private:
 	Ui::MainWindow ui;	 
	int progress;
	QNetworkRequest m_request;
	QNetworkAccessManager *m_manager; 
	QMap<QString,QString> JsonSessionMap;
	QString  locationEdit;
    QStackedWidget *stackedWidget;      
    void createWebViewActions();
	void createActions();
 	void SetNetmanager(const QString& weburl);
	void ParseJsonFromHTTP(const QString &http_response);
 
	void createMenuActions();
	void WriteToDummyFile(QString printData);
	void TestAPIs();


	QStandardItem* m_standardItemSelectedFromSysWin;
	QBrush m_brush;
	QBrush m_BrowsePrev;
	int m_MarkedRowPrev;
	int m_limit;
	int	m_offset;
	QFile* m_DummyFile;
 };



#endif