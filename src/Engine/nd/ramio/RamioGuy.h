//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class RamioGuy : public Entity
{
public:

	static Logger log;


	RamioGuy(Engine* g);


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


	int rightWalkSpeed = 0;
	int leftWalkSpeed = 0;

	int rightWalkCycles = 0;
	int leftWalkCycles = 0;

	static bool jumping;
	int pixelsJumped = 0;
	bool canJump = false;
	int jumpDecelCounter = 0;


	bool wasJumping = false;
	int pixelsFell = 0;
	int fallAccelCounter = 0;


	int facing = RIGHT;
	int frame = 0;


	int jump_decel = 1;
	int fall_accel = 1;


	float forceX = 0.0f;
	float forceY = 0.0f;

	float forceFactor = 0; // 0.1f*pixelsToMoveThisFrame;
	float frictionFactor = 0; // 0.0f2f*pixelsToMoveThisFrame;
	float gravityFactor = 0; // 0.0f2f*pixelsToMoveThisFrame;

	float speedLimit = 5.0f;


	bool running = false;


	virtual void init();


	virtual void jump();


	virtual void fall();


	virtual void update() override;


	virtual bool checkHit(int dir);


	virtual void move(int direction, float floatPixels);


	virtual void render(float alpha, BobTexture* texture, BobTexture* shadowTexture) override;
};

