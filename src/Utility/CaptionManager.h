//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include "src/Utility/HashMap.h"
#include "src/Utility/ArrayList.h"
class Logger;

#include "src/Engine/EnginePart.h"
#include "src/Utility/Color.h"
#include "src/Utility/BobFont.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
class Engine;
class Entity;
class Caption;
class PuzzleGame;
class BobColor;
class BobsGame;
class Area;


class CaptionManager : EnginePart
{
public:

	static Logger log;


	ArrayList<Caption*>* captionList = new ArrayList<Caption*>();



public:
	CaptionManager(Engine* g);

	void update();
	void render(RenderOrder layer); //RenderOrder layer)

	//TODO: add more getCaption creation functions to have lots of nice options?

	Caption* newManagedCaption(int x, int y, int ticks, const string& text, BobFont* font = BobFont::font_normal_8_outlined, BobColor* textColor = BobColor::black, BobColor* textAAColor = nullptr, BobColor* textBGColor = BobColor::clear, RenderOrder r = RenderOrder::ABOVE_TOP, float scale = 1, int width = 0, Entity* entity = nullptr, Area* area = nullptr, bool fadeLetterColorTowardsTop = false, bool centerTextOnMultipleLines = false);
	Caption* newManagedCaption(int x, int y, int ticks, const string& text, TTF_Font* font = BobFont::ttf_bobsgame_8, BobColor* textColor = BobColor::black, BobColor* textBGColor = BobColor::clear, RenderOrder r = RenderOrder::ABOVE_TOP, float scale = 1, Entity* entity = nullptr, Area* area = nullptr);

};

