#include "ConfigSettings.h"
#include "Constants.h"
#include "UT.h"

ConfigSettings* ConfigSettings::_instance = NULL ;
 
ConfigSettings* ConfigSettings::getInstance()
{
    if(ConfigSettings::_instance == NULL)
    {
        ConfigSettings::_instance = new ConfigSettings();
    }
    return _instance;
}

ConfigSettings::ConfigSettings()
{
	 
	bool bExists = true;
	QFile file(QDir::currentPath()+"/"+CONFIG_FILE_NAME);
	if( !file.exists() )
	{
		WRITELOG("The file" + file.fileName() + "does not exist.");
		bExists = false;
		 
	}
	
	m_pSettings = new QSettings(QDir::currentPath()+"/"+CONFIG_FILE_NAME,QSettings::IniFormat);
	if(!bExists)
	{
		//set init params
		WriteToSettingsValueAsVariant(SETTINGS_KEY_NOTIFICATIONTHREAD,SETTINGS_DEFAULT_NOTIFICATIONTHREAD_VALUE);

	}
	WRITELOG("QDir::currentPath():"+QDir::currentPath()+"/"+CONFIG_FILE_NAME);
	
	 
}

QString ConfigSettings::ReadFromSettings(QString key)
{
	
	QVariant variantVal = ReadFromSettingsReturnVariant(key);
	QString val = variantVal.toString();

 	//TODO need to check if i realy need the sync here 
	m_pSettings->sync();
	return val;
}

QVariant ConfigSettings::ReadFromSettingsReturnVariant(QString key)
{
	QVariant variantVal;
	variantVal  = ConfigSettings::m_pSettings->value(key); 
	//TODO need to check if i realy need the sync here 
	m_pSettings->sync();
	return variantVal;
}

void ConfigSettings::WriteToSettings(QString key,QString value)
{
	 m_pSettings->setValue(key,value);
	 m_pSettings->sync();
}

void ConfigSettings::WriteToSettingsValueAsVariant(QString key,const QVariant& value)
{
	 m_pSettings->setValue(key,value);
	 m_pSettings->sync();
}


ConfigSettings::~ConfigSettings()
{
	;
}

