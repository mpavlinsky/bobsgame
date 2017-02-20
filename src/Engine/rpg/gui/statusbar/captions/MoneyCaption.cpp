#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger MoneyCaption::log = Logger("MoneyCaption");


MoneyCaption::MoneyCaption(BGClientEngine* g)
{ //=========================================================================================================================
	this->e = g;
}

void MoneyCaption::init()
{ //=========================================================================================================================

	light = new Light(getEngine(), "moneyLight", -100, 4, 18, 6, 0, 255, 0, 70, 10, 2.0f, 1.0f, 0, true, true); // divided by 2 because lights take 1x pixels from tools

	defaultFGColor = BobColor::green;
	defaultAAColor = BobColor::darkerGreen;
	defaultBGColor = BobColor::clear;

	currentFGColor = defaultFGColor;
	currentAAColor = defaultAAColor;
}

void MoneyCaption::render(int layer)
{ //=========================================================================================================================

	if (enabled == false)
	{
		return;
	}

	StatusBarCaption::render(layer);

	if (layer == 1)
	{
		GLUtils::drawTexture(StatusBar::dividerTexture, (float)dividerX, (float)dividerX + 3, 0, (float)StatusBar::sizeY - 1, 1.0f, GLUtils::FILTER_LINEAR);
	}
}

void MoneyCaption::update()
{ //=========================================================================================================================


	if (caption != nullptr)
	{
		caption->screenX = (float)GLUtils::getViewportWidth() - (100 * 2) - caption->texture->getImageWidth(); //100*2;//timeCaption.caption_width*2+dayCaption.caption_width*2;
		caption->setAlphaImmediately(1.0f);

		if (light != nullptr)
		{
			light->setX(caption->screenX + caption->getWidth() / 2 - 15);
		}

		dividerX = (int)(caption->screenX) - 20;
	}
}

