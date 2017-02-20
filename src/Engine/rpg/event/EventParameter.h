//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class EventParameter : public EnginePart
{
public:
	static Logger log;

	void* object = nullptr;

	int type = -1;

	//	public static int TYPE_MAP			 = 0;
	//	public static int TYPE_SPRITE		 = 1;
	//	public static int TYPE_ENTITY		 = 2;
	//	public static int TYPE_LIGHT		 = 3;
	//	public static int TYPE_DOOR			 = 4;
	//	public static int TYPE_AREA			 = 5;
	//	public static int TYPE_ITEM			 = 6;
	//	public static int TYPE_GAME			 = 7;
	//	public static int TYPE_FLAG			 = 8;
	//	public static int TYPE_SOUND	 	 = 9;
	//	public static int TYPE_MUSIC		 = 10;
	//public static int TYPE_DIALOGUE	 	 = 11;
	//	public static int TYPE_EVENT		 = 12;
	//public static int TYPE_GAMESTRING		 = 13;
	//	public static int TYPE_STATE		 = 14;
	//	public static int TYPE_SKILL		 = ;

	//	public static int TYPE_INT			 = 15;
	//	public static int TYPE_FLOAT		 = 16;
	//	public static int TYPE_STRING		 = 17;
	//	public static int TYPE_BOOL		 	= 18;
	//	public static int TYPE_THIS		 	= 19;
	//	public static int TYPE_PLAYER		 	= 20;
	//
	//	public static int TYPE_ERROR = 99;


	int i = -1;
	float f = -1.0f;
	bool b = false;

	string parameterString = "";


	EventParameter(Engine* g, const string& parameterString);


	virtual void parsePrimitive(const string& typeString, const string& primitiveValueString);


	virtual void updateParameterVariablesFromString(Event* event);


	virtual string toString();


	//	
	//	public String getIDString()
	//	{
	//		if(type==TYPE_ERROR)
	//		{
	//			log.error("Error in Event Parameter: typeName:"+typeString+" String:"+s);
	//			return "ERROR."+s;
	//		}
	//
	//
	//		if(type==TYPE_INT)return "INT."+i;
	//		if(type==TYPE_FLOAT)return "FLOAT."+f;
	//		if(type==TYPE_BOOL)return "BOOL."+b;
	//
	//		if(object!=null)return object.getIDString();
	//
	//		log.error("Error in Event Parameter: typeName:"+typeString+" String:"+s);
	//		return "ERROR"+s;
	//	}


	//	
	//	public String getDisplayName()
	//	{
	//		if(type==TYPE_ERROR)return "ERROR."+typeString+"."+s;
	//		if(type==TYPE_INT)return "INT."+i;
	//		if(type==TYPE_FLOAT)return "FLOAT."+f;
	//		if(type==TYPE_BOOL)return "BOOL."+b;
	//
	//		if(type==TYPE_CAPTION)return "\""+((GameString)object).getText.substring(0,Math.min(20,((GameString)object).getText.length()))+"\"";
	//		if(type==TYPE_DIALOGUE)return "\""+((Dialogue)object).getText.substring(0,Math.min(20,((Dialogue)object).getText.length()))+"\"";
	//
	//		if(object!=null)return object.getShortTypeName();
	//
	//
	//		return "ERROR."+typeString+"."+s;
	//	}
};

