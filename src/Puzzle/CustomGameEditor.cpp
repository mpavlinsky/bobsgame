
#include "stdafx.h"





//	void Layout(Gwen::Skin::Base* skin)
//	{
//		if (GetDock() != Gwen::Pos::None) { return; }
//
//		SizeToChildren(true, true);
//	}

//#define ADD_UNIT_TEST( name )\
//	GUnit* RegisterUnitTest_##name( Gwen::Base* tab );\
//	{\
//		Button* pButton = cat->Add( #name );\
//		pButton->SetName( #name );\
//		GUnit* test = RegisterUnitTest_##name( pCenter );\
//		test->Hide();\
//		test->SetUnitTest( this );\
//		pButton->onPress.Add( this, &ThisClass::OnCategorySelect, test );\
//	}\

//	m_pLastControl = NULL;
//	Dock(Pos::Fill);
//	SetSize(1024, 768);
//	CollapsibleList* pList = new CollapsibleList(this);
//	GetLeft()->GetTabControl()->AddPage("CollapsibleList", pList);
//	GetLeft()->SetWidth(150);
//	m_TextOutput = new ListBox(GetBottom());
//	pButton = GetBottom()->GetTabControl()->AddPage("Output", m_TextOutput);
//	GetBottom()->SetHeight(200);
//	m_StatusBar = new StatusBar(this);
//	m_StatusBar->Dock(Pos::Bottom);
//	Layout::Center* pCenter = new Layout::Center(this);
//
//	pCenter->Dock(Pos::Fill);
//	{
//		CollapsibleCategory* cat = pList->Add("Basic");
//
//		ADD_UNIT_TEST(Button);
////		GUnit* RegisterUnitTest_Button(Gwen::Base* tab); 
////		{
////			Button* pButton = cat->Add("Button");
////			pButton->SetName( "Button" );
////			GUnit* test = RegisterUnitTest_Button( pCenter );
////			test->Hide();
////			test->SetUnitTest( this );
////			pButton->onPress.Add( this, &ThisClass::OnCategorySelect, test );
////		}

//		CollapsibleCategory* cat = pList->Add("Non-Standard");

//	m_StatusBar->SendToBack();
//	PrintText(L"Unit Test Started.\n");
//	m_fLastSecond = Gwen::Platform::GetTimeInSeconds();
//	m_iFrames = 0;
//	pList->GetNamedChildren("MenuStrip").DoAction();
//}
//
//void CustomGameScreen::OnCategorySelect(Gwen::Event::Info info)
//{
//	if (m_pLastControl)
//	{
//		m_pLastControl->Hide();
//	}
//
//	static_cast<Gwen::Base*>(info.Data)->Show();
//	m_pLastControl = static_cast<Gwen::Base*>(info.Data);
//}

//void CustomGameScreen::Render(Gwen::Skin::Base* skin)
//{
//	m_iFrames++;
//
//	if (m_fLastSecond < Gwen::Platform::GetTimeInSeconds())
//	{
//		m_StatusBar->SetText(Gwen::Utility::Format(L"GWEN Unit Test - %i fps", m_iFrames * 2));
//		m_fLastSecond = Gwen::Platform::GetTimeInSeconds() + 0.5f;
//		m_iFrames = 0;
//	}
//
//	BaseClass::Render(skin);
//}




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

using namespace Gwen;
using namespace Gwen::Controls;




//GWEN_CONTROL_CONSTRUCTOR(CustomGameEditorControl)
CustomGameEditorControl::CustomGameEditorControl(Gwen::Controls::Base* pParent, const Gwen::String& pName, BobsGame *b) : Base(pParent, pName)
{//=========================================================================================================================


	this->bobsGame = b;
	

	SetSize(GLUtils::getViewportWidth(), GLUtils::getViewportHeight());
	//SetDeleteOnClose(false);
	Dock(Pos::Fill);

	/*
	None
	Left
	Right
	Top
	Bottom
	CenterV
	CenterH
	Fill
	Center
	*/

	int w = GLUtils::getViewportWidth();
	int h = GLUtils::getViewportHeight();

	mainWindowSplitter = new Gwen::Controls::HorizontalSplitter(this);
	mainWindowSplitter->GetSplitter()->onDragged.Add(this, &CustomGameEditorControl::doResize);
	mainWindowSplitter->SetSize(w,h);


	leftBase = new Base(mainWindowSplitter);
	mainWindowSplitter->SetPanel(0, leftBase);
	//leftBase->SetSize(w * 3 / 5, h - 20);	
	//leftBase->Dock(Pos::Fill);
	{
		leftBaseTabControl = new Controls::TabControl(leftBase);
		leftBaseTabControl->Dock(Pos::Fill);

		settingsTab = leftBaseTabControl->AddPage(L"Game Settings");
		settingsPage = settingsTab->GetPage();
		settingsPage->Dock(Pos::Fill);

		Controls::Label *label = new Controls::Label(settingsPage, "label");
		label->SetText("Will crash on some combinations, SAVE OFTEN! Please request capabilities and features (and report bugs!) in the support forum and I will try and add them!");
		label->Dock(Pos::Top);
		label->SetHeight(15);

		//settings panel
		settingsWindow = new WindowControl(settingsPage);
		settingsWindow->SetTitle("Game Settings");
		settingsWindow->SetToolTip("This is where you set all of the general settings of the game and the rules by which you score or objectives, etc.");
		settingsWindow->SetClosable(false);
		settingsWindow->DisableResizing();
		settingsWindow->Dock(Pos::Fill);
		{

			settingsScrollControl = new ScrollControl(settingsWindow);
			settingsScrollControl->Dock(Pos::Fill);
			settingsScrollControl->SetAutoHideBars(false);
			settingsScrollControl->SetScroll(true, true);
			{


			}
		}

		blockTab = leftBaseTabControl->AddPage(L"Block Designer");
		blockPage = blockTab->GetPage();
		blockPage->Dock(Pos::Fill);


		blockWindow = new WindowControl(blockPage);
		blockWindow->SetTitle("Block Designer");
		blockWindow->SetToolTip("This is where you create and modify blocks.  Blocks are used inside of pieces, or to fill the grid, or to describe \"garbage\" that rises from the floor or drops from the top when your opponent scores.");
		blockWindow->SetClosable(false);
		blockWindow->DisableResizing();
		blockWindow->Dock(Pos::Fill);
		{

			blockWindowSplitter = new Gwen::Controls::HorizontalSplitter(blockWindow);
			blockWindowSplitter->GetSplitter()->onDragged.Add(this, &CustomGameEditorControl::doResize);
			blockWindowSplitter->Dock(Pos::Fill);


			blockListBase = new Base(blockWindowSplitter);
			blockWindowSplitter->SetPanel(0, blockListBase);
			//blockListBase->SetSize(blockWindow->Width() / 5 * 2, blockWindowSplitter->Height());
			{

				//blockSelectionListBase = new Base(blockListBase);
				//blockSelectionListBase->SetToolTip("This is a list of all the active blocks in this game.");
				//blockSelectionListBase->Dock(Pos::Top);
				//blockSelectionListBase->SetSize(blockListBase->Width() - 14, blockListBase->Height() - 55);
				{
					blockSelectionListBox = new ListBox(blockListBase);
					//blockSelectionListBox->SetMargin(Margin(0, 0, 0, 0));
					blockSelectionListBox->Dock(Pos::Fill);
					blockSelectionListBox->SetAllowMultiSelect(false);
					//blockSelectionListBox->SetSize(blockListBase->Width() - 30, blockListBase->Height() - 60);
					


					
					blockButtonBase = new Base(blockListBase);
					blockButtonBase->Dock(Pos::Bottom);
					//blockButtonBase->SetSize(blockListBase->Width(), 20);
					{

						//	Layout::Position* positioner = new Layout::Position(buttonBase);
						//	positioner->Dock(Pos::Fill);

						addBlockButton = new Button(blockButtonBase);
						addBlockButton->SetText(L"New Block");
						addBlockButton->SetToolTip("Create a new empty gray square block and add it to the list.");
						addBlockButton->Dock(Pos::Left | Pos::CenterV);
						addBlockButton->onPress.Add(this, &CustomGameEditorControl::onAddBlockButton);

						duplicateBlockButton = new Button(blockButtonBase);
						duplicateBlockButton->SetText(L"Duplicate Block");
						duplicateBlockButton->Dock(Pos::Left | Pos::CenterV);
						duplicateBlockButton->onPress.Add(this, &CustomGameEditorControl::onDuplicateBlockButton);

						deleteBlockButton = new Button(blockButtonBase);
						deleteBlockButton->SetText(L"Delete Block");
						deleteBlockButton->SetToolTip("Delete the selected block from the list.  It will be removed from any pieces that contain it as well.");
						deleteBlockButton->Dock(Pos::Left | Pos::CenterV);
						//deleteBlockButton->SetWidth(150);
						deleteBlockButton->onPress.Add(this, &CustomGameEditorControl::onDeleteBlockButton);
					}
					
				}


			}

			blockPropertiesScrollControl = new ScrollControl(blockWindowSplitter);
			blockWindowSplitter->SetPanel(1, blockPropertiesScrollControl);
			blockPropertiesScrollControl->SetAutoHideBars(false);
			blockPropertiesScrollControl->SetScroll(true, true);
			//blockPropertiesScrollControl->SetSize(blockWindow->Width() / 5 * 3 - 15, blockWindowSplitter->Height());
			{
				
				
			}
		}

		pieceTab = leftBaseTabControl->AddPage(L"Piece Designer");
		piecePage = pieceTab->GetPage();
		piecePage->Dock(Pos::Fill);

		pieceWindow = new WindowControl(piecePage);
		pieceWindow->SetTitle("Piece Designer");
		pieceWindow->SetToolTip("This is where you create and modify pieces.  Pieces are made up of one or more blocks.  They are usually what the player controls.");
		pieceWindow->SetClosable(false);
		pieceWindow->Dock(Pos::Fill);
		pieceWindow->DisableResizing();
		{

			pieceWindowSplitter = new Gwen::Controls::HorizontalSplitter(pieceWindow);
			pieceWindowSplitter->GetSplitter()->onDragged.Add(this, &CustomGameEditorControl::doResize);
			pieceWindowSplitter->Dock(Pos::Fill);


			pieceListBase = new Base(pieceWindowSplitter);
			pieceWindowSplitter->SetPanel(0, pieceListBase);
			//pieceListBase->SetSize(pieceWindow->Width() / 5 * 2, pieceWindowSplitter->Height());
			{

				//pieceSelectionListBase = new Base(pieceListBase);
				//pieceSelectionListBase->SetToolTip("This is a list of all the active pieces in this game.");
				//pieceSelectionListBase->Dock(Pos::Top);
				//pieceSelectionListBase->SetSize(pieceListBase->Width() - 14, pieceListBase->Height() - 55);
				{
					
					pieceSelectionListBox = new ListBox(pieceListBase);
					//pieceSelectionListBox->SetMargin(Margin(0, 0, 0, 0));
					pieceSelectionListBox->Dock(Pos::Fill);
					pieceSelectionListBox->SetAllowMultiSelect(false);
					//pieceSelectionListBox->SetSize(pieceListBase->Width() - 30, pieceListBase->Height() - 60);
				}

				pieceButtonBase = new Base(pieceListBase);
				pieceButtonBase->Dock(Pos::Bottom);
				//pieceButtonBase->SetSize(pieceListBase->Width(), 20);
				{

					//	Layout::Position* positioner = new Layout::Position(buttonBase);
					//	positioner->Dock(Pos::Fill);

					addPieceButton = new Button(pieceButtonBase);
					addPieceButton->SetText(L"New Piece");
					addPieceButton->SetToolTip("Create a new empty piece populated with a single gray square block.");
					addPieceButton->Dock(Pos::Left | Pos::CenterV);
					addPieceButton->onPress.Add(this, &CustomGameEditorControl::onAddPieceButton);

					duplicatePieceButton = new Button(pieceButtonBase);
					duplicatePieceButton->SetText(L"Duplicate Piece");
					duplicatePieceButton->Dock(Pos::Left | Pos::CenterV);
					duplicatePieceButton->onPress.Add(this, &CustomGameEditorControl::onDuplicatePieceButton);

					deletePieceButton = new Button(pieceButtonBase);
					deletePieceButton->SetText(L"Delete Piece");
					deletePieceButton->SetToolTip("Delete the selected piece from the list of pieces.");
					deletePieceButton->Dock(Pos::Left | Pos::CenterV);
					//deletePieceButton->SetWidth(150);
					deletePieceButton->onPress.Add(this, &CustomGameEditorControl::onDeletePieceButton);
				}
			}

			piecePropertiesScrollControl = new ScrollControl(pieceWindowSplitter);
			pieceWindowSplitter->SetPanel(1, piecePropertiesScrollControl);
			piecePropertiesScrollControl->SetAutoHideBars(false);
			piecePropertiesScrollControl->SetScroll(true, true);
			//piecePropertiesScrollControl->SetSize(pieceWindow->Width() / 5 * 3 - 15, pieceWindowSplitter->Height());
			{
				
			}
		}

		difficultyTab = leftBaseTabControl->AddPage(L"Difficulty Editor");
		difficultyPage = difficultyTab->GetPage();
		difficultyPage->Dock(Pos::Fill);

		difficultyWindow = new WindowControl(difficultyPage);
		difficultyWindow->SetTitle("Difficulty Editor");
		difficultyWindow->SetToolTip("This is where you create and modify difficulty settings.");
		difficultyWindow->SetClosable(false);
		difficultyWindow->Dock(Pos::Fill);
		difficultyWindow->DisableResizing();
		{

			difficultyWindowSplitter = new Gwen::Controls::HorizontalSplitter(difficultyWindow);
			difficultyWindowSplitter->GetSplitter()->onDragged.Add(this, &CustomGameEditorControl::doResize);
			difficultyWindowSplitter->Dock(Pos::Fill);


			difficultyListBase = new Base(difficultyWindowSplitter);
			difficultyWindowSplitter->SetPanel(0, difficultyListBase);
			//difficultyListBase->SetSize(difficultyWindow->Width() / 5 * 2, difficultyWindowSplitter->Height());
			{

				//difficultySelectionListBase = new Base(difficultyListBase);
				//difficultySelectionListBase->SetToolTip("This is a list of all the active difficultys in this game.");
				//difficultySelectionListBase->Dock(Pos::Top);
				//difficultySelectionListBase->SetSize(difficultyListBase->Width() - 14, difficultyListBase->Height() - 55);
				{

					difficultySelectionListBox = new ListBox(difficultyListBase);
					//difficultySelectionListBox->SetMargin(Margin(0, 0, 0, 0));
					difficultySelectionListBox->Dock(Pos::Fill);
					difficultySelectionListBox->SetAllowMultiSelect(false);
					//difficultySelectionListBox->SetSize(difficultyListBase->Width() - 30, difficultyListBase->Height() - 60);
				}

//				difficultyButtonBase = new Base(difficultyListBase);
//				difficultyButtonBase->Dock(Pos::Bottom);
//				//difficultyButtonBase->SetSize(difficultyListBase->Width(), 20);
//				{
//
//					//	Layout::Position* positioner = new Layout::Position(buttonBase);
//					//	positioner->Dock(Pos::Fill);
//
//					addDifficultyButton = new Button(difficultyButtonBase);
//					addDifficultyButton->SetText(L"New Difficulty");
//					addDifficultyButton->SetToolTip("Create a new empty difficulty populated with a single gray square block.");
//					addDifficultyButton->Dock(Pos::Left | Pos::CenterV);
//					addDifficultyButton->onPress.Add(this, &CustomGameEditorControl::onAddDifficultyButton);
//
//					deleteDifficultyButton = new Button(difficultyButtonBase);
//					deleteDifficultyButton->SetText(L"Delete Difficulty");
//					deleteDifficultyButton->SetToolTip("Delete the selected difficulty from the list of difficultys.");
//					deleteDifficultyButton->Dock(Pos::Left | Pos::CenterV);
//					//deleteDifficultyButton->SetWidth(150);
//					deleteDifficultyButton->onPress.Add(this, &CustomGameEditorControl::onDeleteDifficultyButton);
//				}
			}

			difficultyPropertiesScrollControl = new ScrollControl(difficultyWindowSplitter);
			difficultyWindowSplitter->SetPanel(1, difficultyPropertiesScrollControl);
			difficultyPropertiesScrollControl->SetAutoHideBars(false);
			difficultyPropertiesScrollControl->SetScroll(true, true);
			//difficultyPropertiesScrollControl->SetSize(difficultyWindow->Width() / 5 * 3 - 15, difficultyWindowSplitter->Height());
			{

			}
		}
	}



	previewBase = new Base(mainWindowSplitter);
	mainWindowSplitter->SetPanel(1, previewBase);
	//previewBase->SetSize(w * 2 / 5, h - 20);
	//previewBase->Dock(Pos::Fill);
	{

		applyButtonsBase = new Base(previewBase);
		applyButtonsBase->Dock(Pos::Top);
		applyButtonsBase->SetSize(previewBase->Width(), 20);
		{

			previewButton = new Button(applyButtonsBase);
			previewButton->SetText(L"Preview");
			//previewButton->SetToolTip("Preview these settings below.");
			previewButton->Dock(Pos::Left | Pos::Center);
			previewButton->SetWidth(70);
			previewButton->onPress.Add(this, &CustomGameEditorControl::onPreviewButton);

			loadButton = new Button(applyButtonsBase);
			loadButton->SetText(L"Load or create new");
			//loadButton->SetToolTip("Load an existing game or create a new one.");
			loadButton->Dock(Pos::Left | Pos::Center);
			loadButton->SetWidth(150);
			loadButton->onPress.Add(this, &CustomGameEditorControl::onLoadOrCreateButton);

			saveButton = new Button(applyButtonsBase);
			saveButton->SetText(L"Save");
			saveButton->SetToolTip("Saves to XML in "+string(SDL_GetPrefPath("Bob Corporation","bob's game"))+".  Renames existing file with versioning.  Do this often as some combinations may crash.");
			saveButton->Dock(Pos::Left | Pos::Center);
			saveButton->SetWidth(50);
			saveButton->onPress.Add(this, &CustomGameEditorControl::onSaveButton);


			uploadButton = new Button(applyButtonsBase);
			uploadButton->SetText(L"Upload");
			uploadButton->SetToolTip("Upload this game to the server so others can play it.  You will keep ownership rights and reuploading modified versions will overwrite the version on the server.  You can only upload one new game type every 10 minutes.  Please do not upload broken games or unfinished games.");
			uploadButton->Dock(Pos::Left | Pos::Center);
			uploadButton->SetWidth(50);
			uploadButton->onPress.Add(this, &CustomGameEditorControl::onUploadButton);


			exitButton = new Button(applyButtonsBase);
			exitButton->SetText(L"Leave");
			//exitButton->SetToolTip("Leave (Ask to save changes).");
			exitButton->Dock(Pos::Left | Pos::Center);
			exitButton->SetWidth(50);
			exitButton->onPress.Add(this, &CustomGameEditorControl::onExitButton);

			//load, save, preview, exit



			//on load
			//edit
			//copy to new
			//create new game
			//cancel
		}


		darkRectangle = new PreviewRectangle(previewBase, "", bobsGame);
		darkRectangle->SetColor(Color(0, 0, 0, 255));
		darkRectangle->Dock(Pos::Top);
		darkRectangle->SetSize(previewBase->Width(), previewBase->Height() - 20);
	}

	GetParent()->SizeToChildren();
	SizeToChildren();




	//doResize();

	mainWindowSplitter->SetSplitterWidth(w / 5 * 3);

	//mainWindowSplitter->SetSize(w * 3 / 5, h - 20);
	//leftBase->SetSize(w * 3 / 5, h - 20);
	//leftBaseTabControl->SetSize(w * 3 / 5, h - 20);
	//settingsPage->SetSize(w * 3 / 5, h - 20);
	settingsWindow->SetSize(w * 3 / 5, h - 20);

	settingsScrollControl->SetWidth(settingsWindow->Width()-20);

	blockWindowSplitter->SetSize(blockWindow->Width(), blockWindow->Height());
	blockWindowSplitter->SetSplitterWidth(blockWindow->Width() / 3 * 1);
	blockListBase->SetSize(blockWindow->Width() / 3 * 1, blockWindowSplitter->Height());
	blockSelectionListBox->SetSize(blockListBase->Width() - 30, blockListBase->Height() - 60);
	blockButtonBase->SetSize(blockListBase->Width(), 20);
	blockPropertiesScrollControl->SetSize(blockWindow->Width() / 3 * 2 - 15, blockWindowSplitter->Height());

	pieceWindowSplitter->SetSize(pieceWindow->Width(), pieceWindow->Height());
	pieceWindowSplitter->SetSplitterWidth(pieceWindow->Width() / 3 * 1);
	pieceListBase->SetSize(pieceWindow->Width() / 3 * 1, pieceWindowSplitter->Height());
	pieceSelectionListBox->SetSize(pieceListBase->Width() - 30, pieceListBase->Height() - 60);
	pieceButtonBase->SetSize(pieceListBase->Width(), 20);
	piecePropertiesScrollControl->SetSize(pieceWindow->Width() / 3 * 2 - 15, pieceWindowSplitter->Height());

	previewBase->SetSize(w * 2 / 5, h - 20);
	applyButtonsBase->SetSize(previewBase->Width(), 20);
	darkRectangle->SetSize(previewBase->Width(), previewBase->Height() - 20);


	currentGameType = new GameType();
	//currentGameType->tetrid();
	BlockType *bt = new BlockType();
	bt->name = "Gray Square";
	bt->spriteName = "Square";
	bt->colors.add(BobColor::gray);
	bt->useInNormalPieces = true;
	PieceType *pt = new PieceType();
	pt->name = "Single Block Piece";
	pt->useAsNormalPiece = true;
	currentGameType->blockTypes.add(bt);
	currentGameType->pieceTypes.add(pt);
	//currentGameType->difficultyTypes.add(new DifficultyType());
	currentBlockType = currentGameType->blockTypes.get(0);
	currentPieceType = currentGameType->pieceTypes.get(0);
	currentDifficultyType = currentGameType->difficultyTypes.get(0);
	initFromCurrentGameType();

	//settingsPropTree->SetWidth(500);
	//blockPropTree->SetWidth(500);
	//piecePropTree->SetWidth(500);
	doResize();



//	if (blockPropTree != nullptr)
//	{
//		blockPropTree->DelayedDelete();
//		GetCanvas()->DoThink();
//		//delete blockPropTree;
//		blockPropTree = nullptr;
//	}
//
//	if (piecePropTree != nullptr)
//	{
//		piecePropTree->DelayedDelete();
//		GetCanvas()->DoThink();
//		//delete piecePropTree;
//		piecePropTree = nullptr;
//	}

	colors.add(BobColor::cyan);
	colors.add(BobColor::magenta);
	colors.add(BobColor::green);
	colors.add(BobColor::lighterPurple);//was purple, seeing if it helps differentiate from blue
	colors.add(BobColor::darkBlue);
	colors.add(BobColor::orange);
	colors.add(BobColor::yellow);
	colors.add(BobColor::lighterPink);
	colors.add(BobColor::red);
	colors.add(BobColor::white);
	colors.add(BobColor::burgandy);
	colors.add(BobColor::olive);
	colors.add(BobColor::darkerCyan);
	colors.add(BobColor::darkerMagenta);
	colors.add(BobColor::darkerGreen);
	colors.add(BobColor::darkerPurple);
	colors.add(BobColor::lighterBlue);
	colors.add(BobColor::darkerOrange);
	colors.add(BobColor::darkerYellow);
	colors.add(BobColor::darkerPink);
	colors.add(BobColor::darkerRed);
	colors.add(BobColor::darkerBurgandy);
	colors.add(BobColor::darkerOlive);

	rotationSets.add(Piece::get2BlockRotateAround00RotationSet());
	rotationSets.add(Piece::get2BlockBottomLeftAlwaysFilledRotationSet());
	rotationSets.add(Piece::get3BlockVerticalRotationSet());
	rotationSets.add(Piece::get3BlockHorizontalRotationSet());
	rotationSets.add(Piece::get3BlockTRotationSet());
	rotationSets.add(Piece::get3BlockLRotationSet());
	rotationSets.add(Piece::get3BlockJRotationSet());
	rotationSets.add(Piece::get3BlockIRotationSet());
	rotationSets.add(Piece::get3BlockCRotationSet());
	rotationSets.add(Piece::get3BlockDRotationSet());
	rotationSets.add(Piece::get4BlockORotationSet());
	rotationSets.add(Piece::get4BlockSolidRotationSet());
	rotationSets.add(Piece::get9BlockSolidRotationSet());
	rotationSets.add(Piece::get4BlockIRotationSet(RotationType::DTET));
	rotationSets.add(Piece::get4BlockJRotationSet(RotationType::DTET));
	rotationSets.add(Piece::get4BlockLRotationSet(RotationType::DTET));
	rotationSets.add(Piece::get4BlockSRotationSet(RotationType::DTET));
	rotationSets.add(Piece::get4BlockTRotationSet(RotationType::DTET));
	rotationSets.add(Piece::get4BlockZRotationSet(RotationType::DTET));
	rotationSets.add(Piece::get4BlockIRotationSet(RotationType::SRS));
	rotationSets.add(Piece::get4BlockJRotationSet(RotationType::SRS));
	rotationSets.add(Piece::get4BlockLRotationSet(RotationType::SRS));
	rotationSets.add(Piece::get4BlockSRotationSet(RotationType::SRS));
	rotationSets.add(Piece::get4BlockTRotationSet(RotationType::SRS));
	rotationSets.add(Piece::get4BlockZRotationSet(RotationType::SRS));
	rotationSets.add(Piece::get4BlockIRotationSet(RotationType::SEGA));
	rotationSets.add(Piece::get4BlockJRotationSet(RotationType::SEGA));
	rotationSets.add(Piece::get4BlockLRotationSet(RotationType::SEGA));
	rotationSets.add(Piece::get4BlockSRotationSet(RotationType::SEGA));
	rotationSets.add(Piece::get4BlockTRotationSet(RotationType::SEGA));
	rotationSets.add(Piece::get4BlockZRotationSet(RotationType::SEGA));
	rotationSets.add(Piece::get4BlockIRotationSet(RotationType::NES));
	rotationSets.add(Piece::get4BlockJRotationSet(RotationType::NES));
	rotationSets.add(Piece::get4BlockLRotationSet(RotationType::NES));
	rotationSets.add(Piece::get4BlockSRotationSet(RotationType::NES));
	rotationSets.add(Piece::get4BlockTRotationSet(RotationType::NES));
	rotationSets.add(Piece::get4BlockZRotationSet(RotationType::NES));
	rotationSets.add(Piece::get4BlockIRotationSet(RotationType::GB));
	rotationSets.add(Piece::get4BlockJRotationSet(RotationType::GB));
	rotationSets.add(Piece::get4BlockLRotationSet(RotationType::GB));
	rotationSets.add(Piece::get4BlockSRotationSet(RotationType::GB));
	rotationSets.add(Piece::get4BlockTRotationSet(RotationType::GB));
	rotationSets.add(Piece::get4BlockZRotationSet(RotationType::GB));
}

void CustomGameEditorControl::initFromCurrentGameType()
{//=========================================================================================================================
	initSettingsPropTree(currentGameType);
	initBlockSelectionListBox();
	initBlockPropTree(currentBlockType);
	initPieceSelectionListBox();
	initPiecePropTree(currentPieceType);
	initDifficultySelectionListBox();
	initDifficultyPropTree(currentDifficultyType);
}


void CustomGameEditorControl::saveAllToCurrentGameType()
{//=========================================================================================================================
	saveSettingsPropTreeToCurrentGameType();
	saveBlockPropTreeToCurrentBlockType();
	savePiecePropTreeToCurrentPieceType();
	saveDifficultyPropTreeToCurrentDifficultyType();
}




void CustomGameEditorControl::checkResize()
{//=========================================================================================================================
	if (lastW != GLUtils::getViewportWidth() || lastH != GLUtils::getViewportHeight())
	{

		doResize();

		lastW = GLUtils::getViewportWidth();
		lastH = GLUtils::getViewportHeight();

	}
}
void CustomGameEditorControl::doResize()
{//=========================================================================================================================

	
	SetSize(GLUtils::getViewportWidth(), GLUtils::getViewportHeight());
	GetParent()->SizeToChildren();

	int w = GLUtils::getViewportWidth();
	int h = GLUtils::getViewportHeight();
	mainWindowSplitter->SetSize(w, h);
	{

		//leftBase->SetSize(w * 3 / 5, h - 20);
		{
			//leftBaseTabControl->Dock(Pos::Fill);
			{
				//settingsPage->Dock(Pos::Fill);
				{
					//settingsWindow->Dock(Pos::Fill);
					{
						//settingsScrollControl->Dock(Pos::Fill);
						{
							if (settingsPropTree != nullptr)
							{
								int sw = settingsScrollControl->Width() - 20;
								if (600 > sw)sw = 600;
								settingsPropTree->SetSize(settingsScrollControl->Width() - 20, settingsPropTreeNumChildren * fontHeight);
							}
						}
					}
				}

				//blockPage->Dock(Pos::Fill);
				{
					//blockWindow->Dock(Pos::Fill);
					{
						//blockWindowSplitter->Dock(Pos::Fill);
						{

							//blockListBase->SetSize(blockWindow->Width() / 5 * 2, blockWindowSplitter->Height());
							{

								//blockSelectionListBase->SetSize(blockListBase->Width() - 14, blockListBase->Height() - 55);
								{
									blockSelectionListBox->SetSize(blockListBase->Width() - 30, blockListBase->Height() - 60);
								}

								blockButtonBase->SetSize(blockListBase->Width(), 20);
							}


							//blockPropertiesScrollControl->SetSize(blockWindow->Width() / 5 * 3 - 15, blockWindowSplitter->Height());
							{
								if (blockPropTree != nullptr)
								{
									int sw = blockPropertiesScrollControl->Width() - 20;
									if (400 > sw)sw = 400;
									blockPropTree->SetSize(sw, blockPropTreeNumChildren * fontHeight);
								}
							}
						}
					}
				}

				//piecePage->Dock(Pos::Fill);
				{
					//pieceWindow->Dock(Pos::Fill);
					{
						//pieceWindowSplitter->Dock(Pos::Fill);
						{

							//pieceListBase->SetSize(pieceWindow->Width() / 5 * 2, pieceWindowSplitter->Height());
							{
								//pieceWindowSplitter->SetSplitterWidth(pieceSelectionListBox->Width());
								//pieceSelectionListBase->SetSize(pieceListBase->Width() - 14, pieceListBase->Height() - 55);
								{
									pieceSelectionListBox->SetSize(pieceListBase->Width() - 30, pieceListBase->Height() - 60);
								}

								pieceButtonBase->SetSize(pieceListBase->Width(), 20);
							}

							//piecePropertiesScrollControl->SetSize(pieceWindow->Width() / 5 * 3 - 15, pieceWindowSplitter->Height());
							{
								if (piecePropTree != nullptr)
								{
									int sw = piecePropertiesScrollControl->Width() - 20;
									if (400 > sw)sw = 400;
									piecePropTree->SetSize(sw, piecePropTreeNumChildren * fontHeight);
								}
							}
						}
					}
				}


				//difficultyPage->Dock(Pos::Fill);
				{
					//difficultyWindow->Dock(Pos::Fill);
					{
						//difficultyWindowSplitter->Dock(Pos::Fill);
						{

							//difficultyListBase->SetSize(difficultyWindow->Width() / 5 * 2, difficultyWindowSplitter->Height());
							{
								//difficultyWindowSplitter->SetSplitterWidth(difficultySelectionListBox->Width());
								//difficultySelectionListBase->SetSize(difficultyListBase->Width() - 14, difficultyListBase->Height() - 55);
								{
									difficultySelectionListBox->SetSize(difficultyListBase->Width() - 30, difficultyListBase->Height() - 60);
								}

								//difficultyButtonBase->SetSize(difficultyListBase->Width(), 20);
							}

							//difficultyPropertiesScrollControl->SetSize(difficultyWindow->Width() / 5 * 3 - 15, difficultyWindowSplitter->Height());
							{
								if (difficultyPropTree != nullptr)
								{
									int sw = difficultyPropertiesScrollControl->Width() - 20;
									if (400 > sw)sw = 400;
									difficultyPropTree->SetSize(sw, difficultyPropTreeNumChildren * fontHeight);
								}
							}
						}
					}
				}
			}
		}

		previewBase->SetSize(w * 2 / 5, h - 20);
		{
			applyButtonsBase->SetSize(previewBase->Width(), 20);
			darkRectangle->SetSize(previewBase->Width(), previewBase->Height() - 20);
		}
	}

	SizeToChildren(true, true);


}



BlockType* CustomGameEditorControl::getBlockTypeByUUID(string uuid)
{//=========================================================================================================================
	BlockType *bt = nullptr;
	for (int i = 0; i<currentGameType->blockTypes.size(); i++)
	{
		BlockType *b = currentGameType->blockTypes.get(i);
		if (b->uuid == uuid)
		{
			bt = b;
		}
	}
	return bt;
}

PieceType* CustomGameEditorControl::getPieceTypeByUUID(string uuid)
{//=========================================================================================================================
	PieceType *bt = nullptr;
	for (int i = 0; i<currentGameType->pieceTypes.size(); i++)
	{
		PieceType *b = currentGameType->pieceTypes.get(i);
		if (b->uuid == uuid)
		{
			bt = b;
		}
	}
	return bt;
}

DifficultyType* CustomGameEditorControl::getDifficultyTypeByName(string name)
{//=========================================================================================================================
	DifficultyType *bt = nullptr;
	for (int i = 0; i<currentGameType->difficultyTypes.size(); i++)
	{
		DifficultyType *b = currentGameType->difficultyTypes.get(i);
		if (b->name == name)
		{
			bt = b;
		}
	}
	return bt;
}

void CustomGameEditorControl::onBlockListRowSelect(Base* control)
{//=========================================================================================================================

	if (control == nullptr)return;

	//if a blocktype is currently selected, save it to the blocktype
	if (currentBlockType != nullptr)
	{
		//apply piece properties to currentPieceType before saving block properties in case it is linked to a piece that was just modified
		savePiecePropTreeToCurrentPieceType();

		saveBlockPropTreeToCurrentBlockType();
	}

	//populate all the block fields
	Layout::TableRow* row = (Layout::TableRow*)control;
	string uuid = row->GetName().c_str();

	BlockType *bt = getBlockTypeByUUID(uuid);

	if (bt == nullptr)
	{
		BobsGame::log.error("Could not find blocktype with uuid:" + uuid);
		return;
	}
	currentBlockType = bt;
	initBlockPropTree(bt);

}




void CustomGameEditorControl::initBlockSelectionListBox()
{//=========================================================================================================================

	currentBlockType = nullptr;
	blockSelectionListBox->Clear();
	GetCanvas()->DoThink();
	

 //populate the blockList with BlockTypes from settings
	Layout::TableRow* row;
//	if (currentGameType->blockTypes.size() == 0)
//	{
//		BlockType *pt = new BlockType();
//		pt->name = "Square Block With Any Color";
//		currentGameType->blockTypes.add(pt);
//	}


	for (int i = 0; i < currentGameType->blockTypes.size(); i++)
	{
		BlockType *bt = currentGameType->blockTypes.get(i);
		row = blockSelectionListBox->AddItem(bt->name, bt->uuid);
		row->onRowSelected.Add(this, &CustomGameEditorControl::onBlockListRowSelect);
		if (i == 0)
		{
			blockSelectionListBox->SetSelectedRow(row);
			onBlockListRowSelect(row);
		}
	}

}

void CustomGameEditorControl::initPieceSelectionListBox()
{//=========================================================================================================================
	currentPieceType = nullptr;
	pieceSelectionListBox->Clear();

	GetCanvas()->DoThink();

	Layout::TableRow* row;
//	if (currentGameType->pieceTypes.size() == 0)
//	{
//		PieceType *pt = new PieceType();
//		pt->name = "Single Square Block Piece";
//		currentGameType->pieceTypes.add(pt);
//	}


	for (int i = 0; i<currentGameType->pieceTypes.size(); i++)
	{
		PieceType *bt = currentGameType->pieceTypes.get(i);
		row = pieceSelectionListBox->AddItem(bt->name, bt->uuid);
		row->onRowSelected.Add(this, &CustomGameEditorControl::onPieceListRowSelect);

		if(i==0)
		{
			pieceSelectionListBox->SetSelectedRow(row);
			onPieceListRowSelect(row);
		}
	}

}

void CustomGameEditorControl::initSettingsPropTree(GameType *s)
{//=========================================================================================================================
	if (settingsPropTree != nullptr)
	{
		settingsPropTree->DelayedDelete();
		GetCanvas()->DoThink();
		//delete settingsPropTree;
		settingsPropTree = nullptr;
	}


	settingsPropTree = new PropertyTree(settingsScrollControl);
	//settingsPropTree->Dock(Pos::Fill);
	settingsPropTree->SetWidth(600);
	settingsPropTree->SetHeight(1000);
	{
		int n = 0;
		Properties* p;
		n++; p = settingsPropTree->Add("Game Rules"); p->SetToolTip("General game settings");
		{

			n++; p->Add(s->name_Info.label, string(s->name))->SetToolTip(s->name_Info.tip);
			n++; p->Add(s->rules_Info.label, string(s->rules))->SetToolTip(s->rules_Info.tip);

			Property::ComboBox* scoreTypeCombo = new Property::ComboBox(p);
			{
				scoreTypeCombo->GetComboBox()->AddItem(L"Blocks cleared", to_string((int)ScoreType::BLOCKS_CLEARED));
				scoreTypeCombo->GetComboBox()->AddItem(L"Lines cleared", to_string((int)ScoreType::LINES_CLEARED));
				scoreTypeCombo->GetComboBox()->AddItem(L"Pieces made", to_string((int)ScoreType::PIECES_MADE));
				n++; p->Add(s->scoreType_Info.label, scoreTypeCombo, to_string((int)s->scoreType))->SetToolTip(s->scoreType_Info.tip);
				//pRow->onChange.Add(this, &LevelSelectMenuControl::OnFirstNameChanged);
			}
			n++; p->Add(s->scoreTypeAmountPerLevelGained_Info.label, to_string(s->scoreTypeAmountPerLevelGained))->SetToolTip(s->scoreTypeAmountPerLevelGained_Info.tip);

			n++; p->Add(s->nextPieceEnabled_Info.label, new Property::Checkbox(p), to_string(s->nextPieceEnabled))->SetToolTip(s->nextPieceEnabled_Info.tip);
			n++; p->Add(s->numberOfNextPiecesToShow_Info.label, to_string(s->numberOfNextPiecesToShow))->SetToolTip(s->numberOfNextPiecesToShow_Info.tip);

			n++; p->Add(s->holdPieceEnabled_Info.label, new Property::Checkbox(p), to_string(s->holdPieceEnabled))->SetToolTip(s->holdPieceEnabled_Info.tip);
			n++; p->Add(s->resetHoldPieceRotation_Info.label, new Property::Checkbox(p), to_string(s->resetHoldPieceRotation))->SetToolTip(s->resetHoldPieceRotation_Info.tip);

			n++; p->Add(s->chainRule_AmountPerChain_Info.label, to_string(s->chainRule_AmountPerChain))->SetToolTip(s->chainRule_AmountPerChain_Info.tip);
			n++; p->Add(s->chainRule_CheckEntireLine_Info.label, new Property::Checkbox(p), to_string(s->chainRule_CheckEntireLine))->SetToolTip(s->chainRule_CheckEntireLine_Info.tip);
			n++; p->Add(s->chainRule_CheckRow_Info.label, new Property::Checkbox(p), to_string(s->chainRule_CheckRow))->SetToolTip(s->chainRule_CheckRow_Info.tip);
			n++; p->Add(s->chainRule_CheckColumn_Info.label, new Property::Checkbox(p), to_string(s->chainRule_CheckColumn))->SetToolTip(s->chainRule_CheckColumn_Info.tip);
			n++; p->Add(s->chainRule_CheckDiagonal_Info.label, new Property::Checkbox(p), to_string(s->chainRule_CheckDiagonal))->SetToolTip(s->chainRule_CheckDiagonal_Info.tip);
			n++; p->Add(s->chainRule_CheckRecursiveConnections_Info.label, new Property::Checkbox(p), to_string(s->chainRule_CheckRecursiveConnections))->SetToolTip(s->chainRule_CheckRecursiveConnections_Info.tip);
			n++; p->Add(s->chainRule_CheckTouchingBreakerBlocksChain_Info.label, new Property::Checkbox(p), to_string(s->chainRule_CheckTouchingBreakerBlocksChain))->SetToolTip(s->chainRule_CheckTouchingBreakerBlocksChain_Info.tip);

			n++; p->Add(s->gravityRule_onlyMoveDownDisconnectedBlocks_Info.label, new Property::Checkbox(p), to_string(s->gravityRule_onlyMoveDownDisconnectedBlocks))->SetToolTip(s->gravityRule_onlyMoveDownDisconnectedBlocks_Info.tip);

			Property::ComboBox* playingFieldGarbageTypeCombo = new Property::ComboBox(p);
			{
				playingFieldGarbageTypeCombo->GetComboBox()->AddItem(L"Match bottom row", to_string((int)GarbageType::MATCH_BOTTOM_ROW));
				playingFieldGarbageTypeCombo->GetComboBox()->AddItem(L"Random", to_string((int)GarbageType::RANDOM));
				playingFieldGarbageTypeCombo->GetComboBox()->AddItem(L"Zig zag pattern", to_string((int)GarbageType::ZIGZAG_PATTERN));
				n++; p->Add(s->playingFieldGarbageType_Info.label, playingFieldGarbageTypeCombo, to_string((int)s->playingFieldGarbageType))->SetToolTip(s->playingFieldGarbageType_Info.tip);
				//pRow->onChange.Add(this, &LevelSelectMenuControl::OnFirstNameChanged);
			}
			Property::ComboBox* playingFieldGarbageSpawnRuleCombo = new Property::ComboBox(p);
			{
				playingFieldGarbageSpawnRuleCombo->GetComboBox()->AddItem(L"None", to_string((int)GarbageSpawnRule::NONE));
				playingFieldGarbageSpawnRuleCombo->GetComboBox()->AddItem(L"Milliseconds passed", to_string((int)GarbageSpawnRule::TICKS));
				playingFieldGarbageSpawnRuleCombo->GetComboBox()->AddItem(L"Lines cleared", to_string((int)GarbageSpawnRule::LINES_CLEARED));
				playingFieldGarbageSpawnRuleCombo->GetComboBox()->AddItem(L"Blocks cleared", to_string((int)GarbageSpawnRule::BLOCKS_CLEARED));
				playingFieldGarbageSpawnRuleCombo->GetComboBox()->AddItem(L"Pieces made", to_string((int)GarbageSpawnRule::PIECES_MADE));
				n++; p->Add(s->playingFieldGarbageSpawnRule_Info.label, playingFieldGarbageSpawnRuleCombo, to_string((int)s->playingFieldGarbageSpawnRule))->SetToolTip(s->playingFieldGarbageSpawnRule_Info.tip);
				//pRow->onChange.Add(this, &LevelSelectMenuControl::OnFirstNameChanged);
			}
			//n++; p->Add(s->playingFieldGarbageSpawnRuleAmount_Info.label, to_string(s->playingFieldGarbageSpawnRuleAmount))->SetToolTip(s->playingFieldGarbageSpawnRuleAmount_Info.tip);

			n++; p->Add(s->hardDropPunchThroughToLowestValidGridPosition_Info.label, new Property::Checkbox(p), to_string(s->hardDropPunchThroughToLowestValidGridPosition))->SetToolTip(s->hardDropPunchThroughToLowestValidGridPosition_Info.tip);

			n++; p->Add(s->twoSpaceWallKickAllowed_Info.label, new Property::Checkbox(p), to_string(s->twoSpaceWallKickAllowed))->SetToolTip(s->twoSpaceWallKickAllowed_Info.tip);
			n++; p->Add(s->diagonalWallKickAllowed_Info.label, new Property::Checkbox(p), to_string(s->diagonalWallKickAllowed))->SetToolTip(s->diagonalWallKickAllowed_Info.tip);
			n++; p->Add(s->pieceClimbingAllowed_Info.label, new Property::Checkbox(p), to_string(s->pieceClimbingAllowed))->SetToolTip(s->pieceClimbingAllowed_Info.tip);
			n++; p->Add(s->flip180Allowed_Info.label, new Property::Checkbox(p), to_string(s->flip180Allowed))->SetToolTip(s->flip180Allowed_Info.tip);
			n++; p->Add(s->floorKickAllowed_Info.label, new Property::Checkbox(p), to_string(s->floorKickAllowed))->SetToolTip(s->floorKickAllowed_Info.tip);

			p->SetSplitWidth(400);
		}


		n++; p = settingsPropTree->Add("VS Rules Settings");
		{
			Property::ComboBox* vsGarbageRuleCombo = new Property::ComboBox(p);
			{
				vsGarbageRuleCombo->GetComboBox()->AddItem(L"Fall from ceiling in even rows", to_string((int)VSGarbageRule::FALL_FROM_CEILING_IN_EVEN_ROWS));
				vsGarbageRuleCombo->GetComboBox()->AddItem(L"Rise from floor in even rows", to_string((int)VSGarbageRule::RISE_FROM_FLOOR_IN_EVEN_ROWS));
				n++; p->Add(s->vsGarbageRule_Info.label, vsGarbageRuleCombo, to_string((int)s->vsGarbageRule))->SetToolTip(s->vsGarbageRule_Info.tip);
				//pRow->onChange.Add(this, &LevelSelectMenuControl::OnFirstNameChanged);
			}

			p->SetSplitWidth(400);
		}


		n++; p = settingsPropTree->Add("Grid Settings");
		{
			n++; p->Add(s->gridWidth_Info.label, to_string(s->gridWidth))->SetToolTip(s->gridWidth_Info.tip);
			n++; p->Add(s->gridHeight_Info.label, to_string(s->gridHeight))->SetToolTip(s->gridHeight_Info.tip);

			n++; p->Add(s->gridPixelsBetweenRows_Info.label, to_string(s->gridPixelsBetweenRows))->SetToolTip(s->gridPixelsBetweenRows_Info.tip);
			n++; p->Add(s->gridPixelsBetweenColumns_Info.label, to_string(s->gridPixelsBetweenColumns))->SetToolTip(s->gridPixelsBetweenColumns_Info.tip);

			Property::ComboBox* gameModeCombo = new Property::ComboBox(p);
			{
				gameModeCombo->GetComboBox()->AddItem(L"Drop (Falling block)", to_string((int)GameMode::DROP));
				gameModeCombo->GetComboBox()->AddItem(L"Stack (Rise from floor)", to_string((int)GameMode::STACK));
				n++; p->Add(s->gameMode_Info.label, gameModeCombo, to_string((int)s->gameMode))->SetToolTip(s->gameMode_Info.tip);
				//pRow->onChange.Add(this, &LevelSelectMenuControl::OnFirstNameChanged);
			}

			n++; p->Add(s->randomlyFillGrid_Info.label, new Property::Checkbox(p), to_string(s->randomlyFillGrid))->SetToolTip(s->randomlyFillGrid_Info.tip);
			//n++; p->Add(s->randomlyFillGridAmount_Info.label, to_string(s->randomlyFillGridAmount))->SetToolTip(s->randomlyFillGridAmount_Info.tip);
			n++; p->Add(s->randomlyFillGridStartY_Info.label, to_string(s->randomlyFillGridStartY))->SetToolTip(s->randomlyFillGridStartY_Info.tip);

			//n++; p->Add(s->stackRiseGame_Info.label, new Property::Checkbox(p), to_string(s->stackRiseGame))->SetToolTip(s->stackRiseGame_Info.tip);
			n++; p->Add(s->stackDontPutSameColorNextToEachOther_Info.label, new Property::Checkbox(p), to_string(s->stackDontPutSameColorNextToEachOther))->SetToolTip(s->stackDontPutSameColorNextToEachOther_Info.tip);
			n++; p->Add(s->stackDontPutSameBlockTypeNextToEachOther_Info.label, new Property::Checkbox(p), to_string(s->stackDontPutSameBlockTypeNextToEachOther))->SetToolTip(s->stackDontPutSameBlockTypeNextToEachOther_Info.tip);
			n++; p->Add(s->stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull_Info.label, new Property::Checkbox(p), to_string(s->stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull))->SetToolTip(s->stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull_Info.tip);
			n++; p->Add(s->stackLeaveAtLeastOneGapPerRow_Info.label, new Property::Checkbox(p), to_string(s->stackLeaveAtLeastOneGapPerRow))->SetToolTip(s->stackLeaveAtLeastOneGapPerRow_Info.tip);

			n++; p->Add(s->randomlyFillStack_Info.label, new Property::Checkbox(p), to_string(s->randomlyFillStack))->SetToolTip(s->randomlyFillStack_Info.tip);
			//n++; p->Add(s->randomlyFillStackAmount_Info.label, to_string(s->randomlyFillStackAmount))->SetToolTip(s->randomlyFillStackAmount_Info.tip);
			n++; p->Add(s->randomlyFillStackStartY_Info.label, to_string(s->randomlyFillStackStartY))->SetToolTip(s->randomlyFillStackStartY_Info.tip);

			//n++; p->Add(s->useCurrentPieceAsCursor_Info.label, new Property::Checkbox(p), to_string(s->useCurrentPieceAsCursor))->SetToolTip(s->useCurrentPieceAsCursor_Info.tip);
			//n++; p->Add(s->makeNewPiece_Info.label, new Property::Checkbox(p), to_string(s->makeNewPiece))->SetToolTip(s->makeNewPiece_Info.tip);
			//n++; p->Add(s->makeCursorPiece_Info.label, new Property::Checkbox(p), to_string(s->makeCursorPiece))->SetToolTip(s->makeCursorPiece_Info.tip);
			//n++; p->Add(s->cursorPieceSize_Info.label, to_string(s->cursorPieceSize))->SetToolTip(s->cursorPieceSize_Info.tip);

			Property::ComboBox* cursorTypeCombo = new Property::ComboBox(p);
			{
				cursorTypeCombo->GetComboBox()->AddItem(L"One block pick up", to_string((int)::CursorType::ONE_BLOCK_PICK_UP));
				cursorTypeCombo->GetComboBox()->AddItem(L"Two block horizontal swap", to_string((int)::CursorType::TWO_BLOCK_HORIZONTAL));
				cursorTypeCombo->GetComboBox()->AddItem(L"Two block vertical swap", to_string((int)::CursorType::TWO_BLOCK_VERTICAL));
				cursorTypeCombo->GetComboBox()->AddItem(L"Three block horizontal swap", to_string((int)::CursorType::THREE_BLOCK_HORIZONTAL));
				cursorTypeCombo->GetComboBox()->AddItem(L"Three block vertical swap", to_string((int)::CursorType::THREE_BLOCK_VERTICAL));
				cursorTypeCombo->GetComboBox()->AddItem(L"Quad block rotate", to_string((int)::CursorType::QUAD_BLOCK_ROTATE));
				n++; p->Add(s->stackCursorType_Info.label, cursorTypeCombo, to_string((int)s->stackCursorType))->SetToolTip(s->stackCursorType_Info.tip);
				//pRow->onChange.Add(this, &LevelSelectMenuControl::OnFirstNameChanged);
			}

			p->SetSplitWidth(400);
		}


		n++; p = settingsPropTree->Add("Block Settings");
		{
			//n++; p->Add(s->whenGeneratingBlockDontGetBlockColorThatIsntOnGrid_Info.label, new Property::Checkbox(p), to_string(s->whenGeneratingBlockDontGetBlockColorThatIsntOnGrid))->SetToolTip(s->whenGeneratingBlockDontGetBlockColorThatIsntOnGrid_Info.tip);

			//n++; p->Add(s->blockRule_drawDotToSquareOffBlockCorners_Info.label, new Property::Checkbox(p), to_string(s->blockRule_drawDotToSquareOffBlockCorners))->SetToolTip(s->blockRule_drawDotToSquareOffBlockCorners_Info.tip);
			//n++; p->Add(s->drawDotOnCenterOfRotation_Info.label, new Property::Checkbox(p), to_string(s->drawDotOnCenterOfRotation))->SetToolTip(s->drawDotOnCenterOfRotation_Info.tip);
			n++; p->Add(s->gridRule_outlineOpenBlockEdges_Info.label, new Property::Checkbox(p), to_string(s->gridRule_outlineOpenBlockEdges))->SetToolTip(s->gridRule_outlineOpenBlockEdges_Info.tip);
			n++; p->Add(s->fadeBlocksDarkerWhenLocking_Info.label, new Property::Checkbox(p), to_string(s->fadeBlocksDarkerWhenLocking))->SetToolTip(s->fadeBlocksDarkerWhenLocking_Info.tip);
			n++; p->Add(s->blockRule_drawBlocksDarkerWhenLocked_Info.label, new Property::Checkbox(p), to_string(s->blockRule_drawBlocksDarkerWhenLocked))->SetToolTip(s->blockRule_drawBlocksDarkerWhenLocked_Info.tip);
			n++; p->Add(s->blockRule_fillSolidSquareWhenSetInGrid_Info.label, new Property::Checkbox(p), to_string(s->blockRule_fillSolidSquareWhenSetInGrid))->SetToolTip(s->blockRule_fillSolidSquareWhenSetInGrid_Info.tip);

			n++; p->Add(s->blockRule_drawBlocksConnectedByPieceIgnoringColor_Info.label, new Property::Checkbox(p), to_string(s->blockRule_drawBlocksConnectedByPieceIgnoringColor))->SetToolTip(s->blockRule_drawBlocksConnectedByPieceIgnoringColor_Info.tip);
			n++; p->Add(s->blockRule_drawBlocksConnectedByColorIgnoringPiece_Info.label, new Property::Checkbox(p), to_string(s->blockRule_drawBlocksConnectedByColorIgnoringPiece))->SetToolTip(s->blockRule_drawBlocksConnectedByColorIgnoringPiece_Info.tip);
			n++; p->Add(s->blockRule_drawBlocksConnectedByColorInPiece_Info.label, new Property::Checkbox(p), to_string(s->blockRule_drawBlocksConnectedByColorInPiece))->SetToolTip(s->blockRule_drawBlocksConnectedByColorInPiece_Info.tip);

			n++; p->Add(s->blockMovementInterpolationTicks_Info.label, to_string(s->blockMovementInterpolationTicks))->SetToolTip(s->blockMovementInterpolationTicks_Info.tip);
			n++; p->Add(s->blockAnimationTicksRandomUpToBetweenLoop_Info.label, to_string(s->blockAnimationTicksRandomUpToBetweenLoop))->SetToolTip(s->blockAnimationTicksRandomUpToBetweenLoop_Info.tip);

			p->SetSplitWidth(400);
		}


		n++; p = settingsPropTree->Add("Piece Settings");
		{

			n++; p->Add(s->whenGeneratingPieceDontMatchAllBlockColors_Info.label, new Property::Checkbox(p), to_string(s->whenGeneratingPieceDontMatchAllBlockColors))->SetToolTip(s->whenGeneratingPieceDontMatchAllBlockColors_Info.tip);
			n++; p->Add(s->whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor_Info.label, new Property::Checkbox(p), to_string(s->whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor))->SetToolTip(s->whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor_Info.tip);
			n++; p->Add(s->whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor_Info.label, new Property::Checkbox(p), to_string(s->whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor))->SetToolTip(s->whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor_Info.tip);

			//n++; p->Add(s->currentPieceRenderAsNormalPiece_Info.label, new Property::Checkbox(p), to_string(s->currentPieceRenderAsNormalPiece))->SetToolTip(s->currentPieceRenderAsNormalPiece_Info.tip);
			//n++; p->Add(s->drawCursorInsteadOfCurrentPiece_Info.label, new Property::Checkbox(p), to_string(s->drawCursorInsteadOfCurrentPiece))->SetToolTip(s->drawCursorInsteadOfCurrentPiece_Info.tip);
			n++; p->Add(s->currentPieceOutlineFirstBlockRegardlessOfPosition_Info.label, new Property::Checkbox(p), to_string(s->currentPieceOutlineFirstBlockRegardlessOfPosition))->SetToolTip(s->currentPieceOutlineFirstBlockRegardlessOfPosition_Info.tip);
			n++; p->Add(s->currentPieceRule_OutlineBlockAtZeroZero_Info.label, new Property::Checkbox(p), to_string(s->currentPieceRule_OutlineBlockAtZeroZero))->SetToolTip(s->currentPieceRule_OutlineBlockAtZeroZero_Info.tip);
			//n++; p->Add(s->currentPieceRenderHoldingBlock_Info.label, new Property::Checkbox(p), to_string(s->currentPieceRenderHoldingBlock))->SetToolTip(s->currentPieceRenderHoldingBlock_Info.tip);
			//n++; p->Add(s->currentPieceMoveUpHalfABlock_Info.label, new Property::Checkbox(p), to_string(s->currentPieceMoveUpHalfABlock))->SetToolTip(s->currentPieceMoveUpHalfABlock_Info.tip);

			n++; p->Add(s->currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty_Info.label, new Property::Checkbox(p), to_string(s->currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty))->SetToolTip(s->currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty_Info.tip);


			p->SetSplitWidth(400);
		}


		n++; p = settingsPropTree->Add("Timing and Difficulty Settings");
		{
			n++; p->Add(s->maxLockDelayTicks_Info.label, to_string(s->maxLockDelayTicks))->SetToolTip(s->maxLockDelayTicks_Info.tip);
			n++; p->Add(s->spawnDelayTicksAmountPerPiece_Info.label, to_string(s->spawnDelayTicksAmountPerPiece))->SetToolTip(s->spawnDelayTicksAmountPerPiece_Info.tip);
			n++; p->Add(s->lineClearDelayTicksAmountPerLine_Info.label, to_string(s->lineClearDelayTicksAmountPerLine))->SetToolTip(s->lineClearDelayTicksAmountPerLine_Info.tip);
			n++; p->Add(s->lineClearDelayTicksAmountPerBlock_Info.label, to_string(s->lineClearDelayTicksAmountPerBlock))->SetToolTip(s->lineClearDelayTicksAmountPerBlock_Info.tip);

			n++; p->Add(s->gravityRule_ticksToMoveDownBlocksOverBlankSpaces_Info.label, to_string(s->gravityRule_ticksToMoveDownBlocksOverBlankSpaces))->SetToolTip(s->gravityRule_ticksToMoveDownBlocksOverBlankSpaces_Info.tip);

			n++; p->Add(s->moveDownAllLinesOverBlankSpacesAtOnce_Info.label, new Property::Checkbox(p), to_string(s->moveDownAllLinesOverBlankSpacesAtOnce))->SetToolTip(s->moveDownAllLinesOverBlankSpacesAtOnce_Info.tip);

			n++; p->Add(s->removingBlocksDelayTicksBetweenEachBlock_Info.label, to_string(s->removingBlocksDelayTicksBetweenEachBlock))->SetToolTip(s->removingBlocksDelayTicksBetweenEachBlock_Info.tip);


			p->SetSplitWidth(400);
		}


		n++; p = settingsPropTree->Add("Render Settings");
		{
			n++; p->Add(s->bloomIntensity_Info.label, to_string(s->bloomIntensity))->SetToolTip(s->bloomIntensity_Info.tip);
			n++; p->Add(s->bloomTimes_Info.label, to_string(s->bloomTimes))->SetToolTip(s->bloomTimes_Info.tip);
			p->SetSplitWidth(400);
		}

		settingsPropTree->ExpandAll();
		settingsPropTree->SetHeight(n * fontHeight);
		settingsPropTreeNumChildren = n;

	}

}


void CustomGameEditorControl::saveSettingsPropTreeToCurrentGameType()
{//=========================================================================================================================

	if (currentGameType == nullptr)return;

	//parse all fields
	//if name equals any other blocktype names besides currentBlockType add a number afterwards until it doesnt
	Properties* p = settingsPropTree->Find("Game Rules");
	if (p == nullptr)
	{
		BobsGame::log.error("Could not find Settings Properties");
		return;
	}

	GameType defaultGameType;

	PropertyRow* pr = p->Find(currentGameType->name_Info.label);
	string gameTypeName = pr->GetProperty()->GetPropertyValue().c_str();

	while (gameTypeName.find("`") != string::npos)
	{
		string s = gameTypeName.substr(0, gameTypeName.find("`"));
		gameTypeName = gameTypeName.substr(gameTypeName.find("`") + 1);
		s += gameTypeName;
	}
	if (gameTypeName == "")gameTypeName = "Unnamed Game";
	int n = 0;
	for (int i = 0; i<bobsGame->loadedGameTypes.size(); i++)
	{
		GameType *s = bobsGame->loadedGameTypes.get(i);
		if (s != currentGameType && s->name == gameTypeName)
		{
			gameTypeName = gameTypeName + to_string(n);
			n++;
			i = 0;
		}
	}


	//replace name in blockType
	currentGameType->name = gameTypeName;

	//parse the rest of the fields


	/*
	currentGameType->stringItem = p->Find("stringItem")->GetProperty()->GetPropertyValue().c_str();
	currentGameType->boolItem = 0 != stoi(p->Find("boolItem")->GetProperty()->GetPropertyValue().c_str());
	try {
		currentGameType->intItem = stoi(p->Find("intItem")->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->intItem = defaultSettings.intItem; }
	*/

	currentGameType->rules = p->Find(currentGameType->rules_Info.label)->GetProperty()->GetPropertyValue().c_str();

	try {
		currentGameType->scoreType = (ScoreType)stoi(p->Find(currentGameType->scoreType_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->scoreType = defaultGameType.scoreType; }

	try {
		currentGameType->scoreTypeAmountPerLevelGained = stoi(p->Find(currentGameType->scoreTypeAmountPerLevelGained_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->scoreTypeAmountPerLevelGained = defaultGameType.scoreTypeAmountPerLevelGained; }

	currentGameType->nextPieceEnabled = 0 != stoi(p->Find(currentGameType->nextPieceEnabled_Info.label)->GetProperty()->GetPropertyValue().c_str());

	try {
		currentGameType->numberOfNextPiecesToShow = stoi(p->Find(currentGameType->numberOfNextPiecesToShow_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->numberOfNextPiecesToShow = defaultGameType.numberOfNextPiecesToShow; }

	currentGameType->holdPieceEnabled = 0 != stoi(p->Find(currentGameType->holdPieceEnabled_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->resetHoldPieceRotation = 0 != stoi(p->Find(currentGameType->resetHoldPieceRotation_Info.label)->GetProperty()->GetPropertyValue().c_str());

	try {
		currentGameType->chainRule_AmountPerChain = stoi(p->Find(currentGameType->chainRule_AmountPerChain_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->chainRule_AmountPerChain = defaultGameType.chainRule_AmountPerChain; }

	currentGameType->chainRule_CheckEntireLine = 0 != stoi(p->Find(currentGameType->chainRule_CheckEntireLine_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->chainRule_CheckRow = 0 != stoi(p->Find(currentGameType->chainRule_CheckRow_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->chainRule_CheckColumn = 0 != stoi(p->Find(currentGameType->chainRule_CheckColumn_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->chainRule_CheckDiagonal = 0 != stoi(p->Find(currentGameType->chainRule_CheckDiagonal_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->chainRule_CheckRecursiveConnections = 0 != stoi(p->Find(currentGameType->chainRule_CheckRecursiveConnections_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->chainRule_CheckTouchingBreakerBlocksChain = 0 != stoi(p->Find(currentGameType->chainRule_CheckTouchingBreakerBlocksChain_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->gravityRule_onlyMoveDownDisconnectedBlocks = 0 != stoi(p->Find(currentGameType->gravityRule_onlyMoveDownDisconnectedBlocks_Info.label)->GetProperty()->GetPropertyValue().c_str());

	try {
		currentGameType->playingFieldGarbageType = (GarbageType)stoi(p->Find(currentGameType->playingFieldGarbageType_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->playingFieldGarbageType = defaultGameType.playingFieldGarbageType; }

	try {
		currentGameType->playingFieldGarbageSpawnRule = (GarbageSpawnRule)stoi(p->Find(currentGameType->playingFieldGarbageSpawnRule_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->playingFieldGarbageSpawnRule = defaultGameType.playingFieldGarbageSpawnRule; }

//	try {
//		currentGameType->playingFieldGarbageSpawnRuleAmount = stoi(p->Find(currentGameType->playingFieldGarbageSpawnRuleAmount_Info.label)->GetProperty()->GetPropertyValue().c_str());
//	}
//	catch (exception) { currentGameType->playingFieldGarbageSpawnRuleAmount = defaultSettings.playingFieldGarbageSpawnRuleAmount; }

	currentGameType->hardDropPunchThroughToLowestValidGridPosition = 0 != stoi(p->Find(currentGameType->hardDropPunchThroughToLowestValidGridPosition_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->twoSpaceWallKickAllowed = 0 != stoi(p->Find(currentGameType->twoSpaceWallKickAllowed_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->diagonalWallKickAllowed = 0 != stoi(p->Find(currentGameType->diagonalWallKickAllowed_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->pieceClimbingAllowed = 0 != stoi(p->Find(currentGameType->pieceClimbingAllowed_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->flip180Allowed = 0 != stoi(p->Find(currentGameType->flip180Allowed_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->floorKickAllowed = 0 != stoi(p->Find(currentGameType->floorKickAllowed_Info.label)->GetProperty()->GetPropertyValue().c_str());

	p = settingsPropTree->Find("VS Rules Settings");

	try {
		currentGameType->vsGarbageRule = (VSGarbageRule)stoi(p->Find(currentGameType->vsGarbageRule_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->vsGarbageRule = defaultGameType.vsGarbageRule; }

	p = settingsPropTree->Find("Grid Settings");

	try {
		currentGameType->gridWidth = stoi(p->Find(currentGameType->gridWidth_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->gridWidth = defaultGameType.gridWidth; }

	try {
		currentGameType->gridHeight = stoi(p->Find(currentGameType->gridHeight_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->gridHeight = defaultGameType.gridHeight; }

	if (currentGameType->gridWidth < 4)currentGameType->gridWidth = 4;
	if (currentGameType->gridHeight < 4)currentGameType->gridHeight = 4;

	try {
		currentGameType->gridPixelsBetweenRows = stoi(p->Find(currentGameType->gridPixelsBetweenRows_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->gridPixelsBetweenRows = defaultGameType.gridPixelsBetweenRows; }

	try {
		currentGameType->gridPixelsBetweenColumns = stoi(p->Find(currentGameType->gridPixelsBetweenColumns_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->gridPixelsBetweenColumns = defaultGameType.gridPixelsBetweenColumns; }

	currentGameType->randomlyFillGrid = 0 != stoi(p->Find(currentGameType->randomlyFillGrid_Info.label)->GetProperty()->GetPropertyValue().c_str());


	try {
		currentGameType->gameMode = (GameMode)stoi(p->Find(currentGameType->gameMode_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->gameMode = defaultGameType.gameMode; }


//	try {
//		currentGameType->randomlyFillGridAmount = stoi(p->Find(currentGameType->randomlyFillGridAmount_Info.label)->GetProperty()->GetPropertyValue().c_str());
//	}
//	catch (exception) { currentGameType->randomlyFillGridAmount = defaultSettings.randomlyFillGridAmount; }

	try {
		currentGameType->randomlyFillGridStartY = stoi(p->Find(currentGameType->randomlyFillGridStartY_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->randomlyFillGridStartY = defaultGameType.randomlyFillGridStartY; }


	//currentGameType->stackRiseGame = 0 != stoi(p->Find(currentGameType->stackRiseGame_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->stackDontPutSameColorNextToEachOther = 0 != stoi(p->Find(currentGameType->stackDontPutSameColorNextToEachOther_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->stackDontPutSameBlockTypeNextToEachOther = 0 != stoi(p->Find(currentGameType->stackDontPutSameBlockTypeNextToEachOther_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull = 0 != stoi(p->Find(currentGameType->stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->stackLeaveAtLeastOneGapPerRow = 0 != stoi(p->Find(currentGameType->stackLeaveAtLeastOneGapPerRow_Info.label)->GetProperty()->GetPropertyValue().c_str());

	currentGameType->randomlyFillStack = 0 != stoi(p->Find(currentGameType->randomlyFillStack_Info.label)->GetProperty()->GetPropertyValue().c_str());

//	try {
//		currentGameType->randomlyFillStackAmount = stoi(p->Find(currentGameType->randomlyFillStackAmount_Info.label)->GetProperty()->GetPropertyValue().c_str());
//	}
//	catch (exception) { currentGameType->randomlyFillStackAmount = defaultSettings.randomlyFillStackAmount; }

	try {
		currentGameType->randomlyFillStackStartY = stoi(p->Find(currentGameType->randomlyFillStackStartY_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->randomlyFillStackStartY = defaultGameType.randomlyFillStackStartY; }

	//currentGameType->useCurrentPieceAsCursor = 0 != stoi(p->Find(currentGameType->useCurrentPieceAsCursor_Info.label)->GetProperty()->GetPropertyValue().c_str());
	//currentGameType->makeNewPiece = 0 != stoi(p->Find(currentGameType->makeNewPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());
	//currentGameType->makeCursorPiece = 0 != stoi(p->Find(currentGameType->makeCursorPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());

	//try {
		//currentGameType->cursorPieceSize = stoi(p->Find(currentGameType->cursorPieceSize_Info.label)->GetProperty()->GetPropertyValue().c_str());
	//}
	//catch (exception) { currentGameType->cursorPieceSize = defaultSettings.cursorPieceSize; }

	try {
		currentGameType->stackCursorType = (::CursorType)stoi(p->Find(currentGameType->stackCursorType_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->stackCursorType = defaultGameType.stackCursorType; }

	p = settingsPropTree->Find("Block Settings");

	//currentGameType->whenGeneratingBlockDontGetBlockColorThatIsntOnGrid = 0 != stoi(p->Find(currentGameType->whenGeneratingBlockDontGetBlockColorThatIsntOnGrid_Info.label)->GetProperty()->GetPropertyValue().c_str());

	//currentGameType->blockRule_drawDotToSquareOffBlockCorners = 0 != stoi(p->Find(currentGameType->blockRule_drawDotToSquareOffBlockCorners_Info.label)->GetProperty()->GetPropertyValue().c_str());
	//currentGameType->drawDotOnCenterOfRotation = 0 != stoi(p->Find(currentGameType->drawDotOnCenterOfRotation_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->gridRule_outlineOpenBlockEdges = 0 != stoi(p->Find(currentGameType->gridRule_outlineOpenBlockEdges_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->fadeBlocksDarkerWhenLocking = 0 != stoi(p->Find(currentGameType->fadeBlocksDarkerWhenLocking_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->blockRule_drawBlocksDarkerWhenLocked = 0 != stoi(p->Find(currentGameType->blockRule_drawBlocksDarkerWhenLocked_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->blockRule_fillSolidSquareWhenSetInGrid = 0 != stoi(p->Find(currentGameType->blockRule_fillSolidSquareWhenSetInGrid_Info.label)->GetProperty()->GetPropertyValue().c_str());

	currentGameType->blockRule_drawBlocksConnectedByPieceIgnoringColor = 0 != stoi(p->Find(currentGameType->blockRule_drawBlocksConnectedByPieceIgnoringColor_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->blockRule_drawBlocksConnectedByColorIgnoringPiece = 0 != stoi(p->Find(currentGameType->blockRule_drawBlocksConnectedByColorIgnoringPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->blockRule_drawBlocksConnectedByColorInPiece = 0 != stoi(p->Find(currentGameType->blockRule_drawBlocksConnectedByColorInPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());

	try {
		currentGameType->blockMovementInterpolationTicks = stoi(p->Find(currentGameType->blockMovementInterpolationTicks_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->blockMovementInterpolationTicks = defaultGameType.blockMovementInterpolationTicks; }

	try {
		currentGameType->blockAnimationTicksRandomUpToBetweenLoop = stoi(p->Find(currentGameType->blockAnimationTicksRandomUpToBetweenLoop_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->blockAnimationTicksRandomUpToBetweenLoop = defaultGameType.blockAnimationTicksRandomUpToBetweenLoop; }

	p = settingsPropTree->Find("Piece Settings");

	currentGameType->whenGeneratingPieceDontMatchAllBlockColors = 0 != stoi(p->Find(currentGameType->whenGeneratingPieceDontMatchAllBlockColors_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor = 0 != stoi(p->Find(currentGameType->whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor = 0 != stoi(p->Find(currentGameType->whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor_Info.label)->GetProperty()->GetPropertyValue().c_str());

	//currentGameType->currentPieceRenderAsNormalPiece = 0 != stoi(p->Find(currentGameType->currentPieceRenderAsNormalPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());
	//currentGameType->drawCursorInsteadOfCurrentPiece = 0 != stoi(p->Find(currentGameType->drawCursorInsteadOfCurrentPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->currentPieceOutlineFirstBlockRegardlessOfPosition = 0 != stoi(p->Find(currentGameType->currentPieceOutlineFirstBlockRegardlessOfPosition_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->currentPieceRule_OutlineBlockAtZeroZero = 0 != stoi(p->Find(currentGameType->currentPieceRule_OutlineBlockAtZeroZero_Info.label)->GetProperty()->GetPropertyValue().c_str());
	//currentGameType->currentPieceRenderHoldingBlock = 0 != stoi(p->Find(currentGameType->currentPieceRenderHoldingBlock_Info.label)->GetProperty()->GetPropertyValue().c_str());
	//currentGameType->currentPieceMoveUpHalfABlock = 0 != stoi(p->Find(currentGameType->currentPieceMoveUpHalfABlock_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentGameType->currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty = 0 != stoi(p->Find(currentGameType->currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty_Info.label)->GetProperty()->GetPropertyValue().c_str());

	p = settingsPropTree->Find("Timing and Difficulty Settings");

	try {
		currentGameType->maxLockDelayTicks = stoi(p->Find(currentGameType->maxLockDelayTicks_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->maxLockDelayTicks = defaultGameType.maxLockDelayTicks; }

	try {
		currentGameType->spawnDelayTicksAmountPerPiece = stoi(p->Find(currentGameType->spawnDelayTicksAmountPerPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->spawnDelayTicksAmountPerPiece = defaultGameType.spawnDelayTicksAmountPerPiece; }

	try {
		currentGameType->lineClearDelayTicksAmountPerLine = stoi(p->Find(currentGameType->lineClearDelayTicksAmountPerLine_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->lineClearDelayTicksAmountPerLine = defaultGameType.lineClearDelayTicksAmountPerLine; }

	try {
		currentGameType->lineClearDelayTicksAmountPerBlock = stoi(p->Find(currentGameType->lineClearDelayTicksAmountPerBlock_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->lineClearDelayTicksAmountPerBlock = defaultGameType.lineClearDelayTicksAmountPerBlock; }

	try {
		currentGameType->gravityRule_ticksToMoveDownBlocksOverBlankSpaces = stoi(p->Find(currentGameType->gravityRule_ticksToMoveDownBlocksOverBlankSpaces_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->gravityRule_ticksToMoveDownBlocksOverBlankSpaces = defaultGameType.gravityRule_ticksToMoveDownBlocksOverBlankSpaces; }


	currentGameType->moveDownAllLinesOverBlankSpacesAtOnce = 0 != stoi(p->Find(currentGameType->moveDownAllLinesOverBlankSpacesAtOnce_Info.label)->GetProperty()->GetPropertyValue().c_str());

	try {
		currentGameType->removingBlocksDelayTicksBetweenEachBlock = stoi(p->Find(currentGameType->removingBlocksDelayTicksBetweenEachBlock_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->removingBlocksDelayTicksBetweenEachBlock = defaultGameType.removingBlocksDelayTicksBetweenEachBlock; }

	p = settingsPropTree->Find("Render Settings");

	try {
		currentGameType->bloomIntensity = stof(p->Find(currentGameType->bloomIntensity_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->bloomIntensity = defaultGameType.bloomIntensity; }

	try {
		currentGameType->bloomTimes = stoi(p->Find(currentGameType->bloomTimes_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentGameType->bloomTimes = defaultGameType.bloomTimes; }

}




void CustomGameEditorControl::initBlockPropTree(BlockType *b)
{//=========================================================================================================================
	if (blockPropTree != nullptr)
	{
		blockPropTree->DelayedDelete();
		GetCanvas()->DoThink();
		//delete blockPropTree;
		blockPropTree = nullptr;
	}

	if (b == nullptr)return;

	blockPropTree = new PropertyTree(blockPropertiesScrollControl);
	//blockPropTree->Dock(Pos::Fill);
	blockPropTree->SetWidth(400);
	//blockPropTree->SetHeight(1000);
	{


		int n = 0;

		Properties* p;
		n++; p = blockPropTree->Add("Block Properties");
		{
			n++; p->Add(b->name_Info.label, string(b->name))->SetToolTip(b->name_Info.tip);

			Property::ComboBox* spriteNameCombo = new Property::ComboBox(p);
			{
				spriteNameCombo->GetComboBox()->AddItem(Utility::StringToUnicode(""), "");
				for(int i=0;i<bobsGame->loadedSprites.size();i++)
				{
					Sprite *s = bobsGame->loadedSprites.get(i);
					spriteNameCombo->GetComboBox()->AddItem(Utility::StringToUnicode(s->getName()), s->getName());
				}

				n++; p->Add(b->spriteName_Info.label, spriteNameCombo, "1")->SetToolTip(b->spriteName_Info.tip);
				spriteNameCombo->GetComboBox()->SelectItemByName(b->spriteName);
			}

			Property::ComboBox* specialSpriteNameCombo = new Property::ComboBox(p);
			{
				specialSpriteNameCombo->GetComboBox()->AddItem(Utility::StringToUnicode(""),"");
				for (int i = 0; i<bobsGame->loadedSprites.size(); i++)
				{
					Sprite *s = bobsGame->loadedSprites.get(i);
					specialSpriteNameCombo->GetComboBox()->AddItem(Utility::StringToUnicode(s->getName()), s->getName());
				}

				n++; p->Add(b->specialSpriteName_Info.label, specialSpriteNameCombo, "1")->SetToolTip(b->specialSpriteName_Info.tip);
				specialSpriteNameCombo->GetComboBox()->SelectItemByName(b->specialSpriteName);
			}



			n++; p->Add(b->useInNormalPieces_Info.label, new Property::Checkbox(p), to_string(b->useInNormalPieces))->SetToolTip(b->useInNormalPieces_Info.tip);
			n++; p->Add(b->useAsGarbage_Info.label, new Property::Checkbox(p), to_string(b->useAsGarbage))->SetToolTip(b->useAsGarbage_Info.tip);
			n++; p->Add(b->useAsPlayingFieldFiller_Info.label, new Property::Checkbox(p), to_string(b->useAsPlayingFieldFiller))->SetToolTip(b->useAsPlayingFieldFiller_Info.tip);
			n++; p->Add(b->ignoreWhenMovingDownBlocks_Info.label, new Property::Checkbox(p), to_string(b->ignoreWhenMovingDownBlocks))->SetToolTip(b->ignoreWhenMovingDownBlocks_Info.tip);
			n++; p->Add(b->chainConnectionsMustContainAtLeastOneBlockWithThisTrue_Info.label, new Property::Checkbox(p), to_string(b->chainConnectionsMustContainAtLeastOneBlockWithThisTrue))->SetToolTip(b->chainConnectionsMustContainAtLeastOneBlockWithThisTrue_Info.tip);
			n++; p->Add(b->ignoreWhenCheckingChainConnections_Info.label, new Property::Checkbox(p), to_string(b->ignoreWhenCheckingChainConnections))->SetToolTip(b->ignoreWhenCheckingChainConnections_Info.tip);

			for (int i = 0; i < 11; i++)
			{
				Property::ComboBox* colorCombo = new Property::ComboBox(p);
				{
					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"lighterPurple", "lighterPurple");
					colorCombo->GetComboBox()->AddItem(L"lightPurple", "lightPurple");
					colorCombo->GetComboBox()->AddItem(L"purple", "purple");
					colorCombo->GetComboBox()->AddItem(L"darkPurple", "darkPurple");
					colorCombo->GetComboBox()->AddItem(L"darkerPurple", "darkerPurple");

					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"lighterBlue", "lighterBlue");
					colorCombo->GetComboBox()->AddItem(L"lightBlue", "lightBlue");
					colorCombo->GetComboBox()->AddItem(L"blue", "blue");
					colorCombo->GetComboBox()->AddItem(L"darkBlue", "darkBlue");
					colorCombo->GetComboBox()->AddItem(L"darkerBlue", "darkerBlue");

					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"lighterCyan", "lighterCyan");
					colorCombo->GetComboBox()->AddItem(L"cyan", "cyan");
					colorCombo->GetComboBox()->AddItem(L"darkerCyan", "darkerCyan");

					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"lighterAqua", "lighterAqua");
					colorCombo->GetComboBox()->AddItem(L"aqua", "aqua");
					colorCombo->GetComboBox()->AddItem(L"darkerAqua", "darkerAqua");

					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"lightGreen", "lightGreen");
					colorCombo->GetComboBox()->AddItem(L"lighterGreen", "lighterGreen");
					colorCombo->GetComboBox()->AddItem(L"green", "green");
					colorCombo->GetComboBox()->AddItem(L"darkGreen", "darkGreen");
					colorCombo->GetComboBox()->AddItem(L"darkerGreen", "darkerGreen");

					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"lighterOlive", "lighterOlive");
					colorCombo->GetComboBox()->AddItem(L"olive", "olive");
					colorCombo->GetComboBox()->AddItem(L"darkerOlive", "darkerOlive");

					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"lightYellow", "lightYellow");
					colorCombo->GetComboBox()->AddItem(L"yellow", "yellow");
					colorCombo->GetComboBox()->AddItem(L"darkerYellow", "darkerYellow");

					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"lighterOrange", "lighterOrange");
					colorCombo->GetComboBox()->AddItem(L"lightOrange", "lightOrange");
					colorCombo->GetComboBox()->AddItem(L"orange", "orange");
					colorCombo->GetComboBox()->AddItem(L"darkOrange", "darkOrange");
					colorCombo->GetComboBox()->AddItem(L"darkerOrange", "darkerOrange");

					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"lighterRed", "lighterRed");
					colorCombo->GetComboBox()->AddItem(L"red", "red");
					colorCombo->GetComboBox()->AddItem(L"darkerRed", "darkerRed");

					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"lighterMagenta", "lighterMagenta");
					colorCombo->GetComboBox()->AddItem(L"magenta", "magenta");
					colorCombo->GetComboBox()->AddItem(L"darkerMagenta", "darkerMagenta");

					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"lighterPink", "lighterPink");
					colorCombo->GetComboBox()->AddItem(L"pink", "pink");
					colorCombo->GetComboBox()->AddItem(L"darkerPink", "darkerPink");

					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"lighterGray", "lighterGray");
					colorCombo->GetComboBox()->AddItem(L"lightGray", "lightGray");
					colorCombo->GetComboBox()->AddItem(L"gray", "gray");
					colorCombo->GetComboBox()->AddItem(L"darkGray", "darkGray");
					colorCombo->GetComboBox()->AddItem(L"darkerGray", "darkerGray");

					colorCombo->GetComboBox()->AddItem(L"", "");

					colorCombo->GetComboBox()->AddItem(L"white", "white");
					colorCombo->GetComboBox()->AddItem(L"black", "black");
					

					if (i == 10)
					{
						n++; p->Add(b->specialColor_Info.label, colorCombo, "1")->SetToolTip(b->specialColor_Info.tip);
						if(b->specialColor!=nullptr)colorCombo->GetComboBox()->SelectItemByName(b->specialColor->name);
					}
					else
					{
						n++; p->Add("Color " + to_string(i), colorCombo, "1")->SetToolTip(b->colors_Info.tip);
						if (i < b->colors.size())
						{
							colorCombo->GetComboBox()->SelectItemByName(b->colors.get(i)->name);
						}
					}
				}
			}

			n++; p->Add(b->randomSpecialBlockChanceOneOutOf_Info.label, to_string(b->randomSpecialBlockChanceOneOutOf))->SetToolTip(b->randomSpecialBlockChanceOneOutOf_Info.tip);
			n++; p->Add(b->frequencySpecialBlockTypeOnceEveryNPieces_Info.label, to_string(b->frequencySpecialBlockTypeOnceEveryNPieces))->SetToolTip(b->frequencySpecialBlockTypeOnceEveryNPieces_Info.tip);

			n++; p->Add(b->flashingSpecialType_Info.label, new Property::Checkbox(p), to_string(b->flashingSpecialType))->SetToolTip(b->flashingSpecialType_Info.tip);
			n++; p->Add(b->turnBackToNormalBlockAfterNPiecesLock_Info.label, to_string(b->turnBackToNormalBlockAfterNPiecesLock))->SetToolTip(b->turnBackToNormalBlockAfterNPiecesLock_Info.tip);

			{
				string pieceTypesString = "";
				for (int i = 0; i < b->makePieceTypeWhenCleared_UUID.size(); i++)
				{
					PieceType *pt = currentGameType->getPieceTypeByUUID(b->makePieceTypeWhenCleared_UUID.get(i));
					string pieceName = "";
					if (pt != nullptr)pieceName = pt->name;
					else { pieceName = "ERROR"; bobsGame->log.error("Could not find PieceType in makePieceTypeWhenCleared"); }
					pieceTypesString = pieceTypesString + pieceName + ",";
				}
				Property::TextWithButton *tb = new Property::TextWithButton(p, "Edit");
				n++; p->Add(b->makePieceTypeWhenCleared_Info.label, tb, pieceTypesString)->SetToolTip(b->makePieceTypeWhenCleared_Info.tip);
				tb->GetButton()->onPress.Add(this, &CustomGameEditorControl::doEditMakePieceTypeWhenClearedWindowButton);
			}

			n++; p->Add(b->clearEveryOtherLineOnGridWhenCleared_Info.label, new Property::Checkbox(p), to_string(b->clearEveryOtherLineOnGridWhenCleared))->SetToolTip(b->clearEveryOtherLineOnGridWhenCleared_Info.tip);
			n++; p->Add(b->counterType_Info.label, new Property::Checkbox(p), to_string(b->counterType))->SetToolTip(b->counterType_Info.tip);
			n++; p->Add(b->pacmanType_Info.label, new Property::Checkbox(p), to_string(b->pacmanType))->SetToolTip(b->pacmanType_Info.tip);
			n++; p->Add(b->pacJarType_Info.label, new Property::Checkbox(p), to_string(b->pacJarType))->SetToolTip(b->pacJarType_Info.tip);
			n++; p->Add(b->ticksToChangeDirection_Info.label, to_string(b->ticksToChangeDirection))->SetToolTip(b->ticksToChangeDirection_Info.tip);

			{
				string blockTypesString = "";
				for (int i = 0; i < b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.size(); i++)
				{
					BlockType *bt = currentGameType->getBlockTypeByUUID(b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.get(i));
					string blockName = "";
					if(bt==nullptr)blockName = "ERROR";
					else blockName = bt->name;
					blockTypesString = blockTypesString + blockName + ",";
				}
				Property::TextWithButton *tb = new Property::TextWithButton(p, "Edit");
				n++; p->Add(b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_Info.label, tb, blockTypesString)->SetToolTip(b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_Info.tip);
				tb->GetButton()->onPress.Add(this, &CustomGameEditorControl::doEditConnectedUDLRChangeIntoBlockTypeWindowButton);
			}

			n++; p->Add(b->addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks_Info.label, new Property::Checkbox(p), to_string(b->addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks))->SetToolTip(b->addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks_Info.tip);

			{
				string blockTypesString = "";
				for (int i = 0; i < b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); i++)
				{
					TurnFromBlockTypeToType *bt = b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(i);
					blockTypesString = blockTypesString + bt->getName(currentGameType) + ",";
				}
				Property::TextWithButton *tb = new Property::TextWithButton(p, "Edit");
				n++; p->Add(b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut_Info.label, tb, blockTypesString)->SetToolTip(b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut_Info.tip);
				tb->GetButton()->onPress.Add(this, &CustomGameEditorControl::doEditTurnFromBlockTypeToTypeWindowButton);
			}

			n++; p->Add(b->removeAllBlocksOfColorOnFieldBlockIsSetOn_Info.label, new Property::Checkbox(p), to_string(b->removeAllBlocksOfColorOnFieldBlockIsSetOn))->SetToolTip(b->removeAllBlocksOfColorOnFieldBlockIsSetOn_Info.tip);
			n++; p->Add(b->changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor_Info.label, new Property::Checkbox(p), to_string(b->changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor))->SetToolTip(b->changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor_Info.tip);
			n++; p->Add(b->matchAnyColor_Info.label, new Property::Checkbox(p), to_string(b->matchAnyColor))->SetToolTip(b->matchAnyColor_Info.tip);



			p->SetSplitWidth(200);
		}
//
//		currentBlockType_makePieceTypeWhenCleared.clear();
//		for(int i=0;i<b->makePieceTypeWhenCleared.size();i++)
//		{
//			PieceType *pt = b->makePieceTypeWhenCleared.get(i);
//			currentBlockType_makePieceTypeWhenCleared.add(pt);
//		}
//
//		currentBlockType_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType.clear();
//		for (int i = 0; i<b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType.size(); i++)
//		{
//			BlockType *pt = b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType.get(i);
//			currentBlockType_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType.add(pt);
//		}
//
//		currentBlockType_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.clear();
//		for (int i = 0; i<b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); i++)
//		{
//			TurnFromBlockTypeToType *pt = b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(i);
//			currentBlockType_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.add(pt);
//		}

		blockPropTree->ExpandAll();

		blockPropTree->SetHeight(n * fontHeight);
		blockPropTreeNumChildren = n;
	}

}


void CustomGameEditorControl::saveBlockPropTreeToCurrentBlockType()
{//=========================================================================================================================

	if (currentBlockType == nullptr)return;
	if (blockPropTree == nullptr)return;

	//parse all fields
	//if name equals any other blocktype names besides currentBlockType add a number afterwards until it doesnt
	Properties* p = blockPropTree->Find("Block Properties");
	if (p == nullptr)
	{
		BobsGame::log.error("Could not find Block Properties");
		return;
	}

	BlockType defaultBlockType;

	PropertyRow* pr = p->Find(currentBlockType->name_Info.label);
	//	BobsGame::log.debug("GetLabel"+string(pr->GetLabel()->GetText().c_str()));
	//	BobsGame::log.debug("GetName"+ pr->GetName());
	//	BobsGame::log.debug("GetValue"+ string(pr->GetValue().c_str()));
	//	BobsGame::log.debug("GetTypeName"+ string(pr->GetTypeName()));
	//	Property::Base *prop = pr->GetProperty();
	//	
	//	BobsGame::log.debug("GetPropertyValue" + string(prop->GetPropertyValue().c_str()));
	//	BobsGame::log.debug("GetName" + prop->GetName());
	//	BobsGame::log.debug("GetValue" + string(prop->GetValue().c_str()));
	//	BobsGame::log.debug("GetTypeName" + string(prop->GetTypeName()));


	string newName = pr->GetProperty()->GetPropertyValue().c_str();
	if (newName == "")newName = "Unnamed Block";

	{
		int n = 0;
		for (int i = 0; i < currentGameType->blockTypes.size(); i++)
		{
			BlockType *bt = currentGameType->blockTypes.get(i);
			if (bt != currentBlockType && bt->name == newName)
			{
				newName = newName + to_string(n);
				n++;
				i = 0;
			}
		}
	}

	string oldName = currentBlockType->name;
	//replace name in blockType
	currentBlockType->name = newName;

	//replace name in blockTypelist
	for (int i = 0; i<currentGameType->blockTypes.size(); i++)
	{
		BlockType *bt = currentGameType->blockTypes.get(i);
		if (bt == currentBlockType)
		{
			blockSelectionListBox->GetTable()->GetRow(i)->SetCellText(0, newName);
		}
	}


	//parse the rest of the fields
	currentBlockType->spriteName = p->Find(currentBlockType->spriteName_Info.label)->GetProperty()->GetPropertyValue().c_str();
	currentBlockType->sprite = nullptr;
	currentBlockType->specialSpriteName = p->Find(currentBlockType->specialSpriteName_Info.label)->GetProperty()->GetPropertyValue().c_str();
	currentBlockType->specialSprite = nullptr;
	currentBlockType->useInNormalPieces = 0!=stoi(p->Find(currentBlockType->useInNormalPieces_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentBlockType->useAsGarbage = 0 != stoi(p->Find(currentBlockType->useAsGarbage_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentBlockType->useAsPlayingFieldFiller = 0 != stoi(p->Find(currentBlockType->useAsPlayingFieldFiller_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentBlockType->ignoreWhenMovingDownBlocks = 0 != stoi(p->Find(currentBlockType->ignoreWhenMovingDownBlocks_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentBlockType->chainConnectionsMustContainAtLeastOneBlockWithThisTrue = 0 != stoi(p->Find(currentBlockType->chainConnectionsMustContainAtLeastOneBlockWithThisTrue_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentBlockType->ignoreWhenCheckingChainConnections = 0 != stoi(p->Find(currentBlockType->ignoreWhenCheckingChainConnections_Info.label)->GetProperty()->GetPropertyValue().c_str());

	currentBlockType->colors.clear();
	for (int i = 0; i < 11; i++)
	{
		string colorName = "";

		if (i == 10)
		{
			colorName = p->Find(currentBlockType->specialColor_Info.label)->GetProperty()->GetPropertyValue().c_str();
			currentBlockType->specialColor = BobColor::getColorByName(colorName);
		}
		else
		{
			colorName = p->Find("Color " + to_string(i))->GetProperty()->GetPropertyValue().c_str();
			if (colorName != "")currentBlockType->colors.add(BobColor::getColorByName(colorName));
		}
	}

	try {currentBlockType->randomSpecialBlockChanceOneOutOf = stoi(p->Find(currentBlockType->randomSpecialBlockChanceOneOutOf_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}catch (exception) { currentBlockType->randomSpecialBlockChanceOneOutOf = defaultBlockType.randomSpecialBlockChanceOneOutOf; }

	try {
		currentBlockType->frequencySpecialBlockTypeOnceEveryNPieces = stoi(p->Find(currentBlockType->frequencySpecialBlockTypeOnceEveryNPieces_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentBlockType->frequencySpecialBlockTypeOnceEveryNPieces = defaultBlockType.frequencySpecialBlockTypeOnceEveryNPieces; }


	currentBlockType->flashingSpecialType = 0 != stoi(p->Find(currentBlockType->flashingSpecialType_Info.label)->GetProperty()->GetPropertyValue().c_str());

	try {
		currentBlockType->turnBackToNormalBlockAfterNPiecesLock = stoi(p->Find(currentBlockType->turnBackToNormalBlockAfterNPiecesLock_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentBlockType->turnBackToNormalBlockAfterNPiecesLock = defaultBlockType.turnBackToNormalBlockAfterNPiecesLock; }


//	currentBlockType->makePieceTypeWhenCleared.clear();
//	{
//		for (int i = 0; i<currentBlockType_makePieceTypeWhenCleared.size(); i++)
//		{
//			PieceType *pt = currentBlockType_makePieceTypeWhenCleared.get(i);
//			currentBlockType->makePieceTypeWhenCleared.add(pt);
//		}
//	}
	

	currentBlockType->clearEveryOtherLineOnGridWhenCleared = 0 != stoi(p->Find(currentBlockType->clearEveryOtherLineOnGridWhenCleared_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentBlockType->counterType = 0 != stoi(p->Find(currentBlockType->counterType_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentBlockType->pacmanType = 0 != stoi(p->Find(currentBlockType->pacmanType_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentBlockType->pacJarType = 0 != stoi(p->Find(currentBlockType->pacJarType_Info.label)->GetProperty()->GetPropertyValue().c_str());

	try { currentBlockType->ticksToChangeDirection = stoi(p->Find(currentBlockType->ticksToChangeDirection_Info.label)->GetProperty()->GetPropertyValue().c_str()); }
	catch (exception) { currentBlockType->ticksToChangeDirection = defaultBlockType.ticksToChangeDirection; }

//	currentBlockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType.clear();
//	for (int i = 0; i<currentBlockType_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType.size(); i++)
//	{
//		BlockType *pt = currentBlockType_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType.get(i);
//		currentBlockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType.add(pt);
//	}

	currentBlockType->addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks = 0 != stoi(p->Find(currentBlockType->addToChainIfConnectedUpDownLeftRightToExplodingChainBlocks_Info.label)->GetProperty()->GetPropertyValue().c_str());



//	currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.clear();
//	for (int i = 0; i<currentBlockType_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); i++)
//	{
//		TurnFromBlockTypeToType *pt = currentBlockType_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(i);
//		currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.add(pt);
//	}

	currentBlockType->removeAllBlocksOfColorOnFieldBlockIsSetOn = 0 != stoi(p->Find(currentBlockType->removeAllBlocksOfColorOnFieldBlockIsSetOn_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentBlockType->changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor = 0 != stoi(p->Find(currentBlockType->changeAllBlocksOfColorOnFieldBlockIsSetOnToDiamondColor_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentBlockType->matchAnyColor = 0 != stoi(p->Find(currentBlockType->matchAnyColor_Info.label)->GetProperty()->GetPropertyValue().c_str());


}


void CustomGameEditorControl::onPieceListRowSelect(Base* control)
{//=========================================================================================================================

	if (control == nullptr)return;

	//if a piecetype is currently selected, save it to the piecetype
	if (currentPieceType != nullptr)
	{
		//save block props to current block type in case current block was edited and is included in this piece
		saveBlockPropTreeToCurrentBlockType();

		savePiecePropTreeToCurrentPieceType();
	}

	Layout::TableRow* row = (Layout::TableRow*)control;
	string uuid = row->GetName().c_str();

	PieceType *bt = getPieceTypeByUUID(uuid);

	if (bt == nullptr)
	{
		BobsGame::log.error("Could not find piecetype with uuid:" + uuid);
		return;
	}
	currentPieceType = bt;
	//populate all the piecetype fields
	initPiecePropTree(bt);
}

void CustomGameEditorControl::initPiecePropTree(PieceType *b)
{//=========================================================================================================================
	if (piecePropTree != nullptr)
	{
		piecePropTree->DelayedDelete();
		GetCanvas()->DoThink();
		//delete piecePropTree;
		piecePropTree = nullptr;
	}

	if (b == nullptr)return;

	piecePropTree = new PropertyTree(piecePropertiesScrollControl);
	//piecePropTree->Dock(Pos::Fill);
	piecePropTree->SetWidth(400);
	//piecePropTree->SetHeight(1000);
	{

		int n = 0;
		Properties* p;
		n++; p = piecePropTree->Add("Piece Properties");
		{
			n++; p->Add(b->name_Info.label, string(b->name))->SetToolTip(b->name_Info.tip);


			Property::ComboBox* colorCombo = new Property::ComboBox(p);
			{
				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"lighterPurple", "lighterPurple");
				colorCombo->GetComboBox()->AddItem(L"lightPurple", "lightPurple");
				colorCombo->GetComboBox()->AddItem(L"purple", "purple");
				colorCombo->GetComboBox()->AddItem(L"darkPurple", "darkPurple");
				colorCombo->GetComboBox()->AddItem(L"darkerPurple", "darkerPurple");

				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"lighterBlue", "lighterBlue");
				colorCombo->GetComboBox()->AddItem(L"lightBlue", "lightBlue");
				colorCombo->GetComboBox()->AddItem(L"blue", "blue");
				colorCombo->GetComboBox()->AddItem(L"darkBlue", "darkBlue");
				colorCombo->GetComboBox()->AddItem(L"darkerBlue", "darkerBlue");

				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"lighterCyan", "lighterCyan");
				colorCombo->GetComboBox()->AddItem(L"cyan", "cyan");
				colorCombo->GetComboBox()->AddItem(L"darkerCyan", "darkerCyan");

				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"lighterAqua", "lighterAqua");
				colorCombo->GetComboBox()->AddItem(L"aqua", "aqua");
				colorCombo->GetComboBox()->AddItem(L"darkerAqua", "darkerAqua");

				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"lightGreen", "lightGreen");
				colorCombo->GetComboBox()->AddItem(L"lighterGreen", "lighterGreen");
				colorCombo->GetComboBox()->AddItem(L"green", "green");
				colorCombo->GetComboBox()->AddItem(L"darkGreen", "darkGreen");
				colorCombo->GetComboBox()->AddItem(L"darkerGreen", "darkerGreen");

				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"lighterOlive", "lighterOlive");
				colorCombo->GetComboBox()->AddItem(L"olive", "olive");
				colorCombo->GetComboBox()->AddItem(L"darkerOlive", "darkerOlive");

				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"lightYellow", "lightYellow");
				colorCombo->GetComboBox()->AddItem(L"yellow", "yellow");
				colorCombo->GetComboBox()->AddItem(L"darkerYellow", "darkerYellow");

				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"lighterOrange", "lighterOrange");
				colorCombo->GetComboBox()->AddItem(L"lightOrange", "lightOrange");
				colorCombo->GetComboBox()->AddItem(L"orange", "orange");
				colorCombo->GetComboBox()->AddItem(L"darkOrange", "darkOrange");
				colorCombo->GetComboBox()->AddItem(L"darkerOrange", "darkerOrange");

				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"lighterRed", "lighterRed");
				colorCombo->GetComboBox()->AddItem(L"red", "red");
				colorCombo->GetComboBox()->AddItem(L"darkerRed", "darkerRed");

				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"lighterMagenta", "lighterMagenta");
				colorCombo->GetComboBox()->AddItem(L"magenta", "magenta");
				colorCombo->GetComboBox()->AddItem(L"darkerMagenta", "darkerMagenta");

				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"lighterPink", "lighterPink");
				colorCombo->GetComboBox()->AddItem(L"pink", "pink");
				colorCombo->GetComboBox()->AddItem(L"darkerPink", "darkerPink");

				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"lighterGray", "lighterGray");
				colorCombo->GetComboBox()->AddItem(L"lightGray", "lightGray");
				colorCombo->GetComboBox()->AddItem(L"gray", "gray");
				colorCombo->GetComboBox()->AddItem(L"darkGray", "darkGray");
				colorCombo->GetComboBox()->AddItem(L"darkerGray", "darkerGray");

				colorCombo->GetComboBox()->AddItem(L"", "");

				colorCombo->GetComboBox()->AddItem(L"white", "white");
				colorCombo->GetComboBox()->AddItem(L"black", "black");

				n++; p->Add("Color", colorCombo, "1")->SetToolTip(b->color_Info.tip);

				if(b->color!=nullptr)colorCombo->GetComboBox()->SelectItemByName(b->color->name);
			}

			{
				Property::TextWithButton *tb = new Property::TextWithButton(p, "Edit");
				n++; p->Add(b->rotationSet_Info.label, tb, b->rotationSet.name)->SetToolTip(b->rotationSet_Info.tip);
				tb->GetButton()->onPress.Add(this, &CustomGameEditorControl::doEditRotationSetWindowButton);
			}

			n++; p->Add(b->frequencySpecialPieceTypeOnceEveryNPieces_Info.label, to_string(b->frequencySpecialPieceTypeOnceEveryNPieces))->SetToolTip(b->frequencySpecialPieceTypeOnceEveryNPieces_Info.tip);
			n++; p->Add(b->randomSpecialPieceChanceOneOutOf_Info.label, to_string(b->randomSpecialPieceChanceOneOutOf))->SetToolTip(b->randomSpecialPieceChanceOneOutOf_Info.tip);

			n++; p->Add(b->flashingSpecialType_Info.label, new Property::Checkbox(p), to_string(b->flashingSpecialType))->SetToolTip(b->flashingSpecialType_Info.tip);
			n++; p->Add(b->clearEveryRowPieceIsOnIfAnySingleRowCleared_Info.label, new Property::Checkbox(p), to_string(b->clearEveryRowPieceIsOnIfAnySingleRowCleared))->SetToolTip(b->clearEveryRowPieceIsOnIfAnySingleRowCleared_Info.tip);

			n++; p->Add(b->turnBackToNormalPieceAfterNPiecesLock_Info.label, to_string(b->turnBackToNormalPieceAfterNPiecesLock))->SetToolTip(b->turnBackToNormalPieceAfterNPiecesLock_Info.tip);
			n++; p->Add(b->fadeOutOnceSetInsteadOfAddedToGrid_Info.label, new Property::Checkbox(p), to_string(b->fadeOutOnceSetInsteadOfAddedToGrid))->SetToolTip(b->fadeOutOnceSetInsteadOfAddedToGrid_Info.tip);
			n++; p->Add(b->useAsNormalPiece_Info.label, new Property::Checkbox(p), to_string(b->useAsNormalPiece))->SetToolTip(b->useAsNormalPiece_Info.tip);
			n++; p->Add(b->useAsGarbagePiece_Info.label, new Property::Checkbox(p), to_string(b->useAsGarbagePiece))->SetToolTip(b->useAsGarbagePiece_Info.tip);
			n++; p->Add(b->useAsPlayingFieldFillerPiece_Info.label, new Property::Checkbox(p), to_string(b->useAsPlayingFieldFillerPiece))->SetToolTip(b->useAsPlayingFieldFillerPiece_Info.tip);
			n++; p->Add(b->disallowAsFirstPiece_Info.label, new Property::Checkbox(p), to_string(b->disallowAsFirstPiece))->SetToolTip(b->disallowAsFirstPiece_Info.tip);


			Property::ComboBox* spriteNameCombo = new Property::ComboBox(p);
			{
				spriteNameCombo->GetComboBox()->AddItem(Utility::StringToUnicode(""), "");
				for (int i = 0; i<bobsGame->loadedSprites.size(); i++)
				{
					Sprite *s = bobsGame->loadedSprites.get(i);
					spriteNameCombo->GetComboBox()->AddItem(Utility::StringToUnicode(s->getName()), s->getName());
				}

				n++; p->Add(b->spriteName_Info.label, spriteNameCombo, "1")->SetToolTip(b->spriteName_Info.tip);
				spriteNameCombo->GetComboBox()->SelectItemByName(b->spriteName);
			}

			n++; p->Add(b->bombPiece_Info.label, new Property::Checkbox(p), to_string(b->bombPiece))->SetToolTip(b->bombPiece_Info.tip);
			n++; p->Add(b->weightPiece_Info.label, new Property::Checkbox(p), to_string(b->weightPiece))->SetToolTip(b->weightPiece_Info.tip);
			n++; p->Add(b->pieceRemovalShooterPiece_Info.label, new Property::Checkbox(p), to_string(b->pieceRemovalShooterPiece))->SetToolTip(b->pieceRemovalShooterPiece_Info.tip);
			n++; p->Add(b->pieceShooterPiece_Info.label, new Property::Checkbox(p), to_string(b->pieceShooterPiece))->SetToolTip(b->pieceShooterPiece_Info.tip);

			{
				string blockTypesString = "";
				for (int i = 0; i < b->overrideBlockTypes_UUID.size(); i++)
				{
					BlockType *bt = currentGameType->getBlockTypeByUUID(b->overrideBlockTypes_UUID.get(i));
					string blockName = "";
					if (bt != nullptr)blockName = bt->name;
					else blockName = "ERROR";
					blockTypesString = blockTypesString + blockName + ",";
				}
				Property::TextWithButton *tb = new Property::TextWithButton(p, "Edit");
				n++; p->Add(b->overrideBlockTypes_Info.label, tb, blockTypesString)->SetToolTip(b->overrideBlockTypes_Info.tip);
				tb->GetButton()->onPress.Add(this, &CustomGameEditorControl::doOverrideBlockTypesSelectionWindowButton);
			}

			p->SetSplitWidth(200);
		}


		piecePropTree->ExpandAll();

		piecePropTree->SetHeight(n * fontHeight);
		piecePropTreeNumChildren = n;
	}

}


void CustomGameEditorControl::savePiecePropTreeToCurrentPieceType()
{//=========================================================================================================================
	if (currentPieceType == nullptr)return;
	if (piecePropTree == nullptr)return;

	//parse all fields
	//if name equals any other piecetype names besides currentPieceType add a number afterwards until it doesnt
	Properties* p = piecePropTree->Find("Piece Properties");
	if (p == nullptr)
	{
		BobsGame::log.error("Could not find Piece Properties");
		return;
	}


	PropertyRow* pr = p->Find(currentPieceType->name_Info.label);
	string pieceTypeName = pr->GetProperty()->GetPropertyValue().c_str();
	if (pieceTypeName == "")pieceTypeName = "Unnamed Piece";
	int n = 0;
	for (int i = 0; i < currentGameType->pieceTypes.size(); i++)
	{
		PieceType *bt = currentGameType->pieceTypes.get(i);
		if (bt != currentPieceType && bt->name == pieceTypeName)
		{
			pieceTypeName = pieceTypeName + to_string(n);

			n++;
			i = 0;
		}
	}

	//replace name in pieceType
	currentPieceType->name = pieceTypeName;

	for (int i = 0; i<currentGameType->pieceTypes.size(); i++)
	{
		PieceType *bt = currentGameType->pieceTypes.get(i);
		if(bt == currentPieceType)
		{
			pieceSelectionListBox->GetTable()->GetRow(i)->SetCellText(0, pieceTypeName);
		}
	}


	PieceType defaultPieceType;

	string colorName = p->Find("Color")->GetProperty()->GetPropertyValue().c_str();
	currentPieceType->color = BobColor::getColorByName(colorName);


	try {
		currentPieceType->frequencySpecialPieceTypeOnceEveryNPieces = stoi(p->Find(currentPieceType->frequencySpecialPieceTypeOnceEveryNPieces_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentPieceType->frequencySpecialPieceTypeOnceEveryNPieces = defaultPieceType.frequencySpecialPieceTypeOnceEveryNPieces; }

	try {
		currentPieceType->randomSpecialPieceChanceOneOutOf = stoi(p->Find(currentPieceType->randomSpecialPieceChanceOneOutOf_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentPieceType->randomSpecialPieceChanceOneOutOf = defaultPieceType.randomSpecialPieceChanceOneOutOf; }

	currentPieceType->flashingSpecialType = 0 != stoi(p->Find(currentPieceType->flashingSpecialType_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentPieceType->clearEveryRowPieceIsOnIfAnySingleRowCleared = 0 != stoi(p->Find(currentPieceType->clearEveryRowPieceIsOnIfAnySingleRowCleared_Info.label)->GetProperty()->GetPropertyValue().c_str());

	try {
		currentPieceType->turnBackToNormalPieceAfterNPiecesLock = stoi(p->Find(currentPieceType->turnBackToNormalPieceAfterNPiecesLock_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentPieceType->turnBackToNormalPieceAfterNPiecesLock = defaultPieceType.turnBackToNormalPieceAfterNPiecesLock; }

	currentPieceType->fadeOutOnceSetInsteadOfAddedToGrid = 0 != stoi(p->Find(currentPieceType->fadeOutOnceSetInsteadOfAddedToGrid_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentPieceType->useAsNormalPiece = 0 != stoi(p->Find(currentPieceType->useAsNormalPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentPieceType->useAsGarbagePiece = 0 != stoi(p->Find(currentPieceType->useAsGarbagePiece_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentPieceType->useAsPlayingFieldFillerPiece = 0 != stoi(p->Find(currentPieceType->useAsPlayingFieldFillerPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentPieceType->disallowAsFirstPiece = 0 != stoi(p->Find(currentPieceType->disallowAsFirstPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());

	currentPieceType->spriteName = p->Find(currentPieceType->spriteName_Info.label)->GetProperty()->GetPropertyValue().c_str();
	
	currentPieceType->bombPiece = 0 != stoi(p->Find(currentPieceType->bombPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentPieceType->weightPiece = 0 != stoi(p->Find(currentPieceType->weightPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentPieceType->pieceRemovalShooterPiece = 0 != stoi(p->Find(currentPieceType->pieceRemovalShooterPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());
	currentPieceType->pieceShooterPiece = 0 != stoi(p->Find(currentPieceType->pieceShooterPiece_Info.label)->GetProperty()->GetPropertyValue().c_str());


//	currentPieceType->overrideBlockTypes.clear();
//	{
//		for (int i = 0; i < currentPieceType_overrideBlockTypes.size(); i++)
//		{
//			BlockType *pt = currentPieceType_overrideBlockTypes.get(i);
//			currentPieceType->overrideBlockTypes.add(pt);
//		}
//	}
}



void CustomGameEditorControl::onAddBlockButton(Base* control)
{//=========================================================================================================================

	//create new blocktype, add it to list, select it, populate block fields

	BlockType *b = new BlockType();

	string newName = "New Block";
	{
		int n = 0;
		for (int i = 0; i < currentGameType->blockTypes.size(); i++)
		{
			BlockType *bt = currentGameType->blockTypes.get(i);
			if (bt->name == newName)
			{
				newName = newName + to_string(n);
				n++;
				i = 0;
			}
		}
	}

	b->name = newName;
	b->useInNormalPieces = true;

	currentGameType->blockTypes.add(b);

	Layout::TableRow *row = blockSelectionListBox->AddItem(b->name, b->uuid);
	row->onRowSelected.Add(this, &CustomGameEditorControl::onBlockListRowSelect);
	blockSelectionListBox->SetSelectedRow(row);
	onBlockListRowSelect(row);
}

void CustomGameEditorControl::onDuplicateBlockButton(Base* control)
{//=========================================================================================================================


	if (blockSelectionListBox->IsAnyRowSelected() == false)return;

	Layout::TableRow* row = blockSelectionListBox->GetSelectedRow();
	string uuid = row->GetName().c_str();

	BlockType *bt = getBlockTypeByUUID(uuid);

	if (bt == nullptr)
	{
		BobsGame::log.error("Could not find blocktype with uuid:" + uuid);
		return;
	}


	BlockType *b = new BlockType();
	string newuuid = b->uuid;
	*b = *bt;
	b->uuid = newuuid;


	string newName = bt->name + " Copy";
	{
		int n = 0;
		for (int i = 0; i < currentGameType->blockTypes.size(); i++)
		{
			BlockType *temp = currentGameType->blockTypes.get(i);
			if (temp->name == newName)
			{
				newName = newName + to_string(n);
				n++;
				i = 0;
			}
		}
	}

	b->name = newName;

	currentGameType->blockTypes.add(b);

	Layout::TableRow *newRow = blockSelectionListBox->AddItem(b->name, bt->uuid);
	newRow->onRowSelected.Add(this, &CustomGameEditorControl::onBlockListRowSelect);
	blockSelectionListBox->SetSelectedRow(newRow);
	onBlockListRowSelect(newRow);


}
void CustomGameEditorControl::onDeleteBlockButton(Base* control)
{//=========================================================================================================================


	//TODO: warn that it is included in piece or block

	if (blockSelectionListBox->IsAnyRowSelected() == false)return;

	Layout::TableRow* row = blockSelectionListBox->GetSelectedRow();
	string uuid = row->GetName().c_str();

	BlockType *bt = getBlockTypeByUUID(uuid);

	if (bt == nullptr)
	{
		BobsGame::log.error("Could not find blocktype with uuid:" + uuid);
		return;
	}

	if (currentGameType->blockTypes.contains(bt))currentGameType->blockTypes.remove(bt);


	//remove it from any pieces being used
	//b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType
	//b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut fromType,toType
	//p->overrideBlockTypes
	for(int i=0;i<currentGameType->blockTypes.size();i++)
	{
		BlockType *b = currentGameType->blockTypes.get(i);

		if(b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.contains(bt->uuid))b->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.remove(bt->uuid);

		for(int n=0; n < b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); n++)
		{
			TurnFromBlockTypeToType *tb = b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(n);
			if (tb->fromType_UUID == bt->uuid || tb->toType_UUID == bt->uuid)
			{
				b->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.removeAt(n);
				n--;
			}
		}
	}

//	for (int n = 0; n < currentBlockType_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); n++)
//	{
//		TurnFromBlockTypeToType *tb = currentBlockType_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(n);
//		if (tb->fromType == bt->name || tb->toType == bt->name)
//		{
//			currentBlockType_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.removeAt(n);
//			n--;
//		}
//	}

	for (int i = 0; i < currentGameType->pieceTypes.size(); i++)
	{
		PieceType *p = currentGameType->pieceTypes.get(i);
		if (p->overrideBlockTypes_UUID.contains(bt->uuid))p->overrideBlockTypes_UUID.remove(bt->uuid);
	}

	//if (currentPieceType_overrideBlockTypes.contains(bt))currentPieceType_overrideBlockTypes.remove(bt);

	//refresh piecePropTree, just save and reselect
	savePiecePropTreeToCurrentPieceType();
	onPieceListRowSelect(pieceSelectionListBox->GetSelectedRow());



	blockSelectionListBox->UnselectAll();

	//delete it from the list
	blockSelectionListBox->RemoveItem(row);
	GetCanvas()->DoThink();

	//if no blocks in the list, add an empty blocktype to the list and select it
	//otherwise try to select this position, if nothing there select above block

	if (blockSelectionListBox->GetNumRows() == 0)
	{
		//onAddBlockButton(control);
		currentBlockType = nullptr;

		if (blockPropTree != nullptr)
		{
			blockPropTree->DelayedDelete();
			GetCanvas()->DoThink();
			//delete blockPropTree;
			blockPropTree = nullptr;
		}
	}
	else
	{
		blockSelectionListBox->SelectByIndex(0);
		onBlockListRowSelect((Controls::Base*)blockSelectionListBox->GetRow(0));
	}
}


void CustomGameEditorControl::onAddPieceButton(Base* control)
{//=========================================================================================================================
	//add a generic piece to the bottom of the list and populate the fields

	PieceType *b = new PieceType();

	

	string newName = "New Piece";
	{
		int n = 0;
		for (int i = 0; i < currentGameType->pieceTypes.size(); i++)
		{
			PieceType *bt = currentGameType->pieceTypes.get(i);
			if (bt->name == newName)
			{
				newName = newName + to_string(n);
				n++;
				i = 0;
			}
		}
	}

	b->name = newName;
	b->useAsNormalPiece = true;
	currentGameType->pieceTypes.add(b);


	Layout::TableRow *row = pieceSelectionListBox->AddItem(b->name, b->uuid);
	row->onRowSelected.Add(this, &CustomGameEditorControl::onPieceListRowSelect);
	pieceSelectionListBox->SetSelectedRow(row);
	onPieceListRowSelect(row);
}

void CustomGameEditorControl::onDuplicatePieceButton(Base* control)
{//=========================================================================================================================


	if (pieceSelectionListBox->IsAnyRowSelected() == false)return;

	Layout::TableRow* row = pieceSelectionListBox->GetSelectedRow();
	string uuid = row->GetName().c_str();

	PieceType *bt = getPieceTypeByUUID(uuid);

	if (bt == nullptr)
	{
		BobsGame::log.error("Could not find pieceType with uuid:" + uuid);
		return;
	}

	if (currentGameType->pieceTypes.contains(bt))currentGameType->pieceTypes.remove(bt);



	PieceType *b = new PieceType();
	string newuuid = b->uuid;
	*b = *bt;
	b->uuid = newuuid;


	string newName = bt->name + " Copy";
	{
		int n = 0;
		for (int i = 0; i < currentGameType->pieceTypes.size(); i++)
		{
			PieceType *temp = currentGameType->pieceTypes.get(i);
			if (temp->name == newName)
			{
				newName = newName + to_string(n);
				n++;
				i = 0;
			}
		}
	}

	b->name = newName;

	currentGameType->pieceTypes.add(b);


	Layout::TableRow *newRow = pieceSelectionListBox->AddItem(b->name, b->uuid);
	newRow->onRowSelected.Add(this, &CustomGameEditorControl::onPieceListRowSelect);
	pieceSelectionListBox->SetSelectedRow(newRow);
	onPieceListRowSelect(newRow);

}
void CustomGameEditorControl::onDeletePieceButton(Base* control)
{//=========================================================================================================================

	//TODO: warn that it is included in piece or block

	if (pieceSelectionListBox->IsAnyRowSelected() == false)return;

	Layout::TableRow* row = pieceSelectionListBox->GetSelectedRow();
	string uuid = row->GetName().c_str();

	PieceType *bt = getPieceTypeByUUID(uuid);

	if (bt == nullptr)
	{
		BobsGame::log.error("Could not find pieceType with uuid:" + uuid);
		return;
	}

	if (currentGameType->pieceTypes.contains(bt))currentGameType->pieceTypes.remove(bt);


	//remove it from any pieces being used
	//b->makePieceTypeWhenCleared
	for (int i = 0; i<currentGameType->blockTypes.size(); i++)
	{
		BlockType *b = currentGameType->blockTypes.get(i);
		if (b->makePieceTypeWhenCleared_UUID.contains(bt->uuid))b->makePieceTypeWhenCleared_UUID.remove(bt->uuid);
	}
	//if (currentBlockType_makePieceTypeWhenCleared.contains(bt))currentBlockType_makePieceTypeWhenCleared.remove(bt);

	//refresh blockPropTree, just save and reselect
	saveBlockPropTreeToCurrentBlockType();
	onBlockListRowSelect(blockSelectionListBox->GetSelectedRow());


	pieceSelectionListBox->UnselectAll();

	//delete it from the list
	pieceSelectionListBox->RemoveItem(row);
	GetCanvas()->DoThink();

	//if no pieces in the list, add an empty piecetype to the list and select it
	//otherwise try to select this position, if nothing there select above piece

	if (pieceSelectionListBox->GetNumRows() == 0)
	{
		//onAddPieceButton(nullptr);
		currentPieceType = nullptr;

		if (piecePropTree != nullptr)
		{
			piecePropTree->DelayedDelete();
			GetCanvas()->DoThink();
			//delete piecePropTree;
			piecePropTree = nullptr;
		}
	}
	else
	{
		pieceSelectionListBox->SelectByIndex(0);
		onPieceListRowSelect((Controls::Base*)pieceSelectionListBox->GetRow(0));
	}
}



void CustomGameEditorControl::makeSelectionWindow(string name)
{//=========================================================================================================================

	int w = GLUtils::getViewportWidth() / 2;
	int h = GLUtils::getViewportHeight() / 2;

	selectWindow = new WindowControl(GetCanvas());
	selectWindow->SetTitle(name);
	selectWindow->SetSize(w, h);
	selectWindow->MakeModal(true);
	//selectWindow->Position(Pos::Center);
	selectWindow->SetPos(GLUtils::getViewportWidth() / 2 - w / 2, GLUtils::getViewportHeight() / 2 - h / 2);
	selectWindow->SetDeleteOnClose(true);
	//selectWindow->SetClosable(false);

	Controls::Base *topBase = new Base(selectWindow);
	topBase->Dock(Pos::Top);
	topBase->SetWidth(selectWindow->Width());
	topBase->SetHeight(selectWindow->Height()-60);

	selectListBox = new ListBox(topBase);
	{
		selectListBox->Dock(Pos::Left);
		selectListBox->SetAllowMultiSelect(false);
		selectListBox->SetWidth(topBase->Width() / 2 - 60);
	}

	selectAddRemoveButtonBase = new Base(topBase);
	selectAddRemoveButtonBase->Dock(Pos::Left);
	selectAddRemoveButtonBase->SetWidth(70);
	{

		Layout::Position* positioner = new Layout::Position(selectAddRemoveButtonBase);
		positioner->Dock(Pos::Top);
		positioner->SetHeight(topBase->Height() / 2 - 20);

		selectAddButton = new Button(selectAddRemoveButtonBase);
		selectAddButton->SetText(L"Add ->");
		//selectAddButton->SetToolTip(b->_Info.tip);
		selectAddButton->Dock(Pos::Top);
		selectAddButton->SetWidth(70);
		selectAddButton->SetHeight(20);

		selectRemoveButton = new Button(selectAddRemoveButtonBase);
		selectRemoveButton->SetText(L"<- Remove");
		//selectRemoveButton->SetToolTip(b->_Info.tip);
		selectRemoveButton->Dock(Pos::Top);
		selectRemoveButton->SetWidth(70);
		selectRemoveButton->SetHeight(20);

		

	}

	chosenTypesListBox = new ListBox(topBase);
	{
		chosenTypesListBox->Dock(Pos::Left);
		chosenTypesListBox->SetAllowMultiSelect(false);
		chosenTypesListBox->SetWidth(topBase->Width() / 2 - 60);
	}


	selectConfirmCancelButtonBase = new Base(selectWindow);
	selectConfirmCancelButtonBase->Dock(Pos::Bottom);
	selectConfirmCancelButtonBase->SetWidth(selectWindow->Width());
	selectConfirmCancelButtonBase->SetHeight(20);
	{
		Layout::Position* positioner = new Layout::Position(selectAddRemoveButtonBase);
		positioner->Dock(Pos::Left);
		positioner->SetWidth(selectConfirmCancelButtonBase->Width() / 2 - 160);


		selectConfirmButton = new Button(selectConfirmCancelButtonBase);
		selectConfirmButton->SetText(L"Save");
		//selectConfirmButton->SetToolTip(b->_Info.tip);
		selectConfirmButton->Dock(Pos::Left);
		selectConfirmButton->SetWidth(160);
		selectConfirmButton->SetMargin(Margin(0, 0, 0, 0));


		selectCancelButton = new Button(selectConfirmCancelButtonBase);
		selectCancelButton->SetText(L"Cancel");
		//selectCancelButton->SetToolTip(b->_Info.tip);
		selectCancelButton->Dock(Pos::Left);
		selectCancelButton->SetWidth(160);
		selectCancelButton->SetMargin(Margin(0, 0, 0, 0));
		selectCancelButton->onPress.Add(this, &CustomGameEditorControl::cancelTypesWindow);
	}
}


void CustomGameEditorControl::doEditMakePieceTypeWhenClearedWindowButton(Base* control)
{//=========================================================================================================================
 
	windowOpen = true;
	//open window with list of piecetypes in it, and empty list in it, with add-> <-remove buttons

	makeSelectionWindow("Edit makePieceTypeWhenCleared");

	for (int i = 0; i < currentGameType->pieceTypes.size(); i++)
	{
		PieceType *pt = currentGameType->pieceTypes.get(i);
		selectListBox->AddItem(pt->name, pt->uuid);
	}

	for (int i = 0; i < currentBlockType->makePieceTypeWhenCleared_UUID.size(); i++)
	{
		PieceType *pt = currentGameType->getPieceTypeByUUID(currentBlockType->makePieceTypeWhenCleared_UUID.get(i));
		if (pt != nullptr)
		{
			chosenTypesListBox->AddItem(pt->name, pt->uuid);
		}
	}

	selectAddButton->onPress.Add(this, &CustomGameEditorControl::addType);
	selectRemoveButton->onPress.Add(this, &CustomGameEditorControl::removeType);
	selectConfirmButton->onPress.Add(this, &CustomGameEditorControl::saveMakePieceTypes);
	//currentBlockType_makePieceTypeWhenCleared;
}


void CustomGameEditorControl::addType(Base* control)
{//=========================================================================================================================
	//add selected row to listbox if doesnt exist already
	if(selectListBox->IsAnyRowSelected())
	{
		Layout::TableRow* row = selectListBox->GetSelectedRow();

		bool exists = false;
		for(int i=0;i<chosenTypesListBox->GetNumRows();i++)
		{
			Layout::TableRow* selRow = chosenTypesListBox->GetRow(i);
			if (string(selRow->GetName().c_str()) == string(row->GetName().c_str()))exists = true;
		}

		if(exists==false)
		{
			chosenTypesListBox->AddItem(row->GetText(0), row->GetName());
		}
	}
}

void CustomGameEditorControl::removeType(Base* control)
{//=========================================================================================================================
	//remove selected row from listbox
	if(chosenTypesListBox->IsAnyRowSelected())chosenTypesListBox->RemoveItem(chosenTypesListBox->GetSelectedRow());
}

void CustomGameEditorControl::saveMakePieceTypes(Base* control)
{//=========================================================================================================================
	//save listbox to currentBlockType_makePieceTypeWhenCleared

	currentBlockType->makePieceTypeWhenCleared_UUID.clear();

	for(int i=0;i<chosenTypesListBox->GetNumRows();i++)
	{
		Layout::TableRow* row = chosenTypesListBox->GetRow(i);
		string uuid = row->GetName().c_str();

		PieceType *pt = getPieceTypeByUUID(uuid);

		if(pt!=nullptr)currentBlockType->makePieceTypeWhenCleared_UUID.add(pt->uuid);
	
	}


	Properties* p = blockPropTree->Find("Block Properties");
	PropertyRow* pr = p->Find(currentBlockType->makePieceTypeWhenCleared_Info.label);
	{
		string typesString = "";
		for (int i = 0; i < currentBlockType->makePieceTypeWhenCleared_UUID.size(); i++)
		{
			PieceType *pt = currentGameType->getPieceTypeByUUID(currentBlockType->makePieceTypeWhenCleared_UUID.get(i));
			if(pt!=nullptr)typesString = typesString + pt->name + ",";
		}
		//pr->SetValue(pieceTypesString);
		pr->GetProperty()->SetPropertyValue(typesString);
		//pr->GetProperty()->SetValue(pieceTypesString);

	}

	selectWindow->CloseButtonPressed();
	windowOpen = false;
	initPreviewGame();
}


void CustomGameEditorControl::doEditConnectedUDLRChangeIntoBlockTypeWindowButton(Base* control)
{//=========================================================================================================================

	windowOpen = true;
	//open window with list of blocktypes in it, and empty list in it, with add-> <-remove buttons

	makeSelectionWindow("Edit connectedUDLRChangeIntoBlockType");

	for (int i = 0; i < currentGameType->blockTypes.size(); i++)
	{
		BlockType *pt = currentGameType->blockTypes.get(i);
		selectListBox->AddItem(pt->name, pt->uuid);
	}

	selectAddButton->onPress.Add(this, &CustomGameEditorControl::addType);
	selectRemoveButton->onPress.Add(this, &CustomGameEditorControl::removeType);


	for (int i = 0; i < currentBlockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.size(); i++)
	{
		BlockType *pt = currentGameType->getBlockTypeByUUID(currentBlockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.get(i));
		if (pt != nullptr)
		{
			chosenTypesListBox->AddItem(pt->name, pt->uuid);
		}
	}
	
	selectConfirmButton->onPress.Add(this, &CustomGameEditorControl::saveConnectedUDLRChangeIntoBlockTypes);


	//currentBlockType_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType;

}

void CustomGameEditorControl::saveConnectedUDLRChangeIntoBlockTypes(Base* control)
{//=========================================================================================================================
 //save listbox to currentBlockType_ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType

	currentBlockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.clear();

	for (int i = 0; i<chosenTypesListBox->GetNumRows(); i++)
	{
		Layout::TableRow* row = chosenTypesListBox->GetRow(i);
		string uuid = row->GetName().c_str();

		BlockType *bt = getBlockTypeByUUID(uuid);
		if(bt!=nullptr)currentBlockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.add(bt->uuid);
			
	}

	Properties* p = blockPropTree->Find("Block Properties");
	PropertyRow* pr = p->Find(currentBlockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_Info.label);
	{
		string typesString = "";
		for (int i = 0; i < currentBlockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.size(); i++)
		{
			BlockType *pt = currentGameType->getBlockTypeByUUID(currentBlockType->ifConnectedUpDownLeftRightToExplodingBlockChangeIntoThisType_UUID.get(i));
			string blockName = "";
			if (pt != nullptr)blockName = pt->name;
			else blockName = "ERROR";
			typesString = typesString + blockName + ",";
		}
		//pr->SetValue(typesString);
		pr->GetProperty()->SetPropertyValue(typesString);
	}

	selectWindow->CloseButtonPressed();
	windowOpen = false;
	initPreviewGame();
}
void CustomGameEditorControl::cancelTypesWindow(Base* control)
{//=========================================================================================================================
 //just close window
	selectWindow->CloseButtonPressed();
	windowOpen = false;
	initPreviewGame();
}


void CustomGameEditorControl::doOverrideBlockTypesSelectionWindowButton(Base* control)
{//=========================================================================================================================

	windowOpen = true;
	//open window with list of blocktypes in it, and empty list in it, with add-> <-remove buttons

	makeSelectionWindow("Edit overrideBlockTypesSelection");


	for (int i = 0; i < currentGameType->blockTypes.size(); i++)
	{
		BlockType *pt = currentGameType->blockTypes.get(i);
		selectListBox->AddItem(pt->name, pt->uuid);
	}
	
	selectAddButton->onPress.Add(this, &CustomGameEditorControl::addType);
	selectRemoveButton->onPress.Add(this, &CustomGameEditorControl::removeType);
	
	for (int i = 0; i < currentPieceType->overrideBlockTypes_UUID.size(); i++)
	{
		BlockType *pt = currentGameType->getBlockTypeByUUID(currentPieceType->overrideBlockTypes_UUID.get(i));
		if (pt != nullptr)
		{
			chosenTypesListBox->AddItem(pt->name, pt->uuid);
		}
	}
	
	selectConfirmButton->onPress.Add(this, &CustomGameEditorControl::saveOverrideBlockTypes);

	//currentPieceType_overrideBlockTypes;

}




void CustomGameEditorControl::saveOverrideBlockTypes(Base* control)
{//=========================================================================================================================
 //save listbox to currentPieceType_overrideBlockTypes

	currentPieceType->overrideBlockTypes_UUID.clear();

	for (int i = 0; i<chosenTypesListBox->GetNumRows(); i++)
	{
		Layout::TableRow* row = chosenTypesListBox->GetRow(i);
		string uuid = row->GetName().c_str();

		BlockType *bt = getBlockTypeByUUID(uuid);

		if(bt!=nullptr)currentPieceType->overrideBlockTypes_UUID.add(bt->uuid);
			
		
	}

	Properties* p = piecePropTree->Find("Piece Properties");
	PropertyRow* pr = p->Find(currentPieceType->overrideBlockTypes_Info.label);
	{
		string typesString = "";
		for (int i = 0; i < currentPieceType->overrideBlockTypes_UUID.size(); i++)
		{
			BlockType *pt = currentGameType->getBlockTypeByUUID(currentPieceType->overrideBlockTypes_UUID.get(i));
			if (pt != nullptr)
			{
				typesString = typesString + pt->name + ",";
			}
		}
		//pr->SetValue(typesString);
		pr->GetProperty()->SetPropertyValue(typesString);
	}

	selectWindow->CloseButtonPressed();
	windowOpen = false;
	initPreviewGame();
}




void CustomGameEditorControl::doEditTurnFromBlockTypeToTypeWindowButton(Base* control)
{//=========================================================================================================================

	windowOpen = true;

	int w = GLUtils::getViewportWidth() / 2;
	int h = GLUtils::getViewportHeight() / 2;

	selectWindow = new WindowControl(GetCanvas());
	selectWindow->SetTitle("Edit turnFromBlockTypeToType");
	selectWindow->SetSize(w, h);
	selectWindow->MakeModal(true);
	//selectWindow->Position(Pos::Center);
	selectWindow->SetPos(GLUtils::getViewportWidth() / 2 - w / 2, GLUtils::getViewportHeight() / 2 - h / 2);
	selectWindow->SetDeleteOnClose(true);
	selectWindow->SetClosable(false);

	Controls::Base *topBase = new Base(selectWindow);
	topBase->Dock(Pos::Top);
	topBase->SetWidth(selectWindow->Width());
	topBase->SetHeight(selectWindow->Height() - 60);
	{


		Controls::Base *listBase = new Base(topBase);
		listBase->Dock(Pos::Left);
		listBase->SetSize(topBase->Width()/2, topBase->Height()-10);
		{
			toFromListBox = new ListBox(listBase);
			{
				toFromListBox->Dock(Pos::Top);
				toFromListBox->SetAllowMultiSelect(false);
				toFromListBox->SetSize(listBase->Width(), listBase->Height() - 20);
			}

			for(int i=0;i<currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size();i++)
			{
				TurnFromBlockTypeToType *t = currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(i);
				Layout::TableRow *row = toFromListBox->AddItem(t->getName(currentGameType));
				row->onRowSelected.Add(this, &CustomGameEditorControl::onTurnFromBlockTypeToTypeSelect);
			}


			Controls::Base *listButtonBase = new Base(listBase);
			listButtonBase->Dock(Pos::Bottom);
			listButtonBase->SetHeight(20);
			{
				Controls::Button *newButton = new Button(listButtonBase);
				newButton->SetText(L"New");
				newButton->Dock(Pos::Left);
				newButton->SetWidth(40);
				newButton->SetHeight(20);
				newButton->onPress.Add(this, &CustomGameEditorControl::newTurnFromBlockTypeToType);

				Controls::Button *deleteButton = new Button(listButtonBase);
				deleteButton->SetText(L"Delete");
				deleteButton->Dock(Pos::Left);
				deleteButton->SetWidth(60);
				deleteButton->SetHeight(20);
				deleteButton->onPress.Add(this, &CustomGameEditorControl::deleteTurnFromBlockTypeToType);
			}

		}

		Controls::Base *rightBase = new Base(topBase);
		rightBase->Dock(Pos::Left);
		rightBase->SetSize(topBase->Width() / 2 - 20,topBase->Height());
		{

			Layout::Position* positioner = new Layout::Position(rightBase);
			positioner->Dock(Pos::Top);
			positioner->SetHeight(rightBase->Height() / 2 - 20);

			//Controls::Base *toFromComboBase = new Base(rightBase);
			//toFromComboBase->Dock(Pos::Top);
			//toFromComboBase->SetSize(rightBase->Width(),40);
			{
				Controls::Label *fromLabel = new Controls::Label(rightBase, "From");
				fromLabel->SetText("From");
				fromLabel->Dock(Pos::Top);
				fromLabel->SetSize(50, 15);


				fromCombo = new Controls::ComboBox(rightBase, "fromType");
				fromCombo->Dock(Pos::Top);
				fromCombo->SetSize(100, 20);
				for (int i = 0; i < currentGameType->blockTypes.size(); i++)
				{
					BlockType *bt = currentGameType->blockTypes.get(i);
					fromCombo->AddItem(Utility::StringToUnicode(bt->name), bt->uuid);
					fromCombo->onSelection.Add(this, &CustomGameEditorControl::saveFromTypeComboToCurrentType);
				}


				Controls::Label *toLabel = new Controls::Label(rightBase, "To");
				toLabel->SetText("To");
				toLabel->Dock(Pos::Top);
				toLabel->SetSize(50, 15);


				toCombo = new Controls::ComboBox(rightBase, "toType");
				toCombo->Dock(Pos::Top);
				toCombo->SetSize(100, 20);
				for (int i = 0; i < currentGameType->blockTypes.size(); i++)
				{
					BlockType *bt = currentGameType->blockTypes.get(i);
					toCombo->AddItem(Utility::StringToUnicode(bt->name), bt->uuid);
					toCombo->onSelection.Add(this, &CustomGameEditorControl::saveToTypeComboToCurrentType);
				}
			}

		}
	}



	selectConfirmCancelButtonBase = new Base(selectWindow);
	selectConfirmCancelButtonBase->Dock(Pos::Bottom);
	selectConfirmCancelButtonBase->SetWidth(selectWindow->Width());
	selectConfirmCancelButtonBase->SetHeight(20);
	{
		Layout::Position* positioner = new Layout::Position(selectConfirmCancelButtonBase);
		positioner->Dock(Pos::Left);
		positioner->SetWidth(selectConfirmCancelButtonBase->Width() / 2 - 160);


		selectConfirmButton = new Button(selectConfirmCancelButtonBase);
		selectConfirmButton->SetText(L"Save and close");
		//selectConfirmButton->SetToolTip(b->_Info.tip);
		selectConfirmButton->Dock(Pos::Left);
		selectConfirmButton->SetWidth(160);
		selectConfirmButton->SetMargin(Margin(0, 0, 0, 0));
		selectConfirmButton->onPress.Add(this, &CustomGameEditorControl::closeTurnFromBlockTypeToTypeEditor);

	}


	//have list of blocktypes and two edit fields
	//currentBlockType_whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut;
}


void CustomGameEditorControl::newTurnFromBlockTypeToType(Base* control)
{//=========================================================================================================================


	//if something is selected, save it
	if (currentTurnFromBlockTypeToType != nullptr)
	{
		//save the blocktypes in the combo values to currentTurnFromBlockTypeToType
		saveCurrentTurnFromBlockTypeToType();
	}

	//add to list
	//select it
	//set comboboxes
	//set currentTurnFromBlockTypeToType

	if (currentGameType->blockTypes.size() == 0)return;

	TurnFromBlockTypeToType *b = new TurnFromBlockTypeToType();
	b->fromType_UUID = currentGameType->blockTypes.get(0)->uuid;
	b->toType_UUID = currentGameType->blockTypes.get(0)->uuid;
	currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.add(b);

	Layout::TableRow *row = toFromListBox->AddItem(b->getName(currentGameType));
	row->onRowSelected.Add(this, &CustomGameEditorControl::onTurnFromBlockTypeToTypeSelect);
	toFromListBox->SetSelectedRow(row);
	onTurnFromBlockTypeToTypeSelect(row);

}


void CustomGameEditorControl::deleteTurnFromBlockTypeToType(Base* control)
{//=========================================================================================================================
	//delete from array
	//delete from tree


	if (toFromListBox->IsAnyRowSelected() == false)return;

	Layout::TableRow* row = toFromListBox->GetSelectedRow();
	string name = row->GetText(0).c_str();


	TurnFromBlockTypeToType *bt = nullptr;
	for (int i = 0; i<currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); i++)
	{
		TurnFromBlockTypeToType *b = currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(i);
		if (b->getName(currentGameType) == name)
		{
			bt = b;
		}
	}

	if (bt == nullptr)
	{
		BobsGame::log.error("Could not find TurnFromBlockTypeToType with name:" + name);
		return;
	}

	if (currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.contains(bt))currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.remove(bt);



	toFromListBox->UnselectAll();

	//delete it from the list
	toFromListBox->RemoveItem(row);

	//if no TurnFromBlockTypeToTypes in the list, add an empty TurnFromBlockTypeToType to the list and select it
	//otherwise try to select this position, if nothing there select above block

	if (toFromListBox->GetNumRows() == 0)
	{
		//allow the list to be completely empty
	}
	else
	{
		toFromListBox->SelectByIndex(0);
		onTurnFromBlockTypeToTypeSelect((Controls::Base*)toFromListBox->GetRow(0));
	}
}




void CustomGameEditorControl::closeTurnFromBlockTypeToTypeEditor(Base* control)
{//=========================================================================================================================

	//save selected combobox values to currentTurnFromBlockTypeToType

	saveCurrentTurnFromBlockTypeToType();
	selectWindow->CloseButtonPressed();
	currentTurnFromBlockTypeToType = nullptr;

	//save to blockListPropTree

	Properties* p = blockPropTree->Find("Block Properties");
	PropertyRow* pr = p->Find(currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut_Info.label);
	{
		string typesString = "";
		for (int i = 0; i < currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); i++)
		{
			TurnFromBlockTypeToType *pt = currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(i);
			typesString = typesString + pt->getName(currentGameType) + ",";
		}
		//pr->SetValue(typesString);
		pr->GetProperty()->SetPropertyValue(typesString);
	}

	windowOpen = false;
	initPreviewGame();
}

void CustomGameEditorControl::saveFromTypeComboToCurrentType()
{//=========================================================================================================================
	if (currentTurnFromBlockTypeToType == nullptr)return;

	currentTurnFromBlockTypeToType->fromType_UUID = fromCombo->GetSelectedItem()->GetName().c_str();

	//replace name in blockTypelist
	for (int i = 0; i<currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); i++)
	{
		TurnFromBlockTypeToType *bt = currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(i);
		if (bt == currentTurnFromBlockTypeToType)
		{
			toFromListBox->GetTable()->GetRow(i)->SetCellText(0, bt->getName(currentGameType));
		}
	}
}

void CustomGameEditorControl::saveToTypeComboToCurrentType()
{//=========================================================================================================================

	if (currentTurnFromBlockTypeToType == nullptr)return;


	currentTurnFromBlockTypeToType->toType_UUID = toCombo->GetSelectedItem()->GetName().c_str();

	//replace name in blockTypelist
	for (int i = 0; i<currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); i++)
	{
		TurnFromBlockTypeToType *bt = currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(i);
		if (bt == currentTurnFromBlockTypeToType)
		{
			toFromListBox->GetTable()->GetRow(i)->SetCellText(0, bt->getName(currentGameType));
		}
	}
}
void CustomGameEditorControl::saveCurrentTurnFromBlockTypeToType()
{//=========================================================================================================================

	saveFromTypeComboToCurrentType();
	saveToTypeComboToCurrentType();
}


void CustomGameEditorControl::onTurnFromBlockTypeToTypeSelect(Base* control)
{//=========================================================================================================================
	//if something is selected, save it
	if (currentTurnFromBlockTypeToType != nullptr)
	{
		//save the blocktypes in the combo values to currentTurnFromBlockTypeToType
		saveCurrentTurnFromBlockTypeToType();
	}


	Layout::TableRow* row = (Layout::TableRow*)control;
	string name = row->GetText(0).c_str();

	TurnFromBlockTypeToType *bt = nullptr;
	for (int i = 0; i<currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.size(); i++)
	{
		TurnFromBlockTypeToType *b = currentBlockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut.get(i);
		if (b->getName(currentGameType) == name)
		{
			bt = b;
		}
	}

	if (bt == nullptr)
	{
		BobsGame::log.error("Could not find type with name:" + name);
		return;
	}
	currentTurnFromBlockTypeToType = bt;

	BlockType *from = currentGameType->getBlockTypeByUUID(bt->fromType_UUID);
	BlockType *to = currentGameType->getBlockTypeByUUID(bt->toType_UUID);
	if (from != nullptr)fromCombo->SelectItemByName(from->uuid);
	if (to != nullptr)toCombo->SelectItemByName(to->uuid);
	

}


void CustomGameEditorControl::populateGameTypesListBox()
{//=========================================================================================================================
	
	ArrayList<pair<GameType*, pair<string, BobColor*>>> gamesStringColor = bobsGame->getSortedGameTypes();
	for (int i = 0; i < gamesStringColor.size(); i++)
	{
		pair<GameType*, pair<string, BobColor*>> gameTypeStringColorPairPair = gamesStringColor.get(i);
		GameType *g = gameTypeStringColorPairPair.first;
		pair<string, BobColor*> stringColorPair = gameTypeStringColorPairPair.second;
		string name = stringColorPair.first;
		BobColor *color = stringColorPair.second;


		Layout::TableRow *row = gameTypesListBox->AddItem(name, g->uuid);
		row->onRowSelected.Add(this, &CustomGameEditorControl::onGameTypesListSelect);
		if (g->yourVote!="none")row->SetTextColor(Gwen::Color(128, 128, 128));
		else row->SetTextColor(Gwen::Color(color->ri(), color->gi(), color->bi()));

	}
}



#include <fstream>
#include <iostream>
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Delegate.h"
#include "Poco/Zip/Decompress.h"
#include "Poco/Process.h"
#include "Poco/DirectoryIterator.h"
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Process;
using Poco::Path;

void CustomGameEditorControl::onGameTypesListSelect(Base* control)
{//=========================================================================================================================

	Layout::TableRow* row = (Layout::TableRow*)control;
	string uuid = row->GetName().c_str();

	GameType *s = bobsGame->getGameTypeByUUID(uuid);

	if (s == nullptr)
	{
		BobsGame::log.error("Could not find game type with uuid:" + uuid);
		return;
	}


	currentGameType = s;
	currentBlockType = nullptr;// new BlockType();
	currentPieceType = nullptr;// new PieceType();
	if (currentGameType->blockTypes.size() > 0)
	{
		currentBlockType = currentGameType->blockTypes.get(0);
	}
	if (currentGameType->pieceTypes.size() > 0)
	{
		currentPieceType = currentGameType->pieceTypes.get(0);
	}
	currentDifficultyType = currentGameType->difficultyTypes.get(0);
	
	initFromCurrentGameType();

	bobsGame->getPlayer1Game()->currentGameSequence = new GameSequence();
	bobsGame->getPlayer1Game()->currentGameSequence->gameTypes.add(currentGameType);
	bobsGame->getPlayer1Game()->currentGameSequence->endlessMode = true;

	
}


void CustomGameEditorControl::saveCurrentGameTypeToXML()
{//=========================================================================================================================


	bobsGame->saveGameTypeToXML(currentGameType, false);


}



void CustomGameEditorControl::onLoadOrCreateButton(Base* control)
{//=========================================================================================================================

	windowOpen = true;
 //ask to save changes to current game

 //opening a new game will overwrite the currently open game
 //make sure you have saved before editing a different game

	askToSaveBase = new WindowControl(GetCanvas());
	askToSaveBase->SetTitle("Save changes?");
	askToSaveBase->SetSize(200, 60);
	askToSaveBase->MakeModal(true);
	//exitAskToSaveWindow->Position(Pos::Center);
	askToSaveBase->SetPos(GLUtils::getViewportWidth() / 2 - 100, GLUtils::getViewportHeight() / 2 - 30);
	askToSaveBase->SetDeleteOnClose(true);
	//exitAskToSaveWindow->SetClosable(false);
	{

		askToSaveYesButton = new Button(askToSaveBase);
		askToSaveYesButton->SetText(L"Save");
		//askToSaveYesButton->SetToolTip(b->_Info.tip);
		askToSaveYesButton->Dock(Pos::Center | Pos::Left);
		askToSaveYesButton->SetWidth(80);
		askToSaveYesButton->onPress.Add(this, &CustomGameEditorControl::saveAndOpen);


		askToSaveNoButton = new Button(askToSaveBase);
		askToSaveNoButton->SetText(L"Don't Save");
		//askToSaveNoButton->SetToolTip(b->_Info.tip);
		askToSaveNoButton->Dock(Pos::Center | Pos::Left);
		askToSaveNoButton->SetWidth(100);
		askToSaveNoButton->onPress.Add(this, &CustomGameEditorControl::dontSaveAndOpen);

	}

}

void CustomGameEditorControl::saveAndOpen(Base* control)
{//=========================================================================================================================

	askToSaveBase->CloseButtonPressed();


	//save settings, current blocktype, current piecetype, save to current currentGameType, save to xml
	saveAllToCurrentGameType();

	//save to xml
	saveCurrentGameTypeToXML();


	openLoadOrCreateDialog(true);

	windowOpen = false;
	initPreviewGame();
}

void CustomGameEditorControl::dontSaveAndOpen(Base* control)
{//=========================================================================================================================

	askToSaveBase->CloseButtonPressed();
	

	openLoadOrCreateDialog(true);

	windowOpen = false;
	initPreviewGame();
}




void CustomGameEditorControl::openLoadOrCreateDialog(bool allowedToClose = true)
{//=========================================================================================================================

	windowOpen = true;

	int w = GLUtils::getViewportWidth() / 2;
	int h = GLUtils::getViewportHeight() / 2;

	loadOrCreateGameWindow = new WindowControl(GetCanvas());
	{
		loadOrCreateGameWindow->SetTitle("Load existing or create new game type");
		loadOrCreateGameWindow->SetSize(w, h);
		loadOrCreateGameWindow->MakeModal(true);
		//loadOrCreateGameWindow->Position(Pos::Center);
		loadOrCreateGameWindow->SetPos(GLUtils::getViewportWidth() / 2 - w / 2, GLUtils::getViewportHeight() / 2 - h / 2);
		loadOrCreateGameWindow->SetDeleteOnClose(true);
		if (allowedToClose)
		{
			loadOrCreateGameWindow->SetClosable(true);
		}
		else
		{
			loadOrCreateGameWindow->SetClosable(false);
		}


		gameTypesListBox = new ListBox(loadOrCreateGameWindow);
		{
			gameTypesListBox->SetMargin(Margin(0, 0, 0, 0));
			gameTypesListBox->Dock(Pos::Top);
			gameTypesListBox->SetAllowMultiSelect(false);
			gameTypesListBox->SetWidth(loadOrCreateGameWindow->Width());
			gameTypesListBox->SetHeight(loadOrCreateGameWindow->Height());
			//Layout::TableRow* row;
			gameTypesListBox->SetSize(w, h - 75);


			//populate list with existing game types
			//that means i need xml output to a folder in appdata or home that i can read from
			//so i'll have the preset game types in a folder in the data folder and those types are non-editable but you can copy them to a new game type and edit that
			//so it would populate this list from both folders and gray out the edit button for preset game types
			populateGameTypesListBox();

			//row = gameTypeListBox->AddItem("Empty Game Type");
			//row->onRowSelected.Add(this, &CustomGameEditorControl::onBlockListRowSelect);
			//gameTypeListBox->SetSelectedRow(row);
		}

		gameTypeSelectLabel = new Label(loadOrCreateGameWindow);
		gameTypeSelectLabel->Dock(Pos::Top);
		gameTypeSelectLabel->SetText("");
		gameTypeSelectLabel->SetHeight(20);
		gameTypeSelectLabel->SetTextColor(Gwen::Color(255,0,128,255));

		gameTypeSelectButtonBase = new Base(loadOrCreateGameWindow);
		gameTypeSelectButtonBase->Dock(Pos::Bottom);
		gameTypeSelectButtonBase->SetWidth(loadOrCreateGameWindow->Width());
		gameTypeSelectButtonBase->SetHeight(20);
		{
			editSelectedGameTypeButton = new Button(gameTypeSelectButtonBase);//TODO: this should be greyed out if a preset game type is selected
			editSelectedGameTypeButton->SetText(L"Edit");
			//editSelectedGameTypeButton->SetToolTip(b->_Info.tip);
			editSelectedGameTypeButton->Dock(Pos::Left | Pos::CenterV);
			//editSelectedGameTypeButton->SetWidth(160);
			editSelectedGameTypeButton->onPress.Add(this, &CustomGameEditorControl::editSelectedGameType);


			createNewGameTypeButton = new Button(gameTypeSelectButtonBase);
			createNewGameTypeButton->SetText(L"Create new");
			//createNewGameTypeButton->SetToolTip(b->_Info.tip);
			createNewGameTypeButton->Dock(Pos::Left | Pos::CenterV);
			//createNewGameTypeButton->SetWidth(160);
			createNewGameTypeButton->onPress.Add(this, &CustomGameEditorControl::createNewGameType);


			duplicateGameTypeButton = new Button(gameTypeSelectButtonBase);
			duplicateGameTypeButton->SetText(L"Duplicate");
			//duplicateGameTypeButton->SetToolTip(b->_Info.tip);
			duplicateGameTypeButton->Dock(Pos::Left | Pos::CenterV);
			//duplicateGameTypeButton->SetWidth(240);
			duplicateGameTypeButton->onPress.Add(this, &CustomGameEditorControl::duplicateGameType);


			deleteGameTypeButton = new Button(gameTypeSelectButtonBase);
			deleteGameTypeButton->SetText(L"Delete");
			//deleteGameTypeButton->SetToolTip(b->_Info.tip);
			deleteGameTypeButton->Dock(Pos::Left | Pos::CenterV);
			//deleteGameTypeButton->SetWidth(240);
			deleteGameTypeButton->onPress.Add(this, &CustomGameEditorControl::deleteGameType);
		}
	}


}


void CustomGameEditorControl::editSelectedGameType(Base* control)
{//=========================================================================================================================

	//make sure the type is editable, if not, do nothing, or dont even allow the button to get here in the first place

	//load xml into settings, init currentGameType prop tree, blocklist, piecelist
	//should already be done because onselect
	if (gameTypesListBox->IsAnyRowSelected() == false)return;

#ifndef _DEBUG
	if(currentGameType->builtInType)
	{
		//create modal notice that you can only duplicate? or maybe have an error label
		gameTypeSelectLabel->SetText("Built in game types must be duplicated in order to edit them.");
	}
	else
#endif
	if (currentGameType->downloaded)
	{
		//create modal notice that you can only duplicate? or maybe have an error label
		gameTypeSelectLabel->SetText("Downloaded game types must be duplicated in order to edit them.");
	}
	else
	{
		loadOrCreateGameWindow->CloseButtonPressed();
		gameTypeSelectLabel->SetText("");

		windowOpen = false;
		initPreviewGame();
	}
}


void CustomGameEditorControl::createNewGameType(Base* control)
{//=========================================================================================================================
 //create new settings with defaults and close the list
	GameType *s = new GameType();

	BlockType *bt = new BlockType();
	bt->name = "Gray Square";
	bt->spriteName = "Square";
	bt->colors.add(BobColor::gray);
	bt->useInNormalPieces = true;
	PieceType *pt = new PieceType();
	pt->name = "Single Block Piece";
	pt->useAsNormalPiece = true;
	s->blockTypes.add(bt);
	s->pieceTypes.add(pt);

	s->name += to_string(bobsGame->loadedGameTypes.size());
	bobsGame->loadedGameTypes.add(s);



	//initFromCurrentGameType();

	//add to list and select it

	Layout::TableRow *row = gameTypesListBox->AddItem(s->name, s->uuid);
	row->onRowSelected.Add(this, &CustomGameEditorControl::onGameTypesListSelect);
	gameTypesListBox->SetSelectedRow(row);
	onGameTypesListSelect(row);

	loadOrCreateGameWindow->CloseButtonPressed();

	windowOpen = false;
	initPreviewGame();
}


void CustomGameEditorControl::duplicateGameType(Base* control)
{//=========================================================================================================================

 //the only thing we would do is load the selected game type and then append the name with "copy"
	if (gameTypesListBox->IsAnyRowSelected() == false)return;

	//BobsGame::log.debug(to_string(currentGameType->pieceTypes.size()));

	GameType *s = new GameType();
	string uuid = s->uuid;
	*s = *currentGameType;
	s->uuid = uuid;
	s->builtInType = false;
	s->downloaded = false;
	//s->loadedFilename = "";
	//BobsGame::log.debug(to_string(s->pieceTypes.size()));

	s->name += "Copy"+to_string(bobsGame->loadedGameTypes.size());//TODO: rename this properly, could collide
	bobsGame->loadedGameTypes.add(s);

	Layout::TableRow *row = gameTypesListBox->AddItem(s->name, s->uuid);
	row->onRowSelected.Add(this, &CustomGameEditorControl::onGameTypesListSelect);
	gameTypesListBox->SetSelectedRow(row);
	onGameTypesListSelect(row);


	loadOrCreateGameWindow->CloseButtonPressed();

	windowOpen = false;
	initPreviewGame();
}

void CustomGameEditorControl::deleteGameType(Base* control)
{//=========================================================================================================================


	if (gameTypesListBox->IsAnyRowSelected() == false)return;

	Layout::TableRow* row = gameTypesListBox->GetSelectedRow();
	string uuid = row->GetName().c_str();

	GameType *bt = bobsGame->getGameTypeByUUID(uuid);


	if (bt == nullptr)
	{
		BobsGame::log.error("Could not find gameType with uuid:" + uuid);
		return;
	}

	if(bt->builtInType)
	{
		gameTypeSelectLabel->SetText("Cannot delete built in type.");
		return;
	}

	if (bobsGame->loadedGameTypes.contains(bt))bobsGame->loadedGameTypes.remove(bt);

	gameTypeSelectLabel->SetText("");


	gameTypesListBox->UnselectAll();

	//delete it from the list
	gameTypesListBox->RemoveItem(row);
	GetCanvas()->DoThink();

	//if (bt->loadedFilename != "")
	{
		//delete the filename (let's just rename it to deleted)
		//store the filename when load it
		string userDataPathString = FileUtils::appDataPath + "gameTypes/";
		File xmlFile(userDataPathString + bt->uuid+".xml");
		int num = 0;
		while (xmlFile.exists())
		{
			num++;
			xmlFile = File(userDataPathString + bt->uuid + ".deleted" + to_string(num));

		}
		xmlFile = File(userDataPathString + bt->uuid + ".xml");
		if (xmlFile.exists())
		{
			xmlFile.renameTo(userDataPathString + bt->uuid + ".deleted" + to_string(num));
		}
	}


	if (gameTypesListBox->GetNumRows() == 0)
	{
		currentGameType = nullptr;
	}
	else
	{
		gameTypesListBox->SelectByIndex(0);
		onGameTypesListSelect((Controls::Base*)gameTypesListBox->GetRow(0));
	}

	
}



void CustomGameEditorControl::onSaveButton(Base* control)
{//=========================================================================================================================

 //save current game to xml in userdata, maybe upload to server as userid:gametype if user is logged in
 //if current game with that name exists in either folder, say this name is already being used
	saveAllToCurrentGameType();

	//save to xml
	saveCurrentGameTypeToXML();

}

void CustomGameEditorControl::onUploadButton(Base* control)
{//=========================================================================================================================

	saveAllToCurrentGameType();


	GameType g;
	g = *currentGameType;

	std::stringstream ss;
	boost::archive::xml_oarchive oarchive(ss);
	oarchive << BOOST_SERIALIZATION_NVP(g);

	string zip = FileUtils::zipStringToBase64String(ss.str());


	//GameType:XML:name:uuid
	bobsGame->getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(BobNet::Bobs_Game_GameTypesAndSequences_Upload_Request+"GameType:"+ zip + ":`"+g.name+"`:"+g.uuid+":"+BobNet::endline);

	string response = "";
	int tries = 0;
	while (tries<10)
	{
		tries++;
		Main::delay(500);
		response = bobsGame->getServerConnection()->getAndResetBobsGameGameTypesAndSequencesUploadResponse_S();
		if (response != "")
		{
			break;
		}
	}

	if (response == "")response = "Did not get a response from the server. Try again later.";

	WindowControl *result = new WindowControl(GetCanvas());
	result->SetTitle("Result");
	result->SetSize(300, 60);
	result->MakeModal(true);
	result->SetPos(GLUtils::getViewportWidth() / 2 - 150, GLUtils::getViewportHeight() / 2 - 30);
	result->SetDeleteOnClose(true);

	Label* label = new Label(result);
	label->SetText(response);
	label->Dock(Pos::Fill);
}

void CustomGameEditorControl::onExitButton(Base* control)
{//=========================================================================================================================

 //Utility::Format(L"Window %i", m_iWindowCount)


	askToSaveBase = new WindowControl(GetCanvas());
	askToSaveBase->SetTitle("Save changes?");
	askToSaveBase->SetSize(300, 60);
	askToSaveBase->MakeModal(true);
	//exitAskToSaveWindow->Position(Pos::Center);
	askToSaveBase->SetPos(GLUtils::getViewportWidth() / 2 - 150, GLUtils::getViewportHeight() / 2 - 30);
	askToSaveBase->SetDeleteOnClose(true);
	//exitAskToSaveWindow->SetClosable(false);
	{

		askToSaveYesButton = new Button(askToSaveBase);
		askToSaveYesButton->SetText(L"Save and Leave");
		//askToSaveYesButton->SetToolTip(b->_Info.tip);
		askToSaveYesButton->Dock(Pos::Left | Pos::Center);
		askToSaveYesButton->SetWidth(120);
		askToSaveYesButton->onPress.Add(this, &CustomGameEditorControl::saveAndExit);


		askToSaveNoButton = new Button(askToSaveBase);
		askToSaveNoButton->SetText(L"Leave without saving");
		//askToSaveNoButton->SetToolTip(b->_Info.tip);
		askToSaveNoButton->Dock(Pos::Left | Pos::Center);
		askToSaveNoButton->SetWidth(150);
		askToSaveNoButton->onPress.Add(this, &CustomGameEditorControl::dontSaveAndExit);


		//		cancelExitButton = new Button(askToSaveBase);
		//		cancelExitButton->SetText(L"Cancel");
		//		//cancelExitButton->SetToolTip(b->_Info.tip);
		//		cancelExitButton->Dock(Pos::Left | Pos::Center);
		//		cancelExitButton->SetWidth(60);
		//		cancelExitButton->onPress.Add(this, &CustomGameEditorControl::cancelExit);
	}


}


void CustomGameEditorControl::saveAndExit(Base* control)
{//=========================================================================================================================
 //save the game to appdata or home/userid-gamename
 //make sure that there arent any unallowable characters, sanitize, etc
 //ask the user if they want to overwrite if the filename exists

	saveAllToCurrentGameType();

	//save to xml
	saveCurrentGameTypeToXML();

	//go to title screen
	askToSaveBase->CloseButtonPressed();
	exit = true;
}


void CustomGameEditorControl::dontSaveAndExit(Base* control)
{//=========================================================================================================================
 //go back to title screen
	askToSaveBase->CloseButtonPressed();
	exit = true;
}



void CustomGameEditorControl::doEditRotationSetWindowButton(Base* control)
{//=========================================================================================================================


	windowOpen = true;

	rotationEditorOpen = true;


	int w = GLUtils::getViewportWidth() / 4 * 3;
	int h = GLUtils::getViewportHeight() / 4 * 3;

	rotationEditWindow = new WindowControl(GetCanvas());
	{
		rotationEditWindow->SetTitle("Edit rotations and block placement");
		rotationEditWindow->SetSize(w, h);
		rotationEditWindow->MakeModal(true);
		//rotationEditWindow->Position(Pos::Center);
		rotationEditWindow->SetPos(GLUtils::getViewportWidth() / 2 - rotationEditWindow->Width() / 2, GLUtils::getViewportHeight() / 2 - rotationEditWindow->Height() / 2);
		rotationEditWindow->SetDeleteOnClose(true);
		rotationEditWindow->SetClosable(false);

		Base* rotationWindowTopBase = new Base(rotationEditWindow);
		rotationWindowTopBase->Dock(Pos::Top);
		rotationWindowTopBase->SetSize(rotationEditWindow->Width(), rotationEditWindow->Height() - 20);
		{

			Base *rotationLeftBase = new Base(rotationWindowTopBase);
			rotationLeftBase->Dock(Pos::Left);
			rotationLeftBase->SetSize(rotationWindowTopBase->Width() / 2, rotationWindowTopBase->Height());
			{

				Base *rotationListBoxBase = new Base(rotationLeftBase);
				rotationListBoxBase->Dock(Pos::Top);
				rotationListBoxBase->SetSize(rotationLeftBase->Width() - 40, rotationLeftBase->Height()/2 - 40);
				{

					//let's do a load preset button which opens a window

					Button* rotationPresetLoadButton = new Button(rotationListBoxBase);
					rotationPresetLoadButton->SetText("Load preset rotation set...");
					rotationPresetLoadButton->SetHeight(15);
					rotationPresetLoadButton->Dock(Pos::Top);
					rotationPresetLoadButton->onPress.Add(this, &CustomGameEditorControl::onOpenPresetRotationWindow);

					rotationListBox = new ListBox(rotationListBoxBase);
					{
						//rotationListBox->SetMargin(Margin(0, 0, 0, 0));
						rotationListBox->Dock(Pos::Top);
						rotationListBox->SetAllowMultiSelect(false);
						rotationListBox->SetSize(rotationListBoxBase->Width(), rotationListBoxBase->Height() - 25 - 15);



						//fill rotation list box

						for(int i=0;i<currentPieceType->rotationSet.size();i++)
						{
							Layout::TableRow *row = rotationListBox->AddItem("Rotation " + to_string(i));
							row->onRowSelected.Add(this, &CustomGameEditorControl::onRotationListRowSelect);
						}

						//currentPieceType->rotationSet;

					}


					//buttons new, delete, preview checkbox
					Base *rotationListBoxButtonBase = new Base(rotationListBoxBase);
					rotationListBoxButtonBase->Dock(Pos::Bottom);
					rotationListBoxButtonBase->SetSize(rotationListBoxBase->Width(), 20);
					{

						Button *addRotationButton = new Button(rotationListBoxButtonBase);
						addRotationButton->SetText(L"New");
						//addRotationButton->SetToolTip(b->_Info.tip);
						addRotationButton->Dock(Pos::Left | Pos::CenterV);
						//addRotationButton->SetWidth(160);
						addRotationButton->onPress.Add(this, &CustomGameEditorControl::addRotation);


						Button *deleteRotationButton = new Button(rotationListBoxButtonBase);
						deleteRotationButton->SetText(L"Delete");
						//deleteRotationButton->SetToolTip(b->_Info.tip);
						deleteRotationButton->Dock(Pos::Left | Pos::CenterV);
						//deleteRotationButton->SetWidth(240);
						deleteRotationButton->onPress.Add(this, &CustomGameEditorControl::deleteRotation);
					}

				}

				//preview which animates through rotations
				//preview speed slider ?
				//preview checkbox ?
				Base *rotationPreviewBase = new Base(rotationLeftBase);
				rotationPreviewBase->Dock(Pos::Top);
				rotationPreviewBase->SetSize(rotationLeftBase->Width(), rotationLeftBase->Height() / 2);
				{
					int minSize = min(rotationPreviewBase->Width(), rotationPreviewBase->Height() - 60);

					//Layout::Position* positioner = new Layout::Position(rotationPreviewBase);
					//positioner->Dock(Pos::Top);
					//positioner->SetSize(minSize, 20);

					Label *rotationEditorLabel = new Label(rotationPreviewBase);
					rotationEditorLabel->SetText("Preview Animation Speed");
					rotationEditorLabel->SetPos(rotationPreviewBase->X(), rotationPreviewBase->Y() + 20);
					//rotationEditorLabel->Dock(Pos::Top);
					rotationEditorLabel->SetSize(minSize, 20);

					rotationPreviewAnimationSpeedSlider = new HorizontalSlider(rotationPreviewBase);
					//rotationPreviewAnimationSpeedSlider->Dock(Pos::Top);
					rotationPreviewAnimationSpeedSlider->SetPos(rotationEditorLabel->X(), rotationEditorLabel->Y() + 20);
					rotationPreviewAnimationSpeedSlider->SetRange(0, 1);
					rotationPreviewAnimationSpeedSlider->SetSize(minSize, 20);
					rotationPreviewAnimationSpeedSlider->onValueChanged.Add(this, &CustomGameEditorControl::onRotationPreviewSpeedSliderMoved);
					rotationPreviewAnimationSpeedSlider->SetFloatValue(0.5);

					rotationPreviewRectangle = new RotationPreviewRectangle(rotationPreviewBase, "", bobsGame);
					rotationPreviewRectangle->SetColor(Color(0, 0, 0, 255));
					rotationPreviewRectangle->SetPos(rotationPreviewAnimationSpeedSlider->X(), rotationPreviewAnimationSpeedSlider->Y() + 20);
					rotationPreviewRectangle->SetSize(minSize, minSize);

				}

			}

			Base *rotationRightBase = new Base(rotationWindowTopBase);
			rotationRightBase->Dock(Pos::Left);
			rotationRightBase->SetSize(rotationWindowTopBase->Width() / 2 - 60, rotationWindowTopBase->Height()-20);
			{

				Label *rotationEditorLabel = new Label(rotationRightBase);
				rotationEditorLabel->SetText("Click here to place blocks and create a rotation state.");
				rotationEditorLabel->Dock(Pos::Top);

				//block designer
				Base *rotationEditorBase = new Base(rotationRightBase);
				rotationEditorBase->Dock(Pos::Top);
				rotationEditorBase->SetSize(rotationRightBase->Width(), rotationRightBase->Height() - 20);
				{
					
					rotationEditRectangle = new EditRectangle(rotationEditorBase, "", bobsGame);
					rotationEditRectangle->SetColor(Color(0, 0, 0, 255));
					rotationEditRectangle->SetPos(rotationEditorBase->X(), rotationEditorBase->Y());
					int minSize = min(rotationEditorBase->Width(), rotationEditorBase->Height());
					rotationEditRectangle->SetSize(minSize, minSize);
				}
			}
		}

		Base *rotationWindowBottomBase = new Base(rotationEditWindow);
		rotationWindowBottomBase->Dock(Pos::Bottom);
		rotationWindowBottomBase->SetSize(rotationEditWindow->Width(), 20);
		{
			Button *saveRotationButton = new Button(rotationWindowBottomBase);//TODO: this should be greyed out if a preset game type is selected
			saveRotationButton->SetText(L"Save and close");
			//saveRotationButton->SetToolTip(b->_Info.tip);
			saveRotationButton->Dock(Pos::Right);
			//saveRotationButton->SetWidth(160);
			saveRotationButton->onPress.Add(this, &CustomGameEditorControl::closeRotationWindow);
		}

	}

}


//void drawRect(Skin::Base* skin, float x, float y, float w, float h, float r, float g, float b, float a)
//{
//	//Color c = Color(r*255.0f, g * 255.0f, b * 255.0f, a * 255.0f);
//	//skin->GetRender()->SetDrawColor(c);
//	//skin->GetRender()->DrawFilledRect(Rect(x,y,w,h));
//
//	GLUtils::drawFilledRectXYWH(x, y, w, h, r, g, b, a);
//}

//void EditRectangle::Render(Skin::Base* skin)
//{//=========================================================================================================================
//
//	skin->GetRender()->SetDrawColor(m_Color);
//	skin->GetRender()->DrawFilledRect(GetRenderBounds());
//
//	//customGameEditor->renderRotationEditor(skin);
//}
//
//void RotationPreviewRectangle::Render(Skin::Base* skin)
//{//=========================================================================================================================
//
//	skin->GetRender()->SetDrawColor(m_Color);
//	skin->GetRender()->DrawFilledRect(GetRenderBounds());
//
//	//customGameEditor->renderRotationPreview(skin);
//}



void CustomGameEditorControl::renderRotationEditor(BobsGame *g)
{//=========================================================================================================================

	
	float sx = rotationEditRectangle->LocalPosToCanvas(rotationEditRectangle->X()).x;
	float sy = rotationEditRectangle->LocalPosToCanvas(rotationEditRectangle->Y()).y;
	float w = rotationEditRectangle->Width();
	float h = rotationEditRectangle->Height();

	//render grid

	//draw number on blocks, maybe red dot on block 0

	//need to paint a grid 2x + 1

	GLUtils::drawFilledRectXYWH(sx, sy, w, h,0,0,0,1);


	if (currentRotation == nullptr)return;

	int cells = maxNumBlocks + 2;
	if (cells % 2 == 0)cells++;
	float cellW = w / (float)cells;

	Rotation *lastRotation = nullptr;
	for(int i=0;i<currentPieceType->rotationSet.size();i++)
	{
		if(currentPieceType->rotationSet.get(i)==currentRotation)
		{
			if (i == 0)lastRotation = currentPieceType->rotationSet.get(currentPieceType->rotationSet.size()-1);
			else lastRotation = currentPieceType->rotationSet.get(i - 1);
		}
	}
	if (lastRotation != nullptr)
	{
		for (int i = 0; i < lastRotation->blockOffsets.size(); i++)
		{
			BlockOffset *b = lastRotation->blockOffsets.get(i);
			int x = b->x;
			int y = b->y;

			BobColor c = BobColor(255, 255, 255, 255);
			if (i < colors.size())c = *colors.get(i);
			GLUtils::drawFilledRectXYWH(sx + ((cells / 2) * cellW) + cellW*x, sy + ((cells / 2) * cellW) + cellW*y, cellW, cellW, c.rf(), c.gf(), c.bf(), 0.2f);
			if (i < 10)
			{
				Sprite *s = g->getSpriteFromName("Counter");
				s->drawFrameXYWH(to_string(i), sx + ((cells / 2) * cellW) + cellW*x, sy + ((cells / 2) * cellW) + cellW*y, cellW, cellW,1,1,1,0.2f);
			}
		}
	}

	
	for(int i=0; i<currentRotation->blockOffsets.size(); i++)
	{
		BlockOffset *b = currentRotation->blockOffsets.get(i);
		int x = b->x;
		int y = b->y;
		
		BobColor c = BobColor(128, 0, 128, 255);
		if(i<colors.size())c = *colors.get(i);
		GLUtils::drawFilledRectXYWH(sx + ((cells / 2) * cellW) + cellW*x, sy + ((cells / 2) * cellW) + cellW*y, cellW, cellW, c.rf(),c.gf(),c.bf(), 1.0f);
		if (i < 10)
		{
			Sprite *s = g->getSpriteFromName("Counter");
			s->drawFrameXYWH(to_string(i), sx + ((cells / 2) * cellW) + cellW*x, sy + ((cells / 2) * cellW) + cellW*y, cellW, cellW);
		}
	}

	//draw grid
	for (int x = 0; x < cells + 1; x++)
	{
		GLUtils::drawFilledRectXYWH(sx + cellW * x, sy, 1, h, 1.0f, 1.0f, 1.0f, 1.0f);
	}

	for (int y = 0; y < cells + 1; y++)
	{
		GLUtils::drawFilledRectXYWH(sx, sy + cellW * y, w, 1, 1.0f, 1.0f, 1.0f, 1.0f);
	}


	GLUtils::drawFilledRectXYWH(sx + ((cells / 2) * cellW) + cellW * 0 + cellW/3, sy + ((cells / 2) * cellW) + cellW * 0 + cellW / 3, cellW/3, cellW/3, 0, 1, 0, 0.5f);

}

void CustomGameEditorControl::renderRotationPreview()
{//=========================================================================================================================

	float sx = rotationPreviewRectangle->LocalPosToCanvas(rotationEditRectangle->X()).x;
	float sy = rotationPreviewRectangle->LocalPosToCanvas(rotationEditRectangle->Y()).y;
	float w = rotationPreviewRectangle->Width();
	float h = rotationPreviewRectangle->Height();

	GLUtils::drawFilledRectXYWH(sx, sy, w, h, 0, 0, 0, 1);

	if (currentRotation == nullptr)return;

	if (currentPreviewRotationIndex >= currentPieceType->rotationSet.size())
		currentPreviewRotationIndex = 0;

	if (currentPieceType->rotationSet.size() == 0)return;

	int cells = maxNumBlocks + 2;
	if (cells % 2 == 0)cells++;
	float cellW = w / (float)cells;

	for (int i = 0; i<currentPieceType->rotationSet.get(currentPreviewRotationIndex)->blockOffsets.size(); i++)
	{
		BlockOffset *b = currentPieceType->rotationSet.get(currentPreviewRotationIndex)->blockOffsets.get(i);
		int x = b->x;
		int y = b->y;

		BobColor c = BobColor(255, 255, 255, 255);
		if (i<colors.size())c = *colors.get(i);
		GLUtils::drawFilledRectXYWH(sx + ((cells / 2) * cellW) + cellW*x, sy + ((cells / 2) * cellW) + cellW*y, cellW, cellW, c.rf(), c.gf(), c.bf(), 1.0f);
	}

	long long startTime = lastPreviewTime;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	if (previewSpeed > 0 && ticksPassed > 500 * (1.0f - previewSpeed))
	{
		lastPreviewTime = currentTime;
		currentPreviewRotationIndex++;
	}

}


void CustomGameEditorControl::updateRotationEditor()
{//=========================================================================================================================

	maxNumBlocks = 0;
	for(int i=0;i<currentPieceType->rotationSet.size();i++)
	{
		Rotation *r = currentPieceType->rotationSet.get(i);

		int num = r->blockOffsets.size();
		maxNumBlocks = max(num, maxNumBlocks);
	}

}

void EditRectangle::OnMouseClickLeft(int x, int y, bool bDown)
{//=========================================================================================================================
	bobsGame->customGameEditor->onRotationEditMouseClick(x, y, bDown);
}

void CustomGameEditorControl::onRotationEditMouseClick(int x, int y, bool bDown)
{//=========================================================================================================================

	//if block exists at offset, remove

	//if not, add

	if (bDown)return;

	//handle mouse clicks

	//if click on existing block, remove it

	float sx = rotationEditRectangle->LocalPosToCanvas(rotationEditRectangle->X()).x;
	float sy = rotationEditRectangle->LocalPosToCanvas(rotationEditRectangle->Y()).y;
	float w = rotationEditRectangle->Width();
	//float h = rotationEditRectangle->Height();

	int cells = maxNumBlocks + 2;
	if (cells % 2 == 0)cells ++;
	float cellW = w / (float)cells;

//	//draw grid
//	for (int x = 0; x < cells + 1; x++)
//	{
//		GLUtils::drawFilledRectXYWH(sx + cellW * x, sy, 1, h, 1.0f, 1.0f, 1.0f, 1.0f);
//	}
//
//	for (int y = 0; y < cells + 1; y++)
//	{
//		GLUtils::drawFilledRectXYWH(sx, sy + cellW * y, w, 1, 1.0f, 1.0f, 1.0f, 1.0f);
//	}

	bool found = false;

	if (currentRotation == nullptr)return;

	for (int i = 0; i<currentRotation->blockOffsets.size(); i++)
	{
		BlockOffset *b = currentRotation->blockOffsets.get(i);
		int bx = b->x;
		int by = b->y;

		float x0 = sx + ((cells / 2) * cellW) + cellW*bx;
		float x1 = x0 + cellW;
		float y0 = sy + ((cells / 2) * cellW) + cellW*by;
		float y1 = y0 + cellW;

		if(x > x0 && x < x1 && y > y0 && y < y1)
		{
			found = true;
			currentRotation->blockOffsets.removeAt(i);
			i--;
		}
	}

	if(found==false)
	{
		BlockOffset *b = new BlockOffset();
		b->x = floor((x - sx - (cells / 2) * cellW) / cellW);
		b->y = floor((y - sy - (cells / 2) * cellW) / cellW);

		currentRotation->blockOffsets.add(b);
	}
}


void CustomGameEditorControl::onRotationPreviewSpeedSliderMoved(Base* control)
{//=========================================================================================================================

	Gwen::Controls::Slider* pSlider = (Gwen::Controls::Slider*) control;
	previewSpeed = pSlider->GetFloatValue();

	//previewSpeed

}


void CustomGameEditorControl::onRotationListRowSelect(Base* control)
{//=========================================================================================================================



	Layout::TableRow* row = (Layout::TableRow*)control;
	string name = row->GetText(0).c_str();

	string num = name.substr(name.find(" ") + 1);
	
	int i = 0;
	try
	{
		i = stoi(num);
	}
	catch(exception)
	{
		BobsGame::log.error("Could not find rotation with num " + num);
		return;
	}


	currentRotation = currentPieceType->rotationSet.get(i);

}


void CustomGameEditorControl::addRotation(Base* control)
{//=========================================================================================================================

	//add number
	Rotation *r = new Rotation();
	currentPieceType->rotationSet.add(r);
	
	Layout::TableRow *row = rotationListBox->AddItem("Rotation " + to_string(currentPieceType->rotationSet.size()-1));
	row->onRowSelected.Add(this, &CustomGameEditorControl::onRotationListRowSelect);
	
	rotationListBox->SetSelectedRow(row);
	onRotationListRowSelect(row);
}


void CustomGameEditorControl::deleteRotation(Base* control)
{//=========================================================================================================================
	//delete number

	if (rotationListBox->IsAnyRowSelected() == false)return;

	Layout::TableRow* row = rotationListBox->GetSelectedRow();
	string name = row->GetText(0).c_str();


	string num = name.substr(name.find(" ") + 1);

	int i = 0;
	try
	{
		i = stoi(num);
	}
	catch (exception)
	{
		BobsGame::log.error("Could not find rotation with num " + num);
		return;
	}

	currentPieceType->rotationSet.removeAt(i);
	

	rotationListBox->UnselectAll();

	//delete it from the list
	rotationListBox->RemoveItem(rotationListBox->GetRow(rotationListBox->GetNumRows()-1));//delete the last row because it is based on name so all teh numbers will just decrement
	GetCanvas()->DoThink();

	if (rotationListBox->GetNumRows() == 0)
	{
		currentRotation = nullptr;
	}
	else
	{
		rotationListBox->SelectByIndex(0);
		onRotationListRowSelect((Controls::Base*)rotationListBox->GetRow(0));
	}

}


void CustomGameEditorControl::closeRotationWindow(Base* control)
{//=========================================================================================================================

	//need to save lastRotation, numBlocks
	rotationEditorOpen = false;
	//currentPieceType->numBlocks = maxNumBlocks;
	currentRotation = nullptr;

	rotationEditWindow->CloseButtonPressed();
	windowOpen = false;
	initPreviewGame();
}

void CustomGameEditorControl::onOpenPresetRotationWindow(Base* control)
{//=========================================================================================================================
	//modal window
	//listbox populated with rotation sets from built in games
	//ok button
	//cancel button

	windowOpen = true;

	presetRotationWindowOpen = true;

	int w = GLUtils::getViewportWidth() / 2;
	int h = GLUtils::getViewportHeight() / 2;

	rotationPresetSelectWindow = new WindowControl(GetCanvas());
	{
		rotationPresetSelectWindow->SetTitle("Select preset rotation");
		rotationPresetSelectWindow->SetSize(w, h);
		rotationPresetSelectWindow->MakeModal(true);
		//rotationPresetSelectWindow->Position(Pos::Center);
		rotationPresetSelectWindow->SetPos(GLUtils::getViewportWidth() / 2 - rotationPresetSelectWindow->Width() / 2, GLUtils::getViewportHeight() / 2 - rotationPresetSelectWindow->Height() / 2);
		rotationPresetSelectWindow->SetDeleteOnClose(true);
		rotationPresetSelectWindow->SetClosable(false);


		Base *rotationListBoxBase = new Base(rotationPresetSelectWindow);
		rotationListBoxBase->Dock(Pos::Top);
		rotationListBoxBase->SetSize(rotationPresetSelectWindow->Width() - 40, rotationPresetSelectWindow->Height() - 40);
		{

			rotationPresetListBox = new ListBox(rotationListBoxBase);
			{
				//rotationListBox->SetMargin(Margin(0, 0, 0, 0));
				rotationPresetListBox->Dock(Pos::Top);
				rotationPresetListBox->SetAllowMultiSelect(false);
				rotationPresetListBox->SetSize(rotationListBoxBase->Width(), rotationListBoxBase->Height() - 25 - 15);



				

				for (int i = 0; i < rotationSets.size(); i++)
				{
					RotationSet r = rotationSets.get(i);
					//Layout::TableRow *row =
                    rotationPresetListBox->AddItem(r.name);
				}

//				//fill rotation list box
//				for(int i=0;i<loadedGameTypes.size();i++)
//				{
//					GameType *s = loadedGameTypes.get(i);
//					if(s->builtInType)
//					{
//						for(int n=0;n<s->pieceTypes.size();n++)
//						{
//							PieceType *p = s->pieceTypes.get(n);
//
//							Layout::TableRow *row = rotationPresetListBox->AddItem(p->rotationSet.name);
//							//row->onRowSelected.Add(this, &CustomGameEditorControl::onRotationListRowSelect);
//						}
//					}
//
//				}
			}
		}

		Base *rotationListBoxButtonBase = new Base(rotationPresetSelectWindow);
		rotationListBoxButtonBase->Dock(Pos::Bottom);
		rotationListBoxButtonBase->SetSize(rotationPresetSelectWindow->Width(), 20);
		{


			Button *cancelButton = new Button(rotationListBoxButtonBase);
			cancelButton->SetText(L"Cancel");
			//cancelButton->SetToolTip(b->_Info.tip);
			cancelButton->Dock(Pos::Right | Pos::CenterV);
			//cancelButton->SetWidth(240);
			cancelButton->onPress.Add(this, &CustomGameEditorControl::onSelectedPresetRotationCancel);

			Button *okButton = new Button(rotationListBoxButtonBase);
			okButton->SetText(L"OK");
			//okButton->SetToolTip(b->_Info.tip);
			okButton->Dock(Pos::Right | Pos::CenterV);
			//okButton->SetWidth(160);
			okButton->onPress.Add(this, &CustomGameEditorControl::onSelectedPresetRotationOK);
		}
	}

}

void CustomGameEditorControl::onSelectedPresetRotationOK(Base* control)
{//=========================================================================================================================

	//get current selected preset rotation from listbox

	//if nothing selected dont close


	if (rotationPresetListBox->IsAnyRowSelected() == false)return;

	
	Layout::TableRow* row = rotationPresetListBox->GetSelectedRow();
	string name = row->GetText(0).c_str();
	

	//delete current piece rotation set
	//fill it with the selected preset rotations
	currentPieceType->rotationSet.clear();

	rotationListBox->Clear();
	GetCanvas()->DoThink();

//	for (int i = 0; i<loadedGameTypes.size(); i++)
//	{
//		GameType *s = loadedGameTypes.get(i);
//		if (s->builtInType)
//		{
//			for (int n = 0; n<s->pieceTypes.size(); n++)
//			{
//				PieceType *p = s->pieceTypes.get(n);
//
//				if(p->rotationSet.name==name)
//				{
//				
//					for(int x=0;x<p->rotationSet.size();x++)
//					{
//						Rotation *r = new Rotation(*p->rotationSet.get(x));
//						currentPieceType->rotationSet.add(r);
//					}
//				}
//			}
//		}
//	}

	for (int i = 0; i < rotationSets.size(); i++)
	{
		RotationSet rs = rotationSets.get(i);
		if(rs.name==name)
		{
						
			for(int x=0;x<rs.size();x++)
			{
				Rotation *rotation = new Rotation(*rs.get(x));
				currentPieceType->rotationSet.add(rotation);
			}
		}
	}

	for (int i = 0; i<currentPieceType->rotationSet.size(); i++)
	{
		
		Layout::TableRow *r = rotationListBox->AddItem("Rotation " + to_string(i));
		r->onRowSelected.Add(this, &CustomGameEditorControl::onRotationListRowSelect);

		if (i == 0) 
		{
			rotationListBox->SetSelectedRow(r);
			onRotationListRowSelect((Controls::Base*)rotationListBox->GetRow(0));
		}
	}
	

	//close window
	rotationPresetSelectWindow->CloseButtonPressed();
	presetRotationWindowOpen = false;
	windowOpen = false;
	initPreviewGame();
}

//=========================================================================================================================
void CustomGameEditorControl::onSelectedPresetRotationCancel(Base* control)
{//=========================================================================================================================
	//just close without making any changes
	rotationPresetSelectWindow->CloseButtonPressed();
	presetRotationWindowOpen = false;
	windowOpen = false;
	initPreviewGame();
}

//=========================================================================================================================
void CustomGameEditorControl::onPreviewButton(Base* control)
{//=========================================================================================================================
 //we basically already have the settings in memory so we can just create a new game instance and set the currentGameType to these ones
 //but we need to make a game sequence that is only this game
	saveAllToCurrentGameType();
	initPreviewGame();
}


//=========================================================================================================================
void CustomGameEditorControl::initPreviewGame()
{//=========================================================================================================================
	//TODO: also should have options for speeding up gameplay or playing automatically and resetting after x pieces, maybe seeing changes in realtime.

	//need to render game board into fbo
	bobsGame->initPlayer();
	bobsGame->getPlayer1Game()->currentGameType = (currentGameType);
	bobsGame->getPlayer1Game()->dontResetNextPieces = true;
	bobsGame->getPlayer1Game()->resetNextPieces();
	//bobsGame->getPlayer1Game()->grid->reformat(0,0);
	if (bobsGame->getPlayer1Game()->currentGameSequence == nullptr)
	{
		bobsGame->getPlayer1Game()->currentGameSequence = new GameSequence();
		bobsGame->getPlayer1Game()->currentGameSequence->gameTypes.add(currentGameType);
		bobsGame->getPlayer1Game()->currentGameSequence->currentDifficultyName = "Beginner";
		if (currentDifficultyType != nullptr)bobsGame->getPlayer1Game()->currentGameSequence->currentDifficultyName = currentDifficultyType->name;
		bobsGame->getPlayer1Game()->currentGameSequence->endlessMode = true;
	}


	//if selected piece tab, make new random piece with selected piecetype
	//else if block tab make new one random piece with all selected blocktype
	//else if settings tab dont do anything, let it choose normally

//	if(leftBaseTabControl->GetCurrentButton()==pieceTab && pieceSelectionListBox->IsAnyRowSelected())
//	{
//		ArrayList<BlockType*>blockTypes = bobsGame->getPlayer1Game()->getCurrentGameType()->getNormalBlockTypes();
//		if (currentPieceType != nullptr)bobsGame->getPlayer1Game()->nextPieces.add(new Piece(bobsGame->getPlayer1Game(), bobsGame->getPlayer1Game()->grid, currentPieceType, blockTypes));
//	}
//	else
//	if (leftBaseTabControl->GetCurrentButton() == blockTab && blockSelectionListBox->IsAnyRowSelected())
//	{
//		ArrayList<PieceType*>pieceTypes = bobsGame->getPlayer1Game()->getCurrentGameType()->getNormalPieceTypes();
//		if (currentBlockType != nullptr)bobsGame->getPlayer1Game()->nextPieces.add(new Piece(bobsGame->getPlayer1Game(), bobsGame->getPlayer1Game()->grid, bobsGame->getPlayer1Game()->grid->getRandomPieceType(pieceTypes), currentBlockType));
//	}
//	else
//	{
//		
//	}

	ArrayList<BlockType*>blockTypes = bobsGame->getPlayer1Game()->currentGameType->getNormalBlockTypes(bobsGame->getPlayer1Game()->getCurrentDifficulty());
	ArrayList<PieceType*>pieceTypes = bobsGame->getPlayer1Game()->currentGameType->getNormalPieceTypes(bobsGame->getPlayer1Game()->getCurrentDifficulty());

	PieceType *p = bobsGame->getPlayer1Game()->grid->getRandomPieceType(pieceTypes);
	BlockType *b = bobsGame->getPlayer1Game()->grid->getRandomBlockType(blockTypes);

	if (currentPieceType != nullptr)p = currentPieceType;
	if (currentBlockType != nullptr)b = currentBlockType;
			
	bobsGame->getPlayer1Game()->nextPieces.add(new Piece(bobsGame->getPlayer1Game(), bobsGame->getPlayer1Game()->grid, p, b));

}


//
//void CustomGameEditorControl::onAddDifficultyButton(Base* control)
//{//=========================================================================================================================
// //add a generic difficulty to the bottom of the list and populate the fields
//
//	DifficultyType *b = new DifficultyType();
//
//
//	string newName = "New Difficulty";
//	{
//		int n = 0;
//		for (int i = 0; i < currentGameType->difficultyTypes.size(); i++)
//		{
//			DifficultyType *bt = currentGameType->difficultyTypes.get(i);
//			if (bt->name == newName)
//			{
//				newName = newName + to_string(n);
//				n++;
//				i = 0;
//			}
//		}
//	}
//
//	b->name = newName;
//	currentGameType->difficultyTypes.add(b);
//
//
//	Layout::TableRow *row = difficultySelectionListBox->AddItem(b->name);
//	row->onRowSelected.Add(this, &CustomGameEditorControl::onDifficultyListRowSelect);
//	difficultySelectionListBox->SetSelectedRow(row);
//	onDifficultyListRowSelect(row);
//}
//
//void CustomGameEditorControl::onDeleteDifficultyButton(Base* control)
//{//=========================================================================================================================
//
//
//	if (difficultySelectionListBox->IsAnyRowSelected() == false)return;
//
//	Layout::TableRow* row = difficultySelectionListBox->GetSelectedRow();
//	string name = row->GetText(0).c_str();
//
//	DifficultyType *bt = getDifficultyTypeByName(name);
//
//	if (bt == nullptr)
//	{
//		BobsGame::log.error("Could not find difficultyType with name:" + name);
//		return;
//	}
//
//	if (currentGameType->difficultyTypes.contains(bt))currentGameType->difficultyTypes.remove(bt);
//
//
//
//	//refresh DifficultyPropTree, just save and reselect
//	saveDifficultyPropTreeToCurrentDifficultyType();
//	onDifficultyListRowSelect(difficultySelectionListBox->GetSelectedRow());
//
//
//	difficultySelectionListBox->UnselectAll();
//
//	//delete it from the list
//	difficultySelectionListBox->RemoveItem(row);
//	GetCanvas()->DoThink();
//
//	//if no difficultys in the list, add an empty difficultytype to the list and select it
//	//otherwise try to select this position, if nothing there select above difficulty
//
//	if (difficultySelectionListBox->GetNumRows() == 0)
//	{
//		//onAddDifficultyButton(nullptr);
//		currentDifficultyType = nullptr;
//
//		if (difficultyPropTree != nullptr)
//		{
//			difficultyPropTree->DelayedDelete();
//			GetCanvas()->DoThink();
//			//delete difficultyPropTree;
//			difficultyPropTree = nullptr;
//		}
//	}
//	else
//	{
//		difficultySelectionListBox->SelectByIndex(0);
//		onDifficultyListRowSelect((Controls::Base*)difficultySelectionListBox->GetRow(0));
//	}
//}

void CustomGameEditorControl::onDifficultyListRowSelect(Base* control)
{//=========================================================================================================================

	if (control == nullptr)return;

	if (currentDifficultyType != nullptr)
	{
		saveDifficultyPropTreeToCurrentDifficultyType();
	}

	Layout::TableRow* row = (Layout::TableRow*)control;
	string name = row->GetText(0).c_str();

	DifficultyType *bt = getDifficultyTypeByName(name);

	if (bt == nullptr)
	{
		BobsGame::log.error("Could not find difficultyType with name:" + name);
		return;
	}
	currentDifficultyType = bt;


	//populate all the difficultyType fields
	initDifficultyPropTree(bt);

	if(bobsGame->getPlayer1Game()->currentGameSequence!=nullptr)bobsGame->getPlayer1Game()->currentGameSequence->currentDifficultyName = bt->name;
}


void CustomGameEditorControl::initDifficultySelectionListBox()
{//=========================================================================================================================

	currentDifficultyType = nullptr;
	difficultySelectionListBox->Clear();

	GetCanvas()->DoThink();

	Layout::TableRow* row;



	for (int i = 0; i<currentGameType->difficultyTypes.size(); i++)
	{
		DifficultyType *bt = currentGameType->difficultyTypes.get(i);
		row = difficultySelectionListBox->AddItem(bt->name);
		row->onRowSelected.Add(this, &CustomGameEditorControl::onDifficultyListRowSelect);
		if (i == 0)
		{
			difficultySelectionListBox->SetSelectedRow(row);
			onDifficultyListRowSelect(row);
		}
	}
}

void CustomGameEditorControl::initDifficultyPropTree(DifficultyType *b)
{//=========================================================================================================================
	if (difficultyPropTree != nullptr)
	{
		difficultyPropTree->DelayedDelete();
		GetCanvas()->DoThink();
		//delete difficultyPropTree;
		difficultyPropTree = nullptr;
	}

	if (b == nullptr)return;

	difficultyPropTree = new PropertyTree(difficultyPropertiesScrollControl);
	//difficultyPropTree->Dock(Pos::Fill);
	difficultyPropTree->SetWidth(400);
	//difficultyPropTree->SetHeight(1000);
	{

		int n = 0;
		Properties* p;
		n++; p = difficultyPropTree->Add("Difficulty Properties");
		{
			//n++; p->Add(b->name_Info.label, string(b->name))->SetToolTip(b->name_Info.tip);


			n++; p->Add(b->initialLineDropSpeedTicks_Info.label, to_string(b->initialLineDropSpeedTicks))->SetToolTip(b->initialLineDropSpeedTicks_Info.tip);
			n++; p->Add(b->minimumLineDropSpeedTicks_Info.label, to_string(b->minimumLineDropSpeedTicks))->SetToolTip(b->minimumLineDropSpeedTicks_Info.tip);

			n++; p->Add(b->maxStackRise_Info.label, to_string(b->maxStackRise))->SetToolTip(b->maxStackRise_Info.tip);
			n++; p->Add(b->minStackRise_Info.label, to_string(b->minStackRise))->SetToolTip(b->minStackRise_Info.tip);

			n++; p->Add(b->extraStage1Level_Info.label, to_string(b->extraStage1Level))->SetToolTip(b->extraStage1Level_Info.tip);
			n++; p->Add(b->extraStage2Level_Info.label, to_string(b->extraStage2Level))->SetToolTip(b->extraStage2Level_Info.tip);
			n++; p->Add(b->extraStage3Level_Info.label, to_string(b->extraStage3Level))->SetToolTip(b->extraStage3Level_Info.tip);
			n++; p->Add(b->extraStage4Level_Info.label, to_string(b->extraStage4Level))->SetToolTip(b->extraStage4Level_Info.tip);
			n++; p->Add(b->creditsLevel_Info.label, to_string(b->creditsLevel))->SetToolTip(b->creditsLevel_Info.tip);

			n++; p->Add(b->playingFieldGarbageSpawnRuleAmount_Info.label, to_string(b->playingFieldGarbageSpawnRuleAmount))->SetToolTip(b->playingFieldGarbageSpawnRuleAmount_Info.tip);
			n++; p->Add(b->maximumBlockTypeColors_Info.label, to_string(b->maximumBlockTypeColors))->SetToolTip(b->maximumBlockTypeColors_Info.tip);

			n++; p->Add(b->randomlyFillGridAmount_Info.label, to_string(b->randomlyFillGridAmount))->SetToolTip(b->randomlyFillGridAmount_Info.tip);
			n++; p->Add(b->randomlyFillStackAmount_Info.label, to_string(b->randomlyFillStackAmount))->SetToolTip(b->randomlyFillStackAmount_Info.tip);

			{
				string typesString = "";
				for (int i = 0; i < b->pieceTypesToDisallow_UUID.size(); i++)
				{
					PieceType *bt = currentGameType->getPieceTypeByUUID(b->pieceTypesToDisallow_UUID.get(i));
					string pieceName = "";
					if (bt != nullptr)pieceName = bt->name;
					else pieceName = "ERROR";
					typesString = typesString + pieceName + ",";
				}
				Property::TextWithButton *tb = new Property::TextWithButton(p, "Edit");
				n++; p->Add(b->pieceTypesToDisallow_Info.label, tb, typesString)->SetToolTip(b->pieceTypesToDisallow_Info.tip);
				tb->GetButton()->onPress.Add(this, &CustomGameEditorControl::doDifficultyDisallowPieceTypesSelectionWindowButton);
			}


			{
				string typesString = "";
				for (int i = 0; i < b->blockTypesToDisallow_UUID.size(); i++)
				{
					BlockType *bt = currentGameType->getBlockTypeByUUID(b->blockTypesToDisallow_UUID.get(i));
					string blockName = "";
					if (bt != nullptr)blockName = bt->name;
					else blockName = "ERROR";
					typesString = typesString + blockName + ",";
				}
				Property::TextWithButton *tb = new Property::TextWithButton(p, "Edit");
				n++; p->Add(b->blockTypesToDisallow_Info.label, tb, typesString)->SetToolTip(b->blockTypesToDisallow_Info.tip);
				tb->GetButton()->onPress.Add(this, &CustomGameEditorControl::doDifficultyDisallowBlockTypesSelectionWindowButton);
			}

			p->SetSplitWidth(200);
		}


		difficultyPropTree->ExpandAll();

		difficultyPropTree->SetHeight(n * fontHeight);
		difficultyPropTreeNumChildren = n;
	}

}


void CustomGameEditorControl::saveDifficultyPropTreeToCurrentDifficultyType()
{//=========================================================================================================================
	if (currentDifficultyType == nullptr)return;
	if (difficultyPropTree == nullptr)return;

	//parse all fields
	//if name equals any other difficultytype names besides currentDifficultyType add a number afterwards until it doesnt
	Properties* p = difficultyPropTree->Find("Difficulty Properties");
	if (p == nullptr)
	{
		BobsGame::log.error("Could not find Difficulty Properties");
		return;
	}

//
//	PropertyRow* pr = p->Find(currentDifficultyType->name_Info.label);
//	string difficultyTypeName = pr->GetProperty()->GetPropertyValue().c_str();
//	if (difficultyTypeName == "")difficultyTypeName = "Unnamed Difficulty";
//	int n = 0;
//	for (int i = 0; i < currentGameType->difficultyTypes.size(); i++)
//	{
//		DifficultyType *bt = currentGameType->difficultyTypes.get(i);
//		if (bt != currentDifficultyType && bt->name == difficultyTypeName)
//		{
//			difficultyTypeName = difficultyTypeName + to_string(n);
//
//			n++;
//			i = 0;
//		}
//	}
//
//	//replace name in difficultyType
//	currentDifficultyType->name = difficultyTypeName;
//
//	for (int i = 0; i<currentGameType->difficultyTypes.size(); i++)
//	{
//		DifficultyType *bt = currentGameType->difficultyTypes.get(i);
//		if (bt == currentDifficultyType)
//		{
//			difficultySelectionListBox->GetTable()->GetRow(i)->SetCellText(0, difficultyTypeName);
//		}
//	}




	DifficultyType defaultDifficultyType;


	try {
		currentDifficultyType->initialLineDropSpeedTicks = stoi(p->Find(currentDifficultyType->initialLineDropSpeedTicks_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->initialLineDropSpeedTicks = defaultDifficultyType.initialLineDropSpeedTicks; }

	try {
		currentDifficultyType->minimumLineDropSpeedTicks = stoi(p->Find(currentDifficultyType->minimumLineDropSpeedTicks_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->minimumLineDropSpeedTicks = defaultDifficultyType.minimumLineDropSpeedTicks; }

	try {
		currentDifficultyType->maxStackRise = stoi(p->Find(currentDifficultyType->maxStackRise_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->maxStackRise = defaultDifficultyType.maxStackRise; }

	try {
		currentDifficultyType->minStackRise = stoi(p->Find(currentDifficultyType->minStackRise_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->minStackRise = defaultDifficultyType.minStackRise; }

	try {
		currentDifficultyType->extraStage1Level = stoi(p->Find(currentDifficultyType->extraStage1Level_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->extraStage1Level = defaultDifficultyType.extraStage1Level; }

	try {
		currentDifficultyType->extraStage2Level = stoi(p->Find(currentDifficultyType->extraStage2Level_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->extraStage2Level = defaultDifficultyType.extraStage2Level; }

	try {
		currentDifficultyType->extraStage3Level = stoi(p->Find(currentDifficultyType->extraStage3Level_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->extraStage3Level = defaultDifficultyType.extraStage3Level; }

	try {
		currentDifficultyType->extraStage4Level = stoi(p->Find(currentDifficultyType->extraStage4Level_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->extraStage4Level = defaultDifficultyType.extraStage4Level; }

	try {
		currentDifficultyType->creditsLevel = stoi(p->Find(currentDifficultyType->creditsLevel_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->creditsLevel = defaultDifficultyType.creditsLevel; }

	try {
		currentDifficultyType->playingFieldGarbageSpawnRuleAmount = stoi(p->Find(currentDifficultyType->playingFieldGarbageSpawnRuleAmount_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->playingFieldGarbageSpawnRuleAmount = defaultDifficultyType.playingFieldGarbageSpawnRuleAmount; }

	try {
		currentDifficultyType->maximumBlockTypeColors = stoi(p->Find(currentDifficultyType->maximumBlockTypeColors_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->maximumBlockTypeColors = defaultDifficultyType.maximumBlockTypeColors; }

	try {
		currentDifficultyType->randomlyFillGridAmount = stoi(p->Find(currentDifficultyType->randomlyFillGridAmount_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->randomlyFillGridAmount = defaultDifficultyType.randomlyFillGridAmount; }

	try {
		currentDifficultyType->randomlyFillStackAmount = stoi(p->Find(currentDifficultyType->randomlyFillStackAmount_Info.label)->GetProperty()->GetPropertyValue().c_str());
	}
	catch (exception) { currentDifficultyType->randomlyFillStackAmount = defaultDifficultyType.randomlyFillStackAmount; }

	//these are filled in directly from the edit window
	//pieceTypesToDisallow
	//blockTypesToDisallow



}


void CustomGameEditorControl::doDifficultyDisallowPieceTypesSelectionWindowButton(Base* control)
{//=========================================================================================================================

	windowOpen = true;
	//open window with list of piecetypes in it, and empty list in it, with add-> <-remove buttons

	makeSelectionWindow("Edit Difficulty Disallow PieceTypes");

	for (int i = 0; i < currentGameType->pieceTypes.size(); i++)
	{
		PieceType *pt = currentGameType->pieceTypes.get(i);
		selectListBox->AddItem(pt->name, pt->uuid);
	}

	for (int i = 0; i < currentDifficultyType->pieceTypesToDisallow_UUID.size(); i++)
	{
		PieceType *pt = currentGameType->getPieceTypeByUUID(currentDifficultyType->pieceTypesToDisallow_UUID.get(i));
		if (pt != nullptr)
		{
			chosenTypesListBox->AddItem(pt->name, pt->uuid);
		}
	}

	selectAddButton->onPress.Add(this, &CustomGameEditorControl::addType);
	selectRemoveButton->onPress.Add(this, &CustomGameEditorControl::removeType);
	selectConfirmButton->onPress.Add(this, &CustomGameEditorControl::saveDisallowPieceTypes);
	//currentBlockType_makePieceTypeWhenCleared;
}



void CustomGameEditorControl::saveDisallowPieceTypes(Base* control)
{//=========================================================================================================================

	currentDifficultyType->pieceTypesToDisallow_UUID.clear();

	for (int i = 0; i<chosenTypesListBox->GetNumRows(); i++)
	{
		Layout::TableRow* row = chosenTypesListBox->GetRow(i);
		string uuid = row->GetName().c_str();

		PieceType *pt = getPieceTypeByUUID(uuid);

		if (pt != nullptr)currentDifficultyType->pieceTypesToDisallow_UUID.add(pt->uuid);
	}


	Properties* p = difficultyPropTree->Find("Difficulty Properties");
	PropertyRow* pr = p->Find(currentDifficultyType->pieceTypesToDisallow_Info.label);
	{
		string typesString = "";
		for (int i = 0; i < currentDifficultyType->pieceTypesToDisallow_UUID.size(); i++)
		{
			PieceType *pt = currentGameType->getPieceTypeByUUID(currentDifficultyType->pieceTypesToDisallow_UUID.get(i));
			string pieceName = "";
			if (pt != nullptr)pieceName = pt->name;
			else pieceName = "ERROR";
			typesString = typesString + pieceName + ",";
		}

		pr->GetProperty()->SetPropertyValue(typesString);
	}

	selectWindow->CloseButtonPressed();
	windowOpen = false;
	initPreviewGame();
}

void CustomGameEditorControl::doDifficultyDisallowBlockTypesSelectionWindowButton(Base* control)
{//=========================================================================================================================

	windowOpen = true;
	//open window with list of piecetypes in it, and empty list in it, with add-> <-remove buttons

	makeSelectionWindow("Edit Difficulty Disallow BlockTypes");

	for (int i = 0; i < currentGameType->blockTypes.size(); i++)
	{
		BlockType *pt = currentGameType->blockTypes.get(i);
		selectListBox->AddItem(pt->name, pt->uuid);
	}

	for (int i = 0; i < currentDifficultyType->blockTypesToDisallow_UUID.size(); i++)
	{
		BlockType *pt = currentGameType->getBlockTypeByUUID(currentDifficultyType->blockTypesToDisallow_UUID.get(i));
		if (pt != nullptr)
		{
			chosenTypesListBox->AddItem(pt->name, pt->uuid);
		}
	}

	selectAddButton->onPress.Add(this, &CustomGameEditorControl::addType);
	selectRemoveButton->onPress.Add(this, &CustomGameEditorControl::removeType);
	selectConfirmButton->onPress.Add(this, &CustomGameEditorControl::saveDisallowBlockTypes);
	//currentBlockType_makePieceTypeWhenCleared;
}



void CustomGameEditorControl::saveDisallowBlockTypes(Base* control)
{//=========================================================================================================================

	currentDifficultyType->blockTypesToDisallow_UUID.clear();

	for (int i = 0; i<chosenTypesListBox->GetNumRows(); i++)
	{
		Layout::TableRow* row = chosenTypesListBox->GetRow(i);
		string uuid = row->GetName().c_str();

		BlockType *pt = getBlockTypeByUUID(uuid);

		if (pt != nullptr)currentDifficultyType->blockTypesToDisallow_UUID.add(pt->uuid);
	}

	Properties* p = difficultyPropTree->Find("Difficulty Properties");
	PropertyRow* pr = p->Find(currentDifficultyType->blockTypesToDisallow_Info.label);
	{
		string typesString = "";
		for (int i = 0; i < currentDifficultyType->blockTypesToDisallow_UUID.size(); i++)
		{
			BlockType *pt = currentGameType->getBlockTypeByUUID(currentDifficultyType->blockTypesToDisallow_UUID.get(i));
			string blockName = "";
			if (pt != nullptr)blockName = pt->name;
			else blockName = "ERROR";
			typesString = typesString + blockName + ",";
		}

		pr->GetProperty()->SetPropertyValue(typesString);
	}

	selectWindow->CloseButtonPressed();
	windowOpen = false;
	initPreviewGame();
}


//=========================================================================================================================
void PreviewRectangle::Render(Skin::Base* skin)
{//=========================================================================================================================

	
	m_Color = Gwen::Color(0, 0, 0, 255);
	skin->GetRender()->SetDrawColor(m_Color);
	skin->GetRender()->DrawFilledRect(GetRenderBounds());

	if (bobsGame->customGameEditor->windowOpen)return;
	m_Color = Gwen::Color(255, 255, 255, 255);
	skin->GetRender()->SetDrawColor(m_Color);
	//glPushMatrix();
	//glLoadIdentity();
	//bobsGame->setBobsGameFBOSize();
	//bobsGame->renderGameIntoFBO(bobsGame->getPlayer1Game());
	//float x0 = customGameEditor->darkRectangle->LocalPosToCanvas(customGameEditor->darkRectangle->X()).x;
	//float x1 = x0 + customGameEditor->darkRectangle->Width();
	//float y0 = customGameEditor->darkRectangle->LocalPosToCanvas(customGameEditor->darkRectangle->Y()).y;
	//float y1 = y0 + customGameEditor->darkRectangle->Height();

	//GLUtils::bindFBO(0);
	//GLUtils::drawIntoFBOAttachment(GLUtils::preColorFilterFBO); //draw to nD FBO screen texture
	//GLUtils::setPreColorFilterViewport();
	//bobsGame->drawBobsGameFBO(x0, x1, y0, y1);
	//bobsGame->drawBobsGameFBO(0,Width(),0,Height());
	//glPopMatrix();
	//customGameEditor->renderRotationPreview(skin);

	//glPushMatrix();
	//glLoadIdentity();
	//GLUtils::setPreColorFilterViewport();
	Gwen::Texture *t = new Gwen::Texture();
	t->data = (GLuint*)&GLUtils::bobsGame_mainGameFBO_Texture_Attachment0;
	skin->GetRender()->DrawTexturedRect(t, Gwen::Rect(0, Height(), Width(), 0-Height()));
	delete t;
	//glPopMatrix();
}

//=========================================================================================================================
void BobsGame::customGameEditorMenuUpdate()
{//=========================================================================================================================

 //	if (customGameEditorMenu == nullptr)
 //	{
 //		customGameEditorMenu = new Menu(this);
 //
 //		customGameEditorMenu->add("Back To Game", "Back To Game", BobColor::white);
 //		customGameEditorMenu->add("Music Volume: " + to_string((int)(music->getVolume() * 100)) + "%", "Music Volume", BobColor::white);
 //		customGameEditorMenu->add("Quit Game And Return To Title Screen", "Quit Game And Return To Title Screen", BobColor::white);
 //
 //		customGameEditorMenu->cursorPosition = customGameEditorMenuCursorPosition;
 //	}

	bool leaveMenu = false;

	if (customGameEditor == nullptr)
	{
		customGameEditor = new CustomGameEditorControl(Main::gwenCanvas, "CustomGameEditorControl", this);
		
		customGameEditor->initPreviewGame();
		//customGameEditor->loadGameTypesFromXML();

		customGameEditor->openLoadOrCreateDialog(false);

		customGameEditor->doResize();
	}
	


	if(customGameEditor!=nullptr)
	{
		customGameEditor->checkResize();

		if (customGameEditor->rotationEditorOpen)
		{
			customGameEditor->updateRotationEditor();
		}

		if (customGameEditor->windowOpen == false)
		{
			getPlayer1Game()->update(getPlayer1(), 0, 1, customGameEditor->darkRectangle->Width(), customGameEditor->darkRectangle->Height());
		}

		if (customGameEditor->exit == true)
		{

			//remove unsaved gametypes
//			for(int i=0;i<loadedGameTypes.size();i++)
//			{
//				if (loadedGameTypes.get(i)->loadedFilename == "")
//				{
//					loadedGameTypes.removeAt(i);
//					i--;
//				}
//			}

			leaveMenu = true;
			delete customGameEditor;
			customGameEditor = nullptr;
		}
	}
	




	//	if (getControlsManager()->miniGame_UP_Pressed())
	//	{
	//		customGameEditorMenu->up();
	//	}
	//
	//	if (getControlsManager()->miniGame_DOWN_Pressed())
	//	{
	//		customGameEditorMenu->down();
	//	}
	//
	
	//
	//	if (getControlsManager()->miniGame_CONFIRM_Pressed())
	//	{
	//
	//		if (customGameEditorMenu->isSelectedID("Quit Game And Return To Title Screen"))
	//		{
	//			leaveMenu = true;
	//			titleMenuShowing = true;
	//			initPlayer();
	//		}
	//
	//	}
	//
	//	if (getControlsManager()->miniGame_CANCEL_Pressed())
	//	{
	//		leaveMenu = true;
	//	}


	if (leaveMenu)
	{
		initPlayer();

		customGameEditorMenuShowing = false;

		startScreenMenuShowing = true;

		if (customGameEditorMenu != nullptr)
		{
			customGameEditorMenuCursorPosition = customGameEditorMenu->cursorPosition;
			delete customGameEditorMenu;
			customGameEditorMenu = nullptr;
		}
	}
}


//=========================================================================================================================
void BobsGame::customGameEditorMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(255, 255, 255, 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);
	//
	//	BobTexture* t = keyboardTexture;
	//
	//	if (customGameEditorMenu == nullptr)return;
	//
	//	if (t != nullptr)
	//	{
	//		customGameEditorMenu->setGraphic(t, getWidth() / 8 * 6, getHeight() / 10);
	//	}
	//
	//	customGameEditorMenu->render();


	Main::gwenCanvas->RenderCanvas();


	if (customGameEditor != nullptr)
	{
		if (customGameEditor->rotationEditorOpen && customGameEditor->presetRotationWindowOpen == false)
		{
			customGameEditor->renderRotationEditor(this);
			customGameEditor->renderRotationPreview();
		}



		//need to be able to force an FBO size
		//i should give each gamelogic its own captionmanager and render the captions in the fbo with the game 
		//so that the internals of the game doesn't need to know where it is on screen at all

		if (customGameEditor->windowOpen == false)
		{
			setBobsGameFBOSize();
			renderGameIntoFBO(getPlayer1Game(), true);
			//		float x0 = customGameEditor->darkRectangle->LocalPosToCanvas(customGameEditor->darkRectangle->X()).x;
			//		float x1 = x0 + customGameEditor->darkRectangle->Width();
			//		float y0 = customGameEditor->darkRectangle->LocalPosToCanvas(customGameEditor->darkRectangle->Y()).y;
			//		float y1 = y0 + customGameEditor->darkRectangle->Height();
			//
			GLUtils::bindFBO(GLUtils::preColorFilterFBO);
			GLUtils::drawIntoFBOAttachment(0); //draw to nD FBO screen texture
			GLUtils::setPreColorFilterViewport();
			//		drawBobsGameFBO(x0, x1, y0, y1);



		}
	}
}







