//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;
#include <deque>



class PotentialTile;
class Comparable;
class TilePath;


class PathTile
{ // =========================================================================================================================
private:
	TilePath* outerInstance;


public:
	int tileX = 0;
	int tileY = 0;


	PathTile(TilePath* outerInstance, int tileX, int tileY);


	virtual int getX();


	virtual int getY();


	virtual int hashCode();


	//virtual bool equals(void* other);
};

// =========================================================================================================================

class TilePath
{ // =========================================================================================================================
private:
	PathFinder* outerInstance;


public:
	deque<PathTile*>* pathTiles;


	TilePath(PathFinder* outerInstance);


	virtual int getLength();


	virtual PathTile* getTileForPathIndex(int index);


	virtual int getTileXForPathIndex(int index);


	virtual int getTileYForPathIndex(int index);


	virtual void addPathTileToEnd(int x, int y);


	virtual void addPathTileToBeginning(int x, int y);


	virtual bool doesPathContain(int tileX, int tileY);

	// =========================================================================================================================
public:
};

class SortedList
{ // =========================================================================================================================
private:
	PathFinder* outerInstance;

public:
	SortedList(PathFinder* outerInstance);

	/// <summary>
	/// The list of elements </summary>
private:
	ArrayList<PotentialTile*>* list = new ArrayList<PotentialTile*>();


	/// <summary>
	/// Retrieve the first element from the list
	/// </summary>
	/// <returns> The first element from the list </returns>
public:
	virtual PotentialTile* first();


	/// <summary>
	/// Empty the list
	/// </summary>
	virtual void clear();


	virtual void addAndSort(PotentialTile* o);


	virtual void remove(PotentialTile* o);


	virtual int size();


	virtual bool contains(PotentialTile* o);
};

class PotentialTile
{ // =========================================================================================================================
public:
	PathFinder* outerInstance;


	/// <summary>
	/// The x coordinate of the node </summary>
	int x = 0;
	/// <summary>
	/// The y coordinate of the node </summary>
	int y = 0;
	/// <summary>
	/// The path cost for this node </summary>
	float cumulativePathCost = 0;
	/// <summary>
	/// The parent of this node, how we reached it in the search </summary>
	PotentialTile* parent;
	/// <summary>
	/// The heuristic cost of this node </summary>
	float heuristicCost = 0;
	/// <summary>
	/// The search depth of this node </summary>
	int depth = 0;


	// =========================================================================================================================
public:
	PotentialTile(int x, int y);


	// =========================================================================================================================
	virtual int setParentTile(PotentialTile* parent);


	/// <seealso cref= Comparable#compareTo(Object) </seealso>
	// =========================================================================================================================
	virtual int compareTo(PotentialTile* o);
};


class PathFinder
{ // =========================================================================================================================


	// =========================================================================================================================
private:


	/// <summary>
	/// A single node in the search graph
	/// </summary>
	// =========================================================================================================================


public:
	TilePath* path;

private:
	ArrayList<PotentialTile*>* blockedPotentialTilesList = new ArrayList<PotentialTile*>();
	SortedList* openPotentialTilesList = new SortedList(this);

	ArrayList<ArrayList<PotentialTile*>*>* potentialTiles = new ArrayList<ArrayList<PotentialTile*>*>();
	bool* checkedTileArray;


	int maxSearchDistance = 0;
	bool allowDiagMovement = false;

public:
	Entity* e;


	int w = 0;
	int h = 0;


	// =========================================================================================================================
	PathFinder(Entity* e, float middleStartXPixelsHQ, float middleStartYPixelsHQ, float finishXPixelsHQ, float finishYPixelsHQ, int mapWidthTiles1X, int mapHeightTiles1X);


	// =========================================================================================================================
	virtual TilePath* findPath(int startTileX, int startTileY, int toTileX, int toTileY);


	// =========================================================================================================================
	virtual bool isTileBlocked(int tileX, int tileY);


private:
	int minCost = 0;
	// =========================================================================================================================
public:
	virtual int getHeuristicCost(int tileX, int tileY, int endTileX, int endTileY);

	// =========================================================================================================================
	virtual int getTileTypeCost(int fromTileX, int fromTileY, int toTileX, int toTileY);


	// =========================================================================================================================
	virtual void setTileChecked(int tileX, int tileY);


	// =========================================================================================================================
	virtual bool wasTileChecked(int tileX, int tileY);


	// =========================================================================================================================
protected:
	virtual bool isValidLocation(int currentTileX, int currentTileY, int checkTileX, int checkTileY);
};

