//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class DayCaption : public StatusBarCaption
{
public:

	static Logger log;


	DayCaption(BGClientEngine* g);


	virtual void init() override;


	virtual void update() override;


	BobColor* pausedFGColor = BobColor::darkGray;
	BobColor* pausedAAColor = BobColor::gray;
	BobColor* pausedBGColor = BobColor::lightGray;

	BobColor* fastFGColor = BobColor::darkerBlue;
	BobColor* fastAAColor = BobColor::darkBlue;
	BobColor* fastBGColor = BobColor::blue;

	BobColor* unknownFGColor = BobColor::white;
	BobColor* unknownAAColor = BobColor::lightGray;
	BobColor* unknownBGColor = BobColor::black;


	virtual void setPausedColor();


	virtual void setUnknownColor();


	virtual void setFastSpeedColor();
};

