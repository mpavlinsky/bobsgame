//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################
#ifndef __AUTHENTICATIONDIALOGCONTAINER_H_
#define __AUTHENTICATIONDIALOGCONTAINER_H_
#include "Constants.h"
#include "ui_authenticationdialog.h"
#include <QtGui>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QProgressBar>
#include "FBApi.h"
#include "WebBroswerDeleget.h"
 
  

class AuthenticationDialogContainer : public QDialog
{
	Q_OBJECT
	 

public:
	AuthenticationDialogContainer(QWidget *parent=0);
	virtual ~AuthenticationDialogContainer();
	
	Ui::AutoDialog ui;

public slots:
 	void adjustLocation();
    void changeLocation();
    void adjustTitle();
    void setProgress(int p);
    void finishLoading(bool);
	void GetFbAutoAuthenticatStatus(bool b,FbAutoEnum fbAutoEnum);
	void closeEvent(QCloseEvent *event);
	void popupSettingsWindow();
 	 
 
private:
	QStatusBar *bar;	 
	int m_progress;
   	QString  locationEdit;
  	
  	
  	QAction *m_actionClose;
    QAction *m_actionPreferences;
    QMenuBar *m_menubar;
    QMenu *m_menuFile;
    QMenu *m_menuSettings;
     
    void createWebViewActions();
	void createActions();
	void CreateMainSysTray();
	void SetMenuBar();
	void SetStatusBar();
	void createMenuActions();
     	 
	void TestAPIs();
   	bool m_bWebAuthenticationPassed;
 	QProgressBar *pb;
	 
	void setprogressBar(int progress,bool show);
	QStatusBar* statusBar();
	WebBroswerDeleget *pWebBroswerAuthenticate;
	

};


#endif