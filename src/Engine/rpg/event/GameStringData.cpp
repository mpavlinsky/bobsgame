#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger GameStringData::log = Logger("GameStringData");


GameStringData::GameStringData()
{ //=========================================================================================================================
}

GameStringData::GameStringData(int id, const string& name, const string& text)
{ //=========================================================================================================================

	//AssetData(id, name);
	this->id = id;
	this->name = name;

	this->text = text;
}

GameStringData* GameStringData::fromBase64ZippedJSON(const string& b64)
{ //===============================================================================================



	string json = FileUtils::unzipBase64StringToString(b64);

	//Gson gson = new Gson();
	//GameStringData data = gson.fromJson(json,GameStringData.class);

	return fromJSON(json);
}

GameStringData* GameStringData::fromJSON(const string& json)
{ //===============================================================================================

	//Gson* gson = new Gson();
	GameStringData* data = nullptr;// gson->fromJson(json, GameStringData::typeid);


	return data;
}

string GameStringData::getTYPEIDString()
{ //===============================================================================================
	return string("GAMESTRING.") + to_string(getID());
}

string GameStringData::getText()
{
	return text;
}

void GameStringData::setText(const string& s)
{
	text = s;
}

