#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger FriendManager::log = Logger("FriendManager");


FriendManager::FriendManager(BGClientEngine* g)
{ //===============================================================================================
	this->e = g;
}

void FriendManager::init()
{ //===============================================================================================

	//if (BobNet::debugMode)
	{
		//int timesRun = 0;


		//get file with times run

		//get times run

		//write back with timesrun+1
		//
		//      File* sessionFile = new File("C:\\simulator.txt");
		//
		//      if (sessionFile->exists() == false)
		//      {
		//         try
		//         {
		//            sessionFile->createNewFile();
		//         }
		//         catch (IOException e1)
		//         {
		//            e1->printStackTrace();
		//         }
		//      }
		//
		//
		//      string line = "";
		//
		//      try
		//      {
		//         BufferedReader* input = new BufferedReader(new FileReader(sessionFile));
		//         line = input->readLine();
		//         input->close();
		//      }
		//      catch (IOException e)
		//      {
		//         e->printStackTrace();
		//      }
		//
		//      if (line != "")
		//      {
		//         if (line.length() > 0)
		//         {
		//            timesRun = stoi(line);
		//            log.debug(string("") + to_string(timesRun));
		//         }
		//      }
		//
		//
		//      Writer* output;
		//      try
		//      {
		//         output = new BufferedWriter(new FileWriter(sessionFile));
		//         output->write(string("") + to_string(timesRun + 1));
		//         output->close();
		//      }
		//      catch (IOException e)
		//      {
		//         e->printStackTrace();
		//      }
		//
		//
		//      int myPort = 1111;
		//      int theirPort = 1112;
		//
		//      if (timesRun % 2 == 0)
		//      {
		//         theirPort = 1111;
		//         myPort = 1112;
		//      }
		//
		//
		//      FriendCharacter* f = new FriendCharacter(getGameEngine(), 1, FriendCharacter::FACEBOOK_TYPE, myPort, theirPort);
		//
		//
		//      friendCharacters.push_back(f);
	}
}

void FriendManager::cleanup()
{ //===============================================================================================

	for (int i = 0; i < friendCharacters->size(); i++)
	{
		friendCharacters->get(i)->cleanup();
	}
}

void FriendManager::update()
{ //===============================================================================================

	for (int i = 0; i < friendCharacters->size(); i++)
	{
		friendCharacters->get(i)->update();
	}

}


////The following method was originally marked 'synchronized':
//void FriendManager::addNewOnlineFriendIfNotExist(int userID, int peerType)
//{ //===============================================================================================
//	for (int i = 0; i < friendCharacters->size(); i++)
//	{
//		if (friendCharacters->get(i)->userID == userID)
//		{
//			return;
//		}
//	}
//
//
//	friendCharacters->add(new FriendCharacter(getClientGameEngine(), userID, peerType));
//}

