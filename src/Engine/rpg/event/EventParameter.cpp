#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger EventParameter::log = Logger("EventParameter");


EventParameter::EventParameter(Engine* g, const string& parameterString)
{ //===============================================================================================

	this->e = g;
	this->parameterString = parameterString;
}

void EventParameter::parsePrimitive(const string& typeString, const string& primitiveValueString)
{ //===============================================================================================

	if (String::startsWith(typeString, "BOOL"))
	{
		//type=TYPE_BOOL;
		try
		{
			this->b = StringConverterHelper::fromString<bool>(primitiveValueString);
		}
		catch (exception)
		{
			log.error("Could not parse bool in primitiveValueString");
		}
		
	}
	else
	{
		if (String::startsWith(typeString, "INT"))
		{
			//type=TYPE_INT;
			try
			{
				this->i = stoi(primitiveValueString);
			}
			catch (exception)
			{
				log.error("Could not parse int in primitiveValueString");
			}
		}
		else
		{
			if (String::startsWith(typeString, "FLOAT"))
			{
				//type=TYPE_FLOAT;
				try
				{
					this->f = stof(primitiveValueString);
				}
				catch (exception)
				{
					log.error("Could not parse float in primitiveValueString");
				}
			}
		}
	}
}

void EventParameter::updateParameterVariablesFromString(Event* event)
{ //===============================================================================================

	//parameterName is always OBJECT.id


	if (String::startsWith(parameterString, "BOOL."))
	{
		parsePrimitive("BOOL", parameterString.substr(parameterString.find(".") + 1));
	}
	else
	{
		if (String::startsWith(parameterString, "INT."))
		{
			parsePrimitive("INT", parameterString.substr(parameterString.find(".") + 1));
		}
		else
		{
			if (String::startsWith(parameterString, "FLOAT."))
			{
				parsePrimitive("FLOAT", parameterString.substr(parameterString.find(".") + 1));
			}
			else
			{
				if (String::startsWith(parameterString, "STRING."))
				{
					parsePrimitive("STRING", parameterString.substr(parameterString.find(".") + 1));
				}
				else
				{
					if (parameterString == "PLAYER")
					{
						this->object = getPlayer();
					}
					else
					{
						if (parameterString == "THIS")
						{
							Entity* o = nullptr;

							if (event->door != nullptr)
							{
								o = event->door;
							}
							if (event->entity != nullptr)
							{
								o = event->entity;
							}

							this->object = o;
						}
						else
						{
							//if we made it here, it's a map object.
							Map* o = (Map*)getEngine()->getGameObjectByTYPEIDName(parameterString);

							if (o == nullptr)
							{
								log.error(string("Could not find GameObject: ") + parameterString + string(" when parsing Event Parameter."));
							}
							else
							{
								//String newTypeString = parameterString.substring(parameterString.indexOf("."));

								this->object = o;
							}
						}
					}
				}
			}
		}
	}
}

string EventParameter::toString()
{ //===============================================================================================


	log.error("Should never call toString in EventParameter");


	return "";
}

