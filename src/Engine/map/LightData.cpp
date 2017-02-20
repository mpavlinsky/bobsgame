#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger LightData::log = Logger("LightData");


LightData::LightData()
{ //=========================================================================================================================
}

LightData::LightData(int id, const string& mapName, const string& stateName, const string& name, int spawnXPixels1X, int spawnYPixels1X, int widthPixels1X, int heightPixels1X, int redColorByte, int greenColorByte, int blueColorByte, int alphaColorByte, int radiusPixels1X, float blendFalloff, float decayExponent, int focusRadius1X, bool isDayLight, bool isNightLight, bool flickers, bool changesColor, bool toggleable, int toggleXPixels1X, int toggleYPixels1X, int flickerOnTicks, int flickerOffTicks, bool flickerRandomUpToOnTicks, bool flickerRandomUpToOffTicks)
{ //=========================================================================================================================


	initEntityData(id, name, "", spawnXPixels1X, spawnYPixels1X, 0, false, false, 255, 1.0f, 12, false, false, false, false, false, 0, 0, false, false, true, -1, ""); //spriteAssetName


	this->widthPixels1X = widthPixels1X;
	this->heightPixels1X = heightPixels1X;

	this->redColorByte = redColorByte;
	this->greenColorByte = greenColorByte;
	this->blueColorByte = blueColorByte;
	this->alphaColorByte = alphaColorByte;

	this->radiusPixels1X = radiusPixels1X;
	this->blendFalloff = blendFalloff;
	this->decayExponent = decayExponent;
	this->focusRadius1X = focusRadius1X;
	this->isDayLight = isDayLight;
	this->isNightLight = isNightLight;


	this->flickers = flickers;
	this->changesColor = changesColor;
	this->toggleable = toggleable;
	this->toggleXPixels1X = toggleXPixels1X;
	this->toggleYPixels1X = toggleYPixels1X;
	this->flickerOnTicks = flickerOnTicks;
	this->flickerOffTicks = flickerOffTicks;
	this->flickerRandomUpToOnTicks = flickerRandomUpToOnTicks;
	this->flickerRandomUpToOffTicks = flickerRandomUpToOffTicks;
}

LightData::LightData(int id, const string& name)
{ //=========================================================================================================================
	EntityData(id, name, "", 0, 0, 0, false, true, 255, 1.0f, 12, false, false, false, false, false, 0, 0, false, false, true, -1, ""); //int eventID, - boolean getDisableShadow, - boolean getRandomFrames, - boolean getOnlyHereDuringEvent, - int ticksBetweenAnimation, - int getTicksBetweenFrames, - boolean randomTimeBetweenAnimation, - boolean animateThroughFrames, - boolean getAlwaysOnBottom, - boolean getAboveWhenEqual, - boolean getAboveTopLayer, - float getScale, - int alphaByte, - boolean getNonWalkable, - boolean getPushable, - int getInitialFrame, - int getSpawnYPixels1X, - int getSpawnXPixels1X, - String spriteAssetName, - String name, - int id,
}

LightData* LightData::fromBase64ZippedJSON(const string& b64)
{ //===============================================================================================



	string json = FileUtils::unzipBase64StringToString(b64);

	//Gson gson = new Gson();
	//LightData data = gson.fromJson(json,LightData.class);


	return fromJSON(json);
}

LightData* LightData::fromJSON(const string& json)
{ //===============================================================================================


	//Gson* gson = new Gson();
	LightData* data = nullptr;// gson->fromJson(json, LightData::typeid);


	return data;
}

string LightData::getTYPEIDString()
{ //===============================================================================================
	return string("LIGHT.") + to_string(getID());
}

int LightData::getWidthPixels1X()
{
	return widthPixels1X;
}

int LightData::getHeightPixels1X()
{
	return heightPixels1X;
}

int LightData::getWidthPixelsHQ()
{
	return widthPixels1X * 2;
}

int LightData::getHeightPixelsHQ()
{
	return heightPixels1X * 2;
}

int LightData::getRadiusPixels1X()
{
	return radiusPixels1X;
}

int LightData::getRadiusPixelsHQ()
{
	return radiusPixels1X * 2;
}

int LightData::getFocusRadiusPixels1X()
{
	return focusRadius1X;
}

int LightData::getFocusRadiusPixelsHQ()
{
	return focusRadius1X * 2;
}

int LightData::getToggleXPixels1X()
{
	return toggleXPixels1X;
}

int LightData::getToggleYPixels1X()
{
	return toggleYPixels1X;
}

int LightData::getToggleXPixelsHQ()
{
	return toggleXPixels1X * 2;
}

int LightData::getToggleYPixelsHQ()
{
	return toggleYPixels1X * 2;
}

int LightData::getRedColorByte()
{
	return redColorByte;
}

int LightData::getGreenColorByte()
{
	return greenColorByte;
}

int LightData::getBlueColorByte()
{
	return blueColorByte;
}

int LightData::getAlphaColorByte()
{
	return alphaColorByte;
}

int LightData::r()
{
	return redColorByte;
}

int LightData::g()
{
	return greenColorByte;
}

int LightData::b()
{
	return blueColorByte;
}

int LightData::a()
{
	return alphaColorByte;
}

float LightData::getBlendFalloff()
{
	return blendFalloff;
}

float LightData::getDecayExponent()
{
	return decayExponent;
}

bool LightData::getIsDayLight()
{
	return isDayLight;
}

bool LightData::getIsNightLight()
{
	return isNightLight;
}

bool LightData::getFlickers()
{
	return flickers;
}

bool LightData::getChangesColor()
{
	return changesColor;
}

bool LightData::getToggleable()
{
	return toggleable;
}

int LightData::getFlickerOnTicks()
{
	return flickerOnTicks;
}

int LightData::getFlickerOffTicks()
{
	return flickerOffTicks;
}

bool LightData::getFlickerRandomUpToOnTicks()
{
	return flickerRandomUpToOnTicks;
}

bool LightData::getFlickerRandomUpToOffTicks()
{
	return flickerRandomUpToOffTicks;
}

void LightData::setWidthPixels1X(int s)
{
	widthPixels1X = s;
}

void LightData::setHeightPixels1X(int s)
{
	heightPixels1X = s;
}

void LightData::setRadiusPixels1X(int s)
{
	radiusPixels1X = s;
}

void LightData::setFocusRadiusPixels1X(int s)
{
	focusRadius1X = s;
}

void LightData::setToggleXPixels1X(int s)
{
	toggleXPixels1X = s;
}

void LightData::setToggleYPixels1X(int s)
{
	toggleYPixels1X = s;
}

void LightData::setRedColorByte(int s)
{
	redColorByte = s;
}

void LightData::setGreenColorByte(int s)
{
	greenColorByte = s;
}

void LightData::setBlueColorByte(int s)
{
	blueColorByte = s;
}

void LightData::setAlphaColorByte(int s)
{
	alphaColorByte = s;
}

void LightData::setBlendFalloff(float s)
{
	blendFalloff = s;
}

void LightData::setDecayExponent(float s)
{
	decayExponent = s;
}

void LightData::setIsDayLight(bool s)
{
	isDayLight = s;
}

void LightData::setIsNightLight(bool s)
{
	isNightLight = s;
}

void LightData::setFlickers(bool s)
{
	flickers = s;
}

void LightData::setChangesColor(bool s)
{
	changesColor = s;
}

void LightData::setToggleable(bool s)
{
	toggleable = s;
}

void LightData::setFlickerOnTicks(int s)
{
	flickerOnTicks = s;
}

void LightData::setFlickerOffTicks(int s)
{
	flickerOffTicks = s;
}

void LightData::setFlickerRandomUpToOnTicks(bool s)
{
	flickerRandomUpToOnTicks = s;
}

void LightData::setFlickerRandomUpToOffTicks(bool s)
{
	flickerRandomUpToOffTicks = s;
}

