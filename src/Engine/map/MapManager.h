//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class MapManager : public EnginePart
{
public:
	ArrayList<Map*> mapList;
	HashMap<string, Map*> mapByNameHashMap;//new HashMap<string, Map*>();
	HashMap<int, Map*> mapByIDHashMap;//new HashMap<int, Map*>();

	static Logger log;
	

	Map* currentMap = nullptr;
private:
	Map* lastMap = nullptr;


	//	private final KahluaConverterManager converterManager = new KahluaConverterManager();
	//	private final J2SEPlatform platform = new J2SEPlatform();
	//	private final KahluaTable env = platform.newEnvironment();
	//	private final KahluaThread thread = new KahluaThread(platform, env);
	//	private final LuaCaller caller = new LuaCaller(converterManager);
	//
	//	private final LuaJavaClassExposer exposer = new LuaJavaClassExposer(converterManager, platform, env);

public:
	static bool useThreads;
	static bool generateHQ2XChunks;
	static bool loadTexturesOnDemand;


	//textures mapped to light filenames
	HashMap<string, BobTexture*> lightTextureHashMap;//new HashMap<string, Texture*>();


	//hashtable (threadsafe) mapped to light filename, and boolean array[1] set whether it exists (so multiple threads don't check if file exists at same time)
	HashMap<string, BobBool*> lightTextureFileExistsHashtable;//new HashMap<string, BobBool*>();


	Door* doorEntered = nullptr;
	Door* doorExited = nullptr;

	WarpArea* warpEntered = nullptr;
	WarpArea* warpExited = nullptr;


	float drawAngle = 0; //TODO

	float hue = 1.0f;
	float saturation = 1.0f;
	float brightness = 1.0f;
	float contrast = 1.0f;
	float gamma = 1.0f;
	bool grayscale = false;
	bool effects8Bit = false; //TODO
	bool effectsInverted = false; //TODO
	bool effectsBlackAndWhite = false; //TODO


	MapManager(Engine* g);
	~MapManager();


	virtual void update();





	virtual void render();


	virtual void renderLastMap();


	/// <summary>
	///for drawing any map entities over getText </summary>
	virtual void renderEntities(RenderOrder layer);


	virtual void setFBOEffects();


	virtual void setNonFBOEffects();


	virtual void setEffectsShaderEffects();


	virtual void setTextureRotation();


	virtual void rotateMap(int rotateDegrees);


	virtual void renderDebug();


	virtual bool isDayTime();


	virtual bool isNightTime();


	virtual bool isRaining();


	virtual bool isSnowing();


	virtual bool isWindy();


	virtual bool isFoggy();


	//used to keep track of the camera offset so we can scroll the last map along with the new one
	static float lastMapCameraOffsetX;
	static float lastMapCameraOffsetY;
	static float lastMapScreenX;
	static float lastMapScreenY;


	virtual void fadeOutAndReleaseLastMap();


	virtual void setTransitionOffsets();


	virtual void changeMap(const string& mapName, int mapXPixelsHQ, int mapYPixelsHQ);


	virtual void changeMap(const string& mapName, int mapXPixelsHQ, int mapYPixelsHQ, bool updateGameSave);


	virtual void changeMap(Map* m, int mapXTiles1X, int mapYTiles1X);


	virtual void changeMap(Map* m, Door* door);


	virtual void changeMap(Map* m, Area* area);


	virtual void changeMap(Map* m, WarpArea* area);


	virtual void changeMap(const string& mapName, const string& areaName);


	virtual Map* getMapByIDBlockUntilLoaded(int id);


	virtual Map* getMapByNameBlockUntilLoaded(const string& name);


	virtual void requestMapDataIfNotLoadedYet(const string& name);


	virtual MapState* getMapStateByID(int id);


	virtual Area* getAreaByID(int id);


	virtual Entity* getEntityByID(int id);


	virtual Light* getLightByID(int id);


	virtual Door* getDoorByID(int id);
};

