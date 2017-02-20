//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "../EnginePart.h"

class Logger;

class ServerObject : public EnginePart
{
public:

	static Logger log;
	ServerObject();
	ServerObject(Engine* g);


protected:
	bool _initialized = false;
	long long lastTimeRequestedFromServer = 0;

public:
	//The following method was originally marked 'synchronized':
	virtual bool getInitialized_S();

protected:
	//The following method was originally marked 'synchronized':
	virtual void setInitialized_S(bool i);

private:
	void sendServerRequest();


protected:
	bool loadedInfoDataFromServer = false; //non-threaded check
	long long lastCheckedInitializedTime = 0;

	virtual bool getLoadedFromServerSendRequestIfFalse();

public:
	virtual void update();
};

