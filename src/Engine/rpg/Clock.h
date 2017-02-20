//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class Clock : public EnginePart
{
public:
	static Logger log;

private:
	bool paused = false;
	bool unknown = false;
	bool fast = false;


public:
	int ticks = 0;
	int second = 0;
	int minute = 0;
	int hour = 0;
	int day = 0;


	Clock(Engine* g);


	virtual void update();


	virtual void setTime(int day, int hour, int minute, int second);


	virtual void updateCaptions();


	virtual void setPaused(bool b);


	virtual void setPausedOn();

	virtual void setPausedOff();


	virtual void setUnknown(bool b);

	virtual void setUnknownOn();

	virtual void setUnknownOff();


	virtual void setFast(bool b);

	virtual void setFastOn();

	virtual void setFastOff();
};

