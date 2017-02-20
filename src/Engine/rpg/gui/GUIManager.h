//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;





#include "../../state/KeyboardScreen.h"


class GUIManager : public EnginePart
{
public:

	static Logger log;


	StuffMenu* stuffMenu = nullptr;
	//GUI* stuffMenuGUI = nullptr;

	GameStore* gameStore = nullptr;
	//GUI* gameStoreGUI = nullptr;

	PlayerEditMenu* playerEditMenu = nullptr;
	//GUI* playerEditGUI = nullptr;

	ArrayList<GameChallengeNotificationPanel*>* gameChallenges = new ArrayList<GameChallengeNotificationPanel*>();
	//ArrayList<GUI*> gameChallengesGUIs;

	KeyboardScreen* keyboardScreen = nullptr;
	//GUI* keyboardScreenGUI;


	//this panel (with plate)
	static string lightThemeString;
	static string darkThemeString;


	//child panel (with plate)
	static string subMenuPanelDialogLayoutTheme;

	//scrollpane here

	//panel inside scrollpane
	static string emptyDialogLayoutTheme;

	static string buttonTheme;
	static string checkboxTheme;
	static string scrollPaneTheme;

	bool lightTheme = false;


	GUIManager(BGClientEngine* g);


	virtual void init();


	virtual void update();


	virtual void render();


	//The following method was originally marked 'synchronized':
	virtual GameChallengeNotificationPanel* makeGameChallengeNotification(FriendCharacter* friend_in, const string& gameName);


	virtual void removeGameNotification(GameChallengeNotificationPanel* g);


	virtual void cleanup();


	virtual void setDarkTheme();


	virtual void setLightTheme();


	virtual void openND();


	virtual void closeND();


	virtual void openGameStore();


	virtual void openSettingsMenu();


	virtual void openFriendsMenu();


	virtual void openStatusMenu();


	virtual void openLogMenu();


	virtual void openItemsMenu();


	virtual void openStuffMenu();


	virtual void enableAllMenusAndND();


	virtual void disableAllMenusAndND();


	virtual void closeAllMenusAndND();
};

