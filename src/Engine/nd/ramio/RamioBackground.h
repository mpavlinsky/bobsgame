//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "../../map/Map.h"


class RamioBackground : public Map
{
public:

	static Logger log;


	RamioBackground(Engine* g);


	int RAMIO_screen_x = 0;
	int RAMIO_screen_y = 0;

	int RAMIO_tv_rolling = 0;

	int RAMIO_scrollingplayingfield_map_x = 0;
	int RAMIO_scrollingplayingfield_map_y = 0;
	int RAMIO_playing_field_map_scroll_x = 0;


	int RAMIO_map_x = 0;
	int RAMIO_offset_x = 0;


	int RAMIO_map_width = 0;


	int RAMIO_tileset_size = 0;

	int dir = 0;

	bool fadeInOutPulseToggle = false;


	virtual void RAMIO_shakeplayingfield();


	virtual void init();


	virtual void update();
};

