#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger NDMenuMovie::log = Logger("NDMenuMovie");


void NDMenuMovie::init()
{
	//------------------------------------------
	//initialize movie values
	//------------------------------------------
	/*
	      Texture[] movie_border_TEXTURE = new Texture[13];
	
	      movie_border_TEXTURE[0] = GL.loadTexture("res/nD/menu/movie_border/movie_border_00.png");
	      movie_border_TEXTURE[1] = GL.loadTexture("res/nD/menu/movie_border/movie_border_01.png");
	      movie_border_TEXTURE[2] = GL.loadTexture("res/nD/menu/movie_border/movie_border_02.png");
	      movie_border_TEXTURE[3] = GL.loadTexture("res/nD/menu/movie_border/movie_border_03.png");
	      movie_border_TEXTURE[4] = GL.loadTexture("res/nD/menu/movie_border/movie_border_04.png");
	      movie_border_TEXTURE[5] = GL.loadTexture("res/nD/menu/movie_border/movie_border_05.png");
	      movie_border_TEXTURE[6] = GL.loadTexture("res/nD/menu/movie_border/movie_border_06.png");
	      movie_border_TEXTURE[7] = GL.loadTexture("res/nD/menu/movie_border/movie_border_07.png");
	      movie_border_TEXTURE[8] = GL.loadTexture("res/nD/menu/movie_border/movie_border_08.png");
	      movie_border_TEXTURE[9] = GL.loadTexture("res/nD/menu/movie_border/movie_border_09.png");
	      movie_border_TEXTURE[10] = GL.loadTexture("res/nD/menu/movie_border/movie_border_10.png");
	      movie_border_TEXTURE[11] = GL.loadTexture("res/nD/menu/movie_border/movie_border_11.png");
	      movie_border_TEXTURE[12] = GL.loadTexture("res/nD/menu/movie_border/movie_border_12.png");
	
	
	      int movie_x=0;
	      int movie_y=0;
	      int movie_scroll_ticks=0;
	      int movie_play_ticks=0;
	
	      int direction_button_pressed=0;
	
	      SDL_Surface* movie_YUV_SURFACE[4];
	      SMPEG_Info movieInfo[4];
	      SMPEG* movie[4];
	
	      SDL_Surface* movie_RGBA_SURFACE = null;
	      Texture movie_TEXTURE[2] = {null, null};
	
	      int movieswapframe=0;
	      int movie_frame_num=0;
	      int movie_render_step=0;
	      int movieswapframe_opposite=0;
	
	
	
	      //movie[0] = SMPEG_new("res/nD/menu/movie/superbrobros_gameplay.mpg", 	&movieInfo[0], 0);
	      movie[1] = SMPEG_new("res/nD/menu/movie/bobsgame_gameplay.mpg", 		&movieInfo[1], 0);
	      //movie[2] = SMPEG_new("res/nD/menu/movie/splarkapuzzle_gameplay.mpg", 	&movieInfo[2], 0);
	      //movie[3] = SMPEG_new("res/nD/menu/movie/yokoid_gameplay.mpg", 			&movieInfo[3], 0);
	
	
	      int m=1;
	      //for(m=0;m<4;m++)
	      {
	         SDL_Surface* tempSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, movieInfo[m].width, movieInfo[m].height, 32, rmask, gmask, bmask, amask);
	         movie_YUV_SURFACE[m] = SDL_DisplayFormat(tempSurface);
	         SDL_FreeSurface(tempSurface);
	         SMPEG_setdisplay(movie[m], movie_YUV_SURFACE[m], null, null);
	      }
	
	      //SMPEG_setdisplayregion(movie, 0, 0, movieInfo.width, movieInfo.height);
	      //Uint8* keys;
	      //SMPEG_play(movie);
	      //SMPEG_loop(movie, 1);// Set the looping of hte movie
	      //SMPEG_seek(movie, bytes);// Seek a number of bytes into the movie
	      //SMPEG_setdisplayregion(movie, x, y, w, h);// Sets the region of the video to be shown
	      //SMPEG_scaleXY(movie, w, h);// Scale the movie by the desired factors
	      //SMPEG_scale(movie, factor);// Scale the movie by the desired factor
	      //SMPEG_setvolume(movie, vol);// Set's the volume on a getScale of 0 - 100
	      //SMPEG_renderFrame(movie, frame);// Render some frame of the movie
	      //SMPEG_renderFinal(movie, movieSurface, 0, 0);// Render the final frame of the movie
	      //SMPEG_Info SMPEG_getinfo(movie, &movieInfo);
	      //SMPEGstatus SMPEG_status(movie);//Get the current status of the movie, can be SMPEG_ERROR = -1, SMPEG_STOPPED, SMPEG_PLAYING
	*/
	//------------------------------------------
}

