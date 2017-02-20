//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "src/Engine/rpg/event/ActionManager.h"
#include "src/Engine/EnginePart.h"
#include "BobFont.h"
#include "Color.h"

class Logger;
class BobsGame;
class Engine;
class BobColor;
class CaptionManager;
class Entity;
class Area;
class BobTexture;


class Caption : public EnginePart
{
public:
	static Logger log;



	string text = "";
	BobFont* font = BobFont::font_normal_8;
	TTF_Font* ttfFont = nullptr;

private:
	BobColor* textBGColor = BobColor::black;
	BobColor* textColor = BobColor::white;
	BobColor* textAAColor = BobColor::gray;

public:
	float screenX = 0;
	float screenY = 0;
	RenderOrder layer = RenderOrder::ABOVE_TOP;
	float scale = 1.0f;
	long long ticksAge = 0;
	long long ticksToRemain = 0;
	bool visible = true;

	//Caption manager will delete it
	bool deleteMe = false;
private:
	float alpha = 0.0f;
	float alphaTo = 1.0f;
	bool beingDeletedWhenAlphaHitsZero = false;
	


public:
	float entityXWhenCreated = 0;
	float entityYWhenCreated = 0;
	Entity* entity;
	int actionCaptionType = ActionManager::ACTIONCAPTIONTYPE_NONE;
	Area* area = nullptr;
	int actionRangeX = 0;
	int actionRangeY = 0;

	bool fadeLetterColorTowardsTop = true;

	int textCharacterLength = 0;
private:
	int width = 0;
	int height = 0;
public:
	int lines = 1;
	int maxWidth = 0;

	int xInLine = 0;
	int line = 0;
	int longestLineWidth = 0;

private:
	bool initialized = false;

public:
	BobTexture* texture = nullptr;
	u8* textureByteArray = nullptr;
	int texWidth = 0;
	int texHeight = 0;

public:
	int fixedPosition = 0;
	bool flashing = false;
	int flashingTicksPerFlash = 0;
	bool centerTextOnMultipleLines = false;
	long long flashingTicksCount = 0;


	//   int Caption::CENTERED_OVER_ENTITY = -1;
	//   int Caption::CENTERED_SCREEN = -2;
	//   int Caption::CENTERED_X = -3;
	//   int Caption::DELETE_WHEN_MAIN_SPRITE_MOVES = -2;
	//   int Caption::STAY_ONSCREEN_UNTIL_MANUALLY_DELETE = -1;

	//x position modifiers
	static const int CENTERED_OVER_ENTITY = -1;
	static const int CENTERED_SCREEN = -2;
	static const int CENTERED_X = -3;

	//seconds modifiers
	static const int DELETE_WHEN_MAIN_SPRITE_MOVES = -2;
	static const int STAY_ONSCREEN_UNTIL_MANUALLY_DELETE = -1;

	//bool drawAbove = false;



	Caption(Engine* g, float screenX, float screenY, int ticks, const string& text, BobFont* font = BobFont::font_normal_8_outlined, BobColor* textColor = BobColor::black, BobColor* textAAColor=nullptr, BobColor* textBGColor = BobColor::clear, RenderOrder layer = RenderOrder::ABOVE_TOP, float scale=1, int maxWidth=0, Entity* entity = nullptr, Area* area = nullptr, bool fadeLetterColorTowardsTop = false, bool centerTextOnMultipleLines = false);
	Caption(Engine* g, float screenX, float screenY, int ticks, const string& text, TTF_Font* ttfFont = BobFont::ttf_oswald_16, BobColor* textColor = BobColor::black, BobColor* textBGColor = BobColor::clear, RenderOrder layer = RenderOrder::ABOVE_TOP, float scale=1, Entity* entity = nullptr, Area* area = nullptr);

	void setText(const string& text, bool force = false);
	BobColor* getTextColor();
	void setTextColor(BobColor* fg, BobColor* aa = nullptr, BobColor* bg = nullptr);
	void initTTF(Engine* g, float screenX, float screenY, long long ticks, const string& text, TTF_Font* font, BobColor* textColor, BobColor* textBGColor, RenderOrder layer, float scale, Entity* entity, Area* area);
	void init(Engine* g, float screenX, float screenY, long long ticks, const string& text, BobFont* font, BobColor* textColor, BobColor* textAAColor, BobColor* textBGColor, RenderOrder layer, float scale, int maxWidth, Entity* entity, Area* area, bool fadeLetterColorTowardsTop, bool centerTextOnMultipleLines);
	virtual void render();
private:
	void increaseMaxWidthToLongestWord();
	int skipNextWord(int position);
	int getCurrentLineLength(int position);
	void calculateTextureWidthAndHeightByParsingEachLine();
	void drawText();
	void parseOptions(const string& optionBuffer);
	int getLetterPixelColor(int letterIndex, int y, int xInLetter, bool blank);
	void setPixel(int index, BobColor* c);
public:
	virtual float getAlphaTo();
	virtual float getAlpha();
	virtual void setAlphaTo(float a);
	virtual void setAlphaImmediately(float a);
	virtual float getWidth();
	virtual float getHeight();
private:
	void drawBlankColumn();
	void drawColumn(int xInLetter, int letterIndex, bool blank);
	void drawLetter(int letterIndex);
public:
	virtual void updateScreenXY();
	virtual void setToFadeOutAndBeDeleted();
	virtual void setToBeDeletedImmediately();
	virtual bool getBeingDeletedWhenFadeOutStatus();
	virtual void update();
	virtual void setEntity(Entity* e);
};

