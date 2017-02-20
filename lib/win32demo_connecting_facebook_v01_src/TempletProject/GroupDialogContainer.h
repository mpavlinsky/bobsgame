#ifndef __GROUPDIALOGCONTAINER_H_
#define __GROUPDIALOGCONTAINER_H_
#include "Constants.h"
 #include <QtGui>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
 
#include "FBApi.h"
    

class GroupDialogContainer : public QDialog
{
	Q_OBJECT
	 

public:
	GroupDialogContainer(QString GroupId,QString GroupName,QWidget *parent=0); 
	GroupDialogContainer(QWidget *parent=0);
	QString GetGroupID(){ return m_GroupID; }
	virtual ~GroupDialogContainer();
	Ui::GroupDialog ui;
	
public slots:
    void closeEvent(QCloseEvent *event);

signals:
    void WindowClosed();

private:
    QString m_GroupID;

};

#endif