#include "stdafx.h"
#include <algorithm>
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once


#include "./PathFinder.h"


//Logger TilePath::log = Logger("TilePath");


TilePath::TilePath(PathFinder* outerInstance)
{
	this->outerInstance = outerInstance;
}

int TilePath::getLength()
{
	return (int)pathTiles->size();
}

PathTile* TilePath::getTileForPathIndex(int index)
{
	return static_cast<PathTile*>(pathTiles->at(index));
}

int TilePath::getTileXForPathIndex(int index)
{
	return getTileForPathIndex(index)->tileX;
}

int TilePath::getTileYForPathIndex(int index)
{
	return getTileForPathIndex(index)->tileY;
}

void TilePath::addPathTileToEnd(int x, int y)
{
	pathTiles->push_back(new PathTile(this, x, y));
}

void TilePath::addPathTileToBeginning(int x, int y)
{
	pathTiles->push_front(new PathTile(this, x, y));
}

bool TilePath::doesPathContain(int tileX, int tileY)
{
	return find(pathTiles->begin(), pathTiles->end(), new PathTile(this, tileX, tileY)) != pathTiles->end();
}

PathTile::PathTile(TilePath* outerInstance, int tileX, int tileY) : outerInstance(outerInstance)
{
	this->tileX = tileX;
	this->tileY = tileY;
}

int PathTile::getX()
{
	return tileX;
}

int PathTile::getY()
{
	return tileY;
}

int PathTile::hashCode()
{
	return tileX * tileY;
}

//bool PathTile::equals(void* other)
//{
//   if (dynamic_cast<PathTile*>(other) != nullptr)
//   {
//      PathTile* o = static_cast<PathTile*>(other);
//      return (o->tileX == tileX) && (o->tileY == tileY);
//   }
//
//   return false;
//}


SortedList::SortedList(PathFinder* outerInstance)
{
	this->outerInstance = outerInstance;
}

PotentialTile* SortedList::first()
{
	return list->get(0);
}

void SortedList::clear()
{
	list->clear();
}

void SortedList::addAndSort(PotentialTile* o)
{
	list->add(o);
	sort(list->v.begin(), list->v.end());
}

void SortedList::remove(PotentialTile* o)
{
	list->remove(o);
}

int SortedList::size()
{
	return list->size();
}

bool SortedList::contains(PotentialTile* o)
{
	return find(list->v.begin(), list->v.end(), o) != list->v.end();
}

PotentialTile::PotentialTile(int x, int y)
{ // =========================================================================================================================
	this->x = x;
	this->y = y;
}

int PotentialTile::setParentTile(PotentialTile* parent)
{ // =========================================================================================================================
	depth = parent->depth + 1;
	this->parent = parent;

	return depth;
}

int PotentialTile::compareTo(PotentialTile* o)
{ // =========================================================================================================================

	float f = heuristicCost + cumulativePathCost;
	float of = o->heuristicCost + o->cumulativePathCost;

	if (f < of)
	{
		return -1;
	}
	else if (f > of)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

PathFinder::PathFinder(Entity* e, float middleStartXPixelsHQ, float middleStartYPixelsHQ, float finishXPixelsHQ, float finishYPixelsHQ, int mapWidthTiles1X, int mapHeightTiles1X)
{ // =========================================================================================================================


	this->e = e;

	//int characterWidth = (int)(e->getRight() - e->getLeft());
	//int characterHeight = (int)(e->getBottom() - e->getTop());


	w = mapWidthTiles1X;
	h = mapHeightTiles1X;


	int startTileX = (((int)(floor(middleStartXPixelsHQ))) / 8) / 2;
	int startTileY = (((int)(floor(middleStartYPixelsHQ))) / 8) / 2;
	if (startTileX <= 0)
	{
		startTileX = 1;
	}
	if (startTileX >= w - 1)
	{
		startTileX = w - 2;
	}
	if (startTileY <= 0)
	{
		startTileY = 1;
	}
	if (startTileY >= h - 1)
	{
		startTileY = h - 2;
	}

	int finishTileX = (((int)(floor(finishXPixelsHQ))) / 8) / 2;
	int finishTileY = (((int)(floor(finishYPixelsHQ))) / 8) / 2;
	if (finishTileX <= 0)
	{
		finishTileX = 1;
	}
	if (finishTileX >= w - 1)
	{
		finishTileX = w - 2;
	}
	if (finishTileY <= 0)
	{
		finishTileY = 1;
	}
	if (finishTileY >= h - 1)
	{
		finishTileY = h - 2;
	}

	int slop = 0;


	int origStartTileX = startTileX;
	int origStartTileY = startTileY;

	while (e->checkPathBlockedXY((float)startTileX * 2 * 8 + 8, (float)startTileY * 2 * 8 + 8) == true)
	// ||
	// map().checkHitLayerAndHitSpritesXY((startTileX*2*8)-characterWidth/4,(startTileY*2*8)-characterHeight/4)==true||
	// map().checkHitLayerAndHitSpritesXY((startTileX*2*8)+characterWidth/4,(startTileY*2*8)-characterHeight/4)==true||
	// map().checkHitLayerAndHitSpritesXY((startTileX*2*8)-characterWidth/4,(startTileY*2*8)+characterHeight/4)==true||
	// map().checkHitLayerAndHitSpritesXY((startTileX*2*8)+characterWidth/4,(startTileY*2*8)+characterHeight/4)==true
	{
		if (slop == 0)
		{
			startTileX = origStartTileX;
			startTileY = origStartTileY + 1;
			slop++;
		}
		else if (slop == 1)
		{
			startTileX = origStartTileX - 1;
			startTileY = origStartTileY;
			slop++;
		}
		else if (slop == 2)
		{
			startTileX = origStartTileX;
			startTileY = origStartTileY - 1;
			slop++;
		}
		else if (slop == 3)
		{
			startTileX = origStartTileX + 1;
			startTileY = origStartTileY;
			slop++;
		}
		else if (slop == 4)
		{
			startTileX = origStartTileX + 1;
			startTileY = origStartTileY + 1;
			slop++;
		}
		else if (slop == 5)
		{
			startTileX = origStartTileX + 1;
			startTileY = origStartTileY - 1;
			slop++;
		}
		else if (slop == 6)
		{
			startTileX = origStartTileX - 1;
			startTileY = origStartTileY + 1;
			slop++;
		}
		else if (slop == 7)
		{
			startTileX = origStartTileX - 1;
			startTileY = origStartTileY - 1;
			slop++;
		}
		else if (slop == 8)
		{
			startTileX = origStartTileX;
			startTileY = origStartTileY;
			slop++;
		}
		else if (slop < 16)
		{
			slop++;
			if (finishXPixelsHQ < middleStartXPixelsHQ)
			{
				startTileX--;
			}
			else if (finishXPixelsHQ > middleStartXPixelsHQ)
			{
				startTileX++;
			}

			if (finishYPixelsHQ < middleStartYPixelsHQ)
			{
				startTileY--;
			}
			else if (finishYPixelsHQ > middleStartYPixelsHQ)
			{
				startTileY++;
			}
		}
		else
		{
			return;
		}
	}


	slop = 0;


	int origFinishTileX = finishTileX;
	int origFinishTileY = finishTileY;

	while (e->checkPathBlockedXY((float)finishTileX * 2 * 8 + 8, (float)finishTileY * 2 * 8 + 8) == true)
	// ||
	// map().checkHitLayerAndHitSpritesXY((finishTileX*2*8)-characterWidth/4,(finishTileY*2*8)-characterHeight/4)==true||
	// map().checkHitLayerAndHitSpritesXY((finishTileX*2*8)+characterWidth/4,(finishTileY*2*8)-characterHeight/4)==true||
	// map().checkHitLayerAndHitSpritesXY((finishTileX*2*8)-characterWidth/4,(finishTileY*2*8)+characterHeight/4)==true||
	// map().checkHitLayerAndHitSpritesXY((finishTileX*2*8)+characterWidth/4,(finishTileY*2*8)+characterHeight/4)==true
	{
		if (slop == 0)
		{
			finishTileX = origFinishTileX;
			finishTileY = origFinishTileY + 1;
			slop++;
		}
		else if (slop == 1)
		{
			finishTileX = origFinishTileX - 1;
			finishTileY = origFinishTileY;
			slop++;
		}
		else if (slop == 2)
		{
			finishTileX = origFinishTileX;
			finishTileY = origFinishTileY - 1;
			slop++;
		}
		else if (slop == 3)
		{
			finishTileX = origFinishTileX + 1;
			finishTileY = origFinishTileY;
			slop++;
		}
		else if (slop == 4)
		{
			finishTileX = origFinishTileX + 1;
			finishTileY = origFinishTileY + 1;
			slop++;
		}
		else if (slop == 5)
		{
			finishTileX = origFinishTileX + 1;
			finishTileY = origFinishTileY - 1;
			slop++;
		}
		else if (slop == 6)
		{
			finishTileX = origFinishTileX - 1;
			finishTileY = origFinishTileY + 1;
			slop++;
		}
		else if (slop == 7)
		{
			finishTileX = origFinishTileX - 1;
			finishTileY = origFinishTileY - 1;
			slop++;
		}
		else if (slop == 8)
		{
			finishTileX = origFinishTileX;
			finishTileY = origFinishTileY;
			slop++;
		}
		else if (slop < 16)
		{
			slop++;
			if (finishXPixelsHQ > middleStartXPixelsHQ)
			{
				finishTileX--;
			}
			else if (finishXPixelsHQ < middleStartXPixelsHQ)
			{
				finishTileX++;
			}

			if (finishYPixelsHQ > middleStartYPixelsHQ)
			{
				finishTileY--;
			}
			else if (finishYPixelsHQ < middleStartYPixelsHQ)
			{
				finishTileY++;
			}
		}
		else
		{
			return;
		}
	}

	// System.out.println("Width: "+mapWidth);
	// System.out.println("Height: "+mapHeight);
	// System.out.println("Start: "+startTileX+","+startTileY);
	// System.out.println("End: "+finishTileX+","+finishTileY);


	//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
	//ORIGINAL LINE: checkedTileArray = new boolean[w][h];
	checkedTileArray = new bool[w * h];// = RectangularVectors::ReturnRectangularBoolVector(w, h);


	this->maxSearchDistance = w + h;
	this->allowDiagMovement = false;

	//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
	//ORIGINAL LINE: potentialTiles = new PotentialTile[w][h];
	potentialTiles = RectangularVectors::ReturnRectangularPotentialTileVector(w, h);


	for (int x = 0; x < w; x++)
	{
		potentialTiles->add(new ArrayList<PotentialTile*>());
		for (int y = 0; y < h; y++)
		{
			potentialTiles->get(x)->add(new PotentialTile(x, y));
		}
	}


	path = findPath(startTileX, startTileY, finishTileX, finishTileY);
}

TilePath* PathFinder::findPath(int startTileX, int startTileY, int toTileX, int toTileY)
{ // =========================================================================================================================


	// easy first check, if the destination is blocked, we can't get there
	if (isTileBlocked(toTileX, toTileY))
	{
		return nullptr;
	}


	// initial state for A*. The closed group is empty. Only the starting
	// tile is in the open list and it's cost is zero, i.e. we're already there
	potentialTiles->get(startTileX)->get(startTileY)->cumulativePathCost = 0;
	potentialTiles->get(startTileX)->get(startTileY)->depth = 0;
	blockedPotentialTilesList->clear();
	openPotentialTilesList->clear();
	openPotentialTilesList->addAndSort(potentialTiles->get(startTileX)->get(startTileY));

	potentialTiles->get(toTileX)->get(toTileY)->parent = nullptr;

	// while we haven't found the goal and haven't exceeded our max search depth
	int maxDepth = 0;


	while ((maxDepth < maxSearchDistance) && (openPotentialTilesList->size() != 0))
	{
		// pull out the first node in our open list, this is determined to
		// be the most likely to be the next step based on our heuristic
		PotentialTile* current = openPotentialTilesList->first();
		if (current == potentialTiles->get(toTileX)->get(toTileY))
		{
			break;
		}

		openPotentialTilesList->remove(current);
		blockedPotentialTilesList->add(current);

		// search through all the neighbours of the current node evaluating
		// them as next steps
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				// not a neighbour, its the current tile
				if ((x == 0) && (y == 0))
				{
					continue;
				}

				// if we're not allowing diaganol movement then only
				// one of x or y can be set
				if (!allowDiagMovement)
				{
					if ((x != 0) && (y != 0))
					{
						continue;
					}
				}

				// determine the location of the neighbour and evaluate it
				int xp = x + current->x;
				int yp = y + current->y;

				if (isValidLocation(startTileX, startTileY, xp, yp))
				{
					// the cost to get to this node is cost the current plus the movement
					// cost to reach this node. Note that the heursitic value is only used
					// in the sorted open list
					float nextStepCost = current->cumulativePathCost + getTileTypeCost(current->x, current->y, xp, yp);

					PotentialTile* neighbour = potentialTiles->get(xp)->get(yp);

					setTileChecked(xp, yp);

					// if the new cost we've determined for this node is lower than
					// it has been previously makes sure the node hasn't been discarded. We've
					// determined that there might have been a better path to get to
					// this node so it needs to be re-evaluated
					if (nextStepCost < neighbour->cumulativePathCost)
					{
						if (openPotentialTilesList->contains(neighbour))
						{
							openPotentialTilesList->remove(neighbour);
						}

						if (blockedPotentialTilesList->contains(neighbour))
						{
							blockedPotentialTilesList->remove(neighbour);
						}
					}

					// if the node hasn't already been processed and discarded then
					// reset it's cost to our current cost and add it as a next possible
					// step (i.e. to the open list)
					if (!openPotentialTilesList->contains(neighbour) && !(blockedPotentialTilesList->contains(neighbour)))
					{
						neighbour->cumulativePathCost = nextStepCost;
						neighbour->heuristicCost = (float)getHeuristicCost(xp, yp, toTileX, toTileY);
						maxDepth = max(maxDepth,neighbour->setParentTile(current));
						openPotentialTilesList->addAndSort(neighbour);
					}
				}
			}
		}
	}

	// since we've got an empty open list or we've run out of search
	// there was no path. Just return null
	if (potentialTiles->get(toTileX)->get(toTileY)->parent == nullptr)
	{
		return nullptr;
	}


	// TODO: thread this.


	// At this point we've definitely found a path so we can uses the parent
	// references of the nodes to find out way from the target location back
	// to the start recording the nodes on the way.
	TilePath* path = new TilePath(this);
	PotentialTile* target = potentialTiles->get(toTileX)->get(toTileY);
	while (target != potentialTiles->get(startTileX)->get(startTileY))
	{
		path->addPathTileToBeginning(target->x, target->y);
		target = target->parent;
	}
	path->addPathTileToBeginning(startTileX, startTileY);

	// thats it, we have our path
	return path;
}

bool PathFinder::isTileBlocked(int tileX, int tileY)
{ // =========================================================================================================================

	if (e->checkPathBlockedXY((float)tileX * 8 * 2 + 8, (float)tileY * 8 * 2 + 8) == true)
	// ||
	// map().checkHitLayerAndHitSpritesXY((x-1)*8*2,y*8*2) == true ||
	// map().checkHitLayerAndHitSpritesXY((x+1)*8*2,y*8*2) == true
	// ||
	// map().checkHitLayerAndHitSpritesXY((x*8*2)-characterWidth/4,(y*8*2)-characterHeight/4) == true||
	// map().checkHitLayerAndHitSpritesXY((x*8*2)+characterWidth/4,(y*8*2)-characterHeight/4) == true||
	// map().checkHitLayerAndHitSpritesXY((x*8*2)-characterWidth/4,(y*8*2)+characterHeight/4) == true||
	// map().checkHitLayerAndHitSpritesXY((x*8*2)+characterWidth/4,(y*8*2)+characterHeight/4) == true
	{
		return true;
	}

	return false;
}

int PathFinder::getHeuristicCost(int tileX, int tileY, int endTileX, int endTileY)
{ // =========================================================================================================================
	return minCost * (abs(tileX - endTileX) + abs(tileY - endTileY));
}

int PathFinder::getTileTypeCost(int fromTileX, int fromTileY, int toTileX, int toTileY)
{ // =========================================================================================================================
	// TODO: check if tile is marked as being grass, cement, near a guard rail, etc, and increase cost to avoid those areas unless necessary.

	return 1;
}

void PathFinder::setTileChecked(int tileX, int tileY)
{ // =========================================================================================================================
	checkedTileArray[tileY * w + tileX] = true;
}

bool PathFinder::wasTileChecked(int tileX, int tileY)
{ // =========================================================================================================================
	return checkedTileArray[tileY * w + tileX];
}

bool PathFinder::isValidLocation(int currentTileX, int currentTileY, int checkTileX, int checkTileY)
{ // =========================================================================================================================
	bool invalid = (checkTileX < 0) || (checkTileY < 0) || (checkTileX >= w) || (checkTileY >= h);

	if ((!invalid) && ((currentTileX != checkTileX) || (currentTileY != checkTileY)))
	{
		invalid = isTileBlocked(checkTileX, checkTileY);
	}

	return !invalid;
}

