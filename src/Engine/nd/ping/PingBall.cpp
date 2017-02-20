#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger PingBall::log = Logger("PingBall");


int PingBall::h = 4;
int PingBall::w = 4;

PingBall::PingBall(Engine* g)
{ //=========================================================================================================================
	this->e = g;
}

void PingBall::update()
{ //=========================================================================================================================
}

void PingBall::render()
{ //=========================================================================================================================

	GLUtils::drawFilledRectXYWH(x, y, (float)w, (float)h, 1.0f, 1.0f, 1.0f, 1.0f);
}

float PingBall::left()
{
	return x;
}

float PingBall::right()
{
	return x + w;
}

float PingBall::top()
{
	return y;
}

float PingBall::bottom()
{
	return y + h;
}

float PingBall::middleX()
{
	return x + w / 2;
}

float PingBall::middleY()
{
	return y + h / 2;
}

