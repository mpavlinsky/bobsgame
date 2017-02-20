#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger YouWillBeNotifiedState::log = Logger("YouWillBeNotifiedState");


YouWillBeNotifiedState::YouWillBeNotifiedState()
{ //=========================================================================================================================
}

void YouWillBeNotifiedState::update()
{ //=========================================================================================================================
}

void YouWillBeNotifiedState::render()
{ //=========================================================================================================================


	Main::glowTileBackground->render();

	string text = "To be continued...";

	GLUtils::drawFilledRect(0, 0, 0, 0, (float)GLUtils::getViewportWidth(), 0, (float)GLUtils::getViewportHeight(), 0.5f);
	GLUtils::drawOutlinedString(text, (float)GLUtils::getViewportWidth() / 2 - GLUtils::getOutlinedTextWidth(text) / 2, (float)GLUtils::getViewportHeight() / 2, BobColor::white);
}

void YouWillBeNotifiedState::cleanup()
{ //=========================================================================================================================
}

