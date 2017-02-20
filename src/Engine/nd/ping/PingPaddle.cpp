#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger PingPaddle::log = Logger("PingPaddle");


int PingPaddle::h = 32;
int PingPaddle::w = 8;

PingPaddle::PingPaddle(Engine* g)
{ //=========================================================================================================================
	this->e = g;
}

void PingPaddle::update()
{ //=========================================================================================================================
}

void PingPaddle::render()
{ //=========================================================================================================================

	if (selected)
	{
		GLUtils::drawFilledRectXYWH(x, y, (float)w, (float)h, 0.0f, 1.0f, 0.0f, 1.0f);
	}
	else
	{
		GLUtils::drawFilledRectXYWH(x, y, (float)w, (float)h, 1.0f, 1.0f, 1.0f, 1.0f);
	}
}

float PingPaddle::left()
{
	return x;
}

float PingPaddle::right()
{
	return x + w;
}

float PingPaddle::top()
{
	return y;
}

float PingPaddle::bottom()
{
	return y + h;
}

float PingPaddle::middleX()
{
	return x + w / 2;
}

float PingPaddle::middleY()
{
	return y + h / 2;
}

