//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class FlagData : public AssetData
{
public:
	FlagData();


	FlagData(int id, const string& name);


	static FlagData* fromBase64ZippedJSON(const string& b64);


	static FlagData* fromJSON(const string& json);


	virtual string getTYPEIDString();
};

