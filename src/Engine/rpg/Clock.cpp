#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Clock::log = Logger("Clock");


Clock::Clock(Engine* g)
{ //=========================================================================================================================

	this->e = g;
	ticks = 0;
	second = 0;
	minute = 0;
	hour = 0;
	day = 0;

	//updateCaptions();
}

void Clock::update()
{ //=========================================================================================================================


	if (paused == false && unknown == false && getTextManager()->textEngineState == 0)
	{
		ticks += (int)getEngine()->engineTicksPassed();

		if (ticks >= 1000 || (ticks >= 1 && fast == true))
		{
			ticks -= 1000;
			second++; //10 seconds per second (60 vbls)
		}

		if (second >= 60)
		{
			second = 0;
			minute += 1; //ten minutes per minute

			getAudioManager()->playSound("tick", 0.25f, 1.0f, 1);
		}

		if (minute >= 60) //six minutes per hour,one day is 6*24 = 120 = 2 hours.
		{
			minute = 0;
			hour++;

			getAudioManager()->playSound("clockbeep", 0.25f, 1.0f, 1);
		}

		if (hour >= 24)
		{
			hour = 0;
			day++;

			///mailman_came_today=0;
			///icecreamman_came_today=0;
			///jogger_came_today=0;
			///dogwalker_came_today=0;
		}

		if (day >= 7 || day < 0)
		{
			day = 0;
		}
	}


	//		if(last_clock_paused!=paused)
	//		{
	//			last_clock_paused=paused;
	//			timeChanged=true;
	//		}


	updateCaptions();
}

void Clock::setTime(int day, int hour, int minute, int second)
{ //=========================================================================================================================


	if (hour > 23)
	{
		return;
	}
	if (minute > 59)
	{
		return;
	}
	if (second > 59)
	{
		return;
	}

	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->second = second;

	//updateCaptions();
}

void Clock::updateCaptions()
{ //=========================================================================================================================

	string clockString = "";
	string dayString = "";

	string minuteString = string("") + to_string(minute);
	if (minute < 10)
	{
		minuteString = string("0") + to_string(minute);
	}


	switch (hour)
	{
	case 0:
		{
			clockString = string(" 12:") + minuteString + string(" AM ");
			break;
		}
	case 1:
		{
			clockString = string(" 01:") + minuteString + string(" AM ");
			break;
		}
	case 2:
		{
			clockString = string(" 02:") + minuteString + string(" AM ");
			break;
		}
	case 3:
		{
			clockString = string(" 03:") + minuteString + string(" AM ");
			break;
		}
	case 4:
		{
			clockString = string(" 04:") + minuteString + string(" AM ");
			break;
		}
	case 5:
		{
			clockString = string(" 05:") + minuteString + string(" AM ");
			break;
		}
	case 6:
		{
			clockString = string(" 06:") + minuteString + string(" AM ");
			break;
		}
	case 7:
		{
			clockString = string(" 07:") + minuteString + string(" AM ");
			break;
		}
	case 8:
		{
			clockString = string(" 08:") + minuteString + string(" AM ");
			break;
		}
	case 9:
		{
			clockString = string(" 09:") + minuteString + string(" AM ");
			break;
		}
	case 10:
		{
			clockString = string(" 10:") + minuteString + string(" AM ");
			break;
		}
	case 11:
		{
			clockString = string(" 11:") + minuteString + string(" AM ");
			break;
		}
	case 12:
		{
			clockString = string(" 12:") + minuteString + string(" PM ");
			break;
		}
	case 13:
		{
			clockString = string(" 01:") + minuteString + string(" PM ");
			break;
		}
	case 14:
		{
			clockString = string(" 02:") + minuteString + string(" PM ");
			break;
		}
	case 15:
		{
			clockString = string(" 03:") + minuteString + string(" PM ");
			break;
		}
	case 16:
		{
			clockString = string(" 04:") + minuteString + string(" PM ");
			break;
		}
	case 17:
		{
			clockString = string(" 05:") + minuteString + string(" PM ");
			break;
		}
	case 18:
		{
			clockString = string(" 06:") + minuteString + string(" PM ");
			break;
		}
	case 19:
		{
			clockString = string(" 07:") + minuteString + string(" PM ");
			break;
		}
	case 20:
		{
			clockString = string(" 08:") + minuteString + string(" PM ");
			break;
		}
	case 21:
		{
			clockString = string(" 09:") + minuteString + string(" PM ");
			break;
		}
	case 22:
		{
			clockString = string(" 10:") + minuteString + string(" PM ");
			break;
		}
	case 23:
		{
			clockString = string(" 11:") + minuteString + string(" PM ");
			break;
		}
	default:
		{
			break;
		}
	}


	switch (day)
	{
	case 0:
		{
			dayString = " Sunday ";
			break;
		}
	case 1:
		{
			dayString = " Monday ";
			break;
		}
	case 2:
		{
			dayString = " Tuesday ";
			break;
		}
	case 3:
		{
			dayString = " Wednesday ";
			break;
		}
	case 4:
		{
			dayString = " Thursday ";
			break;
		}
	case 5:
		{
			dayString = " Friday ";
			break;
		}
	case 6:
		{
			dayString = " Saturday ";
			break;
		}
	default:
		{
			break;
		}
	}


	if (unknown)
	{
		clockString = " ??:?? ";
		dayString = " ?????? ";
	}

	if (getStatusBar()->clockCaption != nullptr)
	{
		getStatusBar()->clockCaption->updateCaption(clockString);
	}
	if (getStatusBar()->dayCaption != nullptr)
	{
		getStatusBar()->dayCaption->updateCaption(dayString);
	}

	if (Main::introMode) //TODO terrible hack
	{
		if (getStatusBar()->clockCaption != nullptr)
		{
			getStatusBar()->clockCaption->setColors(BobColor::green, BobColor::darkGreen, BobColor::clear);
		}
	}
}

void Clock::setPaused(bool b)
{ //=========================================================================================================================
	if (b == true)
	{
		setPausedOn();
	}
	if (b == false)
	{
		setPausedOff();
	}
}

void Clock::setPausedOn()
{ //=========================================================================================================================
	paused = true;
	getStatusBar()->clockCaption->setPausedColor();
}

void Clock::setPausedOff()
{ //=========================================================================================================================
	paused = false;
	if (unknown)
	{
		getStatusBar()->clockCaption->setUnknownColor();
	}
	else if (paused)
	{
		getStatusBar()->clockCaption->setPausedColor();
	}
	else if (fast)
	{
		getStatusBar()->clockCaption->setFastColor();
	}
	else
	{
		getStatusBar()->clockCaption->setDefaultColor();
	}
}

void Clock::setUnknown(bool b)
{ //=========================================================================================================================
	if (b == true)
	{
		setUnknownOn();
	}
	if (b == false)
	{
		setUnknownOff();
	}
}

void Clock::setUnknownOn()
{ //=========================================================================================================================
	unknown = true;
	getStatusBar()->clockCaption->setUnknownColor();
}

void Clock::setUnknownOff()
{ //=========================================================================================================================
	unknown = false;
	if (unknown)
	{
		getStatusBar()->clockCaption->setUnknownColor();
	}
	else if (paused)
	{
		getStatusBar()->clockCaption->setPausedColor();
	}
	else if (fast)
	{
		getStatusBar()->clockCaption->setFastColor();
	}
	else
	{
		getStatusBar()->clockCaption->setDefaultColor();
	}
}

void Clock::setFast(bool b)
{ //=========================================================================================================================
	if (b == true)
	{
		setFastOn();
	}
	if (b == false)
	{
		setFastOff();
	}
}

void Clock::setFastOn()
{ //=========================================================================================================================
	fast = true;
	getStatusBar()->clockCaption->setFastColor();
}

void Clock::setFastOff()
{ //=========================================================================================================================
	fast = false;
	if (unknown)
	{
		getStatusBar()->clockCaption->setUnknownColor();
	}
	else if (paused)
	{
		getStatusBar()->clockCaption->setPausedColor();
	}
	else if (fast)
	{
		getStatusBar()->clockCaption->setFastColor();
	}
	else
	{
		getStatusBar()->clockCaption->setDefaultColor();
	}
}

