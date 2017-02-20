#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger StuffButton::log = Logger("StuffButton");


StuffButton::StuffButton(BGClientEngine* g)
{ // =========================================================================================================================
	this->e = g;


	texture = GLUtils::getTextureFromPNG("data/statusbar/stuff.png");


	offsetX0 = 0; // GameStoreButton.dividerX+20;//280
	offsetX1 = 0; // offsetX0+54;//334

	pressedOffsetY = 0;
	offsetY0 = 3;
	offsetY1 = 5;


	dividerX = 0; // offsetX1+20;//254

	glowX0 = 0; // offsetX0-60;
	glowX1 = 0; // offsetX1+60;

	glowY0 = -40;
	glowY1 = 60;

	clickX0 = 260;
	clickX1 = dividerX;
}

void StuffButton::init()
{ //=========================================================================================================================
	setOffsets();
}

void StuffButton::setOffsets()
{ //=========================================================================================================================

	offsetX0 = getStatusBar()->gameStoreButton->dividerX + 20; // 280
	offsetX1 = offsetX0 + 54; // 334
	dividerX = offsetX1 + 20; // 254


	glowX0 = offsetX0 - 60;
	glowX1 = offsetX1 + 60;

	clickX0 = 260;
	clickX1 = dividerX;
}

void StuffButton::clicked()
{ //=========================================================================================================================

	if (PlayerEditMenu().getIsActivated() == true)
	{
		return;
	}

	// only open/close if we're on this tab or it isn't showing
	// if(StartMenuWidget.isShowing==false||StartMenuWidget.statusPanel.isVisible()==true)
	if (getGameStore()->getIsActivated() && getGameStore()->getIsScrollingDown() == false)
	{
		getGameStore()->toggleActivated();
	}

	getStuffMenu()->toggleActivated();

	//   getStuffMenu()->stuffMenuTabs[0]->getModel().setSelected(true);
	//   getStuffMenu()->stuffMenuTabs[0]->getModel().fireActionCallback();
}

bool StuffButton::isAssociatedMenuActive()
{ //=========================================================================================================================

	return getStuffMenu()->getIsActivated();
}

