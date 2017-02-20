//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "../../Engine/map/EntityData.h"


class DoorData : public EntityData
{
private:
	string destinationTYPEID = "";


	
	int arrivalXPixels1X = -1;
	
	int arrivalYPixels1X = -1;

	
	bool randomNPCSpawnPoint = false;
	
	float randomSpawnChance = 1.0f; //will distribute max randoms across spawn points based on chance.
	
	bool randomPointOfInterestOrExit = false;
	
	int randomSpawnDelay = 1000;
	
	bool randomSpawnKids = true;
	
	bool randomSpawnAdults = true;
	
	bool randomSpawnMales = true;
	
	bool randomSpawnFemales = true;


	//ONLY USED FOR EXPORT
	
	string destinationMapName = "";
	
	string destinationDoorName = "";


public:
	DoorData();


	DoorData(int id, const string& name, const string& spriteAssetName, int spawnXPixels1X, int spawnYPixels1X, const string& destinationTYPEID, int arrivalXPixels, int arrivalYPixels, bool randomNPCSpawnPoint, float randomSpawnChance, bool randomExitPoint, int randomSpawnDelay, bool randomSpawnKids, bool randomSpawnAdults, bool randomSpawnMales, bool randomSpawnFemales, int eventID, const string& comment);


	DoorData(int id, const string& name);


	static DoorData* fromBase64ZippedJSON(const string& b64);


	static DoorData* fromJSON(const string& json);


	virtual string getTYPEIDString();


	virtual string getDestinationTYPEIDString();
	virtual string getDestinationMapName();
	virtual string getDestinationDoorName();

	virtual int getArrivalXPixels1X();
	virtual int getArrivalYPixels1X();
	virtual float getArrivalXPixelsHQ();
	virtual float getArrivalYPixelsHQ();

	virtual bool getRandomNPCSpawnPoint();
	virtual float getRandomSpawnChance();
	virtual bool getRandomPointOfInterestOrExit();
	virtual int getRandomSpawnDelay();
	virtual bool getRandomSpawnKids();
	virtual bool getRandomSpawnAdults();
	virtual bool getRandomSpawnMales();
	virtual bool getRandomSpawnFemales();


	virtual void setDestinationTYPEIDString(const string& s);
	virtual void setDestinationMapName(const string& s);
	virtual void setDestinationDoorName(const string& s);

	virtual void setRandomPointOfInterestOrExit(bool s);
	virtual void setRandomNPCSpawnPoint(bool s);
	virtual void setRandomSpawnChance(float s);
	virtual void setRandomSpawnDelay(int s);
	virtual void setRandomSpawnKids(bool s);
	virtual void setRandomSpawnAdults(bool s);
	virtual void setRandomSpawnMales(bool s);
	virtual void setRandomSpawnFemales(bool s);


	virtual void setArrivalXPixels1X(int s);
	virtual void setArrivalYPixels1X(int s);
};

