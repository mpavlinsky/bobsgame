//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;

#include "src/Engine/Engine.h"

#include "src/Utility/Console.h"
#include "src/Utility/ConsoleText.h"

class Wallet;
class Clock;
class Player;
class GameSave;
class GUIManager;
class StatusBar;
class FriendManager;
class ND;
class Sprite;
class StadiumScreen;

class BGClientEngine : public Engine
{
	//DebugText playerSpeedText = DebugConsole.add("playerSpeedText");
private:
	typedef Engine super;

public:
	
	static Logger log;

	static bool debugMode;

	ConsoleText* playerMapText = Console::debug("playerMapText");
	ConsoleText* playerScreenText = Console::debug("playerScreenText");


	GUIManager* guiManager = nullptr;
	StatusBar* statusBar = nullptr;
	Wallet* wallet = nullptr;

	Clock* clock = nullptr;


	Player* normalPlayer = nullptr;
	Player* player = nullptr;

	FriendManager* friendManager = nullptr;

	ND* nD = nullptr;
	StadiumScreen* stadiumScreen = nullptr;


	bool controlsEnabled = true;
	bool playerExistsInMap = true;


	BGClientEngine();
	virtual ~BGClientEngine();
	virtual void init();






	virtual void update() override;


	virtual void cleanup() override;


	virtual void render() override;


	virtual bool areAnyMenusOpen();


	virtual void handleGameEngineOptionKeys();


	virtual void updateDebugText() override;


	virtual void loadPreCachedObjectData();

	virtual void initializeGameFromSave_S();
	virtual void setPlayerAppearanceFromGameSave_S();


	virtual BobColor* getNameColor(int accountType);


	virtual string getAccountRankString(int accountRank);
	virtual BobColor* getAccountRankColor(int accountRank);


	virtual void setPlayerToTempPlayerWithSprite(Sprite* s);
	virtual void setPlayerToNormalPlayer();



	Clock* getClock();
	GUIManager* getGUIManager();
	StuffMenu* getStuffMenu();
	GameStore* getGameStore();
	PlayerEditMenu* getPlayerEditMenu();
	Player* getPlayer();
	ND* getND();
	Wallet* getWallet();
	FriendManager* getFriendManager();
	StatusBar* getStatusBar();
	NotificationManager* getNotificationManager();
	//The following method was originally marked 'synchronized':



	//====================================================
	//NETWORKING
	//====================================================

	bool gameSaveCompleted_nonThreaded = false;

	//GameSave* getGameSave_S();

	private:
		bool isGameInitializedFromSave_nonThreaded = false;
		bool _isGameInitializedFromSave = false; //synchronized
public:
	//The following method was originally marked 'synchronized':
	virtual void setGameInitializedFromSave_S(bool b);
	//The following method was originally marked 'synchronized':
	virtual bool getGameInitializedFromSave_S();



	virtual bool serverMessageReceived(string e);


private:
	long long lastSentLoadEventRequestTime = 0;
	bool isLoadEventInitialized_nonThreaded = false;
	int _projectLoadEventID = -1;

public:
	//The following method was originally marked 'synchronized':
	virtual void setProjectLoadEventID_S(int id);

	//The following method was originally marked 'synchronized':
	virtual int getProjectLoadEventID_S();


	virtual bool getFinishedLoadEvent();
	Event* loadEvent = nullptr;

	bool finishedLoadEvent = false;


	public:
		virtual void sendLoadEventRequest();

private:
	void incomingLoadEventResponse(string s);


};

