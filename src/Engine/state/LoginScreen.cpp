#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger LoginScreen::log = Logger("LoginScreen");


LoginScreen::LoginScreen()
{ //=========================================================================================================================

	//MenuPanel();

	//
	//   loginPanel = new DialogLayout();
	//   loginPanel->setTheme("loginpanel");
	//
	//
	//   Label* loginPanelLabel = new Label("Login");
	//   loginPanelLabel->setCanAcceptKeyboardFocus(false);
	//   loginPanelLabel->setTheme("bigLabel");
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
	//
	//   //---------------------------------------------------------
	//   //login with facebook button
	//   //---------------------------------------------------------
	//   loginWithFacebookButton = new Button("Login using your Facebook account!");
	//   loginWithFacebookButton->setTheme("smallButton");
	//   loginWithFacebookButton->setCanAcceptKeyboardFocus(false);
	//
	//   loginWithFacebookButton->addCallback([&] ()
	//      {
	//         doLoginWithFacebook();
	//      }
	//   );
	//
	//   if (Main::isApplet == false)
	//   {
	//      loginWithFacebookButton->setVisible(false);
	//      loginWithFacebookButton->setEnabled(false);
	//   }
	//
	//
	//   //---------------------------------------------------------
	//   //name
	//   //---------------------------------------------------------
	//   emailEditField = new EditField();
	//
	//
	//   emailLabel = new Label("Email");
	//   //emailLabel.setLabelFor(emailEditField);
	//   emailLabel->setCanAcceptKeyboardFocus(false);
	//
	//
	//   //---------------------------------------------------------
	//   //password
	//   //---------------------------------------------------------
	//
	//   passwordLabel = new Label("Password");
	//   //passwordLabel.setLabelFor(passwordEditField);
	//   passwordLabel->setCanAcceptKeyboardFocus(false);
	//
	//   passwordEditField = new EditField();
	//   passwordEditField->setPasswordMasking(true);
	//
	//   passwordEditField->addCallback(new CallbackAnonymousInnerClassHelper(this));
	//
	//   //---------------------------------------------------------
	//   //login
	//   //---------------------------------------------------------
	//   loginButton = new Button("Login");
	//   loginButton->setCanAcceptKeyboardFocus(false);
	//   loginButton->addCallback([&] ()
	//      {
	//         doLogin();
	//      }
	//   );
	//
	//   //---------------------------------------------------------
	//   //forgot pass
	//   //---------------------------------------------------------
	//   forgotPasswordButton = new Button("Forgot Password?");
	//   forgotPasswordButton->setCanAcceptKeyboardFocus(false);
	//   forgotPasswordButton->setTheme("textButton");
	//   forgotPasswordButton->addCallback([&] ()
	//      {
	//         doForgotPassword();
	//      }
	//   );
	//
	//   //---------------------------------------------------------
	//   //create new account
	//   //---------------------------------------------------------
	//   createNewAccountButton = new Button("Create Account");
	//   createNewAccountButton->setCanAcceptKeyboardFocus(false);
	//   createNewAccountButton->addCallback([&] ()
	//      {
	//         doCreateNewAccount();
	//      }
	//   );
	//
	//
	//   //---------------------------------------------------------
	//   //stay logged in
	//   //---------------------------------------------------------
	//   stayLoggedInToggleButton->setTheme(GUIManager::checkboxTheme);
	//   stayLoggedInToggleButton->setCanAcceptKeyboardFocus(false);
	//   stayLoggedInToggleButton->setActive(true);
	//
	//   //		stayLoggedInToggleButton.addCallback(new Runnable()
	//   //		{
	//   //			public void run()
	//   //			{
	//   //
	//   //			}
	//   //		});
	//
	//   stayLoggedInToggleButtonLabel = new Label("Stay Logged In");
	//   stayLoggedInToggleButtonLabel->setCanAcceptKeyboardFocus(false);
	//   stayLoggedInToggleButtonLabel->setLabelFor(stayLoggedInToggleButton);
	//
	//   //---------------------------------------------------------
	//   //send stats
	//   //---------------------------------------------------------
	//   sendStatsToggleButton->setTheme(GUIManager::checkboxTheme);
	//   sendStatsToggleButton->setCanAcceptKeyboardFocus(false);
	//   sendStatsToggleButton->setActive(true);
	//
	//   //		sendStatsToggleButton.addCallback(new Runnable()
	//   //		{
	//   //			public void run()
	//   //			{
	//   //
	//   //			}
	//   //		});
	//
	//   sendStatsToggleButtonLabel = new Label("Send PC Stats");
	//   sendStatsToggleButtonLabel->setCanAcceptKeyboardFocus(false);
	//   sendStatsToggleButtonLabel->setLabelFor(sendStatsToggleButton);
	//
	//   sendStatsQuestionMark = new Label(" ? ");
	//   sendStatsQuestionMark->setCanAcceptKeyboardFocus(false);
	//   sendStatsQuestionMark->setTheme("descriptionLabel");
	//   sendStatsQuestionMark->setTooltipContent("");
	//
	//
	//   //DialogLayout.Group hLabels = loginPanel.createParallelGroup(nameLabel,passwordLabel);
	//   //DialogLayout.Group hFields = loginPanel.createParallelGroup(nameEditField,passwordEditField);
	//   //DialogLayout.Group hBtn = loginPanel.createSequentialGroup().addGap().addWidget(loginButton) ;// right align the button by using a variable gap
	//
	//
	//   loginPanel->setHorizontalGroup(loginPanel->createParallelGroup(loginPanel->createParallelGroup().addMinGap(400), loginPanel->createSequentialGroup().addGap().addWidget(errorLabel).addGap(), loginPanel->createSequentialGroup().addGap().addWidget(statusLabel).addGap(), loginPanel->createSequentialGroup(loginPanel->createParallelGroup().addMinGap(50), loginPanel->createParallelGroup(loginPanel->createSequentialGroup().addGap().addWidget(loginPanelLabel).addGap(), loginPanel->createSequentialGroup().addGap().addWidget(loginWithFacebookButton).addGap(), loginPanel->createSequentialGroup(loginPanel->createParallelGroup().addWidgets(emailLabel, passwordLabel), loginPanel->createParallelGroup().addWidgets(emailEditField, passwordEditField)), loginPanel->createSequentialGroup().addGap().addWidget(forgotPasswordButton).addGap().addWidget(loginButton), loginPanel->createSequentialGroup().addGap().addWidgets(stayLoggedInToggleButtonLabel, stayLoggedInToggleButton), loginPanel->createSequentialGroup().addGap().addWidgets(sendStatsToggleButtonLabel, sendStatsQuestionMark, sendStatsToggleButton), loginPanel->createSequentialGroup().addGap().addWidget(createNewAccountButton).addGap()), loginPanel->createParallelGroup().addMinGap(50))));
	//
	//
	//   loginPanel->setVerticalGroup(loginPanel->createSequentialGroup(loginPanel->createSequentialGroup().addMinGap(20), loginPanel->createParallelGroup(loginPanelLabel), loginPanel->createSequentialGroup().addMinGap(20), loginPanel->createParallelGroup(errorLabel), loginPanel->createParallelGroup(statusLabel), loginPanel->createSequentialGroup().addMinGap(10), loginPanel->createParallelGroup(loginWithFacebookButton), loginPanel->createSequentialGroup().addMinGap(10), loginPanel->createParallelGroup(emailLabel, emailEditField), loginPanel->createParallelGroup(passwordLabel, passwordEditField), loginPanel->createParallelGroup(forgotPasswordButton, loginButton), loginPanel->createSequentialGroup().addMinGap(10), loginPanel->createParallelGroup(stayLoggedInToggleButtonLabel, stayLoggedInToggleButton), loginPanel->createParallelGroup(sendStatsToggleButtonLabel, sendStatsQuestionMark, sendStatsToggleButton), loginPanel->createSequentialGroup().addMinGap(20), loginPanel->createParallelGroup(createNewAccountButton), loginPanel->createSequentialGroup().addMinGap(50)));
	//
	//
	//   //---------------------------------------------------------
	//   //layout
	//   //---------------------------------------------------------
	//
	//   insideScrollPaneLayout->setHorizontalGroup(insideScrollPaneLayout->createParallelGroup(insideScrollPaneLayout->createSequentialGroup().addGap().addWidget(loginPanel).addGap()));
	//
	//   insideScrollPaneLayout->setVerticalGroup(insideScrollPaneLayout->createSequentialGroup(insideScrollPaneLayout->createSequentialGroup().addGap(), insideScrollPaneLayout->createParallelGroup().addWidget(loginPanel), insideScrollPaneLayout->createSequentialGroup().addGap()));
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
	//   scrollPane->setExpandContentSize(true);
	//
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
	//   loginPanel->adjustSize();


	setActivated(true);
}

//
//LoginScreen::CallbackAnonymousInnerClassHelper::CallbackAnonymousInnerClassHelper(LoginScreen* outerInstance)
//{
//   this->outerInstance = outerInstance;
//}
//
//void LoginScreen::CallbackAnonymousInnerClassHelper::callback(int key)
//{
//   if (key == Event::KEY_RETURN)
//   {
//      outerInstance->doLogin();
//   }
//   else
//   {
//      if (outerInstance->passwordEditField->getTextLength() > 0)
//      {
//      }
//      else
//      {
//         if (outerInstance->passwordEditField->getTextLength() == 0)
//         {
//         }
//      }
//   }
//}

void LoginScreen::update()
{ //=========================================================================================================================
	MenuPanel::update();


	if (loggedIn == true)
	{
		if (getIsActivated() == false)
		{
			if (getIsScrollingDown() == false)
			{
				Main::getMain()->stateManager->setState(Main::getMain()->gameEngine);
			}
		}
	}

	Main::glowTileBackground->update();
}

void LoginScreen::onScrolledUp()
{ //=========================================================================================================================

	//   getGUI().setTooltipDelay(1);
	//
	//   sendStatsQuestionMark->setTooltipContent(Main::mainObject->clientInfo->printString());
	//
	//
	//   emailEditField->requestKeyboardFocus();

	checkForSessionTokenAndLogInIfExists();
}

void LoginScreen::layout()
{ //=========================================================================================================================

	//login panel is centered
	//
	//   loginPanel->adjustSize();
	//   loginPanel->setPosition(insideScrollPaneLayout->getInnerX() + (insideScrollPaneLayout->getInnerWidth() - loginPanel->getWidth()) / 2, insideScrollPaneLayout->getInnerY() + (insideScrollPaneLayout->getInnerHeight() - loginPanel->getHeight()) / 2);

	MenuPanel::layout();
}

void LoginScreen::setButtonsVisible(bool b)
{ //=========================================================================================================================

	//   emailEditField->setVisible(b);
	//   passwordEditField->setVisible(b);
	//   loginButton->setVisible(b);
	//   createNewAccountButton->setVisible(b);
	//   forgotPasswordButton->setVisible(b);
	//   emailLabel->setVisible(b);
	//   passwordLabel->setVisible(b);
	//   stayLoggedInToggleButton->setVisible(b);
	//   stayLoggedInToggleButtonLabel->setVisible(b);
	//   sendStatsToggleButton->setVisible(b);
	//   sendStatsToggleButtonLabel->setVisible(b);
	//   sendStatsQuestionMark->setVisible(b);
	//
	//   if (Main::isApplet == true)
	//   {
	//      loginWithFacebookButton->setVisible(b);
	//   }
}

void LoginScreen::doLoginWithFacebook()
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
	//         //if we are an applet we are here
	//
	//
	//         //connect through JSObject and get these from browser
	//         if (Main::browser != nullptr)
	//         {
	//            Main::browser->eval("loginWithFacebook();");
	//         }
	//
	//
	//         //this will use the Facebook JS SDK to open an OAuth dialog
	//         //if they authorize, it calls the function Main.setFacebookCredentials(String facebookID, String accessToken)
	//
	//         //so we need to wait until that gets filled in
	//
	//
	//         int responseTries = 0;
	//         bool gotResponse = false;
	//         while (gotResponse == false)
	//         {
	//            gotResponse = Main::getGotFacebookResponse_S();
	//
	//            if (gotResponse == false)
	//            {
	//               responseTries++;
	//               if (responseTries > 10)
	//               {
	//                  responseTries = 0;
	//                  statusLabel->setText(" ");
	//                  errorLabel->setText("Error: Did not receive a response from the Facebook OAuth dialog.");
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
	//         string facebookID = Main::facebookID;
	//         string accessToken = Main::facebookAccessToken;
	//
	//
	//         if (facebookID == "cancelled")
	//         {
	//            statusLabel->setText(" ");
	//            errorLabel->setText("Cancelled Facebook authorization?");
	//
	//            setButtonsVisible(true);
	//
	//            return;
	//         }
	//
	//
	//         //ask server to check database for facebook ID
	//         //if they already have an account, log them in. (set cookie, set session token file)
	//         //if not we insert a new account into the database based on facebookID and then send them a bobsgame account password to their email.
	//         //we'll assume the email address is valid because it's already verified with facebook so set verified to true and log them in.
	//         //also initialize facebook friends
	//
	//         getServerConnection()->sendFacebookLoginCreateAccountIfNotExist(facebookID, accessToken, sendStatsToggleButton->isActive());
	//
	//
	//         //this will send back a facebookLoginResponse
	//         statusLabel->setText("Logging in with Facebook...");
	//         errorLabel->setText("");
	//
	//
	//         //-------------------------------
	//         //check to see if password response every 1 second
	//         //-------------------------------
	//         int passwordTries = 0;
	//         gotResponse = false;
	//         while (gotResponse == false)
	//         {
	//            gotResponse = getServerConnection()->getGotFacebookLoginResponse_S();
	//
	//            if (gotResponse == false)
	//            {
	//               passwordTries++;
	//               if (passwordTries > 10)
	//               {
	//                  passwordTries = 0;
	//
	//                  statusLabel->setText("Timed out. Trying again...");
	//                  errorLabel->setText("");
	//
	//
	//                  getServerConnection()->sendFacebookLoginCreateAccountIfNotExist(facebookID, accessToken, sendStatsToggleButton->isActive());
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
	//
	//         //we have the response, now lets see if it was a valid login (two steps)
	//         bool passValid = getServerConnection()->getWasFacebookLoginResponseValid_S();
	//
	//         //reset the response state in case we need to try again
	//         getServerConnection()->setGotFacebookLoginResponse_S(false);
	//
	//         if (passValid)
	//         {
	//            errorLabel->setText(" ");
	//            statusLabel->setText("Login with Facebook successful!");
	//
	//            try
	//            {
	//               delay(1000);
	//            }
	//            catch (exception& e)
	//            {
	//               e.printStackTrace();
	//            }
	//
	//
	//            //-------------------------------------------------------
	//            if (Main::isApplet == true)
	//            {
	//               Cache::writeBrowserSessionCookieAndRefreshIFrame();
	//            }
	//
	//
	//            if (stayLoggedInToggleButton->isActive())
	//            {
	//               if (Main::isApplet == true)
	//               {
	//                  Cache::writeBrowserSessionCookieAndRefreshIFrame();
	//               }
	//
	//               Main::cacheManager->writeSessionTokenToCache(getServerConnection()->getUserID_S(), getServerConnection()->getSessionToken_S(), sendStatsToggleButton->isActive());
	//               //String temp = Main.cacheManager.readSessionTokenFromCache();
	//               //log.debug("Read session: "+temp);
	//               //Main.cacheManager.deleteSessionTokenFromCache();
	//               //temp = Main.cacheManager.readSessionTokenFromCache();
	//               //log.debug("Deleted session: "+temp);
	//            }
	//
	//            //-------------------------------------------------------
	//
	//            setActivated(false);
	//            loggedIn = true;
	//         }
	//         else
	//         {
	//            //-------------------------------------------------------
	//            if (Main::isApplet == true)
	//            {
	//               Cache::deleteBrowserSessionCookieAndRefreshIFrame();
	//            }
	//
	//            //delete session cookie if there is one
	//            Main::cacheManager->deleteSessionTokenFromCache();
	//
	//            //-------------------------------------------------------
	//
	//            statusLabel->setText(" ");
	//            errorLabel->setText("Something went wrong, and I have no idea why! I'll check it out.\nIf you have played before, try logging in with your email/password. If not, create an account.");
	//
	//            try
	//            {
	//               delay(2000);
	//            }
	//            catch (exception& e)
	//            {
	//               e.printStackTrace();
	//            }
	//
	//            setButtonsVisible(true);
	//
	//            return;
	//         }
	//
	//
	//         getServerConnection()->sendOnlineFriendListRequest();
	//
	//
	//         statusLabel->setText(" ");
	//         errorLabel->setText(" ");
	//
	//         setButtonsVisible(true);
	//      }
	//   )
	//   .
	//   start();
}

void LoginScreen::doCreateNewAccount()
{ //=========================================================================================================================
	Main::getMain()->stateManager->setState(Main::getMain()->createNewAccountState);
	Main::getMain()->createNewAccountState->createNewAccount->setActivated(true);
}

void LoginScreen::doForgotPassword()
{ //=========================================================================================================================
	//send forgot password request to server, wait for response

	//
	//   GUI* gui = getGUI();
	//   if (gui != nullptr)
	//   {
	//      setButtonsVisible(false);
	//
	//      //create thread, this needs to be a thread because Button.doCallback(Runnable) only calls Runnable.run() which does NOT create a thread.
	//      new Thread([&] ()
	//         {
	//            try
	//            {
	//               Thread::currentThread().setName("LoginScreen_doForgotPassword");
	//            }
	//            catch (SecurityException e)
	//            {
	//               e->printStackTrace();
	//            }
	//
	//            statusLabel->setText(" ");
	//            errorLabel->setText(" ");
	//
	//            if (emailEditField->getText()->contains("`"))
	//            {
	//               errorLabel->setText("Email must not contain `");
	//               setButtonsVisible(true);
	//               return;
	//            }
	//            if (emailEditField->getText().length() == 0)
	//            {
	//               errorLabel->setText("Enter your email address.");
	//               setButtonsVisible(true);
	//               return;
	//            }
	//            if (emailEditField->getText()->contains("@") == false)
	//            {
	//               errorLabel->setText("Email address must contain @");
	//               setButtonsVisible(true);
	//               return;
	//            }
	//
	//            //if(passwordEditField.getText().contains("`")){errorLabel.setText("Password must not contain `");setButtonsVisible(true);return;}
	//            //if(passwordEditField.getText().length()==0){errorLabel.setText("Please enter a password.");setButtonsVisible(true);return;}
	//
	//
	//            //if email address blank, say "please type email address"
	//            //if password is blank, say "must type password"
	//            //check if email address is valid
	//            //may not contain `
	//
	//            //say "trying to connect to server"
	//            errorLabel->setText(" ");
	//            statusLabel->setText("Connecting to server...");
	//
	//            bool connected = getServerConnection()->getConnectedToServer_S();
	//
	//            if (connected == false)
	//            {
	//               getServerConnection()->connectToServer();
	//
	//               //-------------------------------
	//               //check to see if connected every 1 second
	//               //when connected, proceed.
	//               //-------------------------------
	//               int tries = 0;
	//               while (connected == false)
	//               {
	//                  connected = getServerConnection()->getConnectedToServer_S();
	//
	//                  if (connected == false)
	//                  {
	//                     tries++;
	//
	//                     //make dots cycle
	//                     string dots = "";
	//                     for (int i = 0; i < tries % 4; i++)
	//                     {
	//                        dots = dots.concat(".");
	//                     }
	//                     errorLabel->setText(" ");
	//                     statusLabel->setText(string("Connecting to server") + dots);
	//
	//                     if (tries > 10)
	//                     {
	//                        tries = 0;
	//                        errorLabel->setText(" ");
	//                        statusLabel->setText("Error: Could not connect to server.");
	//
	//                        setButtonsVisible(true);
	//
	//                        return;
	//                     }
	//
	//                     try
	//                     {
	//                        delay(1000);
	//                     }
	//                     catch (exception& e)
	//                     {
	//                        e.printStackTrace();
	//                     }
	//                  }
	//               }
	//            }
	//
	//            if (connected == true)
	//            {
	//               errorLabel->setText(" ");
	//               statusLabel->setText("Connected! Sending account recovery request...");
	//            }
	//
	//            getServerConnection()->sendPasswordRecoveryRequest_S(emailEditField->getText());
	//
	//            //-------------------------------
	//            //check to see if password response every 1 second
	//            //-------------------------------
	//            int passwordTries = 0;
	//            bool gotResponse = false;
	//            while (gotResponse == false)
	//            {
	//               gotResponse = getServerConnection()->getGotPasswordRecoveryResponse_S();
	//
	//               if (gotResponse == false)
	//               {
	//                  passwordTries++;
	//                  if (passwordTries > 10)
	//                  {
	//                     passwordTries = 0;
	//                     statusLabel->setText(" ");
	//                     errorLabel->setText("Error: Timed out sending request. Please try again.");
	//
	//                     setButtonsVisible(true);
	//
	//                     return;
	//                  }
	//
	//                  try
	//                  {
	//                     delay(1000);
	//                  }
	//                  catch (exception& e)
	//                  {
	//                     e.printStackTrace();
	//                  }
	//               }
	//            }
	//
	//            //reset the response state in case we need to try again
	//            getServerConnection()->setGotPasswordRecoveryResponse_S(false);
	//
	//            //say "an email was sent if the account was registered"
	//            errorLabel->setText(" ");
	//            statusLabel->setText("If the account exists, a recovery email was sent. Please check your email.");
	//
	//            try
	//            {
	//               delay(3000);
	//            }
	//            catch (exception& e)
	//            {
	//               e.printStackTrace();
	//            }
	//
	//            setButtonsVisible(true);
	//         }
	//      )
	//      .
	//      start();
	//   }
}

void LoginScreen::doLogin()
{ //=========================================================================================================================
	//   GUI* gui = getGUI();
	//   if (gui != nullptr)
	//   {
	//      setButtonsVisible(false);
	//
	//      //create thread, needs to be a thread because Button.doCallback only calls Runnable.run() which does NOT create a thread
	//      new Thread([&] ()
	//         {
	//            try
	//            {
	//               Thread::currentThread().setName("LoginScreen_doLogin");
	//            }
	//            catch (SecurityException e)
	//            {
	//               e->printStackTrace();
	//            }
	//
	//            statusLabel->setText(" ");
	//            errorLabel->setText(" ");
	//
	//            if (emailEditField->getText()->contains("`"))
	//            {
	//               errorLabel->setText("Email must not contain `");
	//               setButtonsVisible(true);
	//               return;
	//            }
	//            if (emailEditField->getText().length() == 0)
	//            {
	//               errorLabel->setText("Enter your email address.");
	//               setButtonsVisible(true);
	//               return;
	//            }
	//            if (emailEditField->getText()->contains("@") == false)
	//            {
	//               errorLabel->setText("Email address must contain @");
	//               setButtonsVisible(true);
	//               return;
	//            }
	//
	//            if (passwordEditField->getText()->contains("`"))
	//            {
	//               errorLabel->setText("Password must not contain `");
	//               setButtonsVisible(true);
	//               return;
	//            }
	//            if (passwordEditField->getText().length() == 0)
	//            {
	//               errorLabel->setText("Please enter a password.");
	//               setButtonsVisible(true);
	//               return;
	//            }
	//
	//            //if email address blank, say "please type email address"
	//            //if password is blank, say "must type password"
	//            //check if email address is valid
	//            //may not contain `
	//
	//            //say "trying to connect to server"
	//
	//            errorLabel->setText(" ");
	//            statusLabel->setText("Connecting to server...");
	//
	//            bool connected = getServerConnection()->getConnectedToServer_S();
	//
	//            if (connected == false)
	//            {
	//               getServerConnection()->connectToServer();
	//
	//               //-------------------------------
	//               //check to see if connected every 1 second
	//               //when connected, proceed.
	//               //-------------------------------
	//               int tries = 0;
	//               while (connected == false)
	//               {
	//                  connected = getServerConnection()->getConnectedToServer_S();
	//
	//                  if (connected == false)
	//                  {
	//                     tries++;
	//
	//                     //make dots cycle
	//                     string dots = "";
	//                     for (int i = 0; i < tries % 4; i++)
	//                     {
	//                        dots = dots.concat(".");
	//                     }
	//                     errorLabel->setText(" ");
	//                     statusLabel->setText(string("Connecting to server") + dots);
	//
	//                     if (tries > 10)
	//                     {
	//                        tries = 0;
	//                        statusLabel->setText(" ");
	//                        errorLabel->setText("Error: Could not connect to server.");
	//
	//                        setButtonsVisible(true);
	//
	//                        return;
	//                     }
	//
	//                     try
	//                     {
	//                        delay(1000);
	//                     }
	//                     catch (exception& e)
	//                     {
	//                        e.printStackTrace();
	//                     }
	//                  }
	//               }
	//            }
	//
	//            if (connected == true)
	//            {
	//               errorLabel->setText(" ");
	//               statusLabel->setText("Connected! Checking login...");
	//            }
	//
	//            getServerConnection()->sendLoginRequest(emailEditField->getText(), passwordEditField->getText(), sendStatsToggleButton->isActive());
	//
	//            //-------------------------------
	//            //check to see if password response every 1 second
	//            //-------------------------------
	//            int passwordTries = 0;
	//            bool gotResponse = false;
	//            while (gotResponse == false)
	//            {
	//               gotResponse = getServerConnection()->getGotLoginResponse_S();
	//
	//               if (gotResponse == false)
	//               {
	//                  passwordTries++;
	//                  if (passwordTries > 10)
	//                  {
	//                     passwordTries = 0;
	//                     statusLabel->setText(" ");
	//                     errorLabel->setText("Error: Timed out validating password. Please try again.");
	//
	//                     setButtonsVisible(true);
	//
	//                     return;
	//                  }
	//
	//                  try
	//                  {
	//                     delay(1000);
	//                  }
	//                  catch (exception& e)
	//                  {
	//                     e.printStackTrace();
	//                  }
	//               }
	//            }
	//
	//            //we have the response, now lets see if it was a valid login (two steps)
	//            bool passValid = getServerConnection()->getWasLoginResponseValid_S();
	//
	//            //reset the response state in case we need to try again
	//            getServerConnection()->setGotLoginResponse_S(false);
	//
	//            if (passValid)
	//            {
	//               errorLabel->setText(" ");
	//               statusLabel->setText("Login successful!");
	//
	//               try
	//               {
	//                  delay(1000);
	//               }
	//               catch (exception& e)
	//               {
	//                  e.printStackTrace();
	//               }
	//
	//
	//               //-------------------------------------------------------
	//               if (Main::isApplet == true)
	//               {
	//                  //TODO: write session cookie, refresh iFrame
	//               }
	//
	//
	//               if (stayLoggedInToggleButton->isActive())
	//               {
	//                  if (Main::isApplet == true)
	//                  {
	//                     //TODO: write browser cookie
	//                  }
	//
	//                  Main::cacheManager->writeSessionTokenToCache(getServerConnection()->getUserID_S(), getServerConnection()->getSessionToken_S(), sendStatsToggleButton->isActive());
	//                  //String temp = Main.cacheManager.readSessionTokenFromCache();
	//                  //log.debug("Read session: "+temp);
	//                  //Main.cacheManager.deleteSessionTokenFromCache();
	//                  //temp = Main.cacheManager.readSessionTokenFromCache();
	//                  //log.debug("Deleted session: "+temp);
	//               }
	//
	//               //-------------------------------------------------------
	//
	//
	//               //setEnabled(false);
	//               setActivated(false);
	//               loggedIn = true;
	//            }
	//            else
	//            {
	//               //-------------------------------------------------------
	//
	//               if (Main::isApplet == true)
	//               {
	//                  //TODO: delete browser cookie, refresh iframe
	//               }
	//
	//               //delete session cookie if there is one
	//               Main::cacheManager->deleteSessionTokenFromCache();
	//
	//
	//               //-------------------------------------------------------
	//
	//
	//               //say "password wrong or account doesn't exist"
	//               statusLabel->setText(" ");
	//               errorLabel->setText("Error: Password incorrect, account doesn't exist, or account isn't verified yet.\n If you just signed up, please check your email and click the verification link.");
	//
	//               try
	//               {
	//                  delay(2000);
	//               }
	//               catch (exception& e)
	//               {
	//                  e.printStackTrace();
	//               }
	//
	//               setButtonsVisible(true);
	//
	//               return;
	//            }
	//         }
	//      )
	//      .
	//      start();
	//   }
}

void LoginScreen::checkForSessionTokenAndLogInIfExists()
{ //=========================================================================================================================


//	if (Main::isApplet == true)
//	{
//		//TODO: check for browser cookie, session or permanent
//	}


	//check cache for session token
	//if session token cache exists, try to log in with that.
	//set browser cookie, refresh iframe

	log.debug("Checking for Session Token");

	const string token = FileUtils::readSessionTokenFromCache();

	if (token != "")
	{
		log.debug("Session Token Found");
	}
	else
	{
		log.debug("Session Token not found in cache.");
	}

	if (token != "")
	{
		//
		//      GUI* gui = getGUI();
		//      if (gui != nullptr)
		//      {
		//         setButtonsVisible(false);
		//
		//         //create thread
		//         new Thread([&] ()
		//            {
		//               try
		//               {
		//                  Thread::currentThread().setName("LoginScreen_checkForSessionTokenAndLogInIfExists");
		//               }
		//               catch (SecurityException e)
		//               {
		//                  e->printStackTrace();
		//               }
		//
		//               //token = userId,`sessionToken`,statsAllowed
		//               string s = token;
		//
		//               long long userID = -1;
		//               try
		//               {
		//                  userID = stoll(s.substr(0, s.find(",")));
		//               }
		//               catch (NumberFormatException ex)
		//               {
		//                  ex->printStackTrace();
		//                  return;
		//               }
		//               s = s.substr(s.find("`") + 1); //sessionToken`,statsAllowed
		//               string sessionToken = s.substr(0, s.find("`"));
		//               s = s.substr(s.find(",") + 1); //statsAllowed
		//               bool statsAllowed = StringConverterHelper::fromString<bool>(s);
		//
		//
		//               errorLabel->setText(" ");
		//               statusLabel->setText("Existing session found! Connecting to server...");
		//
		//               bool connected = getServerConnection()->getConnectedToServer_S();
		//
		//               if (connected == false)
		//               {
		//                  getServerConnection()->connectToServer();
		//
		//                  //-------------------------------
		//                  //check to see if connected every 1 second
		//                  //when connected, proceed.
		//                  //-------------------------------
		//                  int tries = 0;
		//                  while (connected == false)
		//                  {
		//                     connected = getServerConnection()->getConnectedToServer_S();
		//
		//                     if (connected == false)
		//                     {
		//                        tries++;
		//
		//                        //make dots cycle
		//                        string dots = "";
		//                        for (int i = 0; i < tries % 4; i++)
		//                        {
		//                           dots = dots.concat(".");
		//                        }
		//                        errorLabel->setText(" ");
		//                        statusLabel->setText(string("Existing session found! Connecting to server") + dots);
		//
		//                        if (tries > 10)
		//                        {
		//                           tries = 0;
		//                           statusLabel->setText(" ");
		//                           errorLabel->setText("Error: Could not connect to server.");
		//
		//                           setButtonsVisible(true);
		//
		//                           return;
		//                        }
		//
		//                        try
		//                        {
		//                           delay(1000);
		//                        }
		//                        catch (exception& e)
		//                        {
		//                           e.printStackTrace();
		//                        }
		//                     }
		//                  }
		//               }
		//
		//               if (connected == true)
		//               {
		//                  errorLabel->setText(" ");
		//                  statusLabel->setText("Connected! Checking session...");
		//               }
		//
		//               getServerConnection()->sendReconnectRequest(userID, sessionToken, statsAllowed);
		//
		//               //-------------------------------
		//               //check to see if password response every 1 second
		//               //-------------------------------
		//               int passwordTries = 0;
		//               bool gotResponse = false;
		//               while (gotResponse == false)
		//               {
		//                  gotResponse = getServerConnection()->getGotReconnectResponse_S();
		//
		//                  if (gotResponse == false)
		//                  {
		//                     passwordTries++;
		//                     if (passwordTries > 10)
		//                     {
		//                        passwordTries = 0;
		//                        statusLabel->setText(" ");
		//                        errorLabel->setText("Error: Timed out validating session. Please try again.");
		//
		//                        setButtonsVisible(true);
		//
		//                        return;
		//                     }
		//
		//                     try
		//                     {
		//                        delay(1000);
		//                     }
		//                     catch (exception& e)
		//                     {
		//                        e.printStackTrace();
		//                     }
		//                  }
		//               }
		//
		//               //we have the response, now lets see if it was a valid login (two steps)
		//               bool passValid = getServerConnection()->getWasReconnectResponseValid_S();
		//
		//               //reset the response state in case we need to try again
		//               getServerConnection()->setGotReconnectResponse_S(false);
		//
		//               if (passValid)
		//               {
		//                  errorLabel->setText(" ");
		//                  statusLabel->setText("Login successful!");
		//
		//                  try
		//                  {
		//                     delay(1000);
		//                  }
		//                  catch (exception& e)
		//                  {
		//                     e.printStackTrace();
		//                  }
		//
		//
		//                  //-------------------------------------------------------
		//
		//                  if (Main::isApplet == true)
		//                  {
		//                     //TODO: write session cookie, refresh iFrame
		//                     //TODO: write browser cookie
		//                  }
		//
		//
		//                  //-------------------------------------------------------
		//
		//                  //setEnabled(false);
		//                  setActivated(false);
		//                  loggedIn = true;
		//               }
		//               else
		//               {
		//                  //-------------------------------------------------------
		//                  if (Main::isApplet == true)
		//                  {
		//                     //TODO: delete browser cookie, refresh iframe
		//                  }
		//
		//                  //delete session cookie if there is one
		//                  Main::cacheManager->deleteSessionTokenFromCache();
		//
		//                  //-------------------------------------------------------
		//
		//
		//                  statusLabel->setText(" ");
		//                  errorLabel->setText("Error: Session was not valid. Please log in.");
		//
		//                  try
		//                  {
		//                     delay(2000);
		//                  }
		//                  catch (exception& e)
		//                  {
		//                     e.printStackTrace();
		//                  }
		//
		//                  setButtonsVisible(true);
		//
		//                  return;
		//               }
		//            }
		//         )
		//         .
		//         start();
		//      }
	}
}

void LoginScreen::showStatsDialogue()
{ //=========================================================================================================================
}

void LoginScreen::renderBefore()
{ //=========================================================================================================================


	if (getIsScrollingDown() == true)
	{
		return;
	}
	if (getIsActivated() == false)
	{
		return;
	}
	//additional rendering calls go here (after gui is drawn)


	Main::glowTileBackground->render();
}

void LoginScreen::render()
{ //=========================================================================================================================


	if (getIsScrollingDown() == true)
	{
		return;
	}
	if (getIsActivated() == false)
	{
		return;
	}

	//additional rendering calls go here (after gui is drawn)
}

