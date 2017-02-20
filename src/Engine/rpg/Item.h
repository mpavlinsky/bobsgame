//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class Item : public ServerObject
{
public:

	static Logger log;


	Sprite* sprite = nullptr;

	string spriteAssetName = "";
	int spriteAssetID = -1;

private:
	bool haveItemValue_S = false;
	long long timeSet = -1;


public:
	Item(Engine* g, const string& spriteAssetName);


	Item(Engine* g, int spriteAssetID);


	Item(Engine* g, Sprite* sprite);


	virtual void sendServerRequest();


	virtual string getName();
	virtual string description();
	virtual int getID();


	//The following method was originally marked 'synchronized':
	virtual void getWithCaption_S();


	//The following method was originally marked 'synchronized':
	virtual void setHaveItemValue_S(bool b);


	//The following method was originally marked 'synchronized':
	virtual void initHaveItemValue_S(bool b, long long timeSet);


	//The following method was originally marked 'synchronized':
	virtual bool getHaveItemValue_S();


	virtual long long getTimeSet();
};

