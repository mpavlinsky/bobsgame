#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger EntityData::log = Logger("EntityData");

//=========================================================================================================================
EntityData::EntityData()
{ //=========================================================================================================================
}
//=========================================================================================================================
EntityData::EntityData(int id, const string& name, const string& spriteAssetName, int spawnXPixels1X, int spawnYPixels1X, int initialFrame, bool pushable, bool nonWalkable, int alphaByte, float scale, int ticksPerPixelMoved, bool aboveTopLayer, bool aboveWhenEqual, bool alwaysOnBottom, bool animateThroughFrames, bool randomTimeBetweenAnimation, int ticksBetweenFrames, int ticksBetweenAnimation, bool onlyHereDuringEvent, bool randomFrames, bool disableShadow, int eventID, const string& comment)
{ //=========================================================================================================================


	initEntityData(id, name, spriteAssetName, spawnXPixels1X, spawnYPixels1X, initialFrame, pushable, nonWalkable, alphaByte, scale, ticksPerPixelMoved, aboveTopLayer, aboveWhenEqual, alwaysOnBottom, animateThroughFrames, randomTimeBetweenAnimation, ticksBetweenFrames, ticksBetweenAnimation, onlyHereDuringEvent, randomFrames, disableShadow, eventID, comment);
}


//=========================================================================================================================
void EntityData::initEntityData(int id, const string& name, const string& spriteAssetName, int spawnXPixels1X, int spawnYPixels1X, int initialFrame, bool pushable, bool nonWalkable, int alphaByte, float scale, int ticksPerPixelMoved, bool aboveTopLayer, bool aboveWhenEqual, bool alwaysOnBottom, bool animateThroughFrames, bool randomTimeBetweenAnimation, int ticksBetweenFrames, int ticksBetweenAnimation, bool onlyHereDuringEvent, bool randomFrames, bool disableShadow, int eventID, const string& comment)
{//=========================================================================================================================
	this->id = id;
	this->name = name;

	this->spriteName = spriteAssetName;


	this->spawnXPixels1X = (float)spawnXPixels1X;
	this->spawnYPixels1X = (float)spawnYPixels1X;


	this->initialFrame = initialFrame;

	this->pushable = pushable;
	this->nonWalkable = nonWalkable;

	this->toAlpha = ((float)(alphaByte) / 255.0f); //NOTICE, USING getToAlpha NOT alpha, alpha is wrong!


	this->scale = (float)(scale);

	this->ticksPerPixelMoved = (float)ticksPerPixelMoved;

	this->disableShadow = disableShadow;

	if (aboveTopLayer)
	{
		this->renderOrder = RenderOrder::ABOVE_TOP;
	}
	this->aboveTopLayer = aboveTopLayer; //dont use this in client, client only uses layer

	this->aboveWhenEqual = aboveWhenEqual;
	this->alwaysOnBottom = alwaysOnBottom;


	this->animateThroughFrames = animateThroughFrames;
	this->randomFrames = randomFrames;
	this->randomTimeBetweenAnimation = randomTimeBetweenAnimation;
	this->ticksBetweenFrames = ticksBetweenFrames;
	this->ticksBetweenAnimation = ticksBetweenAnimation;


	this->eventID = eventID;
	this->onlyHereDuringEvent = onlyHereDuringEvent;

	this->comment = comment;
}

//=========================================================================================================================
EntityData* EntityData::fromBase64ZippedJSON(const string& b64)
{ //===============================================================================================

	// string decode64 = FileUtils::decodeBase64String(b64);
	string json = "";// FileUtils::unzipBase64StringToString(decode64);


	return fromJSON(json);
}

EntityData* EntityData::fromJSON(const string& json)
{ //===============================================================================================


	//Gson* gson = new Gson();
	EntityData* data = nullptr;// = gson->fromJson(json, EntityData::typeid);

	return data;
}

string EntityData::getTYPEIDString()
{ //===============================================================================================
	return string("ENTITY.") + to_string(getID());
}

float EntityData::getSpawnXPixels1X()
{
	return spawnXPixels1X;
}

float EntityData::getSpawnYPixels1X()
{
	return spawnYPixels1X;
}

float EntityData::getSpawnXPixelsHQ()
{
	return spawnXPixels1X * 2;
}

float EntityData::getSpawnYPixelsHQ()
{
	return spawnYPixels1X * 2;
}

string EntityData::getSpriteName()
{
	return spriteName;
}

string EntityData::getComment()
{
	return comment;
}

int EntityData::getInitialFrame()
{
	return initialFrame;
}

bool EntityData::getPushable()
{
	return pushable;
}

bool EntityData::getNonWalkable()
{
	return nonWalkable;
}

float EntityData::getToAlpha()
{
	return toAlpha;
}

float EntityData::getScale()
{
	return scale;
}

bool EntityData::getDisableShadow()
{
	return disableShadow;
}

int EntityData::getLayer()
{
	return layer;
}

RenderOrder EntityData::getRenderOrder()
{
	return renderOrder;
}

bool EntityData::getAboveWhenEqual()
{
	return aboveWhenEqual;
}

bool EntityData::getAboveTopLayer()
{
	return aboveTopLayer;
}

bool EntityData::getAlwaysOnBottom()
{
	return alwaysOnBottom;
}

bool EntityData::getAlwaysOnTop()
{
	return alwaysOnTop;
}

bool EntityData::getIsNPC()
{
	return isNPC;
}

bool EntityData::getAnimatingThroughAllFrames()
{
	return animateThroughFrames;
}

bool EntityData::getAnimatingThroughCurrentAnimation()
{
	return animateThroughCurrentAnimation;
}

bool EntityData::getLoopAnimation()
{
	return loopAnimation;
}

bool EntityData::getRandomFrames()
{
	return randomFrames;
}

bool EntityData::getRandomUpToTicksBetweenAnimationLoop()
{
	return randomTimeBetweenAnimation;
}

int EntityData::getTicksBetweenFrames()
{
	return ticksBetweenFrames;
}

bool EntityData::getRandomUpToTicksBetweenFrames()
{
	return randomUpToTicksBetweenFrames;
}

int EntityData::getTicksBetweenAnimationLoop()
{
	return ticksBetweenAnimation;
}

float EntityData::getTicksPerPixelMoved()
{
	return ticksPerPixelMoved;
}

bool EntityData::getOnlyHereDuringEvent()
{
	return onlyHereDuringEvent;
}

float EntityData::getVoicePitch()
{
	return voicePitch;
}

bool EntityData::getMovementAnimationDisabled()
{
	return animationDisabled;
}

bool EntityData::getHitLayerDisabled()
{
	return hitLayerDisabled;
}

bool EntityData::getIgnoreHitPlayer()
{
	return ignoreHitPlayer;
}

bool EntityData::getIgnoreHitEntities()
{
	return ignoreHitEntities;
}

bool EntityData::getDontUsePathfinding()
{
	return dontUsePathfinding;
}

bool EntityData::getPullPlayer()
{
	return pullPlayer;
}

bool EntityData::getPushPlayer()
{
	return pushPlayer;
}

int EntityData::getEventID()
{
	return eventID;
}

int EntityData::getMapID()
{
	return mapID;
}

int EntityData::getStateID()
{
	return stateID;
}

ArrayList<string>* EntityData::getConnectionTYPEIDList()
{
	return connectionTYPEIDList;
}

ArrayList<string>* EntityData::getBehaviorList()
{
	return behaviorList;
}

void EntityData::setSpriteName(const string& s)
{
	spriteName = s;
}

void EntityData::setInitialFrame(int s)
{
	initialFrame = s;
}

void EntityData::setPushable(bool s)
{
	pushable = s;
}

void EntityData::setNonWalkable(bool s)
{
	nonWalkable = s;
}

void EntityData::setToAlpha(float s)
{
	if (s > 1.0f)
	{
		s = 1.0f;
	}
	if (s < 0.0f)
	{
		s = 0.0f;
	}
	toAlpha = s;
}

void EntityData::setScale(float s)
{
	scale = s;
}

void EntityData::setDisableShadow(bool s)
{
	disableShadow = s;
}

void EntityData::setRenderOrder(RenderOrder s)
{
	renderOrder = s;
}

void EntityData::setAboveTopLayer(bool s)
{
	aboveTopLayer = s;
}

void EntityData::setAboveWhenEqual(bool s)
{
	aboveWhenEqual = s;
}

void EntityData::setAlwaysOnBottom(bool s)
{
	alwaysOnBottom = s;
}

void EntityData::setAlwaysOnTop(bool s)
{
	alwaysOnTop = s;
}

void EntityData::setIsNPC(bool s)
{
	isNPC = s;
}

void EntityData::setOnlyHereDuringEvent(bool s)
{
	onlyHereDuringEvent = s;
}

void EntityData::setVoicePitch(float s)
{
	voicePitch = s;
}

void EntityData::setAnimationDisabled(bool s)
{
	animationDisabled = s;
}

void EntityData::setHitLayerDisabled(bool s)
{
	hitLayerDisabled = s;
}

void EntityData::setIgnoreHitPlayer(bool s)
{
	ignoreHitPlayer = s;
}

void EntityData::setIgnoreHitEntities(bool s)
{
	ignoreHitEntities = s;
}

void EntityData::setDontUsePathfinding(bool s)
{
	dontUsePathfinding = s;
}

void EntityData::setRandomFrames(bool s)
{
	randomFrames = s;
}

void EntityData::setRandomUpToTicksBetweenAnimationLoop(bool s)
{
	randomTimeBetweenAnimation = s;
}

void EntityData::setTicksBetweenFrames(int s)
{
	ticksBetweenFrames = s;
}

void EntityData::setRandomUpToTicksBetweenFrames(bool s)
{
	randomUpToTicksBetweenFrames = s;
}

void EntityData::setTicksBetweenAnimationLoop(int s)
{
	ticksBetweenAnimation = s;
}

void EntityData::setTicksPerPixelMoved(float s)
{
	ticksPerPixelMoved = s;
}

void EntityData::setSpawnXPixels1X(float s)
{
	spawnXPixels1X = s;
}

void EntityData::setSpawnYPixels1X(float s)
{
	spawnYPixels1X = s;
}

void EntityData::setMapID(int s)
{
	mapID = s;
}

void EntityData::setStateID(int s)
{
	stateID = s;
}

void EntityData::setEventID(int s)
{
	eventID = s;
}

void EntityData::setComment(const string& s)
{
	comment = s;
}

void EntityData::setAnimateThroughAllFrames(bool s)
{
	animateThroughFrames = s;
	if (s == true)
	{
		animateThroughCurrentAnimation = false;
	}
}

void EntityData::setAnimateThroughCurrentAnimation(bool s)
{
	animateThroughCurrentAnimation = s;
	if (s == true)
	{
		animateThroughFrames = false;
	}
}

void EntityData::setLoopAnimation(bool s)
{
	loopAnimation = s;
}

