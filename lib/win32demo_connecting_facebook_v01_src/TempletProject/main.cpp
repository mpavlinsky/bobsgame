//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#include <QApplication>
#include "AuthenticationDialogContainer.h"
#include "Constants.h" 
#include "UT.h"


 int main(int argc, char *argv[])
 {
     Q_INIT_RESOURCE(resources); 
     QApplication app(argc, argv);
	 QCoreApplication::setApplicationName(APP_NAME);
	 QCoreApplication::setApplicationVersion(APP_VERISON);
	 QCoreApplication::setOrganizationDomain(APP_DOMAIN);
	 app.setStyle("WindowsXP");    
	 QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	 QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
   
     AuthenticationDialogContainer *pAuthenticationDialogContainer = new AuthenticationDialogContainer();
 	 if(pAuthenticationDialogContainer->exec() != QDialog::Accepted ) {
		 //app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
		 QTimer::singleShot(0, &app, SLOT(quit()));
	 }
	  QTimer::singleShot(0, &app, SLOT(quit()));
	 
	 //MainWindowContainer mainWindowContainer;	
   
	 ////check the login Info
	 //delete pAuthenticationDialogContainer;
     //WRITELOG(FBApi::getInstance()->GetUserAccessToken());
     //mainWindowContainer.show();
	 //app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
     int returnCode = app.exec();
     return returnCode;
 }