//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class StuffButton : public StatusBarButton
{
public:

	static Logger log;


	StuffButton(BGClientEngine* g);


	virtual void init() override;


	virtual void setOffsets() override;


	virtual void clicked() override;

	virtual bool isAssociatedMenuActive() override;
};

