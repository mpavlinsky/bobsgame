#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once



//Logger SpriteData::log = Logger("SpriteData");


SpriteData::SpriteData
(
	int id,
	const string& name,
	const string& displayName,
	int widthPixels1X,
	int heightPixels1X,
	int frames,
	bool isNPC,// = false, 
	bool isKid,// = false, 
	bool isAdult,// = false, 
	bool isMale,// = false, 
	bool isFemale,// = false, 
	bool isCar,// = false, 
	bool isAnimal,// = false, 
	bool hasShadow,// = false, 
	bool isRandom,// = false, 
	bool isDoor,// = false, 
	bool isGame,// = false, 
	bool isItem,// = false, 
	bool forceHQ2X,// = false, 
	bool forceClientMD5Export,// = false, 
	int eventID,// = -1, 
	const string& itemGameDescription,// = "",
	float gamePrice,// = 0, 
	int utilityOffsetXPixels1X,// = 0, 
	int utilityOffsetYPixels1X,// = 0, 
	const string& dataMD5,// = "",
	const string& paletteMD5// = ""
)
{ //=========================================================================================================================


	//AssetData(id, name);
	this->id = id;
	this->name = name;


	this->displayName = displayName;

	this->widthPixels1X = widthPixels1X;
	this->heightPixels1X = heightPixels1X;


	this->frames = frames;

	this->isNPC = isNPC;

	this->isKid = isKid;
	this->isAdult = isAdult;
	this->isMale = isMale;
	this->isFemale = isFemale;
	this->isCar = isCar;
	this->isAnimal = isAnimal;

	this->hasShadow = hasShadow;
	this->isRandom = isRandom;

	this->isDoor = isDoor;
	this->isGame = isGame;
	this->isItem = isItem;

	this->forceHQ2X = forceHQ2X;
	this->forceMD5Export = forceClientMD5Export;

	this->eventID = eventID;
	this->itemGameDescription = itemGameDescription;
	this->gamePrice = gamePrice;

	this->utilityOffsetXPixels1X = utilityOffsetXPixels1X;
	this->utilityOffsetYPixels1X = utilityOffsetYPixels1X;

	this->dataMD5 = dataMD5;
	this->paletteMD5 = paletteMD5;
}


void SpriteData::addAnimation(const string& frameSequenceName, int frameStart, int hitBoxOffsetLeft1X, int hitBoxOffsetRight1X, int hitBoxOffsetTop1X, int hitBoxOffsetBottom1X)
{ //=========================================================================================================================
	animationList->add(new SpriteAnimationSequence(frameSequenceName, frameStart, hitBoxOffsetLeft1X, hitBoxOffsetRight1X, hitBoxOffsetTop1X, hitBoxOffsetBottom1X));
}

SpriteData* SpriteData::fromBase64ZippedJSON(const string& b64)
{ //===============================================================================================


	//string decode64 = FileUtils::decodeBase64String(b64);
	string json = "";// FileUtils::unzipBase64StringToString(decode64);


	return fromJSON(json);
}

SpriteData* SpriteData::fromJSON(const string& json)
{ //===============================================================================================

	//Gson* gson = new Gson();
	SpriteData* data = nullptr;// gson->fromJson(json, SpriteData::typeid);


	return data;
}

string SpriteData::getTYPEIDString()
{ //===============================================================================================
	return string("SPRITE.") + to_string(getID());
}

string SpriteData::getDisplayName()
{
	return displayName;
}

int SpriteData::getWidthPixels1X()
{
	return widthPixels1X;
}

int SpriteData::getHeightPixels1X()
{
	return heightPixels1X;
}

int SpriteData::getWidthPixelsHQ()
{
	return widthPixels1X * 2;
}

int SpriteData::getHeightPixelsHQ()
{
	return heightPixels1X * 2;
}

int SpriteData::getNumFrames()
{
	return frames;
}

bool SpriteData::getIsNPC()
{
	return isNPC;
}

bool SpriteData::getIsKid()
{
	return isKid;
}

bool SpriteData::getIsAdult()
{
	return isAdult;
}

bool SpriteData::getIsMale()
{
	return isMale;
}

bool SpriteData::getIsFemale()
{
	return isFemale;
}

bool SpriteData::getIsCar()
{
	return isCar;
}

bool SpriteData::getIsAnimal()
{
	return isAnimal;
}

bool SpriteData::getHasShadow()
{
	return hasShadow;
}

bool SpriteData::getIsRandom()
{
	return isRandom;
}

bool SpriteData::getIsDoor()
{
	return isDoor;
}

bool SpriteData::getIsGame()
{
	return isGame;
}

bool SpriteData::getIsItem()
{
	return isItem;
}

bool SpriteData::getForceHQ2X()
{
	return forceHQ2X;
}

int SpriteData::getEventID()
{
	return eventID;
}

string SpriteData::getItemGameDescription()
{
	return itemGameDescription;
}

float SpriteData::getGamePrice()
{
	return gamePrice;
}

int SpriteData::getUtilityOffsetXPixels1X()
{
	return utilityOffsetXPixels1X;
}

int SpriteData::getUtilityOffsetYPixels1X()
{
	return utilityOffsetYPixels1X;
}

int SpriteData::getUtilityOffsetXPixelsHQ()
{
	return utilityOffsetXPixels1X * 2;
}

int SpriteData::getUtilityOffsetYPixelsHQ()
{
	return utilityOffsetYPixels1X * 2;
}

string SpriteData::getDataMD5()
{
	return dataMD5;
}

string SpriteData::getPaletteMD5()
{
	return paletteMD5;
}

ArrayList<SpriteAnimationSequence*>* SpriteData::getAnimationList()
{
	return animationList;
}

string SpriteData::getComment()
{
	return comment;
}

bool SpriteData::getForceMD5Export()
{
	return forceMD5Export;
}

void SpriteData::setComment(const string& s)
{
	comment = s;
}

void SpriteData::setWidthPixels1X(int s)
{
	widthPixels1X = s;
}

void SpriteData::setHeightPixels1X(int s)
{
	heightPixels1X = s;
}

void SpriteData::setFrames(int s)
{
	frames = s;
}

void SpriteData::setDisplayName(const string& s)
{
	displayName = s;
}

void SpriteData::setIsNPC(bool s)
{
	isNPC = s;
}

void SpriteData::setIsKid(bool s)
{
	isKid = s;
}

void SpriteData::setIsAdult(bool s)
{
	isAdult = s;
}

void SpriteData::setIsMale(bool s)
{
	isMale = s;
}

void SpriteData::setIsFemale(bool s)
{
	isFemale = s;
}

void SpriteData::setIsCar(bool s)
{
	isCar = s;
}

void SpriteData::setIsAnimal(bool s)
{
	isAnimal = s;
}

void SpriteData::setHasShadow(bool s)
{
	hasShadow = s;
}

void SpriteData::setIsRandom(bool s)
{
	isRandom = s;
}

void SpriteData::setIsDoor(bool s)
{
	isDoor = s;
}

void SpriteData::setIsGame(bool s)
{
	isGame = s;
}

void SpriteData::setIsItem(bool s)
{
	isItem = s;
}

void SpriteData::setForceHQ2X(bool s)
{
	forceHQ2X = s;
}

void SpriteData::setForceMD5Export(bool s)
{
	forceMD5Export = s;
}

void SpriteData::setEventID(int s)
{
	eventID = s;
}

void SpriteData::setItemGameDescription(const string& s)
{
	itemGameDescription = s;
}

void SpriteData::setGamePrice(float s)
{
	gamePrice = s;
}

void SpriteData::setUtilityOffsetXPixels1X(int s)
{
	utilityOffsetXPixels1X = s;
}

void SpriteData::setUtilityOffsetYPixels1X(int s)
{
	utilityOffsetYPixels1X = s;
}

void SpriteData::setDataMD5(const string& s)
{
	dataMD5 = s;
}

void SpriteData::setPaletteMD5(const string& s)
{
	paletteMD5 = s;
}

