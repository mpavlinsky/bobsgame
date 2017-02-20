//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



class TextWindow;

class TextManager : public EnginePart
{ // =========================================================================================================================


public:
	static Logger log;

	//static TrueTypeFont* ttfFont;


	static string debugtext1;
	static string debugtext2;
	static string debugtext3;
	static string debugtext4;


private:
	bool antiAlias = true;


public:
	ArrayList<TextWindow*>* textBox = new ArrayList<TextWindow*>();



	int width = 64 * 6 * 2; // *2 because we draw everything at 2x to allow for scaling (and higher res 1x unicode fonts)
	int height = 64 * 2;

	int pow2TexWidth = 0;
	int pow2TexHeight = 0;

	int spriteWindowWidth = 64 * 2;

	// public int line_size_x=size_x/2; //because the getText box is drawn at 2x (so the texture scales nicely if i zoom it in or out)

	int MAX_LINES = 4;


	string currentText = "";
	int length = 0;
	int position = 0;


	const static int CLOSED = 0;
	const static int OPEN = 1;
	const static int CLOSING = 2;
	const static int ANSWER_BOX_ON = 3;
	const static int ANSWER_BOX_CLOSING = 4;
	const static int KEYBOARD_CLOSING = 5;
	const static int KEYBOARD_ON = 6;

	int textEngineState = CLOSED;


	const static int BOTTOM = 0;
	const static int TOP = 1;

	int selectedTextbox = BOTTOM;

	bool topBoxActivated = false;


	bool keepOpenForNewText = false;
	bool waitingForButtonForNewPage = false;
	bool pausedUntilButtonPress = false;
	bool waitingForCancelButtonUnpress = false;
	bool cannotCancel = false;
	bool waitingForButtonPressToClose = false;
	bool waitingForUnpress = false;
	bool buttonAUnpressed = false;
	bool buttonIconIsOn = false;
	bool scrollingUp = false;


	bool delay = false;
	int delayTicks = 0;


	BobFont* font = nullptr; // this isn't per-getText window because we want to share the state across the boxes. is that right, or would per-box be better?
	BobColor* textColor = BobColor::white;
	BobColor* textBGColor = BobColor::black;
	BobColor* textAAColor = BobColor::gray;
	BobColor* textShadowColor = BobColor::darkGray;

	BobColor* tC0 = BobColor::black;
	BobColor* tC1 = BobColor::white;
	BobColor* tC2 = BobColor::gray;
	BobColor* tC3 = BobColor::darkGray;

	bool skipText = false;


	bool buttonIconUpDownToggle = false;
	int buttonTimer = 0;
	BobTexture* buttonTexture;
	// TODO: load button texture, draw where appropriate during render


	int MAX_ANSWER_LENGTH = 255;


	Entity* optionTargetEntity1 = nullptr;
	Entity* optionTargetEntity2 = nullptr;
	Entity* optionTargetEntity3 = nullptr;
	Entity* optionTargetEntity4 = nullptr;
	Entity* optionTargetEntity5 = nullptr;
	Entity* optionTargetEntity6 = nullptr;


	int cursorTicks = 0;
	bool cursorPixelUpDownToggle = true;
	float answerBoxY = 0;
	int numberOfAnswers = 0;
	int selectedAnswer = 0;

	ScreenSprite* cursorScreenSprite = nullptr;
	float keyboardY = 0;
	ScreenSprite* keyboardScreenSprite = nullptr;
	ScreenSprite* actionIconScreenSprite = nullptr;
	string optionBuffer;


	//public float BOTTOM_ACTIVE_POSITION_Y=5000;
	//public float BOTTOM_INACTIVE_POSITION_Y=5000;
	//public float TOP_ACTIVE_POSITION_Y=5000;
	//public float TOP_INACTIVE_POSITION_Y=5000;
	//public float POSITION_X=5000;

	static BobTexture* questionMarkTexture;


	//public long textEngineSpeedTicksPerLetter=10;
	//public long drawLetterTicksCounter=100;


	// =========================================================================================================================
	TextManager(Engine* g);


	// =========================================================================================================================
	virtual bool isTextBoxOpen();


	// =========================================================================================================================
	virtual bool isTextAnswerBoxOpen();


	// =========================================================================================================================
	virtual void init();


	// =========================================================================================================================
	virtual void reset();


	// =========================================================================================================================
	virtual void text(const string& s);


	// =========================================================================================================================
	virtual void render();


	// =========================================================================================================================
	virtual int getLineSizeX();


	// =========================================================================================================================
	virtual void update();


	// =========================================================================================================================
	virtual void drawText();


	// =========================================================================================================================
	virtual void handleInput();


	// =========================================================================================================================
	virtual void doScrolling();


	// =========================================================================================================================
	virtual void drawLetter();


	// =========================================================================================================================
	virtual void parseOption();


	virtual void dialogue(Dialogue* d);


	virtual void getTextFromOnscreenKeyboard();


	virtual void getNumberFromOnscreenNumpad();


	virtual void getAnswerToQuestionWithQuestionBox(const string& s, int i);
};

