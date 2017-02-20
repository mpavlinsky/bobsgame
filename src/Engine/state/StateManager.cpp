#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger StateManager::log = Logger("StateManager");


StateManager::StateManager()
{ //=========================================================================================================================
}

State* StateManager::getState()
{ //=========================================================================================================================
	return currentState;
}

void StateManager::setState(State* s)
{ //=========================================================================================================================
	currentState = s;
}

void StateManager::update()
{
	State::updateTimers();
	currentState->update();
}

void StateManager::render()
{
	currentState->render();
}

