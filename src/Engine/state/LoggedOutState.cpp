#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger LoggedOutState::log = Logger("LoggedOutState");


LoggedOutState::LoggedOutState()
{ //=========================================================================================================================
}

void LoggedOutState::update()
{ //=========================================================================================================================

	//   if (Keyboard::isKeyDown(Keyboard::KEY_L))
	//   {
	//      Main::mainObject->stateManager->setState(Main::mainObject->gameEngine);
	//   }
}

void LoggedOutState::render()
{ //=========================================================================================================================


	Main::glowTileBackground->render();


	GLUtils::drawFilledRect(0, 0, 0, 0, (float)GLUtils::getViewportWidth(), 0, (float)GLUtils::getViewportHeight(), 0.5f);
	GLUtils::drawOutlinedString("You have been logged out by a different session.", (float)GLUtils::getViewportWidth() / 2 - 70, (float)GLUtils::getViewportHeight() / 2 - 12, BobColor::white);
	GLUtils::drawOutlinedString("Press L to take this session back and log out that one.", (float)GLUtils::getViewportWidth() / 2 - 90, (float)GLUtils::getViewportHeight() / 2 + 12, BobColor::gray);
}

void LoggedOutState::cleanup()
{ //=========================================================================================================================
}

