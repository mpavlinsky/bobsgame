//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include <Gwen/ControlList.h>
#include "../Utility/ArrayList.h"
#include "../Utility/Color.h"
#include "BobsGame.h"
class Logger;




//C# TO C++ CONVERTER NOTE: Forward class declarations:
class GameLogic;
class Grid;

class TurnFromBlockTypeToType;

//class Block;
//class BlockType;

class Piece;
class PieceType;

class GameType;

class Sprite;
class SpriteAnimationSequence;


enum class AnimationState //static
{
	NORMAL,
	DROPPING,
	TOUCHING_BOTTOM,
	SET_AT_BOTTOM,
	FLASHING,
	REMOVING,
	PRESSURE,
};




//=========================================================================================================================
class BlockType
{//=========================================================================================================================
public:
	string name = "";														Info name_Info = Info("Name", "Unique name of block type.");
	string uuid = "";
	

	string spriteName = "";													Info spriteName_Info = Info("Sprite", "Which preset graphic to assign to this block type.  Request new graphics in the forum, and more will be added.");
	string specialSpriteName = "";											Info specialSpriteName_Info = Info("Special sprite", "If a sprite has a special behavior which only lasts for some amount of time, you can override its normal sprite with this.  For instance, a block which contains a bomb icon which disappears after 3 pieces were placed.");

	bool useInNormalPieces = false;											Info useInNormalPieces_Info = Info("Use in normal pieces", "Whether this block type should be used in normal pieces that are generated at the top of the screen.  This should usually be turned on.");
	bool useAsGarbage = false;												Info useAsGarbage_Info = Info("Use as VS garbage", "Whether this block type should be used as garbage sent to the other player in multiplayer versus mode.");
	bool useAsPlayingFieldFiller = false;									Info useAsPlayingFieldFiller_Info = Info("Use as playing field filler", "Whether this block type should be used in filling the playing field.");
	bool ignoreWhenMovingDownBlocks = false;								Info ignoreWhenMovingDownBlocks_Info = Info("Ignore when moving down blocks", "Ignore this block type when applying gravity.");//used for viruses in drbob
	bool chainConnectionsMustContainAtLeastOneBlockWithThisTrue = false;	Info chainConnectionsMustContainAtLeastOneBlockWithThisTrue_Info = Info("Chain Connections Must Contain At Least One Of These Block Types", "When checking for chains, the chain must contain one of these blocks in order to qualify.");
	bool ignoreWhenCheckingChainConnections = false;						Info ignoreWhenCheckingChainConnections_Info = Info("Ignore When Checking Chain Connections", "This block type is neutral and is ignored when checking chains.  It can only be cleared through other means.");

	ArrayList<BobColor*> colors;												Info colors_Info = Info("Colors", "Possible colors that this block can have, randomly chosen from when creating a block.");
private:
	ArrayList<BobColor> importExport_colors;	
public:
	BobColor *specialColor = nullptr;													Info specialColor_Info = Info("Special Color", "If this is set, it will override the normal color until the block loses its special property.  For instance, you can disguise the true color of a block until some action happens.  For now, the only thing that does this is turnBackToNormalBlockAfterNPiecesLock.");
private:
	BobColor importExport_specialColor;
public:
	int randomSpecialBlockChanceOneOutOf = 0;								Info randomSpecialBlockChanceOneOutOf_Info = Info("Special: Random Special Block Chance One Out Of", "This block will be chosen randomly 1 out of n times when choosing from available blocks. Setting this makes the block a special type.");
	int frequencySpecialBlockTypeOnceEveryNPieces = 0;						Info frequencySpecialBlockTypeOnceEveryNPieces_Info = Info("Special: Frequency Special Block Type Once Every N Pieces", "This block will be chosen after n pieces are created. Setting this makes a block the special type.");

	bool flashingSpecialType = false;										Info flashingSpecialType_Info = Info("Special: Flashing Special Type", "This block will be flashing.");
	int turnBackToNormalBlockAfterNPiecesLock = -1;							Info turnBackToNormalBlockAfterNPiecesLock_Info = Info("Special: Turn Back To Normal Block After N Pieces Lock", "This block will stop flashing and lose its special properties after n pieces are set at the bottom.");

//private:
	//ArrayList<PieceType> importExport_makePieceTypeWhenCleared;
public:
	//don't use!!! use uuid!
	ArrayList<PieceType*> makePieceTypeWhenCleared_DEPRECATED;							Info makePieceTypeWhenCleared_Info = Info("Special: Make Piece Type When Cleared", "When this block is cleared, it will create this piece type in the queue of next pieces.");
	ArrayList<string> makePieceTypeWhenCleared_UUID;

	bool clearEveryOtherLineOnGridWhenCleared = false;						Info clearEveryOtherLineOnGridWhenCleared_Info = Info("Special: Clear Every Other Line On Grid When Cleared", "When this block is cleared it will remove every other line on the grid.");

	bool counterType = false;												Info counterType_Info = Info("Special: CounterType", "This block will count down from a number each time a piece is placed.  It cannot be cleared until it reaches zero.");
	bool pacmanType = false;												Info pacmanType_Info = Info("Special: PacType", "This block will rotate facing a direction, and when it is placed it will eat all blocks in that direction.");
	bool pacJarType = false;												Info pacJarType_Info = Info("Special: PacJarType", "This block will turn into a PacType when it is cleared, and then eat all blocks in the direction it faces.");
	//for pacman type
	int ticksToChangeDirection = 1000;										Info ticksToChangeDirection_Info = Info("Special: PacType: Ticks To Change Direction", "How many milliseconds it should wait to rotate direction.");

//private:
	//ArrayList<BlockType> importExport_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType;
public:
	//don't use!!! use uuid!
	ArrayList<BlockType*> ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_DEPRECATED;		Info ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_Info = Info("If Connected Up Down Left Right To Cleared Block Change Into This Type", "If a block that is touching this one is cleared, this block will transform into one of these block types.");
	ArrayList<string> ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID;

	bool addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks = false;				Info addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks_Info = Info("Add To Chain If Connected Up Down Left Right To Cleared Chain Blocks", "If a block that is touching this one is being cleared, this block should be cleared too even if it does not match.");

	ArrayList<TurnFromBlockTypeToType*> whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut;	Info whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut_Info = Info("When Set Turn All Touching Blocks Of FromTypes Into ToType And Fade Out", "When this block is set into the grid, turn any FromTypes into ToType and clear this block.");
//private:
	ArrayList<TurnFromBlockTypeToType> importExport_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut;
public:
	bool removeAllBlocksOfColorOnFieldBlockIsSetOn = false;									Info removeAllBlocksOfColorOnFieldBlockIsSetOn_Info = Info("Remove All Blocks Of Color On Field Block Is Set On", "When this block is set down, any blocks with the color it touches will be removed from the grid.");
	bool changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor = false;					Info changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor_Info = Info("Change All Blocks Of Color On Field Block Is Set On To This Color", "When this block is set down, any blocks with the color it touches will change into this color.");
	bool matchAnyColor = false;																Info matchAnyColor_Info = Info("Match Any Color", "This block will match any color and make chain if possible.");

	

	bool operator==(const BlockType& rhs) const;
	bool operator!=(const BlockType& rhs) const;

	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version);
	

	static BlockType* emptyBlockType;

	Sprite* sprite = nullptr;//dont serialize these
	Sprite* specialSprite = nullptr;
//	BlockType();
//	BlockType(const string& spriteName, ArrayList<Color*>* colors);
//	BlockType(const string& spriteName, ArrayList<Color*>* colors, Color* specialColor);
//	BlockType(const string& spriteName, ArrayList<Color*>* colors, int randomSpecialBlockChanceOneOutOf, int frequencySpecialBlockTypeOnceEveryNBlocks);
//	BlockType(const string& spriteName, ArrayList<Color*>* colors, Color* specialColor, int randomSpecialBlockChanceOneOutOf, int frequencySpecialBlockTypeOnceEveryNBlocks);
//	BlockType(const string& spriteName, const string& specialSpriteName, ArrayList<Color*>* colors, Color* specialColor, int randomSpecialBlockChanceOneOutOf, int frequencySpecialBlockTypeOnceEveryNBlocks);
//	bool isSpecialType();
//=========================================================================================================================
	BlockType()
	{//=========================================================================================================================
		name = "empty";

		boost::uuids::random_generator generator;
		uuid = to_string(generator());
	}
	//=========================================================================================================================
	BlockType(const string &name, const string& spriteName, const string& specialSpriteName, ArrayList<BobColor*> *colorsArray, BobColor *specialColor, int randomSpecialBlockChanceOneOutOf, int frequencySpecialBlockTypeOnceEveryNBlocks)
	{//=========================================================================================================================
		this->name = name;
		this->spriteName = spriteName;
		this->specialSpriteName = specialSpriteName;
		if (colorsArray != nullptr)
		{
			for(int i=0;i<colorsArray->size();i++)
			{
				this->colors.add(colorsArray->get(i));
			}
			
		}
		this->specialColor = specialColor;
		this->randomSpecialBlockChanceOneOutOf = randomSpecialBlockChanceOneOutOf;
		this->frequencySpecialBlockTypeOnceEveryNPieces = frequencySpecialBlockTypeOnceEveryNBlocks;

		boost::uuids::random_generator generator;
		uuid = to_string(generator());
	}
	//=========================================================================================================================
	bool isNormalType()
	{//=========================================================================================================================
		if (useInNormalPieces)
		{
			return true;
		}

		return false;
	}

	//=========================================================================================================================
	bool isSpecialType()
	{//=========================================================================================================================
		if (randomSpecialBlockChanceOneOutOf != 0)
		{
			return true;
		}
		if (frequencySpecialBlockTypeOnceEveryNPieces != 0)
		{
			return true;
		}
		if (flashingSpecialType != false)
		{
			return true;
		}

		if (makePieceTypeWhenCleared_UUID.size() > 0)
		{
			return true;
		}
		if (clearEveryOtherLineOnGridWhenCleared != false)
		{
			return true;
		}

		return false;
	}

};

BOOST_CLASS_VERSION(BlockType, 1)
BOOST_CLASS_TRACKING(BlockType, boost::serialization::track_never)
//=========================================================================================================================
class TurnFromBlockTypeToType //static
{//=========================================================================================================================
public:
	//don't use!!!
	string fromType_DEPRECATED = "";
	//don't use!!!
	string toType_DEPRECATED = "";

	string fromType_UUID = "";
	string toType_UUID = "";
private:
//	string importExport_fromType;
//	string importExport_toType;
public:
	bool operator==(const TurnFromBlockTypeToType& rhs) const
	{
		return
			fromType_UUID == rhs.fromType_UUID
			&& toType_UUID == rhs.toType_UUID
			;
	}
	bool operator!=(const TurnFromBlockTypeToType& rhs) const
	{
		return
			(*this == rhs) == false
			;
	}
	
	TurnFromBlockTypeToType() {}
	TurnFromBlockTypeToType(string fromUUID,string toUUID)
	{
		fromType_UUID = fromUUID;
		toType_UUID = toUUID;
	}

	string getName(GameType *g) { return g->getBlockTypeByUUID(fromType_UUID)->name + "->" + g->getBlockTypeByUUID(toType_UUID)->name; }

	//=========================================================================================================================
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version)
	{//=========================================================================================================================

		if (version == 0)
		{
			string fromType = "";
			string toType = "";
			ar & BOOST_SERIALIZATION_NVP(fromType);
			ar & BOOST_SERIALIZATION_NVP(toType);
			fromType_DEPRECATED = fromType;
			toType_DEPRECATED = toType;
		}

		if(version>0)
		{
			ar & BOOST_SERIALIZATION_NVP(fromType_UUID);
			ar & BOOST_SERIALIZATION_NVP(toType_UUID);
		}
	}

	
};

BOOST_CLASS_VERSION(TurnFromBlockTypeToType, 1)
BOOST_CLASS_TRACKING(TurnFromBlockTypeToType, boost::serialization::track_never)
//=========================================================================================================================
class Block
{//=========================================================================================================================
public:

	static Logger log;

	//Color noColor;

	GameLogic* game = nullptr;
	Grid* grid = nullptr;







	Piece* piece = nullptr;
	ArrayList<Block*> connectedBlocksByPiece;
	ArrayList<Block*> connectedBlocksByColor;

	int xInPiece = 0; //offset in Piece() block is in
	int yInPiece = 0;

	int xGrid = -1;
	int yGrid = -1;

	BlockType *blockType = nullptr;

private:
	BobColor *color = nullptr;

public:
	float effectAlphaFrom = 0.5f;
	float effectAlphaTo = 0.8f;
	long long effectFadeTicksPerPhase = 1000;
private:
	float effectAlpha = 0.5f; //effectAlphaFrom;
	long long effectFadeTicks = 0;
	bool effectFadeInOutToggle = false;


public:
	float colorFlashFrom = 0.0f;
	float colorFlashTo = 1.0f;
	long long colorFlashTicksPerPhase = 100;
private:
	float colorFlash = 0.0f; //colorFlashFrom;
	long long colorFlashTicks = 0;
	bool colorFlashInOutToggle = false;

public:
	bool overrideAnySpecialBehavior = false;

	int interpolateSwappingWithX = 0; //-1 left  0 none  1 right
	int interpolateSwappingWithY = 0; //-1 up  0 none  1 down
	long long swapTicks = 0;
	bool flashingToBeRemoved = false;
	bool flashingToBeRemovedLightDarkToggle = false;

	bool setInGrid = false;
	bool locking = false;
	int lockingAnimationFrame = 0;
	long long lockAnimationFrameTicks = 0;

	bool fadingOut = false;
	float disappearingAlpha = 1.0f;

	float lastScreenX = -1;
	float lastScreenY = -1;

	long long ticksSinceLastMovement = 0;

	bool slamming = false;
private:
	long long ticksSinceSlam = 0;
public:
	float slamX = 0;
	float slamY = 0;

	AnimationState animationState = AnimationState::NORMAL;
	int animationFrame = 0;
	long long animationFrameTicks = 0;
	int animationFrameSpeed = 100;

	int counterCount = -2;

	bool didFlashingColoredDiamond = false;
	bool ateBlocks = false; //for pacman type
	int direction = -1; //for pacman type
	long long directionChangeTicksCounter = 0; //for pacman type
	

	const static int UP = 0;
	const static int LEFT = 1;
	const static int DOWN = 2;
	const static int RIGHT = 3;

private:
	int customInterpolationTicks = -1; //used for pacman

public:
	bool popping = false;
	bool panic = false;



	bool connectedUp = false;
	bool connectedDown = false;
	bool connectedLeft = false;
	bool connectedRight = false;

	bool connectedUpRight = false;
	bool connectedDownRight = false;
	bool connectedUpLeft = false;
	bool connectedDownLeft = false;


	SpriteAnimationSequence* anim = nullptr;

//	bool operator==(const Block& rhs) const
//	{
//		return
//			  piece == rhs.piece
//			&&connectedBlocksByPiece == rhs.connectedBlocksByPiece
//			&&connectedBlocksByColor == rhs.connectedBlocksByColor
//			&&xInPiece == rhs.xInPiece
//			&&yInPiece == rhs.yInPiece
//			&&xGrid == rhs.xGrid
//			&&yGrid == rhs.yGrid
//			&&blockType == rhs.blockType
//			&&color == rhs.color
//			&&effectAlphaFrom == rhs.effectAlphaFrom
//			&&effectAlphaTo == rhs.effectAlphaTo
//			&&effectFadeTicksPerPhase == rhs.effectFadeTicksPerPhase
//			&&effectAlpha == rhs.effectAlpha
//			&&effectFadeTicks == rhs.effectFadeTicks
//			&&effectFadeInOutToggle == rhs.effectFadeInOutToggle
//			&&colorFlashFrom == rhs.colorFlashFrom
//			&&colorFlashTo == rhs.colorFlashTo
//			&&colorFlashTicksPerPhase == rhs.colorFlashTicksPerPhase
//			&&colorFlash == rhs.colorFlash
//			&&colorFlashTicks == rhs.colorFlashTicks
//			&&colorFlashInOutToggle == rhs.colorFlashInOutToggle
//			&&overrideAnySpecialBehavior == rhs.overrideAnySpecialBehavior
//			&&swappingWith == rhs.swappingWith
//			&&swapTicks == rhs.swapTicks
//			&&flashingToBeRemoved == rhs.flashingToBeRemoved
//			&&flashingToBeRemovedLightDarkToggle == rhs.flashingToBeRemovedLightDarkToggle
//			&&setInGrid == rhs.setInGrid
//			&&locking == rhs.locking
//			&&lockingAnimationFrame == rhs.lockingAnimationFrame
//			&&lockAnimationFrameTicks == rhs.lockAnimationFrameTicks
//			&&fadingOut == rhs.fadingOut
//			&&disappearingAlpha == rhs.disappearingAlpha
//			&&lastScreenX == rhs.lastScreenX
//			&&lastScreenY == rhs.lastScreenY
//			&&ticksSinceLastMovement == rhs.ticksSinceLastMovement
//			&&slamming == rhs.slamming
//			&&ticksSinceSlam == rhs.ticksSinceSlam
//			&&slamX == rhs.slamX
//			&&slamY == rhs.slamY
//			&&animationState == rhs.animationState
//			&&animationFrame == rhs.animationFrame
//			&&animationFrameTicks == rhs.animationFrameTicks
//			&&animationFrameSpeed == rhs.animationFrameSpeed
//			&&counterCount == rhs.counterCount
//			&&didFlashingColoredDiamond == rhs.didFlashingColoredDiamond
//			&&ateBlocks == rhs.ateBlocks
//			&&direction == rhs.direction
//			&&directionChangeTicks == rhs.directionChangeTicks
//			&&customInterpolationTicks == rhs.customInterpolationTicks
//			&&popping == rhs.popping
//			&&panic == rhs.panic
//			;
//	}
//	bool operator!=(const Block& rhs) const
//	{
//		return
//			(*this == rhs) == false
//			;
//	}

	Block();
	Block(GameLogic* game, Grid* grid, Piece *piece, BlockType *blockType);
	void update();
	void setXYOffsetInPiece(int x, int y);
	void breakConnectionsInPiece();
	float getScreenX();
	float getScreenY();
	float* getInterpolatedScreenXY(float screenX, float screenY);
	void renderDisappearing();
	void render(float screenX, float screenY, float a, float scale, bool interpolate, bool ghost);
	void renderOutlines(float screenX, float screenY, float s);
	void setColor(BobColor *color);
	void setRandomBlockTypeColor();
//	Color getRandomMatrixColor();
//	Color getRandomRainbowColor();
//	Color getRandomGrayscaleColor();
	int cellW();
	int cellH();
	int blockW();
	int blockH();
	GameType* getSettings();
	GameLogic* getGameLogic();
	BobsGame* getBobsGame();
	BobColor *getColor();
	BobColor *specialColor();
};

