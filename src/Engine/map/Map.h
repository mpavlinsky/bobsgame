//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




//import com.bobsgame.server.BGSharedNetworkObjects.MapDataMD5sObject;

class MapState;
class WarpArea;


class Map : public EnginePart
{
public:
	static Logger log;


	MapState* currentState = nullptr;
	bool randomSpawnEnabled = true;


	ArrayList<MapState*> stateList;
	ArrayList<int> mapEventIDList;


	float lastKnownScreenX = 0;
	float lastKnownScreenY = 0;


	float alpha = 1.0f;


	//this is a ArrayList of ArrayLists of sorted lights per layer. this is filled in on map first load.
	ArrayList<ArrayList<Light*>*> sortedLightsLayers;


	//these are entities that exist in this map
	ArrayList<Entity*> activeEntityList;
	//this gets filled in once per frame with entities from entityList that are on the screen
	ArrayList<Entity*> drawList;
	//that gets sorted into zList which is drawn in sequence.
	ArrayList<Entity*> zList;

	//door/warp list
	ArrayList<Door*> doorList;
	ArrayList<WarpArea*> warpAreaList;


	int* hitLayer = nullptr;
	int* cameraLayer = nullptr;
	int* groundShaderLayer = nullptr;
	int* lightMaskLayer = nullptr;


	HashMap<int,BobTexture*> chunkTexture;//= new HashMap<int, Texture*>();
	bool* chunkPNGFileExists = nullptr;
	bool* hq2xChunkPNGFileExists = nullptr;
	bool* usingHQ2XTexture = nullptr;

	int* tilesetIntArray = nullptr;
	u8* paletteRGBByteArray = nullptr;


	const static int chunkSizePixelsHQ2X = 512;
	const static int chunkSizePixels1X = chunkSizePixelsHQ2X / 2;
	const static int chunkSizeTiles1X = chunkSizePixels1X / 8;


	//static ExecutorService* generatePNGExecutorService;
	//static ExecutorService* generateLightPNGExecutorService;
	//public ExecutorService generateHQ2XPNGExecutorService = null;


	int chunkTexturesLoaded = 0;

	int maxHq2xChunkPNGThreadsCreated = 0;
	int hq2xChunkPNGThreadsCreated = 0;

	int maxChunkPNGThreadsCreated = 0;
	int chunkPNGThreadsCreated = 0;

	int maxLightPNGThreadsCreated = 0;
	int lightPNGThreadsCreated = 0;

	ConsoleText* texturesLoadedDebugText = nullptr;
	ConsoleText* hq2xChunkPNGThreadsDebugText = nullptr;
	ConsoleText* chunkPNGThreadsDebugText = nullptr;
	ConsoleText* lightPNGThreadsDebugText = nullptr;


	int chunksWidth = 0;
	int chunksHeight = 0;


	bool startedMissingChunkPNGThreads = false;
	bool startedMissingLightPNGThreads = false;
	bool startedMissingHQ2XChunkPNGThreads = false;

	bool allChunkPNGsLoadedAsTextures = false;
	bool allLightsLoadedAsTextures = false;
	bool allHQ2XChunkPNGsLoadedAsTextures = false;

	bool utilityLayersLoaded = false;

	bool miniMapGenerated = false;

	long long lastTimeMD5sRequested = 0;


	Notification* generatingAreaNotification = nullptr;


	bool addedEntitiesAndCharactersFromCurrentStateToActiveEntityList = false;

	bool eventsAllLoadedFromServer = false;


private:
	MapData* data = nullptr;


public:
	Map();
	Map(Engine* g, MapData* mapData);
	void initMap(Engine* g, MapData* mapData);


	virtual Entity* getEntityByName(const string& name);

	virtual Character* getCharacterByName(const string& name);


	virtual Light* getLightByName(const string& name);


	virtual Area* getAreaOrWarpAreaByName(string name);


	virtual Area* getAreaOrWarpAreaByTYPEID(string typeID);

	virtual Door* getDoorByTYPEID(const string& typeID);

	virtual Door* getDoorByName(const string& name);

	//public MapState getStateByName(String name){return getMapStateByName(name);}

	virtual MapState* getMapStateByName(const string& name);


	virtual MapState* getMapStateByID(int id);


	virtual ArrayList<string>* getListOfRandomPointsOfInterestTYPEIDs();


	//public Tile getTileByName(String name)
	//{
	//return tileHashtable.get(name);
	//}


	virtual void fadeIn();


	virtual void fadeOut();


	virtual void loadMapState(MapState* s);


private:
	long long lastLoadEventRequestTime = 0;

public:
	virtual void update();


	virtual void updateLoadingStatus();


	virtual void updateEntities();


	virtual void updateDoors();


	virtual void updateAreas();


	virtual void updateWarpAreas();


	virtual void updateLights();


	virtual void zOrderEntities();


	virtual void sortLightLayers();


	bool defaultDisableClip = false;
	bool defaultDisableFloorOffset = false;


	virtual void render(RenderOrder renderOrder);


	virtual void render(RenderOrder renderOrder, bool disableClip);


	virtual void render(RenderOrder renderOrder, bool disableClip, bool disableFloorOffset);


	virtual void renderEntities(RenderOrder layer);


	virtual void renderAllLightsUnsorted();


	virtual void renderAreaActionIcons();


	virtual void renderChunkBoxes();

	virtual void renderHitLayer();


	virtual void renderLightBoxes();


	virtual void renderAreaDebugBoxes();


	virtual void renderAreaDebugInfo();


	virtual void renderWarpAreaDebugBoxes();


	virtual void renderWarpAreaDebugInfo();


	//
	//	
	//	public void run()
	//	{
	//		//for map script use
	//
	//
	//	}
	//	
	//	public void load()
	//	{
	//		//for map script use
	//	}
	//
	//	
	//	public void unload()
	//	{
	//		//for map script use
	//	}


	virtual void loadUtilityLayers();


	virtual void saveDataToCache(int* intArrayAllLayers, int* tiles, u8* pal);


	virtual void unloadArea(const string& s);

	virtual void unloadLight(const string& s);

	virtual void unloadMapEntity(const string& s);


	virtual void releaseAllTextures();


	/// <summary>
	/// Returns the position of the upper left of the screen relative to the map, in HQ2X equivalent pixels.
	/// If the camera is left of the map, it is negative.
	/// </summary>
	virtual float mapCamX();


	/// <summary>
	/// Returns the position of the upper left of the screen relative to the map, in HQ2X equivalent pixels.
	/// If the camera is left of the map, it is negative.
	/// </summary>
	virtual float mapCamY();


	virtual float getScreenX(float mapX, float width);


	virtual float getScreenY(float mapY, float height);


	virtual float screenX();

	virtual float screenY();


	virtual void updateLastKnownScreenXYBasedOnCamera();


	virtual bool getHitLayerValueAtXYTile1X(int xTile1X, int yTile1X);


	virtual bool getHitLayerValueAtXYPixels(float mapXPixelsHQ, float mapYPixelsHQ);


	virtual int getCameraBoundsFXLayerAtXYTile1X(int xTile1X, int yTile1X);


	virtual int getCameraBoundsFXLayerAtXYPixels(float mapXPixelsHQ, float mapYPixelsHQ);


	virtual bool isXYWithinScreenByAmt(float x, float y, int amt);


	virtual bool isXYXYWithinScreenByAmount(float x, float y, float x2, float y2, float amt);


	virtual bool isXYWithinScreen(float x, float y);


	//The following method was originally marked 'synchronized':
	virtual BobTexture* getChunkTexture(int index);

	//The following method was originally marked 'synchronized':
	virtual void setChunkTexture(int index, BobTexture* t);


	//The following method was originally marked 'synchronized':
	virtual void releaseChunkTexture(int index);


	//The following method was originally marked 'synchronized':
	virtual bool getChunkPNGFileExists(int index);

	//The following method was originally marked 'synchronized':
	virtual void setChunkPNGFileExists_S(int index, bool done);


	//The following method was originally marked 'synchronized':
	virtual bool getHQ2XChunkPNGFileExists(int index);

	//The following method was originally marked 'synchronized':
	virtual void setHQ2XChunkFileExists_S(int index, bool done);


	//The following method was originally marked 'synchronized':
	virtual void incrementChunkTexturesLoaded();

	//The following method was originally marked 'synchronized':
	virtual void decrementChunkTexturesLoaded();

	virtual bool loadChunkTexturesFromCachePNGs();


	virtual bool loadLightTexturesFromCachePNGs();


	virtual bool loadHQ2XTexturesFromCachePNGs();


	//The following method was originally marked 'synchronized':
	virtual void incrementChunkPNGThreadsCreated();


	//The following method was originally marked 'synchronized':
	virtual void decrementChunkPNGThreadsCreated_S();


	virtual void startThreadsForMissingChunkPNGs();


	//The following method was originally marked 'synchronized':
	virtual void incrementLightPNGThreadsCreated();


	//The following method was originally marked 'synchronized':
	virtual void decrementLightPNGThreadsCreated_S();


	virtual void startThreadsForMissingLightPNGs();


	//The following method was originally marked 'synchronized':
	virtual void incrementHQ2XChunkPNGThreadsCreated();


	//The following method was originally marked 'synchronized':
	virtual void decrementHQ2XChunkPNGThreadsCreated();


	virtual void startThreadsForMissingHQ2XChunkPNGs();


	virtual void createChunkTexturePNG_S(int chunkLayer, int chunkX, int chunkY, int chunkIndex, int* tilesetIntArray, u8* paletteRGBByteArray);


	/// <summary>
	/// returns false if no image is needed
	/// </summary>
	virtual bool drawTileLayerIntoBufferedImage(const string& layerFileName, BufferedImage* chunkImage, BufferedImage* chunkImageBorder, int chunkX, int chunkY, int* layerChunkBuffer, bool shadowLayer, int* tilesetIntArray, u8* paletteRGBByteArray);


	virtual void createHQ2XTexturePNG_THREAD(int chunkX, int chunkY);


	virtual void antialiasBufferedImage(BufferedImage* bufferedImage);

	virtual void setHQ2XAlphaFromOriginal(BufferedImage* hq2xBufferedImage, BufferedImage* bufferedImage);


	virtual void addEntitiesAndCharactersFromCurrentStateToActiveEntityList();


	virtual void clearActiveEntityList();


	virtual bool isAnyoneOverlappingXY(float x, float y);

	virtual bool isAnyoneOverlappingXYXY(float x, float y, float x2, float y2);


	virtual bool isAnyRandomCharacterTryingToGoToXY(float x, float y);


	virtual int* findOpenSpaceInArea(Area* a, int w, int h);


	virtual bool isAnyCharacterTouchingArea(Area* a);


	virtual bool isAnyEntityTouchingArea(Area* a);


	virtual ArrayList<Entity*>* getAllEntitiesTouchingArea(Area* a);


	virtual ArrayList<Entity*>* getAllEntitiesPlayerIsTouching();


	virtual bool isAnyoneTryingToGoToArea(Area* a);


	virtual bool isAnyEntityUsingSpriteAsset(Sprite* s);


	virtual ArrayList<Entity*>* getAllEntitiesUsingSpriteAsset(Sprite* s);


	virtual Entity* createEntity(Map* map, const string& spriteName, Sprite* spriteAsset, float mapX, float mapY); // SIZE X AND Y ARE ACTUAL Entity HEIGHT AND WIDTH NOT SPRITE SIZE.. X AND Y ARE UPPER LEFT CORNER NOT FEET


	virtual Entity* createEntityFeetAtXY(Map* map, const string& spriteName, Sprite* sprite, float mapX, float mapY); // SIZE X AND Y ARE ACTUAL Entity HEIGHT AND WIDTH NOT SPRITE SIZE,X AND Y ARE FEET PLACEMENT


	virtual Entity* createEntityIfWithinRangeElseDelete_MUST_USE_RETURNVAL(Map* map, Entity* e, const string& spriteName, Sprite* sprite, float mapX, float mapY, int amt);


	virtual Entity* createEntityAtArea(Map* map, const string& spriteName, Sprite* spriteAsset, Area* a);


	virtual MapData* getData();


	virtual int getID();
	virtual string getName();
	virtual string getMapNote();

	virtual int getWidthTiles1X();
	virtual int getHeightTiles1X();

	virtual int getWidthPixelsHQ();
	virtual int getHeightPixelsHQ();


	virtual int getMaxRandoms();
	virtual bool getIsOutside();

	virtual string getTYPEIDString();

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

	//	public Vector<MapStateData> getStateDataList(){return getData().getStateDataList();}
	//	public Vector<EventData> getEventDataList(){return getData().getEventDataList();}
	//	public Vector<DoorData> getDoorDataList(){return getData().getDoorDataList();}


	//set


	//	public void setWidthTiles(int s){getData().setWidthTiles1X(s);}
	//	public void setHeightTiles(int s){getData().setHeightTiles1X(s);}
	//
	//	public void setID(int s){getData().setID(s);}
	//	public void setMapNote(String s){getData().setMapNote(s);}
	//
	//	public void setMaxRandoms(int s){getData().setMaxRandoms(s);}
	//	public void setIsOutside(boolean s){getData().setIsOutside(s);}
	//

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
};

