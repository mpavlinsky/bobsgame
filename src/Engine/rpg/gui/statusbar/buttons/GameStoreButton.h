//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "StatusBarButton.h"


class GameStoreButton : public StatusBarButton
{
public:

	static Logger log;


	GameStoreButton(BGClientEngine* g);


	virtual void init() override;


	virtual void setOffsets() override;


	virtual void clicked() override;


	virtual bool isAssociatedMenuActive() override;
};

