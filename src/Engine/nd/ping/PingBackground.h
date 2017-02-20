//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class PingBackground : public EnginePart
{
public:

	static Logger log;


	PingBackground(Engine* g);


	bool tvRolling = false;
	int scrollingBackgroundX = 0;
	bool backgroundShakeDirectionToggle = false;
	bool tvScanlinesColorPulseToggle = false;

	bool backgroundInit = false;
	BobTexture* backgroundTexture = nullptr;
	int screenX = 0;
	int screenY = 0;


	long long pulseTicks = 0;
	long long rollTicks = 0;


	virtual void init();


	virtual void update();


	virtual void render();
};

