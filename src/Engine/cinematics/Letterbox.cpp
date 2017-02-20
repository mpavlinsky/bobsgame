#include "stdafx.h"
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Letterbox::log = Logger("Letterbox");


class Easing;

Letterbox::Letterbox(Engine* g)
{ //=========================================================================================================================
	this->e = g;
}

void Letterbox::init()
{ //=========================================================================================================================
}

void Letterbox::setAlpha()
{
	//TODO
}

void Letterbox::setColor()
{
	//TODO
}

void Letterbox::setLayer()
{
	//TODO over/under getText? over/under statusbar?
}

void Letterbox::setOn(int ticksSlideDuration, float percentY)
{ //=========================================================================================================================
	this->ticksSlideDuration = ticksSlideDuration;
	sizeY = (int)(GLUtils::getViewportHeight() * percentY);
	startTime = System::currentHighResTimer();
	on = true;
}

void Letterbox::setOn(int ticksSlideDuration, int sizeY)
{ //=========================================================================================================================
	this->ticksSlideDuration = ticksSlideDuration;
	this->sizeY = sizeY;
	startTime = System::currentHighResTimer();
	on = true;
}

void Letterbox::setOff(int ticksSlideDuration)
{ //=========================================================================================================================

	this->ticksSlideDuration = ticksSlideDuration;
	startTime = System::currentHighResTimer();
	on = false;
}

void Letterbox::update()
{ //=========================================================================================================================



	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime) * getEngine()->engineSpeed);

	//if on, if scroll position isn't size_y scroll down
	if (on == true)
	{
		if (ticksPassed < ticksSlideDuration)
		{
			currentYOffset = (float)(Easing::easeInOutQuadratic(ticksPassed, 0, sizeY, ticksSlideDuration));
		}
		else
		{
			currentYOffset = (float)sizeY;
		}
	}


	//if off, if scroll position isnt 0, scroll up
	if (on == false)
	{
		if (ticksPassed < ticksSlideDuration)
		{
			currentYOffset = (float)(Easing::easeInOutQuadratic(ticksPassed, sizeY, 0, ticksSlideDuration));
		}
		else
		{
			currentYOffset = 0;
		}
	}
}

void Letterbox::render()
{ //=========================================================================================================================
	GLUtils::drawFilledRect(color->ri(), color->gi(), color->bi(), 0, (float)GLUtils::getViewportWidth(), 0, (float)sizeY, alpha);

	GLUtils::drawFilledRect(color->ri(), color->gi(), color->bi(), 0, (float)GLUtils::getViewportWidth(), (float)(GLUtils::getViewportHeight() - sizeY), (float)GLUtils::getViewportHeight(), alpha);
}

