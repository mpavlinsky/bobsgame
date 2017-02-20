//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class String
{
public:
	static bool startsWith(const string& doesThisStart, const string& withThis);

	string s = "";
	String(string s)
	{
		this->s = s;
	}
	void setString(string s)
	{
		this->s = s;
	}
	string getString()
	{
		return s;
	}

};

