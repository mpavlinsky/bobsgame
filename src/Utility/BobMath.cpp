
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------






//Logger Math::log = Logger("Math");


//===========================================================================================================================
int r(int lessthan)
{//===========================================================================================================================
	return rand() % lessthan;
}


//==========================================================================================================================
int HARDWARE_modulo(int var, int modulo)
{//==========================================================================================================================
	while (var < 0) var += modulo;
	return (var % modulo);
}


//=========================================================================================================================
Math::Math()
{//=========================================================================================================================
}

int Math::distance(int x1, int y1, int x2, int y2)
{ //=========================================================================================================================


	//Return the distance between the two points
	return (int)(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

float Math::distance(float x1, float y1, float x2, float y2)
{ //=========================================================================================================================

	//Return the distance between the two points
	return (float)(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

bool Math::isXYTouchingXY(float x, float y, float x2, float y2)
{ //=========================================================================================================================
	return isXYTouchingXYByAmount(x, y, x2, y2, 0);
}

bool Math::isXYXYTouchingXY(float left, float top, float right, float bottom, float x, float y)
{ //=========================================================================================================================
	return isXYXYTouchingXYByAmount(left, top, right, bottom, x, y, 0);
}

bool Math::isXYTouchingXYXY(float x, float y, float left, float top, float right, float bottom)
{ //=========================================================================================================================
	return isXYTouchingXYXYByAmount(x, y, left, top, right, bottom, 0);
}

bool Math::isXYXYTouchingXYXY(float myLeft, float myTop, float myRight, float myBottom, float left, float top, float right, float bottom)
{ //=========================================================================================================================
	return isXYXYTouchingXYXYByAmount(myLeft, myTop, myRight, myBottom, left, top, right, bottom, 0);
}

bool Math::isXYTouchingXYByAmount(float x, float y, float x2, float y2, int amt)
{ //=========================================================================================================================
	return isXYXYTouchingXYXYByAmount(x, y, x, y, x2, y2, x2, y2, amt);
}

bool Math::isXYXYTouchingXYByAmount(float left, float top, float right, float bottom, float x, float y, int amt)
{ //=========================================================================================================================
	return isXYXYTouchingXYXYByAmount(left, top, right, bottom, x, y, x, y, amt);
}

bool Math::isXYTouchingXYXYByAmount(float x, float y, float left, float top, float right, float bottom, int amt)
{ //=========================================================================================================================
	return isXYXYTouchingXYXYByAmount(x, y, x, y, left, top, right, bottom, amt);
}

bool Math::isXYXYTouchingXYXYByAmount(float myLeft, float myTop, float myRight, float myBottom, float left, float top, float right, float bottom, int amt)
{ //=========================================================================================================================
	myLeft = round(myLeft);
	myTop = round(myTop);
	myRight = round(myRight);
	myBottom = round(myBottom);
	left = round(left);
	top = round(top);
	right = round(right);
	bottom = round(bottom);

	if ((myTop - amt <= bottom && myBottom + amt >= top) && (myLeft - amt <= right && myRight + amt >= left)) //to left - above
	{
		return true;
	}

	return false;
}

//=========================================================================================================================
float Math::random()
{//=========================================================================================================================
	return Math::randomFloat();
}

//=========================================================================================================================
float Math::randomFloat()
{//=========================================================================================================================

//	default_random_engine generator;
//	uniform_real_distribution<double> distribution(0.0, 1.0);
//	double number = distribution(generator);

	float number = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	return (float)number;
}


//=========================================================================================================================
int Math::randomInt()
{//=========================================================================================================================

	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, 1);
	int number = distribution(generator);

	return number;
}

int Math::randLessThan(int n)
{ //=========================================================================================================================
	return ((int)(Math::random() * n));
}

int Math::randUpToIncluding(int n)
{ //=========================================================================================================================
	return ((int)(Math::random() * (n + 1)));
}

int Math::randMinMax(int from, int to)
{ //=========================================================================================================================
	return (int)(from + (int)(Math::random() * ((to - from) + 1)));
}

float Math::randLessThanFloat(float n)
{ //=========================================================================================================================
	//return (float)(Math::random() * n);
	float number = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / n));
	return (float)number;
}

float Math::randMinMaxFloat(float from, float to)
{ //=========================================================================================================================
	
	//return (float)(from + (Math::random() * (to - from)));
	float number = from + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (to - from)));
	return (float)number;
}

int Math::getClosestPowerOfTwo(int fold)
{ //===========================================================================================================================


	int ret = 2;
	while (ret < fold)
	{
		ret *= 2;
	}
	return ret;


	/*v--;
	v|=v>>1;
	v|=v>>2;
	v|=v>>4;
	v|=v>>8;
	v|=v>>16;
	v++;
	return v++;*/
}

bool Math::isTexturePowerOfTwo(int width, int height)
{ //==========================================================================================================================
	if ((int)(pow(2.0f, ceil(log((float)(width)) / log(2.0f)))) != width)
	{
		return true;
	}
	if ((int)(pow(2.0f, ceil(log((float)(height)) / log(2.0f)))) != height)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//===========================================================================================================================
int Math::power_of_two(int v)
{//===========================================================================================================================
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v++;
}


//==========================================================================================================================
int Math::IsNPOT(int width, int height)// Check for non-power-of-two textures
{//==========================================================================================================================
	if ((int)powf(2.0f, ceilf(logf((float)width) / logf(2.0f))) != width)
		return 1;
	if ((int)powf(2.0f, ceilf(logf((float)height) / logf(2.0f))) != height)
		return 1;
	else
		return 0;
}

//=========================================================================================================================
int Math::get2Fold(int fold)
{//=========================================================================================================================
	int ret = 2;
	while (ret < fold)
	{
		ret *= 2;
	}
	return ret;
}
