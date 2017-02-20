//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



class Logger;
class Engine;
class EnginePart;

//TODO: improve speed function for this
//TODO: maybe automatically shut off letterbox if leave room

//TODO: need getters and setters


class Letterbox : public EnginePart
{
	//letterbox

public:
	static Logger log;


private:
	float alpha = 1.0f;


	int sizeY = 0;

	float currentYOffset = 0;

	bool on = false;


	BobColor* color = BobColor::black;

	int ticksSlideDuration = 0;

	long long startTime = System::currentHighResTimer();


	/// <summary>
	/// letterbox takes in size, alpha, and speed.
	/// it will scroll from 0 to size on top and bottom.
	/// speed must be low. 0.1f * ticks(16) * 60fps = 96 pixels per second.
	/// </summary>
public:
	Letterbox(Engine* g);


	virtual void init();


	virtual void setAlpha();

	virtual void setColor();


	virtual void setLayer();


	virtual void setOn(int ticksSlideDuration, float percentY);


	virtual void setOn(int ticksSlideDuration, int sizeY);


	virtual void setOff(int ticksSlideDuration);


	virtual void update();


	virtual void render();
};

