//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;

#include "src/Utility/Color.h"


class Caption;



class ConsoleText
{
public:
	static Logger log;

	Caption* caption = nullptr;

	string text = "";

	int x = -1;
	int y = -1;

	int ticks = -1;

	BobColor* color = BobColor::gray;

	bool isDebug = false;

	ConsoleText();
	ConsoleText(const string& s, BobColor* c, int x, int y, int ticks, bool isDebug);
	float getWidth();
	float getHeight();
};

