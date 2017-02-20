//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class NDMenuInfoPanel
{
public:

	static Logger log;

	/*
	
	            Texture infopanel_TEXTURE = GL.loadTexture("res/nD/menu/infopanel/infopanel.png");
	
	            int infopanel_scroll_ticks=0;
	            int infopanel_x=0;
	            int infopanel_y=0;
	
	            Texture infopanel_border_TEXTURE[8];
	
	            infopanel_border_TEXTURE[0] = GL.loadTexture("res/nD/menu/infopanel/infopanel_border_00.png");
	            infopanel_border_TEXTURE[1] = GL.loadTexture("res/nD/menu/infopanel/infopanel_border_01.png");
	            infopanel_border_TEXTURE[2] = GL.loadTexture("res/nD/menu/infopanel/infopanel_border_02.png");
	            infopanel_border_TEXTURE[3] = GL.loadTexture("res/nD/menu/infopanel/infopanel_border_03.png");
	            infopanel_border_TEXTURE[4] = GL.loadTexture("res/nD/menu/infopanel/infopanel_border_04.png");
	            infopanel_border_TEXTURE[5] = GL.loadTexture("res/nD/menu/infopanel/infopanel_border_05.png");
	            infopanel_border_TEXTURE[6] = GL.loadTexture("res/nD/menu/infopanel/infopanel_border_06.png");
	            infopanel_border_TEXTURE[7] = GL.loadTexture("res/nD/menu/infopanel/infopanel_border_07.png");
	
	
	            //pulse colors
	               //gradient between 0,255,0 and 133,0,255
	               // +1, -2, +2
	
	            SDL_Color fade_COLOR[256];
	
	            int fade_r=0;
	            int fade_g=255;
	            int fade_b=0;
	
	            int colorfadedirection=0;
	
	               int l=0;
	               for(l=0;l<256;l++)
	               {
	                  if(colorfadedirection==0)
	                  {
	                     fade_r+=1;
	                     fade_g-=2;
	                     fade_b+=2;
	
	                     if(fade_r>255)fade_r=255;
	                     if(fade_g>255)fade_g=255;
	                     if(fade_b>255)fade_b=255;
	
	                     if(fade_r<0)fade_r=0;
	                     if(fade_g<0)fade_g=0;
	                     if(fade_b<0)fade_b=0;
	
	                     if(fade_b==255)colorfadedirection=1;
	
	                  }
	                  else
	                  if(colorfadedirection==1)
	                  {
	
	                     fade_r-=1;
	                     fade_g+=2;
	                     fade_b-=2;
	
	                     if(fade_r>255)fade_r=255;
	                     if(fade_g>255)fade_g=255;
	                     if(fade_b>255)fade_b=255;
	
	                     if(fade_r<0)fade_r=0;
	                     if(fade_g<0)fade_g=0;
	                     if(fade_b<0)fade_b=0;
	
	                     if(fade_g==255)colorfadedirection=0;
	                  }
	
	                  fade_COLOR[l].r = fade_r;
	                  fade_COLOR[l].g = fade_g;
	                  fade_COLOR[l].b = fade_b;
	               }
	*/
	//------------------------------------------
};

