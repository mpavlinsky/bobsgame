
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once



Logger SpriteManager::log = Logger("SpriteManager");


u8* GAME_original_SPRITE_PALETTE = NULL; //pointer to globalspritepalette.bin
u8* GAME_hq2x_SPRITE_PALETTE = NULL; //pointer to hq2xpalette.bin

u8 GAME_temp_SPRITE_PALETTE[256] = {0};//holds brightened sprite palette

//int HARDWARE_texture_SPRITE_PALETTE[256] = {0}; //holds current palette loaded with HARDWARE_load_sprite_palette, so this is the one that gets used ultimately
u8 HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[256 * 3] = {0};
u8 HARDWARE_HQ2X_SPRITE_PALETTE_ENHANCED_RGB[256 * 3] = {0};


GLuint GLTex_preloaded_sprite_textures[1024 * 8 * 8] = {0};

bool USED_preloaded_sprite_textures_USED[1024 * 8 * 8] = {0};//this is for each individual frame, recording that there is a texture there, since setting GLuint to zero is unreliable.

bool Used_Preloaded_Texture_ID_Array_Slots[1024] = {0};//this is for each 8x8 frame offset, per sprite file. the slot being marked as reserved here doesnt mean theres a texture there yet.

//float rotation_set[128] = {0};

SPRITE* HARDWARE_sprites[256];
GLuint HARDWARE_preload_sprite_texture_frame(GFX* gfx, int frame, int IndexInCachedTextureIDArray);


////==========================================================================================================================
//void HARDWARE_init_arrays()
////==========================================================================================================================
//{
//	int x = 0;
//
//	//for(x=0;x<128;x++)GLTex_sprite[x]=-1;
//	//for(x=0;x<1024;x++)GLTex_preloaded_gfx_structs[x]=NULL;
//	for (x = 0; x < 1024; x++)Used_Preloaded_Texture_ID_Array_Slots[x] = 0;
//	//for(x=0;x<128;x++)PLAYER_id_gfx_slot[x]=-1;
//
//	for (x = 0; x < 256; x++)HARDWARE_sprites[x] = NULL;
//
//	for (x = 0; x < 1024 * 8 * 8; x++)GLTex_preloaded_sprite_textures[x] = 0;
//	for (x = 0; x < 1024 * 8 * 8; x++)USED_preloaded_sprite_textures_USED[x] = 0;
//}
//
//
////==========================================================================================================================
//void HARDWARE_load_sprite_palette(int* palette)//HARDWARE_LoadSpritePal
//{//==========================================================================================================================
//
//	palette = NULL;
//
//	ERROR_set_error("need to fix palette loading");
//}


//==========================================================================================================================
void HARDWARE_set_sprite_texture_filename_and_maybe_preload_texture(GFX* gfx, string & gfx_filename, int data_size_x, int data_size_y, bool shadow, bool preload)//HARDWARE_UpdateSpriteGfx
{//==========================================================================================================================


	//-----------------------------
	//if hq2x is on, use normal data sizes
	//-----------------------------
	if (Main::getMain()->GLOBAL_hq2x_is_on)
	{
		//strcpy(gfx->FileName, gfx_filename);
		gfx->FileName = gfx_filename;

		//if filename has hq2x
		//if (strncmp(gfx_filename, "/sprite/hq2x", 12) == 0)
		string startwith = "/sprite/hq2x";
		if (gfx_filename.rfind("/sprite/hq2x", 0) == 0)//gfx_filename."/sprite/hq2x", 12) == 0)
		{
			//normal character sprites are 16x40, kids are 16x32. (adults 32x80 and kids 32x64 for hq2x)
			if (data_size_x == 32 && data_size_y == 64)
				gfx->kid = 1;

			if (data_size_x == 32 && data_size_y == 80)
				gfx->adult = 1;
		}
	}
	else
	{
		//-----------------------------
		//hq2x is off, we need to cut down the data sizes and load the original sprites
		//-----------------------------

		//if filename has hq2x
		if (gfx_filename.rfind("/sprite/hq2x", 0) == 0)
		{
			//change filename
			//remove hq2x from string
			//cut off first 12 chars, replace with /sprite/

			//sprintf(gfx->FileName, "/sprite/%s", (char*)(&gfx_filename[12]));
			gfx->FileName = "/sprite/" + gfx_filename;

			//see if its a kid, car, adult, or bike
			if (data_size_x == 32 && data_size_y == 80)
				gfx->adult = 1;

			//normal character sprites are 16x40, kids are 16x32. (adults 32x80 and kids 32x64 for hq2x)
			if (data_size_x == 32 && data_size_y == 64)
				gfx->kid = 1;

			//if kid, make 16x32
			if (gfx->kid)
			{
				data_size_x = 16;
				data_size_y = 32;
			}
			//if adult, make 32 x 64. USED TO BE 16*40 but after i imported them into the editor it made them 32x64.
			//hq2x is 32x80 because they werent input into the editor, they were made with an image and a hq2x tool, i think...
			if (gfx->adult)
			{
				data_size_x = 32;
				data_size_y = 64;
			}
			//if car or bike make 64x64
			if (gfx->car || gfx->bike)
			{
				data_size_x = 64;
				data_size_y = 64;
			}
		}
		else gfx->FileName = gfx_filename;// strcpy(gfx->FileName, gfx_filename);
	}

	gfx->data_size_x = data_size_x;
	gfx->data_size_y = data_size_y;


	//find open slot in preloaded sprite textures (in steps of 64)
	int IndexInCachedTextureIDArray = -1;
	int s = 0;
	for (s = 0; s < 1024; s++)
	{
		//if it doesn't have a texture
		if (Used_Preloaded_Texture_ID_Array_Slots[s] == 0)
		{
			IndexInCachedTextureIDArray = s;
			s = 1024;
			break;
		}
	}

	if (IndexInCachedTextureIDArray == -1)
	{
		ERROR_set_error("ran out of preloaded sprite slots \n");
		return;
	}

	//reference this later to find the appropriate texture slot when we are assigning the textures to the actual sprites


	//all this is used for is a marker to get a position in the GLTex_preloaded_sprite_textures, this array is not used outside of this function
	Used_Preloaded_Texture_ID_Array_Slots[IndexInCachedTextureIDArray] = 1;


	gfx->IndexInCachedTextureIDArray = IndexInCachedTextureIDArray;

	gfx->shadow = shadow;


	if (preload == 1)//HARDWARE_preload_sprite_textures(gfx,gfx->data_size_x,gfx->data_size_y,IndexInCachedTextureIDArray);
	{
		int gfx_data_is_file = 1;

		int amount_of_frames_in_file = 0;


		//this is for getCaption chunks, it tracks a dynamic indexed graphic array inside itself
		if (gfx->indexed_gfx_data != NULL)
		{
			//sprite_indexed_gfx_data = gfx->indexed_gfx_data;
			amount_of_frames_in_file = 1;
			gfx_data_is_file = 0;
		}

		if (gfx_data_is_file)
		{
			//need to figure out size of file and size of sprite to calculate amount of frames.
			//get filesize
			long filesize = 0;
			filesize = HARDWARE_get_file_size("data/" + gfx->FileName);

			amount_of_frames_in_file = (int)(filesize / (long)(gfx->data_size_x * gfx->data_size_y));
		}


		//load all possible frames into slot
		int f = 0;
		for (f = 0; f < amount_of_frames_in_file; f++)
		{
			HARDWARE_preload_sprite_texture_frame(gfx, f, IndexInCachedTextureIDArray);
		}
	}
}

//==========================================================================================================================
GLuint HARDWARE_preload_sprite_texture_frame(GFX* gfx, int frame, int IndexInCachedTextureIDArray)//HARDWARE_UpdateSpriteGfx
{//==========================================================================================================================

	//-----------------------------
	//set the palette for hq2x or not
	//-----------------------------

	u8* palette = HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB;//(int*)HARDWARE_texture_SPRITE_PALETTE;

	if (gfx->hq2x)
	{
		palette = HARDWARE_HQ2X_SPRITE_PALETTE_ENHANCED_RGB;//GAME_hq2x_SPRITE_PALETTE;
	}


	//-----------------------------
	//set texture size
	//-----------------------------
	int car = gfx->car;
	int kid = gfx->kid;
	int bike = gfx->bike;
	int adult = gfx->adult;

	int texture_size_x = gfx->data_size_x;
	int texture_size_y = gfx->data_size_y;


	//do this because there isnt enough room for shadow so i have to double the texture size y
	if (car || kid || adult || bike)texture_size_y *= 2;

	//make sure texture size is power of 2!
	texture_size_x = Math::power_of_two(texture_size_x);
	texture_size_y = Math::power_of_two(texture_size_y);

	gfx->texture_size_x = texture_size_x;
	gfx->texture_size_y = texture_size_y;

	//-----------------------------
	//calculate gfx_index by frame and data size
	//-----------------------------
	int sprite_data_size_x = gfx->data_size_x;
	int sprite_data_size_y = gfx->data_size_y;

	int gfx_index = 0;
	gfx_index = frame * sprite_data_size_x * sprite_data_size_y;

	//-----------------------------
	//determine whether we are loading from a file or from internal memory
	//-----------------------------
	int gfx_data_is_file = 1;
	int* sprite_indexed_gfx_data = NULL;


	if (gfx->indexed_gfx_data != NULL)
	{
		sprite_indexed_gfx_data = gfx->indexed_gfx_data;
		gfx_data_is_file = 0;
	}

	if (gfx_data_is_file == 1)sprite_indexed_gfx_data = (int*)HARDWARE_load_file("data/"+gfx->FileName);


	//-----------------------------
	//make the surface
	//-----------------------------
	//SDL_Surface * surface = SDL_CreateRGBSurface(SDL_SWSURFACE, texture_size_x, texture_size_y, 32, rmask, gmask, bmask, amask);
	//SDL_LockSurface( surface );

	unsigned char* rgba_data = (unsigned char*)calloc(texture_size_x * texture_size_y * 4, sizeof(unsigned char));//(unsigned char *)surface->pixels;


	//-----------------------------
	//find the top and bottom of the sprite for the shadow
	//-----------------------------

	int shadow = gfx->shadow;

	int x = 0;
	int y = 0;
	int z = 0;

	int bottomy = 0;
	int topy = 0;
	int rightx = 0;

	int stop = 0;
	//find bottomy
	for (y = sprite_data_size_y - 1; y >= 0 && stop == 0; y--)
		for (x = 0; x < sprite_data_size_x && stop == 0; x++)
		{
			int i = 0;
			i =
				((64 * (x / 8)) + //skip 64 for each tile x
					(x % 8)) + //remaining x
				(64 * (sprite_data_size_x / 8) * (y / 8)) + //skip 2 x 64 for each tile y
				(8 * (y % 8));//8 for each row in tile y

			if (x < sprite_data_size_x && y < sprite_data_size_y && sprite_indexed_gfx_data[gfx_index + i] != 0)
			{
				bottomy = y + 1;
				stop = 1;
				break;
			}
		}

	//find topy
	stop = 0;
	for (y = 0; y < sprite_data_size_y && stop == 0; y++)
		for (x = 0; x < sprite_data_size_x && stop == 0; x++)
		{
			int i = 0;
			i =
				((64 * (x / 8)) + //skip 64 for each tile x
					(x % 8)) + //remaining x
				(64 * (sprite_data_size_x / 8) * (y / 8)) + //skip 2 x 64 for each tile y
				(8 * (y % 8));//8 for each row in tile y

			if (x < sprite_data_size_x && y < sprite_data_size_y && sprite_indexed_gfx_data[gfx_index + i] != 0)
			{
				topy = y;
				stop = 1;
				break;
			}
		}

	//find rightmost pixel
	stop = 0;
	for (y = topy; y < bottomy && stop == 0; y++)
		for (x = 0; x < sprite_data_size_x && stop == 0; x++)
		{
			int i = 0;
			i =
				((64 * (x / 8)) + //skip 64 for each tile x
					(x % 8)) + //remaining x
				(64 * (sprite_data_size_x / 8) * (y / 8)) + //skip 2 x 64 for each tile y
				(8 * (y % 8));//8 for each row in tile y

			if (x < sprite_data_size_x && y < sprite_data_size_y && sprite_indexed_gfx_data[gfx_index + i] != 0)
			{
				if (x > rightx)rightx = x;
			}
		}


	//set the texture content size for clipping while rendering to save render time
	gfx->content_size_x = rightx + 1;
	if (gfx->content_size_x > gfx->texture_size_x)gfx->content_size_x = gfx->texture_size_x;

	if (bottomy + 1 > gfx->content_size_y)gfx->content_size_y = bottomy + 1;

	if (shadow == 1)
	{
		int size_y = (bottomy - 1) - topy;//gfx->data_size_y;

		//from bottom of texture/3 tiles under bottom y to bottom y, mirror the pixels starting from the top as shadow
		int start_shadow_y = (texture_size_y / 4) * 3;

		//dont draw shadows longer than half the sprite height
		if (bottomy + size_y / 2 < start_shadow_y)start_shadow_y = bottomy + size_y / 2;

		//if the sprite is less than half a person tall, draw a small shadow
		if ((bottomy - topy) < size_y / 2)start_shadow_y = bottomy + 8;


		if (start_shadow_y + 1 > gfx->content_size_y)gfx->content_size_y = start_shadow_y + 1;


		//fill the whole array with 0
		z = 0;
		for (y = 0; y < texture_size_y; y++)
		{
			for (x = 0; x < texture_size_x; x++)
			{
				rgba_data[(z * 4) + 0] = 0;
				rgba_data[(z * 4) + 1] = 0;
				rgba_data[(z * 4) + 2] = 0;
				rgba_data[(z * 4) + 3] = 0;
				z++;
			}
		}

		z = 0;
		for (y = start_shadow_y; y >= bottomy - (size_y / 4); y--) //draw the shadow up to 1/4 the sprite height to make sure it covers the feet
		{
			for (x = 0; x < texture_size_x; x++)
			{
				z = (y * texture_size_x) + x;

				int mirrory = topy + (int)((start_shadow_y - y) * 1.25f);
				if (mirrory < 0)mirrory = 0;
				if (mirrory > bottomy)mirrory = bottomy;

				int i = 0;
				i =
					((64 * (x / 8)) + //skip 64 for each tile x
						(x % 8)) + //remaining x
					(64 * (sprite_data_size_x / 8) * (mirrory / 8)) + //skip 2 x 64 for each tile y
					(8 * (mirrory % 8));//8 for each row in tile y

				if (sprite_indexed_gfx_data[gfx_index + i] == 0)
				{
					rgba_data[(z * 4) + 0] = 0;
					rgba_data[(z * 4) + 1] = 0;
					rgba_data[(z * 4) + 2] = 0;
					rgba_data[(z * 4) + 3] = 0;
				}
				else
				{
					rgba_data[(z * 4) + 0] = 0;
					rgba_data[(z * 4) + 1] = 0;
					rgba_data[(z * 4) + 2] = 0;

					int t = 159;
					///ignoring alpha for now
					//if(PLAYER_gfx_slot_alpha[gfx_slot]<t)t=PLAYER_gfx_slot_alpha[gfx_slot];
					if (t < 0)t = 0;

					rgba_data[(z * 4) + 3] = t;
				}
			}
		}
	}


	//fill as usual, ignoring 0 values.

	z = 0;
	for (y = 0; y < texture_size_y; y++)
	{
		for (x = 0; x < texture_size_x; x++)
		{
			int i = 0;
			i =
				((64 * (x / 8)) + //skip 64 for each tile x
					(x % 8)) + //remaining x
				(64 * (sprite_data_size_x / 8) * (y / 8)) + //skip 2 x 64 for each tile y
				(8 * (y % 8));//8 for each row in tile y


			if (x >= sprite_data_size_x || y >= sprite_data_size_y)
			{
				if (!shadow)
				{
					rgba_data[(z * 4) + 2] = 0;
					rgba_data[(z * 4) + 1] = 0;
					rgba_data[(z * 4) + 0] = 0;
					rgba_data[(z * 4) + 3] = 0;
				}
			}
			else if (sprite_indexed_gfx_data[gfx_index + i] == 0)
			{
				if (!shadow)
				{
					rgba_data[(z * 4) + 2] = 0;
					rgba_data[(z * 4) + 1] = 0;
					rgba_data[(z * 4) + 0] = 0;
					rgba_data[(z * 4) + 3] = 0;
				}
			}
			else
			{
				if (car || bike)
				{
					int r = palette[sprite_indexed_gfx_data[gfx_index + i] * 3 + 0];
					int g = palette[sprite_indexed_gfx_data[gfx_index + i] * 3 + 1];
					int b = palette[sprite_indexed_gfx_data[gfx_index + i] * 3 + 2];


					rgba_data[(z * 4) + BYTE_RED] = r;
					rgba_data[(z * 4) + BYTE_GREEN] = g;
					rgba_data[(z * 4) + BYTE_BLUE] = b;
					rgba_data[(z * 4) + 3] = 255;
				}
				else
				{
					int r = palette[sprite_indexed_gfx_data[gfx_index + i] * 3 + 0]; //(spritepalette_bgr[sprite_indexed_gfx_data[gfx_index+i]]%32)*8;
					int g = palette[sprite_indexed_gfx_data[gfx_index + i] * 3 + 1]; //((spritepalette_bgr[sprite_indexed_gfx_data[gfx_index+i]]/32)%32)*8;
					int b = palette[sprite_indexed_gfx_data[gfx_index + i] * 3 + 2]; //(((spritepalette_bgr[sprite_indexed_gfx_data[gfx_index+i]]/32)/32)%32)*8;
					int a = 255;

					//adjust_color(&r,&g,&b);

					rgba_data[(z * 4) + BYTE_RED] = r;
					rgba_data[(z * 4) + BYTE_GREEN] = g;
					rgba_data[(z * 4) + BYTE_BLUE] = b;

					rgba_data[(z * 4) + 3] = a;
				}
			}

			z++;
		}
	}

	if (gfx_data_is_file)HARDWARE_unload_file((void**)&sprite_indexed_gfx_data);


	//SDL_UnlockSurface(surface);

	int w = texture_size_x;//surface->w;
	int h = texture_size_y;//surface->h;
	int* g = (int*)rgba_data;//surface->pixels;


	if (IndexInCachedTextureIDArray != -2)///for normal textures
	{
		//if there is already a texture there delete it and throw error
		if (USED_preloaded_sprite_textures_USED[IndexInCachedTextureIDArray * 8 * 8 + frame] && glIsTexture(GLTex_preloaded_sprite_textures[IndexInCachedTextureIDArray * 8 * 8 + frame]))
		///THIS IS THE MULTIPLE SPRITE BUG SINCE THERE IS A TEXTURE ZERO, EVERY SINGLE ENTRY IS GETTING DELETED
		{
			glDeleteTextures(1, &GLTex_preloaded_sprite_textures[IndexInCachedTextureIDArray * 8 * 8 + frame]);
			//fprintf(stderr,"texture %s already existed and was overwritten. this shouldn't normally happen, so find out why!\n",gfx->FileName);
		}

		glGenTextures(1, &GLTex_preloaded_sprite_textures[IndexInCachedTextureIDArray * 8 * 8 + frame]);
		glBindTexture(GL_TEXTURE_2D, GLTex_preloaded_sprite_textures[IndexInCachedTextureIDArray * 8 * 8 + frame]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, g);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//SDL_FreeSurface(surface);
		if (rgba_data != NULL)
		{
			free(rgba_data);
			rgba_data = NULL;
		}

		USED_preloaded_sprite_textures_USED[IndexInCachedTextureIDArray * 8 * 8 + frame] = 1;

		return GLTex_preloaded_sprite_textures[IndexInCachedTextureIDArray * 8 * 8 + frame]; //dont have to do this
	}
	else /// is -2, for captions ONLY right now
	{
		GLuint newtex = 0;
		glGenTextures(1, &newtex);
		glBindTexture(GL_TEXTURE_2D, newtex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, g);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		//glFinish();

		//SDL_FreeSurface(surface);
		if (rgba_data != NULL)
		{
			free(rgba_data);
			rgba_data = NULL;
		}

		return newtex;
	}
}


//==========================================================================================================================
void HARDWARE_update_sprite_texture(SPRITE* sprite, int gfx_index)
{//==========================================================================================================================


	if (sprite == NULL)
	{
		ERROR_set_error("HARDWARE_update_sprite_texture : no texture struct to update! \n");
	}
	else
	{
		GFX* gfx = sprite->gfx;

		int gfx_data_is_file = 1;


		//if the gfx struct has a pointer to indexed data, then its a getCaption and the gfx struct was made dynamically.
		//it will create texture from this indexed data below.
		if (gfx->indexed_gfx_data != NULL)
		{
			//sprite_indexed_gfx_data = gfx->indexed_gfx_data;
			//amount_of_frames_in_file=1;
			gfx_data_is_file = 0;
		}


		int IndexInCachedTextureIDArray = -1;
		IndexInCachedTextureIDArray = gfx->IndexInCachedTextureIDArray;
		if (IndexInCachedTextureIDArray == -1)
		{
			//sprite filename wasnt loaded properly, throw error
			ERROR_set_error("sprite was not found in preloaded textures, fix this!\n");
		}


		//then figure out frame based on the gfx_index, should be very easy here because we have the sprite data sizes
		int frame = 0;
		frame = gfx_index / (gfx->data_size_x * gfx->data_size_y);


		if (IndexInCachedTextureIDArray == -2)
		{
			//this means its a getCaption and it will have a unique texture every time

			//make new texture ID
			GLuint texture_id = HARDWARE_preload_sprite_texture_frame(gfx, frame, IndexInCachedTextureIDArray);

			sprite->texture_id = texture_id;
		}
		else
		{
			//if sprite isnt preloaded, load it
			//if it is a dynamic texture (getText box, etc) load it again from internal data and overwrite the one thats there
			if (


				USED_preloaded_sprite_textures_USED[IndexInCachedTextureIDArray * 8 * 8 + frame] == 0 //it hasnt been preloaded
				||
				gfx_data_is_file == 0
			)
			{
				//load the frame and set the texture id
				sprite->texture_id = HARDWARE_preload_sprite_texture_frame(gfx, frame, IndexInCachedTextureIDArray);
			}


			if (glIsTexture(GLTex_preloaded_sprite_textures[IndexInCachedTextureIDArray * 8 * 8 + frame]) == 0)
			{
				ERROR_set_error("HARDWARE_update_sprite_texture: the texture was created but isnt a texture!\n");
			}

			if (USED_preloaded_sprite_textures_USED[IndexInCachedTextureIDArray * 8 * 8 + frame] == 0)
			{
				ERROR_set_error("HARDWARE_update_sprite_texture: it wasn't marked as used!\n");
			}

			sprite->texture_id = GLTex_preloaded_sprite_textures[IndexInCachedTextureIDArray * 8 * 8 + frame];
		}
	}
}


//==========================================================================================================================
SPRITE* HARDWARE_create_sprite(GFX* gfx, int gfx_index, int layer, float scale, float screen_x, float screen_y, int alpha)//HARDWARE_CreateSpriteExFromGfx
{//==========================================================================================================================


	if (gfx == NULL)
	{
		ERROR_set_error("creating a sprite without graphics, this is bad! \n");
	}


	//create new sprite struct
	SPRITE* sprite = (SPRITE*)malloc(sizeof(SPRITE));

	//find available sprite slot (for z-ordering and rendering)
	int slot = -1;
	int x = 0;
	for (x = 0; x < 256; x++)
		if (HARDWARE_sprites[x] == NULL)
		{
			slot = x;
			x = 256;
			break;
		}

	if (slot == -1)
	{
		ERROR_set_error("ran out of available sprite slots! \n");
	}


	sprite->layer = layer;
	sprite->scale = scale;
	sprite->screen_x = screen_x;
	sprite->screen_y = screen_y;
	sprite->gfx = gfx;

	sprite->texture_id = 0;

	sprite->alpha = alpha;

	sprite->draw_size_x = 0;
	sprite->draw_size_y = 0;


	HARDWARE_update_sprite_texture(sprite, gfx_index);


	//the texture size isnt set until HARDWARE_update_sprite_texture calls HARDWARE_preload_sprite_texture_frame
	sprite->draw_size_x = gfx->content_size_x;
	sprite->draw_size_y = gfx->content_size_y;

	HARDWARE_sprites[slot] = sprite;


	return sprite;
}

//==========================================================================================================================
void HARDWARE_delete_sprite(SPRITE* sprite)//HARDWARE_DeleteSprite
{//==========================================================================================================================


	if (sprite == NULL)
	{
		ERROR_set_error("deleting a sprite twice somewhere, this is bad! \n");
	}

	//this deletes the sprite struct
	//check HARDWARE_sprites and remove it
	int x = 0;
	for (x = 0; x < 256; x++)
		if (HARDWARE_sprites[x] == sprite)HARDWARE_sprites[x] = NULL;


	///should init all the data in the struct, i guess.

	///could check if the gfx texture is volatile and delete it here


	free(sprite);
}


///this should all be done by the npc vbl when it deletes and creates them
///special cases like the getText box sprite movement should just set the sprite->screen_y;

//==========================================================================================================================
void HARDWARE_set_sprite_x(SPRITE* sprite, float screen_x)
{//==========================================================================================================================


	if (sprite == NULL)
	{
		ERROR_set_error("moving a NULL sprite! \n");
		exit(2);
	}
	sprite->screen_x = screen_x;
}

//==========================================================================================================================
void HARDWARE_set_sprite_y(SPRITE* sprite, float screen_y)
{//==========================================================================================================================
	if (sprite == NULL)
	{
		ERROR_set_error("moving a NULL sprite! \n");
		exit(2);
	}
	sprite->screen_y = screen_y;
}

//==========================================================================================================================
void HARDWARE_set_sprite_xy(SPRITE* sprite, float screen_x, float screen_y)
{//==========================================================================================================================
	if (sprite == NULL)
	{
		ERROR_set_error("moving a NULL sprite! \n");
		exit(2);
	}
	sprite->screen_x = screen_x;
	sprite->screen_y = screen_y;
}

//==========================================================================================================================
void HARDWARE_init_gfx_data()
{//==========================================================================================================================


	//-----------------------------
	//load sprite palettes
	//-----------------------------

	GAME_original_SPRITE_PALETTE = (u8*)HARDWARE_load_file("data/sprite/globalspritepalette_SpritePalette.bin");
	GAME_hq2x_SPRITE_PALETTE = (u8*)HARDWARE_load_file("data/sprite/hq2xpalette_SpritePalette.bin");


	//-----------------------------
	//brighten palette
	//-----------------------------

	//HARDWARE_create_brightened_palette(GAME_original_SPRITE_PALETTE,(int*)&GAME_temp_SPRITE_PALETTE,2);


	//-----------------------------
	//enhance colors
	//-----------------------------
	int x = 0;
	for (x = 0; x < 256; x++)
	{
		int r = (GAME_original_SPRITE_PALETTE[x] % 32) * 8;
		int g = ((GAME_original_SPRITE_PALETTE[x] / 32) % 32) * 8;
		int b = (((GAME_original_SPRITE_PALETTE[x] / 32) / 32) % 32) * 8;


		adjust_color(&r, &g, &b);

		HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[x * 3 + 0] = r;
		HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[x * 3 + 1] = g;
		HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[x * 3 + 2] = b;


		//int HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[256*3];
		//int HARDWARE_HQ2X_SPRITE_PALETTE_ENHANCED_RGB[256*3];
	}

	for (x = 0; x < 256; x++)
	{
		int r = (GAME_hq2x_SPRITE_PALETTE[x] % 32) * 8;
		int g = ((GAME_hq2x_SPRITE_PALETTE[x] / 32) % 32) * 8;
		int b = (((GAME_hq2x_SPRITE_PALETTE[x] / 32) / 32) % 32) * 8;


		adjust_color(&r, &g, &b);

		HARDWARE_HQ2X_SPRITE_PALETTE_ENHANCED_RGB[x * 3 + 0] = r;
		HARDWARE_HQ2X_SPRITE_PALETTE_ENHANCED_RGB[x * 3 + 1] = g;
		HARDWARE_HQ2X_SPRITE_PALETTE_ENHANCED_RGB[x * 3 + 2] = b;


		//int HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[256*3];
		//int HARDWARE_HQ2X_SPRITE_PALETTE_ENHANCED_RGB[256*3];
	}

	//-----------------------------
	//set color 1 to black
	//-----------------------------
	HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[1 * 3 + 0] = 0;
	HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[1 * 3 + 1] = 0;
	HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[1 * 3 + 2] = 0;


	//color 16 green
	HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[16 * 3 + 0] = 0;
	HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[16 * 3 + 1] = 255;
	HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[16 * 3 + 2] = 0;

	//color 22 purple
	HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[22 * 3 + 0] = 170;//#8500ff
	HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[22 * 3 + 1] = 0;
	HARDWARE_ORIGINAL_SPRITE_PALETTE_ENHANCED_RGB[22 * 3 + 2] = 220;

	//255 for hq2x for some reason
	HARDWARE_HQ2X_SPRITE_PALETTE_ENHANCED_RGB[255 * 3 + 0] = 0;
	HARDWARE_HQ2X_SPRITE_PALETTE_ENHANCED_RGB[255 * 3 + 1] = 0;
	HARDWARE_HQ2X_SPRITE_PALETTE_ENHANCED_RGB[255 * 3 + 2] = 0;

	//GAME_temp_SPRITE_PALETTE[1]=HARDWARE_RGB(0,0,0);


	//-----------------------------
	//init and getPreload gfx datas
	//-----------------------------

	//int SHADOW=1;
	//int NO_SHADOW = 0;

	//int DONT_PRELOAD=0;
	//int PRELOAD = 1;
}


BobTexture* SpriteManager::actionTexture = nullptr;


SpriteManager::SpriteManager(Engine* g)
{ //=========================================================================================================================

	this->e = g;

	//spriteByIDHashMap = new HashMap<int, Sprite*>();
	//spriteByNameHashMap = new HashMap<string, Sprite*>();

	if (actionTexture == nullptr)
	{
		actionTexture = GLUtils::getTextureFromPNG("data/misc/glowingDot.png");
	}
}


void SpriteManager::update()
{ //=========================================================================================================================


	//for doorknobs and action icons for areas
	actionTextureAnimTicks += (int)getEngine()->engineTicksPassed();
	if (actionTextureAnimTicks > 70)
	{
		actionTextureAnimTicks = 0;
		actionTextureFrame++;
		if (actionTextureFrame > 19)
		{
			actionTextureFrame = 0;
		}
	}


	for (int n = 0; n < screenSpriteList.size(); n++)
	{
		Entity* e = screenSpriteList.get(n);
		e->update();
	}


	//TODO: update sprites here, initialize them from server etc. need to reorganize this better.

	ArrayList<Sprite*>* sprites = spriteByIDHashMap.getAllValues();
	for (int n = 0; n < sprites->size(); n++)
	{
		sprites->get(n)->update();
	}
}

void SpriteManager::renderScreenSprites(RenderOrder layer)
{ //=========================================================================================================================

	if (getEngine()->entityLayerEnabled)
	{
		//screensprites

		for (int n = 0; n < screenSpriteList.size(); n++)
		{
			ScreenSprite* e = screenSpriteList.get(n);

			if (e->getRenderOrder() == layer)
			{
				if (e->shouldDraw())
				{
					e->Entity::render(1.0f);
				}
			}
		}
	}
}

Sprite* SpriteManager::getSpriteAssetByIDOrRequestFromServerIfNotExist(int id)
{ //=========================================================================================================================


	if (id == -1)
	{
		Sprite* s = spriteByIDHashMap.get(id);
		if (s == nullptr)
		{
			s = new Sprite(getEngine());
			s->initializeWithSpriteData(nullptr);
			spriteByNameHashMap.put(s->getName(), s);
			spriteByIDHashMap.put(s->getID(), s);
		}
		return s;
	}


	Sprite* s = spriteByIDHashMap.get(id);
	if (s != nullptr)
	{
		if (s->getInitialized_S() == true)
		{
			return s;
		}
		else
		{
		    s->sendDataRequest(id);
		}
	}
	else
	{
		s = new Sprite(getEngine());
		spriteByIDHashMap.put(id, s);

		s->sendDataRequest(id);
	}


	//String e = "SpriteAsset not found! getSpriteByID():"+id;
	//Console.error(e);
	//log.error(e);

	return nullptr;
}

Sprite* SpriteManager::getSpriteByNameOrRequestFromServerIfNotExist(string spriteAssetName)
{ //=========================================================================================================================

	if (spriteAssetName == "" || spriteAssetName == "" || spriteAssetName.length() == 0)
	{
		spriteAssetName = "none";
	}

	if (spriteAssetName == "none" || spriteAssetName == "Camera")
	{
		Sprite* s = nullptr;

		if(spriteByNameHashMap.containsKey(spriteAssetName))
			s = spriteByNameHashMap.get(spriteAssetName);

		if (s == nullptr)
		{
			s = new Sprite(getEngine());

			SpriteData* d = nullptr;
			if (spriteAssetName == "Camera")
			{
				d = new SpriteData(-1, "Camera", "", 0, 0, 1, false, false, false, false, false, false, false, false, false, false, false, false, false, false, -1, "", 0, 0, 0, "", "");
			}
			if (spriteAssetName == "none")
			{
				d = new SpriteData(-1, "none", "", 0, 0, 1, false, false, false, false, false, false, false, false, false, false, false, false, false, false, -1, "", 0, 0, 0, "", "");
			}

			s->initializeWithSpriteData(d);
			spriteByNameHashMap.put(s->getName(), s);
			spriteByIDHashMap.put(s->getID(), s);
		}


		return s;
	}


	Sprite* s = nullptr;

	if (spriteByNameHashMap.containsKey(spriteAssetName))
		s = spriteByNameHashMap.get(spriteAssetName);

	if (s != nullptr)
	{
		if (s->getInitialized_S() == true)
		{
			return s;
		}
		else
		{
			s->sendDataRequest(spriteAssetName);
		}
	}
	else
	if (s == nullptr)
	{
		s = new Sprite(getEngine());

		spriteByNameHashMap.put(spriteAssetName, s);
		
		s->sendDataRequest(spriteAssetName);
	}





	//String e = "SpriteAsset not found! getSpriteByName():"+spriteAssetName;//this is normal
	//Console.error(e);
	//log.warn(e);

	return nullptr;
}





//=========================================================================================================================
Sprite* SpriteManager::preloadSpriteFromFile(const string& spriteAssetName)
{ //=========================================================================================================================

	//log.info(spriteAssetName);
  //get sprite from hashmap if exists
  //if it doesnt, create sprite, sprite will load what it needs
	Sprite* s = nullptr;


	//log.info("if spriteByNameHashMap.containsKey " + spriteAssetName);
	if (spriteByNameHashMap.containsKey(spriteAssetName))
		s = spriteByNameHashMap.get(spriteAssetName);

	if (s == nullptr)
	{
		//log.info("new Sprite "+ spriteAssetName);
		//TODO: here instead of returning preloaded sprite, could check if file exists, if it does load, else check cache, else check network, else create and load from network?
		s = new Sprite(getEngine());

		s->preloadFromFile(spriteAssetName);



		spriteByNameHashMap.put(s->getName(), s);
		spriteByIDHashMap.put(s->getID(), s);
	}


	return s;
}



//=========================================================================================================================
Sprite* SpriteManager::getSpriteByName(const string& spriteAssetName)
{ //=========================================================================================================================

	Sprite* s = nullptr;

	//if (spriteByNameHashMap.containsKey(spriteAssetName))
		s = spriteByNameHashMap.get(spriteAssetName);

	if (s == nullptr)
	{
		log.error(string("getSpriteByName not found in spriteByNameHashMap:") + spriteAssetName);
	}


	return s;
}
