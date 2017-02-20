//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class NDButton : public StatusBarButton
{
public:

	static Logger log;


	NDButton(BGClientEngine* g);


	virtual void init() override;


	virtual void setOffsets() override;


	virtual void clicked() override;

	virtual bool isAssociatedMenuActive() override;
};

