//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class MusicData : public AssetData
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
	
	string fullFilePath = ""; //for use in editor

	
	string md5Name = ""; //for use in client

	
	bool preload = false;


public:
	MusicData();


	MusicData(int id, const string& name, const string& filename);


	static MusicData* fromBase64ZippedJSON(const string& b64);


	static MusicData* fromJSON(const string& json);


	virtual string getTYPEIDString();


	virtual string getFileName();
	virtual string getFullFilePath();
	virtual string getMD5Name();
	virtual bool getPreload();


	virtual void setFileName(const string& s);
	virtual void setFullFilePath(const string& s);
	virtual void setMD5Name(const string& s);
	virtual void setPreload(bool s);
};

