//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class MapState
{
	//these hold the Light objects themselves, created in the constructor for this map.
	//these both hold the same thing for convenience.
public:
	ArrayList<Light*> lightList;
	HashMap<string, Light*> lightByNameHashtable;//new HashMap<string, Light*>();


	ArrayList<Entity*> entityList;
	HashMap<string, Entity*> entityByNameHashtable;//new HashMap<string, Entity*>();

	ArrayList<Character*> characterList;
	HashMap<string, Character*> characterByNameHashtable;//new HashMap<string, Character*>();


	ArrayList<Area*> areaList;
	HashMap<string, Area*> areaByNameHashtable;//new HashMap<string, Area*>();
	HashMap<string, Area*> areaByTYPEIDHashtable;//new HashMap<string, Area*>();


private:
	MapStateData* data = nullptr;


public:
	MapState(MapStateData* mapStateData);


	virtual MapStateData* getData();

	virtual int getID();
	virtual string getName();
};

