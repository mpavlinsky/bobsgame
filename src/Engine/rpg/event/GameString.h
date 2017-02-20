//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



#include "src/Engine/network/ServerObject.h"


class GameStringData;

class GameString : public ServerObject
{
private:
	GameStringData* data;


public:

	static Logger log;
	GameString(Engine* g, int id);


	GameString(Engine* g, GameStringData* data);


	//The following method was originally marked 'synchronized':
	virtual void setData_S(GameStringData* data);


	virtual GameStringData* getData();

	virtual int getID();
	virtual string getName();
	virtual string text();

	virtual string getTYPEIDString();

	virtual void id(int id);
	virtual void setName(const string& name);
	virtual void text(const string& text);
};

