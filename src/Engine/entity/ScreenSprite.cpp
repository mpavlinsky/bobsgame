#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger ScreenSprite::log = Logger("ScreenSprite");


ScreenSprite::ScreenSprite(Engine* g, const string& name, const string& spriteName)
{ //=========================================================================================================================

	this->e = g;

	initEntity(new EntityData(-1, name, spriteName, 0, 0));

	setRenderOrder(RenderOrder::OVER_TEXT);

	getSpriteManager()->screenSpriteList.add(this);
}

float ScreenSprite::getScreenLeft()
{ //=========================================================================================================================

	if (centerX)
	{
		return getEngine()->getWidth() / 2 - getWidth() / 2;
	}

	if (useXPercent)
	{
		return (float)((getEngine()->getWidth() * screenXPercent));
	}

	return screenXPixelsHQ;
}

float ScreenSprite::getScreenTop()
{ //=========================================================================================================================
	if (centerY)
	{
		return getEngine()->getHeight() / 2 - getWidth() / 2;
	}

	if (useYPercent)
	{
		return (float)((getEngine()->getHeight() * screenYPercent));
	}

	return screenYPixelsHQ;
}

void ScreenSprite::setX(float x)
{
	useXPercent = false;
	screenXPixelsHQ = x;
}

void ScreenSprite::setY(float y)
{
	useYPercent = false;
	screenYPixelsHQ = y;
}

void ScreenSprite::setXPercent(float x)
{
	useXPercent = true;
	screenXPixelsHQ = x;
	if (x == -1)
	{
		centerX = true;
	}
}

void ScreenSprite::setYPercent(float y)
{
	useYPercent = true;
	screenYPixelsHQ = y;
	if (y == -1)
	{
		centerY = true;
	}
}

void ScreenSprite::checkIfOnscreen()
{ //=========================================================================================================================
	//don't do anything, manually control draw
}

bool ScreenSprite::shouldDraw()
{ //=========================================================================================================================
	//checkIfOnscreen();

	if (draw == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ScreenSprite::deleteFromMapEntityListAndReleaseTexture()
{ //=========================================================================================================================
	if (getSpriteManager()->screenSpriteList.contains(this))
	{
		getSpriteManager()->screenSpriteList.remove(this);
	}
}

void ScreenSprite::render(float alpha, BobTexture* texture, BobTexture* shadowTexture)
{ //=========================================================================================================================


	float tx0 = 0.0f;
	float tx1 = 1.0f;
	float ty0 = 0.0f;
	float ty1 = 1.0f;

	float x0 = 0;
	float x1 = 0;
	float y0 = 0;
	float y1 = 0;


	//------------------
	//now draw actual sprite
	//------------------
	if (texture != nullptr)
	{
		tx0 = 0.0f;
		tx1 = ((float)(getWidth()) / (float)(texture->getTextureWidth()));
		ty0 = (((float)(getHeight())) * getFrame()) / (float)(texture->getTextureHeight());
		ty1 = (((float)(getHeight())) * (getFrame() + 1)) / (float)(texture->getTextureHeight());


		//x0 = (float)Math.floor(getScreenLeft());
		//x1 = (float)Math.floor(screenRight());
		//y0 = (float)Math.floor(getScreenTop());
		//y1 = (float)Math.floor(screenBottom());


		x0 = getScreenLeft();
		y0 = getScreenTop();
		x1 = (float)(x0 + getWidth());
		y1 = (float)(y0 + getHeight());


		GLUtils::drawTexture(texture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, alpha, GLUtils::FILTER_NEAREST);
	}
}

