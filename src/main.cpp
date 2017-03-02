#include "stdafx.h"
#include <time.h>
#include <fstream>
#include <iostream>
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#undef INADDR_ANY       
//#undef INADDR_LOOPBACK  
//#undef INADDR_BROADCAST 
//#undef INADDR_NONE  
//#include "enet/enet.h"

#include "minilzo.h"
//#include <lib/authenticate-GWEN-master/include/Gwen/renderer/gwen_renderer_sdl2.h>
//#include <lib/authenticate-GWEN-master/include/Gwen/input/gwen_input_sdl2.h>
//#include <lib/authenticate-GWEN-master/include/Gwen/skin/gwen_skin_texture.h>

//#include <imgui.h>
//#include "imgui_impl_sdl.h"

#include "Gwen/Gwen.h"
#include "Gwen/Skins/Simple.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/UnitTest/UnitTest.h"
#include "Gwen/Input/Windows.h"
#include "Gwen/Renderers/OpenGL_TruetypeFont.h"
#include <lib/GWEN-master/gwen/include/Gwen/Input/gwen_input_sdl2.h>

//==========================================================================================================================
int main(int argc, char* argv[])//int argc, char **argv)
{//==========================================================================================================================

//#ifdef WIN32
//	SetDllDirectory(LPCWSTR("./libs/"));
//#endif

	cout << "Starting..." << endl;


	Main::setMain(new Main());
	Main::getMain()->mainInit();
	Main::getMain()->mainLoop();
	Main::getMain()->cleanup();

	return 0;
}


Logger Main::log = Logger("Main");


Main* Main::mainObject = nullptr;

ArrayList<SDL_Event> Main::events;


bool Main::quit = false;

//bool Main::GAME_is_running = false;
bool Main::GLOBAL_hq2x_is_on = false;
//int Main::fpsmeter = true;



ControlsManager* Main::controlsManager = new ControlsManager();
BGClientEngine* Main::gameEngine = nullptr;
//==========================================================================================================================
Main::Main()
{//=========================================================================================================================


}

#ifdef __WINDOWS__
#include <shellapi.h>
wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}
#endif
//==========================================================================================================================
void Main::openURL(string url)
{//==========================================================================================================================

#ifdef __WINDOWS__
	LPCWSTR o = L"open";
	LPCWSTR u = convertCharArrayToLPCWSTR(url.c_str());

	ShellExecute(NULL, o, u, NULL, NULL, SW_SHOWNORMAL);
#endif
#ifdef __LINUX__
	string bin = "/usr/bin/firefox";
	char *args[2];
	args[0] = (char*)url.c_str();
	args[1] = 0;
	//					pid_t pid;
	//					pid = fork();
	//					if (!pid)execvp((char*)bin.c_str(), args);

	int result = system(string(bin + " " + url).c_str());
	if (result == -1)
	{
		bin = "/usr/bin/xdg-open";
		result = system(string(bin + " " + url).c_str());
	}
#endif
#ifdef __MACOSX__
	string command = "open " + url;
	system(command.c_str());
#endif
}


//FileUtils *Main::cacheManager = new FileUtils();
//bool Main::isApplet = false;

string Main::serverAddressString = BobNet::releaseServerAddress;
string Main::STUNServerAddressString = BobNet::releaseSTUNServerAddress;
string Main::version = "";

BobNet* Main::bobNet = nullptr;
Console* Main::console = nullptr;

Gwen::Controls::Canvas* Main::gwenCanvas = nullptr;
Gwen::Input::GwenSDL2 *Main::gwenInput = nullptr;
Gwen::Renderer::OpenGL* Main::gwenRenderer = nullptr;
Gwen::Skin::TexturedBase* Main::gwenSkin = nullptr;
//MSG msg;

//==========================================================================================================================
void Main::mainInit()
{//=========================================================================================================================


 //easy mode
 //debug/skiptext
 //bpp
 //fullscreen
 /*
 dictionary*	ini ;
 ini = iniparser_load("config.ini");
 if (ini==nullptr){fprintf(stderr,"config.ini not found\n");}
 else
 {
 fullscreen = iniparser_getboolean(ini, "bobsgame:fullscreen", 0);
 easymode = iniparser_getboolean(ini, "bobsgame:easymode", 0);
 debug = iniparser_getboolean(ini, "bobsgame:debug", 0);
 ///if(debug)skiptext=1;
 //s = iniparser_getstring(ini, "bobsgame:easymode", nullptr);
 //i = iniparser_getint(ini, "skiptext:year", -1);
 //s = iniparser_getstring(ini, "wine:country", nullptr);
 //d = iniparser_getdouble(ini, "wine:alcohol", -1.0);
 iniparser_freedict(ini);
 }
 */


	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");
	SDL_SetHint(SDL_HINT_XINPUT_ENABLED, "0");

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
		exit(2);
	}

	if (SDLNet_Init() < 0) {
		std::cerr << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
	}


	if (lzo_init() != LZO_E_OK)
	{
		printf("internal error - lzo_init() failed !!!\n");
		printf("(this usually indicates a compiler bug - try recompiling\nwithout optimizations, and enable '-DLZO_DEBUG' for diagnostics)\n");
	}


	//atexit(SDL_Quit);
	BobColor::initPresetColors();
	new GLUtils();
	new AudioManager();
	new Logger();

	AudioManager::initAudio();

	GLUtils::checkSDLError("");


//	bool debugOnLiveServer = true;
//	if (debugOnLiveServer == false)
//	{
//		serverAddressString = BobNet::debugServerAddress;
//		STUNServerAddressString = BobNet::debugSTUNServerAddress;
//	}
//	else
	{
		serverAddressString = BobNet::releaseServerAddress;
		STUNServerAddressString = BobNet::releaseSTUNServerAddress;
	}




	Logger::initLogger();

	log.info("Main Init...");

	//this is done before init game so we can put debug stuff
	console = new Console();

	GLUtils::initGL((char*)"\"bob's game\"");
	//GLUtils::initTWL();
	ControlsManager::initControllers();
	GLUtils::e();

	BobFont::initFonts();
	GLUtils::e();
	
	if (previewClientInEditor == false)
	{
		doLegalScreen();
	}

	cacheManager = new FileUtils();
	cacheManager->initCache();
	GLUtils::e();

	stateManager = new StateManager();
	GLUtils::e();

	//-------------------
	//init login GUI
	//-------------------

	log.info("Init GUIs...");
	if (glowTileBackground == nullptr)
	{
		glowTileBackground = new GlowTileBackground();
	}

	loginState = new LoginState();
	loggedOutState = new LoggedOutState();
	serversHaveShutDownState = new ServersHaveShutDownState();
	createNewAccountState = new CreateNewAccountState();
	titleScreenState = new TitleScreenState();
	youWillBeNotifiedState = new YouWillBeNotifiedState();
	GLUtils::e();

	//-------------------
	//init game
	//-------------------
	log.info("Init Client...");

	systemUtils = new System();
	GLUtils::e();

	System::initDebugInfo();
	GLUtils::e();
	System::initClockAndTimeZone();
	GLUtils::e();
	//-------------------
	//fill in the client session info to send to the server for debug/stats
	//this must be done after everything is initialized.
	//-------------------
	System::initSystemInfo();
	GLUtils::e();
	//makeGhostThread();
	//GLUtils::e();

	srand((int)(time(nullptr)));

	log.info("Create BobsGame");
	bobsGame = new BobsGame();
	log.info("Init BobsGame");
	bobsGame->init();
	stateManager->setState(bobsGame);
	
	log.info("Init BobNet");
	bobNet = new BobNet();
	bobNet->addEngineToForwardMessagesTo(stateManager->getState());

	System::initTimers();



	log.info("Init GUI");

	gwenRenderer = new Gwen::Renderer::OpenGL_TruetypeFont();
	gwenRenderer->Init();
	gwenRenderer->SetDrawColor(Gwen::Color(255, 0, 0, 255));
	gwenSkin = new Gwen::Skin::TexturedBase(gwenRenderer);
	string path = Main::getPath();
	gwenSkin->Init(path + "data/DefaultSkin.png");
	gwenSkin->SetDefaultFont(Gwen::Utility::StringToUnicode(path + "data/fonts/Lato-Medium.ttf"), 16);
	gwenCanvas = new Gwen::Controls::Canvas(gwenSkin);
	gwenCanvas->SetSize(GLUtils::getViewportWidth(), GLUtils::getViewportHeight());
	gwenCanvas->SetDrawBackground(false);
	gwenInput = new Gwen::Input::GwenSDL2();
	gwenInput->Initialize(gwenCanvas);



	log.info("Version Check");
	checkVersion();

	System::initTimers();
	GLUtils::e();

	//initClientEngine();
	GLUtils::e();
	//tcpServerConnection = new BGClientTCP(gameEngine);
	GLUtils::e();

//#ifdef _DEBUG
//	string s = "hello this is a test asdu fasigdf aiohsdf aoisbd gab srihagb isrhbagiusrhb gkjbazarhgbszjkhvgaoishb ashgb uaysb gjabs ougyab eriabslkbgvaoisugh kasbgvjahsidf aslkbasdhga isbga isbr gasbd sg jkseba lkgsdboiags ekjaslgbaisueabhs lgkjahsr jagbrsouigbaisbrgabfoiguas rabg riahbg sirhbgalisrbga isrhbgalisrbg iasrbga lisrhb galisrbg lahsbrgiaubse lagijbse rlkaghbsr iugab srlijabg lsrbga lisrubg ailusrbg alisurbg laiusrbilguabisurgliaubsrlgba bg liseba glsgb asiugejhgdrigshrd";
//	string z = FileUtils::zipStringToBase64String(s);
//	log.debug(z);
//	string u = FileUtils::unzipBase64StringToString(z);
//	log.debug(u);
//#endif

//	GameType *s = new GameType();
//	s->tetsosumi();
//	string zip = s->toBase64GZippedXML();
//	string xml = FileUtils::unzipBase64StringToString(zip);
//		log.info(xml);

#ifndef _DEBUG
	//GLUtils::toggleFullscreen();
#endif



	//ImGui_ImplSdl_Init(GLUtils::window);




}

////===========================================================================================================================
//void Main::e(const string &whereErrorOccurredString)
//{//===========================================================================================================================
//
//	GLUtils::e(whereErrorOccurredString);
//
//}
//
//===========================================================================================================================
//void Main::e()
//{//===========================================================================================================================
//
//	GLUtils::checkSDLError("");
//	GLUtils::checkGLError("");
//
//}


bool Main::introMode = false;
bool Main::previewClientInEditor = false;

//==========================================================================================================================
void Main::initClientEngine()
{//=========================================================================================================================


	if (gameEngine != nullptr)
	{
		gameEngine->cleanup();
	}

	//         if (tcpServerConnection != nullptr)
	//         {
	//            tcpServerConnection->cleanup();
	//         }


	gameEngine = new BGClientEngine();
	//Engine::setClientGameEngine(gameEngine);


	//stateManager.setState(game);
	gameEngine->init();






	if (previewClientInEditor == false)
	{
		bool didIntro = false; //FileUtils.doesDidIntroFileExist();

		if (didIntro == false)
		{
			introMode = true;

			log.info("Setup Intro...");

			gameEngine->statusBar->gameStoreButton->setEnabled(false);
			gameEngine->statusBar->ndButton->setEnabled(false);
			gameEngine->statusBar->stuffButton->setEnabled(false);
			gameEngine->statusBar->moneyCaption->setEnabled(false);
			gameEngine->statusBar->dayCaption->setEnabled(false);

			stateManager->setState(gameEngine);
			gameEngine->cinematicsManager->fadeFromBlack(10000);


			//gameEngine->mapManager->changeMap("ALPHABobsApartment", "atDesk");
			//gameEngine.mapManager.changeMap("GENERIC1UpstairsBedroom1",12*8*2,17*8*2);
			//gameEngine.textManager.getText("Yep \"Yuu\" yay. <.><1>bob! yay, \"bob\" yay! <.><0>\"Yuu\" yay, nD. yay yay \"bob's game\" yay- bob's? yay \"bob's\" yay bob's game<1>yep");
		}
		//				else
		//				{
		//					if (System::debugMode == false)
		//					{
		//						showControlsImage();
		//					}
		//
		//					stateManager->setState(loginState);
		//				}
	}
}



//      string Main::facebookID = "";
//      string Main::facebookAccessToken = "";
//      bool Main::_gotFacebookResponse = false;
//
//      //The following method was originally marked 'synchronized':
//      void Main::setGotFacebookResponse_S(bool b)
//      {
//         _gotFacebookResponse = b;
//      }
//
//      //The following method was originally marked 'synchronized':
//      bool Main::getGotFacebookResponse_S()
//      {
//         return _gotFacebookResponse;
//      }
//
//      void Main::setFacebookCredentials(const string &facebookID, const string &accessToken)
//      { //=========================================================================================================================
//         Main::facebookID = facebookID;
//         Main::facebookAccessToken = accessToken;
//
//         setGotFacebookResponse_S(true);
//      }


//==========================================================================================================================
void Main::whilefix()
{//==========================================================================================================================
	getMain()->processEvents();
	getMain()->stateManager->getState()->resetPressedButtons();

	bool frame = false;

	while (frame == false)
	{
		System::updateRenderTimers();
		System::updateDebugInfo();

		if (System::getTotalRenderTicksPassed() >= 16)
		{
			System::resetTotalRenderTicksPassed();
			System::updateUpdateTimers();

			console->update();
			bobNet->tcpServerConnection.update();

			if (dynamic_cast<Engine*>(getMain()->stateManager->getState()) != NULL)
			{
				((Engine*)getMain()->stateManager->getState())->getCaptionManager()->update();
			}
			

			frame = true;

			getMain()->render();
			SDL_GL_SwapWindow(GLUtils::window);
		}
		SDL_Delay(10);
	}

	getMain()->stateManager->getState()->setButtonStates();
}

//==========================================================================================================================
void Main::delay(int ticks)
{//==========================================================================================================================


 	long long startTime = System::currentHighResTimer();
 	int ticksPassed = 0;

	while (ticksPassed < ticks)
	{
		long long currentTime = System::currentHighResTimer();
		ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		whilefix();
	}
}

//=========================================================================================================================
void Main::oldrender()
{//=========================================================================================================================
	GLUtils::old_clear();
	GLUtils::old_render();
}

//bool show_test_window = true;
//bool show_another_window = false;
//ImVec4 clear_color = ImColor(0, 0, 0);
//=========================================================================================================================
void Main::update()
{//=========================================================================================================================


//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//	{
//		// .. give it to the input handler to process
//		GwenInput.ProcessMessage(msg);
//	}


	processEvents();
	//GLUtils::e();
	stateManager->getState()->updateControls();
	//GLUtils::e();

	doScreenShotCheck();
	doResizeCheck();

	stateManager->update();
	//GLUtils::e();
	console->update();
	//GLUtils::e();
	bobNet->update();


//	ImGui_ImplSdl_NewFrame(GLUtils::window);
//
//	// 1. Show a simple window
//	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
//	{
//		static float f = 0.0f;
//		ImGui::Text("Hello, world!");
//		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
//		ImGui::ColorEdit3("clear color", (float*)&clear_color);
//		if (ImGui::Button("Test Window")) show_test_window ^= 1;
//		if (ImGui::Button("Another Window")) show_another_window ^= 1;
//		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//	}
//
//	// 2. Show another simple window, this time using an explicit Begin/End pair
//	if (show_another_window)
//	{
//		ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
//		ImGui::Begin("Another Window", &show_another_window);
//		ImGui::Text("Hello");
//		ImGui::End();
//	}
//
//	// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
//	if (show_test_window)
//	{
//		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
//		ImGui::ShowTestWindow(&show_test_window);
//	}




}

//=========================================================================================================================
void Main::render()
{//=========================================================================================================================

	glClear(GL_COLOR_BUFFER_BIT);

	stateManager->render();

	GLUtils::setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	console->render();

	if (error_console_on)ERROR_draw_error_console();
	DEBUG_draw_overlays();

	//ImGui::Render();

	

}


//=========================================================================================================================
void Main::mainLoop()
{ //=========================================================================================================================

	log.info("Begin Main Loop...");

	while (quit == false)
	{
		//------------------------------
		//END OLD MAIN LOOP
		//------------------------------
		System::updateRenderTimers();
		System::updateDebugInfo();

		//GLUtils::e();

		//        if (serversAreShuttingDown)
		//        {
		//            GLUtils::drawFilledRect(0, 0, 0, 0, GLUtils::getViewportWidth(), 0, GLUtils::getViewportHeight(), 0.2f);
		//            GLUtils::drawOutlinedString("The servers are shutting down soon for updating.", GLUtils::getViewportWidth() / 2 - 60, GLUtils::getViewportHeight() / 2 - 12, Color::white);
		//        }


		//		if (GLUtils::isActive() == false && debugMode == false)
		//		{
		//			GLUtils::drawFilledRect(0, 0, 0, 0, (float)GLUtils::getViewportWidth(), 0, (float)GLUtils::getViewportHeight(), 0.5f);
		//			GLUtils::drawOutlinedString("Low power mode. Click to resume.", (float)GLUtils::getViewportWidth() / 2 - 70, (float)GLUtils::getViewportHeight() / 2 - 12, Color::white);
		//
		//			Sleep(16 * 3);//skip 3 frames
		//
		//			if (GLUtils::isVisible())
		//			{
		//				update();
		//				render();
		//				SDL_GL_SwapWindow(GLUtils::window);
		//			}
		//			else
		//			{
		//				GLUtils::processMessages();
		//			}
		//		}
		//		else
		{
			if (GLUtils::usingVSync == true)
			{
				System::updateUpdateTimers();
				//this just lowers cpu usage
				//Sleep(2); //TODO: vary this based on system speed
				update();
				render();
				SDL_GL_SwapWindow(GLUtils::window);
				//System::framesrendered++;
			}
			else
			{

				if (GLUtils::noVSync_UpdateAndRenderEveryFrame || System::getTotalRenderTicksPassed() >= 16)
				{
					System::resetTotalRenderTicksPassed();
					System::updateUpdateTimers();
					update();
					render();
					SDL_GL_SwapWindow(GLUtils::window);
					//System::framesrendered++;
				}
				else
				{
					render();
					SDL_GL_SwapWindow(GLUtils::window);
					//System::framesrendered++;
				}

				//TODO: vary this based on system speed
				if (GLUtils::noVSync_DelayOff == false)SDL_Delay(2);

				/*
				try
				{
					//this actually regulates framerate
					Thread.sleep(6);//16);//TODO: vary this based on system speed

					//no ghost thread
					//30 = 30 fps solid, jitter but no stutter, very smooth though **(same for with ghost thread)

					//ghost thread
					//8 = ~ 120-125 fps, starting to get a little bit of stutter
					//7 = ~ 130-140 fps, no stutter, tiny bit choppy for some reason
					//6 = ~ 150 fps, no stutter
					//5 = ~ 200 fps, no stutter
					//4 = ~ 250 fps, no stutter

					//1 = 950 fps, very smooth

					Thread.yield();

				}
				catch(Exception e){e.printStackTrace();}
				*/
			}

			//System::calculate_fps();

			GLUtils::e("End main loop");
		}

		GLUtils::e();
	}
}

bool Main::screenShotKeyPressed = false;
bool Main::resize = false;

//=========================================================================================================================
void Main::doResizeCheck()
{ //=========================================================================================================================

	if ((controlsManager->KEY_RALT_HELD && controlsManager->key_RETURN_Pressed()) || controlsManager->key_F11_Pressed())
	{
		GLUtils::toggleFullscreen();
	}

	if (resize == true)
	{
		resize = false;

		//reset GL model matrix, etc.

		log.info("Resized window.");

		GLUtils::doResize();
	}
}

//=========================================================================================================================
void Main::doScreenShotCheck()
{ //=========================================================================================================================


	bool takeScreenShot = false;

	if (controlsManager->key_PRINTSCREEN_Pressed() || controlsManager->key_F12_Pressed())
	{
		if (screenShotKeyPressed == false)
		{
			screenShotKeyPressed = true;
			takeScreenShot = true;
		}
	}
	else
	{
		screenShotKeyPressed = false;
	}


	if (takeScreenShot)
	{

		if (mainObject->gameEngine != nullptr)mainObject->gameEngine->audioManager->playSound("screenShot", 1.0f, 1.0f, 1);

		time_t t = time(0); // get time now 
		struct tm * now = localtime( & t ); 
		cout << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << endl;

		//string imageName = string("bobsgame-") + (new SimpleDateFormat("yyyy-MM-dd-HH-mm-ss"))->format(Calendar::getInstance().getTime()) + string(".png");
		string fileName = string(Main::getPath())+"screenshot"+to_string(now->tm_year + 1900)+to_string(now->tm_mon + 1) +to_string(now->tm_mday)+to_string(now->tm_hour) + to_string(now->tm_min) + to_string(now->tm_sec) +".png";

		//if (System::getProperty("os.name")->contains("Win"))
		{
			Console::add("Saved screenshot to "+ Main::getPath()+fileName, BobColor::green, 3000);
			//getFileName = System::getProperty("user.home") + "/" + string("Desktop") + "/" + imageName;
		}
		//  				else
		//  				{
		//  					Console::add("Saved screenshot in home folder.",Color::green,3000);
		//  					//getFileName = System::getProperty("user.home") + "/" + imageName;
		//  				}


		int w = GLUtils::getRealWindowWidth();
		int h = GLUtils::getRealWindowHeight();
		glReadBuffer(GL_FRONT);
		u8 *buffer = new u8[w * h * 4];
		glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		u8 *flipdata = new u8[w * h * 4];

		for (int y = 0; y<h; y++)
			for (int x = 0; x<w; x++)
			{
				flipdata[(((y*w) + x) * 4) + 0] = buffer[(((((h - 1) - y)*w) + x) * 4) + 0];//bgra
				flipdata[(((y*w) + x) * 4) + 1] = buffer[(((((h - 1) - y)*w) + x) * 4) + 1];
				flipdata[(((y*w) + x) * 4) + 2] = buffer[(((((h - 1) - y)*w) + x) * 4) + 2];//bgra
				flipdata[(((y*w) + x) * 4) + 3] = buffer[(((((h - 1) - y)*w) + x) * 4) + 3];

			}
		SDL_Surface *s = SDL_CreateRGBSurfaceFrom(flipdata, w, h, 32, w * 4, GLUtils::rmask, GLUtils::gmask, GLUtils::bmask, GLUtils::amask);// 0x0000FF00, 0x00FF0000, 0xFF000000, 0x000000FF);
		IMG_SavePNG(s, fileName.c_str());
		SDL_FreeSurface(s);
		delete[] buffer;
		delete[] flipdata;
	}


}


//==========================================================================================================================
void Main::printEvent(const SDL_Event* e)
{//==========================================================================================================================
	if (e->type == SDL_WINDOWEVENT)
	{
		switch (e->window.event)
		{
		case SDL_WINDOWEVENT_SHOWN:
			SDL_Log("Window %d shown", e->window.windowID);
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			SDL_Log("Window %d hidden", e->window.windowID);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_Log("Window %d exposed", e->window.windowID);
			break;
		case SDL_WINDOWEVENT_MOVED:
			SDL_Log("Window %d moved to %d,%d",
				e->window.windowID, e->window.data1,
				e->window.data2);
			break;
		case SDL_WINDOWEVENT_RESIZED:
			SDL_Log("Window %d resized to %dx%d",
				e->window.windowID, e->window.data1,
				e->window.data2);
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			SDL_Log("Window %d size changed to %dx%d",
				e->window.windowID, e->window.data1,
				e->window.data2);
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			SDL_Log("Window %d minimized", e->window.windowID);
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			SDL_Log("Window %d maximized", e->window.windowID);
			break;
		case SDL_WINDOWEVENT_RESTORED:
			SDL_Log("Window %d restored", e->window.windowID);
			break;
		case SDL_WINDOWEVENT_ENTER:
			SDL_Log("Mouse entered window %d",
				e->window.windowID);
			break;
		case SDL_WINDOWEVENT_LEAVE:
			SDL_Log("Mouse left window %d", e->window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			SDL_Log("Window %d gained keyboard focus",
				e->window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			SDL_Log("Window %d lost keyboard focus",
				e->window.windowID);
			break;
		case SDL_WINDOWEVENT_CLOSE:
			SDL_Log("Window %d closed", e->window.windowID);
			break;
		default:
			SDL_Log("Window %d got unknown event %d",
				e->window.windowID, e->window.event);
			break;
		}
	}
}



//==========================================================================================================================
void Main::processEvents()
{//==========================================================================================================================


	SDL_Event event;

	//While there are events to handle
	while (SDL_PollEvent(&event))
	{

		//printEvent(&event);


		//If the user has Xed out the window
		if (event.type == SDL_QUIT)
		{
			//Quit the program
			Main::quit = true;
		}
		else
			//Window event occured
			if (event.type == SDL_WINDOWEVENT)
			{
				switch (event.window.event)
				{
					//Get new dimensions and repaint on window size change
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				{
					//int width = event.window.data1;
					//int height = event.window.data2;
					resize = true;
				}
				break;

				//Repaint on exposure
				case SDL_WINDOWEVENT_EXPOSED:
					break;

					//Mouse entered window
				case SDL_WINDOWEVENT_ENTER:
					break;

					//Mouse left window
				case SDL_WINDOWEVENT_LEAVE:
					break;

					//Window has keyboard focus
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					break;

					//Window lost keyboard focus
				case SDL_WINDOWEVENT_FOCUS_LOST:
					break;

					//Window minimized
				case SDL_WINDOWEVENT_MINIMIZED:
					break;

					//Window maxized
				case SDL_WINDOWEVENT_MAXIMIZED:
					break;

					//Window restored
				case SDL_WINDOWEVENT_RESTORED:
					break;
				}
			}
			else
			{

				events.add(event);

				gwenInput->ProcessEvent(event);
				//ImGui_ImplSdl_ProcessEvent(&event);
			}

	}

}



//void OnResize(int w, int h) {
//
//   //textureWidth = (float)w;
//   //textureHeight = (float)h;
//
//   setGLWindow(w, h, Surf_Display);
//
//}
//bool setGLWindow(int width, int height, SDL_Surface * Surf_Display)
//{
//   if ((Surf_Display = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_RESIZABLE)) == NULL) {
//      return false;
//   }
//
//   glClearColor(0, 0, 0, 0);
//   glClearDepth(1.0f);
//
//   glViewport(0, 0, width, height);
//
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//
//   glOrtho(0, width, height, 0, 1, -1);
//
//   glMatrixMode(GL_MODELVIEW);
//
//   glEnable(GL_TEXTURE_2D);
//
//   glLoadIdentity();
//
//   return true;
//}


//==========================================================================================================================
void Main::doLegalScreen()
{ //=========================================================================================================================


  //
  //			if ((new File(FileUtils::cacheDir + string("session")))->exists() == false)
  //			{
  //
  //				{
  //				//if(BobNet.debugMode==false)
  //
  //					log.info("Legal Screen...");
  //
  //					LegalScreen *legalScreen = new LegalScreen();
  //					GUI *legalScreenGUI = new GUI(legalScreen, GLUtils::TWLrenderer);
  //					legalScreenGUI->applyTheme(GLUtils::TWLthemeManager);
  //
  //					while (legalScreen->getClickedOK_S() == false)
  //					{
  //
  //						glClear(GL_COLOR_BUFFER_BIT);
  //
  //
  //						legalScreen->update();
  //						legalScreenGUI->update();
  //
  //						if ((System::isCloseRequested() || (System::debugMode == true && Keyboard::isKeyDown(Keyboard::KEY_ESCAPE))) || legalScreen->getClickedCancel_S() == true)
  //						{
  //							legalScreen->destroy();
  //							GLUtils::TWLthemeManager->destroy();
  //							System::destroy();
  //							AL::destroy();
  //							Main::exit();
  //						}
  //
  //						System::sync(60);
  //						System::update();
  //						doResizeCheck();
  //
  //					}
  //
  //					legalScreen->destroy();
  //					glClear(GL_COLOR_BUFFER_BIT);
  //
  //					log.info("Accepted Legal Screen.");
  //
  //				}
  //
  //			}
}

//==========================================================================================================================
void Main::showControlsImage()
{ //=========================================================================================================================


  //
  //			if ((new File(FileUtils::cacheDir + string("session")))->exists() == false)
  //			{
  //
  //				{
  //				//if(BobNet.debugMode==false)
  //					KeyboardScreen *keyboardScreen = new KeyboardScreen();
  //					GUI *keyboardScreenGUI = new GUI(keyboardScreen, GLUtils::TWLrenderer);
  //					keyboardScreenGUI->applyTheme(GLUtils::TWLthemeManager);
  //
  //					keyboardScreen->okButton->setVisible(true);
  //					keyboardScreen->setActivated(true);
  //
  //					while (keyboardScreen->getClickedOK_S() == false)
  //					{
  //						glClear(GL_COLOR_BUFFER_BIT);
  //
  //
  //						keyboardScreen->update();
  //						keyboardScreenGUI->update();
  //
  //
  //						System::sync(60);
  //						System::update();
  //					}
  //					keyboardScreen->destroy();
  //					glClear(GL_COLOR_BUFFER_BIT);
  //				}
  //
  //			}
}

#undef INADDR_ANY       
#undef INADDR_LOOPBACK  
#undef INADDR_BROADCAST 
#undef INADDR_NONE      
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPCredentials.h"
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;

#include "Poco/FileStream.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/Net/FTPStreamFactory.h"
#include <memory>
#include <iostream>
using Poco::FileStream;
using Poco::URIStreamOpener;
using Poco::Net::HTTPStreamFactory;
using Poco::Net::FTPStreamFactory;

#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Delegate.h"
#include "Poco/Zip/Decompress.h"
#include "Poco/Process.h"
#include "Poco/DirectoryIterator.h"
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Process;
using Poco::Path;
using Poco::Delegate;
using Poco::Zip::Decompress;



//==========================================================================================================================
string Main::getPath()
{//==========================================================================================================================

	string exePath = string(SDL_GetBasePath());//this is where the .exe is run from.i.e. bobsgame/DebugVS/

	string cwd = Path::current();//this is the current working dir i.e. bobsgame/


	string versionTextPath = exePath + "version.txt";
	if (File(versionTextPath).exists() == false)
	{
		versionTextPath = cwd + "version.txt";
		if (File(versionTextPath).exists() == false)
		{
			versionTextPath = exePath + "../" + "version.txt";
			if (File(versionTextPath).exists() == false)
			{
				versionTextPath = cwd + "../" + "version.txt";
				if (File(versionTextPath).exists() == false)
				{
					log.error("Could not find version.txt in path");
					return "./";
				}
				return cwd + "../";
			}
			return exePath + "../";
		}
		else
		return cwd;
	}
	else return exePath;

}

#if defined(__LINUX__)
#include "stdlib.h"
#endif

//class ZipTest
//{
//public:
//	static void onDecompressError(const void* pSender, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string>& info)
//	{
//		
//
//	}
//};

//==========================================================================================================================
void Main::checkVersion()
{//==========================================================================================================================

	bool windows = false;
	bool macos = false;
	bool linux = false;

#if defined(__WINDOWS__)
	windows = true;
#endif
#if defined(__LINUX__)
	linux = true;
#endif
#if defined(__MACOSX__)
	macos = true;
#endif

	int localVersion = 0;

#if defined(__WINDOWS__) || defined(__LINUX__) || defined(__MACOSX__)
    /*
     dyld: Symbol not found: _clock_gettime
     Referenced from: /usr/local/lib/libPocoFoundationd.45.dylib (which was built for Mac OS X 10.12)
     Expected in: /usr/lib/libSystem.B.dylib
     */


	//if not in itch
	string exePath = string(SDL_GetBasePath());
	log.debug("SDL_GetBasePath(): " + exePath);//this is where the .exe is run from.i.e. bobsgame/DebugVS/

	string pocoPath = Path::current();
	log.debug("Poco::Path::current():" + pocoPath);//this is the current working dir i.e. bobsgame/


	log.debug("SDL_GetPrefPath():" + string(SDL_GetPrefPath("Bob Corporation", "bob's game")));
	log.debug("Poco::Path::home():" + Path::home());


	if (exePath.find("itch") != std::string::npos) 
	{
		log.debug("'itch' found in path, skipping version check.");
	}
	else
	if(exePath.find("steam") != std::string::npos)
	{
		log.debug("'steam' found in path, skipping version check.");
	}
	else
	if (exePath.find("Steam") != std::string::npos)
	{
		log.debug("'Steam' found in path, skipping version check.");
	}
	else
	{

		try
		{
			File f(exePath+"bobsgame.old");
			if (f.exists())
			{
				f.remove();
				//Caption* c = 
				//((Engine*)(getMain()->stateManager->getState()))->captionManager->newManagedCaption((int)(Caption::CENTERED_SCREEN), 0, 5000, "Update installed!", BobFont::ttf_oswald_32, BobColor::green, BobColor::clear, RenderOrder::OVER_GUI);
				//doesn't go away because we're not updating captionManager??

				Caption* c = new Caption(nullptr, (int)(Caption::CENTERED_SCREEN), 0, -1, "Update installed!", BobFont::ttf_16, BobColor::white, BobColor::clear);

				for (int i = 0; i < 40; i++)
				{
					System::updateRenderTimers();
					System::updateDebugInfo();
					System::updateUpdateTimers();
					c->update();
					c->render();
					SDL_GL_SwapWindow(GLUtils::window);
					SDL_Delay(100);
				}

			}
		}
		catch (Exception)
		{
			log.error("Error deleting bobsgame.old");
		}
		

		string versionTextPath = getPath() + "version.txt";
		if(File(versionTextPath).exists()==false)
		{
			log.error("Could not find version.txt");
			return;
		}

		//load version.txt, read number
		string versionString = FileUtils::loadTextFileFromExePathAndTrim("version.txt");
		log.debug("Local version:" + versionString);
		Main::version = versionString;
		try
		{
			localVersion = stoi(versionString);
		}
		catch (exception)
		{
			log.error("Could not parse localVersion");
			return;
		}

		string serverString = "";

		try
		{
			//check bobsgame.com/version.php?
			URI uri("http://bobsgame.com/version.php");
			string path(uri.getPathAndQuery());
			if (path.empty()) path = "/";

			HTTPClientSession session(uri.getHost(), uri.getPort());
			session.setTimeout(Poco::Timespan(4, 0));
			HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
			HTTPResponse response;

			session.sendRequest(request);
			istream& rs = session.receiveResponse(response);
			//cout << response.getStatus() << " " << response.getReason() << endl;

				
			StreamCopier::copyToString(rs, serverString);
			log.debug("Server version:" + serverString);
		}
		catch(Exception)
		{
			log.warn("Could not check version, no network connectivity?");
			return;
		}

	
		int serverVersion = -1;
		try
		{
			serverVersion = stoi(serverString);
		}
		catch (exception)
		{
			log.error("Could not parse serverVersion");
			return;
		}

		if (serverVersion > localVersion)
		{
			Console::add("Your version is out of date!", BobColor::red);
			Console::add("Your version: " + versionString, BobColor::red);
			Console::add("Latest version: " + serverString, BobColor::red);

			//bobsgame.exe can update itself, download latest.zip, rename itself, unzip in directory and overwrite, reopen itself, exit
			//in linux it doesnt even have to rename itself
			//in mac os who knows

			string exename = "";
			string zipname = "";
			if (windows)
			{

				exename = "bobsgame.exe";
				zipname = "http://bobsgame.com/latestWindows.zip";
			}

			if (macos)
			{
				exename = "bobsgame";
				zipname = "http://bobsgame.com/latestMacOS.zip";
			}

			if(linux)
			{
				exename = "bobsgame";
				zipname = "http://bobsgame.com/latestLinux.zip";
			}


			//if not in correct path quit
			if(File(exePath + exename).exists()==false)
			{
				log.error(exename+" not found in path:"+exePath);
				return;
			}


			//Caption* c = ((Engine*)(getMain()->stateManager->getState()))->captionManager->newManagedCaption((int)(Caption::CENTERED_SCREEN), 0, -1, "Update available! Press Space to download, Esc to skip.", BobFont::ttf_oswald_16, BobColor::white, BobColor::clear);
			Caption* c = new Caption(nullptr, (int)(Caption::CENTERED_SCREEN), 0, -1, "Update available! Press Space to download, Esc to skip.", BobFont::ttf_16, BobColor::white, BobColor::clear);
			System::updateRenderTimers();
			System::updateDebugInfo();
			System::updateUpdateTimers();
			c->update();
			c->render();
			SDL_GL_SwapWindow(GLUtils::window);

			bool skip = false;
			bool stop = false;
			while (stop == false)
			{
				getMain()->processEvents();
				getMain()->stateManager->getState()->resetPressedButtons();
				getMain()->stateManager->getState()->setButtonStates();

				if(controlsManager->key_SPACE_Pressed())
				{
					stop = true;
				}

				if (controlsManager->key_ESC_Pressed())
				{
					stop = true;
					skip = true;
				}
			}

			delete c;

			if (skip)return;

			//put caption in middle of screen, updating, press esc to skip
			log.info("Downloading update...");
			//c = ((Engine*)(getMain()->stateManager->getState()))->captionManager->newManagedCaption((int)(Caption::CENTERED_SCREEN), 0, -1, "Downloading update...", BobFont::ttf_oswald_32, BobColor::white, BobColor::clear);
			c = new Caption(nullptr,(int)(Caption::CENTERED_SCREEN), 0, -1, "Downloading update...", BobFont::ttf_16, BobColor::white, BobColor::clear);
			//Caption* c = ((Engine*)(getMain()->stateManager->getState()))->captionManager->newManagedCaption((int)(Caption::CENTERED_SCREEN), 0, -1, "Downloading update...", BobFont::ttf_oswald_32, Color::white, Color::black,RenderOrder::OVER_GUI);

			glClear(GL_COLOR_BUFFER_BIT);
			//Main::delay(100); //bobsGame doesn't render captionManager
			System::updateRenderTimers();
			System::updateDebugInfo();
			System::updateUpdateTimers();
			c->update();
			c->render();
			SDL_GL_SwapWindow(GLUtils::window);


			//download bobsgame.com/latestWindows.zip to working dir
			try
			{

				HTTPStreamFactory::registerFactory();

					
				URI zipuri(zipname);

				HTTPClientSession session(zipuri.getHost(), zipuri.getPort());
				string path(zipuri.getPathAndQuery());
				HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
				HTTPResponse response;
				session.setTimeout(Poco::Timespan(20, 0));
				session.sendRequest(request);
				//std::istream& rs =
                session.receiveResponse(response);
				//int contentlen = (int)response.getContentLength();


				FileStream fs(exePath + "update.zip", ios::out | ios::trunc | ios::binary);
				std::auto_ptr<std::istream> pStr(URIStreamOpener::defaultOpener().open(zipuri));
				StreamCopier::copyStream(*pStr.get(), fs);
				fs.close();
			}
			catch (Exception)
			{
				//std::cerr << exc.displayText() << std::endl;
				log.error("Could not download latest zip");
				c->setToBeDeletedImmediately();
				delete c;

				return;
			}

			try
			{

				
				//move all files to /old

				//delete /old at start

				//rename bobsgame.exe
				File(exePath + exename).renameTo(exePath + "bobsgame.old");
				File(exePath + exename).copyTo(exePath + exename);

			}
			catch (Exception)
			{
				log.error("Could not rename "+ exename);
			}

			try
			{
				//unzip latestZip to temp


#if defined(__LINUX__)
				int result = system(string("unzip \"" + exePath + "update.zip\"").c_str());
#else
				std::ifstream inp(exePath + "update.zip", std::ios::binary);
				//log.info("Opened ifstream");
				poco_assert(inp);
				//log.info("Assert ifstream");
				
				Decompress dec(inp, Poco::Path(exePath));
				//log.info("Create decompress object");
				//dec.EError += Poco::Delegate<ZipTest, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string> >(this, &ZipTest::onDecompressError);
				dec.decompressAllFiles();
				//dec.EError -= Poco::Delegate<ZipTest, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string> >(this, &ZipTest::onDecompressError);
				//log.info("decompressAllFiles();");
				inp.close();
				//log.info("close()");
#endif






			}
			catch (Exception)
			{
				log.error("Could not unzip update.zip");
			}

			//delete update.zip
			try
			{
				File(exePath + "update.zip").remove();
			}
			catch (Exception)
			{
				log.error("Could not delete update.zip");
			}
			try
			{

#if defined(__LINUX__) || defined(__MACOSX__)
                //int result =
                system(string("chmod 755 "+exePath + exename).c_str());
#endif
				//open bobsgame.exe
				File f = File(exePath + exename);
				if (f.exists() && f.canExecute())
				{
					c->setToBeDeletedImmediately();
					c->update();

					//Args args;
					std::vector<std::string> args;
					Process::launch(exePath + exename, args);
					//quit
					exit(0);
				}
				else
				{
					c->setText("Something went wrong while updating.  Please download manually.");
					c->update();
					c->render();
					SDL_GL_SwapWindow(GLUtils::window);

					log.error("Something went wrong while updating.  Please download manually.");
					SDL_Delay(5000);
					exit(0);
				}

			}
			catch (Exception)
			{
				log.error("Could not run "+ exename);
			}
		}
	}
#endif



#if defined(__WINDOWS__) && defined(_DEBUG)
	//open version.txt
	//increment it
	//save it back
	if (localVersion != 0)
	{
		int newVersion = localVersion + 1;

		ofstream outputFile;
		outputFile.open("version.txt", ofstream::out);//leave this without runpath, will always be run in windows debug in the proper cwd /bobsgame/
		outputFile << newVersion;
		outputFile.close();

		log.debug("Saved new version: " + to_string(newVersion));
	}
#endif

}

//==========================================================================================================================
void Main::makeGhostThread()
{ //=========================================================================================================================

  //			//ghost thread to prevent stuttering
  //			//this is due to windows aero, for some reason creating a ghost thread prevents it for some fucking reason
  //			new Thread([&] ()
  //			{
  //					try
  //					{
  //						Thread::currentThread().setName("ClientMain_ghostThreadToPreventAeroStutter");
  //					}
  //					catch (SecurityException e)
  //					{
  //						e->printStackTrace();
  //					}
  //
  //					while (exit == false)
  //					{
  //						try
  //						{
  //							delay(16); //this only seems to work at 16
  //
  //							//Thread.yield(); //high cpu usage
  //							//if(Display.isActive()==false)Display.processMessages();
  //						}
  //						catch (exception &e)
  //						{
  //							e.printStackTrace();
  //						}
  //					}
  //			}
  //		   ).start();
}



//==========================================================================================================================
void Main::cleanup()
{//=========================================================================================================================



	log.info("Cleaning up...");


	AudioManager::cleanup();



	ControlsManager::cleanup();


	if (gameEngine != nullptr)
	{
		gameEngine->cleanup(); 
		delete gameEngine;
	}
	if (bobsGame != nullptr) 
	{
		bobsGame->cleanup();
		delete bobsGame;
	}
	BobFont::cleanup();
	GLUtils::cleanup();
	delete bobNet;

	SDLNet_Quit();
	//enet_deinitialize();

	log.info("Exiting...");
	SDL_Quit();


}

////==========================================================================================================================
//BGClientEngine* Main::getGameEngine()
//{//==========================================================================================================================
//	return gameEngine;
//}


//==========================================================================================================================
Main* Main::getMain()
{//==========================================================================================================================
	return mainObject;
}

//==========================================================================================================================
void Main::setMain(Main* c)
{//==========================================================================================================================
	mainObject = c;
}

//
//#define USE_ZLIB_MINIZIP 1
//
//#ifdef USE_ZLIB_MINIZIP
//
//
//#define dir_delimter '/'
//#define MAX_FILENAME 2048
//#define READ_SIZE 8192
//
//void Main::unZip(string file)
//{
//	// Open the zip file
//	unzFile *zipfile = unzOpen(file);
//	if (zipfile == NULL)
//	{
//		printf("%s: not found\n");
//		return -1;
//	}
//
//	// Get info about the zip file
//	unz_global_info global_info;
//	if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
//	{
//		printf("could not read file global info\n");
//		unzClose(zipfile);
//		return -1;
//	}
//
//	// Buffer to hold data read from the zip file.
//	char read_buffer[READ_SIZE];
//
//	// Loop to extract all files
//	uLong i;
//	for (i = 0; i < global_info.number_entry; ++i)
//	{
//		// Get info about current file.
//		unz_file_info file_info;
//		char filename[MAX_FILENAME];
//		if (unzGetCurrentFileInfo(
//			zipfile,
//			&file_info,
//			filename,
//			MAX_FILENAME,
//			NULL, 0, NULL, 0) != UNZ_OK)
//		{
//			printf("could not read file info\n");
//			unzClose(zipfile);
//			return -1;
//		}
//
//		// Check if this entry is a directory or file.
//		const size_t filename_length = strlen(filename);
//		if (filename[filename_length - 1] == dir_delimter)
//		{
//			// Entry is a directory, so create it.
//			printf("dir:%s\n", filename);
//			mkdir(filename);
//		}
//		else
//		{
//			// Entry is a file, so extract it.
//			printf("file:%s\n", filename);
//			if (unzOpenCurrentFile(zipfile) != UNZ_OK)
//			{
//				printf("could not open file\n");
//				unzClose(zipfile);
//				return -1;
//			}
//
//			// Open a file to write out the data.
//			FILE *out = fopen(filename, "wb");
//			if (out == NULL)
//			{
//				printf("could not open destination file\n");
//				unzCloseCurrentFile(zipfile);
//				unzClose(zipfile);
//				return -1;
//			}
//
//			int error = UNZ_OK;
//			do
//			{
//				error = unzReadCurrentFile(zipfile, read_buffer, READ_SIZE);
//				if (error < 0)
//				{
//					printf("error %d\n", error);
//					unzCloseCurrentFile(zipfile);
//					unzClose(zipfile);
//					return -1;
//				}
//
//				// Write data to file.
//				if (error > 0)
//				{
//					fwrite(read_buffer, error, 1, out); // You should check return of fwrite...
//				}
//			} while (error > 0);
//
//			fclose(out);
//		}
//
//		unzCloseCurrentFile(zipfile);
//
//		// Go the the next entry listed in the zip file.
//		if ((i + 1) < global_info.number_entry)
//		{
//			if (unzGoToNextFile(zipfile) != UNZ_OK)
//			{
//				printf("cound not read next file\n");
//				unzClose(zipfile);
//				return -1;
//			}
//		}
//	}
//
//	unzClose(zipfile);
//}
//#endif

//
//#define USE_MINIZ
//
//#ifdef USE_MINIZ
//
//#include "../lib/miniz-master/tinfl.c"
//#include <stdio.h>
//#include <limits.h>
//
//typedef unsigned char uint8;
//typedef unsigned short uint16;
//typedef unsigned int uint;
//
//#define my_max(a,b) (((a) > (b)) ? (a) : (b))
//#define my_min(a,b) (((a) < (b)) ? (a) : (b))
//
//static int tinfl_put_buf_func(const void* pBuf, int len, void *pUser)
//{
//	return len == (int)fwrite(pBuf, 1, len, (FILE*)pUser);
//}
//
//int Main::unZip(string file)
//{
//
//	int status;
//	FILE *pInfile, *pOutfile;
//	uint infile_size, outfile_size;
//	size_t in_buf_size;
//	uint8 *pCmp_data;
//	long long file_loc;
//
////	if (argc != 3)
////	{
////		printf("Usage: example4 infile outfile\n");
////		printf("Decompresses zlib stream in file infile to file outfile.\n");
////		printf("Input file must be able to fit entirely in memory.\n");
////		printf("example3 can be used to create compressed zlib streams.\n");
////		return EXIT_FAILURE;
////	}
//
//	// Open input file.
//	pInfile = fopen(file.c_str(), "rb");
//	if (!pInfile)
//	{
//		printf("Failed opening input file!\n");
//		return EXIT_FAILURE;
//	}
//
//	// Determine input file's size.
//	fseek(pInfile, 0, SEEK_END);
//	file_loc = ftell(pInfile);
//	fseek(pInfile, 0, SEEK_SET);
//
////	if ((file_loc < 0))// || (file_loc > INT_MAX))
////	{
////		// This is not a limitation of miniz or tinfl, but this example.
////		printf("File is too large to be processed by this example.\n");
////		return EXIT_FAILURE;
////	}
//
//	infile_size = (uint)file_loc;
//
//	pCmp_data = (uint8 *)malloc(infile_size);
//	if (!pCmp_data)
//	{
//		printf("Out of memory!\n");
//		return EXIT_FAILURE;
//	}
//	if (fread(pCmp_data, 1, infile_size, pInfile) != infile_size)
//	{
//		printf("Failed reading input file!\n");
//		return EXIT_FAILURE;
//	}
//
//	// Open output file.
//	pOutfile = fopen(file.c_str(), "wb");
//	if (!pOutfile)
//	{
//		printf("Failed opening output file!\n");
//		return EXIT_FAILURE;
//	}
//
//	printf("Input file size: %u\n", infile_size);
//
//	in_buf_size = infile_size;
//	status = tinfl_decompress_mem_to_callback(pCmp_data, &in_buf_size, tinfl_put_buf_func, pOutfile, TINFL_FLAG_PARSE_ZLIB_HEADER);
//	if (!status)
//	{
//		printf("tinfl_decompress_mem_to_callback() failed with status %i!\n", status);
//		return EXIT_FAILURE;
//	}
//
//	outfile_size = ftell(pOutfile);
//
//	fclose(pInfile);
//	if (EOF == fclose(pOutfile))
//	{
//		printf("Failed writing to output file!\n");
//		return EXIT_FAILURE;
//	}
//
//	printf("Total input bytes: %u\n", (uint)in_buf_size);
//	printf("Total output bytes: %u\n", outfile_size);
//	printf("Success.\n");
//	return EXIT_SUCCESS;
//	}
//#endif
