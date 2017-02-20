//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




// support color
// support better speed function

//TODO: support fading out specific layers, over/under player, textbox, etc

//TODO: need getters and setters

//TODO: need to know whether to fade in/out or instant on/off


class ScreenOverlay : public EnginePart
{
	//screen fadeout


public:

	static Logger log;

	BobColor* color = BobColor::black;


private:
	float startAlpha = 0.0f;
	float alpha = 0.0f;
	float toAlpha = 0.0f;


	long long startTime = System::currentHighResTimer();
	long long durationTicks = 0;


	//0 = one way , 1 = two-way
	int transitionType = 0;


	const int TYPE_ONE_WAY = 0;
	const int TYPE_ROUNDTRIP = 1;
	const int TYPE_INSTANT = 2;


	/// <summary>
	/// fade screen in or out to a Slick Color, taking in speed.
	/// speed should be low, 0.0f01f * ticks(16) = 0.0f16f* 60 fps = 0.96 seconds to full opacity.
	/// </summary>
public:
	ScreenOverlay(Engine* g);


	virtual void init();


	virtual void doTransition(BobColor* color, float fromAlpha, float toAlpha, int ticks);


	virtual void doToAndFromTransition(BobColor* color, int ticks, float toAlpha);

	virtual void setInstantOverlay(BobColor* color, float alpha);


	virtual void update();

	virtual void clearOverlays();


	virtual void render();
};

