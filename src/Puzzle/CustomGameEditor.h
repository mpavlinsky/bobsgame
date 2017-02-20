
#include "bobtypes.h"

#include "Gwen/Platform.h"
#include <Gwen/Controls/Base.h>
#include <Gwen/Controls/DockBase.h>
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/TabControl.h"
#include "Gwen/Controls/HorizontalSplitter.h"
#include "Gwen/Controls/ListBox.h"
#include "Gwen/Controls/HorizontalSlider.h"
#include "Gwen/Controls/StatusBar.h"
#include <Gwen/Controls/Button.h>
#include <Gwen/Controls/ImagePanel.h>
#include <Gwen/Controls/Rectangle.h>
#include "Gwen/Controls/DockedTabControl.h"
#include "Gwen/Controls/WindowControl.h"
#include "Gwen/Controls/CollapsibleList.h"
#include "Gwen/Controls/Layout/Position.h"

#include <Gwen/Controls/WindowControl.h>
#include <Gwen/Controls/ListBox.h>
#include <Gwen/Controls/Base.h>
#include <Gwen/Controls/Property/BaseProperty.h>
#include <Gwen/Controls/Property/ColorSelector.h>
#include <Gwen/Controls/Property/ComboBox.h>
#include <Gwen/Controls/Property/Checkbox.h>
#include <Gwen/Controls/Property/TextWithButton.h>
#include <Gwen/Controls/Property/Listbox.h>
#include <Gwen/Controls/Properties.h>
#include <Gwen/Controls/PropertyTree.h>
#include <Gwen/Controls/CheckBox.h>
#include <Gwen/Controls/ColorPicker.h>
#include <Gwen/Controls/ComboBox.h>
#include <map>




class TurnFromBlockTypeToType;

//=========================================================================================================================
class EditRectangle : public Gwen::Controls::Rectangle
{//=========================================================================================================================
public:
    
	//GWEN_CONTROL(EditRectangle, Rectangle);
	//#define GWEN_CONTROL( ThisName, BaseName )
	//GWEN_CLASS(EditRectangle, Rectangle)
	//GWEN_DYNAMIC(EditRectangle, Rectangle)
	//#define GWEN_DYNAMIC( ThisName, BaseName )
	//typedef Rectangle BaseClass;
	//typedef EditRectangle ThisClass;
	static const char* GetIdentifier()
	{
		static const char* ident = "Rectangle" ":" "EditRectangle";
		return ident;
	};
	virtual Gwen::Controls::Base* DynamicCast( const char* Variable )
	{
		if ( GetIdentifier() == Variable )
            return this;
        
		return Gwen::Controls::Rectangle::DynamicCast( Variable);
	}
	virtual const char* GetTypeName(){ return "EditRectangle"; }
	virtual const char* GetBaseTypeName(){ return Gwen::Controls::Rectangle::GetTypeName(); }
    //GWEN_CONTROL_CONSTRUCTOR(EditRectangle)
    EditRectangle(Gwen::Controls::Base* pParent, const Gwen::String& pName, BobsGame* b) : Gwen::Controls::Rectangle(pParent, pName)
    {
        bobsGame = b;
        m_Color = Gwen::Color(255, 255, 255, 255);
    }
    
    
	virtual void OnMouseClickLeft(int /*x*/, int /*y*/, bool bDown);
    
    BobsGame* bobsGame = nullptr;
	//virtual void Render(Skin::Base* skin);
};





//=========================================================================================================================
class RotationPreviewRectangle : public Gwen::Controls::Rectangle
{//=========================================================================================================================
public:
    
	//GWEN_CONTROL(RotationPreviewRectangle, Rectangle);
	//typedef RotationPreviewRectangle ThisClass;
	//typedef Rectangle BaseClass;
	static const char* GetIdentifier()
	{
		static const char* ident = "Rectangle" ":" "RotationPreviewRectangle";
		return ident;
	};
	virtual Gwen::Controls::Base* DynamicCast(const char* Variable)
	{
		if (GetIdentifier() == Variable)
			return this;
        
		return Gwen::Controls::Rectangle::DynamicCast(Variable);
	}
	virtual const char* GetTypeName() { return "RotationPreviewRectangle"; }
	virtual const char* GetBaseTypeName() { return Gwen::Controls::Rectangle::GetTypeName(); }
    //GWEN_CONTROL_CONSTRUCTOR(RotationPreviewRectangle)
    RotationPreviewRectangle(Gwen::Controls::Base* pParent, const Gwen::String& pName, BobsGame* b) : Gwen::Controls::Rectangle(pParent, pName)
    {
        bobsGame = b;
        m_Color = Gwen::Color(255, 255, 255, 255);
    }
    
    BobsGame* bobsGame = nullptr;
    
	//virtual void Render(Skin::Base* skin);
};




//=========================================================================================================================
class PreviewRectangle : public Gwen::Controls::Rectangle
{//=========================================================================================================================
public:
    
	//GWEN_CONTROL(PreviewRectangle, Rectangle);
	//typedef PreviewRectangle ThisClass;
	//typedef Rectangle BaseClass;
	static const char* GetIdentifier()
	{
		static const char* ident = "Rectangle" ":" "PreviewRectangle";
		return ident;
	};
	virtual Gwen::Controls::Base* DynamicCast(const char* Variable)
	{
		if (GetIdentifier() == Variable)
			return this;
        
		return Gwen::Controls::Rectangle::DynamicCast(Variable);
	}
	virtual const char* GetTypeName() { return "PreviewRectangle"; }
	virtual const char* GetBaseTypeName() { return Gwen::Controls::Rectangle::GetTypeName(); }
	//GWEN_CONTROL_CONSTRUCTOR(PreviewRectangle)
    PreviewRectangle(Gwen::Controls::Base* pParent, const Gwen::String& pName, BobsGame* b) : Gwen::Controls::Rectangle(pParent, pName)
    {
        bobsGame = b;
        m_Color = Gwen::Color(255, 255, 0, 255);
    }
    
	virtual void Render(Gwen::Skin::Base* skin);
    
	BobsGame *bobsGame = nullptr;
};





//=========================================================================================================================
class CustomGameEditorControl : public Gwen::Controls::Base
{//=========================================================================================================================
public:
	//GWEN_CONTROL(CustomGameEditorControl, Base);
	//typedef CustomGameEditorControl ThisClass;
	//typedef Base BaseClass;
	static const char* GetIdentifier()
	{
		static const char* ident = "Base" ":" "CustomGameEditorControl";
		return ident;
	};
	virtual Gwen::Controls::Base* DynamicCast(const char* Variable)
	{
		if (GetIdentifier() == Variable)
			return this;
        
		return Gwen::Controls::Base::DynamicCast(Variable);
	}
	virtual const char* GetTypeName() { return "CustomGameEditorControl"; }
	virtual const char* GetBaseTypeName() { return Gwen::Controls::Base::GetTypeName(); }
	CustomGameEditorControl(Gwen::Controls::Base* pParent, const Gwen::String& pName, BobsGame *b);
    
    
    
	BlockType* getBlockTypeByUUID(string uuid);
	PieceType* getPieceTypeByUUID(string uuid);
	//GameType* getGameTypeByName(string name);
	DifficultyType* getDifficultyTypeByName(string name);
    
	void onBlockListRowSelect(Gwen::Controls::Base* control);
	void onPieceListRowSelect(Gwen::Controls::Base* control);
    
    
	void initPreviewGame();
	void onPreviewButton(Gwen::Controls::Base* control);

	void onAddBlockButton(Gwen::Controls::Base* control);
	void onDuplicateBlockButton(Gwen::Controls::Base* control);
	void onDeleteBlockButton(Gwen::Controls::Base* control);
	void onAddPieceButton(Gwen::Controls::Base* control);
	void onDuplicatePieceButton(Gwen::Controls::Base* control);
	void onDeletePieceButton(Gwen::Controls::Base* control);
    
	
	void onLoadOrCreateButton(Gwen::Controls::Base* control);
    
	void saveAndOpen(Gwen::Controls::Base* control);
	void dontSaveAndOpen(Gwen::Controls::Base* control);
    
	void openLoadOrCreateDialog(bool allowedToClose);
	void onSaveButton(Gwen::Controls::Base* control);
	void onUploadButton(Gwen::Controls::Base* control);
	void onExitButton(Gwen::Controls::Base* control);
	void saveAndExit(Gwen::Controls::Base* control);
	void dontSaveAndExit(Gwen::Controls::Base* control);
    
	void editSelectedGameType(Gwen::Controls::Base* control);
	void createNewGameType(Gwen::Controls::Base* control);
	void duplicateGameType(Gwen::Controls::Base* control);
	void deleteGameType(Gwen::Controls::Base* control);
	void initBlockPropTree(BlockType *b);
	void saveBlockPropTreeToCurrentBlockType();
	void initPiecePropTree(PieceType *b);
	void savePiecePropTreeToCurrentPieceType();
	void doEditMakePieceTypeWhenClearedWindowButton(Gwen::Controls::Base* control);
	void doEditConnectedUDLRChangeIntoBlockTypeWindowButton(Gwen::Controls::Base* control);
	void doEditTurnFromBlockTypeToTypeWindowButton(Gwen::Controls::Base* control);
	void doEditRotationSetWindowButton(Gwen::Controls::Base* control);
	void doOverrideBlockTypesSelectionWindowButton(Gwen::Controls::Base* control);
	void initSettingsPropTree(GameType *b);
	void saveSettingsPropTreeToCurrentGameType();
	void initBlockSelectionListBox();
	void initPieceSelectionListBox();
    
	void makeSelectionWindow(string name);
	void addType(Gwen::Controls::Base* control);
	void removeType(Gwen::Controls::Base* control);
	void saveMakePieceTypes(Gwen::Controls::Base* control);
	void saveConnectedUDLRChangeIntoBlockTypes(Gwen::Controls::Base* control);
	void cancelTypesWindow(Gwen::Controls::Base* control);
	void saveOverrideBlockTypes(Gwen::Controls::Base* control);
	void newTurnFromBlockTypeToType(Gwen::Controls::Base* control);
	void deleteTurnFromBlockTypeToType(Gwen::Controls::Base* control);
	void closeTurnFromBlockTypeToTypeEditor(Gwen::Controls::Base* control);
	void onTurnFromBlockTypeToTypeSelect(Gwen::Controls::Base* control);
	void saveCurrentTurnFromBlockTypeToType();
	void saveFromTypeComboToCurrentType();
	void saveToTypeComboToCurrentType();
    
    
	void checkResize();
	void doResize();
	void initFromCurrentGameType();
	void saveAllToCurrentGameType();
	//void loadGameTypesFromXML();
	void populateGameTypesListBox();
	void saveCurrentGameTypeToXML();
	void onGameTypesListSelect(Gwen::Controls::Base* control);
    
	void onRotationPreviewSpeedSliderMoved(Gwen::Controls::Base* control);
	void onRotationListRowSelect(Gwen::Controls::Base* control);
	void addRotation(Gwen::Controls::Base* control);
	void deleteRotation(Gwen::Controls::Base* control);
	void closeRotationWindow(Gwen::Controls::Base* control);
	void onOpenPresetRotationWindow(Gwen::Controls::Base* control);
	void onSelectedPresetRotationOK(Gwen::Controls::Base* control);
	void onSelectedPresetRotationCancel(Gwen::Controls::Base* control);
	void renderRotationPreview();
	void renderRotationEditor(BobsGame *g);
	void updateRotationEditor();
	void onRotationEditMouseClick(int x, int y, bool bDown);
    
	//void onAddDifficultyButton(Base* control);
	//void onDeleteDifficultyButton(Base* control);
	void onDifficultyListRowSelect(Gwen::Controls::Base* control);
	void initDifficultyPropTree(DifficultyType *b);
	void saveDifficultyPropTreeToCurrentDifficultyType();
	void initDifficultySelectionListBox();
	void doDifficultyDisallowPieceTypesSelectionWindowButton(Gwen::Controls::Base* control);
	void saveDisallowPieceTypes(Gwen::Controls::Base* control);
	void doDifficultyDisallowBlockTypesSelectionWindowButton(Gwen::Controls::Base* control);
	void saveDisallowBlockTypes(Gwen::Controls::Base* control);
    
private:
    
    
	
    
	Gwen::Controls::HorizontalSplitter* mainWindowSplitter = nullptr;
	Gwen::Controls::HorizontalSplitter* blockWindowSplitter = nullptr;
	Gwen::Controls::HorizontalSplitter* pieceWindowSplitter = nullptr;
	Gwen::Controls::HorizontalSplitter* difficultyWindowSplitter = nullptr;
	Gwen::Controls::TabControl* leftBaseTabControl = nullptr;
	Gwen::Controls::TabButton* settingsTab = nullptr;
	Gwen::Controls::TabButton* blockTab = nullptr;
	Gwen::Controls::TabButton* pieceTab = nullptr;
	Gwen::Controls::TabButton* difficultyTab = nullptr;
    
	Gwen::Controls::Base* settingsPage = nullptr;
	Gwen::Controls::Base* blockPage = nullptr;
	Gwen::Controls::Base* piecePage = nullptr;
	Gwen::Controls::Base* difficultyPage = nullptr;
    
	Gwen::Controls::ListBox* blockSelectionListBox = nullptr;
	Gwen::Controls::ListBox* pieceSelectionListBox = nullptr;
	Gwen::Controls::ListBox* difficultySelectionListBox = nullptr;
	Gwen::Controls::Base* previewBase;
	
public:
	PreviewRectangle* darkRectangle = nullptr;
private:
	Gwen::Controls::Base* applyButtonsBase = nullptr;
	Gwen::Controls::Button* previewButton = nullptr;
	Gwen::Controls::Button* loadButton = nullptr;
	Gwen::Controls::Button* saveButton = nullptr;
	Gwen::Controls::Button* uploadButton = nullptr;
	Gwen::Controls::Button* exitButton = nullptr;
	Gwen::Controls::Base* leftBase;
	Gwen::Controls::WindowControl* settingsWindow = nullptr;
	Gwen::Controls::ScrollControl* settingsScrollControl = nullptr;
	Gwen::Controls::PropertyTree* settingsPropTree = nullptr;
	int settingsPropTreeNumChildren = 0;
	Gwen::Controls::WindowControl* blockWindow = nullptr;
	Gwen::Controls::Base* blockListBase = nullptr;
	//Base* blockSelectionListBase = nullptr;
	Gwen::Controls::ScrollControl* blockPropertiesScrollControl = nullptr;
	Gwen::Controls::PropertyTree* blockPropTree = nullptr;
	int blockPropTreeNumChildren = 0;
	Gwen::Controls::Base* blockButtonBase = nullptr;
	Gwen::Controls::Button* addBlockButton = nullptr;
	Gwen::Controls::Button* duplicateBlockButton = nullptr;
	Gwen::Controls::Button* deleteBlockButton = nullptr;
	//Button* addBlockToPieceButton;
	Gwen::Controls::WindowControl* pieceWindow = nullptr;
	Gwen::Controls::Base* pieceListBase = nullptr;
	//Base* pieceSelectionListBase = nullptr;
	Gwen::Controls::ScrollControl* piecePropertiesScrollControl = nullptr;
	Gwen::Controls::PropertyTree* piecePropTree = nullptr;
	int piecePropTreeNumChildren = 0;
	Gwen::Controls::Base* pieceButtonBase = nullptr;
	Gwen::Controls::Button* addPieceButton = nullptr;
	Gwen::Controls::Button* duplicatePieceButton = nullptr;
	Gwen::Controls::Button* deletePieceButton = nullptr;
	//Button* deleteBlockFromPieceButton;
    
	Gwen::Controls::WindowControl* difficultyWindow = nullptr;
	Gwen::Controls::Base* difficultyListBase = nullptr;
	//Base* difficultySelectionListBase = nullptr;
	Gwen::Controls::ScrollControl* difficultyPropertiesScrollControl = nullptr;
	Gwen::Controls::PropertyTree* difficultyPropTree = nullptr;
	int difficultyPropTreeNumChildren = 0;
	//Base* difficultyButtonBase = nullptr;
	//Button* addDifficultyButton = nullptr;
	//Button* deleteDifficultyButton = nullptr;
    
	Gwen::Controls::WindowControl* askToSaveBase = nullptr;
    
	Gwen::Controls::Button* askToSaveYesButton = nullptr;
	Gwen::Controls::Button* askToSaveNoButton = nullptr;
	//Button* cancelExitButton = nullptr;
    
public:
	Gwen::Controls::WindowControl* loadOrCreateGameWindow = nullptr;
	bool exit = false;
private:
	Gwen::Controls::ListBox* gameTypesListBox = nullptr;
	Gwen::Controls::Label* gameTypeSelectLabel = nullptr;
	Gwen::Controls::Base* gameTypeSelectButtonBase = nullptr;
	Gwen::Controls::Button* editSelectedGameTypeButton = nullptr;
	Gwen::Controls::Button* createNewGameTypeButton = nullptr;
	Gwen::Controls::Button* duplicateGameTypeButton = nullptr;
	Gwen::Controls::Button* deleteGameTypeButton = nullptr;
    
	GameType *currentGameType = nullptr;
	BlockType *currentBlockType = nullptr;
    
	//i use these temp arrays because i need to save the modifications to something
	//ArrayList<PieceType*> currentBlockType_makePieceTypeWhenCleared;
	//ArrayList<BlockType*> currentBlockType_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType;
	//ArrayList<TurnFromBlockTypeToType*> currentBlockType_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut;
    
	PieceType *currentPieceType = nullptr;
	DifficultyType *currentDifficultyType = nullptr;
	//RotationSet currentPieceType_rotationSet;
	//ArrayList<BlockType*> currentPieceType_overrideBlockTypes;
    
	Gwen::Controls::WindowControl* selectWindow = nullptr;
	Gwen::Controls::ListBox* selectListBox = nullptr;
	Gwen::Controls::ListBox* chosenTypesListBox = nullptr;
	Gwen::Controls::Base* selectAddRemoveButtonBase = nullptr;
	Gwen::Controls::Base* selectConfirmCancelButtonBase = nullptr;
	Gwen::Controls::Button* selectAddButton = nullptr;
	Gwen::Controls::Button* selectRemoveButton = nullptr;
	Gwen::Controls::Button* selectConfirmButton = nullptr;
	Gwen::Controls::Button* selectCancelButton = nullptr;
    
	Gwen::Controls::ListBox* toFromListBox = nullptr;
	Gwen::Controls::ComboBox* fromCombo = nullptr;
	Gwen::Controls::ComboBox* toCombo = nullptr;
	TurnFromBlockTypeToType *currentTurnFromBlockTypeToType = nullptr;
    
	Gwen::Controls::WindowControl* rotationEditWindow = nullptr;
	Gwen::Controls::WindowControl* rotationPresetSelectWindow = nullptr;
	Gwen::Controls::ListBox* rotationListBox = nullptr;
	Gwen::Controls::ListBox* rotationPresetListBox = nullptr;
	//Base* rotationLeftBase = nullptr;
	//Base* rotationRightBase = nullptr;
	//Base* rotationListBoxBase = nullptr;
	//Base* rotationListBoxButtonBase = nullptr;
	//Base* rotationWindowButtonBase = nullptr;
	//Button* addRotationButton = nullptr;
	//Button* deleteRotationButton = nullptr;
	//Button* saveRotationButton = nullptr;
    
	EditRectangle *rotationEditRectangle = nullptr;
	Gwen::Controls::HorizontalSlider *rotationPreviewAnimationSpeedSlider = nullptr;
	RotationPreviewRectangle *rotationPreviewRectangle = nullptr;
    
public:
	bool rotationEditorOpen = false;
	bool presetRotationWindowOpen = false;
    
	bool windowOpen = false;
	BobsGame* bobsGame = nullptr;
private:
    
	int maxNumBlocks = 0;
	Rotation* currentRotation = nullptr;
	float previewSpeed = 0.5;
	long long lastPreviewTime = 0;
	int currentPreviewRotationIndex = 0;
	ArrayList<BobColor*> colors;
    
	ArrayList<RotationSet> rotationSets;
    
	int fontHeight = 20;
	int lastW = 0;
	int lastH = 0;
};


