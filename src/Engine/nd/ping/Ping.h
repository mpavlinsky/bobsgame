//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
class Logger;


class Ping : public NDGameEngine
{
public:

	static Logger log;

	Ping(ND* nD);

	PingPaddle* lp = new PingPaddle(this);
	PingPaddle* rp = new PingPaddle(this);

	PingBall* ball = new PingBall(this);

	int LEFT = 0;
	int RIGHT = 1;


	bool easyMode = true;
	bool playingPING = false;
	bool alreadyUpdating = false;

	bool quit = false;

	bool initialized = false;

	bool gotHighScore = false;
	int highScore = 0;
	int score = 0;

	bool credits = false;
	bool creditScreenInit = false;

	int deadX = 0;
	int deadY = 0;
	bool dying = false;
	bool firstDeath = false;

	int whichPaddle = LEFT;
	int paddleSpeed = 2;

	int ballDirX = LEFT;
	int ballSpeed = 1;
	int ballDirY = 0;

	int DOWN = 1;
	int STRAIGHT = 0;
	int UP = -1;

	float angle = 0;

	int maxBallSpeed = 0;

	int framesSincePressedA = 0;
	int framesSincePressedB = 0;
	int framesSincePressedRight = 0;
	int framesSincePressedLeft = 0;
	int framesSincePressedDown = 0;
	int framesSincePressedUp = 0;
	int framesSincePressedR = 0;

	bool canPressA = false;
	bool canPressB = false;
	bool canPressRight = false;
	bool canPressLeft = false;
	bool canPressDown = false;
	bool canPressUp = false;
	bool canPressR = false;

	PingBackground* background = new PingBackground(this);

	virtual void reset();
	virtual void initGame();
	virtual void update() override;
	virtual void render() override;
	virtual void game();
	virtual void updateScore();
};

