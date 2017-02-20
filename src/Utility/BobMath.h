//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




int r(int lessthan);


class Math
{
public:
	//static Logger log;

	Math();


	static int distance(int x1, int y1, int x2, int y2);


	static float distance(float x1, float y1, float x2, float y2);


	static bool isXYTouchingXY(float x, float y, float x2, float y2);

	static bool isXYXYTouchingXY(float left, float top, float right, float bottom, float x, float y);

	static bool isXYTouchingXYXY(float x, float y, float left, float top, float right, float bottom);

	static bool isXYXYTouchingXYXY(float myLeft, float myTop, float myRight, float myBottom, float left, float top, float right, float bottom);

	static bool isXYTouchingXYByAmount(float x, float y, float x2, float y2, int amt);

	static bool isXYXYTouchingXYByAmount(float left, float top, float right, float bottom, float x, float y, int amt);

	static bool isXYTouchingXYXYByAmount(float x, float y, float left, float top, float right, float bottom, int amt);

	static bool isXYXYTouchingXYXYByAmount(float myLeft, float myTop, float myRight, float myBottom, float left, float top, float right, float bottom, int amt);


	static float random();

	//from 0 to 1
	static float randomFloat();

	static int randomInt();



	static int randLessThan(int n);


	static int randUpToIncluding(int n);


	static int randMinMax(int from, int to);


	static float randLessThanFloat(float n);


	static float randMinMaxFloat(float from, float to);


	static int getClosestPowerOfTwo(int fold);


	static bool isTexturePowerOfTwo(int width, int height); // Check for non-power-of-two textures

	static int power_of_two(int v);
	static int IsNPOT(int width, int height);
	static int get2Fold(int fold);
};

