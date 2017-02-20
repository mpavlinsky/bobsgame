//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



class MapStateData;
class EventData;
class DoorData;



class MapData : public AssetData
{
public:
	static int MAP_GROUND_LAYER;
	static int MAP_GROUND_DETAIL_LAYER;
	static int MAP_SHADER_LAYER;
	static int MAP_GROUND_SHADOW_LAYER;

	static int MAP_OBJECT_LAYER;
	static int MAP_OBJECT_DETAIL_LAYER;
	static int MAP_OBJECT_SHADOW_LAYER;

	static int MAP_ENTITY_LAYER;
	static int MAP_DOOR_LAYER;

	//TODO: need a shadow layer here that affects sprite but not overlayer

	static int MAP_ABOVE_LAYER;
	static int MAP_ABOVE_DETAIL_LAYER;
	static int MAP_SPRITE_SHADOW_LAYER;

	static int MAP_CAMERA_BOUNDS_LAYER;
	static int MAP_HIT_LAYER;


	static int MAP_LIGHT_LAYER;
	static int MAP_AREA_LAYER;
	static int MAP_LIGHT_MASK_LAYER;


	static int MAP_ENTITY_LAYER_ABOVE; //not a real layer, just used to draw entity layer with priority

	static int layers;


	static bool isTileLayer(int l);


	static bool isTransparentLayer(int l);


	//DONE clean up layers in mapAsset and Entity to make more sense in game.render()

public:


	/*
	   ----------------------MAP
	   currentMap.render(RenderOrder.GROUND);//layer 0 1 3s 4 5 6s
	
	   currentMap.renderEntities(RenderOrder.GROUND);
	   getCaptionManager()->render(RenderOrder.GROUND);
	
	   currentMap.render(RenderOrder.ABOVE); //includes above shadows, layer 9 - layers 7,8,9
	   currentMap.renderEntities(RenderOrder.ABOVE);
	   currentMap.renderEntities(RenderOrder.ABOVE_TOP);//birds? //TODO should have something OVER lights as well!
	   CinematicsManager().render(RenderOrder.ABOVE);//screen overlay under lights
	
	   getGameEngine()->stadiumScreen.render();
	
	   //LIGHTS HERE
	
	   ---------------------------ENGINE
	   getSpriteManager()->renderScreenSprites(RenderOrder.ABOVE);
	
	   getCaptionManager()->render(RenderOrder.ABOVE);
	
	   getSpriteManager()->renderScreenSprites(RenderOrder.ABOVE_TOP);
	
	   getCaptionManager()->render(RenderOrder.ABOVE_TOP);
	
	   CinematicsManager().render(RenderOrder.ABOVE_TOP);
	
	   getTextManager()->render();
	
	   getMapManager()->renderEntities(RenderOrder.OVER_TEXT);
	
	   getSpriteManager()->renderScreenSprites(RenderOrder.OVER_TEXT);//screensprites
	
	   getCaptionManager()->render(RenderOrder.OVER_TEXT);
	
	   getMapManager()->renderDebug();
	
	   getSpriteManager()->renderScreenSprites(RenderOrder.OVER_GUI);
	
	   getCaptionManager()->render(RenderOrder.OVER_GUI);
	
	
	   ---------------GAME ENGINE
	   nD
	   StatusBar
	   GUI
	
	
	*/

	//	public static final int SPRITE_LAYER_DEBUG_INFO = -2;
	//	public static final int SPRITE_LAYER_DEBUG_BOXES = -1;
	//
	//
	//	public static final int SPRITE_LAYER_UNDERNEATH_MAP = 0;
	//	public static final int MAP_LAYER_GROUND = 0;
	//	public static final int SPRITE_LAYER_GROUND = 1;
	//	public static final int MAP_LAYER_ABOVE = 1;
	//	public static final int SPRITE_LAYER_ABOVE_OVERLAYER = 2;
	//	public static final int SPRITE_LAYER_ABOVE_TEXT = 3;


private:
	
	string mapNote = "";


	
	int widthTiles1X = 40; //1x tile width
	
	int heightTiles1X = 30; //1x tile width
	//	public int getWidthPixels1X = 240; //1x pixel width
	//	public int getHeightPixels1X = 160; //1x pixel width
	//	public int widthTilesHQ2X = 60; //hq2x tile width
	//	public int heightTilesHQ2X = 40; //hq2x tile width
	//	public int widthPixelsHQ2X = 480; //hq2x pixel width
	//	public int heightPixelsHQ2X = 320; //hq2x pixel width

	
	int maxRandoms = 10;
	
	bool isOutside = false;
	
	bool preload = false;

	
	string groundLayerMD5 = "";
	
	string groundObjectsMD5 = "";
	
	string groundShadowMD5 = "";
	
	string objectsMD5 = "";
	
	string objects2MD5 = "";
	
	string objectShadowMD5 = "";
	
	string aboveMD5 = "";
	
	string above2MD5 = "";
	
	string spriteShadowMD5 = "";
	
	string groundShaderMD5 = "";
	
	string cameraBoundsMD5 = "";
	
	string hitBoundsMD5 = "";
	
	string lightMaskMD5 = "";
	
	string paletteMD5 = "";
	
	string tilesMD5 = "";


	//these are ASSET lists only populated with objectDatas to convert into JSON and fill the regular Map lists at runtime with.
	
	ArrayList<MapStateData*>* stateDataList = new ArrayList<MapStateData*>();
	
	ArrayList<EventData*>* eventDataList = new ArrayList<EventData*>();
	
	ArrayList<DoorData*>* doorDataList = new ArrayList<DoorData*>();


public:
	MapData();


	MapData(int id, const string& name, int widthTiles1X, int heightTiles1X);


	static MapData* fromBase64ZippedJSON(const string& b64);


	static MapData* fromJSON(const string& json);


	virtual string getTYPEIDString();


	virtual int getWidthTiles1X();
	virtual int getHeightTiles1X();


	virtual int getMaxRandoms();
	virtual bool getIsOutside();
	virtual bool getPreload();

	virtual string getMapNote();

	virtual string getGroundLayerMD5();
	virtual string getGroundObjectsMD5();
	virtual string getGroundShadowMD5();
	virtual string getObjectsMD5();
	virtual string getObjects2MD5();
	virtual string getObjectShadowMD5();
	virtual string getAboveMD5();
	virtual string getAbove2MD5();
	virtual string getSpriteShadowMD5();
	virtual string getGroundShaderMD5();
	virtual string getCameraBoundsMD5();
	virtual string getHitBoundsMD5();
	virtual string getLightMaskMD5();
	virtual string getPaletteMD5();
	virtual string getTilesMD5();


	virtual int getWidthPixelsHQ();
	virtual int getHeightPixelsHQ();


	virtual ArrayList<MapStateData*>* getStateDataList();
	virtual ArrayList<EventData*>* getEventDataList();
	virtual ArrayList<DoorData*>* getDoorDataList();


	virtual void setGroundLayerMD5(const string& s);
	virtual void setGroundObjectsMD5(const string& s);
	virtual void setGroundShadowMD5(const string& s);
	virtual void setObjectsMD5(const string& s);
	virtual void setObjects2MD5(const string& s);
	virtual void setObjectShadowMD5(const string& s);
	virtual void setAboveMD5(const string& s);
	virtual void setAbove2MD5(const string& s);
	virtual void setSpriteShadowMD5(const string& s);
	virtual void setGroundShaderMD5(const string& s);
	virtual void setCameraBoundsMD5(const string& s);
	virtual void setHitBoundsMD5(const string& s);
	virtual void setLightMaskMD5(const string& s);
	virtual void setPaletteMD5(const string& s);
	virtual void setTilesMD5(const string& s);


	virtual void setMapNote(const string& s);

	virtual void setWidthTiles1X(int s);
	virtual void setHeightTiles1X(int s);


	virtual void setMaxRandoms(int s);
	virtual void setIsOutside(bool s);
	virtual void setPreload(bool s);
};

