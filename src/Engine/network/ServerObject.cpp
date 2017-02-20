#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger ServerObject::log = Logger("ServerObject");


ServerObject::ServerObject()
{ //=========================================================================================================================
}


ServerObject::ServerObject(Engine* g)
{ //=========================================================================================================================
	this->e = g;
}

//The following method was originally marked 'synchronized':
bool ServerObject::getInitialized_S()
{ //=========================================================================================================================
	return _initialized;
}

//The following method was originally marked 'synchronized':
void ServerObject::setInitialized_S(bool i)
{ //=========================================================================================================================
	_initialized = i;
}

void ServerObject::sendServerRequest()
{ //=========================================================================================================================
	if (getInitialized_S() == false)
	{
		//send a request to the server
		long long startTime = lastTimeRequestedFromServer;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 1000)
		{
			getEngine()->sendServerObjectRequest(this);
			lastTimeRequestedFromServer = currentTime;
		}
	}
}

bool ServerObject::getLoadedFromServerSendRequestIfFalse()
{ //=========================================================================================================================

	if (loadedInfoDataFromServer == false)
	{

		//small delay to prevent thread locking on synchronized functions.
		long long startTime = lastCheckedInitializedTime;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 1000)
		{
			lastCheckedInitializedTime = currentTime;

			if (getInitialized_S() == false)
			{
				//this has its own timer delay for network requests
				sendServerRequest();
			}
			else
			{
				loadedInfoDataFromServer = true;
			}
		}
	}
	return loadedInfoDataFromServer;
}

void ServerObject::update()
{ //=========================================================================================================================

	if (getLoadedFromServerSendRequestIfFalse())
	{

	}

}

