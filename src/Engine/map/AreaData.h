//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class AreaData : public AssetData
{
private:
	
	int mapXPixels1X = 0;
	
	int mapYPixels1X = 0;

	
	int widthPixels1X = 0;
	
	int heightPixels1X = 0;


	
	bool randomPointOfInterestOrExit = false;
	
	bool randomNPCSpawnPoint = false;
	
	int standSpawnDirection = -1;
	
	int waitHereTicks = 0; //see random stay here
	
	bool randomWaitTime = false;
	
	bool onlyOneAllowed = false;
	
	bool randomNPCStayHere = false; //for cars, audience//the reason there are BOTH stay here and wait here==-1 is that i might want a spawned NPC to walk away from a chair, but a new NPC come and sit down permanently. just a little more lively! :-) I don't know if i thought of this when i put them in, but i could presumably use it for that.
	
	float randomSpawnChance = 1.0f; //will distribute max randoms across spawn points based on chance.
	
	bool randomSpawnOnlyTryOnce = false; //one shot spawn chance for cars, audience
	
	bool randomSpawnOnlyOffscreen = false;
	
	int randomSpawnDelay = 1000;
	
	bool randomSpawnKids = true;
	
	bool randomSpawnAdults = true;
	
	bool randomSpawnMales = true;
	
	bool randomSpawnFemales = true;
	
	bool randomSpawnCars = false;

	//TODO: handle these
	
	bool autoPilot = false; //player will enable autopilot, show autopilot getCaption, follow connections
	
	bool playerFaceDirection = false; //for couches, chairs
	
	bool suckPlayerIntoMiddle = false; //for chairs
	
	int eventID = -1;


	
	string comment = "";


	
	int mapID = -1;
	
	int stateID = -1;


	//can pull connections from sprites to areas and doors, should add these to points of interest list inside sprite.
	//automatically connect lines from all random points to any random spawn points, when click on random spawn point, should go to other spawn points as well

	
	ArrayList<string>* connectionTYPEIDList = new ArrayList<string>(); //should ALWAYS be by ID


	//warp area specific

	string destinationTYPEID = ""; //AREA.ID


	
	int arrivalXPixels1X = -1;
	
	int arrivalYPixels1X = -1;


	
	bool isWarpArea = false;


	//ONLY USED FOR EXPORT
	
	string destinationMapName = "";
	
	string destinationWarpAreaName = "";


public:
	AreaData();


	AreaData(int id, const string& name, int mapXPixels1X, int mapYPixels1X, int widthPixels1X, int heightPixels1X, const string& destinationTYPEID, int arrivalXPixels1X, int arrivalYPixels1X, bool randomPointOfInterestOrExit, bool randomNPCSpawnPoint, int standSpawnDirection, int waitHereTicks, bool randomWaitTime, bool onlyOneAllowed, bool randomNPCStayHere, float randomSpawnChance, bool randomSpawnOnlyTryOnce, bool randomSpawnOnlyOffscreen, int randomSpawnDelay, bool randomSpawnKids, bool randomSpawnAdults, bool randomSpawnMales, bool randomSpawnFemales, bool randomSpawnCars, bool autoPilot, bool playerFaceDirection, bool suckPlayerIntoMiddle, int eventID, const string& comment);


	AreaData(int id, const string& name);


	AreaData(int id, const string& name, int mapXPixels1X, int mapYPixels1X, int widthPixels1X, int heightPixels1X, bool randomPointOfInterestOrExit, bool randomNPCSpawnPoint, int standSpawnDirection, int waitHereTicks, bool randomWaitTime, bool onlyOneAllowed, bool randomNPCStayHere, float randomSpawnChance, bool randomSpawnOnlyTryOnce, bool randomSpawnOnlyOffscreen, int randomSpawnDelay, bool randomSpawnKids, bool randomSpawnAdults, bool randomSpawnMales, bool randomSpawnFemales, bool randomSpawnCars, bool autoPilot, bool playerFaceDirection, bool suckPlayerIntoMiddle, int eventID, const string& comment);


	virtual void addConnectionString(const string& s);


	static AreaData* fromBase64ZippedJSON(const string& b64);


	static AreaData* fromJSON(const string& json);


	virtual string getTYPEIDString();


	virtual int getMapXPixels1X();
	virtual int getMapYPixels1X();
	virtual float getMapXPixelsHQ();
	virtual float getMapYPixelsHQ();
	virtual int getWidthPixels1X();
	virtual int getHeightPixels1X();
	virtual int getWidthPixelsHQ();
	virtual int getHeightPixelsHQ();
	virtual int getArrivalXPixels1X();
	virtual int getArrivalYPixels1X();
	virtual float getArrivalXPixelsHQ();
	virtual float getArrivalYPixelsHQ();

	virtual bool getIsWarpArea();
	virtual bool getRandomPointOfInterestOrExit();
	virtual bool getRandomNPCSpawnPoint();
	virtual int getStandSpawnDirection();
	virtual int getWaitHereTicks();
	virtual bool getRandomWaitTime();
	virtual bool getOnlyOneAllowed();
	virtual bool getRandomNPCStayHere();
	virtual float getRandomSpawnChance();
	virtual bool getRandomSpawnOnlyTryOnce();
	virtual bool getRandomSpawnOnlyOffscreen();
	virtual int getRandomSpawnDelay();
	virtual bool getRandomSpawnKids();
	virtual bool getRandomSpawnAdults();
	virtual bool getRandomSpawnMales();
	virtual bool getRandomSpawnFemales();
	virtual bool getRandomSpawnCars();
	virtual bool getAutoPilot();
	virtual bool getPlayerFaceDirection();
	virtual bool getSuckPlayerIntoMiddle();
	virtual int getEventID();
	//public String stateName(){return data.stateName;}
	virtual ArrayList<string>* getConnectionTYPEIDList();
	virtual string getComment();
	virtual string getDestinationTYPEIDString();
	virtual string getDestinationMapName();
	virtual string getDestinationWarpAreaName();
	virtual int getMapID();
	virtual int getStateID();


	virtual void setDestinationMapName(const string& s);
	virtual void setDestinationWarpAreaName(const string& s);
	virtual void setDestinationTYPEIDString(const string& s);
	virtual void setRandomPointOfInterestOrExit(bool s);
	virtual void setRandomNPCSpawnPoint(bool s);
	virtual void setStandSpawnDirection(int s);
	virtual void setWaitHereTicks(int s);
	virtual void setRandomWaitTime(bool s);
	virtual void setOnlyOneAllowed(bool s);
	virtual void setRandomNPCStayHere(bool s);
	virtual void setRandomSpawnChance(float s);
	virtual void setRandomSpawnOnlyTryOnce(bool s);
	virtual void setRandomSpawnOnlyOffscreen(bool s);
	virtual void setRandomSpawnDelay(int s);
	virtual void setRandomSpawnKids(bool s);
	virtual void setRandomSpawnAdults(bool s);
	virtual void setRandomSpawnMales(bool s);
	virtual void setRandomSpawnFemales(bool s);
	virtual void setRandomSpawnCars(bool s);
	virtual void setAutoPilot(bool s);
	virtual void setPlayerFaceDirection(bool s);
	virtual void setSuckPlayerIntoMiddle(bool s);
	virtual void setIsWarpArea(bool s);
	virtual void setEventID(int s);
	virtual void setComment(const string& s);
	virtual void setMapXPixels1X(int s);
	virtual void setMapYPixels1X(int s);
	virtual void setArrivalXPixels1X(int s);
	virtual void setArrivalYPixels1X(int s);
	virtual void setWidthPixels1X(int s);
	virtual void setHeightPixels1X(int s);
	virtual void setMapID(int s);
	virtual void setStateID(int s);
};

