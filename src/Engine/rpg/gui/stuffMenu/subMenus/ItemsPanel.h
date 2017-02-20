//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class ItemsPanel : public SubPanel
{
public:

	static Logger log;


	//ArrayList<DialogLayout*> itemDialogLayout;

	//DialogLayout::Group* horizontalGroup = nullptr;
	//DialogLayout::Group* verticalGroup = nullptr;


	ItemsPanel();


	virtual void updateItems();


	virtual void layout() override;


	virtual void setVisible(bool b) override;
};

