#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger DialogueData::log = Logger("DialogueData");


DialogueData::DialogueData()
{ //=========================================================================================================================
}

DialogueData::DialogueData(int id, const string& name, const string& caption, const string& comment, const string& text)
{ //=========================================================================================================================

	//AssetData(id, name);
	this->id = id;
	this->name = name;

	this->caption = caption;
	this->comment = comment;
	this->text = text;
}

DialogueData* DialogueData::fromBase64ZippedJSON(const string& b64)
{ //===============================================================================================



	string json = FileUtils::unzipBase64StringToString(b64);

	//Gson gson = new Gson();
	//DialogueData data = gson.fromJson(json,DialogueData.class);

	return fromJSON(json);
}

DialogueData* DialogueData::fromJSON(const string& json)
{ //===============================================================================================

	// Gson* gson = new Gson();
	DialogueData* data = nullptr;// gson->fromJson(json, DialogueData::typeid);


	return data;
}

string DialogueData::getTYPEIDString()
{ //===============================================================================================
	return string("DIALOGUE.") + to_string(getID());
}

string DialogueData::getCaption()
{
	return caption;
}

string DialogueData::getComment()
{
	return comment;
}

string DialogueData::getText()
{
	return text;
}

void DialogueData::setCaption(const string& s)
{
	this->caption = s;
}

void DialogueData::setComment(const string& s)
{
	this->comment = s;
}

void DialogueData::setText(const string& s)
{
	this->text = s;
}

