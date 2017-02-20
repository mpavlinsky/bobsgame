//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class MiniGameEngine;

class StadiumScreen : public EnginePart
{
public:

	static Logger log;


	//static const int getViewportWidth() = 640 * 2;
	//static const int getViewportHeight() = 480 * 2;
	//static const int FBO_SCALE = 1;


	StateManager* stadiumGameStateManager;


	Area* area;


	StadiumScreen(Engine* g);


	virtual void update();


	virtual void setGame(MiniGameEngine* game, Area* area);


	virtual MiniGameEngine* getGame();


	virtual void render();
};

