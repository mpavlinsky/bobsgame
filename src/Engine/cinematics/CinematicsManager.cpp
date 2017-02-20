#include "stdafx.h"
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger CinematicsManager::log = Logger("CinematicsManager");


CinematicsManager::CinematicsManager(Engine* g)
{ //=========================================================================================================================

	this->e = g;

	screenOverlayOverLights = new ScreenOverlay(g);
	screenOverlayUnderLights = new ScreenOverlay(g);
	screenOverlayGroundLayer = new ScreenOverlay(g);

	letterbox = new Letterbox(g);
}

void CinematicsManager::init()
{ //=========================================================================================================================

	log.info("Init CinematicsManager");

	screenOverlayOverLights->init();
	screenOverlayUnderLights->init();
	screenOverlayGroundLayer->init();


	letterbox->init();
}

void CinematicsManager::update()
{ //=========================================================================================================================
	letterbox->update();

	screenOverlayOverLights->update();
	screenOverlayUnderLights->update();
	screenOverlayGroundLayer->update();
}

void CinematicsManager::render(RenderOrder renderOrder)
{ //=========================================================================================================================
	if (renderOrder == RenderOrder::GROUND)
	{
		screenOverlayGroundLayer->render();
	}

	if (renderOrder == RenderOrder::ABOVE)
	{
		screenOverlayUnderLights->render();
	}

	if (renderOrder == RenderOrder::ABOVE_TOP)
	{
		letterbox->render();
		screenOverlayOverLights->render();
	}
}

void CinematicsManager::setLetterbox(bool on, int slideDurationTicks, int size)
{ //=========================================================================================================================
	if (on == true)
	{
		letterbox->setOn(slideDurationTicks, size);
	}
	else
	{
		letterbox->setOff(slideDurationTicks);
	}
}

void CinematicsManager::setLetterbox(bool on, int slideDurationTicks, float sizePercent)
{ //=========================================================================================================================
	if (on == true)
	{
		letterbox->setOn(slideDurationTicks, sizePercent);
	}
	else
	{
		letterbox->setOff(slideDurationTicks);
	}
}

void CinematicsManager::fadeToWhite(int ticks)
{ //=========================================================================================================================
	screenOverlayOverLights->doTransition(BobColor::white, 0.0f, 1.0f, ticks);
}

void CinematicsManager::fadeFromWhite(int ticks)
{ //=========================================================================================================================
	screenOverlayOverLights->doTransition(BobColor::white, 1.0f, 0.0f, ticks);
}

void CinematicsManager::fadeToBlack(int ticks)
{ //=========================================================================================================================
	screenOverlayOverLights->doTransition(BobColor::black, 0.0f, 1.0f, ticks);
}

void CinematicsManager::fadeFromBlack(int ticks)
{ //=========================================================================================================================
	screenOverlayOverLights->doTransition(BobColor::black, 1.0f, 0.0f, ticks);
}

void CinematicsManager::fadeColorFromCurrentAlphaToAlpha(int ticks, int ri, int gi, int bi, float toAlpha)
{ //=========================================================================================================================
	screenOverlayOverLights->doTransition(new BobColor(ri, gi, bi), -1, toAlpha, ticks);
}

void CinematicsManager::fadeColorFromAlphaToAlpha(int ticks, int ri, int gi, int bi, float fromAlpha, float toAlpha)
{ //=========================================================================================================================
	screenOverlayOverLights->doTransition(new BobColor(ri, gi, bi), fromAlpha, toAlpha, ticks);
}

void CinematicsManager::fadeColorFromTransparentToAlphaBackToTransparent(int ticks, int ri, int gi, int bi, float toAlpha)
{ //=========================================================================================================================
	screenOverlayOverLights->doToAndFromTransition(new BobColor(ri, gi, bi), ticks, toAlpha);
}

void CinematicsManager::setInstantOverlayColor(int ri, int gi, int bi, float a)
{ //=========================================================================================================================
	screenOverlayOverLights->setInstantOverlay(new BobColor(ri, gi, bi), a);
}

void CinematicsManager::clearOverlay()
{ //=========================================================================================================================
	screenOverlayOverLights->clearOverlays();
}

void CinematicsManager::fadeColorFromCurrentAlphaToAlphaUnderLights(int ticks, int ri, int gi, int bi, float toAlpha)
{ //=========================================================================================================================
	screenOverlayUnderLights->doTransition(new BobColor(ri, gi, bi), -1, toAlpha, ticks);
}

void CinematicsManager::setInstantOverlayColorUnderLights(int ri, int gi, int bi, float a)
{ //=========================================================================================================================
	screenOverlayUnderLights->setInstantOverlay(new BobColor(ri, gi, bi), a);
}

void CinematicsManager::clearOverlayUnderLights()
{ //=========================================================================================================================
	screenOverlayUnderLights->clearOverlays();
}

void CinematicsManager::fadeColorFromCurrentAlphaToAlphaGroundLayer(int ticks, int ri, int gi, int bi, float toAlpha)
{ //=========================================================================================================================
	screenOverlayGroundLayer->doTransition(new BobColor(ri, gi, bi), -1, toAlpha, ticks);
}

void CinematicsManager::setInstantOverlayColorGroundLayer(int ri, int gi, int bi, float a)
{ //=========================================================================================================================
	screenOverlayGroundLayer->setInstantOverlay(new BobColor(ri, gi, bi), a);
}

void CinematicsManager::clearOverlayGroundLayer()
{ //=========================================================================================================================
	screenOverlayGroundLayer->clearOverlays();
}

void CinematicsManager::set8BitMode(bool b)
{ //=========================================================================================================================
	getMapManager()->effects8Bit = b;
}

void CinematicsManager::setInvertedColors(bool b)
{ //=========================================================================================================================
	getMapManager()->effectsInverted = b;
}

void CinematicsManager::setBlackAndWhite(bool b)
{ //=========================================================================================================================
	getMapManager()->effectsBlackAndWhite = b;
}

void CinematicsManager::setRotate(bool b)
{ //=========================================================================================================================

	//rotate in a "swing" fashion, back and forth
	//getMapManager()->swingBackAndForth(ticksDuration, maxDegrees, ticksBetweenSwing);

	//rotate in a spiral
	//getMapManager()->rotateInSpiral(ticksDuration, maxDegrees, ticksBetweenSwing);
}

void CinematicsManager::setHBlankWave(bool b)
{ //=========================================================================================================================
	//do this with an FBO
}

void CinematicsManager::setMosaic(bool b)
{ //=========================================================================================================================

	//getMapManager()->mosaicEffect(ticksDuration, maxMosaicSize);

	//TODO: make event for this
}

void CinematicsManager::setBlur(bool b)
{ //=========================================================================================================================

	//getMapManager()->blurEffect(ticksDuration,maxBlurStrength);

	//TODO: make event for this

	//blur on/off
	//blur DURATION
}

void CinematicsManager::openEyes(int ticksDuration)
{ //=========================================================================================================================
	//blur and letterbox

	//TODO: make event for this
}

void CinematicsManager::closeEyes(int ticksDuration)
{ //=========================================================================================================================
	//blur and letterbox

	//TODO: make event for this
}

void CinematicsManager::shakeScreenForTicksDurationEaseInAndOutToMaxAmountWithEasingBetweenShakes(int ticksDuration, int maxX, int maxY, int ticksPerShake)
{ //=========================================================================================================================
	getCameraman()->setShakeScreen(ticksDuration, maxX, maxY, ticksPerShake);
}

void CinematicsManager::shakeScreenForTicksDurationConstantRateEasingBetweenShakes(bool onOff, int maxX, int maxY, int ticksPerShake)
{ //=========================================================================================================================
	//getCameraman()->setShakeScreen(ticksDuration,maxX,maxY,ticksPerShake);

	//TODO: make event for this
}

void CinematicsManager::shakeScreenOnOffConstantRateEasingBetweenShakesMustTurnOff(bool onOff, int maxX, int maxY, int ticksPerShake)
{ //=========================================================================================================================
	//getCameraman()->setShakeScreen(ticksDuration,maxX,maxY,ticksPerShake);

	//TODO: make event for this
}

void CinematicsManager::setGameSpeed(float multiplier)
{ //=========================================================================================================================

	//TODO: make event for this
}

