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
        ~UT(){} 
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
		void SetResultMapWithSets(QList<QMap<QString,QString > >& fql_result_set,
											QScriptValueIterator& resultSetIter);
											
	    int GetAppConfigUniqueId();
        void IncreaseByOneUniqueId();
        int CreateAppConfigUniqueId();
	    
	    struct AppConfig 
	    {
	        int unique_id;
	        
	    } AppConfig;

		
        
    private:
        static UT* _instance;
		UT();
        static QFile m_Debugfile;
		

		
    
};
#endif