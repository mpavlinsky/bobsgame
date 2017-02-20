//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class SkillData : public AssetData
{
public:
	SkillData();


	SkillData(int id, const string& name);


	static SkillData* fromBase64ZippedJSON(const string& b64);


	static SkillData* fromJSON(const string& json);

	virtual string getTYPEIDString();
};

