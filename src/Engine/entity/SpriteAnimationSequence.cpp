#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger SpriteAnimationSequence::log = Logger("SpriteAnimationSequence");


SpriteAnimationSequence::SpriteAnimationSequence(const string& frameSequenceName, int frameStart, int hitBoxFromLeft1X, int hitBoxFromRight1X, int hitBoxFromTop1X, int hitBoxFromBottom1X)
{ //=========================================================================================================================
	this->frameSequenceName = frameSequenceName;
	this->frameStart = frameStart;
	this->hitBoxFromLeftPixels1X = hitBoxFromLeft1X;
	this->hitBoxFromRightPixels1X = hitBoxFromRight1X;
	this->hitBoxFromTopPixels1X = hitBoxFromTop1X;
	this->hitBoxFromBottomPixels1X = hitBoxFromBottom1X;
}

