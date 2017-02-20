#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger TitleScreenState::log = Logger("TitleScreenState");


TitleScreenState::TitleScreenState()
{ //=========================================================================================================================
}

void TitleScreenState::update()
{ //=========================================================================================================================


	ticks += (int)engineTicksPassed();
	if (ticks > 30)
	{
		ticks = 0;

		frame++;
		if (frame >= (int)Main::glowTileBackground->glowTileFramesTexture->size())
		{
			frame = 0;
			count++;
		}
	}


	if (count > 2)
	{
		//			Main.mainObject.createNewAccountState.cancelButton.setEnabled(false);
		//			Main.mainObject.createNewAccountState.cancelButton.setVisible(false);
		//			Main.mainObject.createNewAccountState.cancelButton.setActivated(true);
		Main::getMain()->stateManager->setState(Main::getMain()->createNewAccountState);
	}
}

void TitleScreenState::render()
{ //=========================================================================================================================


	BobTexture* t = Main::glowTileBackground->bgScrollTexture;

	BobTexture* over = Main::glowTileBackground->glowTileFramesTexture->get(frame);

	float screenWidth = (float)GLUtils::getViewportWidth();
	float screenHeight = (float)GLUtils::getViewportHeight();


	float scale = 2.0f;

	float x0 = screenWidth / 2 - (t->getImageWidth() * scale) / 2;
	float x1 = x0 + (t->getImageWidth() * scale);

	float y0 = screenHeight / 2 - (t->getImageHeight() * scale) / 2;
	float y1 = y0 + (t->getImageHeight() * scale);


	GLUtils::drawTexture(t, x0, x1, y0, y1, 1.0f, GLUtils::FILTER_NEAREST);
	GLUtils::drawTexture(over, x0, x1, y0, y1, 1.0f, GLUtils::FILTER_NEAREST);
}

