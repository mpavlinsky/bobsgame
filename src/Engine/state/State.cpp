#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


Logger State::log = Logger("State");

//bool State::callNanoTimeForEachCall = false;

int State::totalFrames = 0;

//long long State::ticksPassedThisUpdate = 0;
int State::framesThisSecond = 0;

long long State::totalTicks = 0;
long long State::ticksThisSecond = 0;
int State::framesSkipped = 0;

ArrayList<UDPPeerConnection*> State::onlineFriends;


//BGClientEngine* State::clientGameEngine = nullptr;

//=========================================================================================================================
State::State()
{//=========================================================================================================================
#ifdef _DEBUG
	log.info("State()");
#endif

}
//=========================================================================================================================
State::~State()
{//=========================================================================================================================
#ifdef _DEBUG
	log.info("~State()");
#endif
}
//=========================================================================================================================
void State::init()
{//=========================================================================================================================
#ifdef _DEBUG
	log.info("State::init()");
#endif
}


//=========================================================================================================================
void State::updateTimers()
{//=========================================================================================================================
	framesThisSecond++;
	totalFrames++;


	totalTicks += realWorldTicksPassed();
	ticksThisSecond += realWorldTicksPassed();

	if (ticksThisSecond >= 1000)
	{
		ticksThisSecond = 0;

		//log.info(string("") + to_string(rendersThisSecond));
		framesThisSecond = 0;
	}

	//if(ticksPassedThisUpdate>17)ticksPassedThisUpdate=17; //TODO: this is frameskip off, basically. game will slow down instead
	if (realWorldTicksPassed() > 16 * 2)
	{
		framesSkipped++; //= ticksPassedThisUpdate/16;
	}
}


void State::setEngineSpeed(double f)
{ //=========================================================================================================================
	engineSpeed = f;
}

int State::engineTicksPassed()
{ //=========================================================================================================================

	//	if (callNanoTimeForEachCall == true)
	//	{
	//
	//
	//		long long currentHighResTime = System::currentHighResTimer();
	//
	//		int ticksPassed = (long long)((double)(currentHighResTime - lastRenderHighResTime) / System::cpuFreq);
	//
	//		return static_cast<long long>(ticksPassed * engineSpeed);
	//	}
	//	else
	{
		return (int)(System::ticksPassedThisUpdate * engineSpeed);
	}


	//DONE: can multiply this to speed up game, divide it to slow game down!
}

int State::realWorldTicksPassed()
{ //=========================================================================================================================

	//	if (callNanoTimeForEachCall == true)
	//	{
	//		currentHighResTime = System::currentHighResTimer();
	//
	//		int ticksPassed = (long long)((double)(currentHighResTime - lastRenderHighResTime) / System::cpuFreq);
	//
	//		return static_cast<long long>(ticksPassed);
	//	}
	//	else
	{
		return (int)(System::ticksPassedThisUpdate);
	}


	//DONE: can multiply this to speed up game, divide it to slow game down!
}

void State::update()
{ //=========================================================================================================================

	onlineFriends.clear();
	for (int i = 0; i < (int)BobNet::udpConnections.size(); i++)
	{
		UDPPeerConnection* f = BobNet::udpConnections.get(i);
		if (f->getConnectedToPeer_S() == true && f->getGotFriendData_S() == true && f->peerStatus == BobNet::status_AVAILABLE)
		{
			if (onlineFriends.contains(f) == false)
				onlineFriends.add(f);
		}
	}
}

void State::render()
{ //=========================================================================================================================
}

void State::cleanup()
{ //=========================================================================================================================
}

void State::updateControls()
{
	resetPressedButtons();
	setButtonStates();
}

void State::resetPressedButtons()
{
	getControlsManager()->resetPressedButtons();
}

void State::setButtonStates()
{
	getControlsManager()->setButtonStates();
}

ControlsManager* State::getControlsManager()
{
	return Main::controlsManager;
}


//
//void State::setClientGameEngine(BGClientEngine* gameEngine)
//{
//	State::clientGameEngine = gameEngine;
//}

BGClientEngine* State::getClientGameEngine()
{
	return Main::gameEngine;
}

TCPServerConnection* State::getServerConnection()
{
	return &(Main::bobNet->tcpServerConnection);
}

long long State::getUserID_S()
{
	return getGameSave_S().userID;
}

string State::getUserName_S()
{
	return getGameSave_S().userName;
}

GameSave State::getGameSave_S()
{
	return getServerConnection()->getGameSave_S();
}

void State::setGameSave_S(GameSave& g)
{
	getServerConnection()->setGameSave_S(g);
}

int State::getWidth()
{
	return GLUtils::getViewportWidth();
}

int State::getHeight()
{
	return GLUtils::getViewportHeight();
}


bool State::udpPeerMessageReceived(UDPPeerConnection* c, string s)
{
	return false;
}


bool State::serverMessageReceived(string cs)
{
	//override this!
	return false;
}

