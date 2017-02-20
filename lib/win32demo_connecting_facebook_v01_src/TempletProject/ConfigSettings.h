#ifndef _CONFIGSETTINGS_H_
#define _CONFIGSETTINGS_H_
#include <QtGui>


class ConfigSettings
{
	public:
		 static ConfigSettings* getInstance();
        ~ConfigSettings();
		void WriteToSettings(QString key,QString value);
		void WriteToSettingsValueAsVariant(QString key,const QVariant& value);

		QString ReadFromSettings(QString key);
		QVariant ReadFromSettingsReturnVariant(QString key);

	private:
		ConfigSettings();
		

		static ConfigSettings* _instance;
 		QSettings* m_pSettings;
};

#endif