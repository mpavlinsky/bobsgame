//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class EntityData : public AssetData
{
private:
	
	string spriteName = "";


	
	float spawnXPixels1X = 0;
	
	float spawnYPixels1X = 0;


	
	int initialFrame = 0;

	
	bool pushable = false;
	
	bool nonWalkable = false;


	
	float toAlpha = 1.0f;


	
	float scale = 1.0f;


	
	bool disableShadow = false;


	
	bool aboveTopLayer = false; //dont use this in client, client only uses layer, this is only for the editor to easily set a sprite to above layer.
	//eventually it will be replaced when i move to objectData save/load in editor.
	//TODO: phase this out for just "set layer" above/below


	int layer = 0; //ground

	
	RenderOrder renderOrder = RenderOrder::GROUND;

	
	bool aboveWhenEqual = false; //if two entities are on the same layer and the bottom lines up, render this one after

	
	bool alwaysOnBottom = false; //render first on whatever layer it is on
	
	bool alwaysOnTop = false; //render last on whatever layer it is on


	bool animateThroughFrames = false; //cannot have BOTH this and animateThroughCurrentAnimation set.

	
	int ticksBetweenFrames = 100;
	
	bool randomUpToTicksBetweenFrames = false; //added in editor

	
	bool randomFrames = false; //initial frame will be randomized too. applies to both animateThroughAllFrames and animateThroughCurrentAnimation

	int ticksBetweenAnimation = 0; //will be random up to this if checked random up to ticks between animation loop
	bool randomTimeBetweenAnimation = false;


public:
	int walkSpeed = 1; //DONE: phase this out for a getTicksPerPixelMoved edit box // THIS VARIABLE IS OBSOLETE, keeping it for backwards compatibility.
private:
	
	float ticksPerPixelMoved = 10;


	
	int eventID = -1;
	
	bool onlyHereDuringEvent = false; //TODO: what does this do


	
	int mapID = -1;
	
	int stateID = -1;


	//TODO: implement in editor:
	bool animateThroughCurrentAnimation = false; //TODO: implement
	
	bool loopAnimation = true; //TODO: implement

	
	float voicePitch = 0; //TODO: implement

	bool animationDisabled = false; //TODO see where this is used.

	
	bool hitLayerDisabled = false;
	
	bool ignoreHitPlayer = false;
	
	bool ignoreHitEntities = false;
	
	bool dontUsePathfinding = false;

	//public boolean ignore_fx_layer=false;
	
	bool pullPlayer = false;
	
	bool pushPlayer = false;


	
	ArrayList<string>* behaviorList = new ArrayList<string>();
	
	ArrayList<string>* connectionTYPEIDList = new ArrayList<string>();


	
	string comment = "";


	
	bool isNPC = false; //only used for export from tools for now to determine whether to spawn a character or an entity. determined from the SPRITE.getIsNPC, which is where it should be.


public:
	EntityData();


	EntityData(int id, const string& name, const string& spriteAssetName = "", int spawnXPixels1X = 0, int spawnYPixels1X = 0, int initialFrame = 0, bool pushable = false, bool nonWalkable = false, int alphaByte = 255, float scale = 1, int ticksPerPixelMoved = 12, bool aboveTopLayer = false, bool aboveWhenEqual = false, bool alwaysOnBottom = false, bool animateThroughFrames = false, bool randomTimeBetweenAnimation = false, int ticksBetweenFrames = 0, int ticksBetweenAnimation = false, bool onlyHereDuringEvent = false, bool randomFrames = false, bool disableShadow = false, int eventID = -1, const string& comment = "");
	void initEntityData(int id, const string& name, const string& spriteAssetName = "", int spawnXPixels1X = 0, int spawnYPixels1X = 0, int initialFrame = 0, bool pushable = false, bool nonWalkable = false, int alphaByte = 255, float scale = 1, int ticksPerPixelMoved = 12, bool aboveTopLayer = false, bool aboveWhenEqual = false, bool alwaysOnBottom = false, bool animateThroughFrames = false, bool randomTimeBetweenAnimation = false, int ticksBetweenFrames = 0, int ticksBetweenAnimation = false, bool onlyHereDuringEvent = false, bool randomFrames = false, bool disableShadow = false, int eventID = -1, const string& comment = "");

	//	
	//	public void addConnection(String s)
	//	{
	//		getConnectionTYPEIDList.add(s);
	//	}


	//	
	//	public void addBehavior(String s)
	//	{
	//		getBehaviorList.add(s);
	//	}


	static EntityData* fromBase64ZippedJSON(const string& b64);


	static EntityData* fromJSON(const string& json);


	virtual string getTYPEIDString();


	virtual float getSpawnXPixels1X();
	virtual float getSpawnYPixels1X();
	virtual float getSpawnXPixelsHQ();
	virtual float getSpawnYPixelsHQ();

	virtual string getSpriteName();
	virtual string getComment();
	virtual int getInitialFrame();
	virtual bool getPushable();
	virtual bool getNonWalkable();
	virtual float getToAlpha();
	virtual float getScale();
	virtual bool getDisableShadow();
	virtual int getLayer();
	virtual RenderOrder getRenderOrder();
	virtual bool getAboveWhenEqual();
	virtual bool getAboveTopLayer();
	virtual bool getAlwaysOnBottom();
	virtual bool getAlwaysOnTop();
	virtual bool getIsNPC();
	virtual bool getAnimatingThroughAllFrames();
	virtual bool getAnimatingThroughCurrentAnimation();
	virtual bool getLoopAnimation();
	virtual bool getRandomFrames();
	virtual bool getRandomUpToTicksBetweenAnimationLoop();
	virtual int getTicksBetweenFrames();
	virtual bool getRandomUpToTicksBetweenFrames();
	virtual int getTicksBetweenAnimationLoop();

	virtual float getTicksPerPixelMoved();
	virtual bool getOnlyHereDuringEvent();
	virtual float getVoicePitch();
	virtual bool getMovementAnimationDisabled();
	virtual bool getHitLayerDisabled();
	virtual bool getIgnoreHitPlayer();
	virtual bool getIgnoreHitEntities();
	virtual bool getDontUsePathfinding();
	virtual bool getPullPlayer();
	virtual bool getPushPlayer();
	virtual int getEventID();
	virtual int getMapID();
	virtual int getStateID();
	virtual ArrayList<string>* getConnectionTYPEIDList();
	virtual ArrayList<string>* getBehaviorList();


	//set

	virtual void setSpriteName(const string& s);
	virtual void setInitialFrame(int s);
	virtual void setPushable(bool s);
	virtual void setNonWalkable(bool s);
	virtual void setToAlpha(float s);
	virtual void setScale(float s);
	virtual void setDisableShadow(bool s);
	virtual void setRenderOrder(RenderOrder s);
	virtual void setAboveTopLayer(bool s);
	virtual void setAboveWhenEqual(bool s);
	virtual void setAlwaysOnBottom(bool s);
	virtual void setAlwaysOnTop(bool s);
	virtual void setIsNPC(bool s);
	virtual void setOnlyHereDuringEvent(bool s);
	virtual void setVoicePitch(float s);
	virtual void setAnimationDisabled(bool s);
	virtual void setHitLayerDisabled(bool s);
	virtual void setIgnoreHitPlayer(bool s);
	virtual void setIgnoreHitEntities(bool s);
	virtual void setDontUsePathfinding(bool s);

	virtual void setRandomFrames(bool s);
	virtual void setRandomUpToTicksBetweenAnimationLoop(bool s);
	virtual void setTicksBetweenFrames(int s);
	virtual void setRandomUpToTicksBetweenFrames(bool s);
	virtual void setTicksBetweenAnimationLoop(int s);

	virtual void setTicksPerPixelMoved(float s);
	virtual void setSpawnXPixels1X(float s);
	virtual void setSpawnYPixels1X(float s);
	virtual void setMapID(int s);
	virtual void setStateID(int s);
	virtual void setEventID(int s);
	virtual void setComment(const string& s);


	virtual void setAnimateThroughAllFrames(bool s);
	virtual void setAnimateThroughCurrentAnimation(bool s);
	virtual void setLoopAnimation(bool s);
};

