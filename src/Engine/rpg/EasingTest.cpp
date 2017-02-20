
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger EasingTest::log = Logger("EasingTest");


Caption* EasingTest::linearTweenCaption = nullptr;
Caption* EasingTest::easeInQuadCaption = nullptr;
Caption* EasingTest::easeInCubicCaption = nullptr;
Caption* EasingTest::easeInQuartCaption = nullptr;
Caption* EasingTest::easeInQuintCaption = nullptr;
Caption* EasingTest::easeInExpoCaption = nullptr;
Caption* EasingTest::easeInCircCaption = nullptr;
Caption* EasingTest::easeInSineCaption = nullptr;
Caption* EasingTest::easeOutQuadCaption = nullptr;
Caption* EasingTest::easeOutCubicCaption = nullptr;
Caption* EasingTest::easeOutQuartCaption = nullptr;
Caption* EasingTest::easeOutQuintCaption = nullptr;
Caption* EasingTest::easeOutExpoCaption = nullptr;
Caption* EasingTest::easeOutCircCaption = nullptr;
Caption* EasingTest::easeOutSineCaption = nullptr;
Caption* EasingTest::easeInOutQuadCaption = nullptr;
Caption* EasingTest::easeInOutCubicCaption = nullptr;
Caption* EasingTest::easeInOutQuartCaption = nullptr;
Caption* EasingTest::easeInOutQuintCaption = nullptr;
Caption* EasingTest::easeInOutExpoCaption = nullptr;
Caption* EasingTest::easeInOutCircCaption = nullptr;
Caption* EasingTest::easeInOutSineCaption = nullptr;

EasingTest::EasingTest(Engine* g) : EnginePart(g)
{
	linearTweenCaption = getCaptionManager()->newManagedCaption(0, 20 * 2, -1, "linear", BobFont::font_small_8_outlined, BobColor::white, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);

	easeInQuadCaption = getCaptionManager()->newManagedCaption(0, 20 * 3, -1, "x^2", BobFont::font_small_8_outlined, BobColor::red, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeInCubicCaption = getCaptionManager()->newManagedCaption(0, 20 * 4, -1, "x^3", BobFont::font_small_8_outlined, BobColor::red, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeInQuartCaption = getCaptionManager()->newManagedCaption(0, 20 * 5, -1, "x^4", BobFont::font_small_8_outlined, BobColor::red, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeInQuintCaption = getCaptionManager()->newManagedCaption(0, 20 * 6, -1, "x^5", BobFont::font_small_8_outlined, BobColor::red, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeInExpoCaption = getCaptionManager()->newManagedCaption(0, 20 * 7, -1, "2^x", BobFont::font_small_8_outlined, BobColor::red, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeInCircCaption = getCaptionManager()->newManagedCaption(0, 20 * 8, -1, "sqrt(1-x^2)", BobFont::font_small_8_outlined, BobColor::red, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeInSineCaption = getCaptionManager()->newManagedCaption(0, 20 * 9, -1, "sin(x)", BobFont::font_small_8_outlined, BobColor::red, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);

	easeOutQuadCaption = getCaptionManager()->newManagedCaption(0, 20 * 12, -1, "x^2", BobFont::font_small_8_outlined, BobColor::green, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeOutCubicCaption = getCaptionManager()->newManagedCaption(0, 20 * 13, -1, "x^3", BobFont::font_small_8_outlined, BobColor::green, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeOutQuartCaption = getCaptionManager()->newManagedCaption(0, 20 * 14, -1, "x^4", BobFont::font_small_8_outlined, BobColor::green, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeOutQuintCaption = getCaptionManager()->newManagedCaption(0, 20 * 15, -1, "x^5", BobFont::font_small_8_outlined, BobColor::green, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeOutExpoCaption = getCaptionManager()->newManagedCaption(0, 20 * 16, -1, "2^x", BobFont::font_small_8_outlined, BobColor::green, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeOutCircCaption = getCaptionManager()->newManagedCaption(0, 20 * 17, -1, "sqrt(1-x^2)", BobFont::font_small_8_outlined, BobColor::green, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeOutSineCaption = getCaptionManager()->newManagedCaption(0, 20 * 18, -1, "sin(x)", BobFont::font_small_8_outlined, BobColor::green, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);

	easeInOutQuadCaption = getCaptionManager()->newManagedCaption(0, 20 * 21, -1, "^2", BobFont::font_small_8_outlined, BobColor::yellow, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeInOutCubicCaption = getCaptionManager()->newManagedCaption(0, 20 * 22, -1, "^3", BobFont::font_small_8_outlined, BobColor::yellow, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeInOutQuartCaption = getCaptionManager()->newManagedCaption(0, 20 * 23, -1, "^4", BobFont::font_small_8_outlined, BobColor::yellow, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeInOutQuintCaption = getCaptionManager()->newManagedCaption(0, 20 * 24, -1, "^5", BobFont::font_small_8_outlined, BobColor::yellow, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeInOutExpoCaption = getCaptionManager()->newManagedCaption(0, 20 * 25, -1, "2^x", BobFont::font_small_8_outlined, BobColor::yellow, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeInOutCircCaption = getCaptionManager()->newManagedCaption(0, 20 * 26, -1, "sqrt(1-x^2)", BobFont::font_small_8_outlined, BobColor::yellow, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
	easeInOutSineCaption = getCaptionManager()->newManagedCaption(0, 20 * 27, -1, "sin(x)", BobFont::font_small_8_outlined, BobColor::yellow, nullptr, BobColor::black, RenderOrder::OVER_GUI, 1.0f, 0);
}

float EasingTest::ticksCount = 0;
float EasingTest::duration = 2000;
float EasingTest::beginningValue = 100;
float EasingTest::changeInValue = (float)GLUtils::getViewportWidth() - 200;

void EasingTest::update()
{
	changeInValue = (float)GLUtils::getViewportWidth() - 200;

	ticksCount += getEngine()->engineTicksPassed();
	if (ticksCount > duration)
	{
		ticksCount = 0;

		if (changeInValue > 0)
		{
			changeInValue *= -1;
			beginningValue = (float)GLUtils::getViewportWidth() - 100;
		}
		else
		{
			changeInValue *= -1;
			beginningValue = 100;
		}
	}


	linearTweenCaption->screenX = (float)(Easing::linearTween(ticksCount, beginningValue, changeInValue, duration));

	easeInQuadCaption->screenX = (float)(Easing::easeInQuadratic(ticksCount, beginningValue, changeInValue, duration));
	easeOutQuadCaption->screenX = (float)(Easing::easeOutQuadratic(ticksCount, beginningValue, changeInValue, duration));
	easeInOutQuadCaption->screenX = (float)(Easing::easeInOutQuadratic(ticksCount, beginningValue, changeInValue, duration));

	easeInCubicCaption->screenX = (float)(Easing::easeInCubic(ticksCount, beginningValue, changeInValue, duration));
	easeOutCubicCaption->screenX = (float)(Easing::easeOutCubic(ticksCount, beginningValue, changeInValue, duration));
	easeInOutCubicCaption->screenX = (float)(Easing::easeInOutCubic(ticksCount, beginningValue, changeInValue, duration));

	easeInQuartCaption->screenX = (float)(Easing::easeInQuartic(ticksCount, beginningValue, changeInValue, duration));
	easeOutQuartCaption->screenX = (float)(Easing::easeOutQuartic(ticksCount, beginningValue, changeInValue, duration));
	easeInOutQuartCaption->screenX = (float)(Easing::easeInOutQuartic(ticksCount, beginningValue, changeInValue, duration));

	easeInQuintCaption->screenX = (float)(Easing::easeInQuintic(ticksCount, beginningValue, changeInValue, duration));
	easeOutQuintCaption->screenX = (float)(Easing::easeOutQuintic(ticksCount, beginningValue, changeInValue, duration));
	easeInOutQuintCaption->screenX = (float)(Easing::easeInOutQuintic(ticksCount, beginningValue, changeInValue, duration));


	easeInSineCaption->screenX = (float)(Easing::easeInSinusoidal(ticksCount, beginningValue, changeInValue, duration));
	easeOutSineCaption->screenX = (float)(Easing::easeOutSinusoidal(ticksCount, beginningValue, changeInValue, duration));
	easeInOutSineCaption->screenX = (float)(Easing::easeInOutSinusoidal(ticksCount, beginningValue, changeInValue, duration));


	easeInExpoCaption->screenX = (float)(Easing::easeInExponential(ticksCount, beginningValue, changeInValue, duration));
	easeOutExpoCaption->screenX = (float)(Easing::easeOutExponential(ticksCount, beginningValue, changeInValue, duration));
	easeInOutExpoCaption->screenX = (float)(Easing::easeInOutExponential(ticksCount, beginningValue, changeInValue, duration));

	easeInCircCaption->screenX = (float)(Easing::easeInCircular(ticksCount, beginningValue, changeInValue, duration));
	easeOutCircCaption->screenX = (float)(Easing::easeOutCircular(ticksCount, beginningValue, changeInValue, duration));
	easeInOutCircCaption->screenX = (float)(Easing::easeInOutCircular(ticksCount, beginningValue, changeInValue, duration));
}

