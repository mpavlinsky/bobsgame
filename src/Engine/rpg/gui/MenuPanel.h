//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class MenuPanel : public EnginePart
{
public:

	static Logger log;


	//DialogLayout* mainPanelLayout;
	//ScrollPane* scrollPane;
	//DialogLayout* insideScrollPaneLayout;


protected:
	
	bool isActivated = false;
	
	bool isScrollingDown = false;
	
	bool isScrolledUp = false;

public:
	int ticksSinceTurnedOn = 0;
	int ticksSinceTurnedOff = 0;

	float screenY = 0;


	float fadeInTime = 600.0f;
	float fadeOutTime = 1000.0f;


private:
	
	bool enabled = true;


public:
	MenuPanel();


	virtual void update();


	virtual void setEnabled(bool b);

	virtual bool getEnabled();


	virtual bool getIsActivated();


	virtual bool getIsScrollingDown();


	virtual bool getIsScrolledUp();


	virtual void setActivated(bool b);


	virtual void toggleActivated();


	virtual void onScrolledUp();


	virtual void scrollUp();


	virtual void scrollDown();


protected:
	virtual void layout();


public:
	virtual void renderBefore();


	virtual void render();

//
//	static BGClientEngine* getClientGameEngine();
//
//
//
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
//
//	static TCPServerConnection* getServerConnection();
//	static GameSave* getGameSave();
};

