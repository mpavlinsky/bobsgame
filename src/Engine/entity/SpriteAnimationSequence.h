//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class SpriteAnimationSequence
{
public:
	string frameSequenceName = "";
	int frameStart = 0;
	int hitBoxFromLeftPixels1X = 0;
	int hitBoxFromRightPixels1X = 0;
	int hitBoxFromTopPixels1X = 0;
	int hitBoxFromBottomPixels1X = 0;
	int cachedNumFrames = -1;//gets cached when accessed in sprite, not initialized when sprite is filled in because we don't know how many animations it's going to have

	SpriteAnimationSequence(const string& frameSequenceName, int frameStart, int hitBoxFromLeft1X, int hitBoxFromRight1X, int hitBoxFromTop1X, int hitBoxFromBottom1X);



	
};

