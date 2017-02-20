//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class StateManager
{
public:

	static Logger log;


	State* currentState = nullptr;


	StateManager();


	virtual State* getState();


	virtual void setState(State* s);


	virtual void update();

	virtual void render();


};

