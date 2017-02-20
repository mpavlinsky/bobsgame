#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger DayCaption::log = Logger("DayCaption");


DayCaption::DayCaption(BGClientEngine* g)
{ //=========================================================================================================================
	this->e = g;
}

void DayCaption::init()
{ //=========================================================================================================================

	light = new Light(getEngine(), "dayLight", -100, 4, 10, 2, 255, 255, 255, 90, 16, 2.0f, 1.0f, 0, true, true);

	defaultFGColor = BobColor::white;
	defaultAAColor = BobColor::gray;
	defaultBGColor = BobColor::clear;

	currentFGColor = defaultFGColor;
	currentAAColor = defaultAAColor;
}

void DayCaption::update()
{ //=========================================================================================================================

	if (caption != nullptr)
	{
		caption->screenX = (float)GLUtils::getViewportWidth() - 95 * 2; //50*2;//timeCaption.caption_width*2;
		caption->setAlphaImmediately(1.0f);

		if (light != nullptr)
		{
			light->setX(caption->screenX + caption->getWidth() / 2 - 10);
		}
	}
}

void DayCaption::setPausedColor()
{ //=========================================================================================================================
	setColors(pausedFGColor, pausedAAColor, pausedBGColor);
}

void DayCaption::setUnknownColor()
{ //=========================================================================================================================
	setColors(unknownFGColor, unknownAAColor, unknownBGColor);
}

void DayCaption::setFastSpeedColor()
{ //=========================================================================================================================
	setColors(fastFGColor, fastAAColor, fastBGColor);
}

