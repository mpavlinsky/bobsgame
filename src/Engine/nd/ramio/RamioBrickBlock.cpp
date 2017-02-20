#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger RamioBrickBlock::log = Logger("RamioBrickBlock");


RamioBrickBlock::RamioBrickBlock(Engine* g)
{ //=========================================================================================================================
	this->e = g;
}

void RamioBrickBlock::getHit()
{ //=========================================================================================================================

	getAudioManager()->playSound("ramiobrickthud", 64, 44100, 0);

	//TODO:if small ramio, just bounce
	//else destroy
}

