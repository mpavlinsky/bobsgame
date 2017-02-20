//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




#include "src/Engine/network/ServerObject.h"

class FlagData;

class Flag : public ServerObject
{
private:
	bool value = false;
	long long timeSet = -1;

	FlagData* data;


public:


	static Logger log;
	Flag(Engine* g, int id);


	Flag(Engine* g, FlagData* data);


	//The following method was originally marked 'synchronized':
	virtual void setData_S(FlagData* data);


	virtual FlagData* getData();


	virtual int getID();
	virtual string getName();
	virtual string getTYPEIDString();


	virtual void setID(int id);
	virtual void setName(const string& name);


	//The following method was originally marked 'synchronized':
	virtual void setValue_S(bool b); //sendServerValueUpdate(boolean b)


	//The following method was originally marked 'synchronized':
	virtual void initValueFromGameSave_S(bool b, long long timeSet); //sendServerValueUpdate(boolean b)


	//The following method was originally marked 'synchronized':
	virtual bool getValue_S();


	virtual long long getTimeSet();
};

