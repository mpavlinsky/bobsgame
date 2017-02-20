//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include "Piece.h"
#include "Block.h"
#include "../Utility/FileUtils.h"

#include <iostream>
#include <sstream>

class Logger;



class GameLogic;


//enum class Difficulty
//{
//	BEGINNER,
//	EASY,
//	NORMAL,
//	HARD,
//	INSANE,
//	
//};

//=========================================================================================================================
class DifficultyType
{//=========================================================================================================================
public:
	string name = "";								//Info name_Info = Info("Name", "The name of the difficulty as shown in the settings.");

	int initialLineDropSpeedTicks = 1000;			Info initialLineDropSpeedTicks_Info = Info("Initial Line Drop Speed Ticks", "The initial (slowest) time in milliseconds a block should take to drop one line.");
	int minimumLineDropSpeedTicks = 64;				Info minimumLineDropSpeedTicks_Info = Info("Min Line Drop Speed Ticks", "The minimum (fastest) time in milliseconds a block shoudl take to drop one line.");
	int maxStackRise = 400;							Info maxStackRise_Info = Info("Initial Stack Rise Ticks", "The initial (slowest) speed that the stack can rise in milliseconds per 16th of a block.");
	int minStackRise = 30;							Info minStackRise_Info = Info("Min Stack Rise Ticks", "The maximum (fastest) speed that the stack can rise in milliseconds per 16th of a block.");

	int extraStage1Level = 10;						Info extraStage1Level_Info = Info("Extra Stage 1 Level", "");
	int extraStage2Level = 15;						Info extraStage2Level_Info = Info("Extra Stage 2 Level", "");
	int extraStage3Level = 20;						Info extraStage3Level_Info = Info("Extra Stage 3 Level", "");
	int extraStage4Level = 25;						Info extraStage4Level_Info = Info("Extra Stage 4 Level", "");
	int creditsLevel = 30;							Info creditsLevel_Info = Info("Credits (Final) Level", "");

	int playingFieldGarbageSpawnRuleAmount = 5;			Info playingFieldGarbageSpawnRuleAmount_Info = Info("Playing Field Garbage Spawn Rule Amount", "Number of blocks or pieces or time (See spawn rule) until garbage is spawned from the bottom.");

	int maximumBlockTypeColors = 8;						Info maximumBlockTypeColors_Info = Info("Maximum Block Colors", "Set the maximum number of colors to use, if less than the amount of colors set, it will only use the colors up to this number.  For instance, you may specify a block type to have 8 possible colors, but on beginner mode it only uses 3.  This will apply to all block types.");
	int randomlyFillGridAmount = 30;												Info randomlyFillGridAmount_Info = Info("Drop: Randomly Fill Grid Amount", "How many blocks to fill the playing field with.");
	int randomlyFillStackAmount = 30;											Info randomlyFillStackAmount_Info = Info("Stack: Randomly Fill Stack Amount", "How many blocks to start the stack filled with.");


	ArrayList<PieceType*> pieceTypesToDisallow_DEPRECATED;		Info pieceTypesToDisallow_Info = Info("Piece Types To Disallow", "Add pieces here if you want them disabled for this difficulty level, for instance, on beginner modes you can have less shapes.");
	ArrayList<BlockType*> blockTypesToDisallow_DEPRECATED;		Info blockTypesToDisallow_Info = Info("Block Types To Disallow", "Add blocks here if you want them disabled for this difficulty level, for instance, on beginner modes you can disable special blocks.");
	//ArrayList<BobColor*> colorsToDisallowInBlockTypes;	Info colorsToDisallowInBlockTypes_Info = Info("Colors To Disallow in Block Types", "Add colors here if you want them disabled for this difficulty level, for instance, on beginner modes you can have less colors to match.");

	ArrayList<string> pieceTypesToDisallow_UUID;
	ArrayList<string> blockTypesToDisallow_UUID;

private:
	//ArrayList<PieceType> importExport_pieceTypesToDisallow;
	//ArrayList<BlockType> importExport_blockTypesToDisallow;
public:

	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version);
	
};
BOOST_CLASS_VERSION(DifficultyType, 1)
BOOST_CLASS_TRACKING(DifficultyType, boost::serialization::track_never)


//=========================================================================================================================
enum class ScoreType
{//=========================================================================================================================
	LINES_CLEARED,
	BLOCKS_CLEARED,
	PIECES_MADE,
};

//=========================================================================================================================
enum class DropLockType
{//=========================================================================================================================
	HARD_DROP_INSTANT_LOCK,
	SOFT_DROP_INSTANT_LOCK,
	NEITHER_INSTANT_LOCK,
};

//=========================================================================================================================
enum class GarbageType
{//=========================================================================================================================
	MATCH_BOTTOM_ROW,
	RANDOM,
	ZIGZAG_PATTERN,
};

//=========================================================================================================================
enum class GarbageSpawnRule
{//=========================================================================================================================
	NONE,
	TICKS,
	LINES_CLEARED,
	BLOCKS_CLEARED,
	PIECES_MADE,
};
//=========================================================================================================================
enum class GameMode
{//=========================================================================================================================
	DROP,
	STACK,

};
//=========================================================================================================================
enum class CursorType
{//=========================================================================================================================
	ONE_BLOCK_PICK_UP,
	TWO_BLOCK_HORIZONTAL,
	TWO_BLOCK_VERTICAL,
	THREE_BLOCK_HORIZONTAL,
	THREE_BLOCK_VERTICAL,
	QUAD_BLOCK_ROTATE,
};

//enum class CursorBehavior
//{
//	PICK_UP,
//	SWAP_OR_ROTATE,//TODO: could do this instead but have to replace holdingBlock with array and store order etc
//};
//=========================================================================================================================
enum class VSGarbageRule
{//=========================================================================================================================
	FALL_FROM_CEILING_IN_EVEN_ROWS,
	RISE_FROM_FLOOR_IN_EVEN_ROWS,
	//
	//		FALL_IN_1_RANDOM_COLUMN,
	//		FALL_IN_2_RANDOM_COLUMNS,
	//		FALL_IN_3_RANDOM_COLUMNS,
	//
	//		FALL_IN_1_COLUMN_FROM_LEFT,
	//		FALL_IN_2_COLUMNS_FROM_LEFT,
	//		FALL_IN_3_COLUMNS_FROM_LEFT,
	//
	//		FALL_IN_1_COLUMN_FROM_RIGHT,
	//		FALL_IN_2_COLUMNS_FROM_RIGHT,
	//		FALL_IN_3_COLUMNS_FROM_RIGHT,
	//
	//		FALL_IN_1_COLUMN_ON_EACH_SIDE,
	//		FALL_IN_2_COLUMNS_ON_EACH_SIDE,
	//		FALL_IN_3_COLUMNS_ON_EACH_SIDE,
	//
	//		FALL_IN_DIAGONAL_STEPS_DECREASING_FROM_SIDES_TO_MIDDLE,// /\
	   //		FALL_IN_DIAGONAL_STEPS_INCREASING_FROM_SIDES_TO_MIDDLE, // \/
};


//=========================================================================================================================
class GameType
{//=========================================================================================================================
public:

	//used for custom game editor
	bool builtInType = false;
	bool downloaded = false;
	//string loadedFilename = "";
	string uuid = "";

	//filled in from server
	long long creatorUserID = -1;
	string creatorUserName = "";
	long long dateCreated = -1;
	long long lastModified = -1;
	long long howManyTimesUpdated = -1;
	long long upVotes = -1;
	long long downVotes = -1;
	string yourVote = "none";

	static DifficultyType* difficulty_BEGINNER;
	static DifficultyType* difficulty_EASY;
	static DifficultyType* difficulty_NORMAL;
	static DifficultyType* difficulty_HARD;
	static DifficultyType* difficulty_INSANE;
	static DifficultyType* difficulty_IMPOSSIBLE;


	static Logger log;


	string toBase64GZippedXML();
	BlockType* getBlockTypeByName(string s);
	PieceType* getPieceTypeByName(string s);
	BlockType* getBlockTypeByUUID(string s);
	PieceType* getPieceTypeByUUID(string s);
	static GameType* fromBase64GZippedXML(string b64GZipJSON);

	//Color noColor;
	//PieceType noPieceType;
	//BlockType noBlockType;
	//ArrayList<Color> emptyColors;

//	const BobColor clear = *BobColor::clear;
//	const BobColor transparent = *BobColor::transparent;
//	const BobColor black = *BobColor::black;
//	const BobColor darkerGray = *BobColor::darkerGray;
//	const BobColor darkGray = *BobColor::darkGray;
//	const BobColor gray = *BobColor::gray;
//	const BobColor lightGray = *BobColor::lightGray;
//	const BobColor lighterGray = *BobColor::lighterGray;
//	const BobColor white = *BobColor::white;
//	const BobColor cyan = *BobColor::cyan; 
//	const BobColor lightCyan = *BobColor::lightCyan; 
//	const BobColor lighterCyan = *BobColor::lighterCyan; 
//	const BobColor darkCyan = *BobColor::darkCyan; 
//	const BobColor darkerCyan = *BobColor::darkerCyan; 
//	const BobColor magenta = *BobColor::magenta; 
//	const BobColor lightMagenta = *BobColor::lightMagenta; 
//	const BobColor lighterMagenta = *BobColor::lighterMagenta; 
//	const BobColor darkMagenta = *BobColor::darkMagenta; 
//	const BobColor darkerMagenta = *BobColor::darkerMagenta; 
//	const BobColor yellow = *BobColor::yellow; 
//	const BobColor lightYellow = *BobColor::lightYellow; 
//	const BobColor lighterYellow = *BobColor::lighterYellow; 
//	const BobColor darkYellow = *BobColor::darkYellow; 
//	const BobColor darkerYellow = *BobColor::darkerYellow; 
//	const BobColor orange = *BobColor::orange; 
//	const BobColor lightOrange = *BobColor::lightOrange; 
//	const BobColor lighterOrange = *BobColor::lighterOrange; 
//	const BobColor darkOrange = *BobColor::darkOrange; 
//	const BobColor darkerOrange = *BobColor::darkerOrange; 
//	const BobColor red = *BobColor::red; 
//	const BobColor lightRed = *BobColor::lightRed; 
//	const BobColor lighterRed = *BobColor::lighterRed; 
//	const BobColor darkRed = *BobColor::darkRed; 
//	const BobColor darkerRed = *BobColor::darkerRed; 
//	const BobColor pink = *BobColor::pink; 
//	const BobColor lightPink = *BobColor::lightPink; 
//	const BobColor lighterPink = *BobColor::lighterPink; 
//	const BobColor darkPink = *BobColor::darkPink; 
//	const BobColor darkerPink = *BobColor::darkerPink; 
//	const BobColor purple = *BobColor::purple; 
//	const BobColor darkPurple = *BobColor::darkPurple; 
//	const BobColor darkerPurple = *BobColor::darkerPurple; 
//	const BobColor lightPurple = *BobColor::lightPurple; 
//	const BobColor lighterPurple = *BobColor::lighterPurple; 
//	const BobColor blue = *BobColor::blue; 
//	const BobColor lightBlue = *BobColor::lightBlue; 
//	const BobColor lighterBlue = *BobColor::lighterBlue; 
//	const BobColor darkBlue = *BobColor::darkBlue; 
//	const BobColor darkerBlue = *BobColor::darkerBlue; 
//	const BobColor green = *BobColor::green;
//	const BobColor lighterGreen = *BobColor::lighterGreen;
//	const BobColor lightGreen = *BobColor::lightGreen;
//	const BobColor darkGreen = *BobColor::darkGreen;
//	const BobColor darkerGreen = *BobColor::darkerGreen;
//	const BobColor aqua = *BobColor::aqua;
//	const BobColor lighterAqua = *BobColor::lighterAqua;
//	const BobColor lightAqua = *BobColor::lightAqua;
//	const BobColor darkAqua = *BobColor::darkAqua;
//	const BobColor darkerAqua = *BobColor::darkerAqua;
//	const BobColor turquoise = *BobColor::turquoise;
//	const BobColor lighterTurquoise = *BobColor::lighterTurquoise;
//	const BobColor lightTurquoise = *BobColor::lightTurquoise;
//	const BobColor darkTurquoise = *BobColor::darkTurquoise;
//	const BobColor darkerTurquoise = *BobColor::darkerTurquoise;
//	const BobColor olive = *BobColor::olive;
//	const BobColor burgandy = *BobColor::burgandy;
//	const BobColor wine = *BobColor::wine;


	//---------------------------------------------------
	// music and sound
	//----------------------------------------------------

	string normalMusic = "";
	string fastMusic = "";
	string winMusic = "";
	string loseMusic = "";
	string deadMusic = "";
	string creditsMusic = "";

	string blocksFlashingSound = "slam";
	string singleLineFlashingSound = "single";
	string doubleLineFlashingSound = "double";
	string tripleLineFlashingSound = "triple";
	string quadLineFlashingSound = "sosumi";

	string hardDropSwishSound = "";
	string hardDropClankSound = "slam2";
	string switchHoldPieceSound = "hold";
	string cantHoldPieceSound = "buzz";

	string moveUpSound = "tick";
	string moveDownSound = "tick";
	string moveLeftSound = "tick";
	string moveRightSound = "tick";


	string pieceSetSound = "lock";
	string touchBottomSound = "touchblock";
	string wallKickSound = "wallkick";
	string doubleWallKickSound = "doublewallkick";
	string diagonalWallKickSound = "specialwallkick";
	string floorKickSound = "floorkick";
	string pieceFlip180Sound = "flip";


	string rotateSound = "rotate";
	string levelUpSound = "levelup";


	string extraStage1Sound = "gtbling";
	string extraStage2Sound = "gtbling";
	string extraStage3Sound = "gtbling";
	string extraStage4Sound = "gtbling";
	string creditsSound = "gtbling";
	string deadSound = "gtbling";
	string winSound = "gtbling";
	string loseSound = "gtbling";

	string stackRiseSound = "tick";

	string readySound = "ready";
	string goSound = "go";

	string gotBombSound = "gotBomb";
	string gotWeightSound = "gotWeight";
	string gotSubtractorSound = "gotSubtractor";
	string gotAdderSound = "gotAdder";
	string flashingClearSound = "flashingClear";
	string scanlineClearSound = "scanlineClear";


	bool useRandomSoundModulation = false;




	//---------------------------------------------------
	//game rules
	//---------------------------------------------------


	string name = "My New Game Type";								Info name_Info = Info("Game Type Name", "The name of the game type.");
	string rules = "Make a line of matching colors to score!";		Info rules_Info = Info("Rules Description", "A short description of the rules.");

	ScoreType scoreType = ScoreType::BLOCKS_CLEARED;						Info scoreType_Info = Info("Score Type", "What the score and level is based on.");
	int scoreTypeAmountPerLevelGained = 4;									Info scoreTypeAmountPerLevelGained_Info = Info("Score Type Amount Per Level Gained", "Amount which determines whether a level is gained, for instance 8 lines cleared, 20 blocks cleared, or 10 pieces made.");

	bool nextPieceEnabled = true;											Info nextPieceEnabled_Info = Info("Next Piece Enabled", "Whether to show next piece preview at top.");
	int numberOfNextPiecesToShow = 3;										Info numberOfNextPiecesToShow_Info = Info("Number Of Next Pieces To Show", "How many next pieces to show at top.");

	bool holdPieceEnabled = true;											Info holdPieceEnabled_Info = Info("Hold Piece Enabled", "Allow the player to hold a piece.");
	bool resetHoldPieceRotation = true;										Info resetHoldPieceRotation_Info = Info("Reset Hold Piece Rotation", "Reset the hold piece rotation when held.");

	

	bool chainRule_CheckEntireLine = false;									Info chainRule_CheckEntireLine_Info = Info("Chain Rule: Check Entire Line", "If checking for chains, entire horizontal line must match to be cleared.");
	int chainRule_AmountPerChain = 0;										Info chainRule_AmountPerChain_Info = Info("Chain Rule: Amount Per Chain", "If checking for chains, how many matching blocks needed in order to be cleared.");
	//TODO: match by color, match by type


	bool chainRule_CheckRowOrColumn = false;//deprecated!!								//Info chainRule_CheckRowOrColumn_Info = Info("Chain Rule: Check Row Or Column", "If checking for chains, check both up and down and left and right.");
	bool chainRule_CheckRow = false;								Info chainRule_CheckRow_Info = Info("Chain Rule: Check Row", "If checking for chains, check left and right.");
	bool chainRule_CheckColumn = false;								Info chainRule_CheckColumn_Info = Info("Chain Rule: Check Column", "If checking for chains, check up and down.");
	
	
	
	
	bool chainRule_CheckDiagonal = false;									Info chainRule_CheckDiagonal_Info = Info("Chain Rule: Check Diagonal", "If checking for chains, include diagonal blocks in search.");
	bool chainRule_CheckRecursiveConnections = false;						Info chainRule_CheckRecursiveConnections_Info = Info("Chain Rule: Check Recursive Connections", "If checking for chains, search up and down and left and right on each new found block.");
	bool chainRule_CheckTouchingBreakerBlocksChain = false;					Info chainRule_CheckTouchingBreakerBlocksChain_Info = Info("Chain Rule: Check Touching Breaker Blocks Chain", "If checking for chains, chain must be touching a breaker block to be cleared.");

	bool gravityRule_onlyMoveDownDisconnectedBlocks = false;				Info gravityRule_onlyMoveDownDisconnectedBlocks_Info = Info("Gravity Rule: Only Move Down Disconnected Blocks", "When applying gravity, do not apply it to blocks connected to other blocks by color or by piece.");

	GarbageType playingFieldGarbageType = GarbageType::ZIGZAG_PATTERN;		Info playingFieldGarbageType_Info = Info("Playing Field Garbage Type", "Pattern to use when filling the playing field from the bottom with garbage blocks.");
	GarbageSpawnRule playingFieldGarbageSpawnRule = GarbageSpawnRule::NONE;	Info playingFieldGarbageSpawnRule_Info = Info("Playing Field Garbage Spawn Rule", "By what metric should garbage blocks be spawned from the bottom.");
	//TODO: garbage rule where it only pushes up blocks but not spaces

	bool hardDropPunchThroughToLowestValidGridPosition = false;				Info hardDropPunchThroughToLowestValidGridPosition_Info = Info("Hard Drop Punch Through To Lowest Valid Grid Position", "Allow a hard drop (slam) to teleport through blocks in the way and fill the lowest valid position at the bottom of the grid.");

	bool twoSpaceWallKickAllowed = true;									Info twoSpaceWallKickAllowed_Info = Info("Two Space Wall Kick Allowed", "Whether when rotating a piece it can kick two spaces away from a wall."); //check away from wall, away twice from wall
	bool diagonalWallKickAllowed = true;									Info diagonalWallKickAllowed_Info = Info("Diagonal Wall Kick Allowed", "Whether when rotating a piece it can kick diagonally away from a wall, allowing it to transport between blocks in the way."); //check away from wall, down, down away from wall
	bool pieceClimbingAllowed = true;										Info pieceClimbingAllowed_Info = Info("Piece Climbing Allowed", "Whether when rotating a piece it can climb out of holes it is placed in."); //check held direction and up as many times as piece height.
	bool flip180Allowed = true;												Info flip180Allowed_Info = Info("Flip 180 Allowed", "Whether when rotating a piece it can flip itself 180 degrees even if obstructed.");
	bool floorKickAllowed = true;											Info floorKickAllowed_Info = Info("Floor Kick Allowed", "Whether when rotating a piece it can kick off of the ground.");


	int readyTicksAmount = 2000;//TODO: should this be a game settings?  should it allow to pause between games?




	//----------------------------------------------------
	//VS rules
	//----------------------------------------------------

	VSGarbageRule vsGarbageRule = VSGarbageRule::FALL_FROM_CEILING_IN_EVEN_ROWS;Info vsGarbageRule_Info = Info("VS Garbage Rule", "How garbage should act when sent from your opponent when they create combos.");

	//TODO: need what constitutes sending garbage, how many pieces to trigger, combo balancing, multiplier per game, etc
	
	//---------------------------------------------------
	//grid
	//---------------------------------------------------

	int gridWidth = 10;															Info gridWidth_Info = Info("Grid Width", "Width of the playing field grid."); //10;
	int gridHeight = 20;															Info gridHeight_Info = Info("Grid Height", "Height of the playing field grid."); //20;

	int gridPixelsBetweenRows = 0;												Info gridPixelsBetweenRows_Info = Info("Grid Pixels Between Rows", "If there should be spacing between the block rows.");
	int gridPixelsBetweenColumns = 0;											Info gridPixelsBetweenColumns_Info = Info("Grid Pixels Between Columns", "If there should be spacing between the block columns.");


	
	GameMode gameMode = GameMode::DROP;											Info gameMode_Info = Info("Game Mode", "Whether this is a falling block type game (where blocks fall from the top) or a stack based game (where a stack rises from the floor).  More game modes will be implemented in the future.");

	bool randomlyFillGrid = false;												Info randomlyFillGrid_Info = Info("Drop: Randomly Fill Grid", "Whether the playing field should be randomly filled on start.");
	int randomlyFillGridStartY = 0;												Info randomlyFillGridStartY_Info = Info("Drop: Randomly Fill Grid StartY", "How many lines from the top to start filling blocks.");

	//bool stackRiseGame = false;													Info stackRiseGame_Info = Info("Stack Rise Game", "Whether blocks should rise from the bottom instead of dropping from the top.");
	bool stackDontPutSameColorNextToEachOther = false;							Info stackDontPutSameColorNextToEachOther_Info = Info("Stack: Don't Put Same Color Next To Each Other", "When creating blocks from the bottom of the stack, don't put two of the same color next to each other.");
	bool stackDontPutSameBlockTypeNextToEachOther = false;						Info stackDontPutSameBlockTypeNextToEachOther_Info = Info("Stack: Don't Put Same Block Type Next To Each Other", "When creating blocks from the bottom of the stack, don't put the same type next to each other.");
	bool stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull = false;		Info stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull_Info = Info("Stack: Don't Put Same Color Diagonal Or Next To Each Other", "When creating blocks from the bottom of the stack, don't put two of the same color next to each other or diagonal.");
	bool stackLeaveAtLeastOneGapPerRow = false;									Info stackLeaveAtLeastOneGapPerRow_Info = Info("Stack: Leave At Least One Gap Per Row", "When creating blocks from the bottom of the stack, leave one block open in each row.");

	bool randomlyFillStack = false;												Info randomlyFillStack_Info = Info("Stack: Randomly Fill Stack", "Whether to begin the game with a randomly filled stack.");
	int randomlyFillStackStartY = 0;											Info randomlyFillStackStartY_Info = Info("Stack: Randomly Fill Stack Start Y", "How many lines from the top to start filling the stack.");

	//bool useCurrentPieceAsCursor = true;										Info useCurrentPieceAsCursor_Info = Info("Use Current Piece As Cursor", "Instead of moving a piece, draw a cursor.  You'll want this for stack based games, probably.");
	//bool makeNewPiece = false;													Info makeNewPiece_Info = Info("Make New Piece", "Whether to create a new piece at the top, which will be rotated.");
	//bool makeCursorPiece = false;												Info makeCursorPiece_Info = Info("Make Cursor", "Whether to create a cursor to swap or rotate blocks.");

	::CursorType stackCursorType = ::CursorType::ONE_BLOCK_PICK_UP;									Info stackCursorType_Info = Info("Stack: Cursor Type", "What type of cursor to swap or rotate blocks in stack games. Does nothing in drop gameNames.");
	//int cursorPieceSize = 1;													Info cursorPieceSize_Info = Info("Cursor Piece Size", "How many block should the cursor be? 1-4 should work.");//TODO: change this into a PieceType





	bool blockRule_drawDotToSquareOffBlockCorners = false;					//Info blockRule_drawDotToSquareOffBlockCorners_Info = Info("Draw Dot To Square Off Block Corners", "This is used for block games");
																			//TODO: make this automatic when using square sprites and joined blocks
	bool drawDotOnCenterOfRotation = false;									//Info drawDotOnCenterOfRotation_Info = Info("DrawDotOnCenterOfRotation", "");
																			//TODO: move to user options, this is just a debug mode thing



	//---------------------------------------------------
	//block
	//---------------------------------------------------

	//TODO: actually hook this up to something
	//bool whenGeneratingBlockDontGetBlockColorThatIsntOnGrid = false;		Info whenGeneratingBlockDontGetBlockColorThatIsntOnGrid_Info = Info("When Generating Block Don't Get Block Color That Isn't On Grid", ""); 
	//TODO, also check currentPiece, holdPiece, etc. and maybe replace colors.

	bool gridRule_outlineOpenBlockEdges = false;							Info gridRule_outlineOpenBlockEdges_Info = Info("Visual: Outline Open Block Edges", "Draw a white outline along the block edges after they are set.");
	bool fadeBlocksDarkerWhenLocking = true;								Info fadeBlocksDarkerWhenLocking_Info = Info("Visual: Fade Blocks Darker When Locking", "Fade blocks darker when set in the grid and locking.");
	bool blockRule_drawBlocksDarkerWhenLocked = false;						Info blockRule_drawBlocksDarkerWhenLocked_Info = Info("Visual: Draw Blocks Darker When Locked", "Darken the blocks once they are locked into the grid.");
	bool blockRule_fillSolidSquareWhenSetInGrid = false;					Info blockRule_fillSolidSquareWhenSetInGrid_Info = Info("Visual: Fill Solid Square When Set In Grid", "Fill blocks set into the grid with a solid color, ignoring block sprite graphics.");

	bool blockRule_drawBlocksConnectedByPieceIgnoringColor = false;			Info blockRule_drawBlocksConnectedByPieceIgnoringColor_Info = Info("Visual: Draw Blocks Connected By Piece Ignoring Color", "When drawing a piece, visually connect the blocks inside of it.");//tetrid
	//TODO: maybe put these in pieceType or blockType

	bool blockRule_drawBlocksConnectedByColorIgnoringPiece = false;			Info blockRule_drawBlocksConnectedByColorIgnoringPiece_Info = Info("Visual: Draw Blocks Connected By Color Ignoring Piece", "When drawing blocks, visually connect those with matching colors."); //blob
	//can do sticky with this by checking blob color every frame

	bool blockRule_drawBlocksConnectedByColorInPiece = false;				Info blockRule_drawBlocksConnectedByColorInPiece_Info = Info("Visual: Draw Blocks Connected By Color In Piece", "When drawing a piece, visually connect blocks connected by color within it.");//drbob

	long long blockMovementInterpolationTicks = 100;						Info blockMovementInterpolationTicks_Info = Info("Visual: Block Movement Interpolation Ticks", "How many milliseconds to animate transitions between one movement to the next.");
	int blockAnimationTicksRandomUpToBetweenLoop = 0;						Info blockAnimationTicksRandomUpToBetweenLoop_Info = Info("Visual: Block Animation Ticks Random Up To Between Loop", "If a block sprite has animation, maximum amount of milliseconds to wait before triggering animation cycle.");//drbob


	ArrayList<BlockType*> blockTypes;										//Info blockTypes_Info = Info("Block Types", "");
	private:
	ArrayList<BlockType> importExport_blockTypes;
	public:



	//---------------------------------------------------
	//piece
	//---------------------------------------------------

	bool whenGeneratingPieceDontMatchAllBlockColors = false;									Info whenGeneratingPieceDontMatchAllBlockColors_Info = Info("When Generating Piece Don't Match All Block Colors", "Make sure that there are at least two different colors of block when a piece is created."); // used in columns
	bool whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor = false;		Info whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor_Info = Info("When Generating Piece Don't Match Two Blocks Of The Same Special Random Type And Color", "Don't put two special blocks next to each other inside of a piece, otherwise they might cancel each other out."); //used in puzzlefight
	bool whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor = false;	Info whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor_Info = Info("When Generating Piece Don't Match Normal Block With Block Of Different Type And Same Color", "Don't match a normal block type with a different normal block type of the same color, otherwise they might cancel each other out.");

	//bool currentPieceRenderAsNormalPiece = true;												Info currentPieceRenderAsNormalPiece_Info = Info("Current Piece Render As Normal Piece", ""); //set to false for cursors
	//bool drawCursorInsteadOfCurrentPiece = false;													Info drawCursorInsteadOfCurrentPiece_Info = Info("Draw Cursor Instead Of Current Piece", ""); //used for cursors //was currentPieceOutlineAllPieces
	bool currentPieceOutlineFirstBlockRegardlessOfPosition = false;								Info currentPieceOutlineFirstBlockRegardlessOfPosition_Info = Info("Current Piece Outline First Block Regardless Of Position", "Draw an outline around the first block of a piece."); //used in columns
	bool currentPieceRule_OutlineBlockAtZeroZero = false;										Info currentPieceRule_OutlineBlockAtZeroZero_Info = Info("Current Piece Outline Block At Zero Zero", "Draw an outline around the center block of a piece.");


	//bool currentPieceRenderHoldingBlock = false;												Info currentPieceRenderHoldingBlock_Info = Info("Current Piece Render Holding Block", "");
	//bool currentPieceMoveUpHalfABlock = false;													Info currentPieceMoveUpHalfABlock_Info = Info("Current Piece Move Up Half A Block", "");

	bool currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty = false;		Info currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty_Info = Info("Get New Pieces Randomly Out Of Bag With One Of Each Piece Until Empty", "Get one of each piece type randomly until all of them have been used instead of generating a completely random piece each time.  Prevents many duplicates in a row and guarantees you will get each piece, but reduces randomness.");

	//TODO: can change these to pieceType.garbage, etc
	ArrayList<PieceType*> pieceTypes;															//Info pieceTypes_Info = Info("pieceTypes", "");
private:
	ArrayList<PieceType> importExport_pieceTypes;
public:

	ArrayList<DifficultyType*> difficultyTypes;
private:
	ArrayList<DifficultyType> importExport_difficulties;
public:

	//---------------------------------------------------
	//timing and difficulty
	//---------------------------------------------------

	//not user settable!---------------------
	//DifficultyType* currentDifficulty = nullptr;// = new DifficultyType();
	//long long initialLineDropSpeedTicks = 0;
	//int minStackRise = 0;
	//int maxStackRise = 0;
	//long long minimumLineDropSpeedTicks = 0;

	//int extraStage1Level = 0;
	//int extraStage2Level = 0;
	//int extraStage3Level = 0;
	//int extraStage4Level = 0;
	//int creditsLevel = 0;
	GameType();
	DifficultyType* getDifficultyByName(string s);
	//GameType(DifficultyType *d);

	//void setTimingBasedOnDifficulty(DifficultyType d);



	float bloomIntensity = 1.5f;															Info bloomIntensity_Info = Info("Bloom Intensity", "Intensity of the bloom effect.");
	int bloomTimes = 4;/*blur passes!!*/															Info bloomTimes_Info = Info("Bloom Blur Passes", "How many times to blur the bloom filter.");
	//--------------------------------------------


	//TODO: max stack wait delay
	long long maxLockDelayTicks = 17 * 30;															Info maxLockDelayTicks_Info = Info("Max Lock Delay Ticks", "Maximum milliseconds a piece can be set at the bottom before locking.");
	long long spawnDelayTicksAmountPerPiece = 30 * 17;												Info spawnDelayTicksAmountPerPiece_Info = Info("Spawn Delay Ticks Amount Per Piece", "Millisecond delay that a piece waits before dropping from the top.");
	long long lineClearDelayTicksAmountPerLine = 100 * 17;											Info lineClearDelayTicksAmountPerLine_Info = Info("Line Clear Delay Ticks Amount Per Line", "How many milliseconds to wait after clearing a line.  Only affects games that clear entire lines.");
	long long lineClearDelayTicksAmountPerBlock = 10 * 17;											Info lineClearDelayTicksAmountPerBlock_Info = Info("Line Clear Delay Ticks Amount Per Block", "How many milliseconds to wait after making a chain, per block.  Only affects games that use chains.");

	//public int stackRiseSpeed = 0;//used for panel

	long long gravityRule_ticksToMoveDownBlocksOverBlankSpaces = 200;								Info gravityRule_ticksToMoveDownBlocksOverBlankSpaces_Info = Info("Gravity Rule Ticks To Move Down Blocks Over Blank Spaces", "How many milliseconds should blocks pause each time they fall down a line, used for animating blocks falling incrementally."); //used for dr style slow fall
	
	//TODO: test to see what this behaves like, i'm not using it in anything
	bool moveDownAllLinesOverBlankSpacesAtOnce = false;												Info moveDownAllLinesOverBlankSpacesAtOnce_Info = Info("Move Down All Lines Over Blank Spaces At Once", "Instantly drop any solid lines over blank lines down instead of animating them."); //if we want old t style, instant fall

	int removingBlocksDelayTicksBetweenEachBlock = 0;												Info removingBlocksDelayTicksBetweenEachBlock_Info = Info("Removing Blocks Delay Ticks Between Each Block", "How many milliseconds to delay the animation of each block being cleared.");//used in swap games to make things pop

	//TODO: whether to have a limit on levels or not
	//TODO: whether to use extra stage effects
	//TODO: choose amount of colors possible here
	//also have user settings for changing difficulty, having endless mode, etc
	//maybe have a checkbox somehow for user editable settings

//
//	int initialLineDropSpeedTicks_BEGINNER = 2000;//default 1000
//	int minimumLineDropSpeedTicks_BEGINNER = 1000;//default 64
//	int minStackRise_BEGINNER = 600;//default 30
//	int maxStackRise_BEGINNER = 1500;//default 400
//
//	int extraStage1Level_BEGINNER = 5;
//	int extraStage2Level_BEGINNER = 6;
//	int extraStage3Level_BEGINNER = 7;
//	int extraStage4Level_BEGINNER = 8;
//	int creditsLevel_BEGINNER = 9;
//
//
//
//
//	int initialLineDropSpeedTicks_EASY = 1500;//default 1000
//	int minimumLineDropSpeedTicks_EASY = 500;//default 64
//	int minStackRise_EASY = 300;//default 30
//	int maxStackRise_EASY = 800;//default 400
//
//	int extraStage1Level_EASY = 10;
//	int extraStage2Level_EASY = 11;
//	int extraStage3Level_EASY = 12;
//	int extraStage4Level_EASY = 13;
//	int creditsLevel_EASY = 15;
//
//
//
//
//	int initialLineDropSpeedTicks_NORMAL = 1000;
//	int minStackRise_NORMAL = 30;
//	int maxStackRise_NORMAL = 400;
//	int minimumLineDropSpeedTicks_NORMAL = 64; //256;
//
//	int extraStage1Level_NORMAL = 10;
//	int extraStage2Level_NORMAL = 15;
//	int extraStage3Level_NORMAL = 20;
//	int extraStage4Level_NORMAL = 25;
//	int creditsLevel_NORMAL = 30;
//
//
//
//
//	int initialLineDropSpeedTicks_HARD = 500;
//	int minimumLineDropSpeedTicks_HARD = 32;
//	int minStackRise_HARD = 15;//default 30
//	int maxStackRise_HARD = 300;//default 400
//
//	int extraStage1Level_HARD = 20;
//	int extraStage2Level_HARD = 30;
//	int extraStage3Level_HARD = 40;
//	int extraStage4Level_HARD = 50;
//	int creditsLevel_HARD = 60;
//
//
//	int initialLineDropSpeedTicks_INSANE = 128;
//	int minimumLineDropSpeedTicks_INSANE = 8;
//	int minStackRise_INSANE = 15;//default 30
//	int maxStackRise_INSANE = 200;//default 400
//
//	int extraStage1Level_INSANE = 50;
//	int extraStage2Level_INSANE = 60;
//	int extraStage3Level_INSANE = 70;
//	int extraStage4Level_INSANE = 80;
//	int creditsLevel_INSANE = 99;





	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version);


	ArrayList<BlockType*> getNormalBlockTypes(DifficultyType *d);
	ArrayList<BlockType*> getGarbageBlockTypes(DifficultyType *d);
	ArrayList<BlockType*> getPlayingFieldBlockTypes(DifficultyType *d);
	ArrayList<BlockType*> getBlockTypesToIgnoreWhenCheckingChain(DifficultyType *d);
	ArrayList<BlockType*> getBlockTypesToIgnoreWhenMovingDown(DifficultyType *d);
	ArrayList<BlockType*> getBlockTypesChainMustContain(DifficultyType *d);
	ArrayList<PieceType*> getNormalPieceTypes(DifficultyType *d);
	ArrayList<PieceType*> getGarbagePieceTypes(DifficultyType *d);
	ArrayList<PieceType*> getPlayingFieldPieceTypes(DifficultyType *d);


};


BOOST_CLASS_VERSION(GameType, 5)
BOOST_CLASS_TRACKING(GameType, boost::serialization::track_never)