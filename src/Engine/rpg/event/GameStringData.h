//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class GameStringData : public AssetData
{
private:
	
	string text = "";


public:
	GameStringData();


	GameStringData(int id, const string& name, const string& text);


	static GameStringData* fromBase64ZippedJSON(const string& b64);


	static GameStringData* fromJSON(const string& json);


	virtual string getTYPEIDString();


	virtual string getText();

	virtual void setText(const string& s);
};

