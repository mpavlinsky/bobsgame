//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include "../../Utility/BobBool.h"
#include "Sprite.h"
class Logger;




class SpriteAnimationSequence;
class EnginePart;
class Engine;
class EntityData;
class MapData;
class Map;
class Area;


class Entity : public EnginePart
{
public:

	static Logger log;

	static int DOWN;
	static int UP;
	static int LEFT;
	static int RIGHT;

	static int UPLEFT;
	static int DOWNRIGHT;
	static int DOWNLEFT;
	static int UPRIGHT;


	int SPEED_ACCEL_INCREMENT_AMOUNT = 1;


	//these are ticks per pixel moved
	int ticksPerPixel_CAR = 2;
	int ticksPerPixel_FASTEST = 3;
	int ticksPerPixel_FASTER = 4;
	int ticksPerPixel_FAST = 5;
	int ticksPerPixel_NORMAL = 10;
	int ticksPerPixel_SLOW = 15;
	int ticksPerPixel_SLOWER = 20;
	int ticksPerPixel_SLOWEST = 30;


	int ticksPerPixel_CAMERA_CONVERSATION = 4;
	int ticksPerPixel_CAMERA_STOPPED = 30;// ticksPerPixel_SLOWEST;


	int YUU_WALKING_SPEED_KEYBOARD = 24;
	int YUU_RUNNING_SPEED_KEYBOARD = 3;// ticksPerPixel_FASTEST;
	int YUU_STANDING_SPEED_KEYBOARD = 20;// ticksPerPixel_SLOWER;

	int YUU_WALKING_SPEED_JOYSTICK = 28;
	int YUU_RUNNING_SPEED_JOYSTICK = 3;// ticksPerPixel_FASTEST;
	int YUU_STANDING_SPEED_JOYSTICK = 20;// ticksPerPixel_SLOWER;


	bool disableMovementAnimationForAllEntities = false;
	bool isPlayerBeingDraggedThisFrame = false;
	int numberOfEntitiesPullingPlayerThisFrame = 0;
	bool isWalkingIntoPlayerThisFrame = false;
	bool isWalkingIntoWallThisFrame = false;


	Sprite* sprite = nullptr;

protected:
	EntityData* data = nullptr;


public:
	float mapX = 0;
	float mapY = 0;


	float standJitterX = 0; //used when characters are standing to give them a little extra movement
	float standJitterY = 0;


	float alpha = 1.0f;

	bool draw = false;


private:
	int animationTicksCounter = 0; // was vbl_animation_timer
	int frameIndexInTexture = 0; //based on current sequence (getAnimDirection()) and currentAnimationFrameInSequence, this is what will be rendered
	SpriteAnimationSequence* currentAnimation = nullptr;

	int ticksBetweenAnimationLoopThisLoop = 0; //for storing random value between loops

public:
	int movementDirection = 0; //was walk_dir


	float* shadowClipPerPixel = nullptr;
	bool clipShadow = false;
	float shadowSize = 0.65f;
	//public float getShadowStart = 0.75f;
	float shadowAlpha = 0.60f;


	int ticksSinceLastMovement = 0;
public:
	float pixelsToMoveThisFrame = 0;


	bool behaviorEnabled = true;

	ArrayList<string>* eventBehaviorList = new ArrayList<string>(); //TODO: do something with this!
	ArrayList<string>* eventTargetTYPEIDList = new ArrayList<string>(); //TODO: do something with this!


	string currentAreaTYPEIDTarget = "";


private:
	bool deleteWhenAlphaZero = false;


public:
	Entity();
	Entity(Engine* g);


	Entity(Engine* g, EntityData* entityData);


	void initEntity(EntityData* entityData);


	virtual void initCurrentAnimationFromSprite();


	virtual void update();


	virtual void updateTimers();


	//	
	//	public void addDialogue(String dialogueIDString)
	//	{
	//
	//		int dialogueID = Integer.parseInt(dialogueIDString);
	//
	//		if(dialogueID!=-1)
	//		{
	//
	//			Dialogue d = g.getDialogueByID(dialogueID);
	//
	//			if(d!=null)dialogueList.add(d);
	//			else
	//			dialogueList.add(new Dialogue(dialogueID));
	//
	//		}
	//	}


	virtual void renderDebugBoxes();


	virtual void renderDebugInfo();


	virtual string getCurrentAreaTargetName();


	//	
	//	public void render()
	//	{
	//		render(alpha);
	//		//overrode this so i can send in arbitrary alpha, really only used for fading sprites out with the last map.
	//	}


	virtual void render(float mapAlpha);


	virtual void render(float alpha, BobTexture* texture, BobTexture* shadowTexture);


	virtual Map* getCurrentMap() override;


	virtual Map* getMap();


	virtual bool shouldDraw();


	virtual bool isWithinScreenBounds();


	//
	//	
	//	public boolean check_collide_fx(int dir)
	//	{
	//
	//		boolean return_this=true;
	//
	//
	//
	//		if(dir==UP)
	//		{
	//			if(
	//				getMap()->get_fx_layer_xy(getLeft()+1,getTop())==0
	//				&&getMap()->get_fx_layer_xy(getMiddleX()-1,getTop())==0
	//				&&getMap()->get_fx_layer_xy(getMiddleX(),getTop())==0
	//				&&getMap()->get_fx_layer_xy(getRight()-1,getTop())==0
	//			)return_this=false;
	//		}
	//		else
	//		if(dir==DOWN)
	//		{
	//			if(
	//					getMap()->get_fx_layer_xy(getLeft()+1,getBottom())==0
	//				&&getMap()->get_fx_layer_xy(getMiddleX()-1,getBottom())==0
	//				&&getMap()->get_fx_layer_xy(getMiddleX(),getBottom())==0
	//				&&getMap()->get_fx_layer_xy(getRight()-1,getBottom())==0
	//			)return_this=false;
	//		}
	//		else
	//		if(dir==LEFT)
	//		{
	//			if(
	//					getMap()->get_fx_layer_xy(getLeft(),getBottom()-1)==0
	//				&&getMap()->get_fx_layer_xy(getLeft(),getBottom()-4)==0
	//			)return_this=false;
	//		}
	//		else
	//		if(dir==RIGHT)
	//		{
	//			if(
	//					getMap()->get_fx_layer_xy(getRight()-1,getBottom()-1)==0
	//				&&getMap()->get_fx_layer_xy(getRight()-1,getBottom()-4)==0
	//			)return_this=false;
	//		}
	//
	//		if(ignore_fx_layer==true)return false;
	//
	//		return return_this;
	//	}


	virtual bool checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(int dir);


	virtual bool checkMiddlePixelAgainstHitLayerAndNonWalkableEntitiesInDirection(int dir);


	/// 
	/// <summary>
	/// this is used for PATHFINDING so it ignores doors (so sprites can go through doors) and walkable sprites!!
	/// 
	/// </summary>
	virtual bool checkPathBlockedXY(float x, float y);


	virtual bool checkXYAgainstNonWalkableEntities(float x, float y);


	virtual bool checkXYAgainstHitLayerAndNonWalkableEntities(float x, float y);


	virtual bool checkHitBoxAndMovePixelInDirection(int dir); //returns 0 if getHit wall   ( DOES HIT DETECTION/WALL DETECTION,HIT WITH SPRITE DETECTION )


	virtual bool checkMiddlePixelHitAndMovePixelInDirection(int dir); //returns 0 if getHit wall   ( DOES HIT DETECTION/WALL DETECTION,HIT WITH SPRITE DETECTION )


	virtual void movePixelInDirection(int dir);


	virtual bool ifCanMoveAPixelThisFrameSubtractAndReturnTrue();


	virtual bool canCreateAtXY(float x, float y);


	virtual void setFeetAtMapXY(float mapXPixels2X, float mapYPixels2X);


	virtual int getFrame();


	virtual void setFrame(int f);


protected:
	virtual void resetAnimationTimer();


public:
	virtual bool haveTicksPassedSinceLastAnimated_ResetIfTrue(int ticks);


	virtual SpriteAnimationSequence* getCurrentAnimation();


	virtual void setCurrentAnimation(SpriteAnimationSequence* a);


	virtual void setCurrentAnimationByName(const string& name);


	virtual void setCurrentAnimationByDirection(int dir);


	virtual int getSpriteLastFrame();


	virtual SpriteAnimationSequence* getAnimationBySpriteFrame(int frame);


	virtual void setCurrentAnimationBySpriteFrame(int frame);


	virtual int getCurrentAnimationNumberOfFrames();


	virtual int getCurrentAnimationStartFrame();


	virtual int getCurrentAnimationLastFrame();


	virtual string getCurrentAnimationName();


	virtual int getCurrentFrameOffsetInCurrentAnimation();


	virtual void setFrameOffsetInCurrentAnimation(int frameOffset);


	virtual void setFrameInAllFrames(int frame);


	virtual void selectRandomFrame(int from, int toIncluding);


	virtual void selectRandomFrameInAllFrames();


	virtual void selectRandomFrameInCurrentAnimation();


	virtual void incrementAnimationFrame(int from, int toIncluding); //increments the frame in the current walking direction


	virtual void incrementAnimationFrameInAllFrames(); //increments the frame in the current walking direction


	virtual void incrementAnimationFrameInCurrentAnimation(); //increments the frame in the current walking direction


	virtual void stopAnimation();


	virtual void setAnimateLoopThroughCurrentAnimation();


	virtual void setAnimateLoopThroughAllFrames();


	virtual void setFrameToAllFramesZero();


	virtual void setFrameToCurrentAnimationStart();


	virtual void setAnimateOnceThroughCurrentAnimation();


	virtual void setAnimateOnceThroughAllFrames();


	virtual void doAnimation();


	virtual void setAlphaImmediately(float a);


	virtual void fadeOutAndDelete();


	virtual void deleteFromMapEntityListAndReleaseTexture();


	virtual void addEventBehavior(const string& s);

	//	
	//	public void addBehavior(String s)
	//	{
	//		getBehaviorList().add(s);
	//	}
	//
	//
	//	
	//	public void addConnectionTYPEID(String s)
	//	{
	//		getConnectionTYPEIDList().add(s);
	//	}


	/// <summary>
	/// This gets called repeatedly in events, until it returns a non-null value, at which point the event continues and does not ask again.
	/// This function will continue asking the server for the value, returning null until the server has set the response value.
	/// Upon finding a non-null response value set by the networking thread by a server response, we reset it to null and return that value, ensuring that it is always a fresh copy from the server.
	/// </summary>
	virtual BobBool* checkServerTalkedToTodayValueAndResetAfterSuccessfulReturn();


	virtual void tellServerTalkedToToday();


	virtual float getDistanceFromEntity(Entity* e);


	virtual Entity* findNearestEntity();


	virtual Entity* findNearestEntityInDirection(int dir);


	virtual bool isWalkingIntoEntity(Entity* entity);


	virtual bool isWalkingIntoArea(Area* area);


	virtual bool isEntityHitBoxTouchingMyHitBox(Entity* e);

	virtual bool isNearestEntityHitBoxTouchingMyHitBox();

	virtual bool isAreaCenterTouchingMyHitBox(Area* a);

	virtual bool isAreaBoundaryTouchingMyHitBox(Area* a);

	virtual bool isXYTouchingMyHitBox(float x, float y);

	virtual bool isXYXYTouchingMyHitBox(float left, float top, float right, float bottom);

	virtual bool isAreaBoundaryTouchingMyMiddleXY(Area* a);

	virtual bool isEntityMiddleXYTouchingMyMiddleXY(Entity* e);

	virtual bool isAreaCenterTouchingMyMiddleXY(Area* a);

	virtual bool isXYTouchingMyMiddleXY(float x, float y);

	virtual bool isXYXYTouchingMyMiddleXY(float left, float top, float right, float bottom);

	virtual bool isEntityHitBoxTouchingMyHitBoxByAmount(Entity* e, int amt);

	virtual bool isNearestEntityHitBoxTouchingMyHitBoxByAmount(int amt);

	virtual bool isAreaCenterTouchingMyHitBoxByAmount(Area* a, int amt);

	virtual bool isAreaBoundaryTouchingMyHitBoxByAmount(Area* a, int amt);

	virtual bool isXYTouchingMyHitBoxByAmount(float x, float y, int amt);

	virtual bool isXYXYTouchingMyHitBoxByAmount(float left, float top, float right, float bottom, int amt);

	virtual bool isAreaBoundaryTouchingMyMiddleXYByAmount(Area* a, int amt);

	virtual bool isEntityMiddleXYTouchingMyMiddleXYByAmount(Entity* e, int amt);

	virtual bool isAreaCenterTouchingMyMiddleXYByAmount(Area* a, int amt);

	virtual bool isXYTouchingMyMiddleXYByAmount(float x, float y, int amt);

	virtual bool isXYXYTouchingMyMiddleXYByAmount(float left, float top, float right, float bottom, int amt);


	virtual bool isTouchingPlayerInDirection(int dir);


	virtual bool isHitBoxTouchingEntityInDirectionByAmount(Entity* e, int direction, int amt);

	virtual bool isHitBoxTouchingXYInDirectionByAmount(float x, float y, int direction, int amt);

	virtual bool isHitBoxTouchingXYXYInDirectionByAmount(float left, float top, float right, float bottom, int direction, int amt);


	virtual float getTop();

	virtual float getLeft();

	virtual float getRight();

	virtual float getBottom();

	float getMiddleX();

	float getMiddleY();


	virtual float getRoundedMiddleX();

	virtual float getRoundedMiddleY();

	virtual float getMiddleOffsetX();

	virtual float getMiddleOffsetY();


private:
	float getScreenX();


	float getScreenY();


public:
	virtual float getScreenLeft();


	virtual float getScreenTop();


	float getScreenMiddleHitboxY();


	/// <summary>
	/// This is the offset from x to the hitbox </summary>
	virtual float getHitBoxFromLeft();


	/// <summary>
	/// This is the offset from x + width to the hitbox, it is a positive number but subtracted: x + width - hitbox </summary>
	virtual float getHitBoxFromRight();


	/// <summary>
	/// This is the offset from y to the hitbox, this is larger for people as it offsets down to the feet </summary>
	virtual float getHitBoxFromTop();


	/// <summary>
	/// This is the offset from y + height to the hitbox, it is a positive number but subtracted: y + height - hitbox </summary>
	virtual float getHitBoxFromBottom();


	virtual float getShadowStart();


	virtual float getX();
	virtual float getY();


	virtual void setX(float x);


	virtual void setY(float y);


	virtual void incX();
	virtual void incY();
	virtual void decX();
	virtual void decY();


	virtual float getWidth();


	virtual float getHeight();


	virtual EntityData* getData();


	virtual string getName();
	virtual string getComment();
	virtual int getID();
	virtual int getMapID();
	virtual string getSpriteName();


	virtual bool getIsNPC();
	virtual bool getPushable();
	virtual bool getNonWalkable();
	virtual float getToAlpha();
	virtual float getScale();
	virtual bool getDisableShadow();
	virtual bool getAboveWhenEqual();
	virtual bool getAlwaysOnTop();
	virtual bool getAlwaysOnBottom();
	virtual RenderOrder getRenderOrder();
	virtual bool getAboveTopLayer();
	virtual int getInitialFrame();
	virtual bool getAnimatingThroughAllFrames();
	virtual bool getRandomFrames();
	virtual bool getRandomUpToTicksBetweenFrames();
	virtual bool getRandomUpToTicksBetweenAnimationLoop();
	virtual int getTicksBetweenFrames();
	virtual int getTicksBetweenAnimationLoop();

	virtual float getTicksPerPixelMoved();

	virtual int getEventID();
	virtual bool getOnlyHereDuringEvent();
	virtual float getVoicePitch();
	virtual bool getMovementAnimationDisabled();
	virtual bool getIgnoreHitLayer();
	virtual bool getIgnoreHitPlayer();
	virtual bool getPullPlayer();
	virtual bool getPushPlayer();

	virtual bool getAnimatingThroughCurrentAnimation();
	virtual bool getLoopAnimation();

	virtual ArrayList<string>* getConnectionTYPEIDList();
	virtual ArrayList<string>* getBehaviorList();

	virtual string getTYPEIDString();


	//set
	virtual void setID(int s);
	virtual void setName(const string& s);
	virtual void setComment(const string& s);

	virtual void setSpawnXPixelsHQ(float s);
	virtual void setSpawnYPixelsHQ(float s);
	virtual void setIsNPC(bool s);
	virtual void setPushable(bool s);
	virtual void setNonWalkable(bool s);
	virtual void setToAlpha(float alpha);
	virtual void setScale(float s);
	virtual void setDisableShadow(bool s);
	virtual void setInitialFrame(int f);
	virtual void setRandomFrames(bool s);
	virtual void setRandomUpToTicksBetweenFrames(bool s);
	virtual void setRandomUpToTicksBetweenAnimationLoop(bool s);
	virtual void setTicksBetweenFrames(int s);
	virtual void setTicksBetweenAnimationLoop(int s);

	virtual void setTicksPerPixelMoved(float s);
	virtual void setRenderOrder(RenderOrder s);
	virtual void setAboveTopLayer(bool s);
	virtual void setAboveWhenEqual(bool s);
	virtual void setAlwaysOnBottom(bool s);
	virtual void setAlwaysOnTop(bool s);
	virtual void setOnlyHereDuringEvent(bool s);
	virtual void setVoicePitch(float s);
	virtual void setAnimationDisabled(bool s);
	virtual void setHitLayerDisabled(bool s);
	virtual void setIgnoreHitPlayer(bool s);
	virtual void setEventID(int s);

	virtual void setAnimateThroughAllFrames(bool s);
	virtual void setAnimateThroughCurrentAnimation(bool s);
	virtual void setLoopAnimation(bool s);
};

