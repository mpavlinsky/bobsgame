#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger ControlsPanel::log = Logger("ControlsPanel");


ControlsPanel::ControlsPanel()
{ //=========================================================================================================================

	SubPanel();
	//
	//
	//   Label* mainControlsLabel = new Label("Main Controls");
	//   mainControlsLabel->setCanAcceptKeyboardFocus(false);
	//   mainControlsLabel->setTheme("helpLabelBig");
	//
	//
	//   /*
	//      Label wasdLabel = new Label("(You can also control movement with \"WASD\")");
	//      wasdLabel.setCanAcceptKeyboardFocus(false);
	//      wasdLabel.setTheme("helpLabelSmall");
	//                           */
	//
	//
	//   //up down left right wasd
	//
	//   //zoom in/out
	//   //TODO: add mousewheel for this
	//
	//   //TODO: add mouse click controls
	//
	//   //TODO: add gameController support
	//
	//
	//   Widget* keyboardImagePanel = new WidgetAnonymousInnerClassHelper(this);
	//   keyboardImagePanel->setTheme("keyboardImagePanel");
	//
	//
	//   //		Label otherControlsLabel = new Label("Other Controls:");
	//   //		otherControlsLabel.setCanAcceptKeyboardFocus(false);
	//   //		otherControlsLabel.setTheme("helpLabelBig");
	//   //
	//   //		Label otherControlsTextLabel = new Label("F12 - Take Screenshot");
	//   //		otherControlsTextLabel.setCanAcceptKeyboardFocus(false);
	//   //		otherControlsTextLabel.setTheme("helpLabelSmall");
	//
	//
	//   Label* gameControllerSetupLabel = new Label("Game Controller Setup");
	//   gameControllerSetupLabel->setCanAcceptKeyboardFocus(false);
	//   gameControllerSetupLabel->setTheme("helpLabelBig");
	//
	//
	//   Label* gameControllerInfoLabel = new Label("\"bob's game\" supports most USB Game Controllers. Please plug your controller in before starting the game.");
	//   gameControllerInfoLabel->setCanAcceptKeyboardFocus(false);
	//   gameControllerInfoLabel->setTheme("helpLabelSmall");
	//
	//
	//   /*
	//         Label scrollDownLabel = new Label("In the \"Stuff Menu,\" you can click with the mouse and scroll down with the mouse wheel.");
	//         scrollDownLabel.setCanAcceptKeyboardFocus(false);
	//         scrollDownLabel.setTheme("helpLabelSmall");
	//   */
	//
	//
	//   DialogLayout* gameControllerLayout = new DialogLayout();
	//   gameControllerLayout->setCanAcceptKeyboardFocus(false);
	//   gameControllerLayout->setTheme("gameControllerSetupLayout");
	//
	//
	//   int buttons = 10;
	//
	//   ArrayList<Label*> buttonLabel(buttons);
	//   buttonValueLabel = ArrayList<Label*>(buttons);
	//   ArrayList<Button*> buttonButton(buttons);
	//
	//   ArrayList<DialogLayout*> buttonLayout(buttons);
	//
	//
	//   for (int i = 0; i < buttons; i++)
	//   {
	//      buttonLabel[i] = new Label("");
	//      buttonLabel[i]->setCanAcceptKeyboardFocus(false);
	//      buttonLabel[i]->setTheme("font16PurpleOutline");
	//
	//      buttonValueLabel[i] = new Label("NONE");
	//      buttonValueLabel[i]->setCanAcceptKeyboardFocus(false);
	//      buttonValueLabel[i]->setTheme("font11WhiteOutline");
	//
	//      buttonButton[i] = new Button("Set");
	//      buttonButton[i]->setCanAcceptKeyboardFocus(false);
	//
	//      const int threadi = i;
	//
	//      buttonButton[i]->addCallback([&] () //even though this is a runnable, it is NOT a thread. fireCallback just calls Runnable.run() which does not create a thread.
	//         {
	//            new Thread([&] ()
	//               {
	//                  try
	//                  {
	//                     Thread::currentThread().setName("ControlsPanel_setGameControllerInput");
	//                  }
	//                  catch (SecurityException e)
	//                  {
	//                     e->printStackTrace();
	//                  }
	//
	//                  int timer = 10000;
	//                  buttonValueLabel[threadi]->setText(string("Waiting for Game Controller input: ") + to_string(timer / 1000));
	//
	//                  //Controllers.clearEvents();
	//
	//
	//                  bool stop = false;
	//                  while (stop == false)
	//                  {
	//                     Controllers::poll();
	//
	//                     try
	//                     {
	//                        delay(100);
	//                     }
	//                     catch (InterruptedException e)
	//                     {
	//                        e->printStackTrace();
	//                     }
	//
	//                     timer -= 100;
	//                     if (timer <= 0)
	//                     {
	//                        buttonValueLabel[threadi]->setText("NONE");
	//                        return;
	//                     }
	//
	//                     buttonValueLabel[threadi]->setText(string("Waiting for Game Controller input: ") + to_string(timer / 1000));
	//
	//
	//                     while (Controllers->next() == true)
	//                     {
	//                        Controller* c = Controllers::getEventSource();
	//
	//
	//                        float val = 0.0f;
	//
	//                        val = c->getXAxisValue();
	//                        if (abs(val) > 0.5f && abs(val) < 1.0f)
	//                        {
	//                           if (val < 0)
	//                           {
	//                              val = -1.0f;
	//                           }
	//                           if (val > 0)
	//                           {
	//                              val = 1.0f;
	//                           }
	//
	//                           while (c->getXAxisValue() != 0.0f)
	//                           {
	//                              Controllers::clearEvents();
	//                              Controllers::poll();
	//                           }
	//
	//                           buttonValueLabel[threadi]->setText(string("Left Analog X Axis ") + to_string(val));
	//
	//                           if (val < 0)
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_LeftAnalog_XAxis_Negative);
	//                           }
	//                           else
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_LeftAnalog_XAxis_Positive);
	//                           }
	//
	//                           Engine::getControlsManager()->controller = c;
	//
	//                           return;
	//                        }
	//
	//                        val = c->getYAxisValue();
	//                        if (abs(val) > 0.5f && abs(val) < 1.0f)
	//                        {
	//                           if (val < 0)
	//                           {
	//                              val = -1.0f;
	//                           }
	//                           if (val > 0)
	//                           {
	//                              val = 1.0f;
	//                           }
	//
	//                           while (c->getYAxisValue() != 0.0f)
	//                           {
	//                              Controllers::clearEvents();
	//                              Controllers::poll();
	//                           }
	//
	//                           buttonValueLabel[threadi]->setText(string("Left Analog Y Axis ") + to_string(val));
	//
	//                           if (val < 0)
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_LeftAnalog_YAxis_Negative);
	//                           }
	//                           else
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_LeftAnalog_YAxis_Positive);
	//                           }
	//
	//                           Engine::getControlsManager()->controller = c;
	//
	//                           return;
	//                        }
	//
	//                        val = c->getZAxisValue();
	//                        if (abs(val) > 0.5f && abs(val) < 1.0f)
	//                        {
	//                           if (val < 0)
	//                           {
	//                              val = -1.0f;
	//                           }
	//                           if (val > 0)
	//                           {
	//                              val = 1.0f;
	//                           }
	//
	//                           while (c->getZAxisValue() != 0.0f)
	//                           {
	//                              Controllers::clearEvents();
	//                              Controllers::poll();
	//                           }
	//
	//                           buttonValueLabel[threadi]->setText(string("Z Axis ") + to_string(val));
	//
	//                           if (val < 0)
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_LeftAnalog_ZAxis_Negative);
	//                           }
	//                           else
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_LeftAnalog_ZAxis_Positive);
	//                           }
	//
	//                           Engine::getControlsManager()->controller = c;
	//
	//                           return;
	//                        }
	//
	//                        val = c->getPovX();
	//                        if (abs(val) > 0.5f)
	//                        {
	//                           if (val < 0)
	//                           {
	//                              val = -1.0f;
	//                           }
	//                           if (val > 0)
	//                           {
	//                              val = 1.0f;
	//                           }
	//
	//                           while (c->getPovX() != 0.0f)
	//                           {
	//                              Controllers::clearEvents();
	//                              Controllers::poll();
	//                           }
	//
	//                           buttonValueLabel[threadi]->setText(string("Pov X ") + to_string(val));
	//
	//                           if (val < 0)
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_POV_X_Negative);
	//                           }
	//                           else
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_POV_X_Positive);
	//                           }
	//
	//                           Engine::getControlsManager()->controller = c;
	//
	//                           return;
	//                        }
	//
	//                        val = c->getPovY();
	//                        if (abs(val) > 0.5f)
	//                        {
	//                           if (val < 0)
	//                           {
	//                              val = -1.0f;
	//                           }
	//                           if (val > 0)
	//                           {
	//                              val = 1.0f;
	//                           }
	//
	//                           while (c->getPovY() != 0.0f)
	//                           {
	//                              Controllers::clearEvents();
	//                              Controllers::poll();
	//                           }
	//
	//                           buttonValueLabel[threadi]->setText(string("Pov Y ") + to_string(val));
	//
	//                           if (val < 0)
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_POV_Y_Negative);
	//                           }
	//                           else
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_POV_Y_Positive);
	//                           }
	//
	//                           Engine::getControlsManager()->controller = c;
	//
	//                           return;
	//                        }
	//
	//                        val = c->getRXAxisValue();
	//                        if (abs(val) > 0.5f && abs(val) < 1.0f)
	//                        {
	//                           if (val < 0)
	//                           {
	//                              val = -1.0f;
	//                           }
	//                           if (val > 0)
	//                           {
	//                              val = 1.0f;
	//                           }
	//
	//                           while (c->getRXAxisValue() != 0.0f)
	//                           {
	//                              Controllers::clearEvents();
	//                              Controllers::poll();
	//                           }
	//
	//                           buttonValueLabel[threadi]->setText(string("Right Analog X Axis ") + to_string(val));
	//
	//                           if (val < 0)
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_RightAnalog_XAxis_Negative);
	//                           }
	//                           else
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_RightAnalog_XAxis_Positive);
	//                           }
	//
	//                           Engine::getControlsManager()->controller = c;
	//
	//                           return;
	//                        }
	//
	//                        val = c->getRYAxisValue();
	//                        if (abs(val) > 0.5f && abs(val) < 1.0f)
	//                        {
	//                           if (val < 0)
	//                           {
	//                              val = -1.0f;
	//                           }
	//                           if (val > 0)
	//                           {
	//                              val = 1.0f;
	//                           }
	//
	//                           while (c->getRYAxisValue() != 0.0f)
	//                           {
	//                              Controllers::clearEvents();
	//                              Controllers::poll();
	//                           }
	//
	//                           buttonValueLabel[threadi]->setText(string("Right Analog Y Axis ") + to_string(val));
	//
	//                           if (val < 0)
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_RightAnalog_YAxis_Negative);
	//                           }
	//                           else
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_RightAnalog_YAxis_Positive);
	//                           }
	//
	//                           Engine::getControlsManager()->controller = c;
	//
	//                           return;
	//                        }
	//
	//                        val = c->getRZAxisValue();
	//                        if (abs(val) > 0.5f && abs(val) < 1.0f)
	//                        {
	//                           if (val < 0)
	//                           {
	//                              val = -1.0f;
	//                           }
	//                           if (val > 0)
	//                           {
	//                              val = 1.0f;
	//                           }
	//
	//                           while (c->getRZAxisValue() != 0.0f)
	//                           {
	//                              Controllers::clearEvents();
	//                              Controllers::poll();
	//                           }
	//
	//                           buttonValueLabel[threadi]->setText(string("RZ Axis ") + to_string(val));
	//
	//                           if (val < 0)
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_RightAnalog_ZAxis_Negative);
	//                           }
	//                           else
	//                           {
	//                              setButton(threadi, Engine::getControlsManager()->gameController_RightAnalog_ZAxis_Positive);
	//                           }
	//
	//                           Engine::getControlsManager()->controller = c;
	//
	//                           return;
	//                        }
	//
	//
	//                        for (int i = 0; i < c->getButtonCount(); i++)
	//                        {
	//                           if (c->isButtonPressed(i) == true)
	//                           {
	//                              buttonValueLabel[threadi]->setText(string("Button ") + to_string(i));
	//
	//                              while (c->isButtonPressed(i) != false)
	//                              {
	//                                 Controllers::clearEvents();
	//                                 Controllers::poll();
	//                              }
	//
	//                              setButton(threadi, i);
	//
	//                              Engine::getControlsManager()->controller = c;
	//
	//                              return;
	//                           }
	//                        }
	//                     }
	//                  }
	//               }
	//            )
	//            .
	//            start();
	//         }
	//      );
	//
	//
	//      buttonLayout[i] = new DialogLayout();
	//      buttonLayout[i]->setCanAcceptKeyboardFocus(false);
	//
	//      buttonLayout[i]->setHorizontalGroup(buttonLayout[i]->createParallelGroup(buttonLayout[i]->createParallelGroup(buttonLayout[i]->createSequentialGroup().addWidget(buttonButton[i]).addGap().addWidgets(buttonLabel[i], buttonValueLabel[i]).addGap())));
	//
	//      buttonLayout[i]->setVerticalGroup(buttonLayout[i]->createSequentialGroup(buttonLayout[i]->createSequentialGroup(buttonLayout[i]->createParallelGroup(buttonButton[i], buttonLabel[i], buttonValueLabel[i]))));
	//   }
	//
	//   buttonLabel[0]->setText("Up: ");
	//   buttonLabel[1]->setText("Down: ");
	//   buttonLabel[2]->setText("Left: ");
	//   buttonLabel[3]->setText("Right: ");
	//   buttonLabel[4]->setText("Action: ");
	//   buttonLabel[5]->setText("Run/Cancel: ");
	//   buttonLabel[6]->setText("Open nD: ");
	//   buttonLabel[7]->setText("Stuff Menu: ");
	//   buttonLabel[8]->setText("QuickZoom In: ");
	//   buttonLabel[9]->setText("QuickZoom Out: ");
	//
	//
	//   gameControllerLayout->setHorizontalGroup(gameControllerLayout->createParallelGroup(gameControllerLayout->createSequentialGroup().addGap().addGroup(gameControllerLayout->createParallelGroup(buttonLayout)).addGap()));
	//
	//   gameControllerLayout->setVerticalGroup(gameControllerLayout->createSequentialGroup(gameControllerLayout->createSequentialGroup(buttonLayout)));
	//
	//
	//   insideLayout->setHorizontalGroup(insideLayout->createParallelGroup(insideLayout->createParallelGroup(mainControlsLabel), insideLayout->createParallelGroup(keyboardImagePanel), insideLayout->createParallelGroup(gameControllerSetupLabel), insideLayout->createParallelGroup(gameControllerInfoLabel), insideLayout->createParallelGroup(insideLayout->createSequentialGroup().addGap().addGroup(insideLayout->createParallelGroup(gameControllerLayout)).addGap())));
	//   //insideLayout.createParallelGroup(otherControlsLabel),
	//   //insideLayout.createParallelGroup(otherControlsTextLabel),
	//   //insideLayout.createParallelGroup(scrollDownLabel),
	//   //insideLayout.createParallelGroup(wasdLabel),
	//
	//   insideLayout->setVerticalGroup(insideLayout->createSequentialGroup(insideLayout->createSequentialGroup(mainControlsLabel), insideLayout->createSequentialGroup(keyboardImagePanel), insideLayout->createSequentialGroup().addGap(40), insideLayout->createSequentialGroup(gameControllerSetupLabel), insideLayout->createSequentialGroup(gameControllerInfoLabel).addGap(20), insideLayout->createSequentialGroup(gameControllerLayout)));
	//   //insideLayout.createSequentialGroup().addGap(20),
	//   //insideLayout.createSequentialGroup(otherControlsLabel),
	//   //insideLayout.createSequentialGroup(otherControlsTextLabel),
	//   //insideLayout.createSequentialGroup(wasdLabel),
	//   //insideLayout.createSequentialGroup().addGap(20),
	//   //insideLayout.createSequentialGroup(scrollDownLabel),
}

ControlsPanel::WidgetAnonymousInnerClassHelper::WidgetAnonymousInnerClassHelper(ControlsPanel* outerInstance)
{
	this->outerInstance = outerInstance;
}

void ControlsPanel::WidgetAnonymousInnerClassHelper::layout()
{
	//force the keyboard image to fit inside the layout/scrollpane/layout/layout
	//
	//   outerInstance->thisDialogLayout->setBorderSize(0, 20);
	//   outerInstance->insideLayout->setBorderSize(0, 20);
	//   outerInstance->scrollPane->setBorderSize(0, 20);
	//
	//   int w = (int)(outerInstance->thisDialogLayout->getWidth() * 0.80f);
	//   if (w < 0)
	//   {
	//      w = 128;
	//   }
	//
	//   //setMinSize(w,50);
	//   setMaxSize(w, 390);
	//   //adjustSize();
}

void ControlsPanel::setButton(int index, int value)
{ //=========================================================================================================================
	//   if (index == 0)
	//   {
	//      Engine::getControlsManager()->JOY_UP = value;
	//   }
	//   if (index == 1)
	//   {
	//      Engine::getControlsManager()->JOY_DOWN = value;
	//   }
	//   if (index == 2)
	//   {
	//      Engine::getControlsManager()->JOY_LEFT = value;
	//   }
	//   if (index == 3)
	//   {
	//      Engine::getControlsManager()->JOY_RIGHT = value;
	//   }
	//   if (index == 4)
	//   {
	//      Engine::getControlsManager()->JOY_ACTION = value;
	//   }
	//   if (index == 5)
	//   {
	//      Engine::getControlsManager()->JOY_RUN = value;
	//   }
	//   if (index == 6)
	//   {
	//      Engine::getControlsManager()->JOY_ND = value;
	//   }
	//   if (index == 7)
	//   {
	//      Engine::getControlsManager()->JOY_STUFF = value;
	//   }
	//   if (index == 8)
	//   {
	//      Engine::getControlsManager()->JOY_ZOOMIN = value;
	//   }
	//   if (index == 9)
	//   {
	//      Engine::getControlsManager()->JOY_ZOOMOUT = value;
	//   }
}

