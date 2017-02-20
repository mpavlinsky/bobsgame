
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once



Logger NDButton::log = Logger("NDButton");


NDButton::NDButton(BGClientEngine* g)
{ //=========================================================================================================================

	this->e = g;

	texture = GLUtils::getTextureFromPNG("data/statusbar/nDButton.png");


	offsetX0 = 20;
	offsetX1 = 0; // offset0+60;

	pressedOffsetY = 0;
	offsetY0 = 0;
	offsetY1 = 2;

	dividerX = 0; // offsetX1+20;

	glowX0 = 0; // offsetX0-60;
	glowX1 = 0; // offsetX1+60;

	glowY0 = -40;
	glowY1 = 60;


	clickX0 = 0;
	clickX1 = dividerX;
}

void NDButton::init()
{ //=========================================================================================================================

	setOffsets();
}

void NDButton::setOffsets()
{ //=========================================================================================================================

	offsetX1 = offsetX0 + 60;
	dividerX = offsetX1 + 20;
	glowX0 = offsetX0 - 60;
	glowX1 = offsetX1 + 60;

	clickX0 = 0;
	clickX1 = dividerX;
}

void NDButton::clicked()
{ //=========================================================================================================================

	if (getPlayerEditMenu()->getIsActivated() == true)
	{
		return;
	}

	getND()->toggleActivated();
}

bool NDButton::isAssociatedMenuActive()
{ //=========================================================================================================================

	return getND()->getIsActivated();
}

