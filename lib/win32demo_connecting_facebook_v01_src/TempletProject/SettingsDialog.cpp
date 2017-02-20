 
#include <QtGui>
#include "SettingsDialog.h"
#include "UT.h"
#include "Constants.h"
#include "ConfigSettings.h"

//! [0]
SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
	
	ui.setupUi(this);
	 setWindowFlags(Qt::WindowStaysOnTopHint);
	connect(ui.pushButtonabout_ok, SIGNAL(clicked()), this, SLOT(PreAccept()));
	connect(ui.labelAbout, SIGNAL(linkActivated(const QString& )), this, SLOT(LinkClickHandler(const QString&)));
	ui.labelAbout->setTextFormat(Qt::RichText);
	ui.labelAbout->openExternalLinks();
    ui.labelAbout->setText("<center>Thanks For Your Support!<br> Please visit the link for updateds <br><a href=\"http://code.google.com/p/facebook-cpp-graph-api/\">facebook-cpp-graph-api</a></center");
    
	 
}
void SettingsDialog::LinkClickHandler(const QString& link)
{
    WRITELOG(link);
    QDesktopServices::openUrl(QUrl(link));
}
void SettingsDialog::PreAccept()
{
 	
	accept();
}
void SettingsDialog::PreReject()
{

}
void SettingsDialog::setPreDefinedConfig()
{
	/*QString path =  "";
	if(UT::getInstance()->GetAppSettings()->contains(SAVING_PATH_DIR))
	{
		path  = UT::getInstance()->GetAppSettings()->value(SAVING_PATH_DIR).toString();
		ui.lineEdit_Files_path->setText(path);
	}*/
	
}


void SettingsDialog::changeDirectory()
{
/* select a directory using file dialog */
   /* QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), directory.path());
    if ( path.isNull() == false )
    {
        directory.setPath(path);
		m_path = directory.path();
		ui.lineEdit_Files_path->setText(m_path);
        
    }*/
}
//! [0]
