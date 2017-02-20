//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




//================
//defines
//================


//================
//variables
//================


//================
//prototypes
//================


void HARDWARE_set_sprite_y(SPRITE* sprite, int screen_y);

SPRITE* HARDWARE_create_sprite(GFX* gfx, int gfx_index, int layer, float scale, int screen_x, int screen_y, int alpha);
void HARDWARE_update_sprite_texture(SPRITE* sprite, int gfx_index);
void HARDWARE_set_sprite_xy(SPRITE* sprite, int screen_x, int screen_y);
void HARDWARE_delete_sprite(SPRITE* sprite);
void HARDWARE_load_sprite_palette(int* palette);

void HARDWARE_init_arrays();
void HARDWARE_init_gfx_data();


class SpriteManager : public EnginePart
{
public:

	static Logger log;


	HashMap<int, Sprite*> spriteByIDHashMap;//new HashMap<int, Sprite*>();
	HashMap<string, Sprite*> spriteByNameHashMap;//new HashMap<string, Sprite*>();


	ArrayList<ScreenSprite*> screenSpriteList;


	static BobTexture* actionTexture;// = nullptr;

	int actionTextureFrame = 0;
	int actionTextureAnimTicks = 0;


	SpriteManager(Engine* g);



	virtual void update();


	virtual void renderScreenSprites(RenderOrder layer);


	//
	//	
	//	Entity delete_entity(Entity e)
	//	{
	//


	//DONE: if this is a random entity with a custom texture, delete the texture.


	//if it is a normal entity, its texture is still stored in graphics memory, referenced by the spriteAsset.
	//next time that entity is created, its texture already exists.
	//TODO: if this becomes a problem and we start filling up the VRAM, we can unload these textures. in fact, might as well, it's not that expensive to load them again.
	//just need to set the spriteAsset texture to null after releasing it, the MD5 is still stored and it doesn't need the server call again.


	/*
   
	if(e!=null)
	{
   
	   //if it's the first one, make the next one the first one.
	   if(e==first_NPC)
	   {
	      //if it's the only one, then entity.next will be null and this will set first_NPC to null
	      //otherwise it makes the next one the first one
	      first_NPC = entity.next;
   
	   }
	   else //connect the chain before and after this one
	   {
   
	      Entity current_entity = first_NPC;
   
	      //find the one that points to this entity (directly before it)
	      while(current_entity.next!=entity)
	      {
	         current_entity = (Entity )current_entity.next;
	      }
   
	      //set it to point to the one after this one
	      //if this one is the last one it will point to null, so this will just set the second to last one to null.
	      current_entity.next = entity.next;
	   }
   
	   if(entity.sprite!=null)HARDWARE_delete_sprite(entity.sprite);
	   entity.sprite=null;
   
	   stop_chasing(entitypp);
	   stop_avoiding(entitypp);
	   stop_following(entitypp);
	   stop_pulling_against(entitypp);
   
	   //if it has an external pointer (it should) then set that pointer to null
	   if(entity.entitypp!=null)
	   {
	      //set the external pointer to null
	      if(*(entity.entitypp)!=null)
	      {
	         *(entity.entitypp)=null;
	      }
   
	      //set the internal pointer to that pointer to null (dont really need to do this)
	      entity.entitypp=null;
	   }
   
	   free(entity);
	}
   
	*/
	//		return null;
	//	}
	//


	//DONE: maybe have entities not controlled by pointers, but by getText
	//make_entity("yuu",x,y);
	//delete_entity("yuu");
	//set_var("yuu",3);

	//
	//	
	//	void delete_all_entitys()
	//	{

	/*
	if(first_NPC!=null)
	{
   
	   Entity current_entity = first_NPC;
   
	   while(current_entity.next!=null)
	   {
	      Entity temp_entity = current_entity;
	      current_entity = (Entity )current_entity.next;
   
	      if(temp_entity!=first_NPC)delete_entity(&temp_entity);
	   }
	   if(current_entity!=first_NPC)delete_entity(&current_entity);
	}
   
	delete_chase_structs();
	delete_follow_structs();
	delete_avoid_structs();
	delete_pull_againster_structs();
	*/
	//	}
	//
	//
	//	
	//	void pause()
	//	{

	//just deletes all the sprites
	/*
	   if(first_NPC==null)return;
   
	   Entity current_entity = first_NPC;
	   int stop=0;
	   while(stop==0)
	   {
	      if(current_entity.sprite!=null)HARDWARE_delete_sprite(current_entity.sprite);
	      current_entity.sprite=null;
   
   
	      if(current_entity.next!=null)current_entity = (Entity )current_entity.next; else stop=1;
	   }
	   */

	//	}
	//
	//	
	//	void unpause()
	//	{
	//
	//
	//	}


	virtual Sprite* getSpriteAssetByIDOrRequestFromServerIfNotExist(int id);


	virtual Sprite* getSpriteByNameOrRequestFromServerIfNotExist(string spriteAssetName);
	Sprite * preloadSpriteFromFile(const string & spriteAssetName);
	Sprite * getSpriteByName(const string & spriteAssetName);
};

