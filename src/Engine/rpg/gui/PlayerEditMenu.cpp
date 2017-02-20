#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger PlayerEditMenu::log = Logger("PlayerEditMenu");


PlayerEditMenu::PlayerEditMenu()
{ //=========================================================================================================================

	MenuPanel();

	//
	//   editPanel = new DialogLayout();
	//   editPanel->setTheme("darkPanel");
	//
	//
	//   animPanel = new DialogLayout();
	//   //animPanel.setTheme("loginpanel");
	//
	//
	//   playerEditPanelLabel = new Label("Edit Your Character");
	//   playerEditPanelLabel->setCanAcceptKeyboardFocus(false);
	//   playerEditPanelLabel->setTheme("bigLabel");
	//
	//
	//   errorLabel = new Label(" ");
	//   errorLabel->setTheme("errorLabel");
	//   errorLabel->setCanAcceptKeyboardFocus(false);
	//
	//   statusLabel = new Label(" ");
	//   statusLabel->setTheme("statusLabel");
	//   statusLabel->setCanAcceptKeyboardFocus(false);
	//
	//   //---------------------------------------------------------
	//   //player name
	//   //---------------------------------------------------------
	//   nameLabel = new Label("Player Name:");
	//   nameLabel->setCanAcceptKeyboardFocus(false);
	//
	//   nameEditField = new EditField();
	//   nameEditField->setTheme("editfield");
	//   nameEditField->setText("New Player");
	//   nameEditField->setMaxTextLength(40);
	//
	//   nameEditField->addCallback(new CallbackAnonymousInnerClassHelper(this));
	//
	//
	//   //---------------------------------------------------------
	//   //zip code
	//   //---------------------------------------------------------
	//   zipCodeEditField = new EditField();
	//   zipCodeEditField->setText("");
	//   zipCodeEditField->setMaxTextLength(40);
	//   zipCodeEditField->addCallback(new CallbackAnonymousInnerClassHelper2(this));
	//   zipCodeLabel = new Label("Zip/Postal Code:");
	//   zipCodeLabel->setLabelFor(zipCodeEditField);
	//   zipCodeLabel->setCanAcceptKeyboardFocus(false);
	//
	//   //---------------------------------------------------------
	//   //country
	//   //---------------------------------------------------------
	//   countryLabel = new Label("Country:");
	//   countryLabel->setCanAcceptKeyboardFocus(false);
	//
	//   countryStrings = CountryCodes::getCountryList();
	//
	//   countryComboBox = new ComboBox<string>(countryStrings);
	//
	//   //		countryComboBox.addCallback(new Runnable()
	//   //		{
	//   //			public void run()
	//   //			{
	//   //
	//   //			}
	//   //		});
	//
	//   //---------------------------------------------------------
	//   //add facebook account button
	//   //---------------------------------------------------------
	//
	//   addSocialAccountsLabel = new Label("Link your Facebook or Google+ Account to play with your friends!");
	//
	//   addFacebookAccountButton = new Button("Link Facebook Account");
	//   addFacebookAccountButton->setCanAcceptKeyboardFocus(false);
	//   addFacebookAccountButton->setTheme("button");
	//   addFacebookAccountButton->addCallback([&] ()
	//      {
	//         linkFacebookAccount();
	//      }
	//   );
	//   facebookAccountLabel = new Label("Facebook: Not Connected");
	//   facebookAccountLabel->setLabelFor(addFacebookAccountButton);
	//   facebookAccountLabel->setTheme("statusLabel");
	//   facebookAccountLabel->setCanAcceptKeyboardFocus(false);
	//
	//   //---------------------------------------------------------
	//   //add google plus account button
	//   //---------------------------------------------------------
	//   //		addGooglePlusAccountButton = new Button("Link Google+ Account");
	//   //		addGooglePlusAccountButton.setCanAcceptKeyboardFocus(false);
	//   //		addGooglePlusAccountButton.setTheme("button");
	//   //		addGooglePlusAccountButton.addCallback(new Runnable()
	//   //		{
	//   //			public void run()
	//   //			{
	//   //
	//   //			}
	//   //		});
	//   //		googlePlusAccountLabel = new Label("Google+: Not Connected");
	//   //		googlePlusAccountLabel.setLabelFor(addGooglePlusAccountButton);
	//   //		googlePlusAccountLabel.setTheme("statusLabel");
	//   //		googlePlusAccountLabel.setCanAcceptKeyboardFocus(false);
	//
	//
	//   //---------------------------------------------------------
	//   //random button
	//   //---------------------------------------------------------
	//   randomButton = new Button("Randomize Appearance");
	//   randomButton->setCanAcceptKeyboardFocus(false);
	//   randomButton->setTheme("button");
	//   randomButton->addCallback([&] ()
	//      {
	//         setRandomOptions();
	//
	//         redrawPlayer();
	//      }
	//   );
	//
	//   //---------------------------------------------------------
	//   //gender
	//   //---------------------------------------------------------
	//   genderLabel = new Label("Gender:");
	//   genderLabel->setCanAcceptKeyboardFocus(false);
	//
	//   genderButtons = ArrayList<ToggleButton*>(2);
	//   genderButtonLabels = ArrayList<Label*>(2);
	//
	//   genderButtonLabels[0] = new Label("Male");
	//   genderButtonLabels[1] = new Label("Female");
	//
	//   genderOptionModel = new SimpleIntegerModel(1, genderButtons->size(), 1);
	//   for (int i = 0; i < genderButtons->size(); i++)
	//   {
	//      genderButtons[i] = new ToggleButton(new OptionBooleanModel(genderOptionModel, i + 1));
	//      genderButtons[i]->setTheme("radiobutton");
	//
	//      genderButtons[i]->addCallback([&] ()
	//         {
	//            redrawPlayer();
	//         }
	//      );
	//   }
	//   genderButtonLabels[0]->setLabelFor(genderButtons[0]);
	//   genderButtonLabels[1]->setLabelFor(genderButtons[1]);
	//
	//
	//   //---------------------------------------------------------
	//   //archetype
	//   //---------------------------------------------------------
	//   archetypeLabel = new Label("Archetype:");
	//   archetypeLabel->setCanAcceptKeyboardFocus(false);
	//
	//   archetypeStrings = new SimpleChangableListModel<string>("Popular", "Hipster", "Gothy", "Tough", "Jock", "Nerdy", "Chunky", "Punk", "Skater", "Thuggin'", "Pimply", "Normal 1", "Normal 2", "Normal 3", "Normal 4", "Normal 5", "Normal 6", "Normal 7", "Normal 8", "Normal 9", "Normal 10", "Normal 11", "Normal 12", "Normal 13", "Normal 14", "Normal 15");
	//   archetypeComboBox = new ComboBox<string>(archetypeStrings);
	//
	//   archetypeComboBox->addCallback([&] ()
	//      {
	//         redrawPlayer();
	//      }
	//   );
	//
	//
	//   //---------------------------------------------------------
	//   //hair color
	//   //---------------------------------------------------------
	//   hairColorLabel = new Label("Hair Color:");
	//   hairColorLabel->setCanAcceptKeyboardFocus(false);
	//
	//   hairColorStrings = new SimpleChangableListModel<string>("Black", "Dark Brown", "Light Brown", "Blonde", "Red");
	//   hairColorComboBox = new ComboBox<string>(hairColorStrings);
	//
	//
	//   hairColorComboBox->addCallback([&] ()
	//      {
	//         redrawPlayer();
	//      }
	//   );
	//
	//
	//   //---------------------------------------------------------
	//   //eye color
	//   //---------------------------------------------------------
	//   eyeColorLabel = new Label("Eye Color:");
	//   eyeColorLabel->setCanAcceptKeyboardFocus(false);
	//
	//   eyeColorStrings = new SimpleChangableListModel<string>("Black", "Brown", "Green", "Blue", "Gray");
	//   eyeColorComboBox = new ComboBox<string>(eyeColorStrings);
	//
	//   eyeColorComboBox->addCallback([&] ()
	//      {
	//         redrawPlayer();
	//      }
	//   );
	//
	//   //---------------------------------------------------------
	//   //skin shade
	//   //---------------------------------------------------------
	//   skinColorLabel = new Label("Skin Shade:");
	//   skinColorLabel->setCanAcceptKeyboardFocus(false);
	//
	//   skinColorStrings = new SimpleChangableListModel<string>("Lightest", "Light", "Medium", "Dark", "Darkest");
	//   skinColorComboBox = new ComboBox<string>(skinColorStrings);
	//
	//   skinColorComboBox->addCallback([&] ()
	//      {
	//         redrawPlayer();
	//      }
	//   );
	//
	//   //---------------------------------------------------------
	//   //shirt color
	//   //---------------------------------------------------------
	//   shirtColorLabel = new Label("Shirt Color:");
	//   shirtColorLabel->setCanAcceptKeyboardFocus(false);
	//
	//   shirtColorStrings = new SimpleChangableListModel<string>("Black", "Gray", "White", "Brown", "Blue", "Purple", "Red", "Magenta", "Pink", "Orange", "Yellow", "Green", "Cyan");
	//   shirtColorComboBox = new ComboBox<string>(shirtColorStrings);
	//
	//
	//   shirtColorComboBox->addCallback([&] ()
	//      {
	//         redrawPlayer();
	//      }
	//   );
	//
	//   //---------------------------------------------------------
	//   //pants color
	//   //---------------------------------------------------------
	//   pantsColorLabel = new Label("Pants Color:");
	//   pantsColorLabel->setCanAcceptKeyboardFocus(false);
	//
	//   pantsColorStrings = new SimpleChangableListModel<string>("Black", "Gray", "White", "Brown", "Blue", "Purple", "Red", "Magenta", "Pink", "Orange", "Yellow", "Green", "Cyan");
	//   pantsColorComboBox = new ComboBox<string>(pantsColorStrings);
	//
	//   pantsColorComboBox->addCallback([&] ()
	//      {
	//         redrawPlayer();
	//      }
	//   );
	//
	//   //---------------------------------------------------------
	//   //shoe color
	//   //---------------------------------------------------------
	//   shoeColorLabel = new Label("Shoe Color:");
	//   shoeColorLabel->setCanAcceptKeyboardFocus(false);
	//
	//   shoeColorStrings = new SimpleChangableListModel<string>("Black", "Gray", "White", "Brown", "Blue", "Purple", "Red", "Magenta", "Pink", "Orange", "Yellow", "Green", "Cyan");
	//   shoeColorComboBox = new ComboBox<string>(shoeColorStrings);
	//
	//   shoeColorComboBox->addCallback([&] ()
	//      {
	//         redrawPlayer();
	//      }
	//   );
	//
	//
	//   //---------------------------------------------------------
	//   //ok button
	//   //---------------------------------------------------------
	//   okButton = new Button("Ok!");
	//   okButton->setCanAcceptKeyboardFocus(false);
	//   okButton->setTheme("button");
	//   okButton->addCallback([&] ()
	//      {
	//         doOKButton();
	//      }
	//   );
	//
	//
	//   //---------------------------------------------------------
	//   //layout
	//   //---------------------------------------------------------
	//
	//   animPanel->setHorizontalGroup(animPanel->createParallelGroup(animPanel->createSequentialGroup().addGap(80)));
	//
	//   animPanel->setVerticalGroup(animPanel->createSequentialGroup(animPanel->createSequentialGroup().addGap(160)));
	//
	//
	//   //---------------------------------------------------------
	//   //layout
	//   //---------------------------------------------------------
	//
	//   editPanel->setHorizontalGroup(editPanel->createParallelGroup(editPanel->createSequentialGroup().addMinGap(40), editPanel->createParallelGroup(editPanel->createSequentialGroup().addGap().addWidgets(playerEditPanelLabel).addGap(), editPanel->createSequentialGroup().addGap().addWidgets(errorLabel).addGap(), editPanel->createSequentialGroup().addGap().addWidgets(statusLabel).addGap(), editPanel->createSequentialGroup(editPanel->createSequentialGroup().addGap(), editPanel->createParallelGroup(editPanel->createSequentialGroup().addGap().addWidgets(zipCodeLabel), editPanel->createSequentialGroup().addGap().addWidgets(countryLabel), editPanel->createSequentialGroup().addGap().addWidgets(nameLabel), editPanel->createSequentialGroup().addGap().addWidgets(genderLabel), editPanel->createSequentialGroup().addGap().addWidgets(archetypeLabel), editPanel->createSequentialGroup().addGap().addWidgets(hairColorLabel), editPanel->createSequentialGroup().addGap().addWidgets(eyeColorLabel), editPanel->createSequentialGroup().addGap().addWidgets(skinColorLabel), editPanel->createSequentialGroup().addGap().addWidgets(shirtColorLabel), editPanel->createSequentialGroup().addGap().addWidgets(pantsColorLabel), editPanel->createSequentialGroup().addGap().addWidgets(shoeColorLabel)), editPanel->createParallelGroup(editPanel->createSequentialGroup().addWidgets(zipCodeEditField), editPanel->createSequentialGroup().addWidgets(countryComboBox), editPanel->createSequentialGroup().addWidgets(nameEditField), editPanel->createSequentialGroup().addGap().addWidgets(genderButtonLabels[0], genderButtons[0]).addGap().addWidgets(genderButtonLabels[1], genderButtons[1]).addGap(), editPanel->createSequentialGroup().addWidgets(archetypeComboBox), editPanel->createSequentialGroup().addWidgets(hairColorComboBox), editPanel->createSequentialGroup().addWidgets(eyeColorComboBox), editPanel->createSequentialGroup().addWidgets(skinColorComboBox), editPanel->createSequentialGroup().addWidgets(shirtColorComboBox), editPanel->createSequentialGroup().addWidgets(pantsColorComboBox), editPanel->createSequentialGroup().addWidgets(shoeColorComboBox)), editPanel->createSequentialGroup().addGap()), editPanel->createSequentialGroup().addGap().addWidgets(randomButton).addGap(), editPanel->createSequentialGroup().addGap().addWidgets(animPanel).addGap(), editPanel->createSequentialGroup().addGap().addWidgets(okButton).addGap()), editPanel->createSequentialGroup().addMinGap(40)));
	//   //editPanel.createSequentialGroup().addGap().addWidgets(addSocialAccountsLabel).addGap(),
	//   //editPanel.createSequentialGroup().addGap().addWidgets(facebookAccountLabel).addGap(),
	//   //editPanel.createSequentialGroup().addGap().addWidgets(addFacebookAccountButton).addGap(),
	//   //editPanel.createSequentialGroup().addGap().addWidgets(googlePlusAccountLabel).addGap(),
	//   //editPanel.createSequentialGroup().addGap().addWidgets(addGooglePlusAccountButton).addGap(),
	//
	//   editPanel->setVerticalGroup(editPanel->createSequentialGroup(editPanel->createParallelGroup().addMinGap(20).addWidgets(playerEditPanelLabel).addMinGap(20), editPanel->createParallelGroup().addMinGap(10), editPanel->createParallelGroup().addMinGap(20).addWidgets(nameLabel, nameEditField).addMinGap(20), editPanel->createParallelGroup().addMinGap(10), editPanel->createParallelGroup().addMinGap(20).addWidgets(zipCodeLabel, zipCodeEditField).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(countryLabel).addWidgets(countryComboBox).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(animPanel).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(randomButton).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(genderLabel).addWidgets(genderButtons).addWidgets(genderButtonLabels).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(archetypeLabel).addWidgets(archetypeComboBox).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(hairColorLabel).addWidgets(hairColorComboBox).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(eyeColorLabel).addWidgets(eyeColorComboBox).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(skinColorLabel).addWidgets(skinColorComboBox).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(shirtColorLabel).addWidgets(shirtColorComboBox).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(pantsColorLabel).addWidgets(pantsColorComboBox).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(shoeColorLabel).addWidgets(shoeColorComboBox).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(statusLabel).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(errorLabel).addMinGap(20), editPanel->createParallelGroup().addMinGap(20).addWidgets(okButton).addMinGap(20)));
	//   //editPanel.createParallelGroup().addMinGap(10),
	//   //editPanel.createParallelGroup().addMinGap(20).addWidgets(addSocialAccountsLabel).addMinGap(20),
	//   //editPanel.createParallelGroup().addMinGap(20).addWidgets(addFacebookAccountButton).addMinGap(20),
	//   //editPanel.createParallelGroup().addMinGap(20).addWidgets(facebookAccountLabel),
	//   //editPanel.createParallelGroup().addMinGap(20).addWidgets(addGooglePlusAccountButton).addMinGap(20),
	//   //editPanel.createParallelGroup().addMinGap(20).addWidgets(googlePlusAccountLabel),
	//   //editPanel.createParallelGroup().addMinGap(20),
	//
	//
	//   //---------------------------------------------------------
	//   //layout
	//   //---------------------------------------------------------
	//
	//   insideScrollPaneLayout->setHorizontalGroup(insideScrollPaneLayout->createParallelGroup(insideScrollPaneLayout->createSequentialGroup().addGap().addWidget(editPanel).addGap()));
	//
	//   insideScrollPaneLayout->setVerticalGroup(insideScrollPaneLayout->createSequentialGroup(insideScrollPaneLayout->createSequentialGroup().addGap(), insideScrollPaneLayout->createParallelGroup().addWidget(editPanel), insideScrollPaneLayout->createSequentialGroup().addGap()));
	//
	//
	//   //---------------------
	//   //scrollpane
	//   //----------------------
	//
	//   scrollPane = new ScrollPane(insideScrollPaneLayout);
	//
	//   scrollPane->setTheme(GUIManager::scrollPaneTheme);
	//   scrollPane->setCanAcceptKeyboardFocus(false);
	//   //scrollPane.setExpandContentSize(true);
	//
	//   scrollPane->setExpandContentSize(true);
	//
	//   //---------------------
	//   //add scrollpane to outside panel
	//   //----------------------
	//
	//   //mainPanelLayout.add(scrollPane);
	//
	//
	//   mainPanelLayout->setCanAcceptKeyboardFocus(false);
	//   mainPanelLayout->setHorizontalGroup(mainPanelLayout->createParallelGroup(scrollPane));
	//
	//   mainPanelLayout->setVerticalGroup(mainPanelLayout->createSequentialGroup(scrollPane));
	//
	//
	//   add(mainPanelLayout);
	//
	//
	//   editPanel->adjustSize();
}

PlayerEditMenu::CallbackAnonymousInnerClassHelper::CallbackAnonymousInnerClassHelper(PlayerEditMenu* outerInstance)
{
	this->outerInstance = outerInstance;
}

void PlayerEditMenu::CallbackAnonymousInnerClassHelper::callback(int key)
{
	outerInstance->redrawPlayer();
}

PlayerEditMenu::CallbackAnonymousInnerClassHelper2::CallbackAnonymousInnerClassHelper2(PlayerEditMenu* outerInstance)
{
	this->outerInstance = outerInstance;
}

void PlayerEditMenu::CallbackAnonymousInnerClassHelper2::callback(int key)
{
	//zip cannot contain `
}

void PlayerEditMenu::init()
{ //=========================================================================================================================

	//   countryComboBox->setSelected(0);
	//
	//
	//   archetypeComboBox->setSelected(0);
	//   hairColorComboBox->setSelected(0);
	//   eyeColorComboBox->setSelected(1);
	//   skinColorComboBox->setSelected(2);
	//   shirtColorComboBox->setSelected(8);
	//
	//   pantsColorComboBox->setSelected(4);
	//   shoeColorComboBox->setSelected(2);
}

void PlayerEditMenu::setButtonsVisible(bool b)
{ //=========================================================================================================================

	//
	//   //handle all the buttons and labels etc
	//
	//   nameLabel->setVisible(b);
	//   nameEditField->setVisible(b);
	//
	//   zipCodeLabel->setVisible(b);
	//   zipCodeEditField->setVisible(b);
	//
	//
	//   addSocialAccountsLabel->setVisible(b);
	//   facebookAccountLabel->setVisible(b);
	//   addFacebookAccountButton->setVisible(b);
	//
	//   //googlePlusAccountLabel.setVisible(b);
	//   //addGooglePlusAccountButton.setVisible(b);
	//
	//   genderLabel->setVisible(b);
	//   for (int i = 0; i < genderButtonLabels->size(); i++)
	//   {
	//      genderButtonLabels[i]->setVisible(b);
	//   }
	//
	//   for (int i = 0; i < genderButtons->size(); i++)
	//   {
	//      genderButtons[i]->setVisible(b);
	//   }
	//
	//   countryLabel->setVisible(b);
	//
	//   countryComboBox->setVisible(b);
	//
	//   archetypeLabel->setVisible(b);
	//
	//   archetypeComboBox->setVisible(b);
	//
	//   hairColorLabel->setVisible(b);
	//
	//   hairColorComboBox->setVisible(b);
	//
	//   skinColorLabel->setVisible(b);
	//
	//   skinColorComboBox->setVisible(b);
	//
	//   eyeColorLabel->setVisible(b);
	//
	//   eyeColorComboBox->setVisible(b);
	//
	//   shirtColorLabel->setVisible(b);
	//
	//   shirtColorComboBox->setVisible(b);
	//
	//   pantsColorLabel->setVisible(b);
	//
	//   pantsColorComboBox->setVisible(b);
	//
	//   shoeColorLabel->setVisible(b);
	//
	//   shoeColorComboBox->setVisible(b);
	//
	//   randomButton->setVisible(b);
	//   okButton->setVisible(b);
}

PlayerEditMenu::AddressInfo::AddressInfo(PlayerEditMenu* outerInstance) : outerInstance(outerInstance)
{
}

PlayerEditMenu::AddressInfo* PlayerEditMenu::queryYahooGeocodingAPI(const string& address)
{ //=========================================================================================================================

	AddressInfo* a = new AddressInfo(this);


	// URL prefix to the geocoder
	string GEOCODER_REQUEST_PREFIX_FOR_XML = "where.yahooapis.com/geocode";
	//
	//   // prepare a URL to the geocoder
	//   URL* url = nullptr;
	//   try
	//   {
	//      url = new URL(GEOCODER_REQUEST_PREFIX_FOR_XML + string("?q=") + URLEncoder::encode(address, "UTF-8"));
	//   }
	//   catch (MalformedURLException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//   catch (UnsupportedEncodingException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   // prepare an HTTP connection to the geocoder
	//   HttpURLConnection* conn = nullptr;
	//   try
	//   {
	//      conn = static_cast<HttpURLConnection*>(url->openConnection());
	//   }
	//   catch (IOException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   Document* geocoderResultDocument = nullptr;
	//
	//   try
	//   {
	//      // open the connection and get results as InputSource.
	//      conn->connect();
	//   }
	//   catch (IOException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   try
	//   {
	//      InputSource* geocoderResultInputSource = new InputSource(conn->getInputStream());
	//      // read result and parse into XML Document
	//      geocoderResultDocument = DocumentBuilderFactory::newInstance().newDocumentBuilder().parse(geocoderResultInputSource);
	//   }
	//   catch (IOException e)
	//   {
	//      e->printStackTrace();
	//      return nullptr;
	//   }
	//   catch (SAXException e)
	//   {
	//      e->printStackTrace();
	//      return nullptr;
	//   }
	//   catch (ParserConfigurationException e)
	//   {
	//      e->printStackTrace();
	//      return nullptr;
	//   }
	//   //JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
	//   finally
	//      {
	//         conn->disconnect();
	//      }
	//
	//   // prepare XPath
	//   XPath* xpath = XPathFactory::newInstance().newXPath();
	//
	//   /*
	//      http://where.yahooapis.com/geocode?q=95817,%20United%20States
	//                  
	//      <resultset xmlns:ns1=3D"http://www.yahooapis.com/v1/base.rng" version=3D"2.0f" xml:lang=3D"en-US">
	//      <error>0</error>
	//      <errormessage>No error</errormessage>
	//      <locale>en-US</locale>
	//      <found>1</found>
	//      <quality>60</quality>
	//      <result>
	//         <quality>60</quality>
	//         <latitude>38.55117</latitude>
	//         <longitude>-121.449264</longitude>
	//         <offsetlat>38.55172</offsetlat>
	//         <offsetlon>-121.449692</offsetlon>
	//         <radius>3100</radius>
	//         <name></name>
	//         <line1></line1>
	//         <line2>Sacramento, CA 95817</line2>
	//         <line3></line3>
	//         <line4>United States</line4>
	//         <house></house>
	//         <street></street>
	//         <xstreet></xstreet>
	//         <unittype></unittype>
	//         <unit></unit>
	//         <postal>95817</postal>
	//         <neighborhood></neighborhood>
	//         <city>Sacramento</city>
	//         <county>Sacramento County</county>
	//         <state>California</state>
	//         <country>United States</country>
	//         <countrycode>US</countrycode>
	//         <statecode>CA</statecode>
	//         <countycode></countycode>
	//         <uzip>95817</uzip>
	//         <hash></hash>
	//         <woeid>12798003</woeid>
	//         <woetype>11</woetype>
	//      </result>
	//      </resultset>
	//                  
	//                  
	//   */
	//
	//
	//   // extract the result
	//   NodeList* resultNodeList = nullptr;
	//
	//   //validate status
	//   try
	//   {
	//      resultNodeList = static_cast<NodeList*>(xpath->evaluate("/resultset/errormessage", geocoderResultDocument, XPathConstants::NODESET));
	//   }
	//   catch (XPathExpressionException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   if (resultNodeList == nullptr)
	//   {
	//      //JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
	//      log.debug(string("No errormessage in Yahoo GeoCoding API (It returned nothing?)") + geocoderResultDocument->toString());
	//      return nullptr;
	//   }
	//
	//   for (int i = 0; i < resultNodeList->getLength(); ++i)
	//   {
	//      if (resultNodeList->item(i).getTextContent().equals("No error") == false)
	//      {
	//         log.debug(string("Error in Yahoo GeoCoding API: ") + resultNodeList->item(i).getTextContent());
	//         return nullptr;
	//      }
	//   }
	//
	//
	//   //get the formatted postal code
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete resultNodeList;
	//   try
	//   {
	//      resultNodeList = static_cast<NodeList*>(xpath->evaluate("/resultset/result[1]/postal", geocoderResultDocument, XPathConstants::NODESET));
	//   }
	//   catch (XPathExpressionException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   if (resultNodeList == nullptr)
	//   {
	//      log.debug("No postal code in Yahoo GeoCoding API");
	//      return nullptr;
	//   }
	//
	//   for (int i = 0; i < resultNodeList->getLength(); ++i)
	//   {
	//      a->postalCode = resultNodeList->item(i).getTextContent();
	//   }
	//
	//
	//   //get the city
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete resultNodeList;
	//   try
	//   {
	//      resultNodeList = static_cast<NodeList*>(xpath->evaluate("/resultset/result[1]/city", geocoderResultDocument, XPathConstants::NODESET));
	//   }
	//   catch (XPathExpressionException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   if (resultNodeList == nullptr)
	//   {
	//      log.debug("No locality (city/placeName) in Yahoo GeoCoding API");
	//      a->placeName = "?";
	//   }
	//
	//   for (int i = 0; i < resultNodeList->getLength(); ++i)
	//   {
	//      a->placeName = resultNodeList->item(i).getTextContent();
	//   }
	//
	//
	//   //get the state
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete resultNodeList;
	//   try
	//   {
	//      resultNodeList = static_cast<NodeList*>(xpath->evaluate("/resultset/result[1]/state", geocoderResultDocument, XPathConstants::NODESET));
	//   }
	//   catch (XPathExpressionException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   if (resultNodeList == nullptr)
	//   {
	//      log.debug("No state in Yahoo GeoCoding API");
	//      a->stateName = "?";
	//   }
	//
	//   for (int i = 0; i < resultNodeList->getLength(); ++i)
	//   {
	//      a->stateName = resultNodeList->item(i).getTextContent();
	//   }
	//
	//   //get the lat and lon
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete resultNodeList;
	//   try
	//   {
	//      resultNodeList = static_cast<NodeList*>(xpath->evaluate("/resultset/result[1]/latitude", geocoderResultDocument, XPathConstants::NODESET));
	//   }
	//   catch (XPathExpressionException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   if (resultNodeList == nullptr)
	//   {
	//      log.debug("No lat in Yahoo GeoCoding API");
	//      a->stateName = "?";
	//   }
	//
	//   for (int i = 0; i < resultNodeList->getLength(); ++i)
	//   {
	//      try
	//      {
	//         a->lat = (float)(resultNodeList->item(i).getTextContent());
	//      }
	//      catch (NumberFormatException ex)
	//      {
	//         ex->printStackTrace();
	//      }
	//   }
	//
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete resultNodeList;
	//   try
	//   {
	//      resultNodeList = static_cast<NodeList*>(xpath->evaluate("/resultset/result[1]/longitude", geocoderResultDocument, XPathConstants::NODESET));
	//   }
	//   catch (XPathExpressionException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   if (resultNodeList == nullptr)
	//   {
	//      log.debug("No lon in Yahoo GeoCoding API");
	//      a->stateName = "?";
	//   }
	//
	//   for (int i = 0; i < resultNodeList->getLength(); ++i)
	//   {
	//      try
	//      {
	//         a->lon = (float)(resultNodeList->item(i).getTextContent());
	//      }
	//      catch (NumberFormatException ex)
	//      {
	//         ex->printStackTrace();
	//      }
	//   }


	return a;
}

PlayerEditMenu::AddressInfo* PlayerEditMenu::queryGoogleGeocodingAPI(const string& address)
{ //=========================================================================================================================
	AddressInfo* a = new AddressInfo(this);


	// URL prefix to the geocoder
	string GEOCODER_REQUEST_PREFIX_FOR_XML = "http://maps.google.com/maps/api/geocode/xml";
	//
	//   // prepare a URL to the geocoder
	//   URL* url = nullptr;
	//   try
	//   {
	//      url = new URL(GEOCODER_REQUEST_PREFIX_FOR_XML + string("?address=") + URLEncoder::encode(address, "UTF-8") + string("&sensor=false"));
	//   }
	//   catch (MalformedURLException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//   catch (UnsupportedEncodingException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   // prepare an HTTP connection to the geocoder
	//   HttpURLConnection* conn = nullptr;
	//   try
	//   {
	//      conn = static_cast<HttpURLConnection*>(url->openConnection());
	//   }
	//   catch (IOException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   Document* geocoderResultDocument = nullptr;
	//
	//   try
	//   {
	//      // open the connection and get results as InputSource.
	//      conn->connect();
	//   }
	//   catch (IOException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   try
	//   {
	//      InputSource* geocoderResultInputSource = new InputSource(conn->getInputStream());
	//      // read result and parse into XML Document
	//      geocoderResultDocument = DocumentBuilderFactory::newInstance().newDocumentBuilder().parse(geocoderResultInputSource);
	//   }
	//   catch (IOException e)
	//   {
	//      e->printStackTrace();
	//      return nullptr;
	//   }
	//   catch (SAXException e)
	//   {
	//      e->printStackTrace();
	//      return nullptr;
	//   }
	//   catch (ParserConfigurationException e)
	//   {
	//      e->printStackTrace();
	//      return nullptr;
	//   }
	//   //JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
	//   finally
	//      {
	//         conn->disconnect();
	//      }
	//
	//   // prepare XPath
	//   XPath* xpath = XPathFactory::newInstance().newXPath();
	//
	//
	//   /*
	//      <geocoderesponse>
	//         <status>OK</status>
	//                  
	//         <result>
	//            <address_component>
	//               <long_name>Sacramento</long_name>
	//               <short_name>Sacramento</short_name>
	//               <type>administrative_area_level_2</type>
	//               <type>political</type>
	//            </address_component>
	//                  
	//            <address_component>
	//               <long_name>California</long_name>
	//               <short_name>CA</short_name>
	//               <type>administrative_area_level_1</type>
	//               <type>political</type>
	//            </address_component>
	//                  
	//            <address_component>
	//               <long_name>95817</long_name>
	//               <short_name>95817</short_name>
	//               <type>postal_code</type>
	//            </address_component>
	//                  
	//            <geometry>
	//               <location>
	//                  <lat>38.5500434</lat>
	//                  <lng>-121.4599012</lng>
	//               </location>
	//            </geometry>
	//         </result>
	//                  
	//      </geocoderesponse>
	//    */
	//
	//   // extract the result
	//   NodeList* resultNodeList = nullptr;
	//
	//   //validate status
	//   try
	//   {
	//      resultNodeList = static_cast<NodeList*>(xpath->evaluate("/GeocodeResponse/status", geocoderResultDocument, XPathConstants::NODESET));
	//   }
	//   catch (XPathExpressionException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   if (resultNodeList == nullptr)
	//   {
	//      //JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
	//      log.debug(string("No status in Google GeoCoding API (It returned nothing?)") + geocoderResultDocument->toString());
	//      return nullptr;
	//   }
	//
	//   for (int i = 0; i < resultNodeList->getLength(); ++i)
	//   {
	//      if (resultNodeList->item(i).getTextContent().equals("OK") == false)
	//      {
	//         log.debug(string("Status Error in Google GeoCoding API: ") + resultNodeList->item(i).getTextContent());
	//         return nullptr;
	//      }
	//   }
	//
	//
	//   //get the formatted postal code
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete resultNodeList;
	//   try
	//   {
	//      resultNodeList = static_cast<NodeList*>(xpath->evaluate("/GeocodeResponse/result[1]/address_component[type/getText() = 'postal_code']/long_name", geocoderResultDocument, XPathConstants::NODESET));
	//   }
	//   catch (XPathExpressionException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   if (resultNodeList == nullptr)
	//   {
	//      log.debug("No postal code in Google GeoCoding API");
	//      return nullptr;
	//   }
	//
	//   for (int i = 0; i < resultNodeList->getLength(); ++i)
	//   {
	//      a->postalCode = resultNodeList->item(i).getTextContent();
	//   }
	//
	//
	//   //get the city
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete resultNodeList;
	//   try
	//   {
	//      resultNodeList = static_cast<NodeList*>(xpath->evaluate("/GeocodeResponse/result[1]/address_component[type/getText() = 'locality']/long_name", geocoderResultDocument, XPathConstants::NODESET));
	//   }
	//   catch (XPathExpressionException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   if (resultNodeList == nullptr)
	//   {
	//      log.debug("No locality (city/placeName) in Google GeoCoding API");
	//      a->placeName = "?";
	//   }
	//
	//   for (int i = 0; i < resultNodeList->getLength(); ++i)
	//   {
	//      a->placeName = resultNodeList->item(i).getTextContent();
	//   }
	//
	//
	//   //get the state
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete resultNodeList;
	//   try
	//   {
	//      resultNodeList = static_cast<NodeList*>(xpath->evaluate("/GeocodeResponse/result[1]/address_component[type/getText() = 'administrative_area_level_1']/long_name", geocoderResultDocument, XPathConstants::NODESET));
	//   }
	//   catch (XPathExpressionException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   if (resultNodeList == nullptr)
	//   {
	//      log.debug("No state in Google GeoCoding API");
	//      a->stateName = "?";
	//   }
	//
	//   for (int i = 0; i < resultNodeList->getLength(); ++i)
	//   {
	//      a->stateName = resultNodeList->item(i).getTextContent();
	//   }
	//
	//   //get the lat and lon
	//   //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//   delete resultNodeList;
	//   try
	//   {
	//      resultNodeList = static_cast<NodeList*>(xpath->evaluate("/GeocodeResponse/result[1]/geometry/location/*", geocoderResultDocument, XPathConstants::NODESET));
	//   }
	//   catch (XPathExpressionException e1)
	//   {
	//      e1->printStackTrace();
	//      return nullptr;
	//   }
	//
	//   if (resultNodeList == nullptr)
	//   {
	//      log.debug("No lat/lon in Google GeoCoding API");
	//      return nullptr;
	//   }
	//
	//   for (int i = 0; i < resultNodeList->getLength(); ++i)
	//   {
	//      Node* node = resultNodeList->item(i);
	//      if ((string("lat")) == node->getNodeName())
	//      {
	//         try
	//         {
	//            a->lat = (float)(node->getTextContent());
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//         }
	//      }
	//
	//      if ((string("lng")) == node->getNodeName())
	//      {
	//         try
	//         {
	//            a->lon = (float)(node->getTextContent());
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//         }
	//      }
	//      if ((string("lon")) == node->getNodeName())
	//      {
	//         try
	//         {
	//            a->lon = (float)(node->getTextContent());
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//         }
	//      }
	//   }


	return a;
}

void PlayerEditMenu::doOKButton()
{ //=========================================================================================================================
	//
	//   new Thread([&] () //needs to be a thread because Button.doCallback only calls Runnable.run() which does NOT create a thread
	//      {
	//         try
	//         {
	//            Thread::currentThread().setName("PlayerEditMenu_doOKButton");
	//         }
	//         catch (SecurityException e)
	//         {
	//            e->printStackTrace();
	//         }
	//
	//         setButtonsVisible(false);
	//
	//         //make sure name is set
	//         errorLabel->setText(" ");
	//         statusLabel->setText("Validating location...");
	//
	//         if (nameEditField->getText().length() == 0)
	//         {
	//            errorLabel->setText("Please enter a name.");
	//            return;
	//         }
	//         if (nameEditField->getText()->contains("`"))
	//         {
	//            errorLabel->setText("Name cannot contain ` ");
	//            return;
	//         }
	//
	//         if (zipCodeEditField->getText().length() == 0)
	//         {
	//            errorLabel->setText("Please enter a Zip/Postal Code.");
	//            return;
	//         }
	//         if (zipCodeEditField->getText()->contains("`"))
	//         {
	//            errorLabel->setText("Zip/Postal Code cannot contain ` ");
	//            return;
	//         }
	//
	//         //send gameSave update to server for name and styles
	//
	//         //Main.clientTCP.addQueuedGameSaveUpdateRequest_S("characterName:`"+nameEditField.getText()+"`");
	//         //Game().gameSave.characterName = nameEditField.getText();
	//
	//         string characterAppearance = string("") + genderIndex + string(",") + archetypeIndex + string(",") + hairColorIndex + string(",") + skinColorIndex + string(",") + eyeColorIndex + string(",") + shirtColorIndex + string(",") + pantsColorIndex + string(",") + to_string(shoeColorIndex);
	//         getServerConnection()->addQueuedGameSaveUpdateRequest_S(string("characterName:`") + nameEditField->getText() + string("`") + string(",") + string("characterAppearance:`") + characterAppearance + string("`"));
	//         getGameSave()->characterName = nameEditField->getText();
	//         getGameSave()->characterAppearance = characterAppearance;
	//
	//
	//         Player * p = getPlayer();
	//         if (p != nullptr)
	//         {
	//            p->setCharacterNameAndCaption(getGameEngine()->getNameColor(getGameSave()->accountType), nameString, getGameEngine()->getAccountTypeColor(getGameSave()->accountType), getGameEngine()->getAccountTypeString(getGameSave()->accountType));
	//         }
	//
	//
	//         bool wasValid = true;
	//
	//
	//         if (System::debugMode == false)
	//         {
	//            string countryName = countryStrings->getEntry(countryComboBox->getSelected());
	//            string postalCode = zipCodeEditField->getText();
	//
	//            string countryCode = GameSave::getCountryCodeFromCountryString(countryName);
	//
	//            //get locality info from google API
	//            AddressInfo* a = queryGoogleGeocodingAPI(string("") + postalCode + string(", ") + countryName);
	//
	//            if (a == nullptr)
	//            {
	//               //try again with yahoo
	//               a = queryYahooGeocodingAPI(string("") + postalCode + string(", ") + countryName);
	//            }
	//
	//            //TODO: also try open maps?
	//
	//
	//            if (a != nullptr)
	//            {
	//               getServerConnection()->addQueuedGameSaveUpdateRequest_S(string("postalCode:`") + a->postalCode + string("`") + string(",") + string("countryName:`") + countryName + string("`") + string(",") + string("isoCountryCode:`") + countryCode + string("`") + string(",") + string("stateName:`") + a->stateName + string("`") + string(",") + string("placeName:`") + a->placeName + string("`") + string(",") + string("lat:`") + a->lat + string("`") + string(",") + string("lon:`") + a->lon + string("`"));
	//               getGameSave()->postalCode = a->postalCode;
	//               getGameSave()->countryName = countryName;
	//               getGameSave()->isoCountryCode = countryCode;
	//               getGameSave()->stateName = a->stateName;
	//               getGameSave()->placeName = a->placeName;
	//               getGameSave()->lat = a->lat;
	//               getGameSave()->lon = a->lon;
	//            }
	//            else
	//            {
	//               wasValid = false;
	//            }
	//         }
	//
	//         //server side geolookup in local database:
	//         //					{
	//         //
	//         //						Main.clientTCP.setPostalCodeUpdateReceived_S(false);
	//         //						Main.clientTCP.setPostalCodeUpdateWasValid_S(false);
	//         //
	//         //						Main.clientTCP.sendPostalCodeUpdateRequest(zipCodeEditField.getText(), countryStrings.getEntry(countryComboBox.getSelected()));
	//         //
	//         //						setButtonsVisible(false);
	//         //
	//         //						//wait for postal code return
	//         //						//-------------------------------
	//         //						//check to see if response every 1 second
	//         //						//-------------------------------
	//         //						int responseTries = 0;
	//         //						boolean gotResponse = false;
	//         //						while(gotResponse==false)
	//         //						{
	//         //							gotResponse = Main.clientTCP.getPostalCodeUpdateReceived_S();
	//         //
	//         //							if(gotResponse==false)
	//         //							{
	//         //								responseTries++;
	//         //								if(responseTries>5)
	//         //								{
	//         //									responseTries=0;
	//         //									statusLabel.setText(" ");
	//         //									errorLabel.setText("Error: Did not receive a response from the server.");
	//         //
	//         //									setButtonsVisible(true);
	//         //
	//         //									return;
	//         //								}
	//         //
	//         //								try{Thread.sleep(1000);}catch (Exception e){e.printStackTrace();}
	//         //							}
	//         //						}
	//         //
	//         //
	//         //						if(Main.clientTCP.getPostalCodeUpdateWasValid_S()==false)
	//         //						{
	//         //							wasValid=false;
	//         //							Main.clientTCP.setPostalCodeUpdateReceived_S(false);
	//         //						}
	//         //					}
	//
	//
	//         if (wasValid == false)
	//         {
	//            statusLabel->setText(" ");
	//            errorLabel->setText(string("Error: Zip/Postal Code could not be found.\n") + string("Are you sure it is formatted correctly? Also make sure you've selected the correct Country.\n") + string("Hint: You can also try putting your city name into the Postal Code field."));
	//            setButtonsVisible(true);
	//         }
	//         else
	//         {
	//            statusLabel->setText(" ");
	//            errorLabel->setText(" ");
	//
	//            setButtonsVisible(true);
	//            setActivated(false);
	//         }
	//      }
	//   )
	//   .
	//   start();
}

void PlayerEditMenu::linkFacebookAccount()
{ //=========================================================================================================================

	//
	//   new Thread([&] () //needs to be a thread because Button.doCallback only calls Runnable.run() which does NOT create a thread
	//      {
	//         try
	//         {
	//            Thread::currentThread().setName("PlayerEditMenu_linkFacebookAccount");
	//         }
	//         catch (SecurityException e)
	//         {
	//            e->printStackTrace();
	//         }
	//
	//
	//         errorLabel->setText(" ");
	//         statusLabel->setText(" ");
	//
	//
	//         setButtonsVisible(false);
	//
	//
	//         //do we have a sessionToken already?
	//
	//         string facebookAccessToken = getGameSave()->facebookAccessToken;
	//         bool haveAccessToken = false;
	//         bool accessTokenIsValid = true;
	//
	//         if (facebookAccessToken.length() > 0)
	//         {
	//            haveAccessToken = true;
	//
	//
	//            //check if our session token is valid
	//            //restFB stuff here
	//            FacebookClient* facebookClient = nullptr;
	//
	//            //------------------------
	//            //log into facebook to test token
	//            //------------------------
	//            try
	//            {
	//               facebookClient = new DefaultFacebookClient(facebookAccessToken);
	//               User* user = facebookClient->fetchObject("me", User::typeid);
	//
	//               string facebookID = user->getId();
	//               log.debug(string("Facebook ID: ") + facebookID);
	//            }
	//            catch (exception& ex)
	//            {
	//               accessTokenIsValid = false;
	//            }
	//         }
	//
	//
	//         //if we have facebook accessToken already, let's not bother the user
	//
	//
	//         if (haveAccessToken == false || accessTokenIsValid == false)
	//         {
	//            statusLabel->setText("Please authorize Facebook Connect in the browser window.");
	//
	//            if (Main::isApplet == true)
	//            {
	//               //TODO: use FB JS SDK here? don't need to do this yet.
	//               //can check if we are logged in and already verified though.
	//
	//
	//               //if we AREN'T authorized, the client should pop up the facebook window or load it into an iframe
	//               //the client will use the iframe (or javascript popup) to send a request to facebook with our app token
	//               //facebook redirects us back to our facebook.php which sets the accessToken in SQL.
	//
	//
	//               //check if we are logged into facebook in browser - use the JS SDK which checks our cookies i think, or we can do this with JSObject or CookieManager probably.
	//               //if we're not logged into facebook and we have facebook accessToken already, let's not bother the user
	//               //if we ARE logged into facebook and our application IS authorized, we can just automatically get a new session token by refreshing facebook.php
	//
	//
	//               //basically either way, we should just refresh the iframe to facebook.php and resize it.
	//               //if they've already authorized us, it should get the accessToken and hide itself.
	//
	//
	//               //open with javascript
	//
	//
	//               //TODO: have iframe redirect and expand to auth size, then remove it/resize to nothing when we are done
	//               //best way to do this?
	//               //probably have the PHP output javascript which resizes its iframe to nothing from inside, after we've got our error response or authToken.
	//
	//
	//               //$('<frame />').attr('src', 'http://example.com').attachTo('body')
	//               //in applet obj tag
	//               //<PARAM NAME="MAYSCRIPT" VALUE="true">
	//               //					         JSObject win = JSObject.getWindow(Main.mainObject);
	//               //					         JSObject doc = (JSObject) win.getMember("document");
	//               //					         JSObject loc = (JSObject) doc.getMember("location");
	//               //
	//               //					         String s = (String) loc.getMember("href");  // document.location.href
	//               //					         win.call("f", null);
	//
	//
	//               //String url = "http://www.bobsgame.com/facebook.php?u="+Game().gameSave.userID;
	//
	//               URL* url = nullptr;
	//               try
	//               {
	//                  url = new URL(string("http://www.bobsgame.com/facebook.php?u=") + getGameSave()->userID);
	//               }
	//               catch (MalformedURLException e)
	//               {
	//                  e->printStackTrace();
	//               }
	//
	//               Main::mainObject->getAppletContext().showDocument(url, "_blank");
	//
	//
	//               //TODO: pause until we have confirmation
	//
	//               //could have the PHP call javascript which connects back to this applet and tells us it's done (or error)
	//               //could also have this check with javascript to see if the iframe has error or accessToken set.
	//
	//               //could also have a pause/cancel button here.
	//               //or could just wait.
	//
	//               try
	//               {
	//                  delay(5000);
	//               }
	//               catch (exception& e)
	//               {
	//                  e.printStackTrace();
	//               }
	//            }
	//            else
	//            {
	//               try
	//               {
	//                  //open browser window, we can't get it with JS as a desktop client so we need to redirect to PHP or something which stores it in SQL
	//                  string url = string("http://www.bobsgame.com/facebook.php?u=") + getGameSave()->userID;
	//
	//                  java::awt::Desktop::getDesktop().browse(java::net::URI::create(url));
	//               }
	//               catch (IOException e)
	//               {
	//                  log.error(string("Could not open browser: ") + e->getMessage());
	//               }
	//
	//
	//               //TODO: pause until we have confirmation, how to do this? ok button?
	//               //could also have a pause/cancel button here.
	//               //or could just wait.
	//
	//               try
	//               {
	//                  delay(5000);
	//               }
	//               catch (exception& e)
	//               {
	//                  e.printStackTrace();
	//               }
	//            }
	//         }
	//
	//
	//         //if we are an applet, we can get the access token through javascript and have the server update immediately.
	//
	//
	//         //if we are a desktop app, we should just tell the server to update from the database, since the authorization happened there.
	//         //we could keep asking the server if we have the token yet
	//
	//
	//         statusLabel->setText("Checking to see if account was authorized. Please wait for 10 seconds...");
	//
	//         //DONE: send update facebook account command
	//         //UpdateFacebookAccountInDB
	//
	//
	//         //TODO should do this on login if the session is still valid
	//         //do this on login on the server side and then send online friend list, don't even request from client.
	//
	//         //refresh the session token and send to server
	//         getServerConnection()->sendUpdateFacebookAccountInDBRequest_S();
	//
	//         //-------------------------------
	//         //check to see if response every 1 second
	//         //-------------------------------
	//         int responseTries = 0;
	//         bool gotResponse = false;
	//         while (gotResponse == false)
	//         {
	//            gotResponse = getServerConnection()->getFacebookAccountUpdateResponseReceived_S();
	//
	//            if (gotResponse == false)
	//            {
	//               responseTries++;
	//               if (responseTries > 10)
	//               {
	//                  responseTries = 0;
	//                  statusLabel->setText(" ");
	//                  errorLabel->setText("Error: Did not receive a response from the server.");
	//
	//                  setButtonsVisible(true);
	//
	//                  return;
	//               }
	//
	//               try
	//               {
	//                  delay(1000);
	//               }
	//               catch (exception& e)
	//               {
	//                  e.printStackTrace();
	//               }
	//            }
	//         }
	//
	//         bool wasValid = getServerConnection()->getFacebookAccountUpdateResponseWasValid_S();
	//
	//         //reset the state
	//         getServerConnection()->setFacebookAccountUpdateResponseState_S(false, false);
	//
	//         if (wasValid == false)
	//         {
	//            statusLabel->setText(" ");
	//            errorLabel->setText("Error: Facebook session could not be validated. Please try again.");
	//            setButtonsVisible(true);
	//         }
	//         else
	//         {
	//            getServerConnection()->sendOnlineFriendListRequest();
	//
	//
	//            statusLabel->setText(" ");
	//            errorLabel->setText(" ");
	//
	//            setButtonsVisible(true);
	//
	//            //replace the facebook button with "account linked!"
	//            facebookAccountLabel->setText("Facebook: Connected!");
	//            addFacebookAccountButton->setEnabled(false);
	//            addFacebookAccountButton->setVisible(false);
	//         }
	//      }
	//   )
	//   .
	//   start();
}

void PlayerEditMenu::redrawPlayer()
{ //=========================================================================================================================

	if (getIsActivated() == false)
	{
		return;
	}
	//
	//   nameString = nameEditField->getText();
	//
	//   if (genderButtons[0]->isActive())
	//   {
	//      genderIndex = 0;
	//   }
	//   else
	//   {
	//      genderIndex = 1;
	//   }
	//
	//
	//   archetypeIndex = archetypeComboBox->getSelected();
	//   shoeColorIndex = shoeColorComboBox->getSelected();
	//   shirtColorIndex = shirtColorComboBox->getSelected();
	//   pantsColorIndex = pantsColorComboBox->getSelected();
	//   skinColorIndex = skinColorComboBox->getSelected();
	//   eyeColorIndex = eyeColorComboBox->getSelected();
	//   hairColorIndex = hairColorComboBox->getSelected();
	//
	//
	//   Player * p = getPlayer();
	//
	//   if (p != nullptr)
	//   {
	//      p->generateUniqueTexture(genderIndex, archetypeIndex, shoeColorIndex, shirtColorIndex, pantsColorIndex, skinColorIndex, eyeColorIndex, hairColorIndex);
	//      p->setCharacterNameAndCaption(getGameEngine()->getNameColor(getGameSave()->accountType), nameString, getGameEngine()->getAccountTypeColor(getGameSave()->accountType), getGameEngine()->getAccountTypeString(getGameSave()->accountType));
	//   }
}

void PlayerEditMenu::setRandomOptions()
{ //=========================================================================================================================
	//
	//   genderButtons[Utils::randLessThan(2)]->setActive(true);
	//
	//
	//   archetypeComboBox->setSelected(Utils::randLessThan(archetypeStrings->getNumEntries()));
	//   shoeColorComboBox->setSelected(Utils::randLessThan(shoeColorStrings->getNumEntries()));
	//   shirtColorComboBox->setSelected(Utils::randLessThan(shirtColorStrings->getNumEntries()));
	//   pantsColorComboBox->setSelected(Utils::randLessThan(pantsColorStrings->getNumEntries()));
	//   skinColorComboBox->setSelected(Utils::randLessThan(skinColorStrings->getNumEntries()));
	//   eyeColorComboBox->setSelected(Utils::randLessThan(eyeColorStrings->getNumEntries()));
	//   hairColorComboBox->setSelected(Utils::randLessThan(hairColorStrings->getNumEntries()));
}

void PlayerEditMenu::layout()
{ //=========================================================================================================================
	//
	//   //edit panel is centered
	//
	//   editPanel->adjustSize();
	//   editPanel->setPosition(insideScrollPaneLayout->getInnerX() + (insideScrollPaneLayout->getInnerWidth() - editPanel->getWidth()) / 2, insideScrollPaneLayout->getInnerY() + (insideScrollPaneLayout->getInnerHeight() - editPanel->getHeight()) / 2);

	MenuPanel::layout();
}

void PlayerEditMenu::setActivated(bool b)
{ //=========================================================================================================================
	MenuPanel::setActivated(b);
	//
	//   if (b == true)
	//   {
	//      if (getGameSave()->characterAppearance == nullptr || getGameSave()->characterAppearance::length() == 0 || getGameSave()->characterAppearance::equals(""))
	//      {
	//         setRandomOptions();
	//         redrawPlayer();
	//      }
	//      else
	//      {
	//         nameEditField->setText(getGameSave()->characterName);
	//
	//         zipCodeEditField->setText(getGameSave()->postalCode);
	//
	//         //on dialogue load, load character values from gameSave
	//
	//         string s = getGameSave()->characterAppearance;
	//
	//         try
	//         {
	//            genderIndex = stoi(s.substr(0, s.find(",")));
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//            return;
	//         }
	//         s = s.substr(s.find(",") + 1);
	//         try
	//         {
	//            archetypeIndex = stoi(s.substr(0, s.find(",")));
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//            return;
	//         }
	//         s = s.substr(s.find(",") + 1);
	//         try
	//         {
	//            hairColorIndex = stoi(s.substr(0, s.find(",")));
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//            return;
	//         }
	//         s = s.substr(s.find(",") + 1);
	//         try
	//         {
	//            skinColorIndex = stoi(s.substr(0, s.find(",")));
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//            return;
	//         }
	//         s = s.substr(s.find(",") + 1);
	//         try
	//         {
	//            eyeColorIndex = stoi(s.substr(0, s.find(",")));
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//            return;
	//         }
	//         s = s.substr(s.find(",") + 1);
	//         try
	//         {
	//            shirtColorIndex = stoi(s.substr(0, s.find(",")));
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//            return;
	//         }
	//         s = s.substr(s.find(",") + 1);
	//         try
	//         {
	//            pantsColorIndex = stoi(s.substr(0, s.find(",")));
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//            return;
	//         }
	//         s = s.substr(s.find(",") + 1);
	//         try
	//         {
	//            shoeColorIndex = stoi(s);
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//            return;
	//         }
	//
	//         genderButtons[genderIndex]->setActive(true);
	//         archetypeComboBox->setSelected(archetypeIndex);
	//         shoeColorComboBox->setSelected(shoeColorIndex);
	//         shirtColorComboBox->setSelected(shirtColorIndex);
	//         pantsColorComboBox->setSelected(pantsColorIndex);
	//         skinColorComboBox->setSelected(skinColorIndex);
	//         eyeColorComboBox->setSelected(eyeColorIndex);
	//         hairColorComboBox->setSelected(hairColorIndex);
	//
	//         redrawPlayer();
	//      }
	//
	//
	//      if (getGameSave()->facebookAccessToken::length() > 0)
	//      {
	//         //if we have a sessionToken already, remove the facebookConnect button on load and replace with "account linked!"
	//
	//         //replace the facebook button with "account linked!"
	//         facebookAccountLabel->setText("Facebook: Connected!");
	//         addFacebookAccountButton->setEnabled(false);
	//         addFacebookAccountButton->setVisible(false);
	//      }
	//      else
	//      {
	//         facebookAccountLabel->setText("Facebook: Not Connected");
	//         addFacebookAccountButton->setEnabled(true);
	//         addFacebookAccountButton->setVisible(true);
	//      }
	//   }
}

void PlayerEditMenu::update()
{ //=========================================================================================================================

	MenuPanel::update();

	if (getIsScrollingDown() == true || getIsActivated() == false)
	{
		if (playerNameCaption != nullptr)
		{
			playerNameCaption->setToFadeOutAndBeDeleted();
			//Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
			delete playerNameCaption;
		}
	}
}

void PlayerEditMenu::render()
{ //=========================================================================================================================


	if (getIsScrollingDown() == true)
	{
		return;
	}
	if (getIsActivated() == false)
	{
		return;
	}
	if (getIsScrolledUp() == false)
	{
		return;
	}

	//additional rendering calls go here (after gui is drawn)

	//Player* p = getPlayer();

	//Texture* texture = p->uniqueTexture;

	long long startTime = lastTime;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	if (ticksPassed > 80)
	{
		lastTime = currentTime;
		frame++;
		if (frame >= 8)
		{
			frame = 0;
			loopCount++;
		}

		if (loopCount > 0)
		{
			loopCount = 0;
			if (direction == Entity::DOWN)
			{
				direction = Entity::DOWNLEFT;
			}
			else if (direction == Entity::DOWNLEFT)
			{
				direction = Entity::LEFT;
			}
			else if (direction == Entity::LEFT)
			{
				direction = Entity::UPLEFT;
			}
			else if (direction == Entity::UPLEFT)
			{
				direction = Entity::UP;
			}
			else if (direction == Entity::UP)
			{
				direction = Entity::UPRIGHT;
			}
			else if (direction == Entity::UPRIGHT)
			{
				direction = Entity::RIGHT;
			}
			else if (direction == Entity::RIGHT)
			{
				direction = Entity::DOWNRIGHT;
			}
			else if (direction == Entity::DOWNRIGHT)
			{
				direction = Entity::DOWN;
			}
		}
	}

	//int renderFrame = direction * 8 + frame;


	//float drawScale = 2.0f;

	//   if (texture != nullptr)
	//   {
	//      float tx0 = 0.0f;
	//      float tx1 = ((float)(p->sprite->w()) / (float)(texture->getTextureWidth()));
	//      float ty0 = (((float)(p->sprite->h())) * renderFrame) / (float)(texture->getTextureHeight());
	//      float ty1 = (((float)(p->sprite->h())) * (renderFrame + 1)) / (float)(texture->getTextureHeight());
	//
	//      //x0 = (float)Math.floor(getScreenLeft());
	//      //x1 = (float)Math.floor(screenRight());
	//      //y0 = (float)Math.floor(getScreenTop());
	//      //y1 = (float)Math.floor(screenBottom());
	//
	//      float x0 = animPanel->getX() + animPanel->getWidth() / 2 - p->w() * drawScale / 2.0f; //Display.getWidth()/2 - p.width()*drawScale/2.0f;
	//      float y0 = animPanel->getY() + animPanel->getHeight() / 2 - p->h() * drawScale / 2.0f; //Display.getHeight()/2 - p.height()*drawScale/2.0f;
	//      float x1 = (float)(x0 + p->w() * drawScale);
	//      float y1 = (float)(y0 + p->h() * drawScale);
	//
	//
	//      GLUtils::drawTexture(texture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, 1.0f, GLUtils::FILTER_NEAREST);
	//   }
	//
	//   //if(playerNameCaption!=null)playerNameCaption.render();
}

