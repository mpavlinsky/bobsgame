#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger ScreenOverlay::log = Logger("ScreenOverlay");


ScreenOverlay::ScreenOverlay(Engine* g)
{ //=========================================================================================================================
	this->e = g;
}

void ScreenOverlay::init()
{ //=========================================================================================================================
}

void ScreenOverlay::doTransition(BobColor* color, float fromAlpha, float toAlpha, int ticks)
{ //=========================================================================================================================

	this->color = color;

	this->startTime = System::currentHighResTimer();

	if (fromAlpha != -1)
	{
		this->startAlpha = fromAlpha;
	}
	else
	{
		startAlpha = alpha;
	}

	this->alpha = startAlpha;

	this->toAlpha = toAlpha;

	this->durationTicks = ticks;

	this->transitionType = TYPE_ONE_WAY;
}

void ScreenOverlay::doToAndFromTransition(BobColor* color, int ticks, float toAlpha)
{ //=========================================================================================================================


	this->color = color;

	this->startTime = System::currentHighResTimer();


	this->alpha = 0;
	this->toAlpha = toAlpha;

	this->durationTicks = ticks;


	this->transitionType = TYPE_ROUNDTRIP;
}

void ScreenOverlay::setInstantOverlay(BobColor* color, float alpha)
{ //=========================================================================================================================

	this->color = color;

	this->startTime = System::currentHighResTimer();


	this->alpha = alpha;
	this->toAlpha = alpha;

	this->durationTicks = 0;


	this->transitionType = TYPE_INSTANT;
}

void ScreenOverlay::update()
{ //=========================================================================================================================

	
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime) * getEngine()->engineSpeed);

	if (transitionType == TYPE_ONE_WAY)
	{
		if (ticksPassed < durationTicks)
		{
			alpha = (float)(Easing::easeInOutQuadratic(ticksPassed, startAlpha, toAlpha - startAlpha, (float)durationTicks));
		}
		else
		{
			alpha = toAlpha;
			//getToAlpha=0;
			//startAlpha=0;
			//durationTicks=0;
		}
	}
	else
	{
		if (transitionType == TYPE_ROUNDTRIP)
		{
			if (ticksPassed < durationTicks / 2)
			{
				alpha = (float)(Easing::easeInOutQuadratic(ticksPassed, 0, toAlpha, (float)durationTicks));
			}
			else
			{
				if (ticksPassed < durationTicks)
				{
					alpha = (float)(Easing::easeInOutQuadratic(ticksPassed, toAlpha, 0, (float)durationTicks));
				}
				else
				{
					alpha = 0;
				}
			}
		}
		else
		{
			if (transitionType == TYPE_INSTANT)
			{
				alpha = toAlpha;
			}
		}
	}
}

void ScreenOverlay::clearOverlays()
{ //=========================================================================================================================
	alpha = 0;
	toAlpha = 0;
	transitionType = TYPE_INSTANT;
	color = BobColor::black;
}

void ScreenOverlay::render()
{ //=========================================================================================================================
	GLUtils::drawFilledRect(color->ri(), color->gi(), color->bi(), 0, (float)GLUtils::getViewportWidth(), 0, (float)GLUtils::getViewportHeight(), alpha);
}

