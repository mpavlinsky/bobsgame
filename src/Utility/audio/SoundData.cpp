#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger SoundData::log = Logger("SoundData");


SoundData::SoundData()
{ //=========================================================================================================================
}

SoundData::SoundData(int id, const string& name, const string& filename)
{ //=========================================================================================================================

	//AssetData(id, name);
	this->id = id;
	this->name = name;

	this->fileName = filename;
}

SoundData* SoundData::fromBase64ZippedJSON(const string& b64)
{ //===============================================================================================

	string json = FileUtils::unzipBase64StringToString(b64);

	//Gson gson = new Gson();
	//SoundData data = gson.fromJson(json,SoundData.class);


	return fromJSON(json);
}

SoundData* SoundData::fromJSON(const string& json)
{ //===============================================================================================


	//Gson* gson = new Gson();
	SoundData* data = nullptr;// gson->fromJson(json, SoundData::typeid);


	return data;
}

string SoundData::getTYPEIDString()
{ //===============================================================================================
	return string("SOUND.") + to_string(getID());
}

string SoundData::getFileName()
{
	return fileName;
}

string SoundData::getFullFilePath()
{
	return fullFilePath;
}

string SoundData::getMD5Name()
{
	return md5Name;
}

void SoundData::setFileName(const string& s)
{
	fileName = s;
}

void SoundData::setFullFilePath(const string& s)
{
	fullFilePath = s;
}

void SoundData::setMD5Name(const string& s)
{
	md5Name = s;
}

