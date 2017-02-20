//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




//TODO make comment structure for these


class EventScriptCommand
{
protected:
	string command;
	string comment; //for editor

	//ArrayList<EventParameter> eventParameters

public:
	virtual string toString();
	//public EventCommand toEventCommandWithParameters(){return null;}

	EventScriptCommand();

	EventScriptCommand(const string& command, const string& comment);


	virtual string getCommand();

	virtual string getCommandWithArguments();

	virtual string getComment(); //TODO: handle comments in editor event editor
};


class EventScriptQualifier : public EventScriptCommand
{
public:
	EventScriptQualifier(const string& command, const string& comment);
};


class EventScriptTree
{
private:
	EventData* outerInstance;

public:
	EventScriptTree(EventData* outerInstance);


	//public String toEventText();

	//TODO: should unify all the event parsing stuff into a class here instead of having basically the same thing in both client and editor.
};


class EventData : public AssetData
{
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------
	//
	//
	//
	//	WARNING! EDITING THESE NAMES WILL BREAK JSON DECODING
	//
	//
	//
	//
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------


public:


private:
	
	int type = 0;
	
	string comment = "";
	
	string text = "";


public:

	static Logger log;


	EventData();


	EventData(int id, const string& name, int type, const string& comment, const string& text);


	static EventData* fromBase64ZippedJSON(const string& b64);


	static EventData* fromJSON(const string& json);


	virtual string getTYPEIDString();


	virtual int getType();
	virtual string getComment();
	virtual string getText();

	virtual void setType(int s);
	virtual void setComment(const string& s);
	virtual void setText(const string& s);


	static int TYPE_PROJECT_INITIAL_LOADER; //project cutscene loader, one per project
	static int TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED; //project cutscene loader, one per project

	static int TYPE_MAP_RUN_ONCE_BEFORE_LOAD; //maps will use this for setting the map State, it is run exactly once upon map load, before any objects are created.
	static int TYPE_NORMAL_REPEAT_WHILE_MAP_RUNNING; //all object will use this (door, area, entity, sprite)
	static int TYPE_MAP_DONT_RUN_UNTIL_CALLED; //maps can set this type, which is populated in the EventEditor Events tab. it is an event that any of the objects on this map can call.
	static int TYPE_MAP_RUN_ONCE_AFTER_LOAD; //maps can set this type, it is used for cutscenes


public:
	static ArrayList<EventScriptCommand*>* commandList;
	static ArrayList<EventScriptQualifier*>* qualifierList;


	static EventScriptQualifier* isPlayerTouchingThisArea;
	static EventScriptQualifier* isPlayerWalkingIntoThisDoor;
	static EventScriptQualifier* isPlayerTouchingThisEntity;
	static EventScriptQualifier* isPlayerTouchingAnyEntityUsingThisSprite;
	static EventScriptQualifier* isPlayerWalkingIntoDoor_DOOR;
	static EventScriptQualifier* isPlayerWalkingIntoWarp_WARP;
	static EventScriptQualifier* isActionButtonHeld;
	static EventScriptQualifier* isPlayerAutoPilotOn;
	static EventScriptQualifier* isFlagSet_FLAG;
	static EventScriptQualifier* hasSkillAtLeast_SKILL_FLOAT1;
	static EventScriptQualifier* isCurrentState_STATE;
	static EventScriptQualifier* isPlayerStandingInArea_AREA;
	static EventScriptQualifier* isEntityStandingInArea_ENTITY_AREA;
	static EventScriptQualifier* hourPastOrEqualTo_INT23;
	static EventScriptQualifier* hourLessThan_INT23;
	static EventScriptQualifier* minutePastOrEqualTo_INT59;
	static EventScriptQualifier* minuteLessThan_INT59;
	static EventScriptQualifier* hasMoneyAtLeastAmount_FLOAT;
	static EventScriptQualifier* hasMoneyLessThanAmount_FLOAT;
	static EventScriptQualifier* hasItem_ITEM;
	static EventScriptQualifier* hasGame_GAME;
	static EventScriptQualifier* isPlayerMale;
	static EventScriptQualifier* isPlayerFemale;
	static EventScriptQualifier* isAnyEntityUsingSprite_SPRITE;
	static EventScriptQualifier* isAnyEntityUsingSpriteAtArea_SPRITE_AREA;
	static EventScriptQualifier* isEntitySpawned_ENTITY;
	static EventScriptQualifier* isEntityAtArea_ENTITY_AREA;
	static EventScriptQualifier* isAreaEmpty_AREA;
	static EventScriptQualifier* hasFinishedDialogue_DIALOGUE;
	static EventScriptQualifier* isTextBoxOpen;
	static EventScriptQualifier* isTextAnswerBoxOpen;
	static EventScriptQualifier* isTextAnswerSelected_INT4;
	static EventScriptQualifier* isTextAnswerSelected_STRING;
	static EventScriptQualifier* randomEqualsOneOutOfLessThan_INT;
	static EventScriptQualifier* randomEqualsOneOutOfIncluding_INT;
	static EventScriptQualifier* isAnyMusicPlaying;
	static EventScriptQualifier* isMusicPlaying_MUSIC;
	static EventScriptQualifier* isRaining;
	static EventScriptQualifier* isWindy;
	static EventScriptQualifier* isSnowing;
	static EventScriptQualifier* isFoggy;
	//	public static final EventScriptQualifier isPlayerHolding = new EventScriptQualifier("isPlayerHolding_ITEM","");
	//	public static final EventScriptQualifier isPlayerWearing = new EventScriptQualifier("isPlayerWearing_ITEM","");
	static EventScriptQualifier* isMapOutside;
	static EventScriptQualifier* hasTalkedToThisToday;
	static EventScriptQualifier* hasBeenMinutesSinceFlagSet_FLAG_INT;
	static EventScriptQualifier* hasBeenHoursSinceFlagSet_FLAG_INT23;
	static EventScriptQualifier* hasBeenDaysSinceFlagSet_FLAG_INT;
	static EventScriptQualifier* isThisActivated;
	static EventScriptQualifier* haveSecondsPassedSinceActivated_INT;
	static EventScriptQualifier* haveMinutesPassedSinceActivated_INT;
	static EventScriptQualifier* haveHoursPassedSinceActivated_INT;
	static EventScriptQualifier* haveDaysPassedSinceActivated_INT;
	static EventScriptQualifier* hasActivatedThisEver;
	static EventScriptQualifier* hasActivatedThisSinceEnterRoom;
	static EventScriptQualifier* hasBeenHereEver;
	static EventScriptQualifier* hasBeenHereSinceEnterRoom;
	static EventScriptQualifier* haveSecondsPassedSinceBeenHere_INT;
	static EventScriptQualifier* haveMinutesPassedSinceBeenHere_INT;
	static EventScriptQualifier* haveHoursPassedSinceBeenHere_INT;
	static EventScriptQualifier* haveDaysPassedSinceBeenHere_INT;
	static EventScriptQualifier* isLightOn_LIGHT;


	//commands
	static EventScriptCommand* alwaysBlockWhileNotStandingHere;
	//doesn't delete from the stack, checks every time, continues stack underneath normally.
	//this is an alternative to having an option for deleting the stack when not standing in area
	//instead of deleting the stack
	//this could cause state problems like NPC AI getting stuck off, etc.


	static EventScriptCommand* e00;
	static EventScriptCommand* blockUntilActionButtonPressed; //BLOCK//doesn't delete from the stack until valid, doesn't proceed until it is.
	static EventScriptCommand* blockUntilActionCaptionButtonPressed_STRING; //BLOCK//this will stay in the queue checking if we are standing here, use ACTION_area
	static EventScriptCommand* blockUntilCancelButtonPressed; //BLOCK
	static EventScriptCommand* blockForTicks_INT; //BLOCK
	static EventScriptCommand* blockUntilClockHour_INT23; //BLOCK
	static EventScriptCommand* blockUntilClockMinute_INT59; //BLOCK
	static EventScriptCommand* e000;
	static EventScriptCommand* loadMapState_STATE;
	static EventScriptCommand* runEvent_EVENT;
	static EventScriptCommand* blockUntilEventDone_EVENT;
	static EventScriptCommand* clearThisEvent;
	static EventScriptCommand* clearEvent_EVENT;
	static EventScriptCommand* e001;
	static EventScriptCommand* setThisActivated_BOOL;
	static EventScriptCommand* toggleThisActivated;
	static EventScriptCommand* e002;
	static EventScriptCommand* setLastBeenHereTime;
	static EventScriptCommand* resetLastBeenHereTime;
	static EventScriptCommand* e003;
	static EventScriptCommand* setFlag_FLAG_BOOL;
	static EventScriptCommand* setFlagTrue_FLAG;
	static EventScriptCommand* setFlagFalse_FLAG;
	static EventScriptCommand* e004;
	static EventScriptCommand* giveSkillPoints_SKILL_INT;
	static EventScriptCommand* removeSkillPoints_SKILL_INT;
	static EventScriptCommand* setSkillPoints_SKILL_INT;
	static EventScriptCommand* e005;

	static EventScriptCommand* enterThisDoor;
	static EventScriptCommand* enterThisWarp;
	static EventScriptCommand* enterDoor_DOOR;
	static EventScriptCommand* enterWarp_WARP;
	static EventScriptCommand* changeMap_MAP_AREA;
	static EventScriptCommand* changeMap_MAP_DOOR;
	static EventScriptCommand* changeMap_MAP_WARP;
	static EventScriptCommand* changeMap_MAP_INT_INT;
	static EventScriptCommand* e006;
	static EventScriptCommand* doDialogue_DIALOGUE;
	static EventScriptCommand* doDialogueWithCaption_DIALOGUE;
	static EventScriptCommand* doDialogueIfNew_DIALOGUE;
	static EventScriptCommand* e007;
	static EventScriptCommand* setSpriteBox0_ENTITY;
	static EventScriptCommand* setSpriteBox1_ENTITY;
	static EventScriptCommand* setSpriteBox0_SPRITE;
	static EventScriptCommand* setSpriteBox1_SPRITE;
	static EventScriptCommand* e008;
	static EventScriptCommand* blockUntilTextBoxClosed;
	static EventScriptCommand* blockUntilTextAnswerBoxClosed;
	static EventScriptCommand* e009;
	static EventScriptCommand* doCinematicTextNoBorder_DIALOGUE_INTy;

	static EventScriptCommand* e025;
	static EventScriptCommand* setDoorOpenAnimation_DOOR_BOOLopenClose;
	static EventScriptCommand* setDoorActionIcon_DOOR_BOOLonOff;
	static EventScriptCommand* setDoorDestination_DOOR_DOORdestination;
	static EventScriptCommand* setAreaActionIcon_AREA_BOOLonOff;
	static EventScriptCommand* setWarpDestination_WARP_WARPdestination;


	//public static final EventScriptCommand playVideo_VIDEO = new EventScriptCommand("playVideo_VIDEO","");
	static EventScriptCommand* e010;


	static EventScriptCommand* e012;
	static EventScriptCommand* setCameraNoTarget;
	static EventScriptCommand* setCameraTargetToArea_AREA;
	static EventScriptCommand* setCameraTargetToEntity_ENTITY;
	static EventScriptCommand* setCameraIgnoreBounds_BOOL;
	static EventScriptCommand* setCameraTargetToPlayer;
	static EventScriptCommand* blockUntilCameraReaches_AREA;
	static EventScriptCommand* blockUntilCameraReaches_ENTITY;
	static EventScriptCommand* blockUntilCameraReachesPlayer;
	static EventScriptCommand* pushCameraState;
	static EventScriptCommand* popCameraState;
	static EventScriptCommand* setKeyboardCameraZoom_BOOL;
	static EventScriptCommand* enableKeyboardCameraZoom;
	static EventScriptCommand* disableKeyboardCameraZoom;
	static EventScriptCommand* setCameraAutoZoomByPlayerMovement_BOOL;
	static EventScriptCommand* enableCameraAutoZoomByPlayerMovement;
	static EventScriptCommand* disableCameraAutoZoomByPlayerMovement;
	static EventScriptCommand* setCameraZoom_FLOAT;
	static EventScriptCommand* setCameraSpeed_FLOAT;


	static EventScriptCommand* setPlayerToTempPlayerWithSprite_SPRITE;
	static EventScriptCommand* setPlayerToNormalPlayer;
	static EventScriptCommand* setPlayerExists_BOOL;
	static EventScriptCommand* setPlayerControlsEnabled_BOOL;
	static EventScriptCommand* enablePlayerControls;
	static EventScriptCommand* disablePlayerControls;
	static EventScriptCommand* setPlayerAutoPilot_BOOL;
	static EventScriptCommand* setPlayerShowNameCaption_BOOL;
	static EventScriptCommand* setPlayerShowAccountTypeCaption_BOOL;

	static EventScriptCommand* playerSetBehaviorQueueOnOff_BOOL;
	static EventScriptCommand* playerSetToArea_AREA;
	static EventScriptCommand* playerSetToDoor_DOOR;
	static EventScriptCommand* playerSetToTileXY_INTxTile1X_INTyTile1X;
	static EventScriptCommand* playerWalkToArea_AREA;
	static EventScriptCommand* playerWalkToDoor_DOOR;
	static EventScriptCommand* playerWalkToEntity_ENTITY;
	static EventScriptCommand* playerWalkToTileXY_INTxTile1X_INTyTile1X;
	//	public static final EventScriptCommand playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	static EventScriptCommand* playerBlockUntilReachesArea_AREA;
	static EventScriptCommand* playerBlockUntilReachesDoor_DOOR;
	static EventScriptCommand* playerBlockUntilReachesEntity_ENTITY;
	static EventScriptCommand* playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X;
	static EventScriptCommand* playerWalkToAreaAndBlockUntilThere_AREA;
	static EventScriptCommand* playerWalkToEntityAndBlockUntilThere_ENTITY;
	static EventScriptCommand* playerWalkToDoorAndBlockUntilThere_DOOR;
	static EventScriptCommand* playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X;
	static EventScriptCommand* playerStandAndShuffle;
	//	public static final EventScriptCommand playerStandAndShuffleAndFacePlayer = new EventScriptCommand("playerStandAndShuffleAndFacePlayer","");
	static EventScriptCommand* playerStandAndShuffleAndFaceEntity_ENTITY;
	//	public static final EventScriptCommand playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerDoAnimationByNameOnce_STRINGanimationName = new EventScriptCommand("playerDoAnimationByNameOnce_STRINGanimationName","");
	//	public static final EventScriptCommand playerDoAnimationByNameLoop_STRINGanimationName = new EventScriptCommand("playerDoAnimationByNameLoop_STRINGanimationName","");
	static EventScriptCommand* playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame;
	static EventScriptCommand* playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame;
	static EventScriptCommand* playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks;
	static EventScriptCommand* playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	static EventScriptCommand* playerStopAnimating;
	static EventScriptCommand* playerSetGlobalAnimationDisabled_BOOL;
	static EventScriptCommand* playerSetMovementSpeed_INTticksPerPixel;
	static EventScriptCommand* playerSetFaceMovementDirection_STRINGdirection;
	//	public static final EventScriptCommand playerSetNonWalkable_BOOL = new EventScriptCommand("playerSetNonWalkable_BOOL","");
	//	public static final EventScriptCommand playerSetPushable_BOOL = new EventScriptCommand("playerSetPushable_BOOL","");
	static EventScriptCommand* playerSetToAlpha_FLOAT;
	//public static final EventScriptCommand playerFadeOutDelete = new EventScriptCommand("playerFadeOutDelete","");
	//public static final EventScriptCommand playerDeleteInstantly = new EventScriptCommand("playerDeleteInstantly","");


	//	public static final EventScriptCommand thisEntitySetBehaviorQueueOnOff_BOOL = new EventScriptCommand("thisEntitySetBehaviorQueueOnOff_BOOL","");
	//	public static final EventScriptCommand thisEntitySetToArea_AREA = new EventScriptCommand("thisEntitySetToArea_AREA","");
	//	public static final EventScriptCommand thisEntitySetToDoor_DOOR = new EventScriptCommand("thisEntitySetToDoor_DOOR","");
	//	public static final EventScriptCommand thisEntitySetToTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("thisEntitySetToTileXY_INTxTile1X_INTyTile1X","");
	//	public static final EventScriptCommand thisEntityWalkToArea_AREA = new EventScriptCommand("thisEntityWalkToArea_AREA","");
	//	public static final EventScriptCommand thisEntityWalkToDoor_DOOR = new EventScriptCommand("thisEntityWalkToDoor_DOOR","");
	//	public static final EventScriptCommand thisEntityWalkToEntity_ENTITY = new EventScriptCommand("thisEntityWalkToEntity_ENTITY","");
	//	public static final EventScriptCommand thisEntityWalkToTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("thisEntityWalkToTileXY_INTxTile1X_INTyTile1X","");
	//	public static final EventScriptCommand thisEntityMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("thisEntityMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("thisEntityMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("thisEntityMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("thisEntityMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesArea_AREA = new EventScriptCommand("thisEntityBlockUntilReachesArea_AREA","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesDoor_DOOR = new EventScriptCommand("thisEntityBlockUntilReachesDoor_DOOR","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesEntity_ENTITY = new EventScriptCommand("thisEntityBlockUntilReachesEntity_ENTITY","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("thisEntityBlockUntilReachesTileXY_INTxTile1X_INTyTile1X","");
	//	public static final EventScriptCommand thisEntityStandAndShuffle = new EventScriptCommand("thisEntityStandAndShuffle","");
	//	public static final EventScriptCommand thisEntityStandAndShuffleAndFacePlayer = new EventScriptCommand("thisEntityStandAndShuffleAndFacePlayer","");
	//	public static final EventScriptCommand thisEntityStandAndShuffleAndFaceEntity_ENTITY = new EventScriptCommand("thisEntityStandAndShuffleAndFaceEntity_ENTITY","");
	//	public static final EventScriptCommand thisEntityAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntitySetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("thisEntitySetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityStopAnimating = new EventScriptCommand("thisEntityStopAnimating","");
	//	public static final EventScriptCommand thisEntitySetGlobalAnimationDisabled_BOOL = new EventScriptCommand("thisEntitySetGlobalAnimationDisabled_BOOL","");
	//	public static final EventScriptCommand thisEntitySetMovementSpeed_INTticksPerPixel = new EventScriptCommand("thisEntitySetMovementSpeed_INTticksPerPixel","");
	//	public static final EventScriptCommand thisEntitySetFaceMovementDirection_STRINGdirection = new EventScriptCommand("thisEntitySetFaceMovementDirection_STRINGdirection","");
	//	public static final EventScriptCommand thisEntitySetNonWalkable_BOOL = new EventScriptCommand("thisEntitySetNonWalkable_BOOL","");
	//	public static final EventScriptCommand thisEntitySetPushable_BOOL = new EventScriptCommand("thisEntitySetPushable_BOOL","");
	//	public static final EventScriptCommand thisEntitySetToAlpha_FLOAT = new EventScriptCommand("thisEntitySetToAlpha_FLOAT","");
	//	public static final EventScriptCommand thisEntityFadeOutDelete = new EventScriptCommand("thisEntityFadeOutDelete","");
	//	public static final EventScriptCommand thisEntityDeleteInstantly = new EventScriptCommand("thisEntityDeleteInstantly","");


	static EventScriptCommand* e024;
	static EventScriptCommand* entitySetBehaviorQueueOnOff_ENTITY_BOOL;
	static EventScriptCommand* entitySetToArea_ENTITY_AREA;
	static EventScriptCommand* entitySetToDoor_ENTITY_DOOR;
	static EventScriptCommand* entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X;
	static EventScriptCommand* entityWalkToArea_ENTITY_AREA;
	static EventScriptCommand* entityWalkToDoor_ENTITY_DOOR;
	static EventScriptCommand* entityWalkToEntity_ENTITY_ENTITY;
	static EventScriptCommand* entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X;
	static EventScriptCommand* entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	static EventScriptCommand* entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	static EventScriptCommand* entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	static EventScriptCommand* entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	static EventScriptCommand* entityBlockUntilReachesArea_ENTITY_AREA;
	static EventScriptCommand* entityBlockUntilReachesDoor_ENTITY_DOOR;
	static EventScriptCommand* entityBlockUntilReachesEntity_ENTITY_ENTITY;
	static EventScriptCommand* entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X;
	static EventScriptCommand* entityWalkToAreaAndBlockUntilThere_ENTITY_AREA;
	static EventScriptCommand* entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY;
	static EventScriptCommand* entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR;
	static EventScriptCommand* entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X;
	static EventScriptCommand* entityStandAndShuffle_ENTITY;
	static EventScriptCommand* entityStandAndShuffleAndFacePlayer_ENTITY;
	static EventScriptCommand* entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY;
	static EventScriptCommand* entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks;
	static EventScriptCommand* entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	static EventScriptCommand* entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks;
	static EventScriptCommand* entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	static EventScriptCommand* entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks;
	static EventScriptCommand* entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName;
	static EventScriptCommand* entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame;
	static EventScriptCommand* entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame;
	static EventScriptCommand* entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks;
	static EventScriptCommand* entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	static EventScriptCommand* entityStopAnimating_ENTITY;
	static EventScriptCommand* entitySetGlobalAnimationDisabled_ENTITY_BOOL;
	static EventScriptCommand* entitySetMovementSpeed_ENTITY_INTticksPerPixel;
	static EventScriptCommand* entitySetFaceMovementDirection_ENTITY_STRINGdirection;
	static EventScriptCommand* entitySetNonWalkable_ENTITY_BOOL;
	static EventScriptCommand* entitySetPushable_ENTITY_BOOL;
	static EventScriptCommand* entitySetToAlpha_ENTITY_FLOAT;
	static EventScriptCommand* entityFadeOutDelete_ENTITY;
	static EventScriptCommand* entityDeleteInstantly_ENTITY;

	static EventScriptCommand* e016;
	static EventScriptCommand* spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA;
	static EventScriptCommand* spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA;
	static EventScriptCommand* spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA;
	static EventScriptCommand* spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA;
	static EventScriptCommand* e017;
	static EventScriptCommand* createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy;
	static EventScriptCommand* createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy;
	static EventScriptCommand* createScreenSpriteUnderText_SPRITE_INTx_INTy;
	static EventScriptCommand* createScreenSpriteOverText_SPRITE_INTx_INTy;


	static EventScriptCommand* e026;
	static EventScriptCommand* giveItem_ITEM;
	static EventScriptCommand* takeItem_ITEM;
	static EventScriptCommand* giveGame_GAME;
	static EventScriptCommand* takeMoney_FLOAT;
	static EventScriptCommand* giveMoney_FLOAT;

	static EventScriptCommand* e027;
	static EventScriptCommand* playSound_SOUND;
	static EventScriptCommand* playSound_SOUND_FLOATvol;
	static EventScriptCommand* playSound_SOUND_FLOATvol_FLOATpitch_INTtimes;
	static EventScriptCommand* playMusicOnce_MUSIC;
	static EventScriptCommand* playMusicLoop_MUSIC;
	static EventScriptCommand* playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop;
	static EventScriptCommand* stopAllMusic;
	static EventScriptCommand* stopMusic_MUSIC;
	static EventScriptCommand* fadeOutMusic_MUSIC_INT;
	static EventScriptCommand* blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC;
	static EventScriptCommand* blockUntilMusicDone_MUSIC;
	static EventScriptCommand* fadeOutAllMusic_INT;
	static EventScriptCommand* blockUntilAllMusicDone;

	static EventScriptCommand* e028;
	static EventScriptCommand* shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake;
	static EventScriptCommand* fadeToBlack_INTticks;
	static EventScriptCommand* fadeFromBlack_INTticks;
	static EventScriptCommand* fadeToWhite_INTticks;
	static EventScriptCommand* fadeFromWhite_INTticks;
	static EventScriptCommand* e029;
	static EventScriptCommand* fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	static EventScriptCommand* fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha;
	static EventScriptCommand* fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	static EventScriptCommand* setInstantOverlay_INTr_INTg_INTb_FLOATa;
	static EventScriptCommand* clearOverlay;

	static EventScriptCommand* fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	static EventScriptCommand* setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa;
	static EventScriptCommand* clearOverlayUnderLights;

	static EventScriptCommand* fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	static EventScriptCommand* setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa;
	static EventScriptCommand* clearOverlayGroundLayer;

	static EventScriptCommand* e030;
	static EventScriptCommand* setLetterbox_BOOL;
	static EventScriptCommand* setLetterbox_BOOL_INTticks;
	static EventScriptCommand* setLetterbox_BOOL_INTticks_INTsize;
	static EventScriptCommand* setLetterbox_BOOL_INTticks_FLOATsize;
	static EventScriptCommand* setBlur_BOOL;
	static EventScriptCommand* setMosaic_BOOL;
	static EventScriptCommand* setHBlankWave_BOOL;
	static EventScriptCommand* setRotate_BOOL;
	static EventScriptCommand* setBlackAndWhite_BOOL;
	static EventScriptCommand* setInvertedColors_BOOL;
	static EventScriptCommand* set8BitMode_BOOL;
	static EventScriptCommand* e031;
	static EventScriptCommand* setEngineSpeed_FLOAT;
	static EventScriptCommand* e032;
	static EventScriptCommand* toggleLightOnOff_LIGHT;
	static EventScriptCommand* setLightOnOff_LIGHT_BOOL;
	static EventScriptCommand* setLightFlicker_LIGHT_BOOL;
	static EventScriptCommand* toggleAllLightsOnOff;
	static EventScriptCommand* setAllLightsOnOff_BOOL;
	static EventScriptCommand* e033;
	static EventScriptCommand* setRandomSpawn_BOOL;
	static EventScriptCommand* deleteRandoms;
	static EventScriptCommand* e034;
	static EventScriptCommand* makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb;
	static EventScriptCommand* makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb;
	static EventScriptCommand* makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb;
	static EventScriptCommand* makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb;
	static EventScriptCommand* setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks;


	static EventScriptCommand* e035;
	static EventScriptCommand* setShowClockCaption_BOOL;
	static EventScriptCommand* setShowDayCaption_BOOL;
	static EventScriptCommand* setShowMoneyCaption_BOOL;
	static EventScriptCommand* setShowAllStatusBarCaptions_BOOL;
	static EventScriptCommand* setShowStatusBar_BOOL;

	static EventScriptCommand* setShowNDButton_BOOL;
	static EventScriptCommand* setShowGameStoreButton_BOOL;
	static EventScriptCommand* setShowStuffButton_BOOL;
	static EventScriptCommand* setShowAllButtons_BOOL;

	static EventScriptCommand* setNDEnabled_BOOL;
	static EventScriptCommand* setGameStoreMenuEnabled_BOOL;
	static EventScriptCommand* setStuffMenuEnabled_BOOL;
	static EventScriptCommand* setAllMenusAndNDEnabled_BOOL;


	static EventScriptCommand* e046;
	static EventScriptCommand* setClockUnknown;
	static EventScriptCommand* setClockNormal;
	static EventScriptCommand* setTimePaused_BOOL;
	static EventScriptCommand* setTimeFastForward;
	static EventScriptCommand* setTimeNormalSpeed;
	static EventScriptCommand* e037;


	static EventScriptCommand* setNDOpen_BOOL;
	static EventScriptCommand* startGame;
	static EventScriptCommand* startBobsGameOnStadiumScreen_AREA;
	static EventScriptCommand* blockUntilBobsGameDead;
	static EventScriptCommand* showLoginScreen;
	//public static final EventScriptCommand closeND = new EventScriptCommand("closeND","");

	static EventScriptCommand* e038;
	static EventScriptCommand* closeAllMenusAndND;

	//public static final EventScriptCommand enableAllMenus = new EventScriptCommand("enableAllMenus","");
	static EventScriptCommand* e039;
	static EventScriptCommand* openStuffMenu;
	static EventScriptCommand* openItemsMenu;
	static EventScriptCommand* openLogMenu;
	static EventScriptCommand* openStatusMenu;
	static EventScriptCommand* openFriendsMenu;
	static EventScriptCommand* openSettingsMenu;
	static EventScriptCommand* openGameStoreMenu;

	//	static final EventScriptCommand e040 = new EventScriptCommand();
	//	public static final EventScriptCommand pushGameState = new EventScriptCommand("pushGameState","");
	//	public static final EventScriptCommand popGameState = new EventScriptCommand("popGameState","");
	//	static final EventScriptCommand e041 = new EventScriptCommand();
	//	public static final EventScriptCommand showTitleScreen = new EventScriptCommand("showTitleScreen","");
	//	public static final EventScriptCommand showCinemaEvent = new EventScriptCommand("showCinemaEvent","");
	//	public static final EventScriptCommand runGlobalEvent = new EventScriptCommand("runGlobalEvent","");
	//	static final EventScriptCommand e042 = new EventScriptCommand();
};

