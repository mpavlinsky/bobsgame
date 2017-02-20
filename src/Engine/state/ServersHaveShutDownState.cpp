#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger ServersHaveShutDownState::log = Logger("ServersHaveShutDownState");


ServersHaveShutDownState::ServersHaveShutDownState()
{ //=========================================================================================================================
}

void ServersHaveShutDownState::update()
{ //=========================================================================================================================
}

GlowTileBackground* Main::glowTileBackground;

void ServersHaveShutDownState::render()
{ //=========================================================================================================================


	Main::glowTileBackground->render();


	GLUtils::drawFilledRect(0, 0, 0, 0, (float)GLUtils::getViewportWidth(), 0, (float)GLUtils::getViewportHeight(), 0.5f);
	GLUtils::drawOutlinedString("The servers have shut down for updating.", (float)GLUtils::getViewportWidth() / 2 - 60, (float)GLUtils::getViewportHeight() / 2 - 12, BobColor::white);
	GLUtils::drawOutlinedString("Your progress was saved. Please reload the client.", (float)GLUtils::getViewportWidth() / 2 - 70, (float)GLUtils::getViewportHeight() / 2 + 12, BobColor::gray);
}

void ServersHaveShutDownState::cleanup()
{ //=========================================================================================================================
}

