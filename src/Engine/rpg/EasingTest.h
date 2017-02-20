//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



class EasingTest : public EnginePart
{
public:
	static Caption* linearTweenCaption;

	static Caption* easeInQuadCaption;
	static Caption* easeInCubicCaption;
	static Caption* easeInQuartCaption;
	static Caption* easeInQuintCaption;
	static Caption* easeInExpoCaption;
	static Caption* easeInCircCaption;
	static Caption* easeInSineCaption;

	static Caption* easeOutQuadCaption;
	static Caption* easeOutCubicCaption;
	static Caption* easeOutQuartCaption;
	static Caption* easeOutQuintCaption;
	static Caption* easeOutExpoCaption;
	static Caption* easeOutCircCaption;
	static Caption* easeOutSineCaption;

	static Caption* easeInOutQuadCaption;
	static Caption* easeInOutCubicCaption;
	static Caption* easeInOutQuartCaption;
	static Caption* easeInOutQuintCaption;
	static Caption* easeInOutExpoCaption;
	static Caption* easeInOutCircCaption;
	static Caption* easeInOutSineCaption;


	EasingTest(Engine* g);


	static float ticksCount;
	static float duration;
	static float beginningValue;
	static float changeInValue;

	virtual void update();
};

