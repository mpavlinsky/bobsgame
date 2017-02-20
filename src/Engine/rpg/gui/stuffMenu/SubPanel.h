//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once

#include "bobtypes.h"

class Logger;

class SubPanel : public EnginePart
{
public:

	static Logger log;

	SubPanel();

	virtual void init();
	virtual void setVisible(bool b);
	virtual void layout();
	virtual void update();
	virtual void render();

//	static BGClientEngine* getClientEngine();
//	static EventManager* getEventManager();
//	static Clock* getClock();
//	static GUIManager* getGUIManager();
//	static StuffMenu* getStuffMenu();
//	static GameStore* getGameStore();
//	static PlayerEditMenu* getPlayerEditMenu();
//	static Player* getPlayer();
//	static ND* getND();
//	static Wallet* getWallet();
//	static FriendManager* getFriendManager();
//	static StatusBar* getStatusBar();
//	static NotificationManager* getNotificationManager();
//	static GameSave* getGameSave();
//	static TCPServerConnection* getServerConnection();


};

