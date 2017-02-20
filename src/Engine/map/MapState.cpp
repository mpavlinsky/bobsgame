#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger MapState::log = Logger("MapState");


MapState::MapState(MapStateData* mapStateData)
{ //=========================================================================================================================
	
	this->data = mapStateData;
	//lightByNameHashtable = new HashMap<string, Light*>();
	//entityByNameHashtable = new HashMap<string, Entity*>();
	//characterByNameHashtable = new HashMap<string, Character*>();
	//areaByNameHashtable = new HashMap<string, Area*>();
	//areaByTYPEIDHashtable = new HashMap<string, Area*>();
}

MapStateData* MapState::getData()
{
	return data;
}

int MapState::getID()
{
	return getData()->getID();
}

string MapState::getName()
{
	return getData()->getName();
}

