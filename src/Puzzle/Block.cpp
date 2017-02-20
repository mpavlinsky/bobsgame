#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------





Logger Block::log = Logger("Block");

class BobsGame;
class GLUtils;

//string Block::Circle = "Circle";
//string Block::Square = "Square";
//string Block::RoundedSquareOutline = "RoundedSquareOutline";
//string Block::SquareGem = "SquareGem";
//string Block::DiamondGem = "DiamondGem";
//string Block::blobName = "Blob";
//string Block::virusName = "Virus";
//string Block::CircleOutline = "CircleOutline";
//string Block::SquareOutline = "SquareOutline";
//string Block::Counter = "Counter";
//string Block::SparkBall = "SparkBall";
//string Block::HappyBall = "HappyBall";
//string Block::AngryBall = "AngryBall";
//string Block::PacJar = "PacJar";
//string Block::PacBlob = "PacBlob";
//string Block::BallJar = "BallJar";
//string Block::ExclamationIconBlock = "ExclamationIconBlock";
//string Block::HeartIconBlock = "HeartIconBlock";
//string Block::CircleIconBlock = "CircleIconBlock";
//string Block::TriangleIconBlock = "TriangleIconBlock";
//string Block::UpsideDownTriangleIconBlock = "UpsideDownTriangleIconBlock";
//string Block::DiamondIconBlock = "DiamondIconBlock";
//string Block::StarIconBlock = "StarIconBlock";
//string Block::PlusBlock = "PlusBlock";
//string Block::MinusBlock = "MinusBlock";
//string Block::BombBlock = "BombBlock";
//string Block::WeightSpawnBlock = "WeightSpawnBlock";
//string Block::LinesBlock = "LinesBlock";
//string Block::Bomb = "Bomb";
//string Block::Weight = "Weight";
//
//Sprite* Block::circle = nullptr;
//Sprite* Block::square = nullptr;
//Sprite* Block::roundedSquareOutline = nullptr;
//Sprite* Block::squareGem = nullptr;
//Sprite* Block::diamondGem = nullptr;
//Sprite* Block::blob = nullptr;
//Sprite* Block::virus = nullptr;
//Sprite* Block::circleOutline = nullptr;
//Sprite* Block::squareOutline = nullptr;
//Sprite* Block::counter = nullptr;
//Sprite* Block::sparkBall = nullptr;
//Sprite* Block::happyBall = nullptr;
//Sprite* Block::angryBall = nullptr;
//Sprite* Block::pacJar = nullptr;
//Sprite* Block::pacBall = nullptr;
//Sprite* Block::ballJar = nullptr;
//Sprite* Block::exclamationIconBlock = nullptr;
//Sprite* Block::heartIconBlock = nullptr;
//Sprite* Block::circleIconBlock = nullptr;
//Sprite* Block::triangleIconBlock = nullptr;
//Sprite* Block::upsideDownTriangleIconBlock = nullptr;
//Sprite* Block::diamondIconBlock = nullptr;
//Sprite* Block::starIconBlock = nullptr;
//Sprite* Block::plusShooterBlock = nullptr;
//Sprite* Block::minusShooterBlock = nullptr;
//Sprite* Block::bombBlock = nullptr;
//Sprite* Block::weightBlock = nullptr;
//Sprite* Block::linesBlock = nullptr;
//Sprite* Block::bomb = nullptr;
//Sprite* Block::weight = nullptr;

BlockType* BlockType::emptyBlockType = new BlockType();
//=========================================================================================================================
bool BlockType::operator==(const BlockType& rhs) const
{//=========================================================================================================================
	return
		
		uuid == rhs.uuid
//		&& spriteName == rhs.spriteName
//		&& specialSpriteName == rhs.specialSpriteName
//
//		&& usedInNormalPieces == rhs.usedInNormalPieces
//		&& usedAsGarbage == rhs.usedAsGarbage
//		&& usedAsPlayingFieldFiller == rhs.usedAsPlayingFieldFiller
//		&& ignoreWhenMovingDownBlocks == rhs.ignoreWhenMovingDownBlocks
//		&& chainConnectionsMustContainAtLeastOneOfThisBlock == rhs.chainConnectionsMustContainAtLeastOneOfThisBlock
//		&& ignoreWhenCheckingChainConnections == rhs.ignoreWhenCheckingChainConnections
//
//		&& colors == rhs.colors
//		&& specialColor == rhs.specialColor
//		&& randomSpecialBlockChanceOneOutOf == rhs.randomSpecialBlockChanceOneOutOf
//		&& frequencySpecialBlockTypeOnceEveryNPieces == rhs.frequencySpecialBlockTypeOnceEveryNPieces
//		&& flashingSpecialType == rhs.flashingSpecialType
//		&& turnBackToNormalBlockAfterNPiecesLock == rhs.turnBackToNormalBlockAfterNPiecesLock
//		&& makePieceTypeWhenCleared == rhs.makePieceTypeWhenCleared
//		&& clearEveryOtherLineOnGridWhenCleared == rhs.clearEveryOtherLineOnGridWhenCleared
//		&& counterType == rhs.counterType
//		&& pacmanType == rhs.pacmanType
//		&& ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType == rhs.ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType
//		&& addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks == rhs.addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks
//		&& whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut == rhs.whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut
//		&& removeAllBlocksOfColorOnFieldBlockIsSetOn == rhs.removeAllBlocksOfColorOnFieldBlockIsSetOn
//		&& changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor == rhs.changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor
//		&& matchAnyColor == rhs.matchAnyColor
		;
}
//=========================================================================================================================
bool BlockType::operator!=(const BlockType& rhs) const
{//=========================================================================================================================
	return
		(*this == rhs) == false
		;
}

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>


template void BlockType::serialize<boost::archive::xml_oarchive>(boost::archive::xml_oarchive &ar, const unsigned int);
template void BlockType::serialize<boost::archive::xml_iarchive>(boost::archive::xml_iarchive &ar, const unsigned int);
//=========================================================================================================================
template <typename Archive>
void BlockType::serialize(Archive & ar, const unsigned int version)
{//=========================================================================================================================

	ar & BOOST_SERIALIZATION_NVP(name);
	ar & BOOST_SERIALIZATION_NVP(spriteName);
	ar & BOOST_SERIALIZATION_NVP(specialSpriteName);

	ar & BOOST_SERIALIZATION_NVP(useInNormalPieces);
	ar & BOOST_SERIALIZATION_NVP(useAsGarbage);
	ar & BOOST_SERIALIZATION_NVP(useAsPlayingFieldFiller);
	ar & BOOST_SERIALIZATION_NVP(ignoreWhenMovingDownBlocks);
	ar & BOOST_SERIALIZATION_NVP(chainConnectionsMustContainAtLeastOneBlockWithThisTrue);
	ar & BOOST_SERIALIZATION_NVP(ignoreWhenCheckingChainConnections);


	//ar & BOOST_SERIALIZATION_NVP(colors);
	importExport_colors.clear();
	for (int i = 0; i < colors.size(); i++)
	{
		BobColor *bp = colors.get(i);
		if (bp->name != "" && bp->name != "empty")
		{
			BobColor b;//keep this, custom copy constructor which doesnt copy uuid
			b = *bp;

//			boost::uuids::random_generator generator;
//			b.uuid = to_string(generator());
//			b.name = bp->name;
//			b.r = bp->r;
//			b.g = bp->g;
//			b.b = bp->b;
//			b.a = bp->a;

			importExport_colors.add(b);
		}
	}
	ar & BOOST_SERIALIZATION_NVP(importExport_colors);
	colors.clear();
	for (int i = 0; i < importExport_colors.size(); i++)
	{
		BobColor b = importExport_colors.get(i);
		BobColor *bp = BobColor::getColorByName(b.name);
		if (bp != nullptr && bp->name != "" && bp->name != "empty")
		{
			colors.add(bp);
		}
		else
		{
			//BobsGame::log.error("Could not find color on import with name:" + b.name);
		}
	}
	importExport_colors.clear();



	//ar & BOOST_SERIALIZATION_NVP(specialColor);
	importExport_specialColor = BobColor();
	if (specialColor != nullptr && specialColor->name != "" && specialColor->name != "empty")
	{
		importExport_specialColor = *specialColor;

//		boost::uuids::random_generator generator;
//		importExport_specialColor.uuid = to_string(generator());
//		importExport_specialColor.name = specialColor->name;
//		importExport_specialColor.r = specialColor->r;
//		importExport_specialColor.g = specialColor->g;
//		importExport_specialColor.b = specialColor->b;
//		importExport_specialColor.a = specialColor->a;

	}
	ar & BOOST_SERIALIZATION_NVP(importExport_specialColor);
	specialColor = nullptr;
	if (importExport_specialColor.name != "" && importExport_specialColor.name != "empty")
	{
		specialColor = BobColor::getColorByName(importExport_specialColor.name);
	}
    importExport_specialColor = BobColor();
    
    
    
    
    ar & BOOST_SERIALIZATION_NVP(randomSpecialBlockChanceOneOutOf);
    ar & BOOST_SERIALIZATION_NVP(frequencySpecialBlockTypeOnceEveryNPieces);
    
    ar & BOOST_SERIALIZATION_NVP(flashingSpecialType);
    ar & BOOST_SERIALIZATION_NVP(turnBackToNormalBlockAfterNPiecesLock);
    
    
    
	if (version == 0)
	{
		ArrayList<PieceType> importExport_makePieceTypeWhenCleared;
		ar & BOOST_SERIALIZATION_NVP(importExport_makePieceTypeWhenCleared);
		makePieceTypeWhenCleared_DEPRECATED.clear();
		for (int i = 0; i < importExport_makePieceTypeWhenCleared.size(); i++)
		{
			PieceType b = importExport_makePieceTypeWhenCleared.get(i);
			PieceType *bp = new PieceType();
			*bp = b;
			makePieceTypeWhenCleared_DEPRECATED.add(bp);
		}
		importExport_makePieceTypeWhenCleared.clear();


	}
	else
	{
		ar & BOOST_SERIALIZATION_NVP(makePieceTypeWhenCleared_UUID);
	}
    
    ar & BOOST_SERIALIZATION_NVP(clearEveryOtherLineOnGridWhenCleared);
    
    ar & BOOST_SERIALIZATION_NVP(counterType);
    ar & BOOST_SERIALIZATION_NVP(pacmanType);
    ar & BOOST_SERIALIZATION_NVP(pacJarType);
    ar & BOOST_SERIALIZATION_NVP(ticksToChangeDirection);
    
    
	if (version == 0)
	{
		ArrayList<BlockType> importExport_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType;
		ar & BOOST_SERIALIZATION_NVP(importExport_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType);
		ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_DEPRECATED.clear();
		{
			for (int i = 0; i < importExport_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType.size(); i++)
			{
				BlockType b = importExport_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType.get(i);
				BlockType *bp = new BlockType();
				*bp = b;
				ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_DEPRECATED.add(bp);
			}
		}
		importExport_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType.clear();
	}
	else
	{
		ar & BOOST_SERIALIZATION_NVP(ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID);
	}
    
    ar & BOOST_SERIALIZATION_NVP(addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks);
    
    
    
	importExport_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.clear();
	{
		for (int i = 0; i < whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); i++)
		{
			TurnFromBlockTypeToType *bp = whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(i);
			TurnFromBlockTypeToType b;
			b = *bp;
			importExport_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.add(b);
		}
	}
	ar & BOOST_SERIALIZATION_NVP(importExport_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut);
	whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.clear();
	{
		for (int i = 0; i < importExport_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); i++)
		{
			TurnFromBlockTypeToType b = importExport_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(i);
			TurnFromBlockTypeToType *bp = new TurnFromBlockTypeToType();
			*bp = b;
			whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.add(bp);
		}
	}
	importExport_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.clear();

    
    
    ar & BOOST_SERIALIZATION_NVP(removeAllBlocksOfColorOnFieldBlockIsSetOn);
    ar & BOOST_SERIALIZATION_NVP(changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor);
    ar & BOOST_SERIALIZATION_NVP(matchAnyColor);
    
	if (version>0)
	{
		ar & BOOST_SERIALIZATION_NVP(uuid);
	}
}



//=========================================================================================================================
Block::Block()
{//=========================================================================================================================

}

//=========================================================================================================================
Block::Block(GameLogic* game, Grid* grid, Piece* piece, BlockType* blockType)
{//=========================================================================================================================

	this->game = game;
	this->grid = grid;
	this->piece = piece;
	this->blockType = blockType;
}


//=========================================================================================================================
void Block::update()
{//=========================================================================================================================



	if(blockType->sprite==nullptr && blockType->spriteName.length() > 0)
	{
		blockType->sprite = getBobsGame()->getSpriteFromName(blockType->spriteName);
	}

	if (blockType->specialSprite == nullptr && blockType->specialSpriteName.length() > 0)
	{
		blockType->specialSprite = getBobsGame()->getSpriteFromName(blockType->specialSpriteName);
	}

	effectFadeTicks += getGameLogic()->ticks();

	ticksSinceLastMovement += getGameLogic()->ticks();


	if (slamming)
	{
		ticksSinceSlam += getGameLogic()->ticks();

		if (ticksSinceSlam >= 100)
		{
			slamming = false;
		}
	}

	if (locking)
	{
		lockAnimationFrameTicks += getGameLogic()->ticks();
		if (lockAnimationFrameTicks > 20)
		{
			lockAnimationFrameTicks = 0;
			if (lockingAnimationFrame < 8)
			{
				lockingAnimationFrame++;
			}
			else
			{
				lockingAnimationFrame = 0;
				locking = false;
			}
		}
	}

	if (fadingOut)
	{
		if (disappearingAlpha > 0.0f)
		{
			disappearingAlpha -= (float)(getGameLogic()->ticks()) * 0.005f;
		}

		if (disappearingAlpha < 0.0f)
		{
			disappearingAlpha = 0.0f;
		}

		if (disappearingAlpha == 0.0f)
		{
			fadingOut = false;

			getGameLogic()->fadingOutBlocks.remove(this);
			return;
		}
	}

	if (popping)
	{
		if (animationFrame == -1)
		{
			popping = false;
			int randomIndex = getGameLogic()->getRandomIntLessThan(blockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.size(),"Block::update");
			blockType = getGameLogic()->currentGameType->getBlockTypeByUUID(blockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.get(randomIndex));
		}
	}

	animationFrameTicks -= getGameLogic()->ticks();
	if (animationFrameTicks <= 0)
	{
		if (animationFrame >= 0)
		{
			animationFrameTicks = animationFrameSpeed;
			animationFrame++;
		}
		else
		{
			if (animationFrame == -1)
			{
				animationFrame++;
				animationFrameTicks = animationFrameSpeed;
				if (getSettings()->blockAnimationTicksRandomUpToBetweenLoop > 0)
				{
					animationFrameTicks += getGameLogic()->getRandomIntLessThan(getSettings()->blockAnimationTicksRandomUpToBetweenLoop,"Block::update");
				}
			}
		}
	}

	if(blockType->pacJarType)
	{
		directionChangeTicksCounter += getGameLogic()->ticks();
		if (directionChangeTicksCounter > blockType->ticksToChangeDirection)
		{
			directionChangeTicksCounter = 0;

			direction++;
			if (direction > 3)
			{
				direction = 0;
			}
		}
	}

	if (blockType->pacmanType && ateBlocks == false && fadingOut == false)
	{
		if (setInGrid)
		{
			ateBlocks = true;
			customInterpolationTicks = 1000;

			int x = xGrid;
			int y = yGrid;

			if (direction == UP)
			{
				for (int yy = y; yy >= 0; yy--)
				{
					if (grid->get(x, yy) != nullptr)
					{
						grid->remove(grid->get(x, yy), true, true);
					}
				}
				grid->moveToAndRemoveAndFadeOut(this, x, 0);
			}
			else
			if (direction == DOWN)
			{
				for (int yy = y; yy < grid->getHeight(); yy++)
				{
					if (grid->get(x, yy) != nullptr)
					{
						grid->remove(grid->get(x, yy), true, true);
					}
				}
				grid->moveToAndRemoveAndFadeOut(this, x, grid->getHeight() - 1);
			}
			else
			if (direction == LEFT)
			{
				for (int xx = x; xx >= 0; xx--)
				{
					if (grid->get(xx, y) != nullptr)
					{
						grid->remove(grid->get(xx, y), true, true);
					}
				}
				grid->moveToAndRemoveAndFadeOut(this, 0, y);
			}
			else
			if (direction == RIGHT)
			{
				for (int xx = x; xx < grid->getWidth(); xx++)
				{
					if (grid->get(xx, y) != nullptr)
					{
						grid->remove(grid->get(xx, y), true, true);
					}
				}
				grid->moveToAndRemoveAndFadeOut(this, grid->getWidth() - 1, y);
			}
			else
			{
				grid->remove(this, true, true);
			}
			
			
			

			getGameLogic()->forceGravityThisFrame = true;//TODO: probably only apply gravity to the relevant blocks
		}
		else
		{
			directionChangeTicksCounter += getGameLogic()->ticks();
			if (directionChangeTicksCounter > blockType->ticksToChangeDirection)
			{
				directionChangeTicksCounter = 0;

				direction++;
				if (direction > 3)
				{
					direction = 0;
				}
			}
		}
	}

	if (blockType->removeAllBlocksOfColorOnFieldBlockIsSetOn && ateBlocks == false && fadingOut == false)
	{
		if (setInGrid)
		{
			if (yGrid < grid->getHeight() - 1)
			{
				Block* a = grid->get(xGrid, yGrid + 1);
				if (a != nullptr && a->getColor() != nullptr && a->blockType->removeAllBlocksOfColorOnFieldBlockIsSetOn==false && a->blockType->changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor == false)//dont remove other diamonds
				{
					for (int y = 0; y < grid->getHeight(); y++)
					{
						for (int x = 0; x < grid->getWidth(); x++)
						{
							Block* b = grid->get(x, y);
							if (b != nullptr && b != this)
							{
								if (b->getColor() == a->getColor())
								{
									grid->remove(b, true, true);
								}
							}
						}
					}
				}
			}

			//this causes an error when it is a fading out diamondGem block called from fadingOutBlocks
			//i believe it is when there are multiple diamonds stacked, the top ones actually delete the bottom ones since they are the same color
			//so i'm checking to see if the grid actually contains it, otherwise i could not have it delete diamonds above
			//if(grid->contains(xGrid,yGrid))
			grid->remove(this, true, true);
			
			getGameLogic()->manuallyApplyGravityWithoutChainChecking();//TODO: probably only apply gravity to the relevant blocks
			getGameLogic()->forceGravityThisFrame = true;//TODO: doubt i need to do this because of above
			ateBlocks = true;
		}
	}

	if (blockType->changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor && didFlashingColoredDiamond == false && fadingOut == false)
	{
		if (setInGrid)
		{
			if (yGrid < grid->getHeight() - 1)
			{
				Block* a = grid->get(xGrid, yGrid + 1);
				if (a != nullptr && a->getColor() != nullptr && a->getColor() != this->getColor() && a->blockType->removeAllBlocksOfColorOnFieldBlockIsSetOn == false && a->blockType->changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor == false)//dont remove other diamonds
				{
					BobColor *colorToReplace = a->getColor();

					for (int y = 0; y < grid->getHeight(); y++)
					{
						for (int x = 0; x < grid->getWidth(); x++)
						{
							Block* b = grid->get(x, y);
							if (b != nullptr && b != this)
							{
								if (b->getColor() == colorToReplace)
								{
									b->setColor(this->getColor());
								}
							}
						}
					}
				}
			}
			//if (grid->contains(xGrid, yGrid))
			grid->remove(this, true, true);


			getGameLogic()->manuallyApplyGravityWithoutChainChecking();//TODO: probably only apply gravity to the relevant blocks
			getGameLogic()->forceGravityThisFrame = true;//TODO: doubt i need to do this because of above
			didFlashingColoredDiamond = true;
		}
	}


	colorFlashTicks += getGameLogic()->ticks();

	if (colorFlashTicks > colorFlashTicksPerPhase)
	{
		colorFlashTicks = 0;
		colorFlashInOutToggle = !colorFlashInOutToggle;
	}
	if (colorFlashInOutToggle == true)
	{
		colorFlash = colorFlashFrom + ((float)(colorFlashTicks) / (float)(colorFlashTicksPerPhase)) * (colorFlashTo - colorFlashFrom);
	}
	else
	{
		colorFlash = colorFlashTo - ((float)(colorFlashTicks) / (float)(colorFlashTicksPerPhase)) * (colorFlashTo - colorFlashFrom);
	}


	if (effectFadeTicks > effectFadeTicksPerPhase)
	{
		effectFadeTicks = 0;
		effectFadeInOutToggle = !effectFadeInOutToggle;
	}


	if (effectFadeInOutToggle == true)
	{
		effectAlpha = effectAlphaFrom + ((float)(effectFadeTicks) / (float)(effectFadeTicksPerPhase)) * (effectAlphaTo - effectAlphaFrom);
	}
	else
	{
		effectAlpha = effectAlphaTo - ((float)(effectFadeTicks) / (float)(effectFadeTicksPerPhase)) * (effectAlphaTo - effectAlphaFrom);
	}





	connectedUp = false;
	connectedDown = false;
	connectedLeft = false;
	connectedRight = false;

	connectedUpRight = false;
	connectedDownRight = false;
	connectedUpLeft = false;
	connectedDownLeft = false;

	if (getSettings()->blockRule_drawBlocksConnectedByColorIgnoringPiece)
	{
		if (connectedBlocksByColor.size() > 0)
		{
			for (int i = 0; i < connectedBlocksByColor.size(); i++)
			{
				Block* c = connectedBlocksByColor.get(i);
				if (c->xGrid == xGrid && c->yGrid == yGrid - 1)
				{
					connectedUp = true;
				}
				if (c->xGrid == xGrid && c->yGrid == yGrid + 1)
				{
					connectedDown = true;
				}
				if (c->xGrid == xGrid - 1 && c->yGrid == yGrid)
				{
					connectedLeft = true;
				}
				if (c->xGrid == xGrid + 1 && c->yGrid == yGrid)
				{
					connectedRight = true;
				}

				if (c->xGrid == xGrid - 1 && c->yGrid == yGrid - 1)
				{
					connectedUpLeft = true;
				}
				if (c->xGrid == xGrid + 1 && c->yGrid == yGrid - 1)
				{
					connectedUpRight = true;
				}
				if (c->xGrid == xGrid - 1 && c->yGrid == yGrid + 1)
				{
					connectedDownLeft = true;
				}
				if (c->xGrid == xGrid + 1 && c->yGrid == yGrid + 1)
				{
					connectedDownRight = true;
				}
			}
		}
	}

	if (getSettings()->blockRule_drawBlocksConnectedByPieceIgnoringColor)
	{
		if (connectedBlocksByPiece.size() > 0)
		{
			for (int i = 0; i < connectedBlocksByPiece.size(); i++)
			{
				Block* c = connectedBlocksByPiece.get(i);

				if (c->xInPiece == xInPiece && c->yInPiece == yInPiece - 1)
				{
					connectedUp = true;
				}
				if (c->xInPiece == xInPiece && c->yInPiece == yInPiece + 1)
				{
					connectedDown = true;
				}
				if (c->xInPiece == xInPiece - 1 && c->yInPiece == yInPiece)
				{
					connectedLeft = true;
				}
				if (c->xInPiece == xInPiece + 1 && c->yInPiece == yInPiece)
				{
					connectedRight = true;
				}

				if (c->xInPiece == xInPiece - 1 && c->yInPiece == yInPiece - 1)
				{
					connectedUpLeft = true;
				}
				if (c->xInPiece == xInPiece + 1 && c->yInPiece == yInPiece - 1)
				{
					connectedUpRight = true;
				}
				if (c->xInPiece == xInPiece - 1 && c->yInPiece == yInPiece + 1)
				{
					connectedDownLeft = true;
				}
				if (c->xInPiece == xInPiece + 1 && c->yInPiece == yInPiece + 1)
				{
					connectedDownRight = true;
				}


				if (c->xGrid == xGrid && c->yGrid == yGrid - 1)
				{
					connectedUp = true;
				}
				if (c->xGrid == xGrid && c->yGrid == yGrid + 1)
				{
					connectedDown = true;
				}
				if (c->xGrid == xGrid - 1 && c->yGrid == yGrid)
				{
					connectedLeft = true;
				}
				if (c->xGrid == xGrid + 1 && c->yGrid == yGrid)
				{
					connectedRight = true;
				}

				if (c->xGrid == xGrid - 1 && c->yGrid == yGrid - 1)
				{
					connectedUpLeft = true;
				}
				if (c->xGrid == xGrid + 1 && c->yGrid == yGrid - 1)
				{
					connectedUpRight = true;
				}
				if (c->xGrid == xGrid - 1 && c->yGrid == yGrid + 1)
				{
					connectedDownLeft = true;
				}
				if (c->xGrid == xGrid + 1 && c->yGrid == yGrid + 1)
				{
					connectedDownRight = true;
				}
			}
		}
	}

	//BobColor noColor;


	if (getSettings()->blockRule_drawBlocksConnectedByColorInPiece)
	{
		if (connectedBlocksByPiece.size() > 0)
		{
			for (int i = 0; i < connectedBlocksByPiece.size(); i++)
			{
				Block* c = connectedBlocksByPiece.get(i);

				if (c->xInPiece == xInPiece && c->yInPiece == yInPiece - 1 && c->color == color && color != nullptr)
				{
					connectedUp = true;
				}
				if (c->xInPiece == xInPiece && c->yInPiece == yInPiece + 1 && c->color == color && color != nullptr)
				{
					connectedDown = true;
				}
				if (c->xInPiece == xInPiece - 1 && c->yInPiece == yInPiece && c->color == color && color != nullptr)
				{
					connectedLeft = true;
				}
				if (c->xInPiece == xInPiece + 1 && c->yInPiece == yInPiece && c->color == color && color != nullptr)
				{
					connectedRight = true;
				}

				if (c->xInPiece == xInPiece - 1 && c->yInPiece == yInPiece - 1 && c->color == color && color != nullptr)
				{
					connectedUpLeft = true;
				}
				if (c->xInPiece == xInPiece + 1 && c->yInPiece == yInPiece - 1 && c->color == color && color != nullptr)
				{
					connectedUpRight = true;
				}
				if (c->xInPiece == xInPiece - 1 && c->yInPiece == yInPiece + 1 && c->color == color && color != nullptr)
				{
					connectedDownLeft = true;
				}
				if (c->xInPiece == xInPiece + 1 && c->yInPiece == yInPiece + 1 && c->color == color && color != nullptr)
				{
					connectedDownRight = true;
				}

				if (c->xGrid == xGrid && c->yGrid == yGrid - 1 && c->color == color && color != nullptr)
				{
					connectedUp = true;
				}
				if (c->xGrid == xGrid && c->yGrid == yGrid + 1 && c->color == color && color != nullptr)
				{
					connectedDown = true;
				}
				if (c->xGrid == xGrid - 1 && c->yGrid == yGrid && c->color == color && color != nullptr)
				{
					connectedLeft = true;
				}
				if (c->xGrid == xGrid + 1 && c->yGrid == yGrid && c->color == color && color != nullptr)
				{
					connectedRight = true;
				}

				if (c->xGrid == xGrid - 1 && c->yGrid == yGrid - 1 && c->color == color && color != nullptr)
				{
					connectedUpLeft = true;
				}
				if (c->xGrid == xGrid + 1 && c->yGrid == yGrid - 1 && c->color == color && color != nullptr)
				{
					connectedUpRight = true;
				}
				if (c->xGrid == xGrid - 1 && c->yGrid == yGrid + 1 && c->color == color && color != nullptr)
				{
					connectedDownLeft = true;
				}
				if (c->xGrid == xGrid + 1 && c->yGrid == yGrid + 1 && c->color == color && color != nullptr)
				{
					connectedDownRight = true;
				}
			}
		}
	}



	if (blockType->sprite != nullptr)
	{
		string animationName = "";


		if (connectedUp && connectedDown && connectedLeft && connectedRight)
		{
			animationName = ("ConnectedAll");
		}
		else if (connectedUp && connectedLeft && connectedRight)
		{
			animationName = ("ConnectedAllBottom");
		}
		else if (connectedDown && connectedLeft && connectedRight)
		{
			animationName = ("ConnectedAllTop");
		}
		else if (connectedRight && connectedUp && connectedDown)
		{
			animationName = ("ConnectedAllLeft");
		}
		else if (connectedLeft && connectedUp && connectedDown)
		{
			animationName = ("ConnectedAllRight");
		}

		else if (connectedLeft && connectedUp)
		{
			animationName = ("ConnectedUpLeft");
		}
		else if (connectedLeft && connectedDown)
		{
			animationName = ("ConnectedDownLeft");
		}
		else if (connectedRight && connectedUp)
		{
			animationName = ("ConnectedUpRight");
		}
		else if (connectedRight && connectedDown)
		{
			animationName = ("ConnectedDownRight");
		}

		else if (connectedUp && connectedDown)
		{
			animationName = ("ConnectedUpDown");
		}
		else if (connectedRight && connectedLeft)
		{
			animationName = ("ConnectedLeftRight");
		}

		else if (connectedRight)
		{
			animationName = ("ConnectedRight");
		}
		else if (connectedLeft)
		{
			animationName = ("ConnectedLeft");
		}
		else if (connectedUp)
		{
			animationName = ("ConnectedUp");
		}
		else if (connectedDown)
		{
			animationName = ("ConnectedDown");
		}


		if (direction != -1)
		{
			if (direction == UP)
			{
				animationName = "Up";
			}
			if (direction == DOWN)
			{
				animationName = "Down";
			}
			if (direction == LEFT)
			{
				animationName = "Left";
			}
			if (direction == RIGHT)
			{
				animationName = "Right";
			}
		}


		if (counterCount > -1)
		{
			if (blockType->sprite->getAnimationByName("" + to_string(counterCount)) != nullptr)animationName = "" + to_string(counterCount);
		}


		if (panic)
		{
			if (blockType->sprite->getAnimationByName("Panic") != nullptr)animationName = "Panic";
		}

		if (popping)
		{
			if (blockType->sprite->getAnimationByName("Popping") != nullptr)animationName = "Popping";
		}

		if (flashingToBeRemoved)
		{
			if (blockType->sprite->getAnimationByName("Flashing") != nullptr)animationName = "Flashing";
		}


		//if (anim == nullptr)anim = blockType->sprite->getFirstAnimation();
		if (animationName.length() > 0)
		{
			SpriteAnimationSequence* namedAnimation = blockType->sprite->getAnimationByName(animationName);
			if (namedAnimation != nullptr)anim = namedAnimation;
		}
		else anim = blockType->sprite->getFirstAnimation();

		if(anim==nullptr)anim = blockType->sprite->getFirstAnimation();

		int animLength = blockType->sprite->getAnimationNumFramesByAnimation(anim);
		if (animationFrame >= animLength)animationFrame = -1;
		
	}
}


//=========================================================================================================================
void Block::setXYOffsetInPiece(int x, int y)
{//=========================================================================================================================
	this->xInPiece = x;
	this->yInPiece = y;
}


//=========================================================================================================================
void Block::breakConnectionsInPiece()
{//=========================================================================================================================

	for (int i = 0; i < connectedBlocksByColor.size(); i++)
	{
		//remove this block from its connected blocks connectedBlocks list.
		Block* connectedBlock = connectedBlocksByColor.get(i);
		connectedBlock->connectedBlocksByColor.remove(this);
	}
	connectedBlocksByColor.clear();


	for (int i = 0; i < connectedBlocksByPiece.size(); i++)
	{
		//remove this block from its connected blocks connectedBlocks list.
		Block* connectedBlock = connectedBlocksByPiece.get(i);
		connectedBlock->connectedBlocksByPiece.remove(this);
	}
	connectedBlocksByPiece.clear();


	if (piece != nullptr)
	{
		//these should never happen due to above
		for (int i = 0; i < (int)piece->blocks.size(); i++)
		{
			Block* c = piece->blocks.get(i);
			while (c->connectedBlocksByColor.contains(this))
			{
				log.error("A block in this piece was connected to this block, but this block wasn't connected to that one.");
				c->connectedBlocksByColor.remove(this);
				
			}
			while (c->connectedBlocksByPiece.contains(this))
			{
				c->connectedBlocksByPiece.remove(this);
				log.error("A block in this piece was connected to this block, but this block wasn't connected to that one.");
			}
		}


		for (int i = 0; i < (int)piece->blocks.size(); i++)
		{
			if (piece->blocks.get(i) == this)
			{
				piece->blocks.removeAt(i);
				i = 0;
			}
		}

		//this should never happen due to above
		while (piece->blocks.contains(this))
		{
			piece->blocks.remove(this);

			log.error("Shouldn't happen!");
		}
	}
}


//=========================================================================================================================
float Block::getScreenX()
{//=========================================================================================================================
	return grid->getXInFBO() + xGrid * cellW();
}


//=========================================================================================================================
float Block::getScreenY()
{//=========================================================================================================================
	return grid->getYInFBO() + yGrid * cellH() + (grid->scrollPlayingFieldY/grid->scrollBlockIncrement)*cellH();
}


//=========================================================================================================================
float* Block::getInterpolatedScreenXY(float screenX, float screenY)
{//=========================================================================================================================
	if (screenX != lastScreenX || screenY != lastScreenY)
	{
		float fromX = 0;
		float fromY = 0;

		float w = (float)GLUtils::getViewportWidth();
		float h = (float)GLUtils::getViewportHeight();

		//sweep in from closest screen edge if coming from offscreen
		if (lastScreenX == -1)
		{
			if (screenX < w / 2)
			{
				fromX = screenX;
			}
			else
			{
				fromX = w - screenX;
			}
		}
		if (lastScreenY == -1)
		{
			if (screenY < h / 2)
			{
				fromY = screenY;
			}
			else
			{
				fromY = h - screenY;
			}
		}
		if (lastScreenX == -1 && lastScreenY == -1)
		{
			if (fromX < fromY)
			{
				if (screenX < w / 2)
				{
					lastScreenX = 0;
				}
				else
				{
					lastScreenX = w;
				}
				lastScreenY = screenY;
			}
			else
			{
				if (screenY < h / 2)
				{
					lastScreenY = 0;
				}
				else
				{
					lastScreenY = h;
				}
				lastScreenX = screenX;
			}
		}

		int ticks = (int)(getSettings()->blockMovementInterpolationTicks);
		if (customInterpolationTicks != -1)
		{
			ticks = customInterpolationTicks;
		}

		if (ticksSinceLastMovement < ticks)
		{
			// draw in between animation
			float xDiff = screenX - lastScreenX;
			float yDiff = screenY - lastScreenY;

			float betweenX = ((float)(ticksSinceLastMovement) / (float)(ticks)) * xDiff;
			float betweenY = ((float)(ticksSinceLastMovement) / (float)(ticks)) * yDiff;


			//added this to try and fix skipping
			if (abs(betweenX) > abs(xDiff))
			{
				betweenX = xDiff;
			}
			if (abs(betweenY) > abs(yDiff))
			{
				betweenY = yDiff;
			}


			screenX = lastScreenX + betweenX;
			screenY = lastScreenY + betweenY;
		}
		else
		{
			lastScreenX = screenX;
			lastScreenY = screenY;

			//added this to try and fix skipping, but i think it is "too" smooth? this is probably the issue.
			//ticksSinceLastMovement=0;
		}
	}
	else
	{
		lastScreenX = screenX;
		lastScreenY = screenY;
		ticksSinceLastMovement = 0;
	}


	float* xy = new float[2]{screenX,screenY};
	return xy;
}


//=========================================================================================================================
void Block::renderDisappearing()
{//=========================================================================================================================

	render(getScreenX(), getScreenY(), disappearingAlpha, 1.0f + (2.0f - (disappearingAlpha * 2.0f)), true, false);
}


//=========================================================================================================================
void Block::render(float screenX, float screenY, float a, float scale, bool interpolate, bool ghost)
{//=========================================================================================================================


	BobColor *renderColor = nullptr;

	//BobColor noColor;
	//PieceType noPieceType;

	if (overrideAnySpecialBehavior == false && blockType->specialColor != nullptr)
	{
		renderColor = new BobColor(*blockType->specialColor);
	}

	if (
		(overrideAnySpecialBehavior == false && blockType->flashingSpecialType)
		|| 
		(piece != nullptr && piece->overrideAnySpecialBehavior == false && piece->pieceType != nullptr && piece->pieceType->flashingSpecialType)
	)
	{
		BobColor *c = nullptr;
		
		if (color != nullptr)c = color;
				
		if (blockType->specialColor != nullptr)
		{
			c = blockType->specialColor;
		}
		if (c == nullptr)c = BobColor::gray;//TODO: should never happen?

		//if (renderColor != nullptr)delete renderColor;
		renderColor = new BobColor(c->rf() + colorFlash, c->gf() + colorFlash, c->bf() + colorFlash, c->af());
	}

	

	if (renderColor == nullptr)
	{
		if (color != nullptr)
		{
			renderColor = new BobColor(*color);
		}
		else
		{
			renderColor = new BobColor(*BobColor::black);
		}
	}


	
	float w = blockW() * scale;
	float h = blockH() * scale;

	//screenX = floor(screenX);
	//screenY = floor(screenY);
	//w = ceil(w);
	//h = ceil(h);

	if (interpolateSwappingWithX != 0)
	{
		if (interpolateSwappingWithX == -1)
		{
			screenX -= (w / (17 * 6)) * swapTicks;
		}
		if (interpolateSwappingWithX == 1)
		{
			screenX += (w / (17 * 6)) * swapTicks;
		}
		if (interpolateSwappingWithX == -2)
		{
			screenX -= (w / (17 * 6)) * swapTicks*2;
		}
		if (interpolateSwappingWithX == 2)
		{
			screenX += (w / (17 * 6)) * swapTicks*2;
		}
		interpolate = false;

		lastScreenX = screenX;
		lastScreenY = screenY;
		ticksSinceLastMovement = 0;
	}
	if (interpolateSwappingWithY != 0)
	{
		if (interpolateSwappingWithY == -1)
		{
			screenY -= (h / (17 * 6)) * swapTicks;
		}
		if (interpolateSwappingWithY == 1)
		{
			screenY += (h / (17 * 6)) * swapTicks;
		}
		if (interpolateSwappingWithY == -2)
		{
			screenY -= (h / (17 * 6)) * swapTicks*2;
		}
		if (interpolateSwappingWithY == 2)
		{
			screenY += (h / (17 * 6)) * swapTicks*2;
		}
		interpolate = false;

		lastScreenX = screenX;
		lastScreenY = screenY;
		ticksSinceLastMovement = 0;
	}

	if (interpolate)
	{
		float* xy = getInterpolatedScreenXY(screenX, screenY);

		screenX = xy[0];
		screenY = xy[1];

		delete[] xy;
	}


	//-------------------------------------------------
	//do locking animation, draw darker if locked into Grid()
	//-------------------------------------------------
	BobColor *textureColor = new BobColor(*renderColor);
	if (getSettings()->fadeBlocksDarkerWhenLocking && locking)
	{
		for (int i = 0; i < lockingAnimationFrame; i++)
		{
			textureColor->darker(0.1f);
		}

		if (lockingAnimationFrame > 5)
		{
			//delete textureColor;
			textureColor = new BobColor(*BobColor::white);
		}
	}
	else
	{
		if (getSettings()->blockRule_drawBlocksDarkerWhenLocked && setInGrid && flashingToBeRemoved == false)
		{
			textureColor->darker(0.5f); //.darker();//a=0.6f;//
		}
	}


	if (flashingToBeRemoved)
	{
		if (flashingToBeRemovedLightDarkToggle == true)
		{
			textureColor->lighter();
			textureColor->lighter();
			textureColor->lighter();
		}
		else
		{
			textureColor->darker();
			textureColor->darker();
			textureColor->darker();
		}
	}


	float r = textureColor->rf();
	float g = textureColor->gf();
	float b = textureColor->bf();


	if (slamming)
	{
		if (ticksSinceSlam < 100)
		{
			float xDiff = screenX - slamX;
			float yDiff = screenY - slamY;

			screenX = slamX;
			screenY = slamY;

			w += xDiff;
			h += yDiff;
		}
	}




	//-------------------------------------------------
	//if Piece() has color, draw color to background before draw Piece()
	//so that special blocks like spark balls inside of square pieces don't look so disconnected.
	//-------------------------------------------------
	//		if(Piece()!=null)
	//		{
	//			if(Piece().pieceType.color!=null)
	//			{
	//				Color c = Piece().pieceType.color;
	//				GLUtils::drawFilledRectXYWH(x,y,w,h,0,0,0,a);
	//				GLUtils::drawFilledRectXYWH(x+1*s,y+1*s,w-2*s,h-2*s,c.r(),c.g(),c.b(),a);
	//			}
	//		}


	//for special blocks that are larger than one tile (like the weight), we need to draw just the part of the frame we need
	if (overrideAnySpecialBehavior == false && piece != nullptr && piece->pieceType != nullptr && piece->pieceType->spriteName != string("") && piece->overrideAnySpecialBehavior == false)
	{
		//figure out what block we are in the piece

		//draw that part of the sprite


		float blocksWidth = (float)piece->getWidth();
		float blocksHeight = (float)piece->getHeight();
		float lowestX = (float)piece->getLowestOffsetX();
		float thisX = (float)xInPiece - lowestX;
		float lowestY = (float)piece->getLowestOffsetY();
		float thisY = (float)yInPiece - lowestY;


		Sprite* sprite = getBobsGame()->getSpriteFromName(piece->pieceType->spriteName);
		BobTexture* texture = sprite->texture;


		float x0InImage = (thisX / blocksWidth) + 1.0f/ sprite->getImageWidth();
		float x1InImage = ((thisX + 1) / blocksWidth) + 1.0f / sprite->getImageWidth();
		float y0InImage = (thisY / blocksHeight) + 1.0f / sprite->getImageHeight();
		float y1InImage = ((thisY + 1) / blocksHeight) + 1.0f / sprite->getImageHeight();


		float spriteImageWidth = (float)sprite->getImageWidth();
		float spriteImageHeight = (float)sprite->getImageHeight();


		float imageToTextureRatioX = (spriteImageWidth / (float)texture->getTextureWidth());
		float tx0 = x0InImage * imageToTextureRatioX;
		float tx1 = x1InImage * imageToTextureRatioX;
		float imageToTextureRatioY = (spriteImageHeight / (float)texture->getTextureHeight());
		float ty0 = y0InImage * imageToTextureRatioY;
		float ty1 = y1InImage * imageToTextureRatioY;


		//log.info(""+tx0+" "+tx1+" "+ty0+" "+ty1);


		float x0 = screenX;
		float x1 = screenX + w;
		float y0 = screenY;
		float y1 = screenY + h;
		sprite->draw(tx0, tx1, ty0, ty1, x0, x1, y0, y1, r, g, b, a, GLUtils::FILTER_LINEAR);

//		delete renderColor;
//		delete textureColor;
		return;
	}



	if (blockType->specialSprite != nullptr && overrideAnySpecialBehavior == false)
	{
		blockType->specialSprite->drawFrame(0, screenX, screenX + w, screenY, screenY + h, r, g, b, a, GLUtils::FILTER_LINEAR);
	}
	else if (blockType->sprite != nullptr)
	{
		int frame = animationFrame;
		if (frame == -1)frame = 0;
		if(anim!=nullptr)blockType->sprite->drawFrame(anim->frameStart + frame, screenX, screenX + w, screenY, screenY + h, r, g, b, a, GLUtils::FILTER_LINEAR);
	}


	if (getSettings()->blockRule_drawDotToSquareOffBlockCorners)
	{
		if (connectedDown && connectedRight && !connectedDownRight)GLUtils::drawFilledRectXYWH(screenX + w - 1.0f, screenY + h - 1.0f, 1.0f * scale, 1.0f * scale, r, g, b, a);
		if (connectedDown && connectedLeft && !connectedDownLeft)GLUtils::drawFilledRectXYWH(screenX, screenY + h - 1.0f, 1.0f * scale, 1.0f * scale, r, g, b, a);
		if (connectedUp && connectedLeft && !connectedUpLeft)GLUtils::drawFilledRectXYWH(screenX, screenY, 1.0f * scale, 1.0f * scale, r, g, b, a);
		if (connectedUp && connectedRight && !connectedUpRight)GLUtils::drawFilledRectXYWH(screenX + w - 1.0f, screenY, 1.0f * scale, 1.0f * scale, r, g, b, a);
	}


	if (getSettings()->blockRule_fillSolidSquareWhenSetInGrid && setInGrid && flashingToBeRemoved == false)
	{
		BobColor c = BobColor(*renderColor, 0.1f);
		GLUtils::drawFilledRectXYWH(screenX, screenY, w, h, c.rf(), c.gf(), c.bf(), c.af());
		//delete c;
	}


	if (getSettings()->drawDotOnCenterOfRotation)
	{
		BobColor dotColor = BobColor(*renderColor, 1.0f);
		dotColor.lighter();
		dotColor.lighter();
		if (xInPiece == 0 && yInPiece == 0)GLUtils::drawFilledRectXYWH(screenX + 3 * scale, screenY + 3 * scale, w - 6 * scale, h - 6 * scale, dotColor.rf(), dotColor.gf(), dotColor.bf(), a);
		//delete dotColor;
	}

//	delete renderColor;
//	delete textureColor;
}

//TODO: SLOW
//=========================================================================================================================
void Block::renderOutlines(float screenX, float screenY, float s)
{//=========================================================================================================================

	float w = blockW() * s;
	float h = blockH() * s;

	if (getSettings()->gridRule_outlineOpenBlockEdges && setInGrid == true && fadingOut == false)
	{
		if (grid != nullptr)
		{
			float gridAlpha = 1.0f;

			int gridOutlineWidth = 4; //TODO: getScale with screen res

			for (int j = 0; j < gridOutlineWidth; j++)
			{
				float i = (float)j;

				//left
				if (xGrid - 1 >= 0 && grid->get(xGrid - 1, yGrid) == nullptr)GLUtils::drawFilledRectXYWH(screenX - i, screenY, i, h, 1.0f, 1.0f, 1.0f, gridAlpha);
				//right
				if (xGrid + 1 <= grid->getWidth() - 1 && grid->get(xGrid + 1, yGrid) == nullptr)GLUtils::drawFilledRectXYWH(screenX + w, screenY, i, h, 1.0f, 1.0f, 1.0f, gridAlpha);

				//up
				if (yGrid - 1 >= 0 && grid->get(xGrid, yGrid - 1) == nullptr)GLUtils::drawFilledRectXYWH(screenX, screenY - i, w, i, 1.0f, 1.0f, 1.0f, gridAlpha);
				//down
				if (yGrid + 1 <= grid->getHeight() - 1 && grid->get(xGrid, yGrid + 1) == nullptr)GLUtils::drawFilledRectXYWH(screenX, screenY + h, w, i, 1.0f, 1.0f, 1.0f, gridAlpha);


				//if left and up is clear, draw pixel there
				if (xGrid - 1 >= 0)
					if (yGrid - 1 >= 0 && grid->get(xGrid - 1, yGrid - 1) == nullptr)
						GLUtils::drawFilledRectXYWH(screenX - i, screenY - i, i, i, 1.0f, 1.0f, 1.0f, gridAlpha);

				//if right and up is clear, draw pixel there
				if (xGrid + 1 <= grid->getWidth() - 1)
					if (yGrid - 1 >= 0 && grid->get(xGrid + 1, yGrid - 1) == nullptr)
						GLUtils::drawFilledRectXYWH(screenX + w, screenY - i, i, i, 1.0f, 1.0f, 1.0f, gridAlpha);

				//if left and down is clear, draw pixel there
				if (xGrid - 1 >= 0)
					if (yGrid + 1 <= grid->getHeight() - 1 && grid->get(xGrid - 1, yGrid + 1) == nullptr)
						GLUtils::drawFilledRectXYWH(screenX - i, screenY + h, i, i, 1.0f, 1.0f, 1.0f, gridAlpha);

				//if right and down is clear, draw pixel there
				if (xGrid + 1 <= grid->getWidth() - 1)
					if (yGrid + 1 <= grid->getHeight() - 1 && grid->get(xGrid + 1, yGrid + 1) == nullptr)
						GLUtils::drawFilledRectXYWH(screenX + w, screenY + h, i, i, 1.0f, 1.0f, 1.0f, gridAlpha);
			}
		}
	}

	//		if(Piece()!=null)
	//		{
	//			int blockNum = 0;
	//			for(int i=0;i<Piece().pieceType.numblocks;i++)
	//			{
	//				if(Piece().blocks.get(i)==this){blockNum=i;break;}
	//			}
	//
	//			GLUtils::drawOutlinedString(""+blockNum,(int)x,(int)y,Color.white);
	//			GLUtils::drawOutlinedString(""+xInPiece+","+yInPiece,(int)x,(int)y+4,Color.white);
	//		}
}


//=========================================================================================================================
void Block::setColor(BobColor *color)
{//=========================================================================================================================
	this->color = color;
}


//=========================================================================================================================
void Block::setRandomBlockTypeColor()
{//=========================================================================================================================

	int amtColors = this->blockType->colors.size();
	amtColors = min(amtColors, getGameLogic()->getCurrentDifficulty()->maximumBlockTypeColors);

	if (amtColors > 0) 
	{
		this->color = this->blockType->colors.get(getGameLogic()->getRandomIntLessThan(amtColors,"setRandomBlockTypeColor"));
	}
}

//
////=========================================================================================================================
//Color Block::getRandomMatrixColor()
//{//=========================================================================================================================
//	int i = getGameLogic()->getRandomIntLessThan(5);
//
//	if (i == 0)
//	{
//		return *Color::green;
//	}
//	if (i == 1)
//	{
//		return *Color::darkGreen;
//	}
//	if (i == 2)
//	{
//		return *Color::lightGreen;
//	}
//	if (i == 3)
//	{
//		return *Color::darkerGreen;
//	}
//	if (i == 4)
//	{
//		return *Color::lighterGreen;
//	}
//
//	return *Color::green;
//}
//
//
////=========================================================================================================================
//Color Block::getRandomRainbowColor()
//{//=========================================================================================================================
//	int i = getGameLogic()->getRandomIntLessThan(22);
//
//	if (i == 0)
//	{
//		return *Color::lightGreen;// ::lighter();
//	}
//	if (i == 1)
//	{
//		return *Color::green;
//	}
//	if (i == 2)
//	{
//		return *Color::darkGreen;// ::darker();
//	}
//	if (i == 3)
//	{
//		return *Color::lightRed;// ::lighter();
//	}
//	if (i == 4)
//	{
//		return *Color::red;
//	}
//	if (i == 5)
//	{
//		return *Color::darkRed;// ::darker();
//	}
//	if (i == 6)
//	{
//		return *Color::lightYellow;// ::lighter();
//	}
//	if (i == 7)
//	{
//		return *Color::yellow;
//	}
//	if (i == 8)
//	{
//		return *Color::darkYellow;// ::darker();
//	}
//	if (i == 9)
//	{
//		return *Color::lightPink;// ::lighter();
//	}
//	if (i == 10)
//	{
//		return *Color::pink;
//	}
//	if (i == 11)
//	{
//		return *Color::darkPink;// ::darker();
//	}
//	if (i == 12)
//	{
//		return *Color::lightPurple;// ::lighter();
//	}
//	if (i == 13)
//	{
//		return *Color::purple;
//	}
//	if (i == 14)
//	{
//		return *Color::darkPurple;// ::darker();
//	}
//	if (i == 15)
//	{
//		return *Color::lightOrange;// ::lighter();
//	}
//	if (i == 16)
//	{
//		return *Color::orange;
//	}
//	if (i == 17)
//	{
//		return *Color::darkOrange;// ::darker();
//	}
//	if (i == 18)
//	{
//		return *Color::lightBlue;// ::lighter();
//	}
//	if (i == 19)
//	{
//		return *Color::blue;
//	}
//	if (i == 20)
//	{
//		return *Color::darkBlue;// ::darker();
//	}
//	if (i == 21)
//	{
//		return *Color::lightMagenta;// ::lighter();
//	}
//	if (i == 21)
//	{
//		return *Color::magenta;
//	}
//	if (i == 21)
//	{
//		return *Color::darkMagenta;// ::darker();
//	}
//
//	return *Color::green;
//}
//
//
////=========================================================================================================================
//Color Block::getRandomGrayscaleColor()
//{//=========================================================================================================================
//	int i = getGameLogic()->getRandomIntLessThan(7);
//
//	if (i == 0)
//	{
//		return Color(0.2f, 0.2f, 0.2f);
//	}
//	if (i == 1)
//	{
//		return Color(0.3f, 0.3f, 0.3f);
//	}
//	if (i == 2)
//	{
//		return Color(0.4f, 0.4f, 0.4f);
//	}
//	if (i == 3)
//	{
//		return Color(0.5f, 0.5f, 0.5f);
//	}
//	if (i == 4)
//	{
//		return Color(0.6f, 0.6f, 0.6f);
//	}
//	if (i == 5)
//	{
//		return Color(0.7f, 0.7f, 0.7f);
//	}
//	if (i == 6)
//	{
//		return Color(0.8f, 0.8f, 0.8f);
//	}
//
//	return *Color::black;
//}

//=========================================================================================================================
int Block::cellW()
{//=========================================================================================================================
	return getGameLogic()->cellW();
}

//=========================================================================================================================
int Block::cellH()
{//=========================================================================================================================
	return getGameLogic()->cellH();
}

//=========================================================================================================================
int Block::blockW()
{//=========================================================================================================================
	return getGameLogic()->blockWidth;
}

//=========================================================================================================================
int Block::blockH()
{//=========================================================================================================================
	return getGameLogic()->blockHeight;
}

//=========================================================================================================================
GameType* Block::getSettings()
{//=========================================================================================================================
	return getGameLogic()->currentGameType;
}

//=========================================================================================================================
GameLogic* Block::getGameLogic()
{//=========================================================================================================================
	return game;
}

//=========================================================================================================================
BobsGame* Block::getBobsGame()
{//=========================================================================================================================
	return getGameLogic()->getBobsGame();
}

//=========================================================================================================================
BobColor* Block::getColor()
{//=========================================================================================================================
	return color;
}

//=========================================================================================================================
BobColor* Block::specialColor()
{//=========================================================================================================================



	if (blockType == nullptr)
	{
		return nullptr;
	}

	return blockType->specialColor;
}

