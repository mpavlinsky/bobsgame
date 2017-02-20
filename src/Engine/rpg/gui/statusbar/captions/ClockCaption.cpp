#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger ClockCaption::log = Logger("ClockCaption");


ClockCaption::ClockCaption(BGClientEngine* g)
{ //=========================================================================================================================
	this->e = g;
}

void ClockCaption::init()
{ //=========================================================================================================================

	//TODO: replace these lights with just pre-made pngs, less hackiness.

	light = new Light(getEngine(), "timeLight", -100, 4, 24, 2, 255, 0, 0, 90, 16, 2.0f, 1.0f, 0, true, true);


	defaultFGColor = BobColor::red;
	defaultAAColor = BobColor::darkRed;
	defaultBGColor = BobColor::clear;

	currentFGColor = defaultFGColor;
	currentAAColor = defaultAAColor;
	currentBGColor = defaultBGColor;
}

void ClockCaption::update()
{ //=========================================================================================================================


	//if(timecaption!=null)timecaption->getScale=2.0f/ZOOM;
	//if(daycaption!=null)daycaption->getScale=2.0f/ZOOM;


	if (caption != nullptr)
	{
		caption->screenX = (float)GLUtils::getViewportWidth() - 50 * 2; //50*2;//timeCaption.caption_width*2;

		//TODO: need to manually update the getCaption if they arent in the captionmanager. hmm. maybe have a different list for captions to be updated, or maybe just do captions by layer
		//TODO: make a global list of all captions that get updated, and a smaller managed subset that get rendered in the game

		//if i don't set the alpha they will never increase
		caption->setAlphaImmediately(1.0f);

		if (light != nullptr)
		{
			light->setX(caption->screenX + caption->getWidth() / 2 - 20);
		}
	}
}

void ClockCaption::setDarkTheme()
{ //=========================================================================================================================
}

void ClockCaption::setLightTheme()
{ //=========================================================================================================================
}

void ClockCaption::setPausedColor()
{ //=========================================================================================================================
	setColors(pausedFGColor, pausedAAColor, pausedBGColor);
}

void ClockCaption::setUnknownColor()
{ //=========================================================================================================================
	setColors(unknownFGColor, unknownAAColor, unknownBGColor);
}

void ClockCaption::setFastColor()
{ //=========================================================================================================================
	setColors(fastFGColor, fastAAColor, fastBGColor);
}

void ClockCaption::setColors(BobColor* fg, BobColor* aa, BobColor* bg)
{ //=========================================================================================================================

	StatusBarCaption::setColors(fg, aa, bg);

	if (light != nullptr && (light->r() != fg->ri() || light->g() != fg->gi() || light->b() != fg->bi()))
	{
		//light->deleteFromMapEntityListAndReleaseTexture();
		delete light;
		light = nullptr;
		light = new Light(getEngine(), "timeLight", -100, 4, 24, 2, fg->ri(), fg->gi(), fg->bi(), 90, 16, 2.0f, 1.0f, 0, true, true);
	}
}

