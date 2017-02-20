//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class GameStore : public MenuPanel
{
public:

	static Logger log;


	ArrayList<GameItem*>* games = new ArrayList<GameItem*>();
	//public GameListPanel gameStorePanel;


	GameStore();


	virtual void setActivated(bool b) override;


	virtual void render() override;
};

