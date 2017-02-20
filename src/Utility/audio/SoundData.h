//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class SoundData : public AssetData
{
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------
	//
	//
	//
	//	WARNING! EDITING THESE NAMES WILL BREAK JSON DECODING
	//
	//
	//
	//
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------

private:
	
	string fileName = "";
	
	string fullFilePath = "";


	
	string md5Name = ""; //for use in client


public:
	SoundData();


	SoundData(int id, const string& name, const string& filename);


	static SoundData* fromBase64ZippedJSON(const string& b64);


	static SoundData* fromJSON(const string& json);


	virtual string getTYPEIDString();

	virtual string getFileName();
	virtual string getFullFilePath();
	virtual string getMD5Name();


	virtual void setFileName(const string& s);
	virtual void setFullFilePath(const string& s);
	virtual void setMD5Name(const string& s);
};

