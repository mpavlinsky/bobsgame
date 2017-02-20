#include "stdafx.h"
#include <algorithm>

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Event::log = Logger("Event");


Event::Event(Engine* g, int id)
{ //=========================================================================================================================

	this->e = g;

	this->data = new EventData(id, "", 0, "", "");

	for (int i = 0; i < (int)getEventManager()->eventList.size(); i++)
	{
		if (getEventManager()->eventList.get(i)->getID() == data->getID())
		{
			log.error(string("Event already exists:") + data->getName());
			return;
		}
	}
	getEventManager()->eventList.add(this); //this tracks events created for areas and entities that don't exist after the map is unloaded, so they don't have to be loaded from the server and parsed again.
}

Event::Event(Engine* g, EventData* eventData)
{ //=========================================================================================================================

	this->e = g;

	this->data = eventData;
	setInitialized_S(true);

	for (int i = 0; i < (int)getEventManager()->eventList.size(); i++)
	{
		if (getEventManager()->eventList.get(i)->getID() == data->getID())
		{
			log.error(string("Event already exists:") + data->getName());
			return;
		}
	}
	getEventManager()->eventList.add(this); //this tracks events created for areas and entities that don't exist after the map is unloaded, so they don't have to be loaded from the server and parsed again.
}

EventData* Event::getData()
{
	return data;
}

int Event::getID()
{
	return data->getID();
}

string Event::getName()
{
	return data->getName();
}

int Event::type()
{
	return data->getType();
}

string Event::getComment()
{
	return data->getComment();
}

string Event::text()
{
	return data->getText();
}

string Event::getTYPEIDString()
{
	return data->getTYPEIDString();
}

void Event::setID(int id)
{
	data->setID(id);
}

void Event::setName(const string& name)
{
	data->setName(name);
}

void Event::setType(int type)
{
	data->setType(type);
}

void Event::setComment(const string& comment)
{
	data->setComment(comment);
}

void Event::setText(const string& text)
{
	data->setText(text);
}

//The following method was originally marked 'synchronized':
void Event::setData_S(EventData* eventData)
{ //=========================================================================================================================
	this->data = eventData;
	setInitialized_S(true);
}

Map* Event::getMap()
{ //=========================================================================================================================

	if (type() == EventData::TYPE_PROJECT_INITIAL_LOADER || type() == EventData::TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED)
	{
		return ServerObject::getCurrentMap();
	}

	if (map != nullptr)
	{
		return map; //DONE: any event changeMap events will have to set the map.
	}
	if (door != nullptr)
	{
		return door->getMap();
	}
	if (area != nullptr)
	{
		return area->getMap();
	}
	if (entity != nullptr)
	{
		return entity->getMap();
	}

	if (getPlayer() != nullptr)
	{
		return getPlayer()->getMap();
	}

	return getCurrentMap();
}

Map* Event::getCurrentMap()
{ //=========================================================================================================================
	log.warn("Don't use getCurrentMap() in Events!");
	return ServerObject::getCurrentMap();
}

bool Event::getWasAddedToQueue()
{ //=========================================================================================================================
	return addedToQueue;
}

void Event::setAddedToQueue()
{ //=========================================================================================================================
	addedToQueue = true;
	timeAddedToQueue = System::currentHighResTimer();
}

void Event::reset()
{ //=========================================================================================================================

	//reset to the first command
	delete commandTree; //we're going to have to reparse it each time because the MapObjects aren't persistent and the parameters point to them.
	commandTree = nullptr;

	delete currentCommand;
	currentCommand = nullptr;

	addedToQueue = false;
	blockWhileNotHere = false;
}

void Event::parseEventString(string s)
{ //===============================================================================================


	commandTree = new EventCommand(getEngine(), "none", nullptr, 0);

	EventCommand* currentParent = commandTree;


	s = s.substr(1, s.length() - 1 - 1); //split off { }, string now looks like "command,command,if(qualifier == TRUE){command,command}"

	//fadeFromBlack(INT.10000),
	//if(isFlagSet(FLAG.0) == TRUE){},if(isFlagSet(FLAG.0) == FALSE){setPlayerToTempPlayerWithSprite(SPRITE.938)}


	while (s.length() > 0)
	{
		//log.info("Parsing Event String: "+s);

		if (String::startsWith(s, "}"))
		{
			if (String::startsWith(s, "},"))
			{
				s = s.substr(2);
			}
			else if (String::startsWith(s, "}"))
			{
				s = s.substr(1);
			}

			currentParent = static_cast<EventCommand*>(currentParent->getParent());
		}
		else
		{
			if (String::startsWith(s, "if("))
			{
				//handle qualifier

				s = s.substr(3); //split off if(, string looks like "qualifier == TRUE){command,command}"

				string qualifier = s.substr(0, s.find("{") - 1); //get "qualifier == TRUE"
				s = s.substr(s.find("{") + 1); //string now looks like "command,command}"

				EventCommand* e = EventCommand::parseEventCommandFromCommandString(getEngine(), this, qualifier);


				currentParent->addChild(e);


				currentParent = e;
			}
			else
			{
				if (s.find(",") != -1) //there is another instruction
				{
					if (s.find("}") != -1 && s.find("}") < s.find(",")) //looks like "command()},command()
					{
						string command = s.substr(0, s.find("}")); //get command
						s = s.substr(s.find("}")); //split off command and comma

						EventCommand* e = EventCommand::parseEventCommandFromCommandString(getEngine(), this, command);

						currentParent->addChild(e);
					}
					else
					{
						if (s.find("),") != -1 && s.find("),") < s.find("}")) //looks like "command(),command()}"
						{
							string command = s.substr(0, s.find("),") + 1); //get command
							s = s.substr(s.find("),") + 2); //split off command and comma

							EventCommand* e = EventCommand::parseEventCommandFromCommandString(getEngine(), this, command);

							currentParent->addChild(e);
						}
						else //looks like "command,command}"
						{
							string command = s.substr(0, s.find(",")); //get command
							s = s.substr(s.find(",") + 1); //split off command and comma

							EventCommand* e = EventCommand::parseEventCommandFromCommandString(getEngine(), this, command);

							currentParent->addChild(e);
						}
					}
				}
				else
				{
					if (s.find("}") != -1) //looks like "command}" or "command}if(thing){}" or "command}}}"
					{
						string command = s.substr(0, s.find("}")); //get command
						s = s.substr(s.find("}")); //split off command and comma

						EventCommand* e = EventCommand::parseEventCommandFromCommandString(getEngine(), this, command);

						currentParent->addChild(e);
					}
					else //looks like "command"
					{
						string command = s;

						s = s.substr(command.length());

						EventCommand* e = EventCommand::parseEventCommandFromCommandString(getEngine(), this, command);

						currentParent->addChild(e);
					}
				}
			}
		}
	}
}

void Event::run()
{ //=========================================================================================================================

	if (getLoadedFromServerSendRequestIfFalse())
	{
		if (blockWhileNotHere == true)
		{
			if (area != nullptr)
			{
				if (getPlayer()->isAreaBoundaryTouchingMyHitBox(area) == false && getPlayer()->isWalkingIntoArea(area) == false)
				{
					return;
				}
			}

			if (door != nullptr)
			{
				if (getPlayer()->isWalkingIntoEntity(door) == false)
				{
					return;
				}
			}

			if (entity != nullptr)
			{
				if (getPlayer()->isEntityHitBoxTouchingMyHitBox(entity) == false && getPlayer()->isWalkingIntoEntity(entity) == false)
				{
					return;
				}
			}
		}

		if (commandTree == nullptr)
		{
			parseEventString(text());
			currentCommand = commandTree->getNextChild(); //the actual commandTree command is blank. get the first child.
		}

		if (commandTree != nullptr)
		{
			//this is already done automatically when the parameter objects are parsed, simply by requesting the ID we create the object which updates itself from the server in its update() function.

			//go through all commands, all parameters, load all dialogues, gamestrings from server.
			//if this event requires a button press, put an action icon.
			//do i really need to do this? it is actually better to load the dialogues on-demand, so people can't hack the memory and see dialogue they can't access...
		}


		if (currentCommand != nullptr)
		{
			doCommand();
		}


		if (commandTree != nullptr) //set to null if the command changes the map, which clears the event queue and resets this event: but it's still running!
		{
			if (currentCommand == nullptr)
			{
				//remove this from EventManager.eventQueue when finished
				if (type() == EventData::TYPE_MAP_RUN_ONCE_BEFORE_LOAD || type() == EventData::TYPE_MAP_RUN_ONCE_AFTER_LOAD || type() == EventData::TYPE_PROJECT_INITIAL_LOADER)
				{
					reset();
					getEventManager()->runningEventQueue.remove(this);
				}
				else
				{
					//reset to the first command
					commandTree->currentChildIndex = 0;
					currentCommand = commandTree->getNextChild(); //the actual commandTree command is blank. get the first child.
				}
			}
		}
	}
}

void Event::getNextCommandInParent()
{ //=========================================================================================================================

	if (currentCommand != nullptr)
	{
		if (currentCommand->getParent() == nullptr) //this was the last command
		{
			delete currentCommand;
			currentCommand = nullptr;
		}
		else
		{
			currentCommand = currentCommand->getParent()->getNextChild();
			doCommand();
		}
	}
	else
	{
		//we must have changed the map and reset this event.
	}
}

void Event::getNextCommand()
{ //=========================================================================================================================

	if (currentCommand != nullptr)
	{
		//increment command into currentCommand's children
		if (currentCommand->children->size() > 0)
		{
			currentCommand = currentCommand->getNextChild();
			doCommand();
		}
		else
		{
			getNextCommandInParent();
		}
	}
	else
	{
		//we must have changed the map and reset this event.
	}
}

void Event::getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(bool b)
{ //===============================================================================================

	if ((currentCommand->type == EventCommand::TYPE_QUALIFIER_TRUE && b == true) || (currentCommand->type == EventCommand::TYPE_QUALIFIER_FALSE && b == false))
	{
		//increment command into currentCommand's children
		getNextCommand();
	}
	else
	{
		//skip to the next command in currentCommand's parent, skipping over this block
		getNextCommandInParent();
	}
}

void Event::doCommand()
{ //=========================================================================================================================

	//log.debug("Current Command: "+currentCommand.commandString);


	if (currentCommand == nullptr)
	{
		return;
	}

	//qualifiers. check if TRUE or FALSE. skip children if false.

	if (currentCommand->parameterList->size() > 0)
	{
		for (int i = 0; i < (int)currentCommand->parameterList->size(); i++)
		{
			EventParameter* e = currentCommand->parameterList->get(i);
			e->updateParameterVariablesFromString(this);
		}
	}


	if (currentCommand->commandString == EventData::isPlayerTouchingThisArea->getCommand())
	{
		isPlayerTouchingThisArea();
		return;
	}
	if (currentCommand->commandString == EventData::isPlayerWalkingIntoThisDoor->getCommand())
	{
		isPlayerWalkingIntoThisDoor();
		return;
	}
	if (currentCommand->commandString == EventData::isPlayerTouchingThisEntity->getCommand())
	{
		isPlayerTouchingThisEntity();
		return;
	}
	if (currentCommand->commandString == EventData::isPlayerTouchingAnyEntityUsingThisSprite->getCommand())
	{
		isPlayerTouchingAnyEntityUsingThisSprite();
		return;
	}
	if (currentCommand->commandString == EventData::isPlayerWalkingIntoDoor_DOOR->getCommand())
	{
		isPlayerWalkingIntoDoor_DOOR();
		return;
	}
	if (currentCommand->commandString == EventData::isPlayerWalkingIntoWarp_WARP->getCommand())
	{
		isPlayerWalkingIntoWarp_WARP();
		return;
	}
	if (currentCommand->commandString == EventData::isActionButtonHeld->getCommand())
	{
		isActionButtonHeld();
		return;
	}
	if (currentCommand->commandString == EventData::isPlayerAutoPilotOn->getCommand())
	{
		isPlayerAutoPilotOn();
		return;
	}
	if (currentCommand->commandString == EventData::isFlagSet_FLAG->getCommand())
	{
		isFlagSet_FLAG();
		return;
	}
	if (currentCommand->commandString == EventData::hasSkillAtLeast_SKILL_FLOAT1->getCommand())
	{
		hasSkillAtLeast_SKILL_FLOAT1();
		return;
	}
	if (currentCommand->commandString == EventData::isCurrentState_STATE->getCommand())
	{
		isCurrentState_STATE();
		return;
	}
	if (currentCommand->commandString == EventData::isPlayerStandingInArea_AREA->getCommand())
	{
		isPlayerStandingInArea_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::isEntityStandingInArea_ENTITY_AREA->getCommand())
	{
		isEntityStandingInArea_ENTITY_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::hourPastOrEqualTo_INT23->getCommand())
	{
		hourPastOrEqualTo_INT23();
		return;
	}
	if (currentCommand->commandString == EventData::hourLessThan_INT23->getCommand())
	{
		hourLessThan_INT23();
		return;
	}
	if (currentCommand->commandString == EventData::minutePastOrEqualTo_INT59->getCommand())
	{
		minutePastOrEqualTo_INT59();
		return;
	}
	if (currentCommand->commandString == EventData::minuteLessThan_INT59->getCommand())
	{
		minuteLessThan_INT59();
		return;
	}
	if (currentCommand->commandString == EventData::hasMoneyAtLeastAmount_FLOAT->getCommand())
	{
		hasMoneyAtLeastAmount_FLOAT();
		return;
	}
	if (currentCommand->commandString == EventData::hasMoneyLessThanAmount_FLOAT->getCommand())
	{
		hasMoneyLessThanAmount_FLOAT();
		return;
	}
	if (currentCommand->commandString == EventData::hasItem_ITEM->getCommand())
	{
		hasItem_ITEM();
		return;
	}
	if (currentCommand->commandString == EventData::hasGame_GAME->getCommand())
	{
		hasGame_GAME();
		return;
	}
	if (currentCommand->commandString == EventData::isPlayerMale->getCommand())
	{
		isPlayerMale();
		return;
	}
	if (currentCommand->commandString == EventData::isPlayerFemale->getCommand())
	{
		isPlayerFemale();
		return;
	}
	if (currentCommand->commandString == EventData::isAnyEntityUsingSprite_SPRITE->getCommand())
	{
		isAnyEntityUsingSprite_SPRITE();
		return;
	}
	if (currentCommand->commandString == EventData::isAnyEntityUsingSpriteAtArea_SPRITE_AREA->getCommand())
	{
		isAnyEntityUsingSpriteAtArea_SPRITE_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::isEntitySpawned_ENTITY->getCommand())
	{
		isEntitySpawned_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::isEntityAtArea_ENTITY_AREA->getCommand())
	{
		isEntityAtArea_ENTITY_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::isAreaEmpty_AREA->getCommand())
	{
		isAreaEmpty_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::hasFinishedDialogue_DIALOGUE->getCommand())
	{
		hasFinishedDialogue_DIALOGUE();
		return;
	}
	if (currentCommand->commandString == EventData::isTextBoxOpen->getCommand())
	{
		isTextBoxOpen();
		return;
	}
	if (currentCommand->commandString == EventData::isTextAnswerBoxOpen->getCommand())
	{
		isTextAnswerBoxOpen();
		return;
	}
	if (currentCommand->commandString == EventData::isTextAnswerSelected_INT4->getCommand())
	{
		isTextAnswerSelected_INT4();
		return;
	}
	if (currentCommand->commandString == EventData::isTextAnswerSelected_STRING->getCommand())
	{
		isTextAnswerSelected_STRING();
		return;
	}
	if (currentCommand->commandString == EventData::randomEqualsOneOutOfLessThan_INT->getCommand())
	{
		randomEqualsOneOutOfLessThan_INT();
		return;
	}
	if (currentCommand->commandString == EventData::randomEqualsOneOutOfIncluding_INT->getCommand())
	{
		randomEqualsOneOutOfIncluding_INT();
		return;
	}
	if (currentCommand->commandString == EventData::isAnyMusicPlaying->getCommand())
	{
		isAnyMusicPlaying();
		return;
	}
	if (currentCommand->commandString == EventData::isMusicPlaying_MUSIC->getCommand())
	{
		isMusicPlaying();
		return;
	}
	if (currentCommand->commandString == EventData::isRaining->getCommand())
	{
		isRaining();
		return;
	}
	if (currentCommand->commandString == EventData::isWindy->getCommand())
	{
		isWindy();
		return;
	}
	if (currentCommand->commandString == EventData::isSnowing->getCommand())
	{
		isSnowing();
		return;
	}
	if (currentCommand->commandString == EventData::isFoggy->getCommand())
	{
		isFoggy();
		return;
	}
	//		 if(currentCommand.commandString.equals(EventData.isPlayerHolding.getCommand())){isPlayerHolding();return; }
	//		 if(currentCommand.commandString.equals(EventData.isPlayerWearing.getCommand())){isPlayerWearing();return; }
	if (currentCommand->commandString == EventData::isMapOutside->getCommand())
	{
		isMapOutside();
		return;
	}
	if (currentCommand->commandString == EventData::hasTalkedToThisToday->getCommand())
	{
		hasTalkedToThisToday();
		return;
	}
	if (currentCommand->commandString == EventData::hasBeenMinutesSinceFlagSet_FLAG_INT->getCommand())
	{
		hasBeenMinutesSinceFlagSet_FLAG_INT();
		return;
	}
	if (currentCommand->commandString == EventData::hasBeenHoursSinceFlagSet_FLAG_INT23->getCommand())
	{
		hasBeenHoursSinceFlagSet_FLAG_INT23();
		return;
	}
	if (currentCommand->commandString == EventData::hasBeenDaysSinceFlagSet_FLAG_INT->getCommand())
	{
		hasBeenDaysSinceFlagSet_FLAG_INT();
		return;
	}
	if (currentCommand->commandString == EventData::isThisActivated->getCommand())
	{
		isThisActivated();
		return;
	}
	if (currentCommand->commandString == EventData::haveSecondsPassedSinceActivated_INT->getCommand())
	{
		haveSecondsPassedSinceActivated_INT();
		return;
	}
	if (currentCommand->commandString == EventData::haveMinutesPassedSinceActivated_INT->getCommand())
	{
		haveMinutesPassedSinceActivated_INT();
		return;
	}
	if (currentCommand->commandString == EventData::haveHoursPassedSinceActivated_INT->getCommand())
	{
		haveHoursPassedSinceActivated_INT();
		return;
	}
	if (currentCommand->commandString == EventData::haveDaysPassedSinceActivated_INT->getCommand())
	{
		haveDaysPassedSinceActivated_INT();
		return;
	}
	if (currentCommand->commandString == EventData::hasActivatedThisEver->getCommand())
	{
		hasActivatedThisEver();
		return;
	}
	if (currentCommand->commandString == EventData::hasActivatedThisSinceEnterRoom->getCommand())
	{
		hasActivatedThisSinceEnterRoom();
		return;
	}
	if (currentCommand->commandString == EventData::hasBeenHereEver->getCommand())
	{
		hasBeenHereEver();
		return;
	}
	if (currentCommand->commandString == EventData::hasBeenHereSinceEnterRoom->getCommand())
	{
		hasBeenHereSinceEnterRoom();
		return;
	}
	if (currentCommand->commandString == EventData::haveSecondsPassedSinceBeenHere_INT->getCommand())
	{
		haveSecondsPassedSinceBeenHere_INT();
		return;
	}
	if (currentCommand->commandString == EventData::haveMinutesPassedSinceBeenHere_INT->getCommand())
	{
		haveMinutesPassedSinceBeenHere_INT();
		return;
	}
	if (currentCommand->commandString == EventData::haveHoursPassedSinceBeenHere_INT->getCommand())
	{
		haveHoursPassedSinceBeenHere_INT();
		return;
	}
	if (currentCommand->commandString == EventData::haveDaysPassedSinceBeenHere_INT->getCommand())
	{
		haveDaysPassedSinceBeenHere_INT();
		return;
	}
	if (currentCommand->commandString == EventData::isLightOn_LIGHT->getCommand())
	{
		isLightOn_LIGHT();
		return;
	}


	//commands
	if (currentCommand->commandString == EventData::alwaysBlockWhileNotStandingHere->getCommand())
	{
		alwaysBlockWhileNotStandingHere();
		return;
	}

	if (currentCommand->commandString == EventData::blockUntilActionButtonPressed->getCommand())
	{
		blockUntilActionButtonPressed();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilActionCaptionButtonPressed_STRING->getCommand())
	{
		blockUntilActionCaptionButtonPressed_STRING();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilCancelButtonPressed->getCommand())
	{
		blockUntilCancelButtonPressed();
		return;
	}
	if (currentCommand->commandString == EventData::blockForTicks_INT->getCommand())
	{
		blockForTicks_INT();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilClockHour_INT23->getCommand())
	{
		blockUntilClockHour_INT23();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilClockMinute_INT59->getCommand())
	{
		blockUntilClockMinute_INT59();
		return;
	}

	if (currentCommand->commandString == EventData::loadMapState_STATE->getCommand())
	{
		loadMapState_STATE();
		return;
	}
	if (currentCommand->commandString == EventData::runEvent_EVENT->getCommand())
	{
		runEvent_EVENT();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilEventDone_EVENT->getCommand())
	{
		blockUntilEventDone_EVENT();
		return;
	}
	if (currentCommand->commandString == EventData::clearThisEvent->getCommand())
	{
		clearThisEvent();
		return;
	}
	if (currentCommand->commandString == EventData::clearEvent_EVENT->getCommand())
	{
		clearEvent_EVENT();
		return;
	}

	if (currentCommand->commandString == EventData::setThisActivated_BOOL->getCommand())
	{
		setThisActivated_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::toggleThisActivated->getCommand())
	{
		toggleThisActivated();
		return;
	}

	if (currentCommand->commandString == EventData::setLastBeenHereTime->getCommand())
	{
		setLastBeenHereTime();
		return;
	}
	if (currentCommand->commandString == EventData::resetLastBeenHereTime->getCommand())
	{
		resetLastBeenHereTime();
		return;
	}

	if (currentCommand->commandString == EventData::setFlag_FLAG_BOOL->getCommand())
	{
		setFlag_FLAG_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setFlagTrue_FLAG->getCommand())
	{
		setFlagTrue_FLAG();
		return;
	}
	if (currentCommand->commandString == EventData::setFlagFalse_FLAG->getCommand())
	{
		setFlagFalse_FLAG();
		return;
	}

	if (currentCommand->commandString == EventData::giveSkillPoints_SKILL_INT->getCommand())
	{
		giveSkillPoints_SKILL_INT();
		return;
	}
	if (currentCommand->commandString == EventData::removeSkillPoints_SKILL_INT->getCommand())
	{
		removeSkillPoints_SKILL_INT();
		return;
	}
	if (currentCommand->commandString == EventData::setSkillPoints_SKILL_INT->getCommand())
	{
		setSkillPoints_SKILL_INT();
		return;
	}

	if (currentCommand->commandString == EventData::enterThisDoor->getCommand())
	{
		enterThisDoor();
		return;
	}
	if (currentCommand->commandString == EventData::enterThisWarp->getCommand())
	{
		enterThisWarp();
		return;
	}
	if (currentCommand->commandString == EventData::enterDoor_DOOR->getCommand())
	{
		enterDoor_DOOR();
		return;
	}
	if (currentCommand->commandString == EventData::enterWarp_WARP->getCommand())
	{
		enterWarp_WARP();
		return;
	}
	if (currentCommand->commandString == EventData::changeMap_MAP_AREA->getCommand())
	{
		changeMap_MAP_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::changeMap_MAP_DOOR->getCommand())
	{
		changeMap_MAP_DOOR();
		return;
	}
	if (currentCommand->commandString == EventData::changeMap_MAP_INT_INT->getCommand())
	{
		changeMap_MAP_INT_INT();
		return;
	}
	if (currentCommand->commandString == EventData::changeMap_MAP_WARP->getCommand())
	{
		changeMap_MAP_WARP();
		return;
	}

	if (currentCommand->commandString == EventData::doDialogue_DIALOGUE->getCommand())
	{
		doDialogue_DIALOGUE();
		return;
	}
	if (currentCommand->commandString == EventData::doDialogueWithCaption_DIALOGUE->getCommand())
	{
		doDialogueWithCaption_DIALOGUE();
		return;
	}
	if (currentCommand->commandString == EventData::doDialogueIfNew_DIALOGUE->getCommand())
	{
		doDialogueIfNew_DIALOGUE();
		return;
	}

	if (currentCommand->commandString == EventData::setSpriteBox0_ENTITY->getCommand())
	{
		setSpriteBox0_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::setSpriteBox1_ENTITY->getCommand())
	{
		setSpriteBox1_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::setSpriteBox0_SPRITE->getCommand())
	{
		setSpriteBox0_SPRITE();
		return;
	}
	if (currentCommand->commandString == EventData::setSpriteBox1_SPRITE->getCommand())
	{
		setSpriteBox1_SPRITE();
		return;
	}

	if (currentCommand->commandString == EventData::blockUntilTextBoxClosed->getCommand())
	{
		blockUntilTextBoxClosed();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilTextAnswerBoxClosed->getCommand())
	{
		blockUntilTextAnswerBoxClosed();
		return;
	}

	if (currentCommand->commandString == EventData::doCinematicTextNoBorder_DIALOGUE_INTy->getCommand())
	{
		doCinematicTextNoBorder_DIALOGUE_INTy();
		return;
	}
	// if(currentCommand.commandString.equals(EventData.playVideo_VIDEO.getCommand())){playVideo_VIDEO();return; }


	if (currentCommand->commandString == EventData::setDoorOpenAnimation_DOOR_BOOLopenClose->getCommand())
	{
		setDoorOpenAnimation_DOOR_BOOLopenClose();
		return;
	}
	if (currentCommand->commandString == EventData::setDoorActionIcon_DOOR_BOOLonOff->getCommand())
	{
		setDoorActionIcon_DOOR_BOOLonOff();
		return;
	}
	if (currentCommand->commandString == EventData::setDoorDestination_DOOR_DOORdestination->getCommand())
	{
		setDoorDestination_DOOR_DOORdestination();
		return;
	}
	if (currentCommand->commandString == EventData::setAreaActionIcon_AREA_BOOLonOff->getCommand())
	{
		setAreaActionIcon_AREA_BOOLonOff();
		return;
	}
	if (currentCommand->commandString == EventData::setWarpDestination_WARP_WARPdestination->getCommand())
	{
		setWarpDestination_WARP_WARPdestination();
		return;
	}


	if (currentCommand->commandString == EventData::setCameraNoTarget->getCommand())
	{
		setCameraNoTarget();
		return;
	}
	if (currentCommand->commandString == EventData::setCameraTargetToArea_AREA->getCommand())
	{
		setCameraTarget_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::setCameraTargetToEntity_ENTITY->getCommand())
	{
		setCameraTarget_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::setCameraIgnoreBounds_BOOL->getCommand())
	{
		setCameraIgnoreBounds_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setCameraTargetToPlayer->getCommand())
	{
		setCameraTargetToPlayer();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilCameraReaches_AREA->getCommand())
	{
		blockUntilCameraReaches_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilCameraReaches_ENTITY->getCommand())
	{
		blockUntilCameraReaches_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilCameraReachesPlayer->getCommand())
	{
		blockUntilCameraReachesPlayer();
		return;
	}
	if (currentCommand->commandString == EventData::pushCameraState->getCommand())
	{
		pushCameraState();
		return;
	}
	if (currentCommand->commandString == EventData::popCameraState->getCommand())
	{
		popCameraState();
		return;
	}
	if (currentCommand->commandString == EventData::setKeyboardCameraZoom_BOOL->getCommand())
	{
		setKeyboardCameraZoom_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::enableKeyboardCameraZoom->getCommand())
	{
		enableKeyboardCameraZoom();
		return;
	}
	if (currentCommand->commandString == EventData::disableKeyboardCameraZoom->getCommand())
	{
		disableKeyboardCameraZoom();
		return;
	}
	if (currentCommand->commandString == EventData::setCameraAutoZoomByPlayerMovement_BOOL->getCommand())
	{
		setCameraAutoZoomByPlayerMovement_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::enableCameraAutoZoomByPlayerMovement->getCommand())
	{
		enableCameraAutoZoomByPlayerMovement();
		return;
	}
	if (currentCommand->commandString == EventData::disableCameraAutoZoomByPlayerMovement->getCommand())
	{
		disableCameraAutoZoomByPlayerMovement();
		return;
	}
	if (currentCommand->commandString == EventData::setCameraZoom_FLOAT->getCommand())
	{
		setCameraZoom_FLOAT();
		return;
	}
	if (currentCommand->commandString == EventData::setCameraSpeed_FLOAT->getCommand())
	{
		setCameraSpeed_FLOAT();
		return;
	}


	if (currentCommand->commandString == EventData::setPlayerToTempPlayerWithSprite_SPRITE->getCommand())
	{
		setPlayerToTempPlayerWithSprite_SPRITE();
		return;
	}
	if (currentCommand->commandString == EventData::setPlayerToNormalPlayer->getCommand())
	{
		setPlayerToNormalPlayer();
		return;
	}
	if (currentCommand->commandString == EventData::setPlayerExists_BOOL->getCommand())
	{
		setPlayerExists_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setPlayerControlsEnabled_BOOL->getCommand())
	{
		setPlayerControlsEnabled_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::enablePlayerControls->getCommand())
	{
		enablePlayerControls();
		return;
	}
	if (currentCommand->commandString == EventData::disablePlayerControls->getCommand())
	{
		disablePlayerControls();
		return;
	}
	if (currentCommand->commandString == EventData::setPlayerAutoPilot_BOOL->getCommand())
	{
		setPlayerAutoPilot_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setPlayerShowNameCaption_BOOL->getCommand())
	{
		setPlayerShowNameCaption_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setPlayerShowAccountTypeCaption_BOOL->getCommand())
	{
		setPlayerShowAccountTypeCaption_BOOL();
		return;
	}

	if (currentCommand->commandString == EventData::playerSetBehaviorQueueOnOff_BOOL->getCommand())
	{
		playerSetBehaviorQueueOnOff_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::playerSetToArea_AREA->getCommand())
	{
		playerSetToArea_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::playerSetToDoor_DOOR->getCommand())
	{
		playerSetToDoor_DOOR();
		return;
	}
	if (currentCommand->commandString == EventData::playerSetToTileXY_INTxTile1X_INTyTile1X->getCommand())
	{
		playerSetToTileXY_INTxTile1X_INTyTile1X();
		return;
	}
	if (currentCommand->commandString == EventData::playerWalkToArea_AREA->getCommand())
	{
		playerWalkToArea_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::playerWalkToDoor_DOOR->getCommand())
	{
		playerWalkToDoor_DOOR();
		return;
	}
	if (currentCommand->commandString == EventData::playerWalkToEntity_ENTITY->getCommand())
	{
		playerWalkToEntity_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::playerWalkToTileXY_INTxTile1X_INTyTile1X->getCommand())
	{
		playerWalkToTileXY_INTxTile1X_INTyTile1X();
		return;
	}
	//		 if(currentCommand.commandString.equals(EventData.playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal.getCommand())){playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();return; }
	//		 if(currentCommand.commandString.equals(EventData.playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal.getCommand())){playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();return; }
	//		 if(currentCommand.commandString.equals(EventData.playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal.getCommand())){playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();return; }
	//		 if(currentCommand.commandString.equals(EventData.playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal.getCommand())){playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();return; }
	if (currentCommand->commandString == EventData::playerBlockUntilReachesArea_AREA->getCommand())
	{
		playerBlockUntilReachesArea_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::playerBlockUntilReachesDoor_DOOR->getCommand())
	{
		playerBlockUntilReachesDoor_DOOR();
		return;
	}
	if (currentCommand->commandString == EventData::playerBlockUntilReachesEntity_ENTITY->getCommand())
	{
		playerBlockUntilReachesEntity_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X->getCommand())
	{
		playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X();
		return;
	}
	if (currentCommand->commandString == EventData::playerWalkToAreaAndBlockUntilThere_AREA->getCommand())
	{
		playerWalkToAreaAndBlockUntilThere_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::playerWalkToEntityAndBlockUntilThere_ENTITY->getCommand())
	{
		playerWalkToEntityAndBlockUntilThere_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::playerWalkToDoorAndBlockUntilThere_DOOR->getCommand())
	{
		playerWalkToDoorAndBlockUntilThere_DOOR();
		return;
	}
	if (currentCommand->commandString == EventData::playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X->getCommand())
	{
		playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X();
		return;
	}
	if (currentCommand->commandString == EventData::playerStandAndShuffle->getCommand())
	{
		playerStandAndShuffle();
		return;
	}
	//		 if(currentCommand.commandString.equals(EventData.playerStandAndShuffleAndFacePlayer.getCommand())){playerStandAndShuffleAndFacePlayer();return; }
	if (currentCommand->commandString == EventData::playerStandAndShuffleAndFaceEntity_ENTITY->getCommand())
	{
		playerStandAndShuffleAndFaceEntity_ENTITY();
		return;
	}
	//		 if(currentCommand.commandString.equals(EventData.playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks.getCommand())){playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks();return; }
	//		 if(currentCommand.commandString.equals(EventData.playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks.getCommand())){playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks();return; }
	//		 if(currentCommand.commandString.equals(EventData.playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks.getCommand())){playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks();return; }
	//		 if(currentCommand.commandString.equals(EventData.playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks.getCommand())){playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks();return; }
	//		 if(currentCommand.commandString.equals(EventData.playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks.getCommand())){playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks();return; }
	if (currentCommand->commandString == EventData::playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame->getCommand())
	{
		playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame();
		return;
	}
	if (currentCommand->commandString == EventData::playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame->getCommand())
	{
		playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame();
		return;
	}
	if (currentCommand->commandString == EventData::playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks->getCommand())
	{
		playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks();
		return;
	}
	if (currentCommand->commandString == EventData::playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks->getCommand())
	{
		playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks();
		return;
	}
	if (currentCommand->commandString == EventData::playerStopAnimating->getCommand())
	{
		playerStopAnimating();
		return;
	}
	if (currentCommand->commandString == EventData::playerSetGlobalAnimationDisabled_BOOL->getCommand())
	{
		playerSetGlobalAnimationDisabled_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::playerSetMovementSpeed_INTticksPerPixel->getCommand())
	{
		playerSetMovementSpeed_INTticksPerPixel();
		return;
	}
	if (currentCommand->commandString == EventData::playerSetFaceMovementDirection_STRINGdirection->getCommand())
	{
		playerSetFaceMovementDirection_STRINGdirection();
		return;
	}
	//		 if(currentCommand.commandString.equals(EventData.playerSetNonWalkable_BOOL.getCommand())){playerSetNonWalkable_BOOL();return; }
	//		 if(currentCommand.commandString.equals(EventData.playerSetPushable_BOOL.getCommand())){playerSetPushable_BOOL();return; }
	if (currentCommand->commandString == EventData::playerSetToAlpha_FLOAT->getCommand())
	{
		playerSetToAlpha_FLOAT();
		return;
	}
	//		 if(currentCommand.commandString.equals(EventData.playerFadeOutDelete.getCommand())){playerFadeOutDelete();return; }
	//		 if(currentCommand.commandString.equals(EventData.playerDeleteInstantly.getCommand())){playerDeleteInstantly();return; }


	if (currentCommand->commandString == EventData::entitySetBehaviorQueueOnOff_ENTITY_BOOL->getCommand())
	{
		entitySetBehaviorQueueOnOff_ENTITY_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::entitySetToArea_ENTITY_AREA->getCommand())
	{
		entitySetToArea_ENTITY_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::entitySetToDoor_ENTITY_DOOR->getCommand())
	{
		entitySetToDoor_ENTITY_DOOR();
		return;
	}
	if (currentCommand->commandString == EventData::entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X->getCommand())
	{
		entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X();
		return;
	}
	if (currentCommand->commandString == EventData::entityWalkToArea_ENTITY_AREA->getCommand())
	{
		entityWalkToArea_ENTITY_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::entityWalkToDoor_ENTITY_DOOR->getCommand())
	{
		entityWalkToDoor_ENTITY_DOOR();
		return;
	}
	if (currentCommand->commandString == EventData::entityWalkToEntity_ENTITY_ENTITY->getCommand())
	{
		entityWalkToEntity_ENTITY_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X->getCommand())
	{
		entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X();
		return;
	}
	if (currentCommand->commandString == EventData::entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal->getCommand())
	{
		entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();
		return;
	}
	if (currentCommand->commandString == EventData::entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal->getCommand())
	{
		entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();
		return;
	}
	if (currentCommand->commandString == EventData::entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal->getCommand())
	{
		entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();
		return;
	}
	if (currentCommand->commandString == EventData::entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal->getCommand())
	{
		entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal();
		return;
	}
	if (currentCommand->commandString == EventData::entityBlockUntilReachesArea_ENTITY_AREA->getCommand())
	{
		entityBlockUntilReachesArea_ENTITY_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::entityBlockUntilReachesDoor_ENTITY_DOOR->getCommand())
	{
		entityBlockUntilReachesDoor_ENTITY_DOOR();
		return;
	}
	if (currentCommand->commandString == EventData::entityBlockUntilReachesEntity_ENTITY_ENTITY->getCommand())
	{
		entityBlockUntilReachesEntity_ENTITY_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X->getCommand())
	{
		entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X();
		return;
	}
	if (currentCommand->commandString == EventData::entityWalkToAreaAndBlockUntilThere_ENTITY_AREA->getCommand())
	{
		entityWalkToAreaAndBlockUntilThere_ENTITY_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY->getCommand())
	{
		entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR->getCommand())
	{
		entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR();
		return;
	}
	if (currentCommand->commandString == EventData::entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X->getCommand())
	{
		entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X();
		return;
	}

	if (currentCommand->commandString == EventData::entityStandAndShuffle_ENTITY->getCommand())
	{
		entityStandAndShuffle_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::entityStandAndShuffleAndFacePlayer_ENTITY->getCommand())
	{
		entityStandAndShuffleAndFacePlayer_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY->getCommand())
	{
		entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks->getCommand())
	{
		entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks();
		return;
	}
	if (currentCommand->commandString == EventData::entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks->getCommand())
	{
		entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks();
		return;
	}
	if (currentCommand->commandString == EventData::entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks->getCommand())
	{
		entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks();
		return;
	}
	if (currentCommand->commandString == EventData::entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks->getCommand())
	{
		entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks();
		return;
	}
	if (currentCommand->commandString == EventData::entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks->getCommand())
	{
		entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks();
		return;
	}
	if (currentCommand->commandString == EventData::entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName->getCommand())
	{
		entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName();
		return;
	}
	if (currentCommand->commandString == EventData::entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame->getCommand())
	{
		entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame();
		return;
	}
	if (currentCommand->commandString == EventData::entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame->getCommand())
	{
		entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame();
		return;
	}
	if (currentCommand->commandString == EventData::entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks->getCommand())
	{
		entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks();
		return;
	}
	if (currentCommand->commandString == EventData::entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks->getCommand())
	{
		entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks();
		return;
	}
	if (currentCommand->commandString == EventData::entityStopAnimating_ENTITY->getCommand())
	{
		entityStopAnimating_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::entitySetGlobalAnimationDisabled_ENTITY_BOOL->getCommand())
	{
		entitySetGlobalAnimationDisabled_ENTITY_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::entitySetMovementSpeed_ENTITY_INTticksPerPixel->getCommand())
	{
		entitySetMovementSpeed_ENTITY_INTticksPerPixel();
		return;
	}
	if (currentCommand->commandString == EventData::entitySetFaceMovementDirection_ENTITY_STRINGdirection->getCommand())
	{
		entitySetFaceMovementDirection_ENTITY_STRINGdirection();
		return;
	}
	if (currentCommand->commandString == EventData::entitySetNonWalkable_ENTITY_BOOL->getCommand())
	{
		entitySetNonWalkable_ENTITY_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::entitySetPushable_ENTITY_BOOL->getCommand())
	{
		entitySetPushable_ENTITY_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::entitySetToAlpha_ENTITY_FLOAT->getCommand())
	{
		entitySetToAlpha_ENTITY_FLOAT();
		return;
	}
	if (currentCommand->commandString == EventData::entityFadeOutDelete_ENTITY->getCommand())
	{
		entityFadeOutDelete_ENTITY();
		return;
	}
	if (currentCommand->commandString == EventData::entityDeleteInstantly_ENTITY->getCommand())
	{
		entityDeleteInstantly_ENTITY();
		return;
	}


	if (currentCommand->commandString == EventData::spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA->getCommand())
	{
		spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA->getCommand())
	{
		spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA->getCommand())
	{
		spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA->getCommand())
	{
		spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA();
		return;
	}

	if (currentCommand->commandString == EventData::createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy->getCommand())
	{
		createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy();
		return;
	}
	if (currentCommand->commandString == EventData::createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy->getCommand())
	{
		createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy();
		return;
	}
	if (currentCommand->commandString == EventData::createScreenSpriteUnderText_SPRITE_INTx_INTy->getCommand())
	{
		createScreenSpriteUnderText_SPRITE_INTx_INTy();
		return;
	}
	if (currentCommand->commandString == EventData::createScreenSpriteOverText_SPRITE_INTx_INTy->getCommand())
	{
		createScreenSpriteOverText_SPRITE_INTx_INTy();
		return;
	}


	if (currentCommand->commandString == EventData::giveItem_ITEM->getCommand())
	{
		giveItem_ITEM();
		return;
	}
	if (currentCommand->commandString == EventData::takeItem_ITEM->getCommand())
	{
		takeItem_ITEM();
		return;
	}
	if (currentCommand->commandString == EventData::giveGame_GAME->getCommand())
	{
		giveGame_GAME();
		return;
	}
	if (currentCommand->commandString == EventData::takeMoney_FLOAT->getCommand())
	{
		takeMoney_FLOAT();
		return;
	}
	if (currentCommand->commandString == EventData::giveMoney_FLOAT->getCommand())
	{
		giveMoney_FLOAT();
		return;
	}


	if (currentCommand->commandString == EventData::playSound_SOUND->getCommand())
	{
		playSound_SOUND();
		return;
	}
	if (currentCommand->commandString == EventData::playSound_SOUND_FLOATvol->getCommand())
	{
		playSound_SOUND_FLOATvol();
		return;
	}
	if (currentCommand->commandString == EventData::playSound_SOUND_FLOATvol_FLOATpitch_INTtimes->getCommand())
	{
		playSound_SOUND_FLOATvol_FLOATpitch_INTtimes();
		return;
	}
	if (currentCommand->commandString == EventData::playMusicOnce_MUSIC->getCommand())
	{
		playMusicOnce_MUSIC();
		return;
	}
	if (currentCommand->commandString == EventData::playMusicLoop_MUSIC->getCommand())
	{
		playMusicLoop_MUSIC();
		return;
	}
	if (currentCommand->commandString == EventData::playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop->getCommand())
	{
		playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop();
		return;
	}
	if (currentCommand->commandString == EventData::stopMusic_MUSIC->getCommand())
	{
		stopMusic_MUSIC();
		return;
	}
	if (currentCommand->commandString == EventData::stopAllMusic->getCommand())
	{
		stopAllMusic();
		return;
	}
	if (currentCommand->commandString == EventData::fadeOutMusic_MUSIC_INT->getCommand())
	{
		fadeOutMusic_MUSIC_INT();
		return;
	}
	if (currentCommand->commandString == EventData::fadeOutAllMusic_INT->getCommand())
	{
		fadeOutAllMusic_INT();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC->getCommand())
	{
		blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilMusicDone_MUSIC->getCommand())
	{
		blockUntilMusicDone_MUSIC();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilAllMusicDone->getCommand())
	{
		blockUntilAllMusicDone();
		return;
	}


	if (currentCommand->commandString == EventData::shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake->getCommand())
	{
		shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake();
		return;
	}
	if (currentCommand->commandString == EventData::fadeToBlack_INTticks->getCommand())
	{
		fadeToBlack_INTticks();
		return;
	}
	if (currentCommand->commandString == EventData::fadeFromBlack_INTticks->getCommand())
	{
		fadeFromBlack_INTticks();
		return;
	}
	if (currentCommand->commandString == EventData::fadeToWhite_INTticks->getCommand())
	{
		fadeToWhite_INTticks();
		return;
	}
	if (currentCommand->commandString == EventData::fadeFromWhite_INTticks->getCommand())
	{
		fadeFromWhite_INTticks();
		return;
	}

	if (currentCommand->commandString == EventData::fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha->getCommand())
	{
		fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha();
		return;
	}
	if (currentCommand->commandString == EventData::fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha->getCommand())
	{
		fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha();
		return;
	}
	if (currentCommand->commandString == EventData::fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha->getCommand())
	{
		fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha();
		return;
	}
	if (currentCommand->commandString == EventData::setInstantOverlay_INTr_INTg_INTb_FLOATa->getCommand())
	{
		setInstantOverlay_INTr_INTg_INTb_FLOATa();
		return;
	}
	if (currentCommand->commandString == EventData::clearOverlay->getCommand())
	{
		clearOverlay();
		return;
	}

	if (currentCommand->commandString == EventData::fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha->getCommand())
	{
		fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha();
		return;
	}
	if (currentCommand->commandString == EventData::setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa->getCommand())
	{
		setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa();
		return;
	}
	if (currentCommand->commandString == EventData::clearOverlayUnderLights->getCommand())
	{
		clearOverlayUnderLights();
		return;
	}
	if (currentCommand->commandString == EventData::fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha->getCommand())
	{
		fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha();
		return;
	}
	if (currentCommand->commandString == EventData::setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa->getCommand())
	{
		setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa();
		return;
	}
	if (currentCommand->commandString == EventData::clearOverlayGroundLayer->getCommand())
	{
		clearOverlayGroundLayer();
		return;
	}

	if (currentCommand->commandString == EventData::setLetterbox_BOOL->getCommand())
	{
		setLetterbox_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setLetterbox_BOOL_INTticks->getCommand())
	{
		setLetterbox_BOOL_INTticks();
		return;
	}
	if (currentCommand->commandString == EventData::setLetterbox_BOOL_INTticks_INTsize->getCommand())
	{
		setLetterbox_BOOL_INTticks_INTsize();
		return;
	}
	if (currentCommand->commandString == EventData::setLetterbox_BOOL_INTticks_FLOATsize->getCommand())
	{
		setLetterbox_BOOL_INTticks_FLOATsize();
		return;
	}
	if (currentCommand->commandString == EventData::setBlur_BOOL->getCommand())
	{
		setBlur_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setMosaic_BOOL->getCommand())
	{
		setMosaic_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setHBlankWave_BOOL->getCommand())
	{
		setHBlankWave_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setRotate_BOOL->getCommand())
	{
		setRotate_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setBlackAndWhite_BOOL->getCommand())
	{
		setBlackAndWhite_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setInvertedColors_BOOL->getCommand())
	{
		setInvertedColors_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::set8BitMode_BOOL->getCommand())
	{
		set8BitMode_BOOL();
		return;
	}

	if (currentCommand->commandString == EventData::setEngineSpeed_FLOAT->getCommand())
	{
		setEngineSpeed_FLOAT();
		return;
	}

	if (currentCommand->commandString == EventData::toggleLightOnOff_LIGHT->getCommand())
	{
		toggleLightOnOff_LIGHT();
		return;
	}
	if (currentCommand->commandString == EventData::setLightOnOff_LIGHT_BOOL->getCommand())
	{
		setLightOnOff_LIGHT_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setLightFlicker_LIGHT_BOOL->getCommand())
	{
		setLightFlicker_LIGHT_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::toggleAllLightsOnOff->getCommand())
	{
		toggleAllLightsOnOff();
		return;
	}
	if (currentCommand->commandString == EventData::setAllLightsOnOff_BOOL->getCommand())
	{
		setAllLightsOnOff_BOOL();
		return;
	}

	if (currentCommand->commandString == EventData::setRandomSpawn_BOOL->getCommand())
	{
		setRandomSpawn_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::deleteRandoms->getCommand())
	{
		deleteRandoms();
		return;
	}

	if (currentCommand->commandString == EventData::makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb->getCommand())
	{
		makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb();
		return;
	}
	if (currentCommand->commandString == EventData::makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb->getCommand())
	{
		makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb();
		return;
	}
	if (currentCommand->commandString == EventData::makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb->getCommand())
	{
		makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb();
		return;
	}
	if (currentCommand->commandString == EventData::makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb->getCommand())
	{
		makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb();
		return;
	}
	if (currentCommand->commandString == EventData::setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks->getCommand())
	{
		setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks();
		return;
	}

	if (currentCommand->commandString == EventData::setShowClockCaption_BOOL->getCommand())
	{
		setShowClockCaption_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setShowDayCaption_BOOL->getCommand())
	{
		setShowDayCaption_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setShowMoneyCaption_BOOL->getCommand())
	{
		setShowMoneyCaption_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setShowAllStatusBarCaptions_BOOL->getCommand())
	{
		setShowAllStatusBarCaptions_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setShowStatusBar_BOOL->getCommand())
	{
		setShowStatusBar_BOOL();
		return;
	}


	if (currentCommand->commandString == EventData::setShowNDButton_BOOL->getCommand())
	{
		setShowNDButton_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setShowGameStoreButton_BOOL->getCommand())
	{
		setShowGameStoreButton_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setShowStuffButton_BOOL->getCommand())
	{
		setShowStuffButton_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setShowAllButtons_BOOL->getCommand())
	{
		setShowAllButtons_BOOL();
		return;
	}


	if (currentCommand->commandString == EventData::setNDEnabled_BOOL->getCommand())
	{
		setNDEnabled_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setGameStoreMenuEnabled_BOOL->getCommand())
	{
		setGameStoreMenuEnabled_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setStuffMenuEnabled_BOOL->getCommand())
	{
		setStuffMenuEnabled_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setAllMenusAndNDEnabled_BOOL->getCommand())
	{
		setAllMenusAndNDEnabled_BOOL();
		return;
	}


	if (currentCommand->commandString == EventData::setClockUnknown->getCommand())
	{
		setClockUnknown();
		return;
	}
	if (currentCommand->commandString == EventData::setClockNormal->getCommand())
	{
		setClockNormal();
		return;
	}
	if (currentCommand->commandString == EventData::setTimePaused_BOOL->getCommand())
	{
		setTimePaused_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::setTimeFastForward->getCommand())
	{
		setTimeFastForward();
		return;
	}
	if (currentCommand->commandString == EventData::setTimeNormalSpeed->getCommand())
	{
		setTimeNormalSpeed();
		return;
	}

	if (currentCommand->commandString == EventData::setNDOpen_BOOL->getCommand())
	{
		setNDOpen_BOOL();
		return;
	}
	if (currentCommand->commandString == EventData::startGame->getCommand())
	{
		startGame();
		return;
	}
	if (currentCommand->commandString == EventData::startBobsGameOnStadiumScreen_AREA->getCommand())
	{
		startBobsGameOnStadiumScreen_AREA();
		return;
	}
	if (currentCommand->commandString == EventData::blockUntilBobsGameDead->getCommand())
	{
		blockUntilBobsGameDead();
		return;
	}
	if (currentCommand->commandString == EventData::showLoginScreen->getCommand())
	{
		showLoginScreen();
		return;
	}


	if (currentCommand->commandString == EventData::closeAllMenusAndND->getCommand())
	{
		closeAllMenusAndND();
		return;
	}

	// if(currentCommand.commandString.equals(EventData.enableAllMenus.getCommand())){enableAllMenusAndND();return; }

	if (currentCommand->commandString == EventData::openStuffMenu->getCommand())
	{
		openStuffMenu();
		return;
	}
	if (currentCommand->commandString == EventData::openItemsMenu->getCommand())
	{
		openItemsMenu();
		return;
	}
	if (currentCommand->commandString == EventData::openLogMenu->getCommand())
	{
		openLogMenu();
		return;
	}
	if (currentCommand->commandString == EventData::openStatusMenu->getCommand())
	{
		openStatusMenu();
		return;
	}
	if (currentCommand->commandString == EventData::openFriendsMenu->getCommand())
	{
		openFriendsMenu();
		return;
	}
	if (currentCommand->commandString == EventData::openSettingsMenu->getCommand())
	{
		openSettingsMenu();
		return;
	}
	if (currentCommand->commandString == EventData::openGameStoreMenu->getCommand())
	{
		openGameStoreMenu();
		return;
	}

	//		 if(currentCommand.commandString.equals(EventData.pushGameState.getCommand())){pushGameState();return; }
	//		 if(currentCommand.commandString.equals(EventData.popGameState.getCommand())){popGameState();return; }
	//
	//		 if(currentCommand.commandString.equals(EventData.showTitleScreen.getCommand())){showTitleScreen();return; }
	//		 if(currentCommand.commandString.equals(EventData.showCinemaEvent.getCommand())){showCinemaEvent();return; }
	//		 if(currentCommand.commandString.equals(EventData.runGlobalEvent.getCommand())){runGlobalEvent();return; }


	{
		log.error(string("Error! Unknown Command: ") + currentCommand->commandString);
		getNextCommandInParent();
		return;
	}
}

void Event::isPlayerTouchingThisArea()
{ //===============================================================================================


	if (this->area == nullptr)
	{
		log.error("isPlayerTouchingThisArea() in event with no area!");
	}

	if ((dynamic_cast<WarpArea*>(this->area) != NULL))
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getPlayer()->isWalkingIntoArea(area));
	}
	else
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getPlayer()->isAreaBoundaryTouchingMyHitBox(area));
	}
}

void Event::isPlayerWalkingIntoThisDoor()
{ //===============================================================================================

	if (this->door == nullptr)
	{
		log.error("isPlayerWalkingIntoThisDoor() in event with no door!");
	}

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getPlayer()->isWalkingIntoEntity(door));
}

void Event::isPlayerTouchingThisEntity()
{ //===============================================================================================

	if (this->entity == nullptr)
	{
		log.error("isPlayerTouchingThisEntity() in event with no entity!");
	}

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getPlayer()->isEntityHitBoxTouchingMyHitBox(entity));
}

void Event::isPlayerTouchingAnyEntityUsingThisSprite()
{ //===============================================================================================


	if (this->sprite == nullptr)
	{
		log.error("isPlayerTouchingAnyEntityUsingThisSprite() in event with no sprite!");
	}

	ArrayList<Entity*>* e = getMap()->getAllEntitiesUsingSpriteAsset(sprite);

	bool b = false;

	for (int i = 0; i < e->size(); i++)
	{
		if (getPlayer()->isEntityHitBoxTouchingMyHitBox(e->get(i)))
		{
			b = true;
		}
	}

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(b);
}

void Event::isPlayerWalkingIntoDoor_DOOR()
{ //===============================================================================================
	int p = 0;
	if (currentCommand->parameterList->size() > 0)
	{
		Door* d = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getPlayer()->isWalkingIntoEntity(d));
	}
}

void Event::isPlayerWalkingIntoWarp_WARP()
{ //===============================================================================================
	int p = 0;
	if (currentCommand->parameterList->size() > 0)
	{
		WarpArea* d = static_cast<WarpArea*>(currentCommand->parameterList->get(p++)->object);

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getPlayer()->isWalkingIntoArea(d));
	}
}

void Event::isPlayerAutoPilotOn()
{ //===============================================================================================


	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getPlayer()->isAutoPilotOn());
}

void Event::isActionButtonHeld()
{ //===============================================================================================


	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getControlsManager()->BGCLIENT_ACTION_HELD);
}

void Event::isFlagSet_FLAG()
{ //===============================================================================================
	int p = 0;

	if (currentCommand->parameterList->size() > 0)
	{
		Flag* f = static_cast<Flag*>(currentCommand->parameterList->get(p++)->object); //we don't particularly need to know what the actual flag name is... ID is fine.

		//Boolean value = f.checkServerValueAndResetAfterSuccessfulReturn();
		//if(value!=null)
		bool value = f->getValue_S();
		{
			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(value);
		}
	}
}

void Event::hasSkillAtLeast_SKILL_FLOAT1()
{ //===============================================================================================
	int p = 0;


	if (currentCommand->parameterList->size() > 1)
	{
		Skill* s = static_cast<Skill*>(currentCommand->parameterList->get(p++)->object);
		float f = currentCommand->parameterList->get(p++)->f;

		float value = s->getValue_S();

		{
			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(value >= f);
		}
	}
}

void Event::isCurrentState_STATE()
{ //===============================================================================================
	int p = 0;

	if (currentCommand->parameterList->size() > 0)
	{
		MapState* s = static_cast<MapState*>(currentCommand->parameterList->get(p++)->object);

		if (s != nullptr)
		{
			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getMap()->currentState == s);
		}
	}
}

void Event::isPlayerStandingInArea_AREA()
{ //===============================================================================================
	int p = 0;

	if (currentCommand->parameterList->size() > 0)
	{
		Area* area = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getPlayer()->isAreaBoundaryTouchingMyHitBox(area));
	}
}

void Event::isEntityStandingInArea_ENTITY_AREA()
{ //===============================================================================================
	int p = 0;

	if (currentCommand->parameterList->size() > 1)
	{
		Entity* entity = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
		Area* area = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(entity->isAreaBoundaryTouchingMyHitBox(area));
	}
}

void Event::hourPastOrEqualTo_INT23()
{ //===============================================================================================
	int p = 0;

	int hour = currentCommand->parameterList->get(p++)->i;

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getClock()->hour >= hour);
}

void Event::hourLessThan_INT23()
{ //===============================================================================================
	int p = 0;

	int hour = currentCommand->parameterList->get(p++)->i;

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getClock()->hour < hour);
}

void Event::minutePastOrEqualTo_INT59()
{ //===============================================================================================
	int p = 0;

	int minute = currentCommand->parameterList->get(p++)->i;

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getClock()->minute >= minute);
}

void Event::minuteLessThan_INT59()
{ //===============================================================================================
	int p = 0;
	int minute = currentCommand->parameterList->get(p++)->i;

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getClock()->minute < minute);
}

void Event::hasMoneyAtLeastAmount_FLOAT()
{ //===============================================================================================
	int p = 0;
	float money = currentCommand->parameterList->get(p++)->f;

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getWallet()->money >= money);
}

void Event::hasMoneyLessThanAmount_FLOAT()
{ //===============================================================================================
	int p = 0;
	float money = currentCommand->parameterList->get(p++)->f;

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getWallet()->money < money);
}

void Event::hasItem_ITEM()
{ //===============================================================================================
	int p = 0;
	Item* item = static_cast<Item*>(currentCommand->parameterList->get(p++)->object);

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(item->getHaveItemValue_S());
}

void Event::hasGame_GAME()
{ //===============================================================================================
	int p = 0;
	Item* item = static_cast<Item*>(currentCommand->parameterList->get(p++)->object);

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(item->getHaveItemValue_S());
}

void Event::isPlayerMale()
{ //===============================================================================================


	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getPlayer()->isMale);
}

void Event::isPlayerFemale()
{ //===============================================================================================


	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getPlayer()->isFemale);
}

void Event::isAnyEntityUsingSprite_SPRITE()
{ //===============================================================================================
	int p = 0;


	Sprite* sprite = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);

	// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
	if (sprite == nullptr)
	{
		return; //block until sprite has loaded.
	}


	bool b = getMap()->isAnyEntityUsingSpriteAsset(sprite);

	if (sprite != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(b);
	}
}

void Event::isAnyEntityUsingSpriteAtArea_SPRITE_AREA()
{ //===============================================================================================
	int p = 0;

	Sprite* sprite = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

	// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
	if (sprite == nullptr)
	{
		return; //block until sprite has loaded.
	}

	ArrayList<Entity*>* e = a->getMap()->getAllEntitiesTouchingArea(a);


	bool b = false;

	for (int i = 0; i < e->size(); i++)
	{
		if (e->get(i)->sprite == sprite)
		{
			b = true;
		}
	}

	if (sprite != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(b);
	}
}

void Event::isEntitySpawned_ENTITY()
{ //===============================================================================================
	int p = 0;


	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	//will be null if it couldn't find the object ID after searching the entityList

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(e != nullptr);
}

void Event::isEntityAtArea_ENTITY_AREA()
{ //===============================================================================================
	int p = 0;

	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);


	if (e != nullptr)
	{
		Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

		bool b = a->isEntityHitBoxTouchingMyBoundary(e);

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(b);
	}
}

void Event::isAreaEmpty_AREA()
{ //===============================================================================================
	int p = 0;
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);


	if (a != nullptr)
	{
		bool b = a->getMap()->isAnyEntityTouchingArea(a);

		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(b);
	}
}

void Event::hasFinishedDialogue_DIALOGUE()
{ //===============================================================================================
	int p = 0;

	Dialogue* d = static_cast<Dialogue*>(currentCommand->parameterList->get(p++)->object);

	if (d != nullptr)
	{
		//Boolean value = d.checkServerValueAndResetAfterSuccessfulReturn();
		//if(value!=null)

		bool value = d->getDialogueDoneValue_S();
		{
			getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(value);
		}
	}
}

void Event::isTextBoxOpen()
{ //===============================================================================================


	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getTextManager()->isTextBoxOpen());
}

void Event::isTextAnswerBoxOpen()
{ //===============================================================================================


	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getTextManager()->isTextAnswerBoxOpen());
}

void Event::isTextAnswerSelected_INT4()
{ //===============================================================================================

	// TODO Auto-generated method stub


	//handle both string and int, can have two different parameters
}

void Event::isTextAnswerSelected_STRING()
{ //===============================================================================================

	// TODO Auto-generated method stub


	//handle both string and int, can have two different parameters
}

void Event::randomEqualsOneOutOfLessThan_INT()
{ //===============================================================================================
	int p = 0;

	int i = currentCommand->parameterList->get(p++)->i;

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Math::randLessThan(i) == 1);
}

void Event::randomEqualsOneOutOfIncluding_INT()
{ //===============================================================================================
	int p = 0;

	int i = currentCommand->parameterList->get(p++)->i;

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(Math::randUpToIncluding(i) == 1);
}

void Event::isAnyMusicPlaying()
{ //===============================================================================================


	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getAudioManager()->isAnyMusicPlaying());
}

void Event::isMusicPlaying()
{ //===============================================================================================
	int p = 0;

	Music* m = static_cast<Music*>(currentCommand->parameterList->get(p++)->object);

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getAudioManager()->isMusicPlaying(m));
}

void Event::isRaining()
{ //===============================================================================================


	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getMapManager()->isRaining());
}

void Event::isWindy()
{ //===============================================================================================


	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getMapManager()->isWindy());
}

void Event::isSnowing()
{ //===============================================================================================


	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getMapManager()->isSnowing());
}

void Event::isFoggy()
{ //===============================================================================================


	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getMapManager()->isFoggy());
}

void Event::isMapOutside()
{ //===============================================================================================


	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(getMap()->getIsOutside());
}

void Event::hasTalkedToThisToday()
{ //===============================================================================================


	bool gotServerValue = false;
	bool hasTalkedTo = true;

	if (area != nullptr)
	{
		BobBool* b = area->checkServerTalkedToTodayValueAndResetAfterSuccessfulReturn();
		if (b != nullptr)
		{
			gotServerValue = true;
			if (b->value == false)
			{
				hasTalkedTo = false;
			}
		}
	}
	if (door != nullptr)
	{
		BobBool* b = door->checkServerTalkedToTodayValueAndResetAfterSuccessfulReturn();
		if (b != nullptr)
		{
			gotServerValue = true;
			if (b->value == false)
			{
				hasTalkedTo = false;
			}
		}
	}
	if (entity != nullptr)
	{
		BobBool* b = entity->checkServerTalkedToTodayValueAndResetAfterSuccessfulReturn();
		if (b != nullptr)
		{
			gotServerValue = true;
			if (b->value == false)
			{
				hasTalkedTo = false;
			}
		}
	}


	if (gotServerValue)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(hasTalkedTo);
	}
}

void Event::hasBeenMinutesSinceFlagSet_FLAG_INT()
{ //===============================================================================================
	int p = 0;
	Flag* f = static_cast<Flag*>(currentCommand->parameterList->get(p++)->object);

	int i = currentCommand->parameterList->get(p++)->i;


	long long startTime = f->getTimeSet();
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	long long millisecondsPassed = (long long)ticksPassed;
	long long secondsPassed = millisecondsPassed / 1000;
	long long minutesPassed = secondsPassed / 60;

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(minutesPassed >= i);
}

void Event::hasBeenHoursSinceFlagSet_FLAG_INT23()
{ //===============================================================================================
	int p = 0;
	Flag* f = static_cast<Flag*>(currentCommand->parameterList->get(p++)->object);

	int i = currentCommand->parameterList->get(p++)->i;

	long long startTime = f->getTimeSet();
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	long long millisecondsPassed = (long long)ticksPassed;
	long long secondsPassed = millisecondsPassed / 1000;
	long long minutesPassed = secondsPassed / 60;
	long long hoursPassed = minutesPassed / 60;

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(hoursPassed >= i);
}

void Event::hasBeenDaysSinceFlagSet_FLAG_INT()
{ //===============================================================================================
	int p = 0;
	Flag* f = static_cast<Flag*>(currentCommand->parameterList->get(p++)->object);

	int i = currentCommand->parameterList->get(p++)->i;

	long long startTime = f->getTimeSet();
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	long long millisecondsPassed = (long long)ticksPassed;
	long long secondsPassed = millisecondsPassed / 1000;
	long long minutesPassed = secondsPassed / 60;
	long long hoursPassed = minutesPassed / 60;
	long long daysPassed = hoursPassed / 24;

	getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(daysPassed >= i);
}

void Event::isThisActivated()
{ //===============================================================================================

	if (sprite != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(sprite->getIsActivated());
	}
	if (entity != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(entity->getIsActivated());
	}
	if (door != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(door->getIsActivated());
	}
	if (map != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(map->getIsActivated());
	}
	if (area != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(area->getIsActivated());
	}
}

void Event::haveSecondsPassedSinceActivated_INT()
{
	// TODO
}

void Event::haveMinutesPassedSinceActivated_INT()
{
	// TODO
}

void Event::haveHoursPassedSinceActivated_INT()
{
	// TODO
}

void Event::haveDaysPassedSinceActivated_INT()
{
	// TODO
}

void Event::hasActivatedThisEver()
{ //===============================================================================================

	// TODO rename this to "since account created"

	//TODO: have every object have a flagTime sort of deal

	//maybe an underlying time hashtable indexed by TYPEID, gets stored to and from gamesave
	//would kind of be a lot of gamesave updates, maybe update it once every time i enter or leave a room.
}

void Event::hasActivatedThisSinceEnterRoom()
{ //===============================================================================================


	//TODO: make this "since logged on"

	if (sprite != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(sprite->getWasEverActivated());
	}
	if (entity != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(entity->getWasEverActivated());
	}
	if (door != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(door->getWasEverActivated());
	}
	if (map != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(map->getWasEverActivated());
	}
	if (area != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(area->getWasEverActivated());
	}
}

void Event::hasBeenHereEver()
{ //===============================================================================================


	// TODO Auto-generated method stub
}

void Event::hasBeenHereSinceEnterRoom()
{ //===============================================================================================


	//TODO: make this "since logged on"


	if (sprite != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(sprite->getWasEverHere());
	}
	if (entity != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(entity->getWasEverHere());
	}
	if (door != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(door->getWasEverHere());
	}
	if (map != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(map->getWasEverHere());
	}
	if (area != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(area->getWasEverHere());
	}
}

void Event::haveSecondsPassedSinceBeenHere_INT()
{
	// TODO
}

void Event::haveMinutesPassedSinceBeenHere_INT()
{
	// TODO
}

void Event::haveDaysPassedSinceBeenHere_INT()
{ //===============================================================================================

	// TODO Auto-generated method stub
}

void Event::haveHoursPassedSinceBeenHere_INT()
{ //===============================================================================================

	// TODO Auto-generated method stub
}

void Event::isLightOn_LIGHT()
{ //===============================================================================================
	int p = 0;
	Light* s = static_cast<Light*>(currentCommand->parameterList->get(p++)->object);
	if (s != nullptr)
	{
		getNextCommandIfTrueOrSkipToNextParentCommandIfFalse(s->toggleOnOffToggle);
	}
}

void Event::alwaysBlockWhileNotStandingHere()
{ //===============================================================================================

	blockWhileNotHere = true;
	getNextCommand();
}

void Event::blockUntilActionButtonPressed()
{ //===============================================================================================

	if (getControlsManager()->bgClient_ACTION_Pressed())
	{
		getNextCommand();
	}
}

void Event::blockUntilActionCaptionButtonPressed_STRING()
{ //===============================================================================================
	int p = 0;
	GameString* s = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);

	if (s->getInitialized_S() == false)
	{
		return; //wait for it to receive server data in its update() function
	}
	else
	{
		if (area != nullptr)
		{
			if (getActionManager()->area(area, s->text()))
			{
				getNextCommand();
			}
		}
		if (door != nullptr)
		{
			if (getActionManager()->entity(door, s->text()))
			{
				getNextCommand();
			}
		}

		if (entity != nullptr)
		{
			if (getActionManager()->entity(entity, s->text()))
			{
				getNextCommand();
			}
		}
	}
}

void Event::blockUntilCancelButtonPressed()
{ //===============================================================================================

	if (getControlsManager()->bgClient_CANCELRUN_Pressed())
	{
		getNextCommand();
	}
}

void Event::blockForTicks_INT()
{ //===============================================================================================
	int p = 0;

	int i = currentCommand->parameterList->get(p++)->i;


	ticksCounter += getEngine()->realWorldTicksPassed();

	if (ticksCounter >= i)
	{
		ticksCounter = 0;
		getNextCommand();
	}
}

void Event::blockUntilClockHour_INT23()
{ //===============================================================================================
	int p = 0;

	int hour = currentCommand->parameterList->get(p++)->i;

	if (getClock()->hour <= hour)
	{
		getNextCommand();
	}
}

void Event::blockUntilClockMinute_INT59()
{ //===============================================================================================
	int p = 0;
	int minute = currentCommand->parameterList->get(p++)->i;

	if (getClock()->minute <= minute)
	{
		getNextCommand();
	}
}

void Event::loadMapState_STATE()
{ //===============================================================================================
	int p = 0;

	MapState* s = static_cast<MapState*>(currentCommand->parameterList->get(p++)->object);

	getMap()->loadMapState(s);

	getNextCommand();
}

void Event::runEvent_EVENT()
{ //===============================================================================================
	int p = 0;
	Event* e = static_cast<Event*>(currentCommand->parameterList->get(p++)->object);

	getEventManager()->addToEventQueueIfNotThere(e);

	getNextCommand();
}

void Event::blockUntilEventDone_EVENT()
{ //===============================================================================================
	int p = 0;
	Event* e = static_cast<Event*>(currentCommand->parameterList->get(p++)->object);

	if (e->addedToQueue == false)
	{
		getNextCommand();
	}
}

void Event::clearEvent_EVENT()
{ //===============================================================================================
	int p = 0;
	Event* e = static_cast<Event*>(currentCommand->parameterList->get(p++)->object);
	e->reset();
	getEventManager()->runningEventQueue.remove(e);

	getNextCommand();
}

void Event::clearThisEvent()
{ //===============================================================================================

	delete currentCommand;
	currentCommand = nullptr;
}

void Event::setThisActivated_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;


	if (sprite != nullptr)
	{
		sprite->setActivated(b);
	}
	if (entity != nullptr)
	{
		entity->setActivated(b);
	}
	if (door != nullptr)
	{
		door->setActivated(b);
	}
	if (map != nullptr)
	{
		map->setActivated(b);
	}
	if (area != nullptr)
	{
		area->setActivated(b);
	}

	getNextCommand();
}

void Event::toggleThisActivated()
{ //===============================================================================================

	if (sprite != nullptr)
	{
		sprite->toggleActivated();
	}
	if (entity != nullptr)
	{
		entity->toggleActivated();
	}
	if (door != nullptr)
	{
		door->toggleActivated();
	}
	if (map != nullptr)
	{
		map->toggleActivated();
	}
	if (area != nullptr)
	{
		area->toggleActivated();
	}

	getNextCommand();
}

void Event::setLastBeenHereTime()
{ //===============================================================================================

	if (sprite != nullptr)
	{
		sprite->setLastTimeHere();
	}
	if (entity != nullptr)
	{
		entity->setLastTimeHere();
	}
	if (door != nullptr)
	{
		door->setLastTimeHere();
	}
	if (map != nullptr)
	{
		map->setLastTimeHere();
	}
	if (area != nullptr)
	{
		area->setLastTimeHere();
	}

	getNextCommand();
}

void Event::resetLastBeenHereTime()
{ //===============================================================================================

	if (sprite != nullptr)
	{
		sprite->resetLastTimeHere();
	}
	if (entity != nullptr)
	{
		entity->resetLastTimeHere();
	}
	if (door != nullptr)
	{
		door->resetLastTimeHere();
	}
	if (map != nullptr)
	{
		map->resetLastTimeHere();
	}
	if (area != nullptr)
	{
		area->resetLastTimeHere();
	}

	getNextCommand();
}

void Event::setFlag_FLAG_BOOL()
{ //===============================================================================================
	int p = 0;
	Flag* f = static_cast<Flag*>(currentCommand->parameterList->get(p++)->object);
	bool b = currentCommand->parameterList->get(p++)->b;

	f->setValue_S(b);
	getNextCommand();
}

void Event::setFlagTrue_FLAG()
{ //===============================================================================================
	int p = 0;
	Flag* f = static_cast<Flag*>(currentCommand->parameterList->get(p++)->object);
	//boolean b = currentCommand.parameterList.get(p++).b;

	f->setValue_S(true);
	getNextCommand();
}

void Event::setFlagFalse_FLAG()
{ //===============================================================================================
	int p = 0;
	Flag* f = static_cast<Flag*>(currentCommand->parameterList->get(p++)->object);
	//boolean b = currentCommand.parameterList.get(p++).b;

	f->setValue_S(false);
	getNextCommand();
}

void Event::giveSkillPoints_SKILL_INT()
{ //===============================================================================================
	int p = 0;
	Skill* f = static_cast<Skill*>(currentCommand->parameterList->get(p++)->object);
	int i = currentCommand->parameterList->get(p++)->i;

	float value = f->getValue_S();
	value += i;
	f->setValue_S(value);

	getNextCommand();
}

void Event::removeSkillPoints_SKILL_INT()
{ //===============================================================================================
	int p = 0;
	Skill* f = static_cast<Skill*>(currentCommand->parameterList->get(p++)->object);
	int i = currentCommand->parameterList->get(p++)->i;

	float value = f->getValue_S();
	value -= i;
	f->setValue_S(value);

	getNextCommand();
}

void Event::setSkillPoints_SKILL_INT()
{ //===============================================================================================
	int p = 0;
	Skill* f = static_cast<Skill*>(currentCommand->parameterList->get(p++)->object);
	int i = currentCommand->parameterList->get(p++)->i;

	f->setValue_S(i);

	getNextCommand();
}

void Event::enterThisDoor()
{ //=========================================================================================================================
	if (door != nullptr)
	{
		door->enter();
	}
	getNextCommand();
}

void Event::enterThisWarp()
{ //=========================================================================================================================
	if (area != nullptr)
	{
		(static_cast<WarpArea*>(area))->enter();
	}
	getNextCommand();
}

void Event::enterDoor_DOOR()
{ //===============================================================================================
	int p = 0;
	Door* d = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);


	if (d != nullptr)
	{
		d->enter();
	}
	getNextCommand();
}

void Event::enterWarp_WARP()
{ //===============================================================================================
	int p = 0;
	WarpArea* a = static_cast<WarpArea*>(currentCommand->parameterList->get(p++)->object);

	if (a != nullptr)
	{
		(static_cast<WarpArea*>(a))->enter();
	}
	getNextCommand();
}

void Event::changeMap_MAP_AREA()
{ //===============================================================================================
	int p = 0;

	Map* m = (Map*)currentCommand->parameterList->get(p++)->object;

	Area* o = (Area*)currentCommand->parameterList->get(p++)->object;

	getMapManager()->changeMap(m, o);
	this->map = m;

	getNextCommand();
}

void Event::changeMap_MAP_DOOR()
{ //===============================================================================================
	int p = 0;

	Map* m = (Map*)currentCommand->parameterList->get(p++)->object;

	Door* o = (Door*)currentCommand->parameterList->get(p++)->object;

	getMapManager()->changeMap(m, o);
	this->map = m;

	getNextCommand();
}

void Event::changeMap_MAP_WARP()
{ //===============================================================================================
	int p = 0;

	Map* m = (Map*)(currentCommand->parameterList->get(p++)->object);

	WarpArea* o = (WarpArea*)currentCommand->parameterList->get(p++)->object;

	getMapManager()->changeMap(m, o);
	this->map = m;

	getNextCommand();
}

void Event::changeMap_MAP_INT_INT()
{ //===============================================================================================
	int p = 0;

	Map* m = (Map*)(currentCommand->parameterList->get(p++)->object);

	int mapXTiles1X = currentCommand->parameterList->get(p++)->i * 2;
	int mapYTiles1X = currentCommand->parameterList->get(p++)->i * 2;

	getMapManager()->changeMap(m, mapXTiles1X, mapYTiles1X);
	this->map = m;

	getNextCommand();
}

void Event::doDialogue_DIALOGUE()
{ //===============================================================================================
	int p = 0;

	if (currentCommand->parameterList->size() > 0)
	{
		Dialogue* d = static_cast<Dialogue*>(currentCommand->parameterList->get(p++)->object);

		if (d->getInitialized_S() == false)
		{
			return; //wait for it to receive server data in its update() function
		}
		else
		{
			if (area != nullptr)
			{
				area->tellServerTalkedToToday();
			}
			if (door != nullptr)
			{
				door->tellServerTalkedToToday();
			}
			if (entity != nullptr)
			{
				entity->tellServerTalkedToToday();
			}

			getTextManager()->dialogue(d);
			getNextCommand();
		}
	}
}

void Event::doDialogueWithCaption_DIALOGUE()
{ //=========================================================================================================================

	int p = 0;
	if (currentCommand->parameterList->size() > 0)
	{
		Dialogue* d = static_cast<Dialogue*>(currentCommand->parameterList->get(p++)->object);

		if (d->getInitialized_S() == false)
		{
			//wait for it to receive server data in its update() function
		}
		else
		{
			if (area != nullptr)
			{
				if (getActionManager()->area(area, d->caption()))
				{
					area->tellServerTalkedToToday();
					getTextManager()->dialogue(d);
					getNextCommand();
				}
			}
			if (door != nullptr)
			{
				if (getActionManager()->entity(door, d->caption()))
				{
					door->tellServerTalkedToToday();
					getTextManager()->dialogue(d);
					getNextCommand();
				}
			}

			if (entity != nullptr)
			{
				if (getActionManager()->entity(entity, d->caption()))
				{
					entity->tellServerTalkedToToday();
					getTextManager()->dialogue(d);
					getNextCommand();
				}
			}
		}
	}
}

void Event::doDialogueIfNew_DIALOGUE()
{ //===============================================================================================
	int p = 0;
	Dialogue* d = static_cast<Dialogue*>(currentCommand->parameterList->get(p++)->object);

	if (d->getInitialized_S() == false)
	{
		//wait for it to receive server data in its update() function
	}
	else
	{
		//Boolean value = d.checkServerValueAndResetAfterSuccessfulReturn();
		bool value = d->getDialogueDoneValue_S();

		//if(value!=null&&value.booleanValue()==false)
		if (value == false)
		{
			if (area != nullptr)
			{
				area->tellServerTalkedToToday();
			}
			if (door != nullptr)
			{
				door->tellServerTalkedToToday();
			}
			if (entity != nullptr)
			{
				entity->tellServerTalkedToToday();
			}

			getTextManager()->dialogue(d);
			getNextCommand();
		}
	}
}

void Event::setSpriteBox0_ENTITY()
{ //===============================================================================================
	int p = 0;
	//handle 2x overloads
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	getTextManager()->textBox->get(0)->setSpriteWindow((static_cast<Entity*>(e)), nullptr, "");

	getNextCommand();
}

void Event::setSpriteBox1_ENTITY()
{ //===============================================================================================
	int p = 0;
	//handle 2x overloads
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	getTextManager()->textBox->get(1)->setSpriteWindow((static_cast<Entity*>(e)), nullptr, "");

	getNextCommand();
}

void Event::setSpriteBox0_SPRITE()
{ //===============================================================================================
	int p = 0;
	//handle 2x overloads
	Sprite* s = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);
	if (s == nullptr)
	{
		return; //block until loaded.
	}

	getTextManager()->textBox->get(0)->setSpriteWindow(nullptr, (static_cast<Sprite*>(s))->texture, (static_cast<Sprite*>(s))->getDisplayName());

	getNextCommand();
}

void Event::setSpriteBox1_SPRITE()
{ //===============================================================================================
	int p = 0;
	//handle 2x overloads
	Sprite* s = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);
	if (s == nullptr)
	{
		return; //block until loaded.
	}

	getTextManager()->textBox->get(1)->setSpriteWindow(nullptr, (static_cast<Sprite*>(s))->texture, (static_cast<Sprite*>(s))->getDisplayName());

	getNextCommand();
}

void Event::blockUntilTextBoxClosed()
{ //===============================================================================================

	if (getTextManager()->isTextBoxOpen() == false)
	{
		getNextCommand();
	}
}

void Event::blockUntilTextAnswerBoxClosed()
{ //===============================================================================================

	if (getTextManager()->isTextAnswerBoxOpen() == false)
	{
		getNextCommand();
	}
}

void Event::doCinematicTextNoBorder_DIALOGUE_INTy()
{ //===============================================================================================


	//TODO

	//shouldnt really need INTy, just center in middle of screen, transparent getText box background

	getNextCommand();
}

void Event::setDoorOpenAnimation_DOOR_BOOLopenClose()
{ //===============================================================================================
	int p = 0;
	Door* d = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);
	bool b = currentCommand->parameterList->get(p++)->b;

	d->setOpenManually(b);

	getNextCommand();
}

void Event::setDoorActionIcon_DOOR_BOOLonOff()
{ //===============================================================================================
	int p = 0;
	Door* d = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);
	bool b = currentCommand->parameterList->get(p++)->b;

	d->showActionIcon = b;

	getNextCommand();
}

void Event::setDoorDestination_DOOR_DOORdestination()
{ //===============================================================================================
	int p = 0;
	Door* d = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);
	Door* d2 = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);

	d->setDestinationTYPEIDString(d2->getTYPEIDString());

	getNextCommand();
}

void Event::setAreaActionIcon_AREA_BOOLonOff()
{ //===============================================================================================
	int p = 0;
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);
	bool b = currentCommand->parameterList->get(p++)->b;

	a->showActionIcon = b;

	getNextCommand();
}

void Event::setWarpDestination_WARP_WARPdestination()
{ //===============================================================================================
	int p = 0;
	WarpArea* d = static_cast<WarpArea*>(currentCommand->parameterList->get(p++)->object);
	WarpArea* d2 = static_cast<WarpArea*>(currentCommand->parameterList->get(p++)->object);

	d->setDestinationTYPEIDString(d2->getTYPEIDString());


	getNextCommand();
}

void Event::setPlayerToTempPlayerWithSprite_SPRITE()
{ //===============================================================================================
	int p = 0;
	Sprite* s = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);

	if (s == nullptr)
	{
		return; //block until sprite has loaded.
	}

	getClientGameEngine()->setPlayerToTempPlayerWithSprite(s);
	getNextCommand();
}

void Event::setPlayerToNormalPlayer()
{ //===============================================================================================


	getClientGameEngine()->setPlayerToNormalPlayer();
	getNextCommand();
}

void Event::setPlayerExists_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;

	getClientGameEngine()->playerExistsInMap = b;
	getMap()->activeEntityList.remove(getPlayer());

	getNextCommand();
}

void Event::setPlayerControlsEnabled_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getClientGameEngine()->controlsEnabled = b;
	getNextCommand();
}

void Event::enablePlayerControls()
{ //===============================================================================================
	//int p=0;
	//boolean b = currentCommand.parameterList.get(p++).b;
	getClientGameEngine()->controlsEnabled = true;
	getNextCommand();
}

void Event::disablePlayerControls()
{ //===============================================================================================
	//int p=0;
	//boolean b = currentCommand.parameterList.get(p++).b;
	getClientGameEngine()->controlsEnabled = false;
	getNextCommand();
}

void Event::setPlayerAutoPilot_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;

	getPlayer()->setAutoPilot(b);
	getNextCommand();
}

void Event::setPlayerShowNameCaption_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;


	getPlayer()->setShowName(b);
	getNextCommand();
}

void Event::setPlayerShowAccountTypeCaption_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;


	getPlayer()->setShowAccountType(b);
	getNextCommand();
}

void Event::playerSetBehaviorQueueOnOff_BOOL()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	bool b = currentCommand->parameterList->get(p++)->b;

	getPlayer()->behaviorEnabled = b;

	getNextCommand();
}

void Event::playerSetToArea_AREA()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

	getPlayer()->setFeetAtMapXY(a->middleX(), a->middleY());

	getNextCommand();
}

void Event::playerSetToDoor_DOOR()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	Door* a = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);

	getPlayer()->setFeetAtMapXY((float)a->arrivalXPixelsHQ() + 8, (float)a->arrivalYPixelsHQ() + 8);

	getNextCommand();
}

void Event::playerSetToTileXY_INTxTile1X_INTyTile1X()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	int tx = currentCommand->parameterList->get(p++)->i;
	int ty = currentCommand->parameterList->get(p++)->i;

	getPlayer()->setFeetAtMapXY((float)tx * 2 * 8 + 8, (float)ty * 2 * 8 + 8);

	getNextCommand();
}

void Event::playerWalkToArea_AREA()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

	//TODO need behavior queue stuff working better.

	getPlayer()->currentAreaTYPEIDTarget = a->getTYPEIDString();

	getNextCommand();
}

void Event::playerWalkToDoor_DOOR()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	Door* a = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);

	//TODO need behavior queue stuff working better.

	//TODO: use eventBehavior and eventCurrentTargetTYPEID list and all that.

	getPlayer()->currentAreaTYPEIDTarget = a->getTYPEIDString();

	getNextCommand();
}

void Event::playerWalkToEntity_ENTITY()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	Entity* e2 = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	//TODO need behavior queue stuff working better.

	getPlayer()->currentAreaTYPEIDTarget = e2->getTYPEIDString();

	getNextCommand();
}

void Event::playerWalkToTileXY_INTxTile1X_INTyTile1X()
{ //===============================================================================================
	//int p=0;

	//Entity a = (Entity) currentCommand.parameterList.get(p++).object;
	//int tx = currentCommand.parameterList.get(p++).i;
	//int ty = currentCommand.parameterList.get(p++).i;
	//TODO

	getNextCommand();
}

void Event::playerBlockUntilReachesArea_AREA()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);
	if (getPlayer()->isAreaBoundaryTouchingMyHitBox(a))
	{
		getNextCommand();
	}
}

void Event::playerBlockUntilReachesEntity_ENTITY()
{ //===============================================================================================
	int p = 0;
	//Entity a = (Entity) currentCommand.parameterList.get(p++).object;
	Entity* b = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	if (getPlayer()->isEntityHitBoxTouchingMyHitBox(b))
	{
		getNextCommand();
	}
}

void Event::playerBlockUntilReachesDoor_DOOR()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	Door* d = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);

	if (getPlayer()->isEntityHitBoxTouchingMyHitBox(d))
	{
		getNextCommand();
	}
}

void Event::playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X()
{ //===============================================================================================
	int p = 0;
	//Entity a = (Entity) currentCommand.parameterList.get(p++).object;
	int tx = currentCommand->parameterList->get(p++)->i;
	int ty = currentCommand->parameterList->get(p++)->i;

	if (getPlayer()->isXYTouchingMyHitBox((float)tx * 8 * 2, (float)ty * 8 * 2))
	{
		getNextCommand();
	}
}

void Event::playerWalkToAreaAndBlockUntilThere_AREA()
{ //===============================================================================================
	int p = 0;
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object); //TODO need to rework behavior, eventBehavior, currentTargetTYPEID, thereYet, walking functions, etc.

	//walk to area, use pathfinding always
	int there = getPlayer()->walkToXYWithPathFinding(a->middleX(), a->middleY());
	if (there == -1)
	{
		if (getPlayer()->walkToXYNoCheckHit(a->middleX(), a->middleY()))
		{
			there = 1;
		}
	}

	//block until touch area
	if (getPlayer()->isAreaBoundaryTouchingMyHitBox(a))
	{
		//wait 500 ticks to walk to center of area
		ticksCounter += getEngine()->realWorldTicksPassed();

		if (ticksCounter >= 500)
		{
			//continue
			ticksCounter = 0;
			getNextCommand();
		}
	}
}

void Event::playerWalkToEntityAndBlockUntilThere_ENTITY()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	Entity* a = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	//walk to area, use pathfinding always
	int there = getPlayer()->walkToXYWithPathFinding(a->getMiddleX(), a->getMiddleY());
	if (there == -1)
	{
		if (getPlayer()->walkToXYNoCheckHit(a->getMiddleX(), a->getMiddleY()))
		{
			there = 1;
		}
	}

	//block until touch area
	if (getPlayer()->isEntityHitBoxTouchingMyHitBox(a))
	{
		//wait 500 ticks to walk to center of area
		ticksCounter += getEngine()->realWorldTicksPassed();

		if (ticksCounter >= 500)
		{
			//continue
			ticksCounter = 0;
			getNextCommand();
		}
	}
}

void Event::playerWalkToDoorAndBlockUntilThere_DOOR()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	Door* a = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);

	//walk to area, use pathfinding always
	int there = getPlayer()->walkToXYWithPathFinding(a->getMiddleX(), a->getMiddleY());
	if (there == -1)
	{
		if (getPlayer()->walkToXYNoCheckHit(a->getMiddleX(), a->getMiddleY()))
		{
			there = 1;
		}
	}

	//block until touch area
	if (getPlayer()->isEntityHitBoxTouchingMyHitBox(a))
	{
		//wait 500 ticks to walk to center of area
		ticksCounter += getEngine()->realWorldTicksPassed();

		if (ticksCounter >= 500)
		{
			//continue
			ticksCounter = 0;
			getNextCommand();
		}
	}
}

void Event::playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X()
{ //===============================================================================================
	int p = 0;
	//Entity a = (Entity) currentCommand.parameterList.get(p++).object;
	int tx = currentCommand->parameterList->get(p++)->i;
	int ty = currentCommand->parameterList->get(p++)->i;

	//TODO can use -1 to just walk in direction, etc

	int x = tx * 8 * 2;
	int y = ty * 8 * 2;


	//walk to area, use pathfinding always
	int there = getPlayer()->walkToXYWithPathFinding((float)x, (float)y);
	if (there == -1)
	{
		if (getPlayer()->walkToXYNoCheckHit((float)x, (float)y))
		{
			there = 1;
		}
	}

	//block until touch area
	if (getPlayer()->isXYTouchingMyHitBox((float)x, (float)y))
	{
		//wait 500 ticks to walk to center of area
		ticksCounter += getEngine()->realWorldTicksPassed();

		if (ticksCounter >= 500)
		{
			//continue
			ticksCounter = 0;
			getNextCommand();
		}
	}
}

void Event::playerStandAndShuffle()
{ //===============================================================================================
	//int p=0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;

	getPlayer()->addEventBehavior("StandAndShuffle"); //TODO

	getNextCommand();
}

void Event::playerStandAndShuffleAndFaceEntity_ENTITY()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	Entity* e2 = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	getPlayer()->addEventBehavior(string("StandAndShuffleAndFace:ENTITY.") + to_string(e2->getID())); //TODO:

	getNextCommand();
}

void Event::playerSetFaceMovementDirection_STRINGdirection()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	//int dir = currentCommand.parameterList.get(p++).i;
	//((Character)e).setAnimationByDirection(dir);
	//getNextCommand();


	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	GameString* gs = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	if (gs->getInitialized_S() == false)
	{
		return;
	}

	string dirString = gs->text();

	//dirString = toupper(dirString);
	string s = dirString;
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	dirString = s;

	int dir = -1;
	if (dirString == ("UP"))//.toUpperCase()->equals
	{
		dir = Entity::UP;
	}
	if (dirString == ("DOWN"))
	{
		dir = Entity::DOWN;
	}
	if (dirString == ("LEFT"))
	{
		dir = Entity::LEFT;
	}
	if (dirString == ("RIGHT"))
	{
		dir = Entity::RIGHT;
	}
	if (dirString == ("UPRIGHT"))
	{
		dir = Entity::UPRIGHT;
	}
	if (dirString == ("DOWNRIGHT"))
	{
		dir = Entity::DOWNRIGHT;
	}
	if (dirString == ("UPLEFT"))
	{
		dir = Entity::UPLEFT;
	}
	if (dirString == ("DOWNLEFT"))
	{
		dir = Entity::DOWNLEFT;
	}

	if (dir != -1)
	{
		getPlayer()->movementDirection = dir; //TODO this should be all i need for this to work but it doesn't

		getPlayer()->setCurrentAnimationByDirection(dir);
		getPlayer()->setFrameOffsetInCurrentAnimation(0);
		//getPlayer().doCharacterAnimation();
	}


	getNextCommand();
}

void Event::playerSetMovementSpeed_INTticksPerPixel()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	int speed = currentCommand->parameterList->get(p++)->i;

	getPlayer()->setTicksPerPixelMoved((float)speed);

	getNextCommand();
}

void Event::playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks()
{ //===============================================================================================
	int p = 0;

	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	GameString* gs = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);


	int ticksBetweenFrames = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenFrames = currentCommand->parameterList->get(p++)->b;


	if (getPlayer() != nullptr && getPlayer()->sprite != nullptr && gs != nullptr)
	{
		if (gs->getInitialized_S() == false)
		{
			return; //wait for object to receive server data in its update() function
		}
		if (getPlayer()->sprite->getInitialized_S() == false)
		{
			return;
		}

		getPlayer()->setCurrentAnimationByName(gs->text());

		getPlayer()->setAnimateOnceThroughCurrentAnimation();

		getPlayer()->setRandomFrames(false);

		getPlayer()->setTicksBetweenFrames(ticksBetweenFrames);
		getPlayer()->setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);


		getNextCommand();
	}
}

void Event::playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	GameString* gs = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	int ticksBetweenFrames = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenFrames = currentCommand->parameterList->get(p++)->b;
	int ticksBetweenLoop = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenLoop = currentCommand->parameterList->get(p++)->b;


	if (getPlayer() != nullptr && getPlayer()->sprite != nullptr && gs != nullptr)
	{
		if (gs->getInitialized_S() == false)
		{
			return; //wait for object to receive server data in its update() function
		}
		if (getPlayer()->sprite->getInitialized_S() == false)
		{
			return;
		}

		getPlayer()->setCurrentAnimationByName(gs->text());

		getPlayer()->setAnimateLoopThroughCurrentAnimation();

		getPlayer()->setRandomFrames(false);

		getPlayer()->setTicksBetweenFrames(ticksBetweenFrames);
		getPlayer()->setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);

		getPlayer()->setTicksBetweenAnimationLoop(ticksBetweenLoop);
		getPlayer()->setRandomUpToTicksBetweenAnimationLoop(randomUpToTicksBetweenLoop);

		getNextCommand();
	}
}

void Event::playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame()
{ //===============================================================================================
	int p = 0;

	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	GameString* gs = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	int ticksBetweenFrames = currentCommand->parameterList->get(p++)->i;


	if (getPlayer() != nullptr && getPlayer()->sprite != nullptr && gs != nullptr)
	{
		if (gs->getInitialized_S() == false)
		{
			return; //wait for object to receive server data in its update() function
		}
		if (getPlayer()->sprite->getInitialized_S() == false)
		{
			return;
		}

		getPlayer()->setCurrentAnimationByName(gs->text());

		getPlayer()->setAnimateOnceThroughCurrentAnimation();

		getPlayer()->setRandomFrames(false);
		getPlayer()->setTicksBetweenFrames(ticksBetweenFrames);

		getNextCommand();
	}
}

void Event::playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	GameString* gs = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	int ticksBetweenFrames = currentCommand->parameterList->get(p++)->i;

	if (getPlayer() != nullptr && getPlayer()->sprite != nullptr && gs != nullptr)
	{
		if (gs->getInitialized_S() == false)
		{
			return; //wait for object to receive server data in its update() function
		}
		if (getPlayer()->sprite->getInitialized_S() == false)
		{
			return;
		}

		getPlayer()->setCurrentAnimationByName(gs->text());

		getPlayer()->setAnimateLoopThroughCurrentAnimation();

		getPlayer()->setRandomFrames(false);
		getPlayer()->setTicksBetweenFrames(ticksBetweenFrames);
		getPlayer()->setTicksBetweenAnimationLoop(ticksBetweenFrames);

		getNextCommand();
	}
}

void Event::playerStopAnimating()
{ //===============================================================================================
	//int p=0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	getPlayer()->stopAnimation();

	getNextCommand();
}

void Event::playerSetGlobalAnimationDisabled_BOOL()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	bool b = currentCommand->parameterList->get(p++)->b;

	getPlayer()->setAnimationDisabled(b);

	getNextCommand();
}

void Event::playerSetToAlpha_FLOAT()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	float f = currentCommand->parameterList->get(p++)->f;

	getPlayer()->setToAlpha(f);

	getNextCommand();
}

void Event::entitySetBehaviorQueueOnOff_ENTITY_BOOL()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	bool b = currentCommand->parameterList->get(p++)->b;

	e->behaviorEnabled = b;

	getNextCommand();
}

void Event::entitySetToArea_ENTITY_AREA()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

	e->setFeetAtMapXY(a->middleX(), a->middleY());

	getNextCommand();
}

void Event::entitySetToDoor_ENTITY_DOOR()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	Door* a = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);

	e->setFeetAtMapXY((float)a->arrivalXPixelsHQ() + 8, (float)a->arrivalYPixelsHQ() + 8);

	getNextCommand();
}

void Event::entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	int tx = currentCommand->parameterList->get(p++)->i;
	int ty = currentCommand->parameterList->get(p++)->i;

	e->setFeetAtMapXY((float)tx * 2 * 8 + 8, (float)ty * 2 * 8 + 8);

	getNextCommand();
}

void Event::entityWalkToArea_ENTITY_AREA()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

	//TODO need behavior queue stuff working better.

	e->currentAreaTYPEIDTarget = a->getTYPEIDString();

	getNextCommand();
}

void Event::entityWalkToDoor_ENTITY_DOOR()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	Door* a = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);

	//TODO need behavior queue stuff working better.

	//TODO: use eventBehavior and eventCurrentTargetTYPEID list and all that.

	e->currentAreaTYPEIDTarget = a->getTYPEIDString();

	getNextCommand();
}

void Event::entityWalkToEntity_ENTITY_ENTITY()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	Entity* e2 = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	//TODO need behavior queue stuff working better.

	e->currentAreaTYPEIDTarget = e2->getTYPEIDString();

	getNextCommand();
}

void Event::entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X()
{ //===============================================================================================
	//int p=0;

	//Entity a = (Entity) currentCommand.parameterList.get(p++).object;
	//int tx = currentCommand.parameterList.get(p++).i;
	//int ty = currentCommand.parameterList.get(p++).i;
	//TODO

	getNextCommand();
}

void Event::entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);
	bool bWalkOrSlide = currentCommand->parameterList->get(p++)->b;
	bool bCheckHit = currentCommand->parameterList->get(p++)->b;
	bool bAvoidOthers = currentCommand->parameterList->get(p++)->b;
	bool bPushOthers = currentCommand->parameterList->get(p++)->b;
	bool bPathFind = currentCommand->parameterList->get(p++)->b;
	bool bAnimate = currentCommand->parameterList->get(p++)->b;
	bool bMoveDiagonally = currentCommand->parameterList->get(p++)->b;

	//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
	e->addEventBehavior(
		string("MoveToArea:") +
		to_string(a->getID()) + string(",") +
		string(StringConverterHelper::toString(bWalkOrSlide)) + string(",") +
		string(StringConverterHelper::toString(bCheckHit)) + string(",") +
		string(StringConverterHelper::toString(bAvoidOthers)) + string(",") +
		string(StringConverterHelper::toString(bPushOthers)) + string(",") +
		string(StringConverterHelper::toString(bPathFind)) + string(",") +
		string(StringConverterHelper::toString(bAnimate)) + string(",") +
		string(StringConverterHelper::toString(bMoveDiagonally))
	);

	getNextCommand();
}

void Event::entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal()
{ //===============================================================================================
	int p = 0;

	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	Door* e2 = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);
	bool bWalkOrSlide = currentCommand->parameterList->get(p++)->b;
	bool bCheckHit = currentCommand->parameterList->get(p++)->b;
	bool bAvoidOthers = currentCommand->parameterList->get(p++)->b;
	bool bPushOthers = currentCommand->parameterList->get(p++)->b;
	bool bPathFind = currentCommand->parameterList->get(p++)->b;
	bool bAnimate = currentCommand->parameterList->get(p++)->b;
	bool bMoveDiagonally = currentCommand->parameterList->get(p++)->b;

	//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
	e->addEventBehavior(
		string("MoveToDoor:") +
		to_string(e2->getID()) + string(",") +
		string(StringConverterHelper::toString(bWalkOrSlide)) + string(",") +
		string(StringConverterHelper::toString(bCheckHit)) + string(",") +
		string(StringConverterHelper::toString(bAvoidOthers)) + string(",") +
		string(StringConverterHelper::toString(bPushOthers)) + string(",") +
		string(StringConverterHelper::toString(bPathFind)) + string(",") +
		string(StringConverterHelper::toString(bAnimate)) + string(",") +
		string(StringConverterHelper::toString(bMoveDiagonally))
	);

	getNextCommand();
}

void Event::entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal()
{ //===============================================================================================
	int p = 0;

	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	Entity* e2 = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	bool bWalkOrSlide = currentCommand->parameterList->get(p++)->b;
	bool bCheckHit = currentCommand->parameterList->get(p++)->b;
	bool bAvoidOthers = currentCommand->parameterList->get(p++)->b;
	bool bPushOthers = currentCommand->parameterList->get(p++)->b;
	bool bPathFind = currentCommand->parameterList->get(p++)->b;
	bool bAnimate = currentCommand->parameterList->get(p++)->b;
	bool bMoveDiagonally = currentCommand->parameterList->get(p++)->b;

	//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
	e->addEventBehavior(
		string("MoveToEntity:") +
		to_string(e2->getID()) + string(",") +
		string(StringConverterHelper::toString(bWalkOrSlide)) + string(",") +
		string(StringConverterHelper::toString(bCheckHit)) + string(",") +
		string(StringConverterHelper::toString(bAvoidOthers)) + string(",") +
		string(StringConverterHelper::toString(bPushOthers)) + string(",") +
		string(StringConverterHelper::toString(bPathFind)) + string(",") +
		string(StringConverterHelper::toString(bAnimate)) + string(",") +
		string(StringConverterHelper::toString(bMoveDiagonally))
	);

	getNextCommand();
}

void Event::entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal()
{ //===============================================================================================
	int p = 0;

	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	int tX = currentCommand->parameterList->get(p++)->i;
	int tY = currentCommand->parameterList->get(p++)->i;
	bool bWalkOrSlide = currentCommand->parameterList->get(p++)->b;
	bool bCheckHit = currentCommand->parameterList->get(p++)->b;
	bool bAvoidOthers = currentCommand->parameterList->get(p++)->b;
	bool bPushOthers = currentCommand->parameterList->get(p++)->b;
	bool bPathFind = currentCommand->parameterList->get(p++)->b;
	bool bAnimate = currentCommand->parameterList->get(p++)->b;
	bool bMoveDiagonally = currentCommand->parameterList->get(p++)->b;

	//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
	e->addEventBehavior(
		string("MoveToMapXY:") +
		to_string(tX * 8 * 2) + string(",") +
		to_string(tY * 8 * 2) + string(",") +
		string(StringConverterHelper::toString(bWalkOrSlide)) + string(",") +
		string(StringConverterHelper::toString(bCheckHit)) + string(",") +
		string(StringConverterHelper::toString(bAvoidOthers)) + string(",") +
		string(StringConverterHelper::toString(bPushOthers)) + string(",") +
		string(StringConverterHelper::toString(bPathFind)) + string(",") +
		string(StringConverterHelper::toString(bAnimate)) + string(",") +
		string(StringConverterHelper::toString(bMoveDiagonally))
	);

	getNextCommand();
}

void Event::entityBlockUntilReachesArea_ENTITY_AREA()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);
	if (e->isAreaBoundaryTouchingMyHitBox(a))
	{
		getNextCommand();
	}
}

void Event::entityBlockUntilReachesEntity_ENTITY_ENTITY()
{ //===============================================================================================
	int p = 0;
	Entity* a = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	Entity* b = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	if (a->isEntityHitBoxTouchingMyHitBox(b))
	{
		getNextCommand();
	}
}

void Event::entityBlockUntilReachesDoor_ENTITY_DOOR()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	Door* d = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);

	if (e->isEntityHitBoxTouchingMyHitBox(d))
	{
		getNextCommand();
	}
}

void Event::entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X()
{ //===============================================================================================
	int p = 0;
	Entity* a = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	int tx = currentCommand->parameterList->get(p++)->i;
	int ty = currentCommand->parameterList->get(p++)->i;

	if (a->isXYTouchingMyHitBox((float)tx * 8 * 2, (float)ty * 8 * 2))
	{
		getNextCommand();
	}
}

void Event::entityWalkToAreaAndBlockUntilThere_ENTITY_AREA()
{ //===============================================================================================
	int p = 0;
	Character* e = static_cast<Character*>(currentCommand->parameterList->get(p++)->object);
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object); //TODO need to rework behavior, eventBehavior, currentTargetTYPEID, thereYet, walking functions, etc.

	//walk to area, use pathfinding always
	int there = e->walkToXYWithPathFinding(a->middleX(), a->middleY());
	if (there == -1)
	{
		if (e->walkToXYNoCheckHit(a->middleX(), a->middleY()))
		{
			there = 1;
		}
	}

	//block until touch area
	if (e->isAreaBoundaryTouchingMyHitBox(a))
	{
		//wait 500 ticks to walk to center of area
		ticksCounter += getEngine()->realWorldTicksPassed();

		if (ticksCounter >= 500)
		{
			//continue
			ticksCounter = 0;
			getNextCommand();
		}
	}
}

void Event::entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY()
{ //===============================================================================================
	int p = 0;
	Character* e = static_cast<Character*>(currentCommand->parameterList->get(p++)->object);
	Entity* a = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	//walk to area, use pathfinding always
	int there = e->walkToXYWithPathFinding(a->getMiddleX(), a->getMiddleY());
	if (there == -1)
	{
		if (e->walkToXYNoCheckHit(a->getMiddleX(), a->getMiddleY()))
		{
			there = 1;
		}
	}

	//block until touch area
	if (e->isEntityHitBoxTouchingMyHitBox(a))
	{
		//wait 500 ticks to walk to center of area
		ticksCounter += getEngine()->realWorldTicksPassed();

		if (ticksCounter >= 500)
		{
			//continue
			ticksCounter = 0;
			getNextCommand();
		}
	}
}

void Event::entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR()
{ //===============================================================================================
	int p = 0;
	Character* e = static_cast<Character*>(currentCommand->parameterList->get(p++)->object);
	Door* a = static_cast<Door*>(currentCommand->parameterList->get(p++)->object);

	//walk to area, use pathfinding always
	int there = e->walkToXYWithPathFinding(a->getMiddleX(), a->getMiddleY());
	if (there == -1)
	{
		if (e->walkToXYNoCheckHit(a->getMiddleX(), a->getMiddleY()))
		{
			there = 1;
		}
	}

	//block until touch area
	if (e->isEntityHitBoxTouchingMyHitBox(a))
	{
		//wait 500 ticks to walk to center of area
		ticksCounter += getEngine()->realWorldTicksPassed();

		if (ticksCounter >= 500)
		{
			//continue
			ticksCounter = 0;
			getNextCommand();
		}
	}
}

void Event::entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X()
{ //===============================================================================================
	int p = 0;
	Character* e = static_cast<Character*>(currentCommand->parameterList->get(p++)->object);
	int tx = currentCommand->parameterList->get(p++)->i;
	int ty = currentCommand->parameterList->get(p++)->i;

	//TODO can use -1 to just walk in direction, etc

	int x = tx * 8 * 2;
	int y = ty * 8 * 2;


	//walk to area, use pathfinding always
	int there = e->walkToXYWithPathFinding((float)x, (float)y);
	if (there == -1)
	{
		if (e->walkToXYNoCheckHit((float)x, (float)y))
		{
			there = 1;
		}
	}

	//block until touch area
	if (e->isXYTouchingMyHitBox((float)x, (float)y))
	{
		//wait 500 ticks to walk to center of area
		ticksCounter += getEngine()->realWorldTicksPassed();

		if (ticksCounter >= 500)
		{
			//continue
			ticksCounter = 0;
			getNextCommand();
		}
	}
}

void Event::entityStandAndShuffle_ENTITY()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	e->addEventBehavior("StandAndShuffle"); //TODO

	getNextCommand();
}

void Event::entityStandAndShuffleAndFacePlayer_ENTITY()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);


	e->addEventBehavior("StandAndShuffleAndFacePlayer"); //TODO:

	getNextCommand();
}

void Event::entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	Entity* e2 = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	e->addEventBehavior(string("StandAndShuffleAndFace:ENTITY.") + to_string(e2->getID())); //TODO:

	getNextCommand();
}

void Event::entitySetFaceMovementDirection_ENTITY_STRINGdirection()
{ //===============================================================================================
	int p = 0;
	//Entity e = (Entity) currentCommand.parameterList.get(p++).object;
	//int dir = currentCommand.parameterList.get(p++).i;
	//((Character)e).setAnimationByDirection(dir);
	//getNextCommand();


	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	GameString* gs = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	if (gs->getInitialized_S() == false)
	{
		return;
	}

	string dirString = gs->text();

	//dirString = toupper(dirString);
	string s = dirString;
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	dirString = s;

	int dir = -1;
	if (dirString == ("UP"))
	{
		dir = Entity::UP;
	}
	if (dirString == ("DOWN"))
	{
		dir = Entity::DOWN;
	}
	if (dirString == ("LEFT"))
	{
		dir = Entity::LEFT;
	}
	if (dirString == ("RIGHT"))
	{
		dir = Entity::RIGHT;
	}
	if (dirString == ("UPRIGHT"))
	{
		dir = Entity::UPRIGHT;
	}
	if (dirString == ("DOWNRIGHT"))
	{
		dir = Entity::DOWNRIGHT;
	}
	if (dirString == ("UPLEFT"))
	{
		dir = Entity::UPLEFT;
	}
	if (dirString == ("DOWNLEFT"))
	{
		dir = Entity::DOWNLEFT;
	}

	if (dir != -1)
	{
		e->movementDirection = dir;
	}

	getNextCommand();
}

void Event::entitySetMovementSpeed_ENTITY_INTticksPerPixel()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	int speed = currentCommand->parameterList->get(p++)->i;

	e->setTicksPerPixelMoved((float)speed);

	getNextCommand();
}

void Event::entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	int ticksPerFrame = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenFrames = currentCommand->parameterList->get(p++)->b;

	e->setAnimateLoopThroughAllFrames();
	e->setRandomFrames(true);
	e->setTicksBetweenFrames(ticksPerFrame);
	e->setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);

	//dont set ticks between loop here because there is no lop

	getNextCommand();
}

void Event::entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	int ticks = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenFrames = currentCommand->parameterList->get(p++)->b;


	e->setAnimateOnceThroughCurrentAnimation();

	e->setRandomFrames(false);
	e->setTicksBetweenFrames(ticks);
	e->setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);


	getNextCommand();
}

void Event::entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	int ticksBetweenFrames = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenFrames = currentCommand->parameterList->get(p++)->b;
	int ticksBetweenLoop = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenLoop = currentCommand->parameterList->get(p++)->b;


	e->setAnimateLoopThroughCurrentAnimation();

	e->setRandomFrames(false);
	e->setTicksBetweenFrames(ticksBetweenFrames);
	e->setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);

	e->setTicksBetweenAnimationLoop(ticksBetweenLoop);
	e->setRandomUpToTicksBetweenAnimationLoop(randomUpToTicksBetweenLoop);

	getNextCommand();
}

void Event::entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	int ticksBetweenFrames = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenFrames = currentCommand->parameterList->get(p++)->b;


	e->setAnimateOnceThroughAllFrames();

	e->setRandomFrames(false);

	e->setTicksBetweenFrames(ticksBetweenFrames);
	e->setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);


	getNextCommand();
}

void Event::entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	int ticksBetweenFrames = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenFrames = currentCommand->parameterList->get(p++)->b;
	int ticksBetweenLoop = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenLoop = currentCommand->parameterList->get(p++)->b;


	e->setAnimateLoopThroughAllFrames();

	e->setRandomFrames(false);

	e->setTicksBetweenFrames(ticksBetweenFrames);
	e->setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);

	e->setTicksBetweenAnimationLoop(ticksBetweenLoop);
	e->setRandomUpToTicksBetweenAnimationLoop(randomUpToTicksBetweenLoop);

	getNextCommand();
}

void Event::entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName()
{ //===============================================================================================
	int p = 0;

	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	GameString* gs = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);


	if (e != nullptr && e->sprite != nullptr && gs != nullptr)
	{
		if (gs->getInitialized_S() == false)
		{
			return; //wait for object to receive server data in its update() function
		}
		if (e->sprite->getInitialized_S() == false)
		{
			return;
		}

		e->setCurrentAnimationByName(gs->text());

		e->setFrameToCurrentAnimationStart();

		getNextCommand();
	}
}

void Event::entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame()
{ //===============================================================================================
	int p = 0;

	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	GameString* gs = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	int ticksBetweenFrames = currentCommand->parameterList->get(p++)->i;


	if (e != nullptr && e->sprite != nullptr && gs != nullptr)
	{
		if (gs->getInitialized_S() == false)
		{
			return; //wait for object to receive server data in its update() function
		}
		if (e->sprite->getInitialized_S() == false)
		{
			return;
		}

		e->setCurrentAnimationByName(gs->text());

		e->setAnimateOnceThroughCurrentAnimation();

		e->setRandomFrames(false);
		e->setTicksBetweenFrames(ticksBetweenFrames);

		getNextCommand();
	}
}

void Event::entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	GameString* gs = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	int ticksBetweenFrames = currentCommand->parameterList->get(p++)->i;

	if (e != nullptr && e->sprite != nullptr && gs != nullptr)
	{
		if (gs->getInitialized_S() == false)
		{
			return; //wait for object to receive server data in its update() function
		}
		if (e->sprite->getInitialized_S() == false)
		{
			return;
		}

		e->setCurrentAnimationByName(gs->text());

		e->setAnimateLoopThroughCurrentAnimation();

		e->setRandomFrames(false);
		e->setTicksBetweenFrames(ticksBetweenFrames);
		e->setTicksBetweenAnimationLoop(ticksBetweenFrames);

		getNextCommand();
	}
}

void Event::entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks()
{ //===============================================================================================
	int p = 0;

	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	GameString* gs = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);


	int ticksBetweenFrames = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenFrames = currentCommand->parameterList->get(p++)->b;


	if (e != nullptr && e->sprite != nullptr && gs != nullptr)
	{
		if (gs->getInitialized_S() == false)
		{
			return; //wait for object to receive server data in its update() function
		}
		if (e->sprite->getInitialized_S() == false)
		{
			return;
		}

		e->setCurrentAnimationByName(gs->text());

		e->setAnimateOnceThroughCurrentAnimation();

		e->setRandomFrames(false);

		e->setTicksBetweenFrames(ticksBetweenFrames);
		e->setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);


		getNextCommand();
	}
}

void Event::entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	GameString* gs = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	int ticksBetweenFrames = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenFrames = currentCommand->parameterList->get(p++)->b;
	int ticksBetweenLoop = currentCommand->parameterList->get(p++)->i;
	bool randomUpToTicksBetweenLoop = currentCommand->parameterList->get(p++)->b;


	if (e != nullptr && e->sprite != nullptr && gs != nullptr)
	{
		if (gs->getInitialized_S() == false)
		{
			return; //wait for object to receive server data in its update() function
		}
		if (e->sprite->getInitialized_S() == false)
		{
			return;
		}

		e->setCurrentAnimationByName(gs->text());

		e->setAnimateLoopThroughCurrentAnimation();

		e->setRandomFrames(false);

		e->setTicksBetweenFrames(ticksBetweenFrames);
		e->setRandomUpToTicksBetweenFrames(randomUpToTicksBetweenFrames);

		e->setTicksBetweenAnimationLoop(ticksBetweenLoop);
		e->setRandomUpToTicksBetweenAnimationLoop(randomUpToTicksBetweenLoop);

		getNextCommand();
	}
}

void Event::entityStopAnimating_ENTITY()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	e->stopAnimation();

	getNextCommand();
}

void Event::entitySetGlobalAnimationDisabled_ENTITY_BOOL()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	bool b = currentCommand->parameterList->get(p++)->b;

	e->setAnimationDisabled(b);

	getNextCommand();
}

void Event::entitySetNonWalkable_ENTITY_BOOL()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	bool b = currentCommand->parameterList->get(p++)->b;

	e->setNonWalkable(b);

	getNextCommand();
}

void Event::entitySetPushable_ENTITY_BOOL()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	bool b = currentCommand->parameterList->get(p++)->b;

	e->setPushable(b);

	getNextCommand();
}

void Event::entityFadeOutDelete_ENTITY()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	e->fadeOutAndDelete();

	getNextCommand();
}

void Event::entityDeleteInstantly_ENTITY()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	e->deleteFromMapEntityListAndReleaseTexture();
	delete e;
	e = nullptr;

	getNextCommand();
}

void Event::entitySetToAlpha_ENTITY_FLOAT()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	float f = currentCommand->parameterList->get(p++)->f;

	e->setToAlpha(f);

	getNextCommand();
}

void Event::spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA()
{ //===============================================================================================
	int p = 0;
	Sprite* sprite = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);
	GameString* gameString = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

	// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
	if (sprite == nullptr)
	{
		return; //block until sprite has loaded.
	}

	if (gameString->getInitialized_S() == false)
	{
		//wait for object to receive server data in its update() function
	}
	else
	{
		Entity* m = getMap()->createEntityAtArea(getMap(), gameString->text(), sprite, a);

		m->setAlphaImmediately(1.0f);

		getNextCommand();
	}
}

void Event::spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA()
{ //===============================================================================================
	int p = 0;
	Sprite* sprite = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);
	GameString* gameString = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

	// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
	if (sprite == nullptr)
	{
		return; //block until sprite has loaded.
	}

	if (gameString->getInitialized_S() == false)
	{
		//wait for object to receive server data in its update() function
	}
	else
	{
		getMap()->createEntityAtArea(getMap(), gameString->text(), sprite, a);


		getNextCommand();
	}
}

void Event::spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA()
{ //===============================================================================================
	int p = 0;
	Sprite* sprite = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);
	GameString* gameString = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

	// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
	if (sprite == nullptr)
	{
		return; //block until sprite has loaded.
	}

	if (gameString->getInitialized_S() == false)
	{
		//wait for object to receive server data in its update() function
	}
	else
	{
		Character* character = new Character(getEngine(), gameString->text(), sprite, a);

		character->setAlphaImmediately(1.0f);

		getNextCommand();
	}
}

void Event::spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA()
{ //===============================================================================================
	int p = 0;
	Sprite* sprite = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);
	GameString* gameString = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);


	// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
	if (sprite == nullptr)
	{
		return; //block until sprite has loaded.
	}

	if (gameString->getInitialized_S() == false)
	{
		//wait for object to receive server data in its update() function
	}
	else
	{
		new Character(getEngine(), gameString->text(), sprite, a);

		getNextCommand();
	}
}

void Event::createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy()
{ //===============================================================================================
	int p = 0;

	Sprite* s = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);
	float screenX = currentCommand->parameterList->get(p++)->f;
	float screenY = currentCommand->parameterList->get(p++)->f;


	// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
	if (s == nullptr)
	{
		return; //block until sprite has loaded.
	}

	ScreenSprite* screenSprite = new ScreenSprite(getEngine(), string("SCREENSPRITE.") + s->getName(), s->getName());

	screenSprite->useXPercent = true;
	screenSprite->useYPercent = true;

	screenSprite->screenXPercent = screenX;
	screenSprite->screenYPercent = screenY;

	if (screenX == -1)
	{
		screenSprite->centerX = true;
	}
	if (screenY == -1)
	{
		screenSprite->centerY = true;
	}

	screenSprite->setRenderOrder(RenderOrder::ABOVE_TOP);


	getNextCommand();
}

void Event::createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy()
{ //===============================================================================================
	int p = 0;

	Sprite* s = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);
	float screenX = currentCommand->parameterList->get(p++)->f;
	float screenY = currentCommand->parameterList->get(p++)->f;


	//no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
	if (s == nullptr)
	{
		return; //block until sprite has loaded.
	}

	ScreenSprite* screenSprite = new ScreenSprite(getEngine(), string("SCREENSPRITE.") + s->getName(), s->getName());

	screenSprite->useXPercent = true;
	screenSprite->useYPercent = true;

	screenSprite->screenXPercent = screenX;
	screenSprite->screenYPercent = screenY;

	if (screenX == -1)
	{
		screenSprite->centerX = true;
	}
	if (screenY == -1)
	{
		screenSprite->centerY = true;
	}

	getNextCommand();
}

void Event::createScreenSpriteUnderText_SPRITE_INTx_INTy()
{ //===============================================================================================
	int p = 0;

	Sprite* s = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);
	int screenX = currentCommand->parameterList->get(p++)->i;
	int screenY = currentCommand->parameterList->get(p++)->i;


	// no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
	if (s == nullptr)
	{
		return; //block until sprite has loaded.
	}

	ScreenSprite* screenSprite = new ScreenSprite(getEngine(), string("SCREENSPRITE.") + s->getName(), s->getName());
	screenSprite->screenXPixelsHQ = (float)screenX;
	screenSprite->screenYPixelsHQ = (float)screenY;

	if (screenX == -1)
	{
		screenSprite->centerX = true;
	}
	if (screenY == -1)
	{
		screenSprite->centerY = true;
	}

	screenSprite->setRenderOrder(RenderOrder::ABOVE_TOP);


	getNextCommand();
}

void Event::createScreenSpriteOverText_SPRITE_INTx_INTy()
{ //===============================================================================================
	int p = 0;

	//DONE: should make the screen coords floats, for percentage of screen. 0.80% x, etc.
	//also an options for centerx and centery

	Sprite* s = static_cast<Sprite*>(currentCommand->parameterList->get(p++)->object);
	int screenX = currentCommand->parameterList->get(p++)->i;
	int screenY = currentCommand->parameterList->get(p++)->i;


	//no spriteAsset here, use spriteAssetName or block until spriteAsset is loaded.
	if (s == nullptr)
	{
		return; //block until sprite has loaded.
	}

	ScreenSprite* screenSprite = new ScreenSprite(getEngine(), string("SCREENSPRITE.") + s->getName(), s->getName());
	screenSprite->screenXPixelsHQ = (float)screenX;
	screenSprite->screenYPixelsHQ = (float)screenY;

	if (screenX == -1)
	{
		screenSprite->centerX = true;
	}
	if (screenY == -1)
	{
		screenSprite->centerY = true;
	}

	getNextCommand();
}

void Event::setCameraTarget_AREA()
{ //===============================================================================================
	int p = 0;
	Area* o = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

	getCameraman()->setTarget(o);

	getNextCommand();
}

void Event::setCameraTarget_ENTITY()
{ //===============================================================================================
	int p = 0;
	Entity* o = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	getCameraman()->setTarget(o);

	getNextCommand();
}

void Event::setCameraNoTarget()
{ //===============================================================================================
	//int p=0;
	getCameraman()->setDummyTarget();

	getNextCommand();
}

void Event::setCameraIgnoreBounds_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getCameraman()->ignoreCameraFXBoundaries = b;
	getNextCommand();
}

void Event::setCameraTargetToPlayer()
{ //===============================================================================================
	//int p=0;
	getCameraman()->setTarget(getPlayer());

	getNextCommand();
}

void Event::blockUntilCameraReaches_AREA()
{ //===============================================================================================
	int p = 0;
	Area* o = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

	if (o->isWithinScreenBounds())
	{
		getNextCommand();
	}
}

void Event::blockUntilCameraReaches_ENTITY()
{ //===============================================================================================
	int p = 0;
	Entity* o = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);

	if (o->isWithinScreenBounds())
	{
		getNextCommand();
	}
}

void Event::blockUntilCameraReachesPlayer()
{ //===============================================================================================
	//int p=0;
	//Entity o = (Entity)currentCommand.parameterList.get(p++).object;

	if (getPlayer()->isWithinScreenBounds())
	{
		getNextCommand();
	}
}

void Event::pushCameraState()
{ //===============================================================================================
	//int p=0;
	//Kryo kryo = new Kryo();//TODO:

	//getEngine()->cameramanStack.push(kryo.copy(getEngine()->cameraman));

	getNextCommand();
}

void Event::popCameraState()
{ //===============================================================================================
	//int p=0;
	//TODO
	//getEngine()->cameraman = getEngine()->cameramanStack->pop();
	getNextCommand();
}

void Event::setKeyboardCameraZoom_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getCameraman()->setPlayerCanZoomManuallyWithKeyboard(b);
	getNextCommand();
}

void Event::enableKeyboardCameraZoom()
{ //===============================================================================================
	//int p=0;
	//boolean b = currentCommand.parameterList.get(p++).b;
	getCameraman()->setPlayerCanZoomManuallyWithKeyboard(true);
	getNextCommand();
}

void Event::disableKeyboardCameraZoom()
{ //===============================================================================================
	//int p=0;
	//boolean b = currentCommand.parameterList.get(p++).b;
	getCameraman()->setPlayerCanZoomManuallyWithKeyboard(false);
	getNextCommand();
}

void Event::setCameraAutoZoomByPlayerMovement_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getCameraman()->setAutoZoomByPlayerMovement(b);

	getNextCommand();
}

void Event::enableCameraAutoZoomByPlayerMovement()
{ //===============================================================================================
	//int p=0;
	//boolean b = currentCommand.parameterList.get(p++).b;
	getCameraman()->setAutoZoomByPlayerMovement(true);

	getNextCommand();
}

void Event::disableCameraAutoZoomByPlayerMovement()
{ //===============================================================================================
	//int p=0;
	//boolean b = currentCommand.parameterList.get(p++).b;
	getCameraman()->setAutoZoomByPlayerMovement(false);

	getNextCommand();
}

void Event::setCameraZoom_FLOAT()
{ //===============================================================================================
	int p = 0;

	float f = currentCommand->parameterList->get(p++)->f;
	getCameraman()->ZOOMto = (f);

	getNextCommand();
}

void Event::setCameraSpeed_FLOAT()
{ //===============================================================================================
	int p = 0;
	float f = currentCommand->parameterList->get(p++)->f;

	getCameraman()->speedMultiplier = f;

	getNextCommand();
}

void Event::giveItem_ITEM()
{ //===============================================================================================
	int p = 0;

	Item* i = static_cast<Item*>(currentCommand->parameterList->get(p++)->object);

	//TODO:ask the server if we can do this

	//confirm this action with the server
	i->getWithCaption_S();

	getNextCommand();
}

void Event::takeItem_ITEM()
{ //===============================================================================================
	int p = 0;

	Item* i = static_cast<Item*>(currentCommand->parameterList->get(p++)->object);

	//confirm this action with the server
	i->setHaveItemValue_S(false);


	getNextCommand();
}

void Event::giveGame_GAME()
{ //===============================================================================================
	int p = 0;

	Item* i = static_cast<Item*>(currentCommand->parameterList->get(p++)->object);

	//TODO:ask the server if we can do this

	//confirm this action with the server
	i->getWithCaption_S();

	getNextCommand();
}

void Event::takeMoney_FLOAT()
{ //===============================================================================================
	//int p=0;

	//confirm this action with the server

	// TODO

	getNextCommand();
}

void Event::giveMoney_FLOAT()
{ //===============================================================================================
	//int p=0;

	//TODO: maybe only server can perform this command.
	//every money request should be performed on the server after activating a certain flag.
	//so each money you get should have a name.

	//ask the server if we can do this

	//confirm this action with the server


	// TODO


	getNextCommand();
}

void Event::playSound_SOUND()
{ //===============================================================================================
	int p = 0;
	Sound* s = static_cast<Sound*>(currentCommand->parameterList->get(p++)->object);

	getAudioManager()->playSound(s);
	getNextCommand();
}

void Event::playSound_SOUND_FLOATvol()
{ //===============================================================================================
	int p = 0;
	Sound* s = static_cast<Sound*>(currentCommand->parameterList->get(p++)->object);
	float vol = currentCommand->parameterList->get(p++)->f;

	getAudioManager()->playSound(s, vol);
	getNextCommand();
}

void Event::playSound_SOUND_FLOATvol_FLOATpitch_INTtimes()
{ //===============================================================================================
	int p = 0;
	Sound* s = static_cast<Sound*>(currentCommand->parameterList->get(p++)->object);
	float vol = currentCommand->parameterList->get(p++)->f;
	float pitch = currentCommand->parameterList->get(p++)->f;
	int times = currentCommand->parameterList->get(p++)->i;

	getAudioManager()->playSound(s, vol, pitch, times);
	getNextCommand();
}

void Event::playMusicOnce_MUSIC()
{ //===============================================================================================
	int p = 0;
	Music* m = static_cast<Music*>(currentCommand->parameterList->get(p++)->object);

	getAudioManager()->playMusic(m, 1.0f, 1.0f, false);
	getNextCommand();
}

void Event::playMusicLoop_MUSIC()
{ //===============================================================================================
	int p = 0;
	Music* m = static_cast<Music*>(currentCommand->parameterList->get(p++)->object);

	getAudioManager()->playMusic(m, 1.0f, 1.0f, true);
	getNextCommand();
}

void Event::playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop()
{ //===============================================================================================
	int p = 0;
	Music* m = static_cast<Music*>(currentCommand->parameterList->get(p++)->object);
	float vol = currentCommand->parameterList->get(p++)->f;
	float pitch = currentCommand->parameterList->get(p++)->f;
	bool loop = currentCommand->parameterList->get(p++)->b;

	getAudioManager()->playMusic(m, vol, pitch, loop);
	getNextCommand();
}

void Event::stopMusic_MUSIC()
{ //===============================================================================================
	int p = 0;
	Music* m = static_cast<Music*>(currentCommand->parameterList->get(p++)->object);

	getAudioManager()->stopMusic(m);

	getNextCommand();
}

void Event::stopAllMusic()
{ //===============================================================================================
	//int p=0;
	getAudioManager()->stopAllMusic();

	getNextCommand();
}

void Event::blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC()
{ //===============================================================================================
	int p = 0;
	Music* currentPlaying = static_cast<Music*>(currentCommand->parameterList->get(p++)->object);
	Music* replaceWith = static_cast<Music*>(currentCommand->parameterList->get(p++)->object);

	if (currentPlaying->getLoop() == true)
	{
		currentPlaying->setLoop(false);
	}

	replaceWith->loadDataIntoChannel();

	if (currentPlaying->isPlaying() == false)
	{
		getAudioManager()->playMusic(replaceWith, currentPlaying->getVolume(), currentPlaying->getPitch(), true);

		getNextCommand();
	}
}

void Event::blockUntilMusicDone_MUSIC()
{ //===============================================================================================
	int p = 0;

	Music* m = static_cast<Music*>(currentCommand->parameterList->get(p++)->object);

	//if music is LOOPING this will always block
	if (m != nullptr)
	{
		if (m->getLoop() && m->isFadingOut() == false)
		{
			m->setLoop(false);
		}
	}

	if (m->isPlaying() == false)
	{
		getNextCommand();
	}
}

void Event::blockUntilAllMusicDone()
{ //===============================================================================================
	//int p=0;


	//if music is LOOPING this will always block
	getAudioManager()->setAllLoopingMusicThatIsNotFadingOutToNotLoop();

	if (getAudioManager()->isAnyMusicPlaying() == false)
	{
		getNextCommand();
	}
}

void Event::fadeOutMusic_MUSIC_INT()
{ //===============================================================================================
	int p = 0;

	Music* m = static_cast<Music*>(currentCommand->parameterList->get(p++)->object);
	int ticks = currentCommand->parameterList->get(p++)->i;

	getAudioManager()->fadeOutMusic(m, ticks);

	getNextCommand();
}

void Event::fadeOutAllMusic_INT()
{ //===============================================================================================
	int p = 0;

	int ticks = currentCommand->parameterList->get(p++)->i;

	getAudioManager()->fadeOutAllMusic(ticks);

	getNextCommand();
}

void Event::shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake()
{ //===============================================================================================
	int p = 0;
	int ticks = currentCommand->parameterList->get(p++)->i;
	int maxX = currentCommand->parameterList->get(p++)->i;
	int maxY = currentCommand->parameterList->get(p++)->i;
	int ticksPerShake = currentCommand->parameterList->get(p++)->i;

	getCinematicsManager()->shakeScreenForTicksDurationEaseInAndOutToMaxAmountWithEasingBetweenShakes(ticks, maxX, maxY, ticksPerShake);

	getNextCommand();
}

void Event::fadeToBlack_INTticks()
{ //===============================================================================================
	int p = 0;
	int ticks = currentCommand->parameterList->get(p++)->i;
	getCinematicsManager()->fadeToBlack(ticks);

	getNextCommand();
}

void Event::fadeFromBlack_INTticks()
{ //===============================================================================================
	int p = 0;
	int ticks = currentCommand->parameterList->get(p++)->i;
	getCinematicsManager()->fadeFromBlack(ticks);

	getNextCommand();
}

void Event::fadeToWhite_INTticks()
{ //===============================================================================================
	int p = 0;
	int ticks = currentCommand->parameterList->get(p++)->i;
	getCinematicsManager()->fadeToWhite(ticks);

	getNextCommand();
}

void Event::fadeFromWhite_INTticks()
{ //===============================================================================================
	int p = 0;
	int ticks = currentCommand->parameterList->get(p++)->i;
	getCinematicsManager()->fadeFromWhite(ticks);

	getNextCommand();
}

void Event::fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha()
{ //===============================================================================================
	int p = 0;
	int ticks = currentCommand->parameterList->get(p++)->i;
	int ri = currentCommand->parameterList->get(p++)->i;
	int gi = currentCommand->parameterList->get(p++)->i;
	int bi = currentCommand->parameterList->get(p++)->i;
	float toAlpha = currentCommand->parameterList->get(p++)->f;

	getCinematicsManager()->fadeColorFromCurrentAlphaToAlpha(ticks, ri, gi, bi, toAlpha);

	getNextCommand();
}

void Event::fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha()
{ //===============================================================================================
	int p = 0;
	int ticks = currentCommand->parameterList->get(p++)->i;
	int ri = currentCommand->parameterList->get(p++)->i;
	int gi = currentCommand->parameterList->get(p++)->i;
	int bi = currentCommand->parameterList->get(p++)->i;
	float fromAlpha = currentCommand->parameterList->get(p++)->f;
	float toAlpha = currentCommand->parameterList->get(p++)->f;

	getCinematicsManager()->fadeColorFromAlphaToAlpha(ticks, ri, gi, bi, fromAlpha, toAlpha);

	getNextCommand();
}

void Event::fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha()
{ //===============================================================================================
	int p = 0;
	int ticks = currentCommand->parameterList->get(p++)->i;
	int ri = currentCommand->parameterList->get(p++)->i;
	int gi = currentCommand->parameterList->get(p++)->i;
	int bi = currentCommand->parameterList->get(p++)->i;
	float toAlpha = currentCommand->parameterList->get(p++)->f;

	getCinematicsManager()->fadeColorFromTransparentToAlphaBackToTransparent(ticks, ri, gi, bi, toAlpha);

	getNextCommand();
}

void Event::setInstantOverlay_INTr_INTg_INTb_FLOATa()
{ //===============================================================================================
	int p = 0;
	int ri = currentCommand->parameterList->get(p++)->i;
	int gi = currentCommand->parameterList->get(p++)->i;
	int bi = currentCommand->parameterList->get(p++)->i;
	float a = currentCommand->parameterList->get(p++)->f;


	getCinematicsManager()->setInstantOverlayColor(ri, gi, bi, a);

	getNextCommand();
}

void Event::clearOverlay()
{ //===============================================================================================
	//int p=0;


	getCinematicsManager()->clearOverlay();

	getNextCommand();
}

void Event::fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha()
{ //===============================================================================================
	int p = 0;
	int ticks = currentCommand->parameterList->get(p++)->i;
	int ri = currentCommand->parameterList->get(p++)->i;
	int gi = currentCommand->parameterList->get(p++)->i;
	int bi = currentCommand->parameterList->get(p++)->i;
	float toAlpha = currentCommand->parameterList->get(p++)->f;

	getCinematicsManager()->fadeColorFromCurrentAlphaToAlphaUnderLights(ticks, ri, gi, bi, toAlpha);

	getNextCommand();
}

void Event::setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa()
{ //===============================================================================================
	int p = 0;
	int ri = currentCommand->parameterList->get(p++)->i;
	int gi = currentCommand->parameterList->get(p++)->i;
	int bi = currentCommand->parameterList->get(p++)->i;
	float a = currentCommand->parameterList->get(p++)->f;


	getCinematicsManager()->setInstantOverlayColorUnderLights(ri, gi, bi, a);

	getNextCommand();
}

void Event::clearOverlayUnderLights()
{ //===============================================================================================
	//int p=0;


	getCinematicsManager()->clearOverlayUnderLights();

	getNextCommand();
}

void Event::fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha()
{ //===============================================================================================
	int p = 0;
	int ticks = currentCommand->parameterList->get(p++)->i;
	int ri = currentCommand->parameterList->get(p++)->i;
	int gi = currentCommand->parameterList->get(p++)->i;
	int bi = currentCommand->parameterList->get(p++)->i;
	float toAlpha = currentCommand->parameterList->get(p++)->f;

	getCinematicsManager()->fadeColorFromCurrentAlphaToAlphaGroundLayer(ticks, ri, gi, bi, toAlpha);

	getNextCommand();
}

void Event::setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa()
{ //===============================================================================================
	int p = 0;
	int ri = currentCommand->parameterList->get(p++)->i;
	int gi = currentCommand->parameterList->get(p++)->i;
	int bi = currentCommand->parameterList->get(p++)->i;
	float a = currentCommand->parameterList->get(p++)->f;


	getCinematicsManager()->setInstantOverlayColorGroundLayer(ri, gi, bi, a);

	getNextCommand();
}

void Event::clearOverlayGroundLayer()
{ //===============================================================================================
	//int p=0;


	getCinematicsManager()->clearOverlayGroundLayer();

	getNextCommand();
}

void Event::setLetterbox_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;

	getCinematicsManager()->setLetterbox(b, 1000, 0.25f);

	getNextCommand();
}

void Event::setLetterbox_BOOL_INTticks()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	int slideDurationTicks = currentCommand->parameterList->get(p++)->i;


	getCinematicsManager()->setLetterbox(b, slideDurationTicks, 0.25f);

	getNextCommand();
}

void Event::setLetterbox_BOOL_INTticks_INTsize()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	int slideDurationTicks = currentCommand->parameterList->get(p++)->i;
	int sizeY = currentCommand->parameterList->get(p++)->i;

	getCinematicsManager()->setLetterbox(b, slideDurationTicks, sizeY);

	getNextCommand();
}

void Event::setLetterbox_BOOL_INTticks_FLOATsize()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	int slideDurationTicks = currentCommand->parameterList->get(p++)->i;
	float sizePercent = currentCommand->parameterList->get(p++)->f;


	getCinematicsManager()->setLetterbox(b, slideDurationTicks, sizePercent);

	getNextCommand();
}

void Event::setBlur_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getCinematicsManager()->setBlur(b);
	getNextCommand();
}

void Event::setMosaic_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getCinematicsManager()->setMosaic(b);
	getNextCommand();
}

void Event::setHBlankWave_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getCinematicsManager()->setHBlankWave(b);
	getNextCommand();
}

void Event::setRotate_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getCinematicsManager()->setRotate(b);
	getNextCommand();
}

void Event::setBlackAndWhite_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getCinematicsManager()->setBlackAndWhite(b);
	getNextCommand();
}

void Event::setInvertedColors_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getCinematicsManager()->setInvertedColors(b);
	getNextCommand();
}

void Event::set8BitMode_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getCinematicsManager()->set8BitMode(b);
	getNextCommand();
}

void Event::setEngineSpeed_FLOAT()
{ //===============================================================================================
	int p = 0;

	float f = currentCommand->parameterList->get(p++)->f;
	getEngine()->setEngineSpeed(f);

	getNextCommand();
}

void Event::toggleLightOnOff_LIGHT()
{ //===============================================================================================
	int p = 0;

	Light* l = static_cast<Light*>(currentCommand->parameterList->get(p++)->object);

	l->toggle();

	getNextCommand();
}

void Event::setLightOnOff_LIGHT_BOOL()
{ //===============================================================================================
	int p = 0;
	Light* l = static_cast<Light*>(currentCommand->parameterList->get(p++)->object);
	bool b = currentCommand->parameterList->get(p++)->b;

	l->setOnOff(b);

	getNextCommand();
}

void Event::setLightFlicker_LIGHT_BOOL()
{ //===============================================================================================
	int p = 0;
	Light* l = static_cast<Light*>(currentCommand->parameterList->get(p++)->object);
	bool b = currentCommand->parameterList->get(p++)->b;

	l->setFlicker(b);

	getNextCommand();
}

void Event::toggleAllLightsOnOff()
{ //===============================================================================================
	//int p=0;

	for (int i = 0; i < (int)getMap()->currentState->lightList.size(); i++)
	{
		getMap()->currentState->lightList.get(i)->toggle();
	}

	getNextCommand();
}

void Event::setAllLightsOnOff_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;

	for (int i = 0; i < (int)getMap()->currentState->lightList.size(); i++)
	{
		getMap()->currentState->lightList.get(i)->setOnOff(b);
	}

	getNextCommand();
}

void Event::setRandomSpawn_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;


	getMap()->randomSpawnEnabled = b;

	getNextCommand();
}

void Event::deleteRandoms()
{ //===============================================================================================
	//int p=0;

	for (int i = 0; i < (int)getMap()->activeEntityList.size(); i++)
	{
		Entity* e = getMap()->activeEntityList.get(i);

		if ((dynamic_cast<RandomCharacter*>(e) != NULL))
		{
			e->fadeOutAndDelete();
		}
	}

	getNextCommand();
}

void Event::makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb()
{ //===============================================================================================
	int p = 0;
	GameString* s = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	int sec = currentCommand->parameterList->get(p++)->i;
	int x = currentCommand->parameterList->get(p++)->i;
	int y = currentCommand->parameterList->get(p++)->i;
	int r = currentCommand->parameterList->get(p++)->i;
	int g = currentCommand->parameterList->get(p++)->i;
	int b = currentCommand->parameterList->get(p++)->i;


	if (s->getInitialized_S() == false)
	{
		return; //wait for object to receive server data in its update() function
	}
	else
	{
		getCaptionManager()->newManagedCaption(x, y, sec * 1000, s->text(), BobFont::font_small_16_outlined_smooth, new BobColor(r, g, b), nullptr, BobColor::clear, RenderOrder::ABOVE_TOP, 1.0f, 0);
		getNextCommand();
	}
}

void Event::makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb()
{ //===============================================================================================
	int p = 0;
	GameString* s = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	int sec = currentCommand->parameterList->get(p++)->i;
	int r = currentCommand->parameterList->get(p++)->i;
	int g = currentCommand->parameterList->get(p++)->i;
	int b = currentCommand->parameterList->get(p++)->i;


	if (s->getInitialized_S() == false)
	{
		return; //wait for object to receive server data in its update() function
	}
	else
	{
		Caption* c = getCaptionManager()->newManagedCaption(Caption::CENTERED_OVER_ENTITY, -20, sec * 1000, s->text(), BobFont::font_small_16_outlined_smooth, new BobColor(r, g, b), nullptr, BobColor::clear, RenderOrder::ABOVE_TOP, 1.0f, 0);
		c->setEntity(getPlayer()); //not really necessary, it does this automatically
		getNextCommand();
	}
}

void Event::makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb()
{ //===============================================================================================
	int p = 0;
	Entity* e = static_cast<Entity*>(currentCommand->parameterList->get(p++)->object);
	GameString* s = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	int sec = currentCommand->parameterList->get(p++)->i;
	int r = currentCommand->parameterList->get(p++)->i;
	int g = currentCommand->parameterList->get(p++)->i;
	int b = currentCommand->parameterList->get(p++)->i;


	if (s->getInitialized_S() == false)
	{
		return; //wait for object to receive server data in its update() function
	}
	else
	{
		Caption* c = getCaptionManager()->newManagedCaption(Caption::CENTERED_OVER_ENTITY, -20, sec * 1000, s->text(), BobFont::font_small_16_outlined_smooth, new BobColor(r, g, b), nullptr, BobColor::clear, RenderOrder::ABOVE_TOP, 1.0f, 0);
		c->setEntity(e);
		getNextCommand();
	}
}

void Event::makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb()
{ //===============================================================================================
	int p = 0;
	GameString* s = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	//		int sec = currentCommand.parameterList.get(p++).i;
	//		int x = currentCommand.parameterList.get(p++).i;
	//		int y = currentCommand.parameterList.get(p++).i;
	//		int r = currentCommand.parameterList.get(p++).i;
	//		int g = currentCommand.parameterList.get(p++).i;
	//		int b = currentCommand.parameterList.get(p++).i;

	//TODO: make notification stuff better, use colors and xy

	if (s->getInitialized_S() == false)
	{
		return; //wait for object to receive server data in its update() function
	}
	else
	{
		getNotificationManager()->add(new Notification(getClientGameEngine(), s->text()));
		getNextCommand();
	}
}

void Event::setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks()
{ //===============================================================================================
	int p = 0;
	GameString* gameString = static_cast<GameString*>(currentCommand->parameterList->get(p++)->object);
	int r = currentCommand->parameterList->get(p++)->i;
	int g = currentCommand->parameterList->get(p++)->i;
	int b = currentCommand->parameterList->get(p++)->i;
	int ticks = currentCommand->parameterList->get(p++)->i;

	Console::add(gameString->text(), new BobColor(r, g, b), ticks);


	getNextCommand();
}

void Event::setShowClockCaption_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getStatusBar()->clockCaption->setEnabled(b);
	getNextCommand();
}

void Event::setShowDayCaption_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getStatusBar()->dayCaption->setEnabled(b);
	getNextCommand();
}

void Event::setShowMoneyCaption_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getStatusBar()->moneyCaption->setEnabled(b);
	getNextCommand();
}

void Event::setShowAllStatusBarCaptions_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getStatusBar()->moneyCaption->setEnabled(b);
	getStatusBar()->clockCaption->setEnabled(b);
	getStatusBar()->dayCaption->setEnabled(b);
	getNextCommand();
}

void Event::setShowStatusBar_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;
	getStatusBar()->setEnabled(b);
	getNextCommand();
}

void Event::setShowNDButton_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;
	getStatusBar()->ndButton->setEnabled(b);
	getNextCommand();
}

void Event::setShowGameStoreButton_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;
	getStatusBar()->gameStoreButton->setEnabled(b);
	getNextCommand();
}

void Event::setShowStuffButton_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;
	getStatusBar()->stuffButton->setEnabled(b);
	getNextCommand();
}

void Event::setShowAllButtons_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;
	getStatusBar()->stuffButton->setEnabled(b);
	getStatusBar()->gameStoreButton->setEnabled(b);
	getStatusBar()->ndButton->setEnabled(b);
	getNextCommand();
}

void Event::setNDEnabled_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;
	getND()->setEnabled(b);
	getNextCommand();
}

void Event::setGameStoreMenuEnabled_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;
	getGameStore()->setEnabled(b);
	getNextCommand();
}

void Event::setStuffMenuEnabled_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;
	getStuffMenu()->setEnabled(b);
	getNextCommand();
}

void Event::setAllMenusAndNDEnabled_BOOL()
{ //===============================================================================================
	int p = 0;
	bool b = currentCommand->parameterList->get(p++)->b;

	if (b)
	{
		getGUIManager()->enableAllMenusAndND();
	}
	else
	{
		getGUIManager()->disableAllMenusAndND();
	}

	getNextCommand();
}

void Event::setClockUnknown()
{ //===============================================================================================
	//int p=0;
	getClock()->setUnknown(true);

	getNextCommand();
}

void Event::setClockNormal()
{ //===============================================================================================
	//int p=0;
	getClock()->setUnknown(false);

	getNextCommand();
}

void Event::setTimePaused_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;


	getClock()->setPaused(b);

	getNextCommand();
}

void Event::setTimeFastForward()
{ //===============================================================================================
	//int p=0;

	getClock()->setFast(true);

	getNextCommand();
}

void Event::setTimeNormalSpeed()
{ //===============================================================================================
	//int p=0;
	getClock()->setFast(false);

	getNextCommand();
}

void Event::setNDOpen_BOOL()
{ //===============================================================================================
	int p = 0;

	bool b = currentCommand->parameterList->get(p++)->b;

	if (b)
	{
		getGUIManager()->openND();
	}
	else
	{
		getGUIManager()->closeND();
	}

	getNextCommand();
}

void Event::startGame()
{ //===============================================================================================
	//int p=0;
	getGUIManager()->openND();
	//getND()->startGame();

	//TODO
	getNextCommand();
}

void Event::startBobsGameOnStadiumScreen_AREA()
{ //===============================================================================================
	int p = 0;
	Area* a = static_cast<Area*>(currentCommand->parameterList->get(p++)->object);

	BobsGameStadium* bobsGameStadium = new BobsGameStadium(getClientGameEngine()->stadiumScreen, a);
	bobsGameStadium->init();

	FileUtils::writeDidIntroFile();


	getNextCommand();
}

void Event::blockUntilBobsGameDead()
{ //===============================================================================================
	//int p=0;


	BobsGameStadium* bobsGameStadium = static_cast<BobsGameStadium*>(getClientGameEngine()->stadiumScreen->stadiumGameStateManager->getState());

	if (bobsGameStadium != nullptr)
	{
		if (bobsGameStadium->getPlayer1Game()->died)
		{
			getClientGameEngine()->stadiumScreen->setActivated(false);
			getNextCommand();
		}
	}
}

void Event::showLoginScreen()
{ //===============================================================================================
	//int p=0;

	//Main.introMode = false;

	//Main.mainObject.makeNewClientEngine();
	Main::getMain()->stateManager->setState(Main::getMain()->titleScreenState);


	//Main.mainObject.showControlsImage();

	getNextCommand();
}

void Event::closeAllMenusAndND()
{ //===============================================================================================
	//int p=0;
	getGUIManager()->closeAllMenusAndND();

	getNextCommand();
}

void Event::openStuffMenu()
{ //===============================================================================================
	//int p=0;
	getGUIManager()->openStuffMenu();

	getNextCommand();
}

void Event::openItemsMenu()
{ //===============================================================================================
	//int p=0;
	getGUIManager()->openItemsMenu();

	getNextCommand();
}

void Event::openLogMenu()
{ //===============================================================================================
	//int p=0;
	getGUIManager()->openLogMenu();

	getNextCommand();
}

void Event::openStatusMenu()
{ //===============================================================================================
	//int p=0;
	getGUIManager()->openStatusMenu();

	getNextCommand();
}

void Event::openFriendsMenu()
{ //===============================================================================================
	//int p=0;
	getGUIManager()->openFriendsMenu();

	getNextCommand();
}

void Event::openSettingsMenu()
{ //===============================================================================================
	//int p=0;
	getGUIManager()->openSettingsMenu();

	getNextCommand();
}

void Event::openGameStoreMenu()
{ //===============================================================================================
	//int p = 0;

	getGUIManager()->openGameStore();

	getNextCommand();
}

void Event::pushGameState()
{ //===============================================================================================
	//int p=0;

	getNextCommand(); //do this first so when i restore it, it doesn't push the stack again.

	//should have Main.gameStack ArrayDeque

	//Kryo kryo = new Kryo();//TODO:
	//Main.mainObject.gameStack.push(kryo.copy(Main.mainObject.gameEngine));
}

void Event::popGameState()
{ //===============================================================================================
	//int p=0;

	//TODO
	//   if (Main::mainObject->gameStack->size() > 0)
	//   {
	//      Main::mainObject->gameEngine = Main::mainObject->gameStack->pop();
	//   }

	getNextCommand();
}

void Event::showTitleScreen()
{ //===============================================================================================
	//int p=0;
	// TODO

	getNextCommand();
}

void Event::showCinemaEvent()
{ //===============================================================================================
	//int p=0;
	// TODO

	getNextCommand();
}

void Event::runGlobalEvent()
{ //===============================================================================================
	//int p=0;
	// TODO

	getNextCommand();
}

