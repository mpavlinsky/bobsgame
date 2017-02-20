//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



class AreaData;


class Area : public EnginePart
{
public:

	static Logger log;


protected:
	AreaData* data = nullptr;


public:
	long long ticksSinceSpawnTry = 0;

	bool spawned = false;
	bool triedSpawn = false;


	float mapX = 0;
	float mapY = 0;

	bool showActionIcon = true;


	Area();
	Area(Engine* g);


	Area(Engine* g, AreaData* a);


	virtual Map* getMap();


	bool fadingInOut = false;
	float fadeAlpha = 0.0f;


	virtual void renderActionIcon();


	virtual void update();


	virtual void renderDebugBoxes();


	virtual void renderDebugInfo();


	/// <summary>
	/// This gets called repeatedly in events, until it returns a non-null value, at which point the event continues and does not ask again.
	/// This function will continue asking the server for the value, returning null until the server has set the response value.
	/// Upon finding a non-null response value set by the networking thread by a server response, we reset it to null and return that value, ensuring that it is always a fresh copy from the server.
	/// </summary>
	virtual BobBool* checkServerTalkedToTodayValueAndResetAfterSuccessfulReturn();

	virtual void tellServerTalkedToToday();


	virtual bool isWithinScreenBounds();


	virtual bool inRangeOfEntityByAmount(Entity* e, int amt);


	virtual float getDistanceFromEntity(Entity* e);


	virtual bool isEntityHitBoxTouchingMyBoundary(Entity* e);

	virtual bool isAreaCenterTouchingMyBoundary(Area* a);

	virtual bool isAreaBoundaryTouchingMyBoundary(Area* a);

	virtual bool isXYTouchingMyBoundary(float x, float y);

	virtual bool isXYXYTouchingMyBoundary(float left, float top, float right, float bottom);

	virtual bool isAreaBoundaryTouchingMyCenter(Area* a);

	virtual bool isEntityMiddleXYTouchingMyCenter(Entity* e);

	virtual bool isAreaCenterTouchingMyCenter(Area* a);

	virtual bool isXYTouchingMyCenter(float x, float y);

	virtual bool isXYXYTouchingMyCenter(float left, float top, float right, float bottom);

	virtual bool isEntityHitBoxTouchingMyBoundaryByAmount(Entity* e, int amt);

	virtual bool isAreaCenterTouchingMyBoundaryByAmount(Area* a, int amt);

	virtual bool isAreaBoundaryTouchingMyBoundaryByAmount(Area* a, int amt);

	virtual bool isXYTouchingMyBoundaryByAmount(float x, float y, int amt);

	virtual bool isXYXYTouchingMyBoundaryByAmount(float left, float top, float right, float bottom, int amt);

	virtual bool isAreaBoundaryTouchingMyCenterByAmount(Area* a, int amt);

	virtual bool isEntityMiddleXYTouchingMyCenterByAmount(Entity* e, int amt);

	virtual bool isAreaCenterTouchingMyCenterByAmount(Area* a, int amt);

	virtual bool isXYTouchingMyCenterByAmount(float x, float y, int amt);

	virtual bool isXYXYTouchingMyCenterByAmount(float left, float top, float right, float bottom, int amt);


	virtual float getTop();

	virtual float getLeft();

	virtual float getRight();

	virtual float getBottom();

	virtual float middleX();

	virtual float middleY();
	virtual float roundedMiddleX();

	virtual float roundedMiddleY();


private:
	float screenX();


	float screenY();


public:
	virtual float screenLeft();


	virtual float screenRight();


	virtual float screenTop();


	virtual float screenBottom();


	virtual AreaData* getData();


	virtual float getX();
	virtual float getY();

	virtual int getWidth();
	virtual int getHeight();


	virtual string getName();
	virtual string getComment();
	virtual int getID();

	virtual int mapID();


	virtual float arrivalXPixelsHQ();
	virtual float arrivalYPixelsHQ();

	virtual bool isWarpArea();
	virtual bool randomPointOfInterestOrExit();
	virtual bool randomNPCSpawnPoint();
	virtual int standSpawnDirection();
	virtual int waitHereTicks();
	virtual bool randomWaitTime();
	virtual bool onlyOneAllowed();
	virtual bool randomNPCStayHere();
	virtual float randomSpawnChance();
	virtual bool randomSpawnOnlyTryOnce();
	virtual bool randomSpawnOnlyOffscreen();
	virtual int randomSpawnDelay();
	virtual bool randomSpawnKids();
	virtual bool randomSpawnAdults();
	virtual bool randomSpawnMales();
	virtual bool randomSpawnFemales();
	virtual bool randomSpawnCars();
	virtual bool autoPilot();
	virtual bool playerFaceDirection();
	virtual bool suckPlayerIntoMiddle();
	virtual int getEventID();
	virtual ArrayList<string>* connectionTYPEIDList();

	virtual string getTYPEIDString();

	virtual string destinationTYPEIDString();
};

