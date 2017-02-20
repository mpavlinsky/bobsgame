#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger EventData::log = Logger("EventData");


class EventScriptCommand;
class EventScriptQualifier;


EventData::EventData()
{ //=========================================================================================================================
}

EventData::EventData(int id, const string& name, int type, const string& comment, const string& text)
{ //=========================================================================================================================

	//AssetData(id, name);
	this->id = id;
	this->name = name;

	this->type = type;
	this->comment = comment;
	this->text = text;
}

EventData* EventData::fromBase64ZippedJSON(const string& b64)
{ //===============================================================================================


	string json = FileUtils::unzipBase64StringToString(b64);

	//Gson gson = new Gson();
	//EventData data = gson.fromJson(json,EventData.class);

	return fromJSON(json);
}

EventData* EventData::fromJSON(const string& json)
{ //===============================================================================================

	//Gson* gson = new Gson();
	EventData* data = nullptr;//gson->fromJson(json, EventData::typeid);


	return data;
}

string EventData::getTYPEIDString()
{ //===============================================================================================
	return string("EVENT.") + to_string(getID());
}

int EventData::getType()
{
	return type;
}

string EventData::getComment()
{
	return comment;
}

string EventData::getText()
{
	return text;
}

void EventData::setType(int s)
{
	this->type = s;
}

void EventData::setComment(const string& s)
{
	this->comment = s;
}

void EventData::setText(const string& s)
{
	this->text = s;
}

int EventData::TYPE_PROJECT_INITIAL_LOADER = -3;
int EventData::TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED = -2;
int EventData::TYPE_MAP_RUN_ONCE_BEFORE_LOAD = -1;
int EventData::TYPE_NORMAL_REPEAT_WHILE_MAP_RUNNING = 0;
int EventData::TYPE_MAP_DONT_RUN_UNTIL_CALLED = 1;
int EventData::TYPE_MAP_RUN_ONCE_AFTER_LOAD = 2;

EventScriptTree::EventScriptTree(EventData* outerInstance) : outerInstance(outerInstance)
{
}

string EventScriptCommand::toString()
{
	return getCommandWithArguments();
}

EventScriptCommand::EventScriptCommand()
{
	this->command = "---";
}

EventScriptCommand::EventScriptCommand(const string& command, const string& comment)
{
	this->command = command;
	this->comment = comment;

	EventData::commandList->add(this);
}

string EventScriptCommand::getCommand()
{
	if (command.find("_") != string::npos)
	{
		return command.substr(0, command.find("_"));
	}
	return command;
}

string EventScriptCommand::getCommandWithArguments()
{
	return command;
}

string EventScriptCommand::getComment()
{
	return comment;
}

EventScriptQualifier::EventScriptQualifier(const string& command, const string& comment)
{
	this->command = command;
	this->comment = comment;

	EventData::qualifierList->add(this);
}

ArrayList<EventScriptCommand*>* EventData::commandList = new ArrayList<EventScriptCommand*>();
ArrayList<EventScriptQualifier*>* EventData::qualifierList = new ArrayList<EventScriptQualifier*>();
EventScriptQualifier* EventData::isPlayerTouchingThisArea = new EventScriptQualifier("isPlayerTouchingThisArea", "");
EventScriptQualifier* EventData::isPlayerWalkingIntoThisDoor = new EventScriptQualifier("isPlayerWalkingIntoThisDoor", "");
EventScriptQualifier* EventData::isPlayerTouchingThisEntity = new EventScriptQualifier("isPlayerTouchingThisEntity", "");
EventScriptQualifier* EventData::isPlayerTouchingAnyEntityUsingThisSprite = new EventScriptQualifier("isPlayerTouchingAnyEntityUsingThisSprite", "");
EventScriptQualifier* EventData::isPlayerWalkingIntoDoor_DOOR = new EventScriptQualifier("isPlayerWalkingIntoDoor_DOOR", "");
EventScriptQualifier* EventData::isPlayerWalkingIntoWarp_WARP = new EventScriptQualifier("isPlayerWalkingIntoWarp_WARP", "");
EventScriptQualifier* EventData::isActionButtonHeld = new EventScriptQualifier("isActionButtonHeld", "");
EventScriptQualifier* EventData::isPlayerAutoPilotOn = new EventScriptQualifier("isPlayerAutoPilotOn", "");
EventScriptQualifier* EventData::isFlagSet_FLAG = new EventScriptQualifier("isFlagSet_FLAG", "");
EventScriptQualifier* EventData::hasSkillAtLeast_SKILL_FLOAT1 = new EventScriptQualifier("hasSkillAtLeast_SKILL_FLOAT1", "");
EventScriptQualifier* EventData::isCurrentState_STATE = new EventScriptQualifier("isCurrentState_STATE", "");
EventScriptQualifier* EventData::isPlayerStandingInArea_AREA = new EventScriptQualifier("isPlayerStandingInArea_AREA", "");
EventScriptQualifier* EventData::isEntityStandingInArea_ENTITY_AREA = new EventScriptQualifier("isEntityStandingInArea_ENTITY_AREA", "");
EventScriptQualifier* EventData::hourPastOrEqualTo_INT23 = new EventScriptQualifier("hourPastOrEqualTo_INT23", "");
EventScriptQualifier* EventData::hourLessThan_INT23 = new EventScriptQualifier("hourLessThan_INT23", "");
EventScriptQualifier* EventData::minutePastOrEqualTo_INT59 = new EventScriptQualifier("minutePastOrEqualTo_INT59", "");
EventScriptQualifier* EventData::minuteLessThan_INT59 = new EventScriptQualifier("minuteLessThan_INT59", "");
EventScriptQualifier* EventData::hasMoneyAtLeastAmount_FLOAT = new EventScriptQualifier("hasMoneyAtLeastAmount_FLOAT", "");
EventScriptQualifier* EventData::hasMoneyLessThanAmount_FLOAT = new EventScriptQualifier("hasMoneyLessThanAmount_FLOAT", "");
EventScriptQualifier* EventData::hasItem_ITEM = new EventScriptQualifier("hasItem_ITEM", "");
EventScriptQualifier* EventData::hasGame_GAME = new EventScriptQualifier("hasGame_GAME", "");
EventScriptQualifier* EventData::isPlayerMale = new EventScriptQualifier("isPlayerMale", "");
EventScriptQualifier* EventData::isPlayerFemale = new EventScriptQualifier("isPlayerFemale", "");
EventScriptQualifier* EventData::isAnyEntityUsingSprite_SPRITE = new EventScriptQualifier("isAnyEntityUsingSprite_SPRITE", "");
EventScriptQualifier* EventData::isAnyEntityUsingSpriteAtArea_SPRITE_AREA = new EventScriptQualifier("isAnyEntityUsingSpriteAtArea_SPRITE_AREA", "");
EventScriptQualifier* EventData::isEntitySpawned_ENTITY = new EventScriptQualifier("isEntitySpawned_ENTITY", "");
EventScriptQualifier* EventData::isEntityAtArea_ENTITY_AREA = new EventScriptQualifier("isEntityAtArea_ENTITY_AREA", "");
EventScriptQualifier* EventData::isAreaEmpty_AREA = new EventScriptQualifier("isAreaEmpty_AREA", "");
EventScriptQualifier* EventData::hasFinishedDialogue_DIALOGUE = new EventScriptQualifier("hasFinishedDialogue_DIALOGUE", "");
EventScriptQualifier* EventData::isTextBoxOpen = new EventScriptQualifier("isTextBoxOpen", "");
EventScriptQualifier* EventData::isTextAnswerBoxOpen = new EventScriptQualifier("isTextAnswerBoxOpen", "");
EventScriptQualifier* EventData::isTextAnswerSelected_INT4 = new EventScriptQualifier("isTextAnswerSelected_INT4", "");
EventScriptQualifier* EventData::isTextAnswerSelected_STRING = new EventScriptQualifier("isTextAnswerSelected_STRING", "");
EventScriptQualifier* EventData::randomEqualsOneOutOfLessThan_INT = new EventScriptQualifier("randomEqualsOneOutOfLessThan_INT", "");
EventScriptQualifier* EventData::randomEqualsOneOutOfIncluding_INT = new EventScriptQualifier("randomEqualsOneOutOfIncluding_INT", "");
EventScriptQualifier* EventData::isAnyMusicPlaying = new EventScriptQualifier("isAnyMusicPlaying", "");
EventScriptQualifier* EventData::isMusicPlaying_MUSIC = new EventScriptQualifier("isMusicPlaying_MUSIC", "");
EventScriptQualifier* EventData::isRaining = new EventScriptQualifier("isRaining", "");
EventScriptQualifier* EventData::isWindy = new EventScriptQualifier("isWindy", "");
EventScriptQualifier* EventData::isSnowing = new EventScriptQualifier("isSnowing", "");
EventScriptQualifier* EventData::isFoggy = new EventScriptQualifier("isFoggy", "");
EventScriptQualifier* EventData::isMapOutside = new EventScriptQualifier("isMapOutside", "");
EventScriptQualifier* EventData::hasTalkedToThisToday = new EventScriptQualifier("hasTalkedToThisToday", "");
EventScriptQualifier* EventData::hasBeenMinutesSinceFlagSet_FLAG_INT = new EventScriptQualifier("hasBeenMinutesSinceFlagSet_FLAG_INT", "");
EventScriptQualifier* EventData::hasBeenHoursSinceFlagSet_FLAG_INT23 = new EventScriptQualifier("hasBeenHoursSinceFlagSet_FLAG_INT23", "");
EventScriptQualifier* EventData::hasBeenDaysSinceFlagSet_FLAG_INT = new EventScriptQualifier("hasBeenDaysSinceFlagSet_FLAG_INT", "");
EventScriptQualifier* EventData::isThisActivated = new EventScriptQualifier("isThisActivated", "");
EventScriptQualifier* EventData::haveSecondsPassedSinceActivated_INT = new EventScriptQualifier("haveSecondsPassedSinceActivated_INT", "");
EventScriptQualifier* EventData::haveMinutesPassedSinceActivated_INT = new EventScriptQualifier("haveMinutesPassedSinceActivated_INT", "");
EventScriptQualifier* EventData::haveHoursPassedSinceActivated_INT = new EventScriptQualifier("haveHoursPassedSinceActivated_INT", "");
EventScriptQualifier* EventData::haveDaysPassedSinceActivated_INT = new EventScriptQualifier("haveDaysPassedSinceActivated_INT", "");
EventScriptQualifier* EventData::hasActivatedThisEver = new EventScriptQualifier("hasActivatedThisEver", "");
EventScriptQualifier* EventData::hasActivatedThisSinceEnterRoom = new EventScriptQualifier("hasActivatedThisSinceEnterRoom", "");
EventScriptQualifier* EventData::hasBeenHereEver = new EventScriptQualifier("hasBeenHereEver", "");
EventScriptQualifier* EventData::hasBeenHereSinceEnterRoom = new EventScriptQualifier("hasBeenHereSinceEnterRoom", "");
EventScriptQualifier* EventData::haveSecondsPassedSinceBeenHere_INT = new EventScriptQualifier("haveSecondsPassedSinceBeenHere_INT", "");
EventScriptQualifier* EventData::haveMinutesPassedSinceBeenHere_INT = new EventScriptQualifier("haveMinutesPassedSinceBeenHere_INT", "");
EventScriptQualifier* EventData::haveHoursPassedSinceBeenHere_INT = new EventScriptQualifier("haveHoursPassedSinceBeenHere_INT", "");
EventScriptQualifier* EventData::haveDaysPassedSinceBeenHere_INT = new EventScriptQualifier("haveDaysPassedSinceBeenHere_INT", "");
EventScriptQualifier* EventData::isLightOn_LIGHT = new EventScriptQualifier("isLightOn_LIGHT", "");
EventScriptCommand* EventData::alwaysBlockWhileNotStandingHere = new EventScriptCommand("alwaysBlockWhileNotStandingHere", "");
EventScriptCommand* EventData::e00 = new EventScriptCommand();
EventScriptCommand* EventData::blockUntilActionButtonPressed = new EventScriptCommand("blockUntilActionButtonPressed", "");
EventScriptCommand* EventData::blockUntilActionCaptionButtonPressed_STRING = new EventScriptCommand("blockUntilActionCaptionButtonPressed_STRING", "");
EventScriptCommand* EventData::blockUntilCancelButtonPressed = new EventScriptCommand("blockUntilCancelButtonPressed", "");
EventScriptCommand* EventData::blockForTicks_INT = new EventScriptCommand("blockForTicks_INT", "");
EventScriptCommand* EventData::blockUntilClockHour_INT23 = new EventScriptCommand("blockUntilClockHour_INT23", "");
EventScriptCommand* EventData::blockUntilClockMinute_INT59 = new EventScriptCommand("blockUntilClockMinute_INT59", "");
EventScriptCommand* EventData::e000 = new EventScriptCommand();
EventScriptCommand* EventData::loadMapState_STATE = new EventScriptCommand("loadMapState_STATE", "");
EventScriptCommand* EventData::runEvent_EVENT = new EventScriptCommand("runEvent_EVENT", "");
EventScriptCommand* EventData::blockUntilEventDone_EVENT = new EventScriptCommand("blockUntilEventDone_EVENT", "");
EventScriptCommand* EventData::clearThisEvent = new EventScriptCommand("clearThisEvent", "");
EventScriptCommand* EventData::clearEvent_EVENT = new EventScriptCommand("clearEvent_EVENT", "");
EventScriptCommand* EventData::e001 = new EventScriptCommand();
EventScriptCommand* EventData::setThisActivated_BOOL = new EventScriptCommand("setThisActivated_BOOL", "");
EventScriptCommand* EventData::toggleThisActivated = new EventScriptCommand("toggleThisActivated", "");
EventScriptCommand* EventData::e002 = new EventScriptCommand();
EventScriptCommand* EventData::setLastBeenHereTime = new EventScriptCommand("setLastBeenHereTime", "");
EventScriptCommand* EventData::resetLastBeenHereTime = new EventScriptCommand("resetLastBeenHereTime", "");
EventScriptCommand* EventData::e003 = new EventScriptCommand();
EventScriptCommand* EventData::setFlag_FLAG_BOOL = new EventScriptCommand("setFlag_FLAG_BOOL", "");
EventScriptCommand* EventData::setFlagTrue_FLAG = new EventScriptCommand("setFlagTrue_FLAG", "");
EventScriptCommand* EventData::setFlagFalse_FLAG = new EventScriptCommand("setFlagFalse_FLAG", "");
EventScriptCommand* EventData::e004 = new EventScriptCommand();
EventScriptCommand* EventData::giveSkillPoints_SKILL_INT = new EventScriptCommand("giveSkillPoints_SKILL_INT", "");
EventScriptCommand* EventData::removeSkillPoints_SKILL_INT = new EventScriptCommand("removeSkillPoints_SKILL_INT", "");
EventScriptCommand* EventData::setSkillPoints_SKILL_INT = new EventScriptCommand("setSkillPoints_SKILL_INT", "");
EventScriptCommand* EventData::e005 = new EventScriptCommand();
EventScriptCommand* EventData::enterThisDoor = new EventScriptCommand("enterThisDoor", "");
EventScriptCommand* EventData::enterThisWarp = new EventScriptCommand("enterThisWarp", "");
EventScriptCommand* EventData::enterDoor_DOOR = new EventScriptCommand("enterDoor_DOOR", "");
EventScriptCommand* EventData::enterWarp_WARP = new EventScriptCommand("enterWarp_WARP", "");
EventScriptCommand* EventData::changeMap_MAP_AREA = new EventScriptCommand("changeMap_MAP_AREA", "");
EventScriptCommand* EventData::changeMap_MAP_DOOR = new EventScriptCommand("changeMap_MAP_DOOR", "");
EventScriptCommand* EventData::changeMap_MAP_WARP = new EventScriptCommand("changeMap_MAP_WARP", "");
EventScriptCommand* EventData::changeMap_MAP_INT_INT = new EventScriptCommand("changeMap_MAP_INT_INT", "");
EventScriptCommand* EventData::e006 = new EventScriptCommand();
EventScriptCommand* EventData::doDialogue_DIALOGUE = new EventScriptCommand("doDialogue_DIALOGUE", "");
EventScriptCommand* EventData::doDialogueWithCaption_DIALOGUE = new EventScriptCommand("doDialogueWithCaption_DIALOGUE", "");
EventScriptCommand* EventData::doDialogueIfNew_DIALOGUE = new EventScriptCommand("doDialogueIfNew_DIALOGUE", "");
EventScriptCommand* EventData::e007 = new EventScriptCommand();
EventScriptCommand* EventData::setSpriteBox0_ENTITY = new EventScriptCommand("setSpriteBox0_ENTITY", "");
EventScriptCommand* EventData::setSpriteBox1_ENTITY = new EventScriptCommand("setSpriteBox1_ENTITY", "");
EventScriptCommand* EventData::setSpriteBox0_SPRITE = new EventScriptCommand("setSpriteBox0_SPRITE", "");
EventScriptCommand* EventData::setSpriteBox1_SPRITE = new EventScriptCommand("setSpriteBox1_SPRITE", "");
EventScriptCommand* EventData::e008 = new EventScriptCommand();
EventScriptCommand* EventData::blockUntilTextBoxClosed = new EventScriptCommand("blockUntilTextBoxClosed", "");
EventScriptCommand* EventData::blockUntilTextAnswerBoxClosed = new EventScriptCommand("blockUntilTextAnswerBoxClosed", "");
EventScriptCommand* EventData::e009 = new EventScriptCommand();
EventScriptCommand* EventData::doCinematicTextNoBorder_DIALOGUE_INTy = new EventScriptCommand("doCinematicTextNoBorder_DIALOGUE_INTy", "");
EventScriptCommand* EventData::e025 = new EventScriptCommand();
EventScriptCommand* EventData::setDoorOpenAnimation_DOOR_BOOLopenClose = new EventScriptCommand("setDoorOpenAnimation_DOOR_BOOLopenClose", "");
EventScriptCommand* EventData::setDoorActionIcon_DOOR_BOOLonOff = new EventScriptCommand("setDoorActionIcon_DOOR_BOOLonOff", "");
EventScriptCommand* EventData::setDoorDestination_DOOR_DOORdestination = new EventScriptCommand("setDoorDestination_DOOR_DOORdestination", "");
EventScriptCommand* EventData::setAreaActionIcon_AREA_BOOLonOff = new EventScriptCommand("setAreaActionIcon_AREA_BOOLonOff", "");
EventScriptCommand* EventData::setWarpDestination_WARP_WARPdestination = new EventScriptCommand("setWarpDestination_WARP_WARPdestination", "");
EventScriptCommand* EventData::e010 = new EventScriptCommand();
EventScriptCommand* EventData::e012 = new EventScriptCommand();
EventScriptCommand* EventData::setCameraNoTarget = new EventScriptCommand("setCameraNoTarget", "");
EventScriptCommand* EventData::setCameraTargetToArea_AREA = new EventScriptCommand("setCameraTargetToArea_AREA", "");
EventScriptCommand* EventData::setCameraTargetToEntity_ENTITY = new EventScriptCommand("setCameraTargetToEntity_ENTITY", "");
EventScriptCommand* EventData::setCameraIgnoreBounds_BOOL = new EventScriptCommand("setCameraIgnoreBounds_BOOL", "");
EventScriptCommand* EventData::setCameraTargetToPlayer = new EventScriptCommand("setCameraTargetToPlayer", "");
EventScriptCommand* EventData::blockUntilCameraReaches_AREA = new EventScriptCommand("blockUntilCameraReaches_AREA", "");
EventScriptCommand* EventData::blockUntilCameraReaches_ENTITY = new EventScriptCommand("blockUntilCameraReaches_ENTITY", "");
EventScriptCommand* EventData::blockUntilCameraReachesPlayer = new EventScriptCommand("blockUntilCameraReachesPlayer", "");
EventScriptCommand* EventData::pushCameraState = new EventScriptCommand("pushCameraState", "");
EventScriptCommand* EventData::popCameraState = new EventScriptCommand("popCameraState", "");
EventScriptCommand* EventData::setKeyboardCameraZoom_BOOL = new EventScriptCommand("setKeyboardCameraZoom_BOOL", "");
EventScriptCommand* EventData::enableKeyboardCameraZoom = new EventScriptCommand("enableKeyboardCameraZoom", "");
EventScriptCommand* EventData::disableKeyboardCameraZoom = new EventScriptCommand("disableKeyboardCameraZoom", "");
EventScriptCommand* EventData::setCameraAutoZoomByPlayerMovement_BOOL = new EventScriptCommand("setCameraAutoZoomByPlayerMovement_BOOL", "");
EventScriptCommand* EventData::enableCameraAutoZoomByPlayerMovement = new EventScriptCommand("enableCameraAutoZoomByPlayerMovement", "");
EventScriptCommand* EventData::disableCameraAutoZoomByPlayerMovement = new EventScriptCommand("disableCameraAutoZoomByPlayerMovement", "");
EventScriptCommand* EventData::setCameraZoom_FLOAT = new EventScriptCommand("setCameraZoom_FLOAT", "");
EventScriptCommand* EventData::setCameraSpeed_FLOAT = new EventScriptCommand("setCameraSpeed_FLOAT", "");
EventScriptCommand* EventData::setPlayerToTempPlayerWithSprite_SPRITE = new EventScriptCommand("setPlayerToTempPlayerWithSprite_SPRITE", "");
EventScriptCommand* EventData::setPlayerToNormalPlayer = new EventScriptCommand("setPlayerToNormalPlayer", "");
EventScriptCommand* EventData::setPlayerExists_BOOL = new EventScriptCommand("setPlayerExists_BOOL", "");
EventScriptCommand* EventData::setPlayerControlsEnabled_BOOL = new EventScriptCommand("setPlayerControlsEnabled_BOOL", "");
EventScriptCommand* EventData::enablePlayerControls = new EventScriptCommand("enablePlayerControls", "");
EventScriptCommand* EventData::disablePlayerControls = new EventScriptCommand("disablePlayerControls", "");
EventScriptCommand* EventData::setPlayerAutoPilot_BOOL = new EventScriptCommand("setPlayerAutoPilot_BOOL", "");
EventScriptCommand* EventData::setPlayerShowNameCaption_BOOL = new EventScriptCommand("setPlayerShowNameCaption_BOOL", "");
EventScriptCommand* EventData::setPlayerShowAccountTypeCaption_BOOL = new EventScriptCommand("setPlayerShowAccountTypeCaption_BOOL", "");
EventScriptCommand* EventData::playerSetBehaviorQueueOnOff_BOOL = new EventScriptCommand("playerSetBehaviorQueueOnOff_BOOL", "");
EventScriptCommand* EventData::playerSetToArea_AREA = new EventScriptCommand("playerSetToArea_AREA", "");
EventScriptCommand* EventData::playerSetToDoor_DOOR = new EventScriptCommand("playerSetToDoor_DOOR", "");
EventScriptCommand* EventData::playerSetToTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("playerSetToTileXY_INTxTile1X_INTyTile1X", "");
EventScriptCommand* EventData::playerWalkToArea_AREA = new EventScriptCommand("playerWalkToArea_AREA", "");
EventScriptCommand* EventData::playerWalkToDoor_DOOR = new EventScriptCommand("playerWalkToDoor_DOOR", "");
EventScriptCommand* EventData::playerWalkToEntity_ENTITY = new EventScriptCommand("playerWalkToEntity_ENTITY", "");
EventScriptCommand* EventData::playerWalkToTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("playerWalkToTileXY_INTxTile1X_INTyTile1X", "");
EventScriptCommand* EventData::playerBlockUntilReachesArea_AREA = new EventScriptCommand("playerBlockUntilReachesArea_AREA", "");
EventScriptCommand* EventData::playerBlockUntilReachesDoor_DOOR = new EventScriptCommand("playerBlockUntilReachesDoor_DOOR", "");
EventScriptCommand* EventData::playerBlockUntilReachesEntity_ENTITY = new EventScriptCommand("playerBlockUntilReachesEntity_ENTITY", "");
EventScriptCommand* EventData::playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X", "");
EventScriptCommand* EventData::playerWalkToAreaAndBlockUntilThere_AREA = new EventScriptCommand("playerWalkToAreaAndBlockUntilThere_AREA", "");
EventScriptCommand* EventData::playerWalkToEntityAndBlockUntilThere_ENTITY = new EventScriptCommand("playerWalkToEntityAndBlockUntilThere_ENTITY", "");
EventScriptCommand* EventData::playerWalkToDoorAndBlockUntilThere_DOOR = new EventScriptCommand("playerWalkToDoorAndBlockUntilThere_DOOR", "");
EventScriptCommand* EventData::playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X = new EventScriptCommand("playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X", "");
EventScriptCommand* EventData::playerStandAndShuffle = new EventScriptCommand("playerStandAndShuffle", "");
EventScriptCommand* EventData::playerStandAndShuffleAndFaceEntity_ENTITY = new EventScriptCommand("playerStandAndShuffleAndFaceEntity_ENTITY", "");
EventScriptCommand* EventData::playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame = new EventScriptCommand("playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame", "");
EventScriptCommand* EventData::playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame = new EventScriptCommand("playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame", "");
EventScriptCommand* EventData::playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks", "");
EventScriptCommand* EventData::playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
EventScriptCommand* EventData::playerStopAnimating = new EventScriptCommand("playerStopAnimating", "");
EventScriptCommand* EventData::playerSetGlobalAnimationDisabled_BOOL = new EventScriptCommand("playerSetGlobalAnimationDisabled_BOOL", "");
EventScriptCommand* EventData::playerSetMovementSpeed_INTticksPerPixel = new EventScriptCommand("playerSetMovementSpeed_INTticksPerPixel", "");
EventScriptCommand* EventData::playerSetFaceMovementDirection_STRINGdirection = new EventScriptCommand("playerSetFaceMovementDirection_STRINGdirection", "");
EventScriptCommand* EventData::playerSetToAlpha_FLOAT = new EventScriptCommand("playerSetToAlpha_FLOAT", "");
EventScriptCommand* EventData::e024 = new EventScriptCommand();
EventScriptCommand* EventData::entitySetBehaviorQueueOnOff_ENTITY_BOOL = new EventScriptCommand("entitySetBehaviorQueueOnOff_ENTITY_BOOL", "");
EventScriptCommand* EventData::entitySetToArea_ENTITY_AREA = new EventScriptCommand("entitySetToArea_ENTITY_AREA", "");
EventScriptCommand* EventData::entitySetToDoor_ENTITY_DOOR = new EventScriptCommand("entitySetToDoor_ENTITY_DOOR", "");
EventScriptCommand* EventData::entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X = new EventScriptCommand("entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X", "");
EventScriptCommand* EventData::entityWalkToArea_ENTITY_AREA = new EventScriptCommand("entityWalkToArea_ENTITY_AREA", "");
EventScriptCommand* EventData::entityWalkToDoor_ENTITY_DOOR = new EventScriptCommand("entityWalkToDoor_ENTITY_DOOR", "");
EventScriptCommand* EventData::entityWalkToEntity_ENTITY_ENTITY = new EventScriptCommand("entityWalkToEntity_ENTITY_ENTITY", "");
EventScriptCommand* EventData::entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X = new EventScriptCommand("entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X", "");
EventScriptCommand* EventData::entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
EventScriptCommand* EventData::entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
EventScriptCommand* EventData::entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
EventScriptCommand* EventData::entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
EventScriptCommand* EventData::entityBlockUntilReachesArea_ENTITY_AREA = new EventScriptCommand("entityBlockUntilReachesArea_ENTITY_AREA", "");
EventScriptCommand* EventData::entityBlockUntilReachesDoor_ENTITY_DOOR = new EventScriptCommand("entityBlockUntilReachesDoor_ENTITY_DOOR", "");
EventScriptCommand* EventData::entityBlockUntilReachesEntity_ENTITY_ENTITY = new EventScriptCommand("entityBlockUntilReachesEntity_ENTITY_ENTITY", "");
EventScriptCommand* EventData::entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X = new EventScriptCommand("entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X", "");
EventScriptCommand* EventData::entityWalkToAreaAndBlockUntilThere_ENTITY_AREA = new EventScriptCommand("entityWalkToAreaAndBlockUntilThere_ENTITY_AREA", "");
EventScriptCommand* EventData::entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY = new EventScriptCommand("entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY", "");
EventScriptCommand* EventData::entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR = new EventScriptCommand("entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR", "");
EventScriptCommand* EventData::entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X = new EventScriptCommand("entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X", "");
EventScriptCommand* EventData::entityStandAndShuffle_ENTITY = new EventScriptCommand("entityStandAndShuffle_ENTITY", "");
EventScriptCommand* EventData::entityStandAndShuffleAndFacePlayer_ENTITY = new EventScriptCommand("entityStandAndShuffleAndFacePlayer_ENTITY", "");
EventScriptCommand* EventData::entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY = new EventScriptCommand("entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY", "");
EventScriptCommand* EventData::entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks", "");
EventScriptCommand* EventData::entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
EventScriptCommand* EventData::entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks", "");
EventScriptCommand* EventData::entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
EventScriptCommand* EventData::entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks", "");
EventScriptCommand* EventData::entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName = new EventScriptCommand("entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName", "");
EventScriptCommand* EventData::entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame = new EventScriptCommand("entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame", "");
EventScriptCommand* EventData::entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame = new EventScriptCommand("entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame", "");
EventScriptCommand* EventData::entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks", "");
EventScriptCommand* EventData::entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
EventScriptCommand* EventData::entityStopAnimating_ENTITY = new EventScriptCommand("entityStopAnimating_ENTITY", "");
EventScriptCommand* EventData::entitySetGlobalAnimationDisabled_ENTITY_BOOL = new EventScriptCommand("entitySetGlobalAnimationDisabled_ENTITY_BOOL", "");
EventScriptCommand* EventData::entitySetMovementSpeed_ENTITY_INTticksPerPixel = new EventScriptCommand("entitySetMovementSpeed_ENTITY_INTticksPerPixel", "");
EventScriptCommand* EventData::entitySetFaceMovementDirection_ENTITY_STRINGdirection = new EventScriptCommand("entitySetFaceMovementDirection_ENTITY_STRINGdirection", "");
EventScriptCommand* EventData::entitySetNonWalkable_ENTITY_BOOL = new EventScriptCommand("entitySetNonWalkable_ENTITY_BOOL", "");
EventScriptCommand* EventData::entitySetPushable_ENTITY_BOOL = new EventScriptCommand("entitySetPushable_ENTITY_BOOL", "");
EventScriptCommand* EventData::entitySetToAlpha_ENTITY_FLOAT = new EventScriptCommand("entitySetToAlpha_ENTITY_FLOAT", "");
EventScriptCommand* EventData::entityFadeOutDelete_ENTITY = new EventScriptCommand("entityFadeOutDelete_ENTITY", "");
EventScriptCommand* EventData::entityDeleteInstantly_ENTITY = new EventScriptCommand("entityDeleteInstantly_ENTITY", "");
EventScriptCommand* EventData::e016 = new EventScriptCommand();
EventScriptCommand* EventData::spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA = new EventScriptCommand("spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA", "");
EventScriptCommand* EventData::spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA = new EventScriptCommand("spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA", "");
EventScriptCommand* EventData::spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA = new EventScriptCommand("spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA", "");
EventScriptCommand* EventData::spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA = new EventScriptCommand("spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA", "");
EventScriptCommand* EventData::e017 = new EventScriptCommand();
EventScriptCommand* EventData::createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy = new EventScriptCommand("createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy", "");
EventScriptCommand* EventData::createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy = new EventScriptCommand("createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy", "");
EventScriptCommand* EventData::createScreenSpriteUnderText_SPRITE_INTx_INTy = new EventScriptCommand("createScreenSpriteUnderText_SPRITE_INTx_INTy", "");
EventScriptCommand* EventData::createScreenSpriteOverText_SPRITE_INTx_INTy = new EventScriptCommand("createScreenSpriteOverText_SPRITE_INTx_INTy", "");
EventScriptCommand* EventData::e026 = new EventScriptCommand();
EventScriptCommand* EventData::giveItem_ITEM = new EventScriptCommand("giveItem_ITEM", "");
EventScriptCommand* EventData::takeItem_ITEM = new EventScriptCommand("takeItem_ITEM", "");
EventScriptCommand* EventData::giveGame_GAME = new EventScriptCommand("giveGame_GAME", "");
EventScriptCommand* EventData::takeMoney_FLOAT = new EventScriptCommand("takeMoney_FLOAT", "");
EventScriptCommand* EventData::giveMoney_FLOAT = new EventScriptCommand("giveMoney_FLOAT", "");
EventScriptCommand* EventData::e027 = new EventScriptCommand();
EventScriptCommand* EventData::playSound_SOUND = new EventScriptCommand("playSound_SOUND", "");
EventScriptCommand* EventData::playSound_SOUND_FLOATvol = new EventScriptCommand("playSound_SOUND_FLOATvol", "");
EventScriptCommand* EventData::playSound_SOUND_FLOATvol_FLOATpitch_INTtimes = new EventScriptCommand("playSound_SOUND_FLOATvol_FLOATpitch_INTtimes", "");
EventScriptCommand* EventData::playMusicOnce_MUSIC = new EventScriptCommand("playMusicOnce_MUSIC", "");
EventScriptCommand* EventData::playMusicLoop_MUSIC = new EventScriptCommand("playMusicLoop_MUSIC", "");
EventScriptCommand* EventData::playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop = new EventScriptCommand("playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop", "");
EventScriptCommand* EventData::stopAllMusic = new EventScriptCommand("stopAllMusic", "");
EventScriptCommand* EventData::stopMusic_MUSIC = new EventScriptCommand("stopMusic_MUSIC", "");
EventScriptCommand* EventData::fadeOutMusic_MUSIC_INT = new EventScriptCommand("fadeOutMusic_MUSIC_INT", "");
EventScriptCommand* EventData::blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC = new EventScriptCommand("blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC", "");
EventScriptCommand* EventData::blockUntilMusicDone_MUSIC = new EventScriptCommand("blockUntilMusicDone_MUSIC", "");
EventScriptCommand* EventData::fadeOutAllMusic_INT = new EventScriptCommand("fadeOutAllMusic_INT", "");
EventScriptCommand* EventData::blockUntilAllMusicDone = new EventScriptCommand("blockUntilAllMusicDone", "");
EventScriptCommand* EventData::e028 = new EventScriptCommand();
EventScriptCommand* EventData::shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake = new EventScriptCommand("shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake", "");
EventScriptCommand* EventData::fadeToBlack_INTticks = new EventScriptCommand("fadeToBlack_INTticks", "");
EventScriptCommand* EventData::fadeFromBlack_INTticks = new EventScriptCommand("fadeFromBlack_INTticks", "");
EventScriptCommand* EventData::fadeToWhite_INTticks = new EventScriptCommand("fadeToWhite_INTticks", "");
EventScriptCommand* EventData::fadeFromWhite_INTticks = new EventScriptCommand("fadeFromWhite_INTticks", "");
EventScriptCommand* EventData::e029 = new EventScriptCommand();
EventScriptCommand* EventData::fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha = new EventScriptCommand("fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
EventScriptCommand* EventData::fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha = new EventScriptCommand("fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha", "");
EventScriptCommand* EventData::fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha = new EventScriptCommand("fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
EventScriptCommand* EventData::setInstantOverlay_INTr_INTg_INTb_FLOATa = new EventScriptCommand("setInstantOverlay_INTr_INTg_INTb_FLOATa", "");
EventScriptCommand* EventData::clearOverlay = new EventScriptCommand("clearOverlay", "");
EventScriptCommand* EventData::fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha = new EventScriptCommand("fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
EventScriptCommand* EventData::setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa = new EventScriptCommand("setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa", "");
EventScriptCommand* EventData::clearOverlayUnderLights = new EventScriptCommand("clearOverlayUnderLights", "");
EventScriptCommand* EventData::fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha = new EventScriptCommand("fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
EventScriptCommand* EventData::setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa = new EventScriptCommand("setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa", "");
EventScriptCommand* EventData::clearOverlayGroundLayer = new EventScriptCommand("clearOverlayGroundLayer", "");
EventScriptCommand* EventData::e030 = new EventScriptCommand();
EventScriptCommand* EventData::setLetterbox_BOOL = new EventScriptCommand("setLetterbox_BOOL", "");
EventScriptCommand* EventData::setLetterbox_BOOL_INTticks = new EventScriptCommand("setLetterbox_BOOL_INTticks", "");
EventScriptCommand* EventData::setLetterbox_BOOL_INTticks_INTsize = new EventScriptCommand("setLetterbox_BOOL_INTticks_INTsize", "");
EventScriptCommand* EventData::setLetterbox_BOOL_INTticks_FLOATsize = new EventScriptCommand("setLetterbox_BOOL_INTticks_FLOATsize", "");
EventScriptCommand* EventData::setBlur_BOOL = new EventScriptCommand("setBlur_BOOL", "");
EventScriptCommand* EventData::setMosaic_BOOL = new EventScriptCommand("setMosaic_BOOL", "");
EventScriptCommand* EventData::setHBlankWave_BOOL = new EventScriptCommand("setHBlankWave_BOOL", "");
EventScriptCommand* EventData::setRotate_BOOL = new EventScriptCommand("setRotate_BOOL", "");
EventScriptCommand* EventData::setBlackAndWhite_BOOL = new EventScriptCommand("setBlackAndWhite_BOOL", "");
EventScriptCommand* EventData::setInvertedColors_BOOL = new EventScriptCommand("setInvertedColors_BOOL", "");
EventScriptCommand* EventData::set8BitMode_BOOL = new EventScriptCommand("set8BitMode_BOOL", "");
EventScriptCommand* EventData::e031 = new EventScriptCommand();
EventScriptCommand* EventData::setEngineSpeed_FLOAT = new EventScriptCommand("setEngineSpeed_FLOAT", "");
EventScriptCommand* EventData::e032 = new EventScriptCommand();
EventScriptCommand* EventData::toggleLightOnOff_LIGHT = new EventScriptCommand("toggleLightOnOff_LIGHT", "");
EventScriptCommand* EventData::setLightOnOff_LIGHT_BOOL = new EventScriptCommand("setLightOnOff_LIGHT_BOOL", "");
EventScriptCommand* EventData::setLightFlicker_LIGHT_BOOL = new EventScriptCommand("setLightFlicker_LIGHT_BOOL", "");
EventScriptCommand* EventData::toggleAllLightsOnOff = new EventScriptCommand("toggleAllLightsOnOff", "");
EventScriptCommand* EventData::setAllLightsOnOff_BOOL = new EventScriptCommand("setAllLightsOnOff_BOOL", "");
EventScriptCommand* EventData::e033 = new EventScriptCommand();
EventScriptCommand* EventData::setRandomSpawn_BOOL = new EventScriptCommand("setRandomSpawn_BOOL", "");
EventScriptCommand* EventData::deleteRandoms = new EventScriptCommand("deleteRandoms", "");
EventScriptCommand* EventData::e034 = new EventScriptCommand();
EventScriptCommand* EventData::makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb = new EventScriptCommand("makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb", "");
EventScriptCommand* EventData::makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb = new EventScriptCommand("makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb", "");
EventScriptCommand* EventData::makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb = new EventScriptCommand("makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb", "");
EventScriptCommand* EventData::makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb = new EventScriptCommand("makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb", "");
EventScriptCommand* EventData::setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks = new EventScriptCommand("setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks", "");
EventScriptCommand* EventData::e035 = new EventScriptCommand();
EventScriptCommand* EventData::setShowClockCaption_BOOL = new EventScriptCommand("setShowClockCaption_BOOL", "");
EventScriptCommand* EventData::setShowDayCaption_BOOL = new EventScriptCommand("setShowDayCaption_BOOL", "");
EventScriptCommand* EventData::setShowMoneyCaption_BOOL = new EventScriptCommand("setShowMoneyCaption_BOOL", "");
EventScriptCommand* EventData::setShowAllStatusBarCaptions_BOOL = new EventScriptCommand("setShowAllStatusBarCaptions_BOOL", "");
EventScriptCommand* EventData::setShowStatusBar_BOOL = new EventScriptCommand("setShowStatusBar_BOOL", "");
EventScriptCommand* EventData::setShowNDButton_BOOL = new EventScriptCommand("setShowNDButton_BOOL", "");
EventScriptCommand* EventData::setShowGameStoreButton_BOOL = new EventScriptCommand("setShowGameStoreButton_BOOL", "");
EventScriptCommand* EventData::setShowStuffButton_BOOL = new EventScriptCommand("setShowStuffButton_BOOL", "");
EventScriptCommand* EventData::setShowAllButtons_BOOL = new EventScriptCommand("setShowAllButtons_BOOL", "");
EventScriptCommand* EventData::setNDEnabled_BOOL = new EventScriptCommand("setNDEnabled_BOOL", "");
EventScriptCommand* EventData::setGameStoreMenuEnabled_BOOL = new EventScriptCommand("setGameStoreMenuEnabled_BOOL", "");
EventScriptCommand* EventData::setStuffMenuEnabled_BOOL = new EventScriptCommand("setStuffMenuEnabled_BOOL", "");
EventScriptCommand* EventData::setAllMenusAndNDEnabled_BOOL = new EventScriptCommand("setAllMenusAndNDEnabled_BOOL", "");
EventScriptCommand* EventData::e046 = new EventScriptCommand();
EventScriptCommand* EventData::setClockUnknown = new EventScriptCommand("setClockUnknown", "");
EventScriptCommand* EventData::setClockNormal = new EventScriptCommand("setClockNormal", "");
EventScriptCommand* EventData::setTimePaused_BOOL = new EventScriptCommand("setTimePaused_BOOL", "");
EventScriptCommand* EventData::setTimeFastForward = new EventScriptCommand("setTimeFastForward", "");
EventScriptCommand* EventData::setTimeNormalSpeed = new EventScriptCommand("setTimeNormalSpeed", "");
EventScriptCommand* EventData::e037 = new EventScriptCommand();
EventScriptCommand* EventData::setNDOpen_BOOL = new EventScriptCommand("setNDOpen_BOOL", "");
EventScriptCommand* EventData::startGame = new EventScriptCommand("startGame", "");
EventScriptCommand* EventData::startBobsGameOnStadiumScreen_AREA = new EventScriptCommand("startBobsGameOnStadiumScreen_AREA", "");
EventScriptCommand* EventData::blockUntilBobsGameDead = new EventScriptCommand("blockUntilBobsGameDead", "");
EventScriptCommand* EventData::showLoginScreen = new EventScriptCommand("showLoginScreen", "");
EventScriptCommand* EventData::e038 = new EventScriptCommand();
EventScriptCommand* EventData::closeAllMenusAndND = new EventScriptCommand("closeAllMenusAndND", "");
EventScriptCommand* EventData::e039 = new EventScriptCommand();
EventScriptCommand* EventData::openStuffMenu = new EventScriptCommand("openStuffMenu", "");
EventScriptCommand* EventData::openItemsMenu = new EventScriptCommand("openItemsMenu", "");
EventScriptCommand* EventData::openLogMenu = new EventScriptCommand("openLogMenu", "");
EventScriptCommand* EventData::openStatusMenu = new EventScriptCommand("openStatusMenu", "");
EventScriptCommand* EventData::openFriendsMenu = new EventScriptCommand("openFriendsMenu", "");
EventScriptCommand* EventData::openSettingsMenu = new EventScriptCommand("openSettingsMenu", "");
EventScriptCommand* EventData::openGameStoreMenu = new EventScriptCommand("openGameStoreMenu", "");

