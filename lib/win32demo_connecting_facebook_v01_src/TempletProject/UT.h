//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

#ifndef __UT_H_
#define __UT_H_
#include <QtGui>

#include <QtNetwork/QNetworkAccessManager>
#include <QtScript/QScriptValueIterator>

#define DEBUG_MODE 1
# define LOGGER(str) UT::getInstance()->LogToFile(str);
#if DEBUG_MODE
    #define WRITELOG( str ) LOGGER(str) 
#else
    #define WRITELOG( str ) // will replace the myDebug calls by nothing.
#endif



//========================
#define IO_ReadOnly QIODevice::ReadOnly
#define IO_WriteOnly QIODevice::WriteOnly
#define IO_ReadWrite QIODevice::ReadWrite
#define IO_Append QIODevice::Append
#define IO_Truncate QIODevice::Truncate
#define IO_Translate QIODevice::Text
#define IO_ModeMask 0x00ff
//========================
class UT 
{
    public:
        static UT* getInstance();
        virtual ~UT(){} 
        void LogToFile(QString data);
		QNetworkAccessManager* getQNAManager();
		bool GetMD5String(const QString& toAPISignature,QString& APIMD5Signature);
		QString GetCurrentTime();
		QString GetCurrentDate();
		QString GetCurrentDateTime();
		QString GetCurrentDateTimeAsSecounds();
		QString GetCurrentDateTimeAsMiliSecounds();
		QString GetFromDateTimeAsSecounds(const QDate& date,const QTime& time);
		void ConvertTimeStampToDateTime(const QString& timeStamp,QString& dateTime);
		void WriteToSettings(QString key,QString value);
		QString ReadFromSettings(QString key);
		 
	    
		void StrReplace(std::string& str, const std::string& old, const std::string& newstr);
	    
	    QSettings* GetAppSettings()
		{
			return m_pSettings;
		}
		 
		QPoint& MoveMainWindowToCenter(int height,int width);
		
        
    private:
        static UT* _instance;
		UT();
        static QFile m_Debugfile;
		QSettings* m_pSettings;
		

		
    
};
#endif