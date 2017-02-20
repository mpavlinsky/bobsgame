//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include "Entity.h"
class Logger;




class PathFinder;
class Engine;
class EntityData;
class BobTexture;
class Caption;
class Sprite;
class Area;


class Character : public Entity
{
public:
	static Logger log;

	int standing_cycles = 0;

	int pixelsToWalk = 0;
	int xPixelCounter = 0; //used for setting diagonal ratio, walking in perfect diagonal line
	int yPixelCounter = 0;

	int ticksToStand = 0;


	int animationDirection = 0;

	PathFinder* pathfinder;


	int pathPosition = 0;

	int pathFindWaitTicks = 0;


	float lastMapX = 0;
	float lastMapY = 0;
	int ticksSinceMoved = 0;

	bool moved = false; //locationChanged
	bool standing = false;
	bool running = false;


	BobTexture* uniqueTexture = nullptr; //if this is set it will render with this, otherwise it will try to render the normal spriteAsset.texture in Entity.render()


	bool showName = false;
	Caption* nameCaption = nullptr;

	bool showAccountType = false;
	Caption* accountTypeCaption = nullptr;

	BobColor* nameColor = BobColor::white;
	BobColor* accountTypeNameColor = BobColor::white;
	string accountTypeName = "";


	bool isMale = false;
	bool isFemale = false;


	int standingTicksBetweenFrames = 0;
	int rotationAnimationSpeedTicks = 160;


	Character();
	//Character(Engine* g);


	Character(Engine* g, EntityData* data);

	void initCharacter();


	Character(Engine* g, string name, Sprite* sprite, Area* a);


	virtual void initCurrentAnimationFromSprite() override;


	virtual void render(float alpha) override;


	virtual void update() override;


	virtual void setAnimationByDirection(int dir);


	virtual bool canDoCharacterMovementOrStandingAnimation();


	virtual void doCharacterAnimation(); //does animation and turns if needed


	virtual void checkIfMoved();


	virtual void dontLookAtEntity(Entity* e); //first id is entity to be avoiding LOOKING,second id is one to NOT BE LOOKED AT


	virtual void lookAtEntity(Entity* e);


	virtual void lookAtEntityButNotOppositeWalkingDirection(Entity* stared_at_entity);


	virtual void setAppearanceFromCharacterAppearanceString(string s);


	virtual void generateUniqueTexture(int genderIndex, int archetypeIndex, int shoeColorIndex, int shirtColorIndex, int pantsColorIndex, int skinColorIndex, int eyeColorIndex, int hairColorIndex);


	virtual void setShowName(bool b);


	virtual void setShowAccountType(bool b);


	virtual void setCharacterNameAndCaption(BobColor* nameColor, const string& name, BobColor* accountTypeNameColor, const string& accountTypeName);


	//
	//	
	//	public void setPriorityFromFXLayer()
	//	{
	//
	//		//this checks the current position to see if it needs to set the background priority up or down
	//
	//
	//
	//		int under2=2;
	//		int over1=1;
	//
	//		if(getMap()->getCameraBoundsFXLayerAtXYPixels(getLeft()+2,getBottom()-2)==under2
	//				||getMap()->getCameraBoundsFXLayerAtXYPixels(getRight()-2,getBottom()-2)==under2
	//				||getMap()->getCameraBoundsFXLayerAtXYPixels(getLeft()+2,getTop()+2)==under2
	//				||getMap()->getCameraBoundsFXLayerAtXYPixels(getRight()-2,getTop()+2)==under2
	//				||getMap()->getCameraBoundsFXLayerAtXYPixels(getMiddleX(),getBottom()-(hitBoxTop()/2))==under2)
	//		{
	//
	//			setRenderOrder(RenderOrder.GROUND);
	//
	//		}
	//		else if(getMap()->getCameraBoundsFXLayerAtXYPixels(getLeft()+2,getBottom()-2)==over1
	//				||getMap()->getCameraBoundsFXLayerAtXYPixels(getRight()-2,getBottom()-2)==over1
	//				||getMap()->getCameraBoundsFXLayerAtXYPixels(getLeft()+2,getTop()+2)==over1
	//				||getMap()->getCameraBoundsFXLayerAtXYPixels(getRight()-2,getTop()+2)==over1
	//				||getMap()->getCameraBoundsFXLayerAtXYPixels(getMiddleX(),getBottom()-(hitBoxTop()/2))==over1)
	//		{
	//			setRenderOrder(RenderOrder.ABOVE);
	//		}
	//		else
	//		{
	//			setRenderOrder(RenderOrder.GROUND);
	//		}
	//
	//
	//	}


	virtual ArrayList<Entity*>* getOnScreenNonCharacterEntitiesWithinRangeAmount(int amt);

	virtual bool checkTouchingAnyEntityInEntityList(ArrayList<Entity*>* list, float x, float y);


	virtual bool checkHitLayerAndTouchingAnyEntityInEntityList(ArrayList<Entity*>* list, float x, float y);


	virtual bool checkTouchingAnyOnScreenNonCharacterNonWalkableEntities(float x, float y);


	virtual void setShadowClip();


	int pathTried = 0;

	float finalPathX = 0;
	float finalPathY = 0;


	/// <summary>
	/// return 0 if not there.
	/// if path is blocked, will wait 500 ticks and try again (for someone to move) 3 times, and then return -1 if still fail.
	/// return 1 if there.
	/// 
	/// </summary>
	virtual int walkToXYWithPathFinding(float x, float y);


	virtual void checkHitBoxAndWalkDirection(int dir);


	virtual void walkDirectionNoCheckHit(int direction);


	virtual void walkRandomlyAroundRoomAndStop();


	virtual void walkRandomlyAroundRoom();


	virtual int walkRandomlyWithinXYXY(float x1, float y1, float x2, float y2);


	virtual void twitchAroundRoom();


	virtual Character* findNearestCharacter();


	virtual int walkToXYLRToUD(float x, float y);


	virtual int walkToXYUDToLR(float toX, float toY);


	virtual bool walkToXYNoCheckHit(float toX, float toY);


	virtual bool walkToXYNoCheckHitOLD(float x, float y);


	virtual bool walkToXYUntilHitWall(float x, float y);


	virtual int walkToXYWithBasicHitCheck(float x, float y);


	virtual int walkToXYNoHitAvoidOthersPushMain(float x, float y);


	virtual int walkToXYStopForOtherEntitiesWithinAmt(float x, float y, int amt); //walk_to_xy_stop_for_other_entitys_amt


	virtual void walkDirectionAvoidOtherEntities(int direction);


	///TEMP TEMP TEMP


	virtual bool walkToXYIntelligentHitPushOthers(float x, float y);


	virtual bool walkToXYIntelligentHitAvoidOthers(float x, float y);


	virtual int walk_to_xy_intelligenthit_stopforothers_pushmain(float x, float y);


	virtual void walkStraightFromPointToPoint(float x1, float y1, float x2, float y2);


	virtual void walkStraightFromPointToPointAndStop(float x1, float y1, float x2, float y2);


	virtual void walkAwayFromPoint(float x, float y);


	virtual int walkDistance(int direction);


	virtual int avoidEntity(Entity* e, int amt); //returns 1 if not in entity area,use it to do something else outside,standing,staring,walking randomly etc


	virtual int avoidNearestEntity(int avoid_amt);


	virtual int avoidNearestCharacter(int avoid_amt);


	virtual void pushableCrowdBehavior();


	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================BEGIN BEGIN BEGIN
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================
	///================================================


	//TODO: problems:

	//entity still gets stuck facing down sometimes
	//entitys are too jittery
	//walking into corners back and forth looks bad.


	//solutions:
	//entity can stop momentarily if there is someone in their way, unless they are walking faster

	//entitys can all push each other out of the way and never change direction when stuck in a corner

	//entitys should pathfind their way out of corners and not randomly decide a direction

	//jitter is caused by pushing back and forth. entitys should communicate to decide who is pushing and who is being pushed?


	virtual int walk_to_xy_intelligenthit_avoidothers_pushmain(float x, float y);


	virtual void renderDebugBoxes() override;
};

