//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



class SkillData;

class Skill : public ServerObject
{
private:
	long long timeSet = -1;
	float value = 0.0f;

	SkillData* data;


public:
	static Logger log;

	Skill(Engine* g, int id);


	Skill(Engine* g, SkillData* data);


	virtual SkillData* getData();


	virtual int getID();
	virtual string getName();

	virtual string getTYPEIDString();


	virtual void setID(int id);
	virtual void setName(const string& name);


	//The following method was originally marked 'synchronized':
	virtual void setData_S(SkillData* data);


	//The following method was originally marked 'synchronized':
	virtual void setValue_S(float f);
	virtual void setValue_S(int i);

	//The following method was originally marked 'synchronized':
	virtual void initValueFromGameSave_S(float f, long long timeSet);

	//The following method was originally marked 'synchronized':
	virtual float getValue_S();

	virtual long long getTimeSet();


	//	
	//	public void sendServerSkillValueRequest()
	//	{
	//
	//		//send a request to the server
	//
	//long long startTime = lastTimeRequestedServerValue;
	//long long currentTime = System::currentHighResTimer();
	//int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	//		if(ticksPassed>1000)
	//		{
	//
	//			if(Main.clientObject.sendSkillValueRequest(id)==true)
	//			{
	//				lastTimeRequestedServerValue=time;
	//			}
	//		}
	//
	//	}
	//
	//	
	//	public void sendServerValueUpdate(float f)
	//	{
	//
	//		//send a request to the server
	//
	//long long startTime = lastTimeSentServerValueUpdate;
	//long long currentTime = System::currentHighResTimer();
	//int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	//		if(ticksPassed>1000)
	//		{
	//
	//			if(Main.clientObject.sendSkillValueUpdate(id, f)==true)
	//			{
	//				lastTimeSentServerValueUpdate=time;
	//			}
	//		}
	//
	//	}
	//
	//	
	//	public synchronized void setServerValue(float f)
	//	{
	//		serverValue = new Float(f);
	//	}
	//	
	//	public synchronized Float getServerValue()
	//	{
	//		return serverValue;
	//
	//	}
	//	
	//	public synchronized void resetServerValue()
	//	{
	//		serverValue = null;
	//	}
	//
	//
	//
	//	
	//	/**
	//	 * This gets called repeatedly in events, until it returns a non-null value, at which point the event continues and does not ask again.
	//	 * This function will continue asking the server for the value, returning null until the server has set the response value.
	//	 * Upon finding a non-null response value set by the networking thread by a server response, we reset it to null and return that value, ensuring that it is always a fresh copy from the server.
	//	 */
	//	public Float checkServerValueAndResetAfterSuccessfulReturn()
	//	{
	//
	//		Float tempValue = getServerValue();
	//
	//		if(tempValue==null)
	//		{
	//			sendServerSkillValueRequest();
	//		}
	//		else
	//		{
	//			resetServerValue();
	//		}
	//
	//		return tempValue;
	//	}
	//
	//	
	//	/**
	//	 * This will keep sending a flag value to the server and then checking it to make sure it was set. Returns true after it confirms.
	//	 * Event commands should repeatedly call this until it returns true.
	//	 */
	//	public boolean setServerValueAndReturnTrueWhenConfirmed(float f)
	//	{
	//
	//
	//		sendServerValueUpdate(f);
	//
	//
	//		Float tempValue = checkServerValueAndResetAfterSuccessfulReturn();
	//
	//		if(tempValue!=null)
	//		{
	//			if(tempValue.intValue()==f)return true;
	//		}
	//
	//		return false;
	//
	//
	//	}
};

