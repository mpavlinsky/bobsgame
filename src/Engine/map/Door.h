//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;

class DoorData;


class Door : public Entity
{
	//private DoorData data;

public:

	static Logger log;

	int doorknobX = 0;
	int doorknobY = 0;

private:
	bool open = false;
	bool stayOpen = false;


public:
	bool showActionIcon = true;


	Door(Engine* g, DoorData* doorAsset);


	virtual bool isOpen();

	virtual void setOpenManually(bool b);

	virtual void setOpenAnimation(bool b);

	long long lastRequestedMapDataTime = 0;

	long long ticksSinceSpawnTry = 0;


	virtual void update() override;


	bool openingButtonHeld = false;


	virtual void enter();


	virtual void renderActionIcon();


	virtual void renderDebugBoxes() override;


	virtual void renderDebugInfo() override;


	virtual EntityData* getData() override;//was return DoorData but covarient problem
	virtual DoorData* getDoorData();


	virtual float arrivalXPixelsHQ();
	virtual float arrivalYPixelsHQ();

	virtual string destinationTYPEIDString();

	virtual string destinationMapName();
	virtual string destinationDoorName();


	virtual bool randomPointOfInterestOrExit();
	virtual bool randomNPCSpawnPoint();
	virtual float randomSpawnChance();
	virtual int randomSpawnDelay();
	virtual bool randomSpawnKids();
	virtual bool randomSpawnAdults();
	virtual bool randomSpawnMales();
	virtual bool randomSpawnFemales();


	virtual void setDestinationTYPEIDString(const string& typeID);

	virtual void setRandomPointOfInterestOrExit(bool s);
	virtual void setRandomNPCSpawnPoint(bool s);
	virtual void setRandomSpawnChance(float s);
	virtual void setRandomSpawnDelay(int s);
	virtual void setRandomSpawnKids(bool s);
	virtual void setRandomSpawnAdults(bool s);
	virtual void setRandomSpawnMales(bool s);
	virtual void setRandomSpawnFemales(bool s);


	virtual void setArrivalXPixels(int s);
	virtual void setArrivalYPixels(int s);
};

