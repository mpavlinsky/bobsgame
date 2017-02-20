
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger GameStoreButton::log = Logger("GameStoreButton");


GameStoreButton::GameStoreButton(BGClientEngine* g)
{ //=========================================================================================================================

	this->e = g;

	texture = GLUtils::getTextureFromPNG("data/statusbar/gameStore.png");


	offsetX0 = 0; // NDButton.dividerX+20;//120
	offsetX1 = 0; // offsetX0+124;//244

	pressedOffsetY = 0;
	offsetY0 = 3;
	offsetY1 = 5;

	dividerX = 0; // offsetX1+16;//260

	glowX0 = 0; // offsetX0-60;//60
	glowX1 = 0; // offsetX1+60;//184

	glowY0 = -40;
	glowY1 = 60;

	clickX0 = 100;
	clickX1 = dividerX;
}

void GameStoreButton::init()
{ //=========================================================================================================================

	setOffsets();
}

void GameStoreButton::setOffsets()
{ //=========================================================================================================================

	offsetX0 = getStatusBar()->ndButton->dividerX + 20; // 120
	offsetX1 = offsetX0 + 124; // 244
	dividerX = offsetX1 + 16; // 260
	glowX0 = offsetX0 - 60; // 60
	glowX1 = offsetX1 + 60; // 184

	clickX0 = 100;
	clickX1 = dividerX;
}

void GameStoreButton::clicked()
{ //=========================================================================================================================

	if (getPlayerEditMenu()->getIsActivated() == true)
	{
		return;
	}


	if (getStuffMenu()->getIsActivated() && getStuffMenu()->getIsScrollingDown() == false)
	{
		getStuffMenu()->toggleActivated();
	}

	getGameStore()->toggleActivated();
}

bool GameStoreButton::isAssociatedMenuActive()
{ //=========================================================================================================================

	return getGameStore()->getIsActivated();
}

