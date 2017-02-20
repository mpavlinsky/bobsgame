//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class WarpArea : public Area
{
	//WarpArea: MapAsset this, String name, int mapXPixels (1x), int mapYPixels (1x), int widthPixels (1x), int heightPixels (1x), String destination, int arrivalXPixels (1x), int arrivalYPixels (1x)


public:

	static Logger log;

	WarpArea(Engine* g, AreaData* a);


	long long lastRequestedMapDataTime = 0;


	virtual void update() override;


	virtual void enter();

	virtual void renderDebugInfo() override;


	virtual void setDestinationTYPEIDString(const string& typeID);

	virtual string getDestinationMapName();
	virtual string getDestinationWarpAreaName();
};

