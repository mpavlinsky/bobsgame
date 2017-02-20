//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "NDMenuBackground.h"
#include "NDMenuWheel.h"

class NDMenu : public NDGameEngine
{
private:
	typedef NDGameEngine super;
public:
	static Logger log;

	NDMenu();
	virtual ~NDMenu();
	NDMenu(ND* nD);
	virtual void init();

	bool runSelectedGame = false;
	int quit = 0;


	NDMenuWheel* wheel = new NDMenuWheel(this);
	NDMenuBackground* background = new NDMenuBackground(this);


	BobColor* WHITE = new BobColor(255, 255, 255);
	BobColor* BLACK = new BobColor(0, 0, 0);
	BobColor* RED = new BobColor(255, 0, 0);
	BobColor* GREEN = new BobColor(0, 255, 0);
	BobColor* BLUE = new BobColor(0, 0, 255);
	BobColor* MAGENTA = new BobColor(255, 0, 255);
	BobColor* YELLOW = new BobColor(0, 127, 127);


	static bool actionButtonPressed;
	long long buttonHeldTicks = 0;

	bool downButtonPressed = false;
	bool rightButtonPressed = false;
	bool upButtonPressed = false;
	bool leftButtonPressed = false;

	int ticksSinceDownPressed = 0;
	int ticksSinceRightPressed = 0;
	int ticksSinceUpPressed = 0;
	int ticksSinceLeftPressed = 0;

	long long ticks_since_down_repeat = 0;
	long long ticks_since_right_repeat = 0;
	long long ticks_since_up_repeat = 0;
	long long ticks_since_left_repeat = 0;

	long long currentTicks = 0;
	long long lastTicks = 0;

	static int actionFadeCountSwitch;

	int showMovie = 0;
	int movieSelected = 1;
	static bool directionButtonPressed;
	bool directionButtonUnpressed = false;


	static int actionFadeCounter;

	int fadeDirection = 0;
	long long fadeOutTicks = 0;


	virtual void addGame(NDGameEngine* game, const string& name, BobColor* color);
	virtual void update() override;
	virtual void cleanup() override;
	virtual void render() override;
	virtual void handleInput();
	virtual void updateVideo();
	virtual void renderVideo();
	virtual void fillScreenBlack(float a);
	virtual void fillScreenWhite(float a);
	virtual void drawScreenOverlayFade();
};

