
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"



//=========================================================================================================================
class GlobalSettings
{//=========================================================================================================================
public:
	int musicVolume = 50;

	float hue = 1.5f;
	float saturation = 1.2f;
	float brightness = 1.0f;
	float contrast = 1.2f;
	float gamma = 1.0f;
	bool useXInput = false;

	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(musicVolume);

		if (version>0)
		{
			ar & BOOST_SERIALIZATION_NVP(hue);
			ar & BOOST_SERIALIZATION_NVP(saturation);
			ar & BOOST_SERIALIZATION_NVP(brightness);
			ar & BOOST_SERIALIZATION_NVP(contrast);
			ar & BOOST_SERIALIZATION_NVP(gamma);
		}
		if(version>1)
		{
			ar & BOOST_SERIALIZATION_NVP(useXInput);
		}
	}


};
BOOST_CLASS_VERSION(GlobalSettings, 2)
BOOST_CLASS_TRACKING(GlobalSettings, boost::serialization::track_never)