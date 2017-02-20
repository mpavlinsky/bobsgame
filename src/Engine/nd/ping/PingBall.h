//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class PingBall : public EnginePart
{
public:

	static Logger log;


	static int h;
	static int w;

	//Texture texture;

	float x = 0;
	float y = 0;

	//float speed;


	PingBall(Engine* g);


	virtual void update();


	virtual void render();

	virtual float left();

	virtual float right();

	virtual float top();

	virtual float bottom();

	virtual float middleX();

	virtual float middleY();
};

