

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
#include "src/Utility/System.h"
#include "src/Utility/HashMap.h"
#include "src/Utility/ArrayList.h"
#include <lib/GWEN-master/gwen/include/Gwen/Input/gwen_input_sdl2.h>
#include <lib/GWEN-master/gwen/include/Gwen/Skins/TexturedBase.h>
#include <lib/GWEN-master/gwen/include/Gwen/Renderers/OpenGL.h>
#include "Engine/network/BobNet.h"
#include "Engine/rpg/BGClientEngine.h"

#include "Puzzle/GlobalSettings.h"

class Logger;


class BGClientTCP;
class Console;
class ControlsManager;
class BobsGame;
class FileUtils;
class StateManager;
class LoggedOutState;
class LoginState;
class ServersHaveShutDownState;
class CreateNewAccountState;
class TitleScreenState;
class YouWillBeNotifiedState;
class GlowTileBackground;

class Main
{
public:


	static string serverAddressString;
	static string STUNServerAddressString;

	static string version;
	//-----------------------------
	//variables
	//-----------------------------

	//static bool vbl_done;
	//static bool timer_done;

	//static TTF_Font* ttf_bobsgame_8;
	//static TTF_Font* ttf_bobsgame_16;
	//static bool seeded;
	//static bool vbl_init;
	//static bool GAME_is_running;
	//static bool append_screen;
	//static int MAIN_QUIT;
	static bool GLOBAL_hq2x_is_on;
	//static int HARDWARE_brightness;
	//static int vsync;
	//static int fpsmeter;
	//static int GAMESTATE;
	//static int GLOBAL_debug_level_select;
	//static bool GAME_paused;
	//static bool music_playing;

	//-----------------------------
	//ini variables
	//-----------------------------

	//static int debug;
	//static int fullscreen;
	//static int skiptext;
	//static int easymode;
	//static int cheater;


	BobsGame* bobsGame = nullptr;

	static Gwen::Controls::Canvas* gwenCanvas;
	static Gwen::Input::GwenSDL2 *gwenInput;
	static Gwen::Renderer::OpenGL* gwenRenderer;
	static Gwen::Skin::TexturedBase* gwenSkin;

	static Logger log;

	static Main* mainObject;

	static Main* getMain();
	static void setMain(Main* c);


	Main();
	static void openURL(string url);
	static string getPath();


	System* clientInfo = new System();


	//virtual void initSystemInfo();


	float timeZoneGMTOffset = 0.0f;
	float DSTOffset = 0.0f;
	//virtual void initClockAndTimeZone();


	virtual void doLegalScreen();


	virtual void showControlsImage();


	virtual void makeGhostThread();



	static GlobalSettings* globalSettings;
	void loadGlobalSettingsFromXML();
	void saveGlobalSettingsToXML();

	//JAVA TO C++ CONVERTER TODO TASK: 'volatile' has a different meaning in C++:
	//ORIGINAL LINE: public volatile boolean exit = false;
	static bool quit;// = false;


	FileUtils* cacheManager = nullptr;
	StateManager* stateManager = nullptr;

	static ControlsManager* controlsManager;// = nullptr;

	static BGClientEngine* gameEngine;// = nullptr;

	//BGClientEngine* getGameEngine();

	//ArrayDeque<BGClientEngine*> *gameStack = new ArrayDeque<BGClientEngine*>();

	static Console* console;// = nullptr;

	LoginState* loginState = nullptr;
	LoggedOutState* loggedOutState = nullptr;
	ServersHaveShutDownState* serversHaveShutDownState = nullptr;
	CreateNewAccountState* createNewAccountState = nullptr;
	TitleScreenState* titleScreenState = nullptr;

	YouWillBeNotifiedState* youWillBeNotifiedState = nullptr;
	static GlowTileBackground* glowTileBackground;


	bool serversAreShuttingDown = false;


	string slash = "/";// System::getProperties().getProperty("file.separator");

					   //static bool isApplet;

	SDL_Window* SDLWindow = nullptr;

	//FileUtils* utils;
	//GLUtils* lwjglUtils = nullptr;
	System* systemUtils = nullptr;
	//GLUtils* glUtils = nullptr;
	// static AudioUtils* audioUtils;

	static BobNet* bobNet;




	//ClientUDP clientUDP;




	virtual void mainInit();


	virtual void initClientEngine();


	static bool introMode;
	static bool previewClientInEditor;


	bool debugKeyPressed = false;

	static bool screenShotKeyPressed;// = false;
	static bool resize;// = false;


	static void doResizeCheck();
	static void doScreenShotCheck();

	static ArrayList<SDL_Event> events;// = new ArrayList<SDL_Event>();

	void printEvent(const SDL_Event* e);
	void processEvents();
	static void whilefix();
	static void delay(int ticks);

	void oldrender();
	void render();
	void update();

	//static void e(const string &whereErrorOccurredString);
	//static void e();
	static void checkVersion();

	//   static string facebookID;
	//   static string facebookAccessToken;
	//   static bool _gotFacebookResponse;
	//

	//   //The following method was originally marked 'synchronized':
	//   static void setGotFacebookResponse_S(bool b);
	//   //The following method was originally marked 'synchronized':
	//   static bool getGotFacebookResponse_S();
	//
	//
	//   //this is called from the browser javascript after we call the facebook JS SDK
	//   virtual void setFacebookCredentials(const string& facebookID, const string& accessToken);


	virtual void mainLoop();




	virtual void cleanup();

	//int unZip(string file);
};

