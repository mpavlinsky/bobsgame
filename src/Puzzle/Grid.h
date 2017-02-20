//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
enum class MovementType;
class Logger;




//C# TO C++ CONVERTER NOTE: Forward class declarations:
class GameLogic;
class Block;
class Piece;
class BlockType;
class PieceType;
class GameType;

//=========================================================================================================================
class Grid
{//=========================================================================================================================
public:

	static Logger log;

	//Color noColor;
	//PieceType noPieceType;
	//BlockType noBlockType;
	//ArrayList<Color> emptyColors;

	GameLogic* game = nullptr;


	float screenX = 0;
	float screenY = 0;

//#define blockHashMap

#ifdef blocksHashMap
	HashMap<int, Block*>* blocks = new HashMap<int, Block*>();
#else
	ArrayList<Block*> blocks;
#endif

	static Block* nullBlock;

private:
	int wigglePlayingFieldTicksSpeed = 60;
	int wigglePlayingFieldMaxX = 0;
	int wigglePlayingFieldMaxY = 0;
	float wigglePlayingFieldX = 0;
	float wigglePlayingFieldY = 0;
	long long wigglePlayingFieldTicks = 0;
	bool wigglePlayingFieldLeftRightToggle = false;


	int shakePlayingFieldScreenTicksCounter = 0;
	long long shakePlayingFieldStartTime = 0;
	int shakePlayingFieldTicksDuration = 0;
	int shakePlayingFieldMaxX = 0;
	int shakePlayingFieldMaxY = 0;
	int shakePlayingFieldTicksPerShake = 0;
	int shakePlayingFieldTicksPerShakeXCounter = 0;
	bool shakePlayingFieldLeftRightToggle = false;
	int shakePlayingFieldTicksPerShakeYCounter = 0;
	bool shakePlayingFieldUpDownToggle = false;
	int shakePlayingFieldX = 0;
	int shakePlayingFieldY = 0;
	void setShakePlayingField(int ticksDuration, int maxX, int maxY, int ticksPerShake);
	void updateShake();

//	long long effectShakeDurationTicks = 0;
//	long long effectShakeTicksCounter = 0;
//	int effectShakeMaxX = 0;
//	int effectShakeMaxY = 0;
//	int effectShakeX = 0;
//	int effectShakeY = 0;


public:
	float scrollPlayingFieldY = 0; //for stack based games
	float scrollBlockIncrement = 60; //for stack based games

private:
	int scrollPlayingFieldBackgroundTicksSpeed = 30;
	int backgroundScrollX = 0;
	int backgroundScrollY = 0;
	long long scrollPlayingFieldBackgroundTicks = 0;


	int deadX = 0;
	int deadY = 0;


public:
	int lastGarbageHoleX = 0;
	bool garbageHoleDirectionToggle = true;
	ArrayList<Piece*> randomBag;;
	Grid(GameLogic* gameInstance);
	float getXInFBO();
	float getXInFBONoShake();
	float getXOnScreenNoShake();
	float getYInFBO();
	float getYInFBONoShake();
	float getYOnScreenNoShake();
	float bgX();
	float bgY();
	int getHeight();
	int getWidth();
	void update();
	void reformat(int oldWidth, int oldHeight);
	int getNumberOfFilledCells();
	void removeAllBlocksOfPieceFromGrid(Piece* p, bool fadeOut);
	void replaceAllBlocksWithNewGameBlocks();
	Piece* dontPutSameColorDiagonalOrNextToEachOtherReturnNull(Piece* p, int x, int y, ArrayList<PieceType*> &pieceTypes, ArrayList<BlockType*> &blockTypes);
	Piece* dontPutSameColorNextToEachOtherOrReturnNull(Piece* p, int x, int y, ArrayList<PieceType*> &pieceTypes, ArrayList<BlockType*> &blockTypes);
	Piece* dontPutSameBlockTypeNextToEachOtherOrReturnNull(Piece* p, int x, int y, ArrayList<PieceType*> &pieceTypes, ArrayList<BlockType*> &blockTypes);
	void removeAndDestroyAllBlocksInGrid();
	Piece* putOneBlockPieceInGridCheckingForFillRules(int x, int y, ArrayList<PieceType*> &pieceTypes, ArrayList<BlockType*> &blockTypes);
	void randomlyFillGridWithPlayingFieldPieces(int numberOfBlocks, int topY);
	void buildRandomStackRetainingExistingBlocks(int numberOfBlocks, int topY);
	bool scrollUpStack(Piece* cursorPiece, int amt);
	Piece* putGarbageBlock(int x, int y);
	void makeGarbageRowFromCeiling();
	void moveAllRowsUpOne();
	void makeGarbageRowFromFloor();
	void cursorSwapBetweenTwoBlocksHorizontal(Piece* cursor);
	void cursorSwapBetweenTwoBlocksVertical(Piece* cursor);
	void cursorSwapBetweenThreeBlocksHorizontal(Piece* cursor, MovementType rotation);
	void cursorSwapBetweenThreeBlocksVertical(Piece* cursor, MovementType rotation);
	void cursorSwapHoldingBlockWithGrid(Piece* cursor);
	void cursorRotateBlocks(Piece* cursor, MovementType rotation);
	bool continueSwappingBlocks();
	void scrollBackground();
	void shakeSmall();
	void shakeMedium();
	void shakeHard();
	void wigglePlayingField();
	void add(int x, int y, Block* b);
	bool contains(int index);
	bool contains(int x, int y);
	Block* get(int x, int y);

private:
	Block* remove(int x, int y, bool fadeOut, bool breakConnections);

public:
	void remove(Block* b, bool fadeOut, bool breakConnections);
	void moveToAndRemoveAndFadeOut(Block* b, int x, int y);
	bool checkLine(int y);
	ArrayList<Piece*> getArrayOfPiecesOnGrid();
	ArrayList<Block*> checkLines(ArrayList<BlockType*> &ignoreTypes, ArrayList<BlockType*> &mustContainAtLeastOneTypes);
	bool doBlocksMatchColor(Block* a, Block* b, ArrayList<BlockType*> &ignoreTypes);
	ArrayList<Block*> getConnectedBlocksUpDownLeftRight(Block* b);
	void checkRecursiveConnectedRowOrColumn(ArrayList<Block*> &connectedBlocks, int leastAmountConnected, int startX, int endX, int startY, int endY, ArrayList<BlockType*> &ignoreTypes, ArrayList<BlockType*> &mustContainAtLeastOneTypes);
	void setColorConnections(ArrayList<BlockType*> &ignoreTypes);// , ArrayList<BlockType*>* mustContainAtLeastOneTypes);
	ArrayList<Block*> checkBreakerBlocks(int toRow, ArrayList<BlockType*> &ignoreUnlessTouchingBreakerBlockTypes, ArrayList<BlockType*> &breakerBlockTypes);
	void recursivelyGetAllMatchingBlocksConnectedToBlockToArrayIfNotInItAlready(Block* b, ArrayList<Block*> &connectedBlocks, ArrayList<BlockType*> &ignoreTypes);
	void addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowAtLeastAmount(Block* b, ArrayList<Block*> &connectedBlocks, int leastInARow, int startX, int endX, int startY, int endY, ArrayList<BlockType*> &ignoreTypes, ArrayList<BlockType*> &mustContainAtLeastOneTypes);
	void addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInColumnAtLeastAmount(Block* b, ArrayList<Block*> &connectedBlocks, int leastInARow, int startX, int endX, int startY, int endY, ArrayList<BlockType*> &ignoreTypes, ArrayList<BlockType*> &mustContainAtLeastOneTypes);
	void addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfDiagonalAtLeastAmount(Block* b, ArrayList<Block*> &connectedBlocks, int leastInARow, int startX, int endX, int startY, int endY, ArrayList<BlockType*> &ignoreTypes, ArrayList<BlockType*> &mustContainAtLeastOneTypes);
	void renderBackground();
	void render();
	void renderBlockOutlines();
	void renderBorder();
	void renderTransparentOverLastRow();
	void renderGhostPiece(Piece* currentPiece);
	bool isWithinBounds(Piece* piece, int x, int y);
	bool isHittingLeft(Piece* piece);
	bool isHittingLeft(Piece* piece, int x, int y);
	bool isHittingRight(Piece* piece);
	bool isHittingRight(Piece* piece, int x, int y);
	bool doesPieceFit(Piece* piece);
	bool doesPieceFit(Piece* piece, int x, int y);
	void setPiece(Piece* piece);
	void setPiece(Piece* piece, int x, int y);
	bool moveDownLinesAboveBlankLinesOneLine();
	bool moveDownDisconnectedBlocksAboveBlankSpacesOneLine(ArrayList<BlockType*> &ignoreTypes);
	bool moveDownAnyBlocksAboveBlankSpacesOneLine(ArrayList<BlockType*> &ignoreTypes);
	void setRandomBlockColors();
	void setRandomMatrixBlockColors();
	void setRandomWholePieceColors(bool grayscale, Piece* currentPiece, ArrayList<Piece*> &nextPieces);
	void setRandomPieceGrayscaleColors(Piece* currentPiece, ArrayList<Piece*> &nextPieces);
	bool isAnythingAboveThreeQuarters();
	void doDeathSequence();
	PieceType* getRandomSpecialPieceTypeFromArrayExcludingNormalPiecesOrNull(ArrayList<PieceType*> &arr);
	PieceType* getRandomPieceTypeFromArrayExcludingSpecialPieceTypes(ArrayList<PieceType*> &arr);
	ArrayList<Piece*> getBagOfOneOfEachNonRandomNormalPieces();
	Piece* getPieceFromNormalPieceRandomBag();
	Piece* getRandomPiece();
	Piece* getRandomPiece(ArrayList<PieceType*> &pieceArray, ArrayList<BlockType*> &blockArray);
	PieceType* getRandomPieceType(ArrayList<PieceType*> &arr);
	BlockType* getRandomBlockType(ArrayList<BlockType*> &arr);
	BlockType* getRandomBlockTypeDisregardingSpecialFrequency(ArrayList<BlockType*> &arr);
	BlockType* getRandomSpecialBlockTypeFromArrayExcludingNormalBlocksOrNull(ArrayList<BlockType*> &arr);
	BlockType* getRandomBlockTypeFromArrayExcludingSpecialBlockTypes(ArrayList<BlockType*> &arr);
	bool areAnyBlocksPopping();
	int cellW();
	int cellH();
	GameType* getGameType();
	GameLogic* getGameLogic();
};

