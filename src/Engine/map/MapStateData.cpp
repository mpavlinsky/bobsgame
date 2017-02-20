#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger MapStateData::log = Logger("MapStateData");


MapStateData::MapStateData()
{ //=========================================================================================================================
}

MapStateData::MapStateData(int id, const string& name)
{ //===============================================================================================
	AssetData(id, name);
}

MapStateData* MapStateData::fromBase64ZippedJSON(const string& b64)
{ //===============================================================================================



	string json = FileUtils::unzipBase64StringToString(b64);

	//Gson gson = new Gson();
	//MapStateData data = gson.fromJson(json,MapStateData.class);


	return fromJSON(json);
}

MapStateData* MapStateData::fromJSON(const string& json)
{ //===============================================================================================


	//Gson* gson = new Gson();
	MapStateData* data = nullptr;// gson->fromJson(json, MapStateData::typeid);


	return data;
}

string MapStateData::getTYPEIDString()
{ //===============================================================================================
	return string("STATE.") + to_string(getID());
}

ArrayList<LightData*>* MapStateData::getLightDataList()
{
	return &lightDataList;
}

ArrayList<EntityData*>* MapStateData::getEntityDataList()
{
	return &entityDataList;
}

ArrayList<AreaData*>* MapStateData::getAreaDataList()
{
	return &areaDataList;
}

int MapStateData::getMapID()
{
	return mapID;
}

void MapStateData::setMapID(int s)
{
	mapID = s;
}

