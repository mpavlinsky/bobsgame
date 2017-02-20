//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




#include "src/Engine/network/ServerObject.h"

class ServerObject;
class Door;
class EventCommand;
class EventData;

class Event : public ServerObject
{
public:
	static Logger log;


private:
	bool addedToQueue = false;
	long long timeAddedToQueue = 0;


	bool blockWhileNotHere = false;

	long long ticksCounter = 0;


public:
	Sprite* sprite = nullptr;
	Map* map;
	Door* door = nullptr;
	Area* area = nullptr;
	Entity* entity = nullptr;


	EventCommand* commandTree = nullptr;
	EventCommand* currentCommand = nullptr;


private:
	EventData* data;


public:
	Event(Engine* g, int id);


	Event(Engine* g, EventData* eventData);


	virtual EventData* getData();

	virtual int getID();
	virtual string getName();
	virtual int type();
	virtual string getComment();
	virtual string text();

	virtual string getTYPEIDString();

	virtual void setID(int id);
	virtual void setName(const string& name);
	virtual void setType(int type);
	virtual void setComment(const string& comment);
	virtual void setText(const string& text);


	//The following method was originally marked 'synchronized':
	virtual void setData_S(EventData* eventData);


	virtual Map* getMap();


	virtual Map* getCurrentMap() override;


	virtual bool getWasAddedToQueue();

	virtual void setAddedToQueue();


	virtual void reset();


private:
	void parseEventString(string s);


public:
	virtual void run();


	virtual void getNextCommandInParent();


	virtual void getNextCommand();


private:
	void getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(bool b);


public:
	virtual void doCommand();


private:
	void isPlayerTouchingThisArea();


	void isPlayerWalkingIntoThisDoor();


	void isPlayerTouchingThisEntity();


	void isPlayerTouchingAnyEntityUsingThisSprite();


	void isPlayerWalkingIntoDoor_DOOR();


	void isPlayerWalkingIntoWarp_WARP();

	void isPlayerAutoPilotOn();


	void isActionButtonHeld();


	void isFlagSet_FLAG();


	void hasSkillAtLeast_SKILL_FLOAT1();


	void isCurrentState_STATE();


	void isPlayerStandingInArea_AREA();


	void isEntityStandingInArea_ENTITY_AREA();


	void hourPastOrEqualTo_INT23();


	void hourLessThan_INT23();


	void minutePastOrEqualTo_INT59();


	void minuteLessThan_INT59();


	void hasMoneyAtLeastAmount_FLOAT();


	void hasMoneyLessThanAmount_FLOAT();


	void hasItem_ITEM();


	void hasGame_GAME();


	void isPlayerMale();


	void isPlayerFemale();


	void isAnyEntityUsingSprite_SPRITE();


	void isAnyEntityUsingSpriteAtArea_SPRITE_AREA();


	void isEntitySpawned_ENTITY();


	void isEntityAtArea_ENTITY_AREA();


	void isAreaEmpty_AREA();


	void hasFinishedDialogue_DIALOGUE();


	void isTextBoxOpen();


	void isTextAnswerBoxOpen();


	void isTextAnswerSelected_INT4();


	void isTextAnswerSelected_STRING();


	void randomEqualsOneOutOfLessThan_INT();


	void randomEqualsOneOutOfIncluding_INT();


	void isAnyMusicPlaying();


	void isMusicPlaying();


	void isRaining();


	void isWindy();


	void isSnowing();


	void isFoggy();


	//	
	//	private void isPlayerHolding()/
	//	{
	//		// TODO Auto-generated method stub
	//
	//	}
	//
	//	
	//	private void isPlayerWearing()
	//	{
	//		// TODO Auto-generated method stub
	//
	//	}


	void isMapOutside();


	void hasTalkedToThisToday();


	void hasBeenMinutesSinceFlagSet_FLAG_INT();


	void hasBeenHoursSinceFlagSet_FLAG_INT23();


	void hasBeenDaysSinceFlagSet_FLAG_INT();


	void isThisActivated();


	void haveSecondsPassedSinceActivated_INT();


	void haveMinutesPassedSinceActivated_INT();


	void haveHoursPassedSinceActivated_INT();


	void haveDaysPassedSinceActivated_INT();


	void hasActivatedThisEver();


	void hasActivatedThisSinceEnterRoom();


	void hasBeenHereEver();


	void hasBeenHereSinceEnterRoom();


	void haveSecondsPassedSinceBeenHere_INT();

	void haveMinutesPassedSinceBeenHere_INT();


	void haveDaysPassedSinceBeenHere_INT();


	void haveHoursPassedSinceBeenHere_INT();


	void isLightOn_LIGHT(); //(INT)


	void alwaysBlockWhileNotStandingHere();


	void blockUntilActionButtonPressed();


	void blockUntilActionCaptionButtonPressed_STRING();


	void blockUntilCancelButtonPressed();


	void blockForTicks_INT();


	void blockUntilClockHour_INT23();


	void blockUntilClockMinute_INT59();


	void loadMapState_STATE();


	void runEvent_EVENT();


	void blockUntilEventDone_EVENT();


	void clearEvent_EVENT();

	void clearThisEvent();


	void setThisActivated_BOOL();

	void toggleThisActivated();


	void setLastBeenHereTime();

	void resetLastBeenHereTime();


	void setFlag_FLAG_BOOL();

	void setFlagTrue_FLAG();

	void setFlagFalse_FLAG();


	void giveSkillPoints_SKILL_INT();


	void removeSkillPoints_SKILL_INT();


	void setSkillPoints_SKILL_INT();


	void enterThisDoor();

	void enterThisWarp();


	void enterDoor_DOOR();


	void enterWarp_WARP();


	void changeMap_MAP_AREA();


	void changeMap_MAP_DOOR();


	void changeMap_MAP_WARP();


	void changeMap_MAP_INT_INT();


	void doDialogue_DIALOGUE();


	void doDialogueWithCaption_DIALOGUE();


	void doDialogueIfNew_DIALOGUE();


	void setSpriteBox0_ENTITY();


	void setSpriteBox1_ENTITY();


	void setSpriteBox0_SPRITE();


	void setSpriteBox1_SPRITE();


	void blockUntilTextBoxClosed();


	void blockUntilTextAnswerBoxClosed();


	void doCinematicTextNoBorder_DIALOGUE_INTy();


	void setDoorOpenAnimation_DOOR_BOOLopenClose(); //(DOOR,BOOL)


	void setDoorActionIcon_DOOR_BOOLonOff(); //(DOOR,BOOL)

	void setDoorDestination_DOOR_DOORdestination(); //(DOOR,DOORdestination)


	void setAreaActionIcon_AREA_BOOLonOff(); //(DOOR,BOOL)

	void setWarpDestination_WARP_WARPdestination(); //(WARP,WARPdestination)


	//	
	//	private void playVideo_VIDEO()//(VIDEO)
	//	{
	//		// TODO
	//
	//		getNextCommand();
	//	}


	void setPlayerToTempPlayerWithSprite_SPRITE();


	void setPlayerToNormalPlayer();


	void setPlayerExists_BOOL();


	void setPlayerControlsEnabled_BOOL();

	void enablePlayerControls();

	void disablePlayerControls();


	void setPlayerAutoPilot_BOOL();


	void setPlayerShowNameCaption_BOOL();

	void setPlayerShowAccountTypeCaption_BOOL();


	void playerSetBehaviorQueueOnOff_BOOL(); //(ENTITY)

	void playerSetToArea_AREA();

	void playerSetToDoor_DOOR();

	void playerSetToTileXY_INTxTile1X_INTyTile1X();

	void playerWalkToArea_AREA();


	void playerWalkToDoor_DOOR();


	void playerWalkToEntity_ENTITY();


	void playerWalkToTileXY_INTxTile1X_INTyTile1X();


	void playerBlockUntilReachesArea_AREA(); //TODO rename these


	void playerBlockUntilReachesEntity_ENTITY();


	void playerBlockUntilReachesDoor_DOOR();


	void playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X();


	void playerWalkToAreaAndBlockUntilThere_AREA();


	void playerWalkToEntityAndBlockUntilThere_ENTITY();


	void playerWalkToDoorAndBlockUntilThere_DOOR();


	void playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X();


	void playerStandAndShuffle(); //(ENTITY)


	void playerStandAndShuffleAndFaceEntity_ENTITY(); //(ENTITY)


	void playerSetFaceMovementDirection_STRINGdirection(); //(ENTITY,INT)

	void playerSetMovementSpeed_INTticksPerPixel(); //(ENTITY,INT)


	void playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks(); //(INTticksPerFrame)


	void playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks(); //(INTticksPerFrame)


	void playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame(); //(INTticksPerFrame)


	void playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame(); //(INTticksPerFrame)


	void playerStopAnimating();


	void playerSetGlobalAnimationDisabled_BOOL();


	void playerSetToAlpha_FLOAT();


	void entitySetBehaviorQueueOnOff_ENTITY_BOOL(); //(ENTITY)

	void entitySetToArea_ENTITY_AREA();

	void entitySetToDoor_ENTITY_DOOR();

	void entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X();

	void entityWalkToArea_ENTITY_AREA();


	void entityWalkToDoor_ENTITY_DOOR();


	void entityWalkToEntity_ENTITY_ENTITY();

	void entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X();

	void entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal(); //(ENTITY,AREA,BOOLwalk,BOOLhit,BOOLpath,BOOLanim,BOOLdiag)


	void entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal(); //(ENTITY,ENTITY,BOOLwalk,BOOLhit,BOOLpath,BOOLanim,BOOLdiag)


	void entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal(); //(ENTITY,ENTITY,BOOLwalk,BOOLhit,BOOLpath,BOOLanim,BOOLdiag)

	void entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal(); //(ENTITY,ENTITY,BOOLwalk,BOOLhit,BOOLpath,BOOLanim,BOOLdiag)


	void entityBlockUntilReachesArea_ENTITY_AREA();


	void entityBlockUntilReachesEntity_ENTITY_ENTITY();


	void entityBlockUntilReachesDoor_ENTITY_DOOR();


	void entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X();


	void entityWalkToAreaAndBlockUntilThere_ENTITY_AREA();


	void entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY();


	void entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR();


	void entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X();


	void entityStandAndShuffle_ENTITY(); //(ENTITY)


	void entityStandAndShuffleAndFacePlayer_ENTITY(); //(ENTITY)


	void entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY(); //(ENTITY)


	void entitySetFaceMovementDirection_ENTITY_STRINGdirection(); //(ENTITY,INT)

	void entitySetMovementSpeed_ENTITY_INTticksPerPixel(); //(ENTITY,INT)


	void entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks(); //(INTticksPerFrame)


	void entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks();


	void entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks(); //(INTticksPerFrame)


	void entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks(); //(INTticksPerFrame)


	void entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks(); //(INTticksPerFrame)


	void entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName(); //(INTticksPerFrame)


	void entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame(); //(INTticksPerFrame)


	void entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame(); //(INTticksPerFrame)

	void entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks(); //(INTticksPerFrame)


	void entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks(); //(INTticksPerFrame)


	void entityStopAnimating_ENTITY();


	void entitySetGlobalAnimationDisabled_ENTITY_BOOL();


	void entitySetNonWalkable_ENTITY_BOOL();


	void entitySetPushable_ENTITY_BOOL();


	void entityFadeOutDelete_ENTITY();


	void entityDeleteInstantly_ENTITY();


	void entitySetToAlpha_ENTITY_FLOAT();


	void spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA(); //(SPRITE,STRINGentityIdent,AREA)


	void spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA(); //(SPRITE,STRINGentityIdent,AREA)


	void spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA(); //(SPRITE,STRINGentityIdent,AREA)


	void spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA(); //(SPRITE,STRINGentityIdent,AREA)


	void createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy(); //(SPRITE,FLOATx,FLOATy)


	void createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy(); //(SPRITE,FLOATx,FLOATy)


	void createScreenSpriteUnderText_SPRITE_INTx_INTy(); //(SPRITE,INTx,INTy)


	void createScreenSpriteOverText_SPRITE_INTx_INTy(); //(SPRITE,INTx,INTy)


	void setCameraTarget_AREA(); //(AREA)


	void setCameraTarget_ENTITY(); //(ENTITY)


	void setCameraNoTarget();


	void setCameraIgnoreBounds_BOOL();


	void setCameraTargetToPlayer();


	void blockUntilCameraReaches_AREA();


	void blockUntilCameraReaches_ENTITY();


	void blockUntilCameraReachesPlayer();


	void pushCameraState();


	void popCameraState();


	void setKeyboardCameraZoom_BOOL();

	void enableKeyboardCameraZoom();

	void disableKeyboardCameraZoom();


	void setCameraAutoZoomByPlayerMovement_BOOL(); //(BOOL)

	void enableCameraAutoZoomByPlayerMovement(); //(BOOL)

	void disableCameraAutoZoomByPlayerMovement(); //(BOOL)


	void setCameraZoom_FLOAT(); //(FLOAT)


	void setCameraSpeed_FLOAT(); //(FLOAT)


	//	
	//	private void setEntityProperty_ENTITY_STRINGpropertyName_BOOL()//(ENTITY,STRINGpropertyName,BOOL)
	//	{
	//		Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	//
	//		boolean b = currentCommand.parameterList.get(p++).b;
	//
	//		// TODO
	//
	//		getNextCommand();
	//
	//	}


	void giveItem_ITEM(); //(ITEM)


	void takeItem_ITEM(); //(ITEM)


	void giveGame_GAME(); //(GAME)


	void takeMoney_FLOAT(); //(FLOAT)


	void giveMoney_FLOAT(); //(FLOAT)


	void playSound_SOUND(); //(SOUND)


	void playSound_SOUND_FLOATvol();


	void playSound_SOUND_FLOATvol_FLOATpitch_INTtimes();


	void playMusicOnce_MUSIC();


	void playMusicLoop_MUSIC();


	void playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop();


	void stopMusic_MUSIC();

	void stopAllMusic();


	void blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC();


	void blockUntilMusicDone_MUSIC();


	void blockUntilAllMusicDone();


	void fadeOutMusic_MUSIC_INT();


	void fadeOutAllMusic_INT();


	void shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake();


	void fadeToBlack_INTticks();


	void fadeFromBlack_INTticks();


	void fadeToWhite_INTticks();


	void fadeFromWhite_INTticks();


	void fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha();

	void fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha();

	void fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha();

	void setInstantOverlay_INTr_INTg_INTb_FLOATa();


	void clearOverlay();


	void fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha();


	void setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa();


	void clearOverlayUnderLights();


	void fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha();


	void setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa();


	void clearOverlayGroundLayer();


	void setLetterbox_BOOL();


	void setLetterbox_BOOL_INTticks(); //(BOOL_INTticks)


	void setLetterbox_BOOL_INTticks_INTsize(); //(BOOL)


	void setLetterbox_BOOL_INTticks_FLOATsize(); //(BOOL)


	void setBlur_BOOL(); //(BOOL)


	void setMosaic_BOOL(); //(BOOL)


	void setHBlankWave_BOOL(); //(BOOL)


	void setRotate_BOOL(); //(BOOL)


	void setBlackAndWhite_BOOL(); //(BOOL)


	void setInvertedColors_BOOL(); //(BOOL)


	void set8BitMode_BOOL(); //(BOOL)


	void setEngineSpeed_FLOAT(); //(INT)


	void toggleLightOnOff_LIGHT(); //(LIGHT)


	void setLightOnOff_LIGHT_BOOL(); //(LIGHT,BOOL)


	void setLightFlicker_LIGHT_BOOL(); //(LIGHT,BOOL)


	void toggleAllLightsOnOff();


	void setAllLightsOnOff_BOOL(); //(BOOL)


	void setRandomSpawn_BOOL();


	void deleteRandoms();


	void makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb();


	void makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb();


	void makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb();

	void makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb(); //(STRING,INTsec,INTx,INTy,INTr,INTg,INTb)

	void setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks();


	void setShowClockCaption_BOOL();

	void setShowDayCaption_BOOL();

	void setShowMoneyCaption_BOOL();


	void setShowAllStatusBarCaptions_BOOL();


	void setShowStatusBar_BOOL();

	void setShowNDButton_BOOL();

	void setShowGameStoreButton_BOOL();

	void setShowStuffButton_BOOL();


	void setShowAllButtons_BOOL();


	void setNDEnabled_BOOL();


	void setGameStoreMenuEnabled_BOOL();


	void setStuffMenuEnabled_BOOL();


	void setAllMenusAndNDEnabled_BOOL();


	void setClockUnknown();


	void setClockNormal();


	void setTimePaused_BOOL();


	void setTimeFastForward();


	void setTimeNormalSpeed();


	void setNDOpen_BOOL();


	void startGame();


	void startBobsGameOnStadiumScreen_AREA();


	void blockUntilBobsGameDead();


	void showLoginScreen();


	void closeAllMenusAndND();


	void openStuffMenu();


	void openItemsMenu();


	void openLogMenu();


	void openStatusMenu();


	void openFriendsMenu();


	void openSettingsMenu();


	void openGameStoreMenu();


	void pushGameState();


	void popGameState();


	void showTitleScreen();


	void showCinemaEvent();


	void runGlobalEvent();
};

