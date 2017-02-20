//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"

class CaptionManager;
class BGClientEngine;
class UDPPeerConnection;
class TCPServerConnection;
class GameSave;
class Logger;
class ControlsManager;



class State
{
public:

	State();
	virtual ~State();
	virtual void init();

	static Logger log;

	//static BGClientEngine* clientGameEngine;

	//static bool callNanoTimeForEachCall;

	static ArrayList<UDPPeerConnection*> onlineFriends;

	double engineSpeed = 1.0;

private:
	static int totalFrames;

	//static long long ticksPassedThisUpdate;

	static int framesThisSecond;
	//static long long lastSecondTime;
	//private static long last100Ticks=lastRenderHighResTime;

	static long long totalTicks;
	static long long ticksThisSecond;
	static int framesSkipped;

public:
	static void updateTimers();
	virtual void setEngineSpeed(double f);
	virtual int engineTicksPassed();
	static int realWorldTicksPassed();

	virtual void update();
	virtual void render();
	virtual void cleanup();


	static ControlsManager* getControlsManager();


	//static void setClientGameEngine(BGClientEngine* gameEngine);
	static BGClientEngine* getClientGameEngine();


	virtual void updateControls();
	virtual void resetPressedButtons();
	virtual void setButtonStates();



	static TCPServerConnection* getServerConnection();

	static long long getUserID_S();
	static string getUserName_S();
	static GameSave getGameSave_S();
	static void setGameSave_S(GameSave &g);
	
	virtual int getWidth();

	virtual int getHeight();

	virtual bool udpPeerMessageReceived(UDPPeerConnection *c, string s);
	virtual bool serverMessageReceived(string cs);
};

