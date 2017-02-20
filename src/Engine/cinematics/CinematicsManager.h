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
class Letterbox;
class ScreenOverlay;
enum class RenderOrder;


class CinematicsManager : public EnginePart
{
public:

	static Logger log;


	Letterbox* letterbox = nullptr;
	ScreenOverlay* screenOverlayOverLights = nullptr;
	ScreenOverlay* screenOverlayUnderLights = nullptr;
	ScreenOverlay* screenOverlayGroundLayer = nullptr;


	//TODO: probably want to organize these effects in a linked list or something

	//need a way to make new effects at any time, or maybe could just have a lot of presets?


	//color overlays (screenfade with max opacity)

	//flashes (screenfade with fast speed)


	//screen shake: need to access cameraman, that's it

	//slow motion: need to modulate Game().ticksPassed() per frame, probably


	//lighting
	//shadows on edges of screen
	//do fps hdr light modulation when go indoor/outdoors

	//hdr, color saturation controls, etc

	//eyes closing and opening (+ blur, nice effect)

	//tv blip like android phone

	//mosaic, rotate, etc

	//darkness layer and torch

	//flicker

	//screen wipes


	//ntsc distortion
	//scanlines
	//crosshatch and glow simulate crt pixels

	//use nnedi3/eedi3 scaling?

	//motion blur

	//timeline, show places lived on map, show desk pictures, do metroid like getText intro, show version of game


	//blur: render to small framebuffer, render back to screen with bilinear filter
	//OR: pixel shader
	//how to do this per-layer?
	//should never blur the getText engine probably, unless it's a dizzyness thing

	//lighting effects (grayscale, sepia, filters,etc)
	//will need pixel shader or framebuffer object for these
	//research using pixel shaders, maybe that even needs framebuffer


	//rewind and fast forward


	CinematicsManager(Engine* g);

	virtual void init();


	virtual void update();


	virtual void render(RenderOrder renderOrder);


	virtual void setLetterbox(bool on, int slideDurationTicks, int size);

	virtual void setLetterbox(bool on, int slideDurationTicks, float sizePercent);


	virtual void fadeToWhite(int ticks);

	virtual void fadeFromWhite(int ticks);


	virtual void fadeToBlack(int ticks);

	virtual void fadeFromBlack(int ticks);


	//	
	//	public void fadeColorFromCurrentAlphaToOpaque(int ticks, int ri, int gi, int bi)
	//	{
	//		screenOverlay.doTransition(new Color(ri,gi,bi),-1,1.0f,ticks);
	//	}
	//	
	//	public void fadeColorFromOpaqueToTransparent(int ticks, int ri, int gi, int bi)
	//	{
	//		screenOverlay.doTransition(new Color(ri,gi,bi),1.0f,0.0f,ticks);
	//	}


	virtual void fadeColorFromCurrentAlphaToAlpha(int ticks, int ri, int gi, int bi, float toAlpha);

	virtual void fadeColorFromAlphaToAlpha(int ticks, int ri, int gi, int bi, float fromAlpha, float toAlpha);

	//	
	//	public void fadeFromTransparentToBlackOpaqueAndBackToTransparent(int ticks)
	//	{
	//		screenOverlay.doToAndFromTransition(Color.black,ticks, 1.0f);
	//	}
	//
	//	
	//	public void fadeFromTransparentToWhiteOpaqueAndBackToTransparent(int ticks)
	//	{
	//		screenOverlay.doToAndFromTransition(Color.white,ticks,1.0f);
	//	}

	//	
	//	public void fadeColorFromTransparentToOpaqueAndBack(int ticks, int ri, int gi, int bi)
	//	{
	//		screenOverlay.doToAndFromTransition(new Color(ri,gi,bi),ticks,1.0f);
	//	}

	virtual void fadeColorFromTransparentToAlphaBackToTransparent(int ticks, int ri, int gi, int bi, float toAlpha);
	//	
	//	public void fadeColorFromCurrentAlphaToAlphaBackToCurrentAlpha(int ticks, int ri, int gi, int bi, float getToAlpha)
	//	{
	//		screenOverlay.doToAndFromTransition(new Color(ri,gi,bi),ticks, getToAlpha);
	//	}

	virtual void setInstantOverlayColor(int ri, int gi, int bi, float a);


	virtual void clearOverlay();

	//TODO eventually redo overlay system to make disposable events that i can combine, i.e. flash red while fading to black, etc.


	virtual void fadeColorFromCurrentAlphaToAlphaUnderLights(int ticks, int ri, int gi, int bi, float toAlpha);


	virtual void setInstantOverlayColorUnderLights(int ri, int gi, int bi, float a);


	virtual void clearOverlayUnderLights();


	virtual void fadeColorFromCurrentAlphaToAlphaGroundLayer(int ticks, int ri, int gi, int bi, float toAlpha);


	virtual void setInstantOverlayColorGroundLayer(int ri, int gi, int bi, float a);


	virtual void clearOverlayGroundLayer();


	virtual void set8BitMode(bool b);


	virtual void setInvertedColors(bool b);


	virtual void setBlackAndWhite(bool b);


	virtual void setRotate(bool b);


	virtual void setHBlankWave(bool b);


	virtual void setMosaic(bool b);


	virtual void setBlur(bool b);


	virtual void openEyes(int ticksDuration);

	virtual void closeEyes(int ticksDuration);


	virtual void shakeScreenForTicksDurationEaseInAndOutToMaxAmountWithEasingBetweenShakes(int ticksDuration, int maxX, int maxY, int ticksPerShake);


	virtual void shakeScreenForTicksDurationConstantRateEasingBetweenShakes(bool onOff, int maxX, int maxY, int ticksPerShake);


	virtual void shakeScreenOnOffConstantRateEasingBetweenShakesMustTurnOff(bool onOff, int maxX, int maxY, int ticksPerShake);


	virtual void setGameSpeed(float multiplier);
};

