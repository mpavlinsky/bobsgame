#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once



//Logger SkillData::log = Logger("SkillData");


SkillData::SkillData()
{ //=========================================================================================================================
}

SkillData::SkillData(int id, const string& name)
{ //=========================================================================================================================

	//AssetData(id, name);
	this->id = id;
	this->name = name;
}

SkillData* SkillData::fromBase64ZippedJSON(const string& b64)
{ //===============================================================================================

	string json = FileUtils::unzipBase64StringToString(b64);

	//Gson gson = new Gson();
	//SkillData data = gson.fromJson(json,SkillData.class);


	return fromJSON(json);
}

SkillData* SkillData::fromJSON(const string& json)
{ //===============================================================================================


	//Gson* gson = new Gson();
	SkillData* data = nullptr;// gson->fromJson(json, SkillData::typeid);


	return data;
}

string SkillData::getTYPEIDString()
{ //===============================================================================================
	return string("SKILL.") + to_string(getID());
}

