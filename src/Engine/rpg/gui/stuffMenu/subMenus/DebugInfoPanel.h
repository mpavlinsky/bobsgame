//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class DebugInfoPanel : public SubPanel
{
public:

	static Logger log;


	//static ArrayList<Label*> label;

	//static DialogLayout::Group* horizontalGroup;
	//static DialogLayout::Group* verticalGroup;


	DebugInfoPanel();

	long long updateTicks = 0;


	virtual void update() override;
};

