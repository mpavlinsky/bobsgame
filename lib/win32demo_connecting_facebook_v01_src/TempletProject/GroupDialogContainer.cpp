#include "GroupDialogContainer.h"


GroupDialogContainer::GroupDialogContainer(QString GroupId,
										   QString GroupName,
											QWidget* parent): 
										    QDialog(parent),
										    m_GroupID(GroupId)  
									 
{
     ui.setupUi(this);
	 setWindowTitle(GroupName);
	 setAttribute(Qt::WA_DeleteOnClose);
	 WRITELOG(GroupId);
	
	//TestAPIs();
	// FBApi::getInstance()->GetGroupLastUpdate(m_GroupID);
  
}

 

GroupDialogContainer::GroupDialogContainer(QWidget* parent) : 
										   QDialog(parent) 
									 
{
 
	ui.setupUi(this);
	 
	
	//TestAPIs();
  
}

GroupDialogContainer::~GroupDialogContainer()
{
	;
}

void GroupDialogContainer::closeEvent(QCloseEvent *event)
 {
    
	 emit WindowClosed();
	 event->accept();
}