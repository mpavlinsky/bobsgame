#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger AssetData::log = Logger("AssetData");


AssetData::AssetData()
{ //===============================================================================================
}

AssetData::AssetData(int id, const string& name)
{ //===============================================================================================
	this->id = id;
	this->name = name;
}

string AssetData::getName()
{
	return name;
}

int AssetData::getID()
{
	return id;
}

void AssetData::setName(const string& s)
{
	name = s;
}

void AssetData::setID(int s)
{
	id = s;
}

