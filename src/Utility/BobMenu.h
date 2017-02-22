
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
#include <src/Engine/EnginePart.h>
#include "Color.h"
#include "Caption.h"
#include "gl/GLUtils.h"



//class BobSubMenu;
//=========================================================================================================================
class BobMenu : public EnginePart
{//=========================================================================================================================
public:
	//do autofit/scrolling, only scroll menu items below info captions

	//do render within xywh

	//add graphic

	//gl draw ratio fit between height or width

	TTF_Font *font = BobFont::ttf_oswald_24;

	static BobColor* menuColor;
	static BobColor* disabledMenuColor;
	static BobColor* warningMenuColor;
	static BobColor* clearColor;
	static BobColor* infoColor;
	static BobColor* statusColor;
	static BobColor* errorColor;
	static BobColor* bgColor;

	Caption* titleCaption = nullptr;
	


	int cursorPosition = 0;
	static BobTexture* rectangleCursorTexture;
	static BobTexture* cursorTexture;
	static BobTexture* upCursorTexture;
	static BobTexture* downCursorTexture;
	static long long cursorInOutToggleTicks;
	static bool cursorInOutToggle;


	long long rectangleCursorPulseLastTime = 0;
	int rectangleCursorPulsePeriodTicks = 300;
	float rectangleCursorPulseFromAlpha = 0.1f;
	float rectangleCursorPulseToAlpha = 0.2f;
	float rectangleCursorPulseCurrentAlpha = 0.2f;
	bool rectangleCursorPulseInOut = false;
	long long rectangleCursorMovementLastTime = 0;
	int rectangleCursorMovementPeriodTicks = 60;
	float rectangleCursorFromY = 0;
	float rectangleCursorToY = 0;
	float rectangleCursorCurrentY = 0;
	
	static ArrayList<BobMenu*> activeMenus;

	BobTexture *graphic = nullptr;
	float spacing = 1.0f;
	bool center = true;
	
	int graphicWidth = 0;
	int graphicYStartPosition = 0;
	
	//=========================================================================================================================
	class MenuItem
	{//=========================================================================================================================
	public:
		Caption* caption = nullptr;
		string id = "";
		BobColor *color = nullptr;
		bool hidden = false;
		bool info = false;
		bool isYesNoType = false;
		bool yesNoValue = true;
		string captionText = "";

		//BobSubMenu *subMenu = nullptr;

		~MenuItem();
		void setYesNo(bool yesNo);
		void toggle();
		void setColor(BobColor* color);
		void setText(string s);
	};

	ArrayList<MenuItem*> menuItems;

	BobMenu(Engine *g, string title);
	~BobMenu();

	void setGraphic(BobTexture* t, int graphicWidth, int graphicYStartPosition);
	void clear();
	void setAllCaptionsToFullAlpha();
	static void update(int ticksPassed);

private:
	bool areAllMenusDisabled();
public:

	void up(bool noSound = false);
	void down(bool noSound = false);
	MenuItem* addInfo(string caption, string id = "", BobColor *color = infoColor);
	virtual MenuItem* add(string caption, string id = "", BobColor *color = menuColor);
	virtual MenuItem* addYesNo(string caption, bool yesNo);

	int getAmountOfMenuItems();
	//returns bottom of graphic y position
	void render(int y = 0, int x = 0, int endY = GLUtils::getViewportHeight(), bool drawCursor = true, int* returnBottomOfGraphic = nullptr, int* returnBottomOfCaptions = nullptr, bool renderBackgroundAndBorder = false, int* returnLeftX = nullptr, int* returnRightX = nullptr);
	void setHidden(string id, bool b);
	void setAllInvisible();
	void setAllVisible();
	bool isSelectedID(string id, bool clicked = false, int mx = 0, int my = 0);
	void setSelectedID(string id);
	Caption* getCaptionByID(string id);
	MenuItem* getMenuItemByID(string id);
	MenuItem* getSelectedMenuItem();


	//bool cancelToQuit = true;
	//bool confirmToConfirm = true;
	//bool *onQuitToggle;


	//	//=========================================================================================================================
	//	BobSubMenu* addSubMenu(string caption, string id, BobsGame *b, void(*f) (BobsGame*, string))
	//	{//=========================================================================================================================
	//		
	//
	//
	//
	//	}

};
//
////=========================================================================================================================
//class BobSubMenu : public BobMenu
//{//=========================================================================================================================
//public:
//	BobMenu *parentMenu = nullptr;
//	BobsGame *bobsGame = nullptr;
//	void (*callBack)(BobsGame*, string) = nullptr;
//	bool isOpen = false;
//
//	BobSubMenu(Engine *g) : BobMenu(g, "")
//	{
//		
//	}
//	~BobSubMenu()
//	{
//		
//	}
//	virtual MenuItem* add(string caption, string id = "", BobColor *color = menuColor)
//	{
//		MenuItem * m = BobMenu::add(caption, id, color);
//		menuItems->get(menuItems->size()-1)->caption->visible = false;
//		return m;
//
//	}
//	void onSelected()
//	{
//		if(callBack!=nullptr)callBack(bobsGame, getSelectedMenuItem()->id);
//	}
//
//
//};


