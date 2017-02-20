//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



class Engine;

class Player : public Character
{
	//public static SpriteAsset walkingSprite = SpriteAssetIndex.sprite_bob;
	//public static SpriteAsset runningSprite = SpriteAssetIndex.sprite_yuurunning;


public:

	static Logger log;


	int GLOBAL_main_sprite_input_off = 0;
	int GLOBAL_main_sprite_actions_off = 0;
	int GLOBAL_main_sprite_fx_off = 0;


	bool noInput = false;


	Caption* autopilotCaption = nullptr;


	float forceX = 0.0f;
	float forceY = 0.0f;

	float forceFactor = 0; //0.1f*pixelsToMoveThisFrame;
	float frictionFactor = 0; //0.0f2f*pixelsToMoveThisFrame;

	float speedLimit = 1.5f;


	Player(Engine* g, const string& spriteName);


	Player(Engine* g);
	void initPlayer();

	virtual void update() override;


	virtual void render(float f) override;


	//	
	//	public Map getMap()
	//	{
	//		return getCurrentMap();
	//	}


	bool autopilotActive = false; //TODO: handle this


	virtual void setAutoPilot(bool b);


	virtual bool isAutoPilotOn();


	virtual void handleAreas();


	long long lastPlayedFootstepSoundTicksCounter = 0;

	virtual void doPlayerSound();


	virtual void setSpeed();


	virtual void handlePlayerControls();


	virtual bool checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(int direction) override;


	/// <summary>
	/// Sets walk_dir to direction.
	/// For each pixel allowed to move this frame:
	/// checks getHit (which checks non-walkable entities as well) in direction (or both directions for diagonals)
	/// then moves pixel.
	/// Moving diagonally counts as one pixel.
	/// </summary>

	virtual void move(int direction, float pixels); //move_check_hit_animate_set_fx_layer
};

