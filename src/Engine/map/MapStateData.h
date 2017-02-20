//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class MapStateData : public AssetData
{
private:
	
	ArrayList<LightData*> lightDataList;

	
	ArrayList<EntityData*> entityDataList;

	//public ArrayList<EntityData> characterDataList = new ArrayList<EntityData>();

	
	ArrayList<AreaData*> areaDataList;


	
	int mapID = -1;


public:
	MapStateData();


	MapStateData(int id, const string& name);


	static MapStateData* fromBase64ZippedJSON(const string& b64);


	static MapStateData* fromJSON(const string& json);


	virtual string getTYPEIDString();

	virtual ArrayList<LightData*>* getLightDataList();
	virtual ArrayList<EntityData*>* getEntityDataList();
	virtual ArrayList<AreaData*>* getAreaDataList();


	virtual int getMapID();

	virtual void setMapID(int s);
};

