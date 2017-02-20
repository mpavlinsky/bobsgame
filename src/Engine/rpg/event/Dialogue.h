//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "src/Engine/network/ServerObject.h"

class ServerObject;
class DialogueData;


class Dialogue : public ServerObject
{
public:

	static Logger log;


private:
	bool doneValue_S = false;
	long long timeSet = -1;

	DialogueData* data;


public:
	Dialogue(Engine* g, int id);


	Dialogue(Engine* g, DialogueData* data);


	//The following method was originally marked 'synchronized':
	virtual void setData_S(DialogueData* data);


	virtual DialogueData* getData();

	virtual int getID();
	virtual string getName();
	virtual string caption();
	virtual string getComment();
	virtual string text();

	virtual string getTYPEIDString();

	virtual void setID(int id);
	virtual void setName(const string& name);
	virtual void setCaption(const string& caption);
	virtual void setComment(const string& comment);
	virtual void setText(const string& text);


	//The following method was originally marked 'synchronized':
	virtual void setDialogueDoneValue_S(bool b); //sendServerDialogueDoneValueUpdate(boolean b)


	//The following method was originally marked 'synchronized':
	virtual void initDialogueDoneValueFromGameSave_S(bool b, long long timeSet);


	//The following method was originally marked 'synchronized':
	virtual bool getDialogueDoneValue_S();


	virtual long long getTimeSet();
};

