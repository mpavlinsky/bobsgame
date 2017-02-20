
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




//=========================================================================================================================
class GameSequenceEditorControl : public Gwen::Controls::Base
{//=========================================================================================================================
public:
	//GWEN_CONTROL(GameSequenceEditorControl, Gwen::Controls::Base);
	//typedef GameSequenceEditorControl ThisClass;
	//typedef Gwen::Controls::Base BaseClass;
	static const char* GetIdentifier()
	{
		static const char* ident = "Base" ":" "GameSequenceEditorControl";
		return ident;
	};
	virtual Gwen::Controls::Base* DynamicCast(const char* Variable)
	{
		if (GetIdentifier() == Variable)
			return this;
        
		return Gwen::Controls::Base::DynamicCast(Variable);
	}
	virtual const char* GetTypeName() { return "GameSequenceEditorControl"; }
	virtual const char* GetBaseTypeName() { return Gwen::Controls::Base::GetTypeName(); }
	GameSequenceEditorControl(Gwen::Controls::Base* pParent, const Gwen::String& pName = "",BobsGame *b = nullptr);
    
    
	void openLoadOrCreateDialog(bool allowedToClose);
	void onLoadOrCreateButton(Gwen::Controls::Base* control);
	void onSaveButton(Gwen::Controls::Base* control);
	void onUploadButton(Gwen::Controls::Base* control);
	void onExitButton(Gwen::Controls::Base* control);
	void saveAndExit(Gwen::Controls::Base* control);
	void dontSaveAndExit(Gwen::Controls::Base* control);
	void saveAndOpen(Gwen::Controls::Base* control);
	void dontSaveAndOpen(Gwen::Controls::Base* control);
    
    
	void editSelectedGameSequence(Gwen::Controls::Base* control);
	void createNewGameSequence(Gwen::Controls::Base* control);
	void duplicateGameSequence(Gwen::Controls::Base* control);
	void deleteGameSequence(Gwen::Controls::Base* control);
    
    
	void onCurrentGameSequenceListRowSelect(Gwen::Controls::Base* control);
	void onAddButton(Gwen::Controls::Base* control);
	void onRemoveButton(Gwen::Controls::Base* control);
	void onUpButton(Gwen::Controls::Base* control);
	void onDownButton(Gwen::Controls::Base* control);
    
    
    
	void checkResize();
	void doResize();
	void populateGameTypesListBox();
	void populateGameSequencesListBox();
	void saveCurrentGameSequenceToXML();
	//GameSequence* getGameSequenceByName(string name);
	void saveGameSequenceListToCurrentGameSequence();
	void onGameSequencesListSelect(Gwen::Controls::Base* control);
    
    
private:
    
    
	
    
	Gwen::Controls::Base* leftBase = nullptr;
	Gwen::Controls::Base* rightBase = nullptr;
	Gwen::Controls::HorizontalSplitter *mainWindowSplitter = nullptr;
	Gwen::Controls::HorizontalSplitter *currentGameSequenceSplitter = nullptr;
    
	Gwen::Controls::Base* gameTypesListBoxBase = nullptr;
	Gwen::Controls::Base* gameTypesAddRemoveButtonsBase = nullptr;
	Gwen::Controls::ListBox* gameTypesListBox = nullptr;
	Gwen::Controls::Base* gameTypesButtonBase = nullptr;
	Gwen::Controls::Button* downloadGameTypesButton = nullptr;
	Gwen::Controls::WindowControl* currentGameSequenceWindow = nullptr;
	Gwen::Controls::Base* currentGameSequenceListBase = nullptr;
	Gwen::Controls::Base* currentGameSequencePropertiesBase = nullptr;
	Gwen::Controls::Base* currentGameSequenceButtonBase = nullptr;
	Gwen::Controls::Base* currentGameSequenceTextBoxesBase = nullptr;
	Gwen::Controls::Base* currentGameSequenceNameTextBoxBase = nullptr;
	Gwen::Controls::Base* currentGameSequenceDescriptionTextBoxBase = nullptr;
	Gwen::Controls::Label* currentGameSequenceNameLabel = nullptr;
	Gwen::Controls::TextBox* currentGameSequenceNameTextBox = nullptr;
	Gwen::Controls::Label* currentGameSequenceDescriptionLabel = nullptr;
	Gwen::Controls::TextBox* currentGameSequenceDescriptionTextBox = nullptr;
	Gwen::Controls::ListBox* currentGameSequenceListBox = nullptr;
	Gwen::Controls::ListBox* gameSequencesListBox = nullptr;
    
	//Controls::TabButton* settingsTab = nullptr;
	//ListBox* blockSelectionListBox = nullptr;
	//ListBox* pieceSelectionListBox = nullptr;
    
    
private:
	Gwen::Controls::Layout::Position* applyButtonsBasePositioner = nullptr;
	Gwen::Controls::Layout::Position* gameTypesAddRemoveButtonsPositioner = nullptr;
    
	Gwen::Controls::Base* applyButtonsBase = nullptr;
	Gwen::Controls::Button* loadButton = nullptr;
	Gwen::Controls::Button* saveButton = nullptr;
	Gwen::Controls::Button* uploadButton = nullptr;
	Gwen::Controls::Button* exitButton = nullptr;
	Gwen::Controls::Button* upButton = nullptr;
	Gwen::Controls::Button* downButton = nullptr;
    
	Gwen::Controls::WindowControl* gameTypesWindow = nullptr;
    
	//ScrollControl* settingsScrollControl = nullptr;
	//PropertyTree* settingsPropTree = nullptr;
	//int settingsPropTreeNumChildren = 0;
    
    
	Gwen::Controls::WindowControl* askToSaveBase = nullptr;
    
	Gwen::Controls::Button* askToSaveYesButton = nullptr;
	Gwen::Controls::Button* askToSaveNoButton = nullptr;
	//Button* cancelExitButton = nullptr;
    
public:
	Gwen::Controls::WindowControl* loadOrCreateGameSequenceWindow = nullptr;
	bool exit = false;
private:
    
    
	Gwen::Controls::Label* gameSequenceSelectLabel = nullptr;
	Gwen::Controls::Base* gameSequenceSelectButtonBase = nullptr;
	Gwen::Controls::Button* editSelectedGameSequenceButton = nullptr;
	Gwen::Controls::Button* createNewGameSequenceButton = nullptr;
	Gwen::Controls::Button* duplicateGameSequenceButton = nullptr;
	Gwen::Controls::Button* deleteGameSequenceButton = nullptr;
    
	GameSequence *currentGameSequence = nullptr;
    
    
	//WindowControl* selectWindow = nullptr;
	//ListBox* selectListBox = nullptr;
	//ListBox* chosenTypesListBox = nullptr;
	//Base* selectAddRemoveButtonBase = nullptr;
	//Base* selectConfirmCancelButtonBase = nullptr;
	Gwen::Controls::Button* selectAddButton = nullptr;
	Gwen::Controls::Button* selectRemoveButton = nullptr;
	Gwen::Controls::Button* selectConfirmButton = nullptr;
	Gwen::Controls::Button* selectCancelButton = nullptr;
    
    
public:
	bool windowOpen = false;
	BobsGame* bobsGame = nullptr;
    
    
	int fontHeight = 20;
	int lastW = 0;
	int lastH = 0;
};

