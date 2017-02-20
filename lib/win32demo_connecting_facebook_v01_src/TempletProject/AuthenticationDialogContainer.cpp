//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################
#include <QtGui>
#include "AuthenticationDialogContainer.h"
#include "UT.h"
#include "HttpClient.h"
#include "json.h"
#include "Constants.h"
 
#include "FBFqlBuilder.h"
#include "SettingsDialog.h"
 
 


 
AuthenticationDialogContainer::AuthenticationDialogContainer(QWidget* parent) : 
										QDialog(parent),
										m_progress(0) 
									 
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
	ui.setupUi(this);
	
	SetMenuBar();
	SetStatusBar();
 	pWebBroswerAuthenticate = new WebBroswerDeleget(ui.webView);
	createWebViewActions();
 	pWebBroswerAuthenticate->load(FBApi::getInstance()->GetAutonticationURL());
	pWebBroswerAuthenticate->show();
	CreateMainSysTray();
	
	//TestAPIs();
  
}


AuthenticationDialogContainer::~AuthenticationDialogContainer()
{
	delete pWebBroswerAuthenticate;
	/*if(m_trayIcon->isSystemTrayAvailable())
	{
		if(m_trayIcon->isVisible())
		{
			m_trayIcon->hide();
			delete m_trayIcon;
		}
	}*/

}

void AuthenticationDialogContainer::closeEvent(QCloseEvent *event)
 {
    delete pWebBroswerAuthenticate;
	/*if(m_trayIcon->isSystemTrayAvailable())
	{
		if(m_trayIcon->isVisible())
		{
			m_trayIcon->hide();
			delete m_trayIcon;
		}
	}*/
	event->accept();
}


void AuthenticationDialogContainer::createMenuActions()
{
	connect(m_actionPreferences, SIGNAL(triggered()),this, SLOT(popupSettingsWindow()));
	connect(m_actionClose, SIGNAL(triggered()),this, SLOT(close()));

}

void AuthenticationDialogContainer::popupSettingsWindow()
{
		 SettingsDialog settingsDialog;
		 if (settingsDialog.exec())
		 {
			 ; // do something with the data from settings dialog
		 }
}



void AuthenticationDialogContainer::SetStatusBar()
{
	bar = new QStatusBar(this);
	bar->setMinimumSize(QSize(0, 20));
	ui.widget->setParent(NULL);
	delete ui.widget;
 	ui.verticalLayout->addWidget(bar);
	ui.verticalLayout->setMargin(0);
    ui.verticalLayout->setSpacing(0);
 
	pb = new QProgressBar(bar);
	pb->setTextVisible(false);
	pb->hide();
	
	bar->addPermanentWidget(pb);
}


void AuthenticationDialogContainer::SetMenuBar()
{
    ui.widget_2->setParent(NULL);
	delete ui.widget_2;
	m_actionClose = new QAction("&Close", this);
	m_actionPreferences = new QAction("&About",this);
	m_menubar = new QMenuBar(this);
	m_menuFile = m_menubar->addMenu("&File");
	m_menuFile->addAction(m_actionClose);
	m_menuSettings = m_menubar->addMenu("&Help");
	m_menuSettings->addAction(m_actionPreferences);
	ui.verticalLayout_menuBarLayOut->setMenuBar(m_menubar);
	createMenuActions();
}


void AuthenticationDialogContainer::TestAPIs()
{


}
QStatusBar* AuthenticationDialogContainer::statusBar()
{
	return bar;
}

 

 
void AuthenticationDialogContainer::CreateMainSysTray()
{
 	 
	/*m_trayIcon = new TrayIcon(this);
	 
    TrayIcon::getInstance()->GetSysTrayIcon();*/
	 
	setWindowTitle(tr(DESKTOP_FB_CAPTION));
	 
}
 
void AuthenticationDialogContainer::createWebViewActions()
{
    connect(pWebBroswerAuthenticate->GetWebBrowser(), SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(pWebBroswerAuthenticate->GetWebBrowser(), SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
    connect(pWebBroswerAuthenticate->GetWebBrowser(), SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(pWebBroswerAuthenticate->GetWebBrowser(), SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
 	connect(pWebBroswerAuthenticate,SIGNAL(GetFBAuthenticat(bool,FbAutoEnum)),SLOT(GetFbAutoAuthenticatStatus(bool,FbAutoEnum)));
 	
	pWebBroswerAuthenticate->GetWebBrowser()->setContextMenuPolicy(Qt::NoContextMenu);
}

 

 
void AuthenticationDialogContainer::GetFbAutoAuthenticatStatus(bool b,FbAutoEnum fbAutoEnum)
{

	if(b)
	{
		WRITELOG("AutoAuthenticatStatus:Success!!");
		 
		WRITELOG("AutoAuthenticatStatus:Success!!");
		WRITELOG(FBApi::getInstance()->GetUserAccessToken());
		WRITELOG("Start setWriteToStdOut().");
        QTextStream qout(stdout); 
        qout <<  FBApi::getInstance()->GetUserAccessToken();
        WRITELOG("Done setWriteToStdOut().");
		done(Accepted);



	}
	else
	{
		WRITELOG("AutoAuthenticatStatus:Fail!!");
		//MEIR add here error printing based on FbAutoEnum
		//done(Rejected);
	}
	
 
}

void AuthenticationDialogContainer::setProgress(int p)
{
    m_progress = p;
    adjustTitle();
}

void AuthenticationDialogContainer::adjustTitle()
{
	 
	 
	pb->show();
	if (m_progress <= 0 || m_progress >= 100)
	{
		QString titl =  pWebBroswerAuthenticate->GetWebBrowser()->title();
		bar->showMessage(titl);
		//statusBar()->showMessage(titl);
        setprogressBar(-1,false);
		 
	}
    else
	{
 	    bar->showMessage(QString("%1 (%2%)").arg(ui.webView->title()).arg(m_progress));
		//statusBar()->showMessage(QString("%1 (%2%)").arg(ui.webView->title()).arg(m_progress));
		setprogressBar(m_progress,true);
	}
}


void AuthenticationDialogContainer::adjustLocation()
{
    
   locationEdit =  ui.webView->url().toString() ;
   QString email(USER_EMAIL);
   QString pass(USER_PASSWORD);
	 
 }

void AuthenticationDialogContainer::finishLoading(bool)
{	
	m_progress = 100;
    adjustTitle();
 }
 
void AuthenticationDialogContainer::changeLocation()
{
    
	QUrl url = QUrl(locationEdit);
	pWebBroswerAuthenticate->GetWebBrowser()->setFocus();
}
 

void AuthenticationDialogContainer::setprogressBar(int progress,bool show)
{
    if(show)
    {
        pb->show();
        pb->setRange(0,100);
        pb->setValue(progress);
    }
    else
    {
        pb->hide();
    } 
}





