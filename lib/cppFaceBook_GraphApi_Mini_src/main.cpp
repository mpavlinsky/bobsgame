//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#include <QApplication>

 #include "MainWindowContainer.h"

 int main(int argc, char *argv[])
 {
      
     QApplication app(argc, argv);
	 app.setStyle("WindowsXP");    
	 QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	 QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
     MainWindowContainer mainWindowContainer;
     mainWindowContainer.show();
	 

     return app.exec();
 }