#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger EnginePart::log = Logger("EnginePart");


//BGClientEngine* EnginePart::clientGameEngine = nullptr;
//ControlsManager* EnginePart::controlsManager = nullptr;

EnginePart::EnginePart()
{ //=========================================================================================================================
}

EnginePart::EnginePart(Engine* g)
{ //=========================================================================================================================
	this->e = g;

	//if(g==null)log.error("e is null");
}


//
//void EnginePart::setControlsManager(ControlsManager* controlsManager)
//{
//	EnginePart::controlsManager = controlsManager;
//}

void EnginePart::toggleActivated()
{
	isActivated = !isActivated;
	timeActivated = System::currentHighResTimer();


	//TODO: send flag update with this game object TYPEID

	//TODO: maybe instead of flag i should allow any kind of value: int, float, bool, string

	//so, GAMEVALUE
}

void EnginePart::setActivated(bool b)
{
	isActivated = b;
	timeActivated = System::currentHighResTimer();

	//TODO: send flag update with this game object TYPEID
}

bool EnginePart::getIsActivated()
{
	return isActivated;
}

bool EnginePart::getWasEverActivated()
{
	if (timeActivated == -1)
	{
		return false;
	}
	return true;
}

int EnginePart::getSecondsSinceActivated()
{
	if (timeActivated == -1)
	{
		return 0;
	}

	long long startTime = timeActivated;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	return (int)(ticksPassed / 1000);
}

bool EnginePart::getWasEverHere()
{
	if (lastTimeHere == -1)
	{
		return false;
	}
	return true;
}

void EnginePart::resetLastTimeHere()
{
	lastTimeHere = -1;
}

void EnginePart::setLastTimeHere()
{
	lastTimeHere = System::currentHighResTimer();

	//TODO: send flag update with this game object TYPEID
}

long long EnginePart::getLastTimeHere()
{
	return lastTimeHere;
}

int EnginePart::getSecondsSinceLastHere()
{
	if (lastTimeHere == -1)
	{
		return -1;
	}

	long long startTime = lastTimeHere;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	return (int)(ticksPassed / 1000);
}

int EnginePart::getMinutesSinceLastHere()
{
	if (lastTimeHere == -1)
	{
		return -1;
	}

	long long startTime = lastTimeHere;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	return (int)((ticksPassed / 1000) / 60);
}

Engine* EnginePart::getEngine()
{
	return e;
}

Cameraman* EnginePart::getCameraman()
{
	return e->cameraman;
}

MapManager* EnginePart::getMapManager()
{
	return e->mapManager;
}

SpriteManager* EnginePart::getSpriteManager()
{
	return e->spriteManager;
}

ActionManager* EnginePart::getActionManager()
{
	return e->actionManager;
}

TextManager* EnginePart::getTextManager()
{
	return e->textManager;
}

AudioManager* EnginePart::getAudioManager()
{
	return e->audioManager;
}

CaptionManager* EnginePart::getCaptionManager()
{
	return e->captionManager;
}

EventManager* EnginePart::getEventManager()
{
	return e->eventManager;
}

CinematicsManager* EnginePart::getCinematicsManager()
{
	return e->cinematicsManager;
}

Map* EnginePart::getCurrentMap()
{
	Map* m = e->mapManager->currentMap;
//	if (m == nullptr)
//	{
//		m = new Map(e, new MapData(-1, "none", 0, 0));
//	}
	return m;
}






//void EnginePart::setClientGameEngine(BGClientEngine* gameEngine)
//{
//	EnginePart::clientGameEngine = gameEngine;
//}

BGClientEngine* EnginePart::getClientGameEngine()
{
	return Main::gameEngine;
}

ControlsManager* EnginePart::getControlsManager()
{
	return Main::controlsManager;
}



Clock* EnginePart::getClock()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->clock;
}

GUIManager* EnginePart::getGUIManager()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->guiManager;
}

StuffMenu* EnginePart::getStuffMenu()
{
	if (getGUIManager() == nullptr)return nullptr;
	return getGUIManager()->stuffMenu;
}

GameStore* EnginePart::getGameStore()
{
	if (getGUIManager() == nullptr)return nullptr;
	return getGUIManager()->gameStore;
}

PlayerEditMenu* EnginePart::getPlayerEditMenu()
{
	if (getGUIManager() == nullptr)return nullptr;
	return getGUIManager()->playerEditMenu;
}

Player* EnginePart::getPlayer()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->player;
}

ND* EnginePart::getND()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->nD;
}

Wallet* EnginePart::getWallet()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->wallet;
}

FriendManager* EnginePart::getFriendManager()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->friendManager;
}

StatusBar* EnginePart::getStatusBar()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->statusBar;
}

NotificationManager* EnginePart::getNotificationManager()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getStatusBar()->notificationManager;
}

TCPServerConnection* EnginePart::getServerConnection()
{
	return &BobNet::tcpServerConnection;
}

GameSave EnginePart::getGameSave()
{
	return getServerConnection()->getGameSave_S();
}


//=========================================================================================================================
bool EnginePart::udpPeerMessageReceived(UDPPeerConnection* c, string e)
{//=========================================================================================================================

	string s = e;

	if (s.find(":") == string::npos)return false;

	string command = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1);

	return false;
}