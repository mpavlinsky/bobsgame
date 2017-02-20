//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class StatusBarButton : public EnginePart
{
public:

	static Logger log;


	BobTexture* texture = nullptr;


	bool pulse = false;
	bool pulseInOut = false;
	int pulseTicks = 0;
	int lastPulseTicks = 0;


	float glowAlpha = 1.0f;
	bool glow = false;


	int offsetX0 = 0;
	int offsetX1 = 0; //offset0+60;

	int pressedOffsetY = 0;

	int offsetY0 = 0;
	int offsetY1 = 0;

	int dividerX = 0; //offsetX1+20;

	int glowX0 = 0; //offsetX0-60;
	int glowX1 = 0; //offsetX1+60;

	int glowY0 = 0;
	int glowY1 = 0;

	int clickX0 = 0;
	int clickX1 = 0;


	bool enabled = true;


	StatusBarButton();
	StatusBarButton(BGClientEngine* g);


	virtual void init();


	virtual void setOffsets();


	virtual void clicked();


	virtual bool isAssociatedMenuActive();


	virtual void update();


	virtual void setEnabled(bool b);


	virtual void render(int layer);
};

