#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------




Logger Piece::log = Logger("Piece");

PieceType* PieceType::emptyPieceType = new PieceType();
//=========================================================================================================================
bool PieceType::operator==(const PieceType& rhs) const
{//=========================================================================================================================
	return
		uuid == rhs.uuid
//		&& numBlocks == rhs.numBlocks
//		&& lastRotation == rhs.lastRotation
//		&& color == rhs.color
//		&& rotationSet == rhs.rotationSet
//		&& frequencySpecialPieceTypeOnceEveryNPieces == rhs.frequencySpecialPieceTypeOnceEveryNPieces
//		&& randomSpecialPieceChanceOneOutOf == rhs.randomSpecialPieceChanceOneOutOf
//		&& flashingSpecialType == rhs.flashingSpecialType
//		&& clearEveryRowPieceIsOnIfAnySingleRowCleared == rhs.clearEveryRowPieceIsOnIfAnySingleRowCleared
//		&& turnBackToNormalPieceAfterNPiecesLock == rhs.turnBackToNormalPieceAfterNPiecesLock
//		&& fadeOutOnceSetInsteadOfAddedToGrid == rhs.fadeOutOnceSetInsteadOfAddedToGrid
//
//		&& useAsNormalPiece == rhs.useAsNormalPiece
//		&& useAsGarbagePiece == rhs.useAsGarbagePiece
//		&& useAsPlayingFieldFillerPiece == rhs.useAsPlayingFieldFillerPiece
//		&& disallowAsFirstPiece == rhs.disallowAsFirstPiece
//
//		&& spriteName == rhs.spriteName
//		&& bombPiece == rhs.bombPiece
//		&& weightPiece == rhs.weightPiece
//		&& pieceRemovalShooterPiece == rhs.pieceRemovalShooterPiece
//		&& pieceShooterPiece == rhs.pieceShooterPiece
//		&& overrideBlockType == rhs.overrideBlockType
		;
}
//=========================================================================================================================
bool PieceType::operator!=(const PieceType& rhs) const
{//=========================================================================================================================
	return
		(*this == rhs) == false
		;
}

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>


template void PieceType::serialize<boost::archive::xml_oarchive>(boost::archive::xml_oarchive &ar, const unsigned int);
template void PieceType::serialize<boost::archive::xml_iarchive>(boost::archive::xml_iarchive &ar, const unsigned int);

//=========================================================================================================================
template <typename Archive>
void PieceType::serialize(Archive & ar, const unsigned int version)
{//=========================================================================================================================
    
    ar & BOOST_SERIALIZATION_NVP(name);
    //ar & BOOST_SERIALIZATION_NVP(numBlocks);
    //ar & BOOST_SERIALIZATION_NVP(lastRotation);
    
    
    //ar & BOOST_SERIALIZATION_NVP(color);
	importExport_color = BobColor();
    if (color != nullptr && color->name!="" && color->name!="empty")
    {
        importExport_color = *color;

		//boost::uuids::random_generator generator;
		//importExport_color.uuid = to_string(generator());
//		importExport_color.name = color->name;
//		importExport_color.r = color->r;
//		importExport_color.g = color->g;
//		importExport_color.b = color->b;
//		importExport_color.a = color->a;

    }
    ar & BOOST_SERIALIZATION_NVP(importExport_color);
    color = nullptr;
	if (importExport_color.name != "" && importExport_color.name != "empty")
	{
		color = BobColor::getColorByName(importExport_color.name);
	}
    importExport_color = BobColor();
    
    
    
    ar & BOOST_SERIALIZATION_NVP(rotationSet);
    
    ar & BOOST_SERIALIZATION_NVP(frequencySpecialPieceTypeOnceEveryNPieces);
    ar & BOOST_SERIALIZATION_NVP(randomSpecialPieceChanceOneOutOf);
    ar & BOOST_SERIALIZATION_NVP(flashingSpecialType);
    ar & BOOST_SERIALIZATION_NVP(clearEveryRowPieceIsOnIfAnySingleRowCleared);
    ar & BOOST_SERIALIZATION_NVP(turnBackToNormalPieceAfterNPiecesLock);
    ar & BOOST_SERIALIZATION_NVP(fadeOutOnceSetInsteadOfAddedToGrid);
    
    ar & BOOST_SERIALIZATION_NVP(useAsNormalPiece);
    ar & BOOST_SERIALIZATION_NVP(useAsGarbagePiece);
    ar & BOOST_SERIALIZATION_NVP(useAsPlayingFieldFillerPiece);
    ar & BOOST_SERIALIZATION_NVP(disallowAsFirstPiece);
    
    ar & BOOST_SERIALIZATION_NVP(spriteName);
    
    ar & BOOST_SERIALIZATION_NVP(bombPiece);
    ar & BOOST_SERIALIZATION_NVP(weightPiece);
    ar & BOOST_SERIALIZATION_NVP(pieceRemovalShooterPiece);
    ar & BOOST_SERIALIZATION_NVP(pieceShooterPiece);
    

	if (version == 0)
	{
		ArrayList<BlockType> importExport_overrideBlockTypes;
		ar & BOOST_SERIALIZATION_NVP(importExport_overrideBlockTypes);
		overrideBlockTypes_DEPRECATED.clear();
		{
			for (int i = 0; i < importExport_overrideBlockTypes.size(); i++)
			{
				BlockType b = importExport_overrideBlockTypes.get(i);
				BlockType *bp = new BlockType();
				*bp = b;
				overrideBlockTypes_DEPRECATED.add(bp);
			}
		}
		importExport_overrideBlockTypes.clear();
	}
	else
	{
		ar & BOOST_SERIALIZATION_NVP(overrideBlockTypes_UUID);
	}

	if(version>0)
	{
		ar & BOOST_SERIALIZATION_NVP(uuid);
	}
}


//=========================================================================================================================
Piece::Piece(GameLogic* gameInstance, Grid* grid, PieceType *pieceType, ArrayList<BlockType*> &blockTypes)
{//=========================================================================================================================

	this->game = gameInstance;

	this->grid = grid;
	this->pieceType = pieceType;

	int maxNumBlocks = 0;
	for(int i=0;i<pieceType->rotationSet.size();i++)
	{
		maxNumBlocks = max(maxNumBlocks, pieceType->rotationSet.get(i)->blockOffsets.size());
	}

	if (pieceType->overrideBlockTypes_UUID.size()>0)
	{
		ArrayList<BlockType*> overrideBlockTypes;
		for(int i=0;i<pieceType->overrideBlockTypes_UUID.size();i++)
		{
			overrideBlockTypes.add(gameInstance->currentGameType->getBlockTypeByUUID(pieceType->overrideBlockTypes_UUID.get(i)));
		}

		for (int b = 0; b < maxNumBlocks; b++)
		{
			blocks.add(new Block(gameInstance, grid, this, grid->getRandomBlockTypeDisregardingSpecialFrequency(overrideBlockTypes)));
		}
	}
	else
	{
		for (int b = 0; b < maxNumBlocks; b++)
		{
			blocks.add(new Block(gameInstance, grid, this, grid->getRandomBlockType(blockTypes)));
		}
	}

	setRotation(0);


	initBlocks();
}


//=========================================================================================================================
Piece::Piece(GameLogic* gameInstance, Grid* grid, PieceType *pieceType, BlockType *blockType)
{//=========================================================================================================================


	this->game = gameInstance;

	//only used for cursors for now
	this->grid = grid;
	this->pieceType = pieceType;

	if (pieceType->overrideBlockTypes_UUID.size()>0)
	{
		ArrayList<BlockType*> overrideBlockTypes;
		for (int i = 0; i<pieceType->overrideBlockTypes_UUID.size(); i++)
		{
			overrideBlockTypes.add(gameInstance->currentGameType->getBlockTypeByUUID(pieceType->overrideBlockTypes_UUID.get(i)));
		}

		blockType = grid->getRandomBlockTypeDisregardingSpecialFrequency(overrideBlockTypes);
	}

	int maxNumBlocks = 0;
	for (int i = 0; i<pieceType->rotationSet.size(); i++)
	{
		maxNumBlocks = max(maxNumBlocks, pieceType->rotationSet.get(i)->blockOffsets.size());
	}

	for (int b = 0; b < maxNumBlocks; b++)
	{
		blocks.add(new Block(gameInstance, grid, this, blockType));
	}


	setRotation(0);


	initBlocks();
}


//=========================================================================================================================
void Piece::initBlocks()
{//=========================================================================================================================
	initColors();
	setPieceBlockConnections();
	setBlockColorConnectionsInPiece();
}


//=========================================================================================================================
void Piece::initColors()
{//=========================================================================================================================
	//set piece color

	for (int i = 0; i < blocks.size(); i++)
	{
		Block* b = blocks.get(i);

		if (b->blockType->colors.size()>0)
		{
			b->setRandomBlockTypeColor();
		}
		else
		{
			//BobColor none;
			if (pieceType->color != nullptr)
			{
				b->setColor(pieceType->color);
			}
		}
	}


	if (getGameType()->whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor)
	{
		//don't match a green crash piece with a green crash piece
		for (int a = 0; a < blocks.size(); a++)
		{
			Block* blockA = blocks.get(a);

			for (int b = 0; b < blocks.size(); b++)
			{
				Block* blockB = blocks.get(b);

				if (blockB == blockA)
				{
					continue;
				}

				if (blockA->blockType == blockB->blockType && blockA->blockType->isSpecialType() && blockB->blockType->isSpecialType())
				{
					while (blockA->getColor() == blockB->getColor() && blockA->blockType->colors.size()>1)
					{
						blockA->setRandomBlockTypeColor();
					}
				}
			}
		}
	}

	if (getGameType()->whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor)
	{
		//don't match a green crash piece with a green gem
		for (int a = 0; a < blocks.size(); a++)
		{
			Block* blockA = blocks.get(a);

			for (int b = 0; b < blocks.size(); b++)
			{
				Block* blockB = blocks.get(b);

				if (blockB == blockA)
				{
					continue;
				}

				if (blockA->blockType != blockB->blockType && blockA->blockType->isSpecialType() != blockB->blockType->isSpecialType())
				{
					if (blockA->blockType->isSpecialType() == false)
					{
						while (blockA->getColor() == blockB->getColor() && blockA->blockType->colors.size()>1)
						{
							blockA->setRandomBlockTypeColor();
						}
					}
					else
					{
						if (blockB->blockType->isSpecialType() == false)
						{
							while (blockA->getColor() == blockB->getColor() && blockB->blockType->colors.size()>1)
							{
								blockB->setRandomBlockTypeColor();
							}
						}
					}
				}
			}
		}
	}

	if (getGameType()->whenGeneratingPieceDontMatchAllBlockColors)
	{
		//don't make 3 jewels of the same color

		BobColor *c = blocks.get(0)->getColor();

		
		if (c != nullptr)
		{
			bool allTheSame = true;

			for (int i = 0; i < blocks.size(); i++)
			{
				if (c != blocks.get(i)->getColor())
				{
					allTheSame = false;
				}
			}

			if (allTheSame)
			{
				Block* blockA = blocks.get(0);

				for (int b = 0; b < blocks.size(); b++)
				{
					Block* blockB = blocks.get(b);

					if (blockB == blockA)
					{
						continue;
					}

					while (blockA->getColor() == blockB->getColor() && blockB->blockType->colors.size()>1)
					{
						blockB->setRandomBlockTypeColor();
					}
				}
			}
		}
	}
}


//=========================================================================================================================
void Piece::setPieceBlockConnections()
{//=========================================================================================================================

	for (int b = 0; b < blocks.size(); b++)
	{
		blocks.get(b)->connectedBlocksByPiece.clear();
	}

	for (int b = 0; b < blocks.size(); b++)
	{
		for (int c = 0; c < blocks.size(); c++)
		{
			if (blocks.get(c) != blocks.get(b))
			{
				if (blocks.get(b)->connectedBlocksByPiece.contains(blocks.get(c)) == false)
				{
					blocks.get(b)->connectedBlocksByPiece.add(blocks.get(c));
				}
			}
		}
	}
}


//=========================================================================================================================
void Piece::setBlockColorConnectionsInPiece()
{//=========================================================================================================================

	for (int b = 0; b < blocks.size(); b++)
	{
		blocks.get(b)->connectedBlocksByColor.clear();
	}

	for (int b = 0; b < blocks.size(); b++)
	{
		for (int c = 0; c < blocks.size(); c++)
		{
			if (blocks.get(c) != blocks.get(b))
			{
				if (blocks.get(b)->getColor() == blocks.get(c)->getColor())
				{
					if (blocks.get(b)->connectedBlocksByColor.contains(blocks.get(c)) == false)
					{
						blocks.get(b)->connectedBlocksByColor.add(blocks.get(c));

					}
				}
			}
		}
	}
}

//=========================================================================================================================
int Piece::getNumBlocksInCurrentRotation()
{//=========================================================================================================================
	return pieceType->rotationSet.get(currentRotation)->blockOffsets.size();

}

//=========================================================================================================================
void Piece::update()
{//=========================================================================================================================

	cursorFadeTicks += getGameLogic()->ticks();

	if (cursorFadeTicks > cursorFadeTicksPerPhase)
	{
		cursorFadeTicks = 0;
		cursorFadeInOutToggle = !cursorFadeInOutToggle;
	}
	if (cursorFadeInOutToggle == true)
	{
		cursorAlpha = cursorAlphaFrom + ((float)(cursorFadeTicks) / (float)(cursorFadeTicksPerPhase)) * (cursorAlphaTo - cursorAlphaFrom);
	}
	else
	{
		cursorAlpha = cursorAlphaTo - ((float)(cursorFadeTicks) / (float)(cursorFadeTicksPerPhase)) * (cursorAlphaTo - cursorAlphaFrom);
	}


	ghostFadeTicks += getGameLogic()->ticks();

	if (ghostFadeTicks > ghostFadeTicksPerPhase)
	{
		ghostFadeTicks = 0;
		ghostFadeInOutToggle = !ghostFadeInOutToggle;
	}
	if (ghostFadeInOutToggle == true)
	{
		ghostAlpha = ghostAlphaFrom + ((float)(ghostFadeTicks) / (float)(ghostFadeTicksPerPhase)) * (ghostAlphaTo - ghostAlphaFrom);
	}
	else
	{
		ghostAlpha = ghostAlphaTo - ((float)(ghostFadeTicks) / (float)(ghostFadeTicksPerPhase)) * (ghostAlphaTo - ghostAlphaFrom);
	}


	for (int i = 0; i < blocks.size(); i++)
	{
		Block* b = blocks.get(i);
		if (b->blockType->counterType)
		{
			if (b->counterCount == -2)
			{
				b->counterCount = getGameLogic()->getRandomIntLessThan(11, "Piece::update");
			}
		}
	}



	if (setInGrid)
	{
		if (pieceType->turnBackToNormalPieceAfterNPiecesLock != -1)
		{
			if (piecesSetSinceThisPieceSet >= pieceType->turnBackToNormalPieceAfterNPiecesLock)
			{
				overrideAnySpecialBehavior = true;
			}
		}



		ArrayList<BlockType*> blockTypes;//special case, this is slow so we don't fill it unless we need it
		bool filledBlockTypes = false;

		for (int i = 0; i < blocks.size(); i++)
		{
			Block* b = blocks.get(i);

			if (b->blockType->turnBackToNormalBlockAfterNPiecesLock != -1)
			{
				if (piecesSetSinceThisPieceSet >= b->blockType->turnBackToNormalBlockAfterNPiecesLock)
				{
					b->overrideAnySpecialBehavior = true;
				}
			}

			if (b->blockType->counterType)
			{
				if (b->counterCount == -1)
				{
					if (filledBlockTypes == false)
					{
						blockTypes = getGameType()->getNormalBlockTypes(getGameLogic()->getCurrentDifficulty());
						filledBlockTypes = true;
					}
					b->counterCount = -2;
					BobColor *color = b->getColor();
					b->blockType = grid->getRandomBlockTypeFromArrayExcludingSpecialBlockTypes(blockTypes);
					b->setColor(color);
				}
			}
		}
	}


	for (int i = 0; i < blocks.size(); i++)
	{
		blocks.get(i)->update();
	}
	if (holdingBlock != nullptr)
	{
		holdingBlock->update();
	}
}


//=========================================================================================================================
float Piece::getScreenX()
{//=========================================================================================================================
	return grid->getXInFBO() + xGrid * cellW();
}


//=========================================================================================================================
float Piece::getScreenY()
{//=========================================================================================================================
	return grid->getYInFBO() + yGrid * cellH() + (grid->scrollPlayingFieldY / grid->scrollBlockIncrement)*cellH();
}


//=========================================================================================================================
void Piece::renderOutlineFirstBlock(float x, float y, float alpha, bool asGhost)
{//=========================================================================================================================

	float w = (float)cellW();
	float h = (float)cellH();

	Block* b = blocks.get(0);


	float bx = x + b->xInPiece * w;
	float by = y + b->yInPiece * h;

	if (asGhost == false)
	{
		float* xy = b->getInterpolatedScreenXY(bx, by);

		bx = xy[0];
		by = xy[1];

		delete xy;
	}


	for (int p = 0; p < 5; p++) //TODO: getScale with screen res
	{
		float a = alpha;


		//this was commented
		//if(p==1)a = 1.0f / alpha;//TODO: shift alpha through cycle?


		//top
		GLUtils::drawFilledRectXYWH(bx, by - p, w, 1.0f, 1.0f, 1.0f, 1.0f, a);
		//bottom
		GLUtils::drawFilledRectXYWH(bx, by + h + (p - 1), w, 1.0f, 1.0f, 1.0f, 1.0f, a);
		//left
		GLUtils::drawFilledRectXYWH(bx - p, by, 1.0f, h, 1.0f, 1.0f, 1.0f, a);
		//right
		GLUtils::drawFilledRectXYWH(bx + w + (p - 1), by, 1.0f, h, 1.0f, 1.0f, 1.0f, a);
	}
}


//=========================================================================================================================
void Piece::renderOutlineBlockZeroZero(float x, float y, float alpha, bool asGhost)
{//=========================================================================================================================

	float w = (float)cellW();
	float h = (float)cellH();


	for (int i = 0; i < getNumBlocksInCurrentRotation() && i < blocks.size(); i++)
	{
		Block* b = blocks.get(i);


		//outline main piece
		if (b->xInPiece == 0 && b->yInPiece == 0)
		{
			float bx = x + b->xInPiece*w;
			float by = y + b->yInPiece*h;

			if (asGhost == false)
			{
				float* xy = b->getInterpolatedScreenXY(bx, by);


				bx = xy[0];
				by = xy[1];

				delete xy;
			}

			for (int p = 0; p < 5; p++) //TODO: getScale with screen res
			{
				float a = alpha;


				//this was commented
				//if(p==1)a = 1.0f / alpha;


				//top
				GLUtils::drawFilledRectXYWH(bx, by - p, w, 1, 1.0f, 1.0f, 1.0f, a);
				//bottom
				GLUtils::drawFilledRectXYWH(bx, by + h + (p - 1), w, 1, 1.0f, 1.0f, 1.0f, a);
				//left
				GLUtils::drawFilledRectXYWH(bx - p, by, 1, h, 1.0f, 1.0f, 1.0f, a);
				//right
				GLUtils::drawFilledRectXYWH(bx + w + (p - 1), by, 1, h, 1.0f, 1.0f, 1.0f, a);
			}
		}
	}
}


//=========================================================================================================================
void Piece::renderAsCurrentPiece()
{//=========================================================================================================================
	renderAsCurrentPiece(getScreenX(), getScreenY());
}

void Piece::renderAsCurrentPiece(float x, float y)
{//=========================================================================================================================


	float w = (float)cellW();
	float h = (float)cellH();


	if (getGameType()->gameMode == GameMode::STACK && getGameType()->stackCursorType==CursorType::ONE_BLOCK_PICK_UP)
	{
		y -= cellH() / 3;
	}

	if (getGameType()->gameMode==GameMode::DROP)//was currentPieceRenderAsNormalPiece
	{
		render(x, y);
	}

	if (getGameType()->currentPieceRule_OutlineBlockAtZeroZero)
	{
		renderOutlineBlockZeroZero(x, y, cursorAlpha, false);
	}

	if (getGameType()->currentPieceOutlineFirstBlockRegardlessOfPosition)
	{
		renderOutlineFirstBlock(x, y, cursorAlpha, false);
	}


	if (getGameType()->gameMode == GameMode::STACK && getGameType()->stackCursorType == CursorType::ONE_BLOCK_PICK_UP)
	{
		if (holdingBlock != nullptr)
		{
			holdingBlock->render(x, y, 1.0f, 1.0f, true, false);
		}
	}

	if (getGameType()->gameMode == GameMode::STACK)
	//if (getCurrentGameType()->drawCursorInsteadOfCurrentPiece)//was currentPieceOutlineAllPieces
	{
		for (int i = 0; i < getNumBlocksInCurrentRotation() && i < blocks.size(); i++)
		{
			int ox = getGameType()->gridPixelsBetweenColumns;
			int oy = getGameType()->gridPixelsBetweenRows;
			Block* b = blocks.get(i);
			float bx = x + b->xInPiece*w + b->xInPiece*ox;
			float by = y + b->yInPiece*h + b->yInPiece*oy;


			//this was commented
			//				float[] xy = b->getInterpolatedScreenXY(bx,by);
			//
			//				bx = xy[0];
			//				by = xy[1];

			for (int p = 0; p < 5; p++)
			{
				float a = cursorAlpha;
				if (p == 1)a = 1.0f / cursorAlpha;


				//top
				GLUtils::drawFilledRectXYWH(bx, by - p, w, 1, 1.0f, 1.0f, 1.0f, a);
				//bottom
				GLUtils::drawFilledRectXYWH(bx, by + h + (p - 1), w, 1, 1.0f, 1.0f, 1.0f, a);
				//left
				GLUtils::drawFilledRectXYWH(bx - p, by, 1, h, 1.0f, 1.0f, 1.0f, a);
				//right
				GLUtils::drawFilledRectXYWH(bx + w + (p - 1), by, 1, h, 1.0f, 1.0f, 1.0f, a);
			}
		}
	}
}


//=========================================================================================================================
void Piece::render(float x, float y)
{//=========================================================================================================================
	for (int i = 0; i < getNumBlocksInCurrentRotation() && i < blocks.size(); i++)
	{
		Block* b = blocks.get(i);
		b->render(x + b->xInPiece*cellW(), y + b->yInPiece*cellH(), 1.0f, 1.0f, true, false);
	}
}


//=========================================================================================================================
void Piece::renderGhost(float x, float y, float alpha)
{//=========================================================================================================================

	for (int i = 0; i < getNumBlocksInCurrentRotation() && i < blocks.size(); i++)
	{
		Block* b = blocks.get(i);


		BobColor *c = getGameLogic()->player->gridCheckeredBackgroundColor1;


		// fill in black square so background doesnt show through alpha
		GLUtils::drawFilledRectXYWH(x + b->xInPiece*cellW(), y + b->yInPiece*cellH(), (float)cellW(), (float)cellH(), c->rf(), c->gf(), c->bf(), 1.0f);


		b->render(x + b->xInPiece*cellW(), y + b->yInPiece*cellH(), ghostAlpha * alpha, 1.0f, false, true);
	}

	if (getGameType()->currentPieceRule_OutlineBlockAtZeroZero)
	{
		renderOutlineBlockZeroZero(x, y, ghostAlpha / 2 * alpha, true);
	}

	if (getGameType()->currentPieceOutlineFirstBlockRegardlessOfPosition)
	{
		renderOutlineFirstBlock(x, y, ghostAlpha / 2 * alpha, true);
	}
}


//=========================================================================================================================
void Piece::setBlocksSlamming()
{//=========================================================================================================================
	for (int i = 0; i < blocks.size(); i++)
	{
		Block* b = blocks.get(i);
		b->slamming = true;
		b->slamX = getScreenX() + (b->xInPiece) * cellW();
		b->slamY = getScreenY() + (b->yInPiece) * cellH();
	}
}


//=========================================================================================================================
int Piece::getWidth()
{//=========================================================================================================================


	int lowestXOffset = 4;
	int highestXOffset = -4;
	for (int b = 0; b < getNumBlocksInCurrentRotation() && b < blocks.size(); b++)
	{
		if (blocks.get(b)->xInPiece < lowestXOffset)
		{
			lowestXOffset = blocks.get(b)->xInPiece;
		}
	}
	for (int b = 0; b < getNumBlocksInCurrentRotation() && b < blocks.size(); b++)
	{
		if (blocks.get(b)->xInPiece > highestXOffset)
		{
			highestXOffset = blocks.get(b)->xInPiece;
		}
	}

	//1+ for 0,0 piece
	return 1 + abs(highestXOffset) + abs(lowestXOffset);
}


//=========================================================================================================================
int Piece::getHeight()
{//=========================================================================================================================

	int lowestYOffset = 4;
	int highestYOffset = -4;
	for (int b = 0; b < getNumBlocksInCurrentRotation() && b < blocks.size(); b++)
	{
		if (blocks.get(b)->yInPiece < lowestYOffset)
		{
			lowestYOffset = blocks.get(b)->yInPiece;
		}
	}
	for (int b = 0; b < getNumBlocksInCurrentRotation() && b < blocks.size(); b++)
	{
		if (blocks.get(b)->yInPiece > highestYOffset)
		{
			highestYOffset = blocks.get(b)->yInPiece;
		}
	}

	return 1 + abs(highestYOffset) + abs(lowestYOffset);
}


//=========================================================================================================================
int Piece::getLowestOffsetX()
{//=========================================================================================================================
	int lowestXOffset = 0;
	for (int b = 0; b < getNumBlocksInCurrentRotation() && b < blocks.size(); b++)
	{
		if (blocks.get(b)->xInPiece < lowestXOffset)
		{
			lowestXOffset = blocks.get(b)->xInPiece;
		}
	}

	return lowestXOffset;
}


//=========================================================================================================================
int Piece::getLowestOffsetY()
{//=========================================================================================================================
	int lowestYOffset = 0;
	for (int b = 0; b < getNumBlocksInCurrentRotation() && b < blocks.size(); b++)
	{
		if (blocks.get(b)->yInPiece < lowestYOffset)
		{
			lowestYOffset = blocks.get(b)->yInPiece;
		}
	}

	return lowestYOffset;
}


//=========================================================================================================================
int Piece::getHighestOffsetX()
{//=========================================================================================================================
	int highestXOffset = 0;
	for (int b = 0; b < getNumBlocksInCurrentRotation() && b < blocks.size(); b++)
	{
		if (blocks.get(b)->xInPiece > highestXOffset)
		{
			highestXOffset = blocks.get(b)->xInPiece;
		}
	}

	return highestXOffset;
}


//=========================================================================================================================
int Piece::getHighestOffsetY()
{//=========================================================================================================================
	int highestYOffset = 0;
	for (int b = 0; b < getNumBlocksInCurrentRotation() && b < blocks.size(); b++)
	{
		if (blocks.get(b)->yInPiece > highestYOffset)
		{
			highestYOffset = blocks.get(b)->yInPiece;
		}
	}

	return highestYOffset;
}


//=========================================================================================================================
void Piece::rotateCCW()
{//=========================================================================================================================
	if (currentRotation == 0)
	{
		currentRotation = pieceType->rotationSet.size()-1;
	}
	else
	{
		currentRotation = currentRotation - 1;
	}
	setRotation(currentRotation);
}


//=========================================================================================================================
void Piece::rotateCW()
{//=========================================================================================================================
	if (currentRotation == pieceType->rotationSet.size() - 1)
	{
		currentRotation = 0;
	}
	else
	{
		currentRotation = currentRotation + 1;
	}
	setRotation(currentRotation);
}


//=========================================================================================================================
void Piece::setRandomPieceColors(bool grayscale)
{//=========================================================================================================================


	//TODO:
	//TODO:
	//TODO:
	//TODO:
	//TODO:
	//TODO:
	//		for(int i=0;i<colors->length;i++)
	//		{
	//			colors->get(i) = Color->black;
	//		}
	//
	//		for(int i=0;i<colors->length;i++)
	//		{
	//			Color temp = Color->black;
	//			bool taken = true;
	//			while(taken==true)
	//			{
	//				taken=false;
	//
	//				if(grayscale)temp = Block->getRandomGrayscaleColor();
	//				else temp = Block->getRandomColor();
	//
	//				for(int n=0;n<colors->length;n++)if(colors->get(n)==temp)taken=true;
	//			}
	//
	//			colors->get(i)=temp;
	//		}
}


//=========================================================================================================================
void Piece::setRotation(int rotation)
{//=========================================================================================================================

	currentRotation = rotation;

	if (rotation >= (int)pieceType->rotationSet.size())
	{
		rotation -= (int)pieceType->rotationSet.size();
	}

	Rotation *r = pieceType->rotationSet.get(rotation);

	for (int i = 0; i < getNumBlocksInCurrentRotation() && i < blocks.size(); i++)
	{
		BlockOffset *b = r->blockOffsets.get(i);
		blocks.get(i)->setXYOffsetInPiece(b->x, b->y);
	}
}


//=========================================================================================================================
RotationSet Piece::get2BlockRotateAround00RotationSet()
{//=========================================================================================================================


	RotationSet rotations("2 Block Rotate Around 0,0");

	//if(pieceType->name->equals("BLOB") || pieceType->name->equals("DAMA") || pieceType->name->equals("PUZZLEFIGHTER"))

	//this is rotation around 0,0
	//if(rotation==0)
	{
		Rotation *r = new Rotation();
		r->add(new BlockOffset(0, 0));
		r->add(new BlockOffset(1, 0));
		rotations.add(r);
	}

	{
		//if(rotation==1)
		Rotation *r = new Rotation();
		r->add(new BlockOffset(0, 0));
		r->add(new BlockOffset(0, 1));
		rotations.add(r);
	}

	{
		//if(rotation==2)
		Rotation *r = new Rotation();
		r->add(new BlockOffset(0, 0));
		r->add(new BlockOffset(-1, 0));
		rotations.add(r);
	}

	{
		//if(rotation==3)
		Rotation *r = new Rotation();
		r->add(new BlockOffset(0, 0));
		r->add(new BlockOffset(0, -1));
		rotations.add(r);
	}

	return rotations;
}


//=========================================================================================================================
RotationSet Piece::get2BlockBottomLeftAlwaysFilledRotationSet()
{//=========================================================================================================================


	RotationSet rotations("2 Block BottomLeft Always Filled");

	//if(pieceType->name->equals("DRBOB"))

	//this is rotation in a 2x2 bounding box with bottom left always filled
	//if(rotation==0)
	{
		Rotation *r = new Rotation();
		
		r->add(new BlockOffset(0, 0));
		r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}

	{
		//if(rotation==1)
		Rotation *r = new Rotation();
		
		r->add(new BlockOffset(0, -1));
		r->add(new BlockOffset(0, 0));
			rotations.add(r);
		}

	{
		//if(rotation==2)
		Rotation *r = new Rotation();
		
		r->add(new BlockOffset(1, 0));
		r->add(new BlockOffset(0, 0));
			rotations.add(r);
		}

	{
		//if(rotation==3)
		Rotation *r = new Rotation();
		
		r->add(new BlockOffset(0, 0));
		r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}

	return rotations;
}



//=========================================================================================================================
RotationSet Piece::get1BlockCursorRotationSet()
{//=========================================================================================================================

	RotationSet rotations("1 Block Cursor");

	{
		//if(pieceType->name->equals("PANELPUZZLE")) if(pieceType->name->equals("DAMASWAP_CURSOR"))
		//this is rotation in a 2x2 bounding box with bottom left always filled
		//if(rotation==0)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			rotations.add(r);
		}
	}

	return rotations;
}

//=========================================================================================================================
RotationSet Piece::get2BlockHorizontalCursorRotationSet()
{//=========================================================================================================================

	RotationSet rotations("2 Block Horizontal Cursor");

	{
		//if(pieceType->name->equals("PANELPUZZLE_CURSOR"))
		//if(rotation==0)
		{
			Rotation *r = new Rotation();

			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}
	}

	return rotations;
}

//=========================================================================================================================
RotationSet Piece::get2BlockVerticalCursorRotationSet()
{//=========================================================================================================================

	RotationSet rotations("2 Block Vertical Cursor");

	{
		//if(pieceType->name->equals("PANELPUZZLE_CURSOR"))
		//if(rotation==0)
		{
			Rotation *r = new Rotation();

			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}
	}

	return rotations;
}

//=========================================================================================================================
RotationSet Piece::get3BlockHorizontalCursorRotationSet()
{//=========================================================================================================================

	RotationSet rotations("3 Block Horizontal Cursor");

	{

		{
			Rotation *r = new Rotation();

			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}
	}

	return rotations;
}

//=========================================================================================================================
RotationSet Piece::get3BlockVerticalCursorRotationSet()
{//=========================================================================================================================

	RotationSet rotations("3 Block Vertical Cursor");

	{

		{
			Rotation *r = new Rotation();

			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}
	}

	return rotations;
}

//=========================================================================================================================
RotationSet Piece::get4BlockCursorRotationSet()
{//=========================================================================================================================

	RotationSet rotations("4 Block Cursor");

	{
		//if(pieceType->name->equals("PUZZLEFIGHTER_CURSOR"))
		//if(rotation==0)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(1, 1));
			rotations.add(r);
		}
	}

	return rotations;
}


//=========================================================================================================================
RotationSet Piece::get3BlockVerticalRotationSet()
{//=========================================================================================================================

	RotationSet rotations("3 Block Vertical Swap");

	{
		//if(pieceType->name->equals("COLUMNS"))

		{
			//if(rotation==0)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, -2));
			rotations.add(r);
		}

		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, -2));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}

		{
			//if(rotation==2)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, -2));
			r->add(new BlockOffset(0, 0));
			rotations.add(r);
		}
	}
	return rotations;
}

//=========================================================================================================================
RotationSet Piece::get3BlockHorizontalRotationSet()
{//=========================================================================================================================

	RotationSet rotations("3 Block Horizontal Swap");

	{
		//if(pieceType->name->equals("COLUMNS"))

		{
			//if(rotation==0)
			Rotation *r = new Rotation();

			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}

		{
			//if(rotation==1)
			Rotation *r = new Rotation();

			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, 0));
			rotations.add(r);
		}

		{
			//if(rotation==2)
			Rotation *r = new Rotation();

			r->add(new BlockOffset(0,0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}
	}
	return rotations;
}
//=========================================================================================================================
RotationSet Piece::get3BlockTRotationSet()
{//=========================================================================================================================

	RotationSet rotations("3 Block T");

	{
		//if(pieceType->name->equals("TETRID_T"))
		/*
		->->->->->->get(0)
		->->->get(1)->->->[2]
		*/
		//if(rotation==0)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 1));
			r->add(new BlockOffset(1, 1));
			rotations.add(r);
		}

		/*
		->->[1]
		->->->->->->get(0)
		->->[2]
		*/
		//if(rotation==1)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, -1));
			r->add(new BlockOffset(-1, 1));
			rotations.add(r);
		}

		/*
		->->[2]->->->[1]
		->->->->->->get(0)
		*/
		//if(rotation==2)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, -1));
			r->add(new BlockOffset(-1, -1));
			rotations.add(r);
		}

		/*
		->->->->->->->->[2]
		->->->->->->get(0)
		->->->->->->->->[1]
		*/
		//if(rotation==3)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 1));
			r->add(new BlockOffset(1, -1));
			rotations.add(r);
		}
	}
	return rotations;
}


//=========================================================================================================================
RotationSet Piece::get3BlockLRotationSet()
{//=========================================================================================================================

	RotationSet rotations("3 Block L");

	{
		//if(pieceType->name->equals("TETRID_L"))
		/*
		->->->[1]
		->->->->->->->get(0)
		->->->->->->[2]
		*/
		//if(rotation==0)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, -1));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}

		/*
		->->->->->->->->->[1]
		->->->[2]->get(0)
		*/
		//if(rotation==1)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, -1));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}

		/*
		->->->->->->[2]
		->->->->->->->get(0)
		->->->->->->->->->[1]
		*/
		//if(rotation==2)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 1));
			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}

		/*
		->->->->->->->get(0)[2]
		->->->[1]
		*/
		//if(rotation==3)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 1));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}
	}


	return rotations;
}


//=========================================================================================================================
RotationSet Piece::get3BlockJRotationSet()
{//=========================================================================================================================

	RotationSet rotations("3 Block J");


	{
		//if(pieceType->name->equals("TETRID_J"))
		/*
		->->->->->->->->->[1]
		->->->->->->->get(0)
		->->->->->->[2]
		*/
		//if(rotation==0)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, -1));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}

		/*
		->->->[2]->get(0)
		->->->->->->->->->[1]
		*/
		//if(rotation==1)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 1));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}

		/*
		->->->->->->[2]
		->->->->->->->get(0)
		->->->[1]
		*/
		//if(rotation==2)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 1));
			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}

		/*
		->->->[1]
		->->->->->->->get(0)[2]
		*/
		//if(rotation==3)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, -1));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}
	}


	return rotations;
}

//=========================================================================================================================
RotationSet Piece::get3BlockIRotationSet()
{//=========================================================================================================================

	RotationSet rotations("3 Block I");


	{
		//if(pieceType->name->equals("TETRID_I"))

		/*
		->->->->[1]
		->->->->->get(0)
		->->->->[2]
		*/
		//if(rotation==0 || rotation==2)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}

		/*
		->->[2]->get(0)[1]
		*/
		//if(rotation==1 || rotation==3)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}

		/*
		->->->->[2]
		->->->->->get(0)
		->->->->[1]
		*/
		//if(rotation==0 || rotation==2)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}

		/*
		->->->get(1)->get(0)[2]
		*/
		//if(rotation==1 || rotation==3)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}
	}


	return rotations;
}

//=========================================================================================================================
RotationSet Piece::get3BlockCRotationSet()
{//=========================================================================================================================

	RotationSet rotations("3 Block C");


	{
		//if(pieceType->name->equals("TETRID_C"))
		/*
		->->[2]->get(0)
		->->->->->[1]
		*/
		//if(rotation==0)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}

		/*
		->->->->->[2]
		->->->get(1)->get(0)
		*/
		//if(rotation==1)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}

		/*
		->->[1]
		->->->get(0)[2]
		*/
		//if(rotation==2)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}

		/*
		->->->get(0)[1]
		->->[2]
		*/
		//if(rotation==3)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}
	}


	return rotations;
}

//=========================================================================================================================
RotationSet Piece::get3BlockDRotationSet()
{//=========================================================================================================================

	RotationSet rotations("3 Block D");

	{
		//if(pieceType->name->equals("TETRID_D"))
		/*
		->->[1]
		->->->->->->get(0)
		->->->->->->->->[2]
		*/
		//if(rotation==0 || rotation==2)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, -1));
			r->add(new BlockOffset(1, 1));
			rotations.add(r);
		}

		/*
		->->->->->->->->[1]
		->->->->->->get(0)
		->->[2]
		*/
		//if(rotation==1 || rotation==3)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, -1));
			r->add(new BlockOffset(-1, 1));
			rotations.add(r);
		}
		/*
		->->[2]
		->->->->->->get(0)
		->->->->->->->->[1]
		*/
		//if(rotation==0 || rotation==2)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 1));
			r->add(new BlockOffset(-1, -1));
			rotations.add(r);
		}

		/*
		->->->->->->->->[2]
		->->->->->->get(0)
		->->[1]
		*/
		//if(rotation==1 || rotation==3)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 1));
			r->add(new BlockOffset(1, -1));
			rotations.add(r);
		}
	}

	return rotations;
}

//=========================================================================================================================
RotationSet Piece::get4BlockORotationSet()
{//=========================================================================================================================

	RotationSet rotations("4 Block O");

	{
		//same everywhere
		//if(rotation==0)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(1, -1));
			rotations.add(r);
		}
		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			

			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, -1));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}
		{
			//if(rotation==2)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(1, -1));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, 0));
			rotations.add(r);
		}
		{
			//if(rotation==3)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(1, -1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}
	}

	return rotations;
}

//=========================================================================================================================
RotationSet Piece::get4BlockSolidRotationSet()
{//=========================================================================================================================

	RotationSet rotations("4 Block Solid");

	{
		//same everywhere
		//if(rotation==0)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(1, -1));
			rotations.add(r);
		}
	}

	return rotations;
}


//=========================================================================================================================
RotationSet Piece::get9BlockSolidRotationSet()
{//=========================================================================================================================

	RotationSet rotations("9 Block Solid");

	{
		//same everywhere
		//if(rotation==0)
		{
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(2, 0));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(1, -1));
			r->add(new BlockOffset(2, -1));
			r->add(new BlockOffset(0, -2));
			r->add(new BlockOffset(1, -2));
			r->add(new BlockOffset(2, -2));
			rotations.add(r);
		}
	}

	return rotations;
}


//=========================================================================================================================
RotationSet Piece::get4BlockIRotationSet(RotationType type)
{//=========================================================================================================================

	string name = "4 Block I";
	if (type == RotationType::DTET)name += " (DTET)";
	if (type == RotationType::SRS)name += " (SRS)";
	if (type == RotationType::SEGA)name += " (SEGA)";
	if (type == RotationType::NES)name += " (NES)";
	if (type == RotationType::GB)name += " (GB)";
	RotationSet rotations(name);


	if (type == RotationType::SRS || type == RotationType::DTET || type == RotationType::SEGA) //unique for SRS: 4 position ISZ rotation
	{
		if (type == RotationType::SRS || type == RotationType::SEGA)
		{
			//if(rotation==0)
			Rotation *r = new Rotation();
			

			r->add(new BlockOffset(-2, 0));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}

		if (type == RotationType::DTET)
		{
			//if(rotation==0)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(-2, 1));
			r->add(new BlockOffset(-1, 1));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(1, 1));
			rotations.add(r);
		}


		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(0, 2));
			rotations.add(r);
		}

		if (type == RotationType::SRS || type == RotationType::DTET)
		{
			{
				//if(rotation==2)
				Rotation *r = new Rotation();
				
				r->add(new BlockOffset(1, 1));

				r->add(new BlockOffset(0, 1));
				r->add(new BlockOffset(-1, 1));
				r->add(new BlockOffset(-2, 1));
			rotations.add(r);
		}
			{
				//if(rotation==3)
				Rotation *r = new Rotation();
				
				r->add(new BlockOffset(-1, 2));

				r->add(new BlockOffset(-1, 1));
				r->add(new BlockOffset(-1, 0));
				r->add(new BlockOffset(-1, -1));
			rotations.add(r);
		}
		}
		if (type == RotationType::SEGA)
		{
			{
				//if(rotation==2)
				Rotation *r = new Rotation();
				
				r->add(new BlockOffset(1, 0));
				r->add(new BlockOffset(0, 0));
				r->add(new BlockOffset(-1, 0));
				r->add(new BlockOffset(-2, 0));
			rotations.add(r);
		}
			{
				//if(rotation==3)
				Rotation *r = new Rotation();
				

				r->add(new BlockOffset(0, 2));
				r->add(new BlockOffset(0, 1));
				r->add(new BlockOffset(0, 0));

				r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}
		}
	}


	if (type == RotationType::GB)
	{
		{
			//if(rotation==0)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(2, 0));
			rotations.add(r);
		}

		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, -2));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}
		{
			//if(rotation==2)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(2, 0));

			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}

		{
			//if(rotation==3)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 1));

			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, -2));
			rotations.add(r);
		}
	}


	if (type == RotationType::NES)
	{
		{
			//if(rotation==0)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(-2, 0));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}
		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, -2));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}
		{
			//if(rotation==2)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(1, 0));

			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(-2, 0));
			rotations.add(r);
		}
		{
			//if(rotation==3)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 1));

			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, -2));
			rotations.add(r);
		}
	}


	return rotations;
}


//=========================================================================================================================
RotationSet Piece::get4BlockJRotationSet(RotationType type)
{//=========================================================================================================================


	//RotationSet rotations("4 Block J");
	string name = "4 Block J";
	if (type == RotationType::DTET)name += " (DTET)";
	if (type == RotationType::SRS)name += " (SRS)";
	if (type == RotationType::SEGA)name += " (SEGA)";
	if (type == RotationType::NES)name += " (NES)";
	if (type == RotationType::GB)name += " (GB)";
	RotationSet rotations(name);

	if (type == RotationType::SRS) //unique for SRS: flat side down
	{
		{
			//if(rotation==0)//this is rotation 2 for every other game()
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, -1));
			r->add(new BlockOffset(-1, 0));

			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}
		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));

			r->add(new BlockOffset(1, -1));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}
		{
			//if(rotation==2)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 1));


			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}
		{
			//if(rotation==3)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));


			r->add(new BlockOffset(-1, 1));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}
	}

	if (type == RotationType::SEGA || type == RotationType::GB || type == RotationType::NES || type == RotationType::DTET)
	{
		{
			//if(rotation==0)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 0));

			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(1, 1));
			rotations.add(r);
		}
		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(-1, 1));
			rotations.add(r);
		}

		if (type == RotationType::SEGA || type == RotationType::DTET)
		{
			//if(rotation==2)//SRS rotation 0 but down 1 //down one from other games, on floor
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(1, 1));
			r->add(new BlockOffset(-1, 1));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}

		if (type == RotationType::GB || type == RotationType::NES)
		{
			//if(rotation==2)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(-1, 0));


			r->add(new BlockOffset(-1, -1));
			rotations.add(r);
		}


		{
			//if(rotation==3)//SRS rotation 1
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(1, -1));
			rotations.add(r);
		}
	}


	return rotations;
}


//=========================================================================================================================
RotationSet Piece::get4BlockLRotationSet(RotationType type)
{//=========================================================================================================================


	//RotationSet rotations("4 Block L");
	string name = "4 Block L";
	if (type == RotationType::DTET)name += " (DTET)";
	if (type == RotationType::SRS)name += " (SRS)";
	if (type == RotationType::SEGA)name += " (SEGA)";
	if (type == RotationType::NES)name += " (NES)";
	if (type == RotationType::GB)name += " (GB)";
	RotationSet rotations(name);

	if (type == RotationType::SRS) //unique for SRS: flat side down
	{
		{
			//if(rotation==0)//this is rotation 2 for every other game()
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));

			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(1, -1));
			rotations.add(r);
		}
		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(1, 1));
			rotations.add(r);
		}
		{
			//if(rotation==2)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));

			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(-1, 1));
			rotations.add(r);
		}
		{
			//if(rotation==3)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(0, -1));

			r->add(new BlockOffset(-1, -1));
			rotations.add(r);
		}
	}


	if (type == RotationType::SEGA || type == RotationType::GB || type == RotationType::NES || type == RotationType::DTET)
	{
		{
			//if(rotation==0)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));

			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(-1, 1));
			rotations.add(r);
		}

		if (type == RotationType::SEGA || type == RotationType::DTET)
		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));

			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(-1, -1));
			rotations.add(r);
		}

		if (type == RotationType::GB || type == RotationType::NES)
		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(-1, -1));
			rotations.add(r);
		}


		{
			//if(rotation==2)//down one from other games, on floor
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 1));


			r->add(new BlockOffset(-1, 1));
			r->add(new BlockOffset(1, 1));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}

		{
			//if(rotation==3)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));

			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(1, 1));
			rotations.add(r);
		}
	}


	return rotations;
}


//=========================================================================================================================
RotationSet Piece::get4BlockSRotationSet(RotationType type)
{//=========================================================================================================================

	//type=RotationType->SRS;
	//type=RotationType->DTET;
	//type=RotationType->SEGA;
	//type=RotationType->NES;
	//type=RotationType->GB;

	//RotationSet rotations("4 Block S");
	string name = "4 Block S";
	if (type == RotationType::DTET)name += " (DTET)";
	if (type == RotationType::SRS)name += " (SRS)";
	if (type == RotationType::SEGA)name += " (SEGA)";
	if (type == RotationType::NES)name += " (NES)";
	if (type == RotationType::GB)name += " (GB)";
	RotationSet rotations(name);

	if (type == RotationType::SRS || type == RotationType::DTET) //unique for SRS: 4 position ISZ rotation
	{
		if (type == RotationType::SRS)
		{
			//if(rotation==0)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(1, -1));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}

		if (type == RotationType::DTET)
		{
			//if(rotation==0)
			Rotation *r = new Rotation();
			

			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(-1, 1));
			rotations.add(r);
		}

		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(1, 1));

			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}
		{
			//if(rotation==2)
			Rotation *r = new Rotation();
			


			r->add(new BlockOffset(-1, 1));
			r->add(new BlockOffset(0, 1));

			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}
		{
			//if(rotation==3)
			Rotation *r = new Rotation();
			


			r->add(new BlockOffset(-1, -1));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}
	}


	if (type == RotationType::SEGA || type == RotationType::GB || type == RotationType::NES)
	{
		{
			//if(rotation==0)
			Rotation *r = new Rotation();
			

			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, 0));

			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(-1, 1));
			rotations.add(r);
		}

		if (type == RotationType::SEGA || type == RotationType::GB)
		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(-1, -1));
			rotations.add(r);
		}

		if (type == RotationType::NES)
		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(1, 1));

			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}

		{
			//if(rotation==2)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(-1, 1));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}

		if (type == RotationType::SEGA || type == RotationType::GB)
		{
			//if(rotation==3)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(-1, -1));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}

		if (type == RotationType::NES)
		{
			//if(rotation==3)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(1, 1));
			rotations.add(r);
		}
	}


	return rotations;
}


//=========================================================================================================================
RotationSet Piece::get4BlockTRotationSet(RotationType type)
{//=========================================================================================================================


	//RotationSet rotations("4 Block T");
	string name = "4 Block T";
	if (type == RotationType::DTET)name += " (DTET)";
	if (type == RotationType::SRS)name += " (SRS)";
	if (type == RotationType::SEGA)name += " (SEGA)";
	if (type == RotationType::NES)name += " (NES)";
	if (type == RotationType::GB)name += " (GB)";
	RotationSet rotations(name);

	if (type == RotationType::SRS) //unique for SRS: flat side down
	{
		{
			//if(rotation==0)//this is rotation 2 for every other game()
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));

			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}
		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));

			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}
		{
			//if(rotation==2)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}
		{
			//if(rotation==3)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));

			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}
	}


	if (type == RotationType::SEGA || type == RotationType::GB || type == RotationType::NES || type == RotationType::DTET)
	{
		{
			//if(rotation==0)//SRS rotation 2, same as NES,GB
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 0));

			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}

		{
			//if(rotation==1)//SRS rotation 3, same as NES,GB
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}

		if (type == RotationType::SEGA || type == RotationType::DTET)
		{
			//if(rotation==2)//down one from other games, on floor
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(1, 1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 1));
			rotations.add(r);
		}

		if (type == RotationType::GB || type == RotationType::NES)
		{
			//if(rotation==2)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));

			r->add(new BlockOffset(1, 0));

			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}


		{
			//if(rotation==3)//STS rotation 1, same as NES,GB
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}
	}


	return rotations;
}


//=========================================================================================================================
RotationSet Piece::get4BlockZRotationSet(RotationType type)
{//=========================================================================================================================

	//RotationSet rotations("4 Block Z");
	string name = "4 Block Z";
	if (type == RotationType::DTET)name += " (DTET)";
	if (type == RotationType::SRS)name += " (SRS)";
	if (type == RotationType::SEGA)name += " (SEGA)";
	if (type == RotationType::NES)name += " (NES)";
	if (type == RotationType::GB)name += " (GB)";
	RotationSet rotations(name);

	if (type == RotationType::SRS || type == RotationType::DTET) //unique for SRS: 4 position ISZ rotation
	{
		if (type == RotationType::SRS)
		{
			//if(rotation==0)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(-1, -1));
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			rotations.add(r);
		}
		else
		{
			if (type == RotationType::DTET)
			{
				//if(rotation==0)
				Rotation *r = new Rotation();
				
				r->add(new BlockOffset(-1, 0));
				r->add(new BlockOffset(0, 0));
				r->add(new BlockOffset(0, 1));
				r->add(new BlockOffset(1, 1));
			rotations.add(r);
		}
		}

		{
			//if(rotation==1)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(1, -1));

			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}

		{
			//if(rotation==2)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(1, 1));

			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}

		{
			//if(rotation==3)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(-1, 1));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, 0));

			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}
	}


	if (type == RotationType::SEGA || type == RotationType::GB || type == RotationType::NES)
	{
		{
			//if(rotation==0)//same as STS rotation 2, same as NES,GB
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(1, 1));
			rotations.add(r);
		}


		if (type == RotationType::SEGA || type == RotationType::NES)
		{
			//if(rotation==1 || rotation==3)//same as STS rotation 1, same as NES
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(1, -1));
			r->add(new BlockOffset(1, 0));


			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, 1));
			rotations.add(r);
		}

		if (type == RotationType::GB)
		{
			//if(rotation==1 || rotation==3)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, -1));
			r->add(new BlockOffset(0, 0));

			r->add(new BlockOffset(-1, 0));

			r->add(new BlockOffset(-1, 1));
			rotations.add(r);
		}
		{
			//if(rotation==2)//same as STS rotation 2, same as NES,GB
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(1, 1));

			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(-1, 0));
			rotations.add(r);
		}

		if (type == RotationType::SEGA || type == RotationType::NES)
		{
			//if(rotation==3)//same as STS rotation 1, same as NES
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(0, 1));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(1, 0));
			r->add(new BlockOffset(1, -1));
			rotations.add(r);
		}

		if (type == RotationType::GB)
		{
			//if(rotation==3)
			Rotation *r = new Rotation();
			
			r->add(new BlockOffset(-1, 1));
			r->add(new BlockOffset(-1, 0));
			r->add(new BlockOffset(0, 0));
			r->add(new BlockOffset(0, -1));
			rotations.add(r);
		}
	}


	return rotations;
}


//=========================================================================================================================
int Piece::cellW()
{//=========================================================================================================================
	return getGameLogic()->cellW();
}

//=========================================================================================================================
int Piece::cellH()
{//=========================================================================================================================

	return getGameLogic()->cellH();
}

//=========================================================================================================================
GameType* Piece::getGameType()
{//=========================================================================================================================
	return getGameLogic()->currentGameType;
}

//=========================================================================================================================
GameLogic* Piece::getGameLogic()
{//=========================================================================================================================
	return game;
}
