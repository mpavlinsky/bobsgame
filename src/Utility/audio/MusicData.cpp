#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger MusicData::log = Logger("MusicData");


MusicData::MusicData()
{ //=========================================================================================================================
}

MusicData::MusicData(int id, const string& name, const string& filename)
{ //=========================================================================================================================

	//AssetData(id, name);
	this->id = id;
	this->name = name;

	this->fileName = filename;
}

MusicData* MusicData::fromBase64ZippedJSON(const string& b64)
{ //===============================================================================================

	string json = FileUtils::unzipBase64StringToString(b64);

	return fromJSON(json);
}

MusicData* MusicData::fromJSON(const string& json)
{ //===============================================================================================


	//Gson* gson = new Gson();
	MusicData* data = nullptr;// gson->fromJson(json, MusicData::typeid);


	return data;
}

string MusicData::getTYPEIDString()
{ //===============================================================================================
	return string("MUSIC.") + to_string(getID());
}

string MusicData::getFileName()
{
	return fileName;
}

string MusicData::getFullFilePath()
{
	return fullFilePath;
}

string MusicData::getMD5Name()
{
	return md5Name;
}

bool MusicData::getPreload()
{
	return preload;
}

void MusicData::setFileName(const string& s)
{
	fileName = s;
}

void MusicData::setFullFilePath(const string& s)
{
	fullFilePath = s;
}

void MusicData::setMD5Name(const string& s)
{
	md5Name = s;
}

void MusicData::setPreload(bool s)
{
	preload = s;
}

