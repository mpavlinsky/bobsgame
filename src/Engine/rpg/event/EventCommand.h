//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class EventParameter;


class EventCommand : public EnginePart
{
public:

	static Logger log;


	string commandString = "";


	int type = -1;
	static int TYPE_COMMAND;
	static int TYPE_QUALIFIER_TRUE;
	static int TYPE_QUALIFIER_FALSE;


	ArrayList<EventParameter*>* parameterList = new ArrayList<EventParameter*>();

	EventCommand* parent = nullptr;


	ArrayList<EventCommand*>* children = new ArrayList<EventCommand*>();


	EventCommand(Engine* g, const string& command, ArrayList<EventParameter*>* parameterList, int type);

	virtual int getNumParams();


	static EventCommand* parseEventCommandFromCommandString(Engine* g, Event* event, string commandString);


	virtual EventCommand* getParent();


	virtual void addChild(EventCommand* e);


	int currentChildIndex = 0;


	virtual EventCommand* getNextChild();
};

