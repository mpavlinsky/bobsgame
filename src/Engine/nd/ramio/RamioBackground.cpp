#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger RamioBackground::log = Logger("RamioBackground");

RamioBackground::RamioBackground(Engine* g)
{ //=========================================================================================================================

	initMap(g, new MapData(-1, "ramio", 400, 20));
}

void RamioBackground::RAMIO_shakeplayingfield()
{ //=========================================================================================================================
	//called every VBL to make the background pretty


	if (dir == 0)
	{
		RAMIO_playing_field_map_scroll_x++;
		if (RAMIO_playing_field_map_scroll_x > 3)
		{
			dir = 1;
			RAMIO_playing_field_map_scroll_x--;
		}
	}
	else
	{
		RAMIO_playing_field_map_scroll_x--;
		if (RAMIO_playing_field_map_scroll_x < -3)
		{
			dir = 0;
			RAMIO_playing_field_map_scroll_x++;
		}
	}


	//HARDWARE_set_AUX_map_xy(2,TV_fromx+RAMIO_playing_field_map_scroll_x,TV_fromy);
}

void RamioBackground::init()
{ //=========================================================================================================================
}

void RamioBackground::update()
{ //=========================================================================================================================
	Map::update();

	{
		//if(ticks%3==0)
		// make the tv scanlines pulse
		if (fadeInOutPulseToggle == false)
		{
			fadeInOutPulseToggle = true;
		}
		else
		{
			fadeInOutPulseToggle = false;
		}
	}
}

