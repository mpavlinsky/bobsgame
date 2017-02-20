#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QtGui>


#define FB_LOGO_PATH ":/resources/f_logo.jpg"
#define DESKTOP_FB_CAPTION "TempletProject"
#define GMAIL_LOGO_PATH ":/resources/Gmail_logo.png"
#define APP_NAME "TempletProject"
#define COMPANY_NAME "Void"
#define APP_VERISON "0.1"
#define APP_DOMAIN "TempletProject.com"
#define CONFIG_FILE_NAME "TempletProject.ini"
#define COOKIEJAR_FILE_NAME "TempletProjectCookies.dat"
#define API_REQUEST_TIMEOUT_INTERVAL  3000
#define API_GET_GROUP_REQUEST_TIMEOUT_INTERVAL  3000


#define MAIN_USER	"mainuser"
#define SETTINGS_KEY_NOTIFICATIONTHREAD "NotificationThread"
#define SETTINGS_DEFAULT_NOTIFICATIONTHREAD_VALUE 30000
#define API_REQUEST_TIMEOUT_INTERVAL_DLD_WORKER  5000
#define APP_DB_FILE_NAME "DesktopFB.db"
#define NETWORK_CONNECTION_REFUSED_ERROR       "<html><body><center> \
												NO NETWORK CONNECTION !! <br> Connection Refused Error \
												</center></body></html>"

#define NETWORK_CONNECTION_HOSTNOTFOUND_ERROR    "<html><body><center> \
											     NO NETWORK CONNECTION !! <br> Host Not Found Error </center> \
												</body></html>"
												
#define NETWORK_OPERATION_CANCELED_ERROR    "<html><body><center> \
											   NETWORK  OPERATION CANCELED !! <br>  Operation Canceled Error </center> \
												</body></html>"												

#define NETWORK_OPERATION_USER_CANCELED_ERROR    "<html><body><center> \
											   NETWORK  OPERATION CANCELED BY USER!! <br>  Operation Canceled Error </center> \
												</body></html>"												
												
  

//fill here the data !!!
#define API_KEY_CONST		   "...."
#define APPLICATION_ID_CONST   "...."
#define APP_SECRET_CONST		"...."
 
#define GENERAL_API_URL_CONST		 "https://graph.facebook.com"
#define FQL_QUERY_API_URL_CONST      "https://api.facebook.com/method/fql.query";
#define FQL_MULTIQUERY_API_URL_CONST "https://api.facebook.com/method/fql.multiquery";

//fill here user name and password !!!
#define USER_EMAIL     ""
#define USER_PASSWORD  ""

#define COOKIE_NAME		"TempletProjectcookeijar.dat"
#define USECOOKIE       false

enum FbAutoEnum{
	SUCCESS,
	NETWORK_FAIL,
	NETWORK_FAIL_CONNECTION_REFUSED,
	NETWORK_FAIL_HOST_NOT_FOUND,
	NETWORK_FAIL_OPERATION_CANCELED,
	NETWORK_FAIL_USER_OPERATION_CANCELED,
	ALLREADY_AUTO,
	DUMMY
};

enum GROUP_TREE_TYPES {
		 GROUPS_ROOT,
		 GROUP_NAME

};


struct StringPer {

	QString key;
	QString val;
	StringPer(){};
	StringPer(QString k,QString v)
	{
		key = k;
		val = v;
	}
};

//========================
#define IO_ReadOnly QIODevice::ReadOnly
#define IO_WriteOnly QIODevice::WriteOnly
#define IO_ReadWrite QIODevice::ReadWrite
#define IO_Append QIODevice::Append
#define IO_Truncate QIODevice::Truncate
#define IO_Translate QIODevice::Text
#define IO_ModeMask 0x00ff
//========================


#endif