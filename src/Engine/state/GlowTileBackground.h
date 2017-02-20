//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class GlowTileBackground : public MenuPanel
{
public:

	static Logger log;


	Engine* e;


public:
	class GlowTile
	{
	private:
		GlowTileBackground* outerInstance;

	public:
		GlowTile(GlowTileBackground* outerInstance);

		int tileX = 0;
		int tileY = 0;
		int frame = 0;
		long long ticks = 0; //=1000+Utils.randUpToIncluding(5000);
		bool started = false;
	};

public:
	ArrayList<GlowTile*>* glowTiles = new ArrayList<GlowTile*>();
	ArrayList<BobTexture*>* glowTileFramesTexture = new ArrayList<BobTexture*>();
	BobTexture* bgScrollTexture;
	float bgScrollX = 0;
	float bgScrollY = 0;
	long long ticksPassed = 0;


	int filter = GLUtils::FILTER_LINEAR;


	//must set these in init()
	int tileFrames = 0;
	int numActiveTiles = 0;
	float scale = 0;
	int ticksPerFrame = 0;
	float scrollSpeedTicksMultiplier = 0;


	GlowTileBackground();


	GlowTileBackground(Engine* g);


	virtual void init();


	virtual void cleanup();


	virtual void update() override;


	virtual void render() override;
};

