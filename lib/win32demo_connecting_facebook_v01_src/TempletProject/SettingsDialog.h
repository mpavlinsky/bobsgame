 
#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "ui_settings.h"
 

//! [0]
class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    SettingsDialog(QWidget *parent=0);
	QString GetPath()
	{
		return m_path;
	}

private slots:
    void changeDirectory();
	void PreAccept();
	void PreReject();
	void LinkClickHandler(const QString & link);

     

private:
	void setPreDefinedConfig();
	Ui::Dialog ui;
	QString m_path;
	QDir directory;
};
//! [0]

#endif
