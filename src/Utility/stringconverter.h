#pragma once
#include "bobtypes.h"
class Logger;



//----------------------------------------------------------------------------------------
//	Copyright © 2007 - 2015 Tangible Software Solutions Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class is used to replace some conversions to or from strings.
//----------------------------------------------------------------------------------------
#include <sstream>

class StringConverterHelper
{
public:
	template <typename T>
	static string toString(const T& subject)
	{
		ostringstream ss;
		ss << subject;
		return ss.str();
	}

	template <typename T>
	static T fromString(const string& subject)
	{
		istringstream ss(subject);
		T target;
		ss >> target;
		return target;
	}
};

