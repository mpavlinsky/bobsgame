#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger AreaData::log = Logger("AreaData");


AreaData::AreaData()
{ //=========================================================================================================================
}

AreaData::AreaData
(
	int id,
	const string& name,
	int mapXPixels1X,
	int mapYPixels1X,
	int widthPixels1X,
	int heightPixels1X,
	const string& destinationTYPEID,
	int arrivalXPixels1X,
	int arrivalYPixels1X,
	bool randomPointOfInterestOrExit,
	bool randomNPCSpawnPoint,
	int standSpawnDirection,
	int waitHereTicks,
	bool randomWaitTime,
	bool onlyOneAllowed,
	bool randomNPCStayHere,
	float randomSpawnChance,
	bool randomSpawnOnlyTryOnce,
	bool randomSpawnOnlyOffscreen,
	int randomSpawnDelay,
	bool randomSpawnKids,
	bool randomSpawnAdults,
	bool randomSpawnMales,
	bool randomSpawnFemales,
	bool randomSpawnCars,
	bool autoPilot,
	bool playerFaceDirection,
	bool suckPlayerIntoMiddle,
	int eventID,
	const string& comment
)
{ //=========================================================================================================================

	AssetData(id, name);
	this->mapXPixels1X = mapXPixels1X;
	this->mapYPixels1X = mapYPixels1X;
	this->widthPixels1X = widthPixels1X;
	this->heightPixels1X = heightPixels1X;
	this->randomPointOfInterestOrExit = randomPointOfInterestOrExit;
	this->randomNPCSpawnPoint = randomNPCSpawnPoint;
	this->standSpawnDirection = standSpawnDirection;
	this->waitHereTicks = waitHereTicks;
	this->randomWaitTime = randomWaitTime;
	this->onlyOneAllowed = onlyOneAllowed;
	this->randomNPCStayHere = randomNPCStayHere;
	this->randomSpawnChance = randomSpawnChance;
	this->randomSpawnOnlyTryOnce = randomSpawnOnlyTryOnce;
	this->randomSpawnOnlyOffscreen = randomSpawnOnlyOffscreen;
	this->randomSpawnDelay = randomSpawnDelay;
	this->randomSpawnKids = randomSpawnKids;
	this->randomSpawnAdults = randomSpawnAdults;
	this->randomSpawnMales = randomSpawnMales;
	this->randomSpawnFemales = randomSpawnFemales;
	this->randomSpawnCars = randomSpawnCars;
	this->autoPilot = autoPilot;
	this->playerFaceDirection = playerFaceDirection;
	this->suckPlayerIntoMiddle = suckPlayerIntoMiddle;
	this->eventID = eventID;


	this->destinationTYPEID = destinationTYPEID;
	this->arrivalXPixels1X = arrivalXPixels1X;
	this->arrivalYPixels1X = arrivalYPixels1X;
	isWarpArea = true;
}

AreaData::AreaData(int id, const string& name)
{ //=========================================================================================================================
	AssetData(id, name);
}

AreaData::AreaData
(
	int id,
	const string& name,
	int mapXPixels1X,
	int mapYPixels1X,
	int widthPixels1X,
	int heightPixels1X,
	bool randomPointOfInterestOrExit,
	bool randomNPCSpawnPoint,
	int standSpawnDirection,
	int waitHereTicks,
	bool randomWaitTime,
	bool onlyOneAllowed,
	bool randomNPCStayHere,
	float randomSpawnChance,
	bool randomSpawnOnlyTryOnce,
	bool randomSpawnOnlyOffscreen,
	int randomSpawnDelay,
	bool randomSpawnKids,
	bool randomSpawnAdults,
	bool randomSpawnMales,
	bool randomSpawnFemales,
	bool randomSpawnCars,
	bool autoPilot,
	bool playerFaceDirection,
	bool suckPlayerIntoMiddle,
	int eventID,
	const string& comment
)
{ //=========================================================================================================================


	AssetData(id, name);


	this->mapXPixels1X = mapXPixels1X;
	this->mapYPixels1X = mapYPixels1X;
	this->widthPixels1X = widthPixels1X;
	this->heightPixels1X = heightPixels1X;
	this->randomPointOfInterestOrExit = randomPointOfInterestOrExit;
	this->randomNPCSpawnPoint = randomNPCSpawnPoint;
	this->standSpawnDirection = standSpawnDirection;
	this->waitHereTicks = waitHereTicks;
	this->randomWaitTime = randomWaitTime;
	this->onlyOneAllowed = onlyOneAllowed;
	this->randomNPCStayHere = randomNPCStayHere;
	this->randomSpawnChance = randomSpawnChance;
	this->randomSpawnOnlyTryOnce = randomSpawnOnlyTryOnce;
	this->randomSpawnOnlyOffscreen = randomSpawnOnlyOffscreen;
	this->randomSpawnDelay = randomSpawnDelay;
	this->randomSpawnKids = randomSpawnKids;
	this->randomSpawnAdults = randomSpawnAdults;
	this->randomSpawnMales = randomSpawnMales;
	this->randomSpawnFemales = randomSpawnFemales;
	this->randomSpawnCars = randomSpawnCars;
	this->autoPilot = autoPilot;
	this->playerFaceDirection = playerFaceDirection;
	this->suckPlayerIntoMiddle = suckPlayerIntoMiddle;
	this->eventID = eventID;
}

void AreaData::addConnectionString(const string& s)
{ //=========================================================================================================================
	connectionTYPEIDList->add(s);
}

AreaData* AreaData::fromBase64ZippedJSON(const string& b64)
{ //===============================================================================================


	string json = FileUtils::unzipBase64StringToString(b64);

	//Gson gson = new Gson();
	//AreaData data = gson.fromJson(json,AreaData.class);


	return fromJSON(json);
}

AreaData* AreaData::fromJSON(const string& json)
{ //===============================================================================================


	//Gson* gson = new Gson();
	AreaData* data = nullptr;// gson->fromJson(json, AreaData::typeid);


	return data;
}

string AreaData::getTYPEIDString()
{ //===============================================================================================

	if (isWarpArea == true)
	{
		return string("AREA.") + to_string(getID());
	}
	return string("AREA.") + to_string(getID());
}

int AreaData::getMapXPixels1X()
{
	return mapXPixels1X;
}

int AreaData::getMapYPixels1X()
{
	return mapYPixels1X;
}

float AreaData::getMapXPixelsHQ()
{
	return (float)mapXPixels1X * 2;
}

float AreaData::getMapYPixelsHQ()
{
	return (float)mapYPixels1X * 2;
}

int AreaData::getWidthPixels1X()
{
	return widthPixels1X;
}

int AreaData::getHeightPixels1X()
{
	return heightPixels1X;
}

int AreaData::getWidthPixelsHQ()
{
	return widthPixels1X * 2;
}

int AreaData::getHeightPixelsHQ()
{
	return heightPixels1X * 2;
}

int AreaData::getArrivalXPixels1X()
{
	return arrivalXPixels1X;
}

int AreaData::getArrivalYPixels1X()
{
	return arrivalYPixels1X;
}

float AreaData::getArrivalXPixelsHQ()
{
	return (float)arrivalXPixels1X * 2;
}

float AreaData::getArrivalYPixelsHQ()
{
	return (float)arrivalYPixels1X * 2;
}

bool AreaData::getIsWarpArea()
{
	return isWarpArea;
}

bool AreaData::getRandomPointOfInterestOrExit()
{
	return randomPointOfInterestOrExit;
}

bool AreaData::getRandomNPCSpawnPoint()
{
	return randomNPCSpawnPoint;
}

int AreaData::getStandSpawnDirection()
{
	return standSpawnDirection;
}

int AreaData::getWaitHereTicks()
{
	return waitHereTicks;
}

bool AreaData::getRandomWaitTime()
{
	return randomWaitTime;
}

bool AreaData::getOnlyOneAllowed()
{
	return onlyOneAllowed;
}

bool AreaData::getRandomNPCStayHere()
{
	return randomNPCStayHere;
}

float AreaData::getRandomSpawnChance()
{
	return randomSpawnChance;
}

bool AreaData::getRandomSpawnOnlyTryOnce()
{
	return randomSpawnOnlyTryOnce;
}

bool AreaData::getRandomSpawnOnlyOffscreen()
{
	return randomSpawnOnlyOffscreen;
}

int AreaData::getRandomSpawnDelay()
{
	return randomSpawnDelay;
}

bool AreaData::getRandomSpawnKids()
{
	return randomSpawnKids;
}

bool AreaData::getRandomSpawnAdults()
{
	return randomSpawnAdults;
}

bool AreaData::getRandomSpawnMales()
{
	return randomSpawnMales;
}

bool AreaData::getRandomSpawnFemales()
{
	return randomSpawnFemales;
}

bool AreaData::getRandomSpawnCars()
{
	return randomSpawnCars;
}

bool AreaData::getAutoPilot()
{
	return autoPilot;
}

bool AreaData::getPlayerFaceDirection()
{
	return playerFaceDirection;
}

bool AreaData::getSuckPlayerIntoMiddle()
{
	return suckPlayerIntoMiddle;
}

int AreaData::getEventID()
{
	return eventID;
}

ArrayList<string>* AreaData::getConnectionTYPEIDList()
{
	return connectionTYPEIDList;
}

string AreaData::getComment()
{
	return comment;
}

string AreaData::getDestinationTYPEIDString()
{
	return destinationTYPEID;
}

string AreaData::getDestinationMapName()
{
	return destinationMapName;
}

string AreaData::getDestinationWarpAreaName()
{
	return destinationWarpAreaName;
}

int AreaData::getMapID()
{
	return mapID;
}

int AreaData::getStateID()
{
	return stateID;
}

void AreaData::setDestinationMapName(const string& s)
{
	destinationMapName = s;
}

void AreaData::setDestinationWarpAreaName(const string& s)
{
	destinationWarpAreaName = s;
}

void AreaData::setDestinationTYPEIDString(const string& s)
{
	destinationTYPEID = s;
}

void AreaData::setRandomPointOfInterestOrExit(bool s)
{
	randomPointOfInterestOrExit = s;
}

void AreaData::setRandomNPCSpawnPoint(bool s)
{
	randomNPCSpawnPoint = s;
}

void AreaData::setStandSpawnDirection(int s)
{
	standSpawnDirection = s;
}

void AreaData::setWaitHereTicks(int s)
{
	waitHereTicks = s;
}

void AreaData::setRandomWaitTime(bool s)
{
	randomWaitTime = s;
}

void AreaData::setOnlyOneAllowed(bool s)
{
	onlyOneAllowed = s;
}

void AreaData::setRandomNPCStayHere(bool s)
{
	randomNPCStayHere = s;
}

void AreaData::setRandomSpawnChance(float s)
{
	randomSpawnChance = s;
}

void AreaData::setRandomSpawnOnlyTryOnce(bool s)
{
	randomSpawnOnlyTryOnce = s;
}

void AreaData::setRandomSpawnOnlyOffscreen(bool s)
{
	randomSpawnOnlyOffscreen = s;
}

void AreaData::setRandomSpawnDelay(int s)
{
	randomSpawnDelay = s;
}

void AreaData::setRandomSpawnKids(bool s)
{
	randomSpawnKids = s;
}

void AreaData::setRandomSpawnAdults(bool s)
{
	randomSpawnAdults = s;
}

void AreaData::setRandomSpawnMales(bool s)
{
	randomSpawnMales = s;
}

void AreaData::setRandomSpawnFemales(bool s)
{
	randomSpawnFemales = s;
}

void AreaData::setRandomSpawnCars(bool s)
{
	randomSpawnCars = s;
}

void AreaData::setAutoPilot(bool s)
{
	autoPilot = s;
}

void AreaData::setPlayerFaceDirection(bool s)
{
	playerFaceDirection = s;
}

void AreaData::setSuckPlayerIntoMiddle(bool s)
{
	suckPlayerIntoMiddle = s;
}

void AreaData::setIsWarpArea(bool s)
{
	isWarpArea = s;
}

void AreaData::setEventID(int s)
{
	eventID = s;
}

void AreaData::setComment(const string& s)
{
	comment = s;
}

void AreaData::setMapXPixels1X(int s)
{
	mapXPixels1X = s;
}

void AreaData::setMapYPixels1X(int s)
{
	mapYPixels1X = s;
}

void AreaData::setArrivalXPixels1X(int s)
{
	arrivalXPixels1X = s;
}

void AreaData::setArrivalYPixels1X(int s)
{
	arrivalYPixels1X = s;
}

void AreaData::setWidthPixels1X(int s)
{
	widthPixels1X = s;
}

void AreaData::setHeightPixels1X(int s)
{
	heightPixels1X = s;
}

void AreaData::setMapID(int s)
{
	mapID = s;
}

void AreaData::setStateID(int s)
{
	stateID = s;
}

