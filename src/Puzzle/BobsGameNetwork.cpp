

#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


const string BobsGame::lobbyCommand_STARTGAME = "STARTGAME:";
const string BobsGame::lobbyCommand_CANCELGAME = "CANCELGAME:";
const string BobsGame::lobbyCommand_PEERGAMEJOIN = "GAMEJOIN:";
const string BobsGame::lobbyCommand_PEERGAMELEAVE = "GAMELEAVE:";
const string BobsGame::lobbyCommand_JOINEDPEER = "JOINEDPEER:";
const string BobsGame::lobbyCommand_PLAYERCONFIRM = "PLAYERCONFIRM:";
const string BobsGame::lobbyCommand_PLAYERJOIN = "PLAYERJOIN:";
const string BobsGame::lobbyCommand_PLAYERLEAVE = "PLAYERLEAVE:";
const string BobsGame::lobbyCommand_PLAYERFORFEIT = "PLAYERFORFEIT:";
const string BobsGame::lobbyCommandAllPeers_PLAYING = "PLAYING:";
const string BobsGame::lobbyCommandAllPeers_HOSTING = "HOSTING:";
const string BobsGame::lobbyCommandAllPeers_NOT_HOSTING = "NOT_HOSTING:";

const string BobsGame::netCommand_START = "START:";
const string BobsGame::netCommand_FRAME = "FRAME:";
const string BobsGame::netCommand_FORFEIT = "FORFEIT:";

#include "Room.h"


//=========================================================================================================================
void BobsGame::sendAllJoinedPeers(string s)
{//=========================================================================================================================

	for (int i = 0; i<joinedPeers->size(); i++)
	{
		UDPPeerConnection *c = joinedPeers->get(i);
		c->writeReliable_S("BOBSGAME:" + s + ":"+ BobNet::endline);
	}
}

//=========================================================================================================================
void BobsGame::sendPeer(UDPPeerConnection *c, string s)
{//=========================================================================================================================
	c->writeReliable_S("BOBSGAME:" + s + ":" + BobNet::endline);
}

//=========================================================================================================================
void BobsGame::sendAllPeers(string s)
{//=========================================================================================================================
	BobNet::sendAllPeers("BOBSGAME:" + s + ":" + BobNet::endline);
}


//=========================================================================================================================
void BobsGame::tellAllPeersOneOfMyPlayersForfeitsGame(PuzzlePlayer *p)
{//=========================================================================================================================

	sendAllJoinedPeers(lobbyCommand_PLAYERFORFEIT + p->getID());
}



//=========================================================================================================================
void BobsGame::tellHostPeerIAmJoiningTheirGame()
{//=========================================================================================================================
	
	sendPeer(currentRoom->hostPeer,lobbyCommand_PEERGAMEJOIN);
}


//=========================================================================================================================
void BobsGame::tellAllPeersIAmHosting()
{//=========================================================================================================================

	string command = lobbyCommandAllPeers_HOSTING + currentRoom->encodeRoomData(getServerConnection()->getUserID_S(),players.size(),true);

	sendAllPeers(command);
}

//=========================================================================================================================
void BobsGame::tellAllPeersIAmNotHosting()
{//=========================================================================================================================
	sendAllPeers(lobbyCommandAllPeers_NOT_HOSTING + to_string(players.size()));
}

//=========================================================================================================================
void BobsGame::tellAllPeersIAmPlayingAGame()
{//=========================================================================================================================
	sendAllPeers(lobbyCommandAllPeers_PLAYING + to_string(players.size()));
}

//=========================================================================================================================
void BobsGame::tellAllJoinedPeersThatANewPeerHasJoinedMyHostedGame(UDPPeerConnection *c)
{//=========================================================================================================================
	sendAllJoinedPeers(lobbyCommand_JOINEDPEER + to_string(c->peerUserID));
}

//=========================================================================================================================
void BobsGame::tellAllJoinedPeersMyHostedGameHasStarted()
{//=========================================================================================================================
	sendAllJoinedPeers(lobbyCommand_STARTGAME);
}

//=========================================================================================================================
void BobsGame::tellAllJoinedPeersIHaveCanceledMyHostedGame()
{//=========================================================================================================================
	sendAllJoinedPeers(lobbyCommand_CANCELGAME);
}

//=========================================================================================================================
void BobsGame::tellAllJoinedPeersIHaveLeftTheGame()
{//=========================================================================================================================
	sendAllJoinedPeers(lobbyCommand_PEERGAMELEAVE);
}

//=========================================================================================================================
void BobsGame::tellAllJoinedPeersOneOfMyPlayersHasLeftTheLobby(PuzzlePlayer *p)
{//=========================================================================================================================
	sendAllJoinedPeers(lobbyCommand_PLAYERLEAVE + p->getID());
}

//=========================================================================================================================
void BobsGame::tellAllJoinedPeersOneOfMyPlayersHasJoinedTheLobby(PuzzlePlayer *p)
{//=========================================================================================================================
	sendAllJoinedPeers(lobbyCommand_PLAYERJOIN + p->getID());
}

//=========================================================================================================================
void BobsGame::tellPeerThatOtherPeerHasJoined(UDPPeerConnection* peerToTell, UDPPeerConnection* joinedPeer)
{//=========================================================================================================================
	sendPeer(peerToTell,lobbyCommand_JOINEDPEER + to_string(joinedPeer->peerUserID));
}

//=========================================================================================================================
void BobsGame::tellPeerThatIHaveJoined(UDPPeerConnection* peerToTell)
{//=========================================================================================================================
	sendPeer(peerToTell, lobbyCommand_JOINEDPEER + to_string(getUserID_S()));
}

//=========================================================================================================================
void BobsGame::tellPeerThatPlayerHasJoined(UDPPeerConnection* peerToTell, PuzzlePlayer *p)
{//=========================================================================================================================
	sendPeer(peerToTell, lobbyCommand_PLAYERJOIN + p->getID());
}

//=========================================================================================================================
void BobsGame::tellPeerThatPlayerHasConfirmedAndSendGameSequence(UDPPeerConnection* peerToTell, PuzzlePlayer *p)
{//=========================================================================================================================

	NetworkGameSequence ngs = NetworkGameSequence(*p->gameLogic->currentGameSequence);
	sendPeer(peerToTell, lobbyCommand_PLAYERCONFIRM + p->getID() + ":" + ngs.toBase64GZippedXML());

}

//=========================================================================================================================
void BobsGame::tellAllPeersThatPlayerHasConfirmedAndSendGameSequence(PuzzlePlayer *p)
{//=========================================================================================================================

	NetworkGameSequence ngs = NetworkGameSequence(*p->gameLogic->currentGameSequence);
	sendAllJoinedPeers(lobbyCommand_PLAYERCONFIRM + p->getID() + ":" + ngs.toBase64GZippedXML());
}

//=========================================================================================================================
void BobsGame::tellServerIAmHostingOrUpdateRoomStatus(string roomDescription)
{//=========================================================================================================================

	getServerConnection()->tellServerBobsGameHostingPublicGameUpdate_S(roomDescription);
}

//=========================================================================================================================
void BobsGame::tellServerIHaveCanceledTheGame(string roomUUID)
{//=========================================================================================================================
	getServerConnection()->tellServerBobsGameIHaveCanceledTheGame_S(roomUUID);
}

//=========================================================================================================================
void BobsGame::tellServerIHaveStartedTheGame(string roomUUID)
{//=========================================================================================================================
	getServerConnection()->tellServerBobsGameIHaveStartedTheGame_S(roomUUID);
}

//=========================================================================================================================
void BobsGame::tellServerTheGameHasEnded(string roomUUID, string results)
{//=========================================================================================================================
	getServerConnection()->tellServerBobsGameTheGameHasEnded_S(roomUUID, results);
}

//=========================================================================================================================
void BobsGame::getUserIDAndRandomSeedAndUUIDFromPlayerIDString(string s, long long &userID, long long &randomSeed, string &uuid)
{//=========================================================================================================================

	string userIDString = s.substr(0, s.find("."));
	s = s.substr(s.find(".")+1);
	string randomSeedString = s.substr(0, s.find("."));
	s = s.substr(s.find(".") + 1);
	string uuidString = s.substr(0, s.find("."));

	try
	{
		userID = stoll(userIDString);
	}
	catch (exception)
	{
		log.error("userID could not be parsed");
		return;
	}

	try
	{
		randomSeed = stoll(randomSeedString);
	}
	catch (exception)
	{
		log.error("randomSeed could not be parsed");
		return;
	}

	uuid = uuidString;
}

//=========================================================================================================================
bool BobsGame::udpPeerMessageReceived(UDPPeerConnection *c, string s)
{//=========================================================================================================================

	if (String::startsWith(s, "BOBSGAME:"))
	{

		//if exists in networkPlayer, forward the message to their BobsGameNetwork

		//remove BOBSGAME:
		s = s.substr(s.find(":") + 1);

		string command = s.substr(0, s.find(":") + 1);
		s = s.substr(s.find(":") + 1);


		/*
		when player joins host, send them a list of all other joined players

		send new joined player to all other joined players

		they will connect to each other,

		when player connects to each other, they send each other their local players, and if they are confirmed send the confirmation and currentGameType
		*/

		if (String::startsWith(command, lobbyCommand_PEERGAMEJOIN))
		{

			UDPPeerConnection *newPeer = c;

			if (hosting)
			{

				//tell everyone else this peer has joined
				tellAllJoinedPeersThatANewPeerHasJoinedMyHostedGame(newPeer);


				//tell the new peer about all the other peers
				//need the host to send the other network players userIDs to each other to add each other as peers because they might not be friends
				for (int i = 0; i < joinedPeers->size(); i++)
				{
					UDPPeerConnection *existingPeer = joinedPeers->get(i);
					tellPeerThatOtherPeerHasJoined(newPeer,existingPeer);
				}

				//tell this peer about ourself
				tellPeerThatIHaveJoined(newPeer);
				

				//tell this new peer about all of our local players
				for (int i = 0; i<players.size(); i++)
				{
					PuzzlePlayer *p = players.get(i);
					if (p->isNetworkPlayer() == false)
					{
						tellPeerThatPlayerHasJoined(newPeer, p);

						if (p->confirmed)
						{
							tellPeerThatPlayerHasConfirmedAndSendGameSequence(newPeer, p);
						}
					}
				}
			}

			if (joinedPeers->contains(newPeer) == false)joinedPeers->add(c);

			return true;
		}

		if (String::startsWith(command, lobbyCommand_PEERGAMELEAVE))
		{
			while (joinedPeers->contains(c) == true)joinedPeers->remove(c);

//			for (int i = 0; i<players.size(); i++)
//			{
//				PuzzlePlayer *p = players.get(i);
//				if (p->peerConnection == c)
//				{
//					p->game->dead = true;
////					players.removeAt(i);
////					i--;
////					delete p;
//				}
//			}

			return true;
		}

		if (String::startsWith(command, lobbyCommand_JOINEDPEER))
		{
			string peerUserIDString = s.substr(0, s.find(":"));
			s = s.substr(s.find(":") + 1);

			long long peerUserID = -1;
			try
			{
				peerUserID = stoll(peerUserIDString);
			}
			catch (exception)
			{
				log.error("Could not parse peerUserID");
				return false;
			}


			bool found = false;

			if (getUserID_S() == peerUserID)found = true;

			UDPPeerConnection *peer = nullptr;

			//look through udpConnectionsList and see if this exists
			for (int i = 0; i < BobNet::udpConnections.size(); i++)
			{
				UDPPeerConnection *p = BobNet::udpConnections.get(i);
				if (p->peerUserID == peerUserID)
				{
					found = true;
					peer = p;
				}
			}
			if (!found)
			{
				peer = new UDPPeerConnection(peerUserID, UDPPeerConnection::ANON_TYPE);
				BobNet::udpConnections.add(peer);
			}

			//tell this new peer about all of our local players
			for (int i = 0; i<players.size(); i++)
			{
				PuzzlePlayer *p = players.get(i);
				if (p->isNetworkPlayer() == false)
				{
					tellPeerThatPlayerHasJoined(peer, p);
					

					if (p->confirmed)
					{
						tellPeerThatPlayerHasConfirmedAndSendGameSequence(peer, p);
					}
				}
			}


			if (joinedPeers->contains(c) == false)joinedPeers->add(c);

			return true;
		}



		//BOBSGAME:PLAYERJOIN:randomSeed:endline
		//BOBSGAME:PLAYERLEAVE:randomSeed:endline
		//BOBSGAME:PLAYERCONFIRM:randomSeed:settingsbase64zip:endline
		//string lobbyCommand_PLAYERJOIN = "PLAYERJOIN:";
		//string lobbyCommand_PLAYERLEAVE = "PLAYERLEAVE:";
		//string lobbyCommand_PLAYERCONFIRM = "PLAYERCONFIRM:";

		if (
			String::startsWith(command, lobbyCommand_PLAYERJOIN)
			||
			String::startsWith(command, lobbyCommand_PLAYERLEAVE)
			||			
			String::startsWith(command, lobbyCommand_PLAYERFORFEIT)
			||
			String::startsWith(command, lobbyCommand_PLAYERCONFIRM)

			)
		{

			//get random seed to find game with, need to base this on something else probably in case two games have the same random seed per network which they probably will!
			string playerIDString = s.substr(0, s.find(":"));
			s = s.substr(s.find(":") + 1);

			long long userID = -1;
			long long randomSeed = -1;
			string uuid = "";
			getUserIDAndRandomSeedAndUUIDFromPlayerIDString(playerIDString, userID, randomSeed, uuid);
			if (userID == -1 || randomSeed == -1 || uuid == "")return false;

			if (String::startsWith(command, lobbyCommand_PLAYERJOIN))
			{

				//support multiple players coming in from one friend
				bool found = false;
				for (int i = 0; i < players.size(); i++)
				{
					PuzzlePlayer *p = players.get(i);
					if (p->getID() == playerIDString)found = true;
				}
				if (!found)
				{
					PuzzlePlayer *p = new PuzzlePlayer(new GameLogic(this, randomSeed));
					p->gameLogic->uuid = uuid;
					p->gameLogic->isNetworkPlayer = true;
					p->peerConnection = c;
					//c->addEnginePartToForwardMessagesTo(n);
					players.add(p);
					string name = "Network player " + to_string(players.size());
					string userName = p->peerConnection->getUserName();
					if (userName != "")name = userName;
					p->nameCaption = getCaptionManager()->newManagedCaption(0, 0, -1, name, BobFont::ttf_oswald_16, BobMenu::menuColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
				}

			}
			if (String::startsWith(command, lobbyCommand_PLAYERLEAVE))
			{
				bool found = false;
				//support disconnected
				for (int i = 0; i < players.size(); i++)
				{
					PuzzlePlayer *p = players.get(i);

					if (p->getID() == playerIDString)
					{
						found = true;
						players.removeAt(i);
						i--;
						delete p;
					}
				}
				if (!found)
				{
					log.debug("Could not find network player with playerIDString on PlayerLeave:" + playerIDString);
				}
			}
			if (String::startsWith(command, lobbyCommand_PLAYERFORFEIT))
			{
				//support disconnected
				for (int i = 0; i < players.size(); i++)
				{
					PuzzlePlayer *p = players.get(i);

					if(p->peerConnection == c && p->getID() == playerIDString)
					{
						p->gameLogic->died = true;
					}
				}
			}
			if (String::startsWith(command, lobbyCommand_PLAYERCONFIRM))
			{
				string gameSequenceString = s.substr(0, s.find(":"));
				s = s.substr(s.find(":") + 1);


				NetworkGameSequence *gs = NetworkGameSequence::fromBase64GZippedXML(gameSequenceString);
				
				if (gs == nullptr)
				{
					log.error("Could not parse received GameSequence");
					return false;
				}

				saveUnknownGameSequencesAndTypesToXML(gs);


				bool found = false;
				for (int i = 0; i < players.size(); i++)
				{
					PuzzlePlayer *p = players.get(i);
					if (p->getID() == playerIDString)
					{
						found = true;

						p->gameLogic->currentGameSequence = gs;

						log.debug("Set network player currentGameType");
						p->confirmed = true;
					}
				}
				if (!found)
				{
					log.debug("Could not find network player with playerIDString to set currentGameType for:"+playerIDString);
				}
			}


			return true;
		}

		//string lobbyCommand_STARTGAME = "STARTGAME:";
		//string lobbyCommand_CANCELGAME = "CANCELGAME:";
		if (
			String::startsWith(command, lobbyCommand_STARTGAME)
			||
			String::startsWith(command, lobbyCommand_CANCELGAME)
			)
		{

			//verify it is the host sending this message

			if (currentRoom != nullptr && c != currentRoom->hostPeer)
			{
				log.error("Got start game or cancel game message from non-host");
				return false;
			}


			if (String::startsWith(command, lobbyCommand_STARTGAME))
			{
				hostStartedGame = true;
			}


			if (String::startsWith(command, lobbyCommand_CANCELGAME))
			{

				getCaptionManager()->newManagedCaption(Caption::CENTERED_SCREEN, 0, 5000, "Game was cancelled by host.", BobFont::ttf_oswald_24, BobColor::lightRed, BobColor::clear, RenderOrder::OVER_GUI);

				BobNet::myStatus = BobNet::status_AVAILABLE;

				joinedPeers->clear();

				hostStartedGame = false;
				networkMultiplayerLobbyMenuShowing = true;
				initPlayer();
			}

			return true;
		}


		//string lobbyCommandAllPeers_PLAYING = "PLAYING:";
		//string lobbyCommandAllPeers_HOSTING = "HOSTING:";
		//string lobbyCommandAllPeers_NOT_HOSTING = "NOT_HOSTING:";

		if (
			String::startsWith(command, lobbyCommandAllPeers_PLAYING)
			||
			String::startsWith(command, lobbyCommandAllPeers_HOSTING)
			||
			String::startsWith(command, lobbyCommandAllPeers_NOT_HOSTING)
			)
		{


			if (String::startsWith(command, lobbyCommandAllPeers_PLAYING))
			{
				//c->bobsGamePlaying = true;
				//c->bobsGameHosting = false;
			}

			if (String::startsWith(command, lobbyCommandAllPeers_HOSTING))
			{

				if (networkMultiplayerLobbyMenuShowing == false)return true;
				
				Room *newRoom = Room::decodeRoomData(s,true);
				if (newRoom == nullptr)
				{
					log.error("Could not decode room data:"+s);
					return true;
				}

				newRoom->hostPeer = c;
				newRoom->hostUserID = c->peerUserID;

				bool found = false;
				for (int i = 0; i<rooms.size(); i++)
				{
					Room *r = rooms.get(i);
					if (r->uuid == newRoom->uuid)
					{
						found = true;
						*r = *newRoom;
					}
				}
				if (found == false)
				{
					rooms.add(newRoom);
				}



				//c->bobsGameHosting = true;
				//c->bobsGamePlaying = false;
			}

			if (String::startsWith(command, lobbyCommandAllPeers_NOT_HOSTING))
			{

				for (int i = 0; i<rooms.size(); i++)
				{
					Room *r = rooms.get(i);
					if(r->hostPeer==c)
					{
						rooms.removeAt(i);
						delete r;
					}
				}

				//c->bobsGameHosting = false;
				//c->bobsGamePlaying = false;
				//c->bobsGamePlayers = 0;
			}
			return true;
		}

		if (String::startsWith(command, netCommand_FRAME))
		{

			//networkID:packetID,MD5:base64
			string playerIDString = s.substr(0, s.find(":"));
			s = s.substr(s.find(":") + 1);

			long long userID = -1;
			long long randomSeed = -1;
			string uuid = "";
			getUserIDAndRandomSeedAndUUIDFromPlayerIDString(playerIDString, userID, randomSeed, uuid);
			if (userID == -1 || randomSeed == -1 || uuid == "")return false;

			bool found = false;
			for (int i = 0; i < players.size(); i++)
			{
				PuzzlePlayer *p = players.get(i);
				if (p->getID() == playerIDString)
				{
					found = true;

					p->gameLogic->incoming_FramePacket(s);
				}
			}
			if (!found)
			{
				log.debug("Could not find network player with playerIDString to set incoming_FramePacket for!");
			}


			return true;
		}



		//	if (String::startsWith(command, netCommand_FORFEIT))
		//	{
		//		incoming_Forfeit(s);
		//		return true;
		//	}


	}
	return false;


}

//=========================================================================================================================
void BobsGame::addToRoomsMenu(Room* c, string name, string id)
{//=========================================================================================================================

	bool add = true;
	if (filterByGameSequenceUUID != "")
	{
		if (c->gameSequenceUUID != filterByGameSequenceUUID)add = false;
	}

	if (filterByGameTypeUUID != "")
	{
		if (c->gameTypeUUID != filterByGameTypeUUID)add = false;
	}

	if (filterByMaxPlayers > 1)
	{
		if (c->maxPlayers < 2 || c->maxPlayers > filterByMaxPlayers)add = false;
	}

	if (filterByKeyword != "")
	{
		if (c->gameSequenceOrTypeName.find(filterByKeyword) == string::npos)add = false;
	}

	if (add)roomsMenu->add(name, id);

}

const string HidePrivateRooms = "Hide Friend Rooms";
const string HidePublicRooms = "Hide Public Rooms";
const string HideFreePlayRooms = "Hide Free Play Rooms";
const string HideTournamentRooms = "Hide Tournament Rooms";
const string FilterByGameSequenceOrTypeRooms = "Filter By Game Sequence Or Game Type";
const string FilterByMaxPlayers = "Filter By Max Players";
const string FilterByKeyword = "Filter By Keyword";

//=========================================================================================================================
void BobsGame::populateRoomsMenu()
{//=========================================================================================================================


 //show private/public rooms
 //sort by game type
 //sort by num players in room
 //sort by tournament type
 //sort by max players

 //create new room
 //room is tournament (one player per PC, counts towards ELO record)
 //max players


	roomsMenu->clear();
	roomsMenu->addInfo(" ");
	roomsMenu->addYesNo(HidePrivateRooms, hidePrivateRooms);
	roomsMenu->addYesNo(HidePublicRooms, hidePublicRooms);
	roomsMenu->addYesNo(HideFreePlayRooms, hideFreePlayRooms);
	roomsMenu->addYesNo(HideTournamentRooms, hideTournamentRooms);
	roomsMenu->add("Filter By Game Sequence Or Type: None", FilterByGameSequenceOrTypeRooms);
	roomsMenu->add("Filter By Max Players: No Limit", FilterByMaxPlayers);
	roomsMenu->add("Filter By Keyword: ", FilterByKeyword);
	roomsMenu->addInfo(" ");

	if (hidePrivateRooms == false)
	{
		roomsMenu->addInfo("Your Friends' Games:");
		for (int i = 0; i < rooms.size(); i++)
		{
			Room* c = rooms.get(i);

			if (c->privateRoom && c->hostPeer != nullptr)
			{
				addToRoomsMenu(c, c->hostPeer->getUserName() + ": " + c->getRoomDescription(), c->uuid);
			}
		}
		roomsMenu->addInfo(" ");
	}


	if (hidePublicRooms == false)
	{
		if (hideFreePlayRooms == false)
		{
			roomsMenu->addInfo("Public Free Play Games:");
			for (int i = 0; i < rooms.size(); i++)
			{
				Room* c = rooms.get(i);

				if (c->privateRoom == false && c->tournamentRoom == false)
				{
					addToRoomsMenu(c, c->getRoomDescription(), c->uuid);
				}
			}
			roomsMenu->addInfo(" ");
		}

		if (hideTournamentRooms == false)
		{
			roomsMenu->addInfo("Public Tournament Games:");
			for (int i = 0; i < rooms.size(); i++)
			{
				Room* c = rooms.get(i);

				if (c->privateRoom == false && c->tournamentRoom == true)
				{
					addToRoomsMenu(c, c->getRoomDescription(), c->uuid);
				}
			}
			roomsMenu->addInfo(" ");
		}
	}
	roomsMenu->setAllCaptionsToFullAlpha();

}

//=========================================================================================================================
string cycleDots(int tries)
{//=========================================================================================================================
	//make dots cycle
	string dots = "";
	for (int i = 0; i < tries % 4; i++)
	{
		dots += ".";
	}
	return dots;
}

//=========================================================================================================================
void BobsGame::networkMultiplayerLobbyMenuUpdate()
{//=========================================================================================================================



	if (networkMultiplayerLobbyMenu == nullptr)
	{
		if (statusLabel == nullptr)statusLabel = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 0, -1, " ", BobFont::ttf_oswald_16, BobMenu::statusColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
		if (errorLabel == nullptr)errorLabel = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 0, -1, " ", BobFont::ttf_oswald_16, BobMenu::errorColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
		//if (onlineFriendsLabel == nullptr)onlineFriendsLabel = getCaptionManager()->newManagedCaption(0, 0, -1, "Online Friends:", BobFont::ttf_oswald_16, BobMenu::menuColor, BobMenu::clearColor, RenderOrder::OVER_GUI);

		networkMultiplayerLobbyMenu = new BobMenu(this, "Network Multiplayer Lobby");
		networkMultiplayerLobbyMenu->center = false;
		//networkMultiplayerLobbyMenu->font = BobFont::ttf_oswald_12;

		networkMultiplayerLobbyMenu->addInfo("", "Logged in", BobMenu::statusColor);
		networkMultiplayerLobbyMenu->addInfo(" ");
		//networkMultiplayerLobbyMenu->add("Add friends by email address");
		//networkMultiplayerLobbyMenu->add("Add friends from Gmail");
		//networkMultiplayerLobbyMenu->add("Add friends from Steam");
		//networkMultiplayerLobbyMenu->add("Play against people in your area");
		//networkMultiplayerLobbyMenu->add("Play against people from all over the world");
		//networkMultiplayerLobbyMenu->add("Compete in global tournament");
		//networkMultiplayerLobbyMenu->add("See your ranking and stats");
		//networkMultiplayerLobbyMenu->add("Watch game");
		networkMultiplayerLobbyMenu->add("Join room");
		networkMultiplayerLobbyMenu->add("Create new room", "Create room");
		networkMultiplayerLobbyMenu->addInfo(" ");


//		networkMultiplayerLobbyMenu->addYesNo(HidePrivateRooms, hidePrivateRooms);
//		networkMultiplayerLobbyMenu->addYesNo(HidePublicRooms, hidePublicRooms);
//		networkMultiplayerLobbyMenu->addYesNo(HideFreePlayRooms, hideFreePlayRooms);
//		networkMultiplayerLobbyMenu->addYesNo(HideTournamentRooms, hideTournamentRooms);
//		networkMultiplayerLobbyMenu->add("Filter By Game Sequence Or Type: None", FilterByGameSequenceOrTypeRooms);
//		networkMultiplayerLobbyMenu->add("Filter By Max Players: No Limit", FilterByMaxPlayers);
//		networkMultiplayerLobbyMenu->add("Filter By Keyword: ", FilterByKeyword);

		//networkMultiplayerLobbyMenu->add("Add friends from Facebook", "Facebook");
		networkMultiplayerLobbyMenu->addInfo(" ");
		networkMultiplayerLobbyMenu->add("Add friend by username: ", "Add friend by username");
		networkMultiplayerLobbyMenu->add("Log out", "Log out");
		networkMultiplayerLobbyMenu->add("Return to title screen");
		networkMultiplayerLobbyMenu->addInfo("");

		networkMultiplayerLobbyMenu->cursorPosition = networkMultiplayerLobbyMenuCursorPosition;
	}

	if(yourStatsMenu == nullptr)
	{
		yourStatsMenu = new BobMenu(this, "");
		yourStatsMenu->center = false;
		yourStatsMenu->font = BobFont::ttf_oswald_10;


		populateUserStatsForSpecificGameAndDifficultyMenu(yourStatsMenu, "OVERALL", "OVERALL");
		//populateLeaderBoardOrHighScoreBoardMenu

	}
	if(leaderBoardMenu == nullptr)
	{
		leaderBoardMenu = new BobMenu(this, "");
		leaderBoardMenu->center = false;
		leaderBoardMenu->font = BobFont::ttf_oswald_10;

		populateLeaderBoardOrHighScoreBoardMenu(leaderBoardMenu, "OVERALL", "OVERALL",false,false,false,true,false,false);
	}

	//	if (getGameSave_S().facebookID != "")
	//	{
	//		if (networkMultiplayerLobbyMenu != nullptr)networkMultiplayerLobbyMenu->setHidden("Facebook", true);
	//	}

	string loggedInName = getUserName_S();
	if (loggedInName != "") 
	{
		networkMultiplayerLobbyMenu->getMenuItemByID("Logged in")->setText("Logged in as: " + loggedInName);
		networkMultiplayerLobbyMenu->getMenuItemByID("Log out")->setText("Log out " + loggedInName);
	}

	bool leaveMenu = false;

	if(joining)
	{
		//statusLabel->setText("Joining room...");
		//errorLabel->setText("");


		//tell the server i am joining room, which tells all the other peers i have joined, who send friend requests to me
		//no longer have the host pc organize the clients

		//tell the host i'm joining them


		int tries = 0;

		bool connectedAndReady = false;
		while (connectedAndReady == false && joining)
		{

			if (currentRoom->hostPeer == nullptr)
			{
				//add peer with room host userID so that I try to connect to it which gets ip address from STUN server
				UDPPeerConnection* p = BobNet::addFriendID(currentRoom->hostUserID, UDPPeerConnection::ANON_TYPE);

				//tell server to tell host to connect to me
				getServerConnection()->tellBobsGameRoomHostMyUserID_S(currentRoom->uuid);

				
				//wait for peer to connect
				while(p->getConnectedToPeer_S()==false)
				{
					tries++;

					statusLabel->setText("Connecting to host" + cycleDots(tries));
					errorLabel->setText(" ");

					if (tries > 20)
					{
						statusLabel->setText(" ");
						errorLabel->setText("Error: Could not connect to host.");
						joining = false;
						break;
					}

					//statusLabel->render();
					//errorLabel->render();

					Main::delay(300);

				}

				//when peer is connected, set currentRoom->hostPeer to that peer
				if(p->getConnectedToPeer_S())
				{
					currentRoom->hostPeer = p;
				}
			}

			tries = 0;
			
			if (currentRoom->hostPeer != nullptr)
			{
				//they should send me their game sequence in the room update

				//when i receive their game sequence, add it to the currentRoom

				//when connected, tell host i am joining their game

				
				bool haveGameSequence = false;
				while(haveGameSequence == false)
				{

					if (currentRoom->multiplayer_SelectedGameSequence != nullptr)haveGameSequence = true;

					tries++;

					statusLabel->setText("Waiting for game sequence from host" + cycleDots(tries));
					errorLabel->setText(" ");

					if (tries > 20)
					{
						statusLabel->setText(" ");
						errorLabel->setText("Error: Timed out waiting for game sequence.");
						joining = false;
						break;
					}

					//statusLabel->render();
					//errorLabel->render();
					Main::delay(300);
				}

				if (haveGameSequence)
				{

					tellHostPeerIAmJoiningTheirGame();
					joinedPeers->add(currentRoom->hostPeer);

					selectingHostedGame = false;
					networkMultiplayerPlayerJoinMenuShowing = true;

					connectedAndReady = true;
					leaveMenu = true;
				}
			}


		}

		joining = false;

	}

	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();

	//show friends online list
	if (friendsOnlineMenu == nullptr)
	{
		friendsOnlineMenu = new BobMenu(this, "");
		friendsOnlineMenu->font = BobFont::ttf_oswald_12;
		friendsOnlineMenu->center = false;
	}

	if (roomsMenu == nullptr)
	{
		roomsMenu = new BobMenu(this, "");
		roomsMenu->font = BobFont::ttf_oswald_12;
		roomsMenu->center = false;
		populateRoomsMenu();
	}

	long long currentTime = System::currentHighResTimer();
	long long startTime = updateStatsTime;
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed > 200)
	{
		bool rotated = false;
		updateStatsTime = currentTime;
		rotateLeaderBoardsTime += ticksPassed;
		if(rotateLeaderBoardsTime>5000)
		{
			rotateLeaderBoardsTime = 0;
			whichLeaderBoardToShow++;
			whichDifficultyToShow++;
			
			rotated = true;
		}

		if (whichLeaderBoardToShow > 5)whichLeaderBoardToShow = 0;
		if (whichDifficultyToShow > 5)whichDifficultyToShow = 0;

		bool totalTimePlayed = false;
		bool totalBlocksCleared = false;
		bool planeswalkerPoints = false;
		bool eloScore = false;
		bool timeLasted = false;
		bool blocksCleared = false;
		
		if (whichLeaderBoardToShow == 0)totalTimePlayed = true;
		if (whichLeaderBoardToShow == 1)totalBlocksCleared = true;
		if (whichLeaderBoardToShow == 2)planeswalkerPoints = true;
		if (whichLeaderBoardToShow == 3)eloScore = true;
		if (whichLeaderBoardToShow == 4)timeLasted = true;
		if (whichLeaderBoardToShow == 5)blocksCleared = true;

		string difficultyName = "OVERALL";
		if (whichDifficultyToShow == 0)difficultyName = "OVERALL";
		if (whichDifficultyToShow == 1)difficultyName = "Beginner";
		if (whichDifficultyToShow == 2)difficultyName = "Easy";
		if (whichDifficultyToShow == 3)difficultyName = "Normal";
		if (whichDifficultyToShow == 4)difficultyName = "Hard";
		if (whichDifficultyToShow == 5)difficultyName = "Insane";

		yourStatsMenu->clear();
		leaderBoardMenu->clear();

		if(selectingHostedGame)
		{
			for (int i = 0; i < rooms.size(); i++)
			{
				Room* c = rooms.get(i);
				if (roomsMenu->isSelectedID(c->uuid, false, mx, my))
				{
					string uuid = c->gameTypeUUID;
					if (uuid == "")uuid = c->gameSequenceUUID;

					populateUserStatsForSpecificGameAndDifficultyMenu(yourStatsMenu, uuid, c->multiplayer_SelectedDifficultyName);

					populateLeaderBoardOrHighScoreBoardMenu(leaderBoardMenu, uuid, c->multiplayer_SelectedDifficultyName,
						totalTimePlayed, totalBlocksCleared, planeswalkerPoints, eloScore, timeLasted, blocksCleared);
				}
			}

		}
		else
		{
			populateUserStatsForSpecificGameAndDifficultyMenu(yourStatsMenu, "OVERALL", difficultyName);

			populateLeaderBoardOrHighScoreBoardMenu(leaderBoardMenu, "OVERALL", difficultyName,
				totalTimePlayed, totalBlocksCleared, planeswalkerPoints, eloScore, timeLasted, blocksCleared);

		}

		if (rotated == false)
		{
			yourStatsMenu->setAllCaptionsToFullAlpha();
			leaderBoardMenu->setAllCaptionsToFullAlpha();
		}
	}


	currentTime = System::currentHighResTimer();
	startTime = updateFriendsTime;
	ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed > 2000)
	{
		updateFriendsTime = currentTime;


		onlineFriends.clear();
		for (int i = 0; i < (int)BobNet::udpConnections.size(); i++)
		{
			UDPPeerConnection* f = BobNet::udpConnections.get(i);
			if (f->getConnectedToPeer_S() == true && f->getGotFriendData_S() == true)// && f->getStatus_S() == BobNet::status_AVAILABLE)
			{
				if (onlineFriends.contains(f) == false)
					onlineFriends.add(f);
			}
		}


		friendsOnlineMenu->clear();
		friendsOnlineMenu->addInfo("Friends Online:");
		
		for (int i = 0; i < onlineFriends.size(); i++)
		{
			UDPPeerConnection* c = onlineFriends.get(i);

//			if (c->bobsGameHosting)
//			{
//				string user = c->getFriendData_S().userName;
//				string description = user + " - Hosting";
//
//				networkMultiplayerLobbyFriendsOnlineMenu->add(description, user);
//			}
//			else
//			if (c->bobsGamePlaying)
//			{
//				string user = c->getFriendData_S().userName;
//				string description = c->getFriendData_S().userName + " - Playing";
//
//				networkMultiplayerLobbyFriendsOnlineMenu->add(description, user);
//			}
//			else
			{
				string user = c->getUserName();
				string description = c->getUserName();

				friendsOnlineMenu->add(description, user);
			}

		}
		friendsOnlineMenu->setAllCaptionsToFullAlpha();

		populateRoomsMenu();
	}




	startTime = updatePublicGamesTime;
	ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed > 5000)
	{
		updatePublicGamesTime = currentTime;

		//get room list from server

		//send new request
		//if got response, parse response

		string s = getServerConnection()->getAndResetBobsGameRoomListResponse_S();

		if(s != "")
		{
			//remove non private rooms
			for (int i = 0; i<rooms.size(); i++)
			{
				Room *r = rooms.get(i);
				if (r->privateRoom == false)
				{
					delete r;
					rooms.removeAt(i);
					i--;
				}
			}

			//roomDescription:...
			while (s.length()>0)
			{
				string roomDescription = s.substr(0, s.find(":"));
				s = s.substr(s.find(":") + 1);
				
				Room *newRoom = Room::decodeRoomData(roomDescription, false);

				rooms.add(newRoom);

			}

			
			populateRoomsMenu();
		}
		else
		{
			getServerConnection()->sendBobsGameRoomListRequest_S();
		}

		
	}

	
	if (filterByGameSequenceName != "")
	{
		roomsMenu->getMenuItemByID(FilterByGameSequenceOrTypeRooms)->setText("Filter By Game Sequence: " + filterByGameSequenceName);
	}
	else
		if (filterByGameTypeName != "")
		{
			roomsMenu->getMenuItemByID(FilterByGameSequenceOrTypeRooms)->setText("Filter By Game Type: " + filterByGameTypeName);
		}
		else
		{
			roomsMenu->getMenuItemByID(FilterByGameSequenceOrTypeRooms)->setText("Filter By Game Sequence Or Type: None");
		}

	if (filterByMaxPlayers > 1)
	{
		roomsMenu->getMenuItemByID(FilterByMaxPlayers)->setText("Filter By Max Players: " + to_string(filterByMaxPlayers));
	}
	else
	{
		roomsMenu->getMenuItemByID(FilterByMaxPlayers)->setText("Filter By Max Players: No Limit");
	}

	if (filterByKeyword != "")roomsMenu->getMenuItemByID(FilterByKeyword)->setText("Filter By Keyword: " + filterByKeyword);
	else roomsMenu->getMenuItemByID(FilterByKeyword)->setText("Filter By Keyword: ");


	

	if (selectGameSequenceOrSingleGameTypeFilterMenuShowing)
	{
		selectGameSequenceOrSingleGameTypeFilterMenuUpdate();
	}
	else
		if (selectGameSequenceFilterMenuShowing)
		{
			selectGameSequenceFilterMenuUpdate();
		}
		else
			if (selectSingleGameTypeFilterMenuShowing)
			{
				selectSingleGameTypeFilterMenuUpdate();
			}
			else
			{
				if (selectingHostedGame == false)
				{
					if (getControlsManager()->miniGame_UP_Pressed())
					{
						networkMultiplayerLobbyMenu->up();

						if (textStarted) { SDL_StopTextInput(); textStarted = false; }
					}

					if (getControlsManager()->miniGame_DOWN_Pressed())
					{
						networkMultiplayerLobbyMenu->down();

						if (textStarted) { SDL_StopTextInput(); textStarted = false; }
					}

					if (getControlsManager()->miniGame_RIGHT_Pressed())
					{
						selectingHostedGame = true;
					}

					if (roomsMenu->isSelectedID(FilterByMaxPlayers))
					{
						string num = "";
						if (filterByMaxPlayers > 1)num = to_string(filterByMaxPlayers);

						if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = num; textStarted = true; }

						filterByMaxPlayers = -1;
						int temp = -1;
						try
						{
							temp = stoi(getControlsManager()->text);
						}
						catch (exception) {}
						if (temp != -1)filterByMaxPlayers = temp;

					}

					if (roomsMenu->isSelectedID(FilterByKeyword))
					{
						if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = filterByKeyword; textStarted = true; }
						filterByKeyword = getControlsManager()->text;
					}

					if (networkMultiplayerLobbyMenu->isSelectedID("Add friend by username"))
					{
						if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = friendUserName; textStarted = true; }
						friendUserName = getControlsManager()->text;

						while (friendUserName.find("`") != string::npos)
						{
							string prefix = friendUserName.substr(0, friendUserName.find("`"));
							friendUserName = prefix + friendUserName.substr(friendUserName.find("`") + 1);
						}

						networkMultiplayerLobbyMenu->getMenuItemByID("Add friend by username")->setText("Add friend by username: " + friendUserName);
					}
				}
				else
				{
					if (getControlsManager()->miniGame_UP_Pressed())
					{
						roomsMenu->up();

						if (textStarted) { SDL_StopTextInput(); textStarted = false; }
					}

					if (getControlsManager()->miniGame_DOWN_Pressed())
					{

						roomsMenu->down();

						if (textStarted) { SDL_StopTextInput(); textStarted = false; }
					}

					if (getControlsManager()->miniGame_LEFT_Pressed())
					{
						selectingHostedGame = false;
					}

				}

				

				bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
				bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();


				if (confirm || clicked)
				{

					if(clicked == true && confirm == false)
					{

						if(yourStatsMenu->isSelectedID(yourStatsMenu->getSelectedMenuItem()->id,clicked,mx,my))
						{
							whichDifficultyToShow++;
							rotateLeaderBoardsTime = -5000;
						}
						if (leaderBoardMenu->isSelectedID(leaderBoardMenu->getSelectedMenuItem()->id,clicked, mx, my))
						{
							whichLeaderBoardToShow++;
							rotateLeaderBoardsTime = -5000;
						}
					}

					if (selectingHostedGame == true || (clicked == true && confirm == false))
					{


						{

							//BobMenu::MenuItem *m = networkMultiplayerLobbyRoomsMenu->getSelectedMenuItem();
							//currentRoom = nullptr;

							//if (m != nullptr)
							//{
							//get the selected host
							for (int i = 0; i < rooms.size(); i++)
							{
								Room* c = rooms.get(i);
								if (roomsMenu->isSelectedID(c->uuid, clicked, mx, my))
								{
									currentRoom = c;
									joining = true;
									hosting = false;
								}
							}
							//}


							if (roomsMenu->isSelectedID(HidePrivateRooms, clicked, mx, my))
							{
								roomsMenu->getMenuItemByID(HidePrivateRooms)->toggle();
								hidePrivateRooms = !hidePrivateRooms;
								populateRoomsMenu();
							}

							if (roomsMenu->isSelectedID(HidePublicRooms, clicked, mx, my))
							{
								roomsMenu->getMenuItemByID(HidePublicRooms)->toggle();
								hidePublicRooms = !hidePublicRooms;
								populateRoomsMenu();
							}

							if (roomsMenu->isSelectedID(HideFreePlayRooms, clicked, mx, my))
							{
								roomsMenu->getMenuItemByID(HideFreePlayRooms)->toggle();
								hideFreePlayRooms = !hideFreePlayRooms;
								populateRoomsMenu();
							}

							if (roomsMenu->isSelectedID(HideTournamentRooms, clicked, mx, my))
							{
								roomsMenu->getMenuItemByID(HideTournamentRooms)->toggle();
								hideTournamentRooms = !hideTournamentRooms;
								populateRoomsMenu();
							}

							if (roomsMenu->isSelectedID(FilterByGameSequenceOrTypeRooms, clicked, mx, my))
							{
								selectGameSequenceOrSingleGameTypeFilterMenuShowing = true;
							}

							if (roomsMenu->isSelectedID(FilterByMaxPlayers))
							{
								//don't need any implementation here, handled above
								populateRoomsMenu();
							}

							if (roomsMenu->isSelectedID(FilterByKeyword))
							{
								//don't need any implementation here, handled above
								populateRoomsMenu();
							}

						}
					}
					
					if (selectingHostedGame == false || (clicked == true && confirm == false))
					{
						//if (networkMultiplayerLobbyMenu->isSelectedID("Facebook", clicked, mx, my))
						//{
						//	getServerConnection()->linkFacebookAccount(statusLabel, errorLabel);
						//}

						if (networkMultiplayerLobbyMenu->isSelectedID("Add friend by username", clicked, mx, my))
						{
							while (friendUserName.find("`") != string::npos)
							{
								string prefix = friendUserName.substr(0, friendUserName.find("`"));
								friendUserName = prefix + friendUserName.substr(friendUserName.find("`") + 1);
							}
							getServerConnection()->doAddFriendByUsername(statusLabel, errorLabel, friendUserName);
						}

						if (networkMultiplayerLobbyMenu->isSelectedID("Join room", clicked, mx, my))
						{
							selectingHostedGame = true;
						}



						if (networkMultiplayerLobbyMenu->isSelectedID("Create room", clicked, mx, my))
						{
							leaveMenu = true;
							multiplayerOptionsMenuShowing = true;

							//TODO
							//TODO
							//TODO
							//TODO
							//TODO

							//let's move the multiplayer options into the hosted room so they can be changed in realtime??
							//


							hosting = true;
							currentRoom = new Room();
						}

						if (networkMultiplayerLobbyMenu->isSelectedID("Log out", clicked, mx, my))
						{
							FileUtils::deleteSessionTokenFromCache();
							getServerConnection()->setNotAuthorizedOnServer_S();
							getServerConnection()->lastUserNameOrEmail = "";
							getServerConnection()->lastPassword = "";
							leaveMenu = true;
							loginMenuShowing = true;
						}

						if (networkMultiplayerLobbyMenu->isSelectedID("Return to title screen", clicked, mx, my))
						{
							leaveMenu = true;
							startScreenMenuShowing = true;
						}



					}
					

				}

				if (getControlsManager()->miniGame_CANCEL_Pressed())
				{
					if (selectingHostedGame == true)
					{
						selectingHostedGame = false;
					}
					else
					{
						leaveMenu = true;
						startScreenMenuShowing = true;
					}
				}
			}

	if (leaveMenu)
	{
		networkMultiplayerLobbyMenuShowing = false;

		selectingHostedGame = false;

		if (networkMultiplayerLobbyMenu != nullptr)
		{
			networkMultiplayerLobbyMenuCursorPosition = networkMultiplayerLobbyMenu->cursorPosition;
			delete networkMultiplayerLobbyMenu;
			networkMultiplayerLobbyMenu = nullptr;
		}

		if (friendsOnlineMenu != nullptr)
		{
			delete friendsOnlineMenu;
			friendsOnlineMenu = nullptr;
		}

		if (yourStatsMenu != nullptr)
		{
			delete yourStatsMenu;
			yourStatsMenu = nullptr;
		}
		if (leaderBoardMenu != nullptr)
		{
			delete leaderBoardMenu;
			leaderBoardMenu = nullptr;
		}
		if (roomsMenu != nullptr)
		{
			delete roomsMenu;
			roomsMenu = nullptr;
		}

		if (selectGameSequenceOrSingleGameTypeMenu != nullptr)
		{
			delete selectGameSequenceOrSingleGameTypeMenu;
			selectGameSequenceOrSingleGameTypeMenu = nullptr;
		}

		if (selectGameSequenceMenu != nullptr)
		{
			delete selectGameSequenceMenu;
			selectGameSequenceMenu = nullptr;
		}

		if (selectSingleGameTypeMenu != nullptr)
		{
			delete selectSingleGameTypeMenu;
			selectSingleGameTypeMenu = nullptr;
		}

//		for (int i = 0; i < onlineFriends.size(); i++)
//		{
//			UDPPeerConnection* f = onlineFriends.get(i);
//		}

		if (statusLabel != nullptr)
		{
			statusLabel->setToBeDeletedImmediately();
			statusLabel = nullptr;
		}

		if (errorLabel != nullptr)
		{
			errorLabel->setToBeDeletedImmediately();
			errorLabel = nullptr;
		}
	}
}



//=========================================================================================================================
void BobsGame::networkMultiplayerLobbyMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	BobTexture* t = onlineTexture;

	if (networkMultiplayerLobbyMenu == nullptr)return;

	if (t != nullptr)
	{
		networkMultiplayerLobbyMenu->setGraphic(t, getWidth() / 8 * 3, 60);
	}


	if (statusLabel != nullptr && errorLabel != nullptr)
	{
		statusLabel->screenY = (float)(getHeight() / 4 * 3);
		errorLabel->screenY = (float)((getHeight() / 4 * 3) + 20);
	}

	int startHeight = 0;
	int bottomHeight = 0;
	int leftX = 0;
	int rightX = 0;
	networkMultiplayerLobbyMenu->render(0, getWidth() / 8 * 1, getHeight(), !selectingHostedGame, &startHeight, &bottomHeight, false, &leftX, &rightX);
	friendsOnlineMenu->render(bottomHeight, leftX, getHeight(), false);

	roomsMenu->render(startHeight, rightX + 80, getHeight(), selectingHostedGame, nullptr, nullptr, false, nullptr, &rightX);

	yourStatsMenu->render(startHeight, rightX + 80, getHeight(), false, nullptr, nullptr, false, nullptr, &rightX);
	leaderBoardMenu->render(startHeight, rightX + 80, getHeight(), false);

	if (selectGameSequenceOrSingleGameTypeFilterMenuShowing && selectGameSequenceOrSingleGameTypeMenu != nullptr)
	{
		Caption *c = networkMultiplayerLobbyMenu->getCaptionByID(FilterByGameSequenceOrTypeRooms);
		selectGameSequenceOrSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

	if (selectGameSequenceFilterMenuShowing && selectGameSequenceMenu != nullptr)
	{
		Caption *c = networkMultiplayerLobbyMenu->getCaptionByID(FilterByGameSequenceOrTypeRooms);
		selectGameSequenceMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}

	if (selectSingleGameTypeFilterMenuShowing && selectSingleGameTypeMenu != nullptr)
	{
		Caption *c = networkMultiplayerLobbyMenu->getCaptionByID(FilterByGameSequenceOrTypeRooms);
		selectSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, GLUtils::getViewportHeight(), true, nullptr, nullptr, true);
	}
}



//=========================================================================================================================
void BobsGame::selectGameSequenceOrSingleGameTypeFilterMenuUpdate()
{//=========================================================================================================================

	if (selectGameSequenceOrSingleGameTypeMenu == nullptr)
	{
		selectGameSequenceOrSingleGameTypeMenu = new BobMenu(this, "");
		selectGameSequenceOrSingleGameTypeMenu->add("None");
		selectGameSequenceOrSingleGameTypeMenu->add("Select Game Sequence");
		selectGameSequenceOrSingleGameTypeMenu->add("Select Single Game Type");
		selectGameSequenceOrSingleGameTypeMenu->cursorPosition = selectGameSequenceOrSingleGameTypeMenuCursorPosition;
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		selectGameSequenceOrSingleGameTypeMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		selectGameSequenceOrSingleGameTypeMenu->down();
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{
		if (selectGameSequenceOrSingleGameTypeMenu->isSelectedID("None", clicked, mx, my))
		{
			filterByGameSequenceName = "";
			filterByGameSequenceUUID = "";
			filterByGameTypeName = "";
			filterByGameTypeUUID = "";
		}

		if (selectGameSequenceOrSingleGameTypeMenu->isSelectedID("Select Game Sequence", clicked, mx, my))
		{
			selectGameSequenceFilterMenuShowing = true;
		}

		if (selectGameSequenceOrSingleGameTypeMenu->isSelectedID("Select Single Game Type", clicked, mx, my))
		{
			selectSingleGameTypeFilterMenuShowing = true;
		}

		leaveMenu = true;
	}

	if (leaveMenu)
	{
		selectGameSequenceOrSingleGameTypeFilterMenuShowing = false;

		if (selectGameSequenceOrSingleGameTypeMenu != nullptr)
		{
			selectGameSequenceOrSingleGameTypeMenuCursorPosition = selectGameSequenceOrSingleGameTypeMenu->cursorPosition;
			delete selectGameSequenceOrSingleGameTypeMenu;
			selectGameSequenceOrSingleGameTypeMenu = nullptr;
		}
	}
}

//=========================================================================================================================
void BobsGame::selectGameSequenceFilterMenuUpdate()
{//=========================================================================================================================

	if (selectGameSequenceMenu == nullptr)
	{
		selectGameSequenceMenu = new BobMenu(this, "");
		selectGameSequenceMenu->center = false;
		populateGameSequencesMenu(selectGameSequenceMenu);
		selectGameSequenceMenu->cursorPosition = selectGameSequenceMenuCursorPosition;
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		selectGameSequenceMenu->up();
	}
	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		selectGameSequenceMenu->down();
	}

	bool leaveMenu = false;
	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{
		for (int i = 0; i<loadedGameSequences.size(); i++)
		{
			GameSequence *g = loadedGameSequences.get(i);
			if (selectGameSequenceMenu->isSelectedID(g->uuid, clicked, mx, my))
			{
				filterByGameSequenceName = g->name;
				filterByGameSequenceUUID = g->uuid;
				filterByGameTypeName = "";
				filterByGameTypeUUID = "";
			}
		}
		leaveMenu = true;
	}

	if (leaveMenu)
	{
		selectGameSequenceFilterMenuShowing = false;

		if (selectGameSequenceMenu != nullptr)
		{
			selectGameSequenceMenuCursorPosition = selectGameSequenceMenu->cursorPosition;
			delete selectGameSequenceMenu;
			selectGameSequenceMenu = nullptr;
		}
	}

}

//=========================================================================================================================
void BobsGame::selectSingleGameTypeFilterMenuUpdate()
{//=========================================================================================================================

	if (selectSingleGameTypeMenu == nullptr)
	{
		selectSingleGameTypeMenu = new BobMenu(this, "");
		selectSingleGameTypeMenu->center = false;
		selectSingleGameTypeMenu->font = BobFont::ttf_oswald_12;
		populateGameTypesMenu(selectSingleGameTypeMenu);
		selectSingleGameTypeMenu->cursorPosition = selectSingleGameTypeMenuCursorPosition;
	}

	//make key repeat work
	if (getControlsManager()->MINIGAME_UP_HELD)
	{
		long long currentTime = System::currentHighResTimer();
		if (upRepeatedStarted == false)
		{
			selectSingleGameTypeMenu->up();
			upRepeatedStarted = true;
			upLastTime = currentTime;
		}
		else
		{
			long long startTime = upLastTime;
			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
			if (upRepeating == false)
			{
				if (ticksPassed > 300)
				{
					upLastTime = currentTime;
					selectSingleGameTypeMenu->up();
					upRepeating = true;
				}
			}
			else
			{
				if (ticksPassed > 30)
				{
					upLastTime = currentTime;
					selectSingleGameTypeMenu->up();
				}
			}
		}
	}
	else
	{
		upRepeating = false;
		upRepeatedStarted = false;
	}

	if (getControlsManager()->MINIGAME_DOWN_HELD)
	{
		long long currentTime = System::currentHighResTimer();
		if (downRepeatedStarted == false)
		{
			selectSingleGameTypeMenu->down();
			downRepeatedStarted = true;
			downLastTime = currentTime;
		}
		else
		{
			long long startTime = downLastTime;
			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

			if (downRepeating == false)
			{
				if (ticksPassed > 300)
				{
					downLastTime = currentTime;
					selectSingleGameTypeMenu->down();
					downRepeating = true;
				}
			}
			else
			{
				if (ticksPassed > 30)
				{
					downLastTime = currentTime;
					selectSingleGameTypeMenu->down();
				}
			}
		}
	}
	else
	{
		downRepeating = false;
		downRepeatedStarted = false;
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{
		for (int i = 0; i<loadedGameTypes.size(); i++)
		{
			GameType *g = loadedGameTypes.get(i);
			if (selectSingleGameTypeMenu->isSelectedID(g->uuid, clicked, mx, my))
			{
				filterByGameTypeUUID = g->uuid;
				filterByGameTypeName = g->name;
				filterByGameSequenceName = "";
				filterByGameSequenceUUID = "";
			}
		}
		leaveMenu = true;
	}

	if (leaveMenu)
	{
		selectSingleGameTypeFilterMenuShowing = false;
		if (selectSingleGameTypeMenu != nullptr)
		{
			selectSingleGameTypeMenuCursorPosition = selectSingleGameTypeMenu->cursorPosition;
			delete selectSingleGameTypeMenu;
			selectSingleGameTypeMenu = nullptr;
		}
	}
}



//=========================================================================================================================
void BobsGame::networkMultiplayerPlayerJoinMenuUpdate()
{//=========================================================================================================================



	if (networkMultiplayerPlayerJoinMenu == nullptr)
	{
		if (statusLabel == nullptr)statusLabel = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 0, -1, " ", BobFont::ttf_oswald_16, BobMenu::statusColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
		if (errorLabel == nullptr)errorLabel = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 0, -1, " ", BobFont::ttf_oswald_16, BobMenu::errorColor, BobMenu::clearColor, RenderOrder::OVER_GUI);

		networkMultiplayerPlayerJoinMenu = new BobMenu(this, "Network Multiplayer Room");
		networkMultiplayerPlayerJoinMenu->font = BobFont::ttf_oswald_12;
		networkMultiplayerPlayerJoinMenu->addInfo("Press the Space key or A on your controller to join. Multiple local players are allowed.");
		networkMultiplayerPlayerJoinMenu->addInfo("Press Esc or Select on your controller to return to lobby.");
		networkMultiplayerPlayerJoinMenu->addInfo(" ");

		players.deleteAll();
	}

	if (networkMultiplayerRoomRulesMenu == nullptr)
	{
		//show room options
		networkMultiplayerRoomRulesMenu = new BobMenu(this, "");
		networkMultiplayerRoomRulesMenu->font = BobFont::ttf_oswald_12;
		networkMultiplayerRoomRulesMenu->center = false;


		networkMultiplayerRoomRulesMenu->addInfo("Host: ","Host");

	
		
		string privateOrPublic = "Public";
		if (currentRoom->privateRoom == true)
			privateOrPublic = "Private";
		networkMultiplayerRoomRulesMenu->addInfo("Visibility: " + privateOrPublic);

		string tournament = "Free Play";
		if (currentRoom->tournamentRoom == true)
			tournament = "Tournament (Will Affect Player Rankings)";
		networkMultiplayerRoomRulesMenu->addInfo("Visibility: " + privateOrPublic);

		string maxPlayers = "No Limit";
		if (currentRoom->maxPlayers > 1)
			maxPlayers = to_string(currentRoom->maxPlayers);
		networkMultiplayerRoomRulesMenu->addInfo("Max Players: " + maxPlayers);

		networkMultiplayerRoomRulesMenu->addInfo(" ");

		string gameName = "Game: Any Game Sequence Or Type";
		if (currentRoom->multiplayer_AllowDifferentGameSequences == false && currentRoom->multiplayer_SelectedGameSequence != nullptr)
		{
			if(currentRoom->multiplayer_SelectedGameSequence->gameTypes.size()==1)gameName = "Game Type: " + currentRoom->multiplayer_SelectedGameSequence->name;
			else gameName = "Game Sequence: " + currentRoom->multiplayer_SelectedGameSequence->name;
		}
		networkMultiplayerRoomRulesMenu->addInfo(gameName);

		string difficulty = "Any Difficulty";
		if (currentRoom->multiplayer_AllowDifferentDifficulties == false)
			difficulty = currentRoom->multiplayer_SelectedDifficultyName;
		networkMultiplayerRoomRulesMenu->addInfo("Difficulty: " + difficulty);

		string garbage = "Allowed";
		if (currentRoom->multiplayer_DisableVSGarbage)
			garbage = "No Garbage";
		networkMultiplayerRoomRulesMenu->addInfo("VS Garbage: " + garbage);

		string endWhenLose = "Continue Until All Players Lose";
		if (currentRoom->multiplayer_GameEndsWhenOnePlayerRemains)endWhenLose = "Game Ends When One Player Remains";
		networkMultiplayerRoomRulesMenu->addInfo("End Rule: " + endWhenLose);

		string endOnCredits = "Endless Mode";
		if (currentRoom->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel)endOnCredits = "Race To Credits";
		networkMultiplayerRoomRulesMenu->addInfo("Finish Rule: " + endWhenLose);

		networkMultiplayerRoomRulesMenu->addInfo(" ");
		
	}


	//TODO tell server when the game has ended, who won, stats, etc
	//TODO handle client timeout, disconnect, etc on server
	//TODO also if client logs off or times out room is removed

	//TODO: chatroom, maybe just use console
	//probably increase console font size
	//or maybe make another console object for chat
	//maybe when you hit g it opens the console and grabs keyboard focus
	//otherwise you can only see a few messages
	//have the chatroom available both in the multiplayer screen and in chat
	//also have a separate one in the multiplayer screen that sends to all connected friends



	{
		//show joined peers
		long long currentTime = System::currentHighResTimer();
		long long startTime = updatedJoinedPeersListTime;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (ticksPassed > 3000)
		{
			updatedJoinedPeersListTime = currentTime;

			if (networkMultiplayerJoinedPeersMenu == nullptr)
			{
				networkMultiplayerJoinedPeersMenu = new BobMenu(this, "");
				networkMultiplayerJoinedPeersMenu->font = BobFont::ttf_oswald_12;
				networkMultiplayerJoinedPeersMenu->center = false;
			}
			networkMultiplayerJoinedPeersMenu->clear();

			BobMenu::MenuItem* m = networkMultiplayerJoinedPeersMenu->addInfo("Peers In Room:");


			string name = "You";
			if (hosting)name += " (Host)";
			m = networkMultiplayerJoinedPeersMenu->addInfo(name);

			for (int i = 0; i < joinedPeers->size(); i++)
			{
				UDPPeerConnection *c = joinedPeers->get(i);
				name = c->getUserName();
				if (hosting == false && c == currentRoom->hostPeer)name += " (Host)";
				m = networkMultiplayerJoinedPeersMenu->addInfo(name);
				
			}
			networkMultiplayerJoinedPeersMenu->setAllCaptionsToFullAlpha();
			
			//set host menu item
			string user = "";
			if (hosting)
			{
				user = "You are hosting";
			}
			else
			{
				if (currentRoom->hostPeer != nullptr)user = currentRoom->hostPeer->getUserName();
			}
			networkMultiplayerRoomRulesMenu->getMenuItemByID("Host")->setText("Host: " + user);
		}
	}


	{

		//if game is public tell server about the room constantly

		long long currentTime = System::currentHighResTimer();
		long long startTime = lastSentServerRoomUpdateTime;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (ticksPassed > 5000)
		{
			lastSentServerRoomUpdateTime = currentTime;

			if (hosting && currentRoom->privateRoom==false)
			{

				string s = currentRoom->encodeRoomData(getServerConnection()->getUserID_S(),players.size(),false);

				tellServerIAmHostingOrUpdateRoomStatus(s);
				
			}
		}
	}


	{
		//need to tell all peers our hosting state because new peers might have connected
		long long currentTime = System::currentHighResTimer();
		long long startTime = lastSentPlayersUpdateTime;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (ticksPassed > 3000)
		{
			lastSentPlayersUpdateTime = currentTime;

			if (hosting)
			{
				tellAllPeersIAmHosting();
			}
		}
	}
	



	bool leaveMenu = false;

	bool allPlayersConfirmed = true;
	for (int i = 0; i<players.size(); i++)
	{
		PuzzlePlayer *p = players.get(i);
		if (p->confirmed == false)
		{
			allPlayersConfirmed = false;


			if (p->isNetworkPlayer() == false)
			{

				if (p->setGameSequence == false)
				{
					if (currentRoom->multiplayer_AllowDifferentGameSequences)
					{
						playerGameSequenceMiniMenuUpdate(p);
					}
					else
					{
						p->gameLogic->currentGameSequence = currentRoom->multiplayer_SelectedGameSequence;
						p->setGameSequence = true;
					}
				}
				else
					if (p->setDifficulty == false)
					{
						if (currentRoom->multiplayer_AllowDifferentDifficulties)
						{
							playerDifficultyMiniMenuUpdate(p);
						}
						else
						{
							p->gameLogic->currentGameSequence->currentDifficultyName = currentRoom->multiplayer_SelectedDifficultyName;
							p->setDifficulty = true;
						}
					}
					else
						if (p->confirmed == false)
						{
							tellAllPeersThatPlayerHasConfirmedAndSendGameSequence(p);
							p->confirmed = true;

							p->gameCaption = getCaptionManager()->newManagedCaption(0, 0, -1, p->gameLogic->currentGameSequence->name, BobFont::ttf_oswald_12, BobMenu::menuColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
							p->difficultyCaption = getCaptionManager()->newManagedCaption(0, 0, -1, p->gameLogic->currentGameSequence->currentDifficultyName, BobFont::ttf_oswald_12, BobMenu::menuColor, BobMenu::clearColor, RenderOrder::OVER_GUI);

						}
			}
		}
	}


	if (getControlsManager()->key_SPACE_Pressed())
	{
		if (currentRoom->maxPlayers > 1 && players.size() >= currentRoom->maxPlayers)
		{
			errorLabel->setText("Maximum players reached, cannot add a new player.");
		}
		else
		{
			bool add = true;
			if(currentRoom->tournamentRoom)
			{
				for(int i=0;i<players.size();i++)
				{
					PuzzlePlayer *p = players.get(i);
					if(p->isNetworkPlayer()==false)
					{
						add = false;
						errorLabel->setText("Tournament rooms can only have one local player per client.");
					}
				}
			}

			if (add)
			{
				bool alreadyInUse = false;
				for (int i = 0; i < players.size(); i++)
				{
					PuzzlePlayer *p = players.get(i);
					if (p->useKeyboard)alreadyInUse = true;
				}
				if (!alreadyInUse)
				{

					PuzzlePlayer *p = new PuzzlePlayer(new GameLogic(this, -1));
					p->useKeyboard = true;
					
					if (players.size()>0)
					{
						//always add local player on the left side, to the right of any existing local players
						int i = 0;
						while (players.get(i)->isNetworkPlayer() == false)i++;
						players.insert(i, p);
					}
					else
					{
						players.add(p);
					}
					p->nameCaption = getCaptionManager()->newManagedCaption(0, 0, -1, "Local (Keyboard)", BobFont::ttf_oswald_12, BobMenu::menuColor, BobMenu::clearColor, RenderOrder::OVER_GUI);

					tellAllJoinedPeersOneOfMyPlayersHasJoinedTheLobby(p);
				}
			}
		}

	}
	if (getControlsManager()->key_LSHIFT_Pressed())
	{
		for (int i = 0; i < players.size(); i++)
		{
			PuzzlePlayer *p = players.get(i);
			if (p->useKeyboard)
			{
				tellAllJoinedPeersOneOfMyPlayersHasLeftTheLobby(p);

				players.removeAt(i);
				delete p;
				i = 0;
			}
		}
	}


	for (int controllerNum = 0; controllerNum < getControlsManager()->gameControllers.size(); controllerNum++)
	{
		GameController *g = getControlsManager()->gameControllers.get(controllerNum);

		if (g->a_Pressed())
		{
			if (currentRoom->maxPlayers > 1 && players.size() >= currentRoom->maxPlayers)
			{
				errorLabel->setText("Maximum players reached, cannot add a new player.");
			}
			else
			{
				bool add = true;
				if (currentRoom->tournamentRoom)
				{
					for (int i = 0; i<players.size(); i++)
					{
						PuzzlePlayer *p = players.get(i);
						if (p->isNetworkPlayer() == false)
						{
							add = false;
							errorLabel->setText("Tournament rooms can only have one local player per client.");
						}
					}
				}

				if (add)
				{
					bool alreadyInUse = false;
					for (int i = 0; i < players.size(); i++)
					{
						PuzzlePlayer *p = players.get(i);
						if (p->gameController == g)alreadyInUse = true;
					}

					if (!alreadyInUse)
					{
						PuzzlePlayer *p = new PuzzlePlayer(new GameLogic(this, -1));
						p->gameController = g;
						if (players.size()>0)
						{
							//always add local player on the left side, to the right of any existing local players
							int i = 0;
							while(players.get(i)->isNetworkPlayer()==false)i++;
							players.insert(i, p);
						}
						else
						{
							players.add(p);
						}
						p->nameCaption = getCaptionManager()->newManagedCaption(0, 0, -1, "Local (Controller " + to_string(controllerNum) + ")", BobFont::ttf_oswald_12, BobMenu::menuColor, BobMenu::clearColor, RenderOrder::OVER_GUI);


						tellAllJoinedPeersOneOfMyPlayersHasJoinedTheLobby(p);
					}
				}
			}
		}

		if (g->b_Pressed())
		{
			for (int i = 0; i < players.size(); i++)
			{
				PuzzlePlayer *p = players.get(i);
				if (p->gameController == g)
				{
					tellAllJoinedPeersOneOfMyPlayersHasLeftTheLobby(p);
					
					players.removeAt(i);
					delete p;
					i = 0;
				}
			}
		}
	}



	//dont have scores yet, score and ranking is only for tournament play one on one
	if (getControlsManager()->key_ESC_Pressed() || getControlsManager()->miniGame_SELECT_Pressed())
	{
		//are you sure?  this will disconnect everyone from your game
		Caption *c = nullptr;

		if (hosting)c = getCaptionManager()->newManagedCaption(Caption::CENTERED_SCREEN, 0, -1, "Are you sure you want to cancel the game?  Press Space or Start to stay, Esc or Select again to cancel and quit.", BobFont::ttf_oswald_16, BobMenu::errorColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
		else c = getCaptionManager()->newManagedCaption(Caption::CENTERED_SCREEN, 0, -1, "Are you sure you want to leave the game?  Press Space or Start to stay, Esc or Select again to cancel and quit.", BobFont::ttf_oswald_16, BobMenu::errorColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
		bool quit = false;
		bool goback = false;
		while (quit == false && goback == false)
		{
			c->update();
			Main::whilefix();
			if (getControlsManager()->key_ESC_Pressed() || getControlsManager()->miniGame_SELECT_Pressed())quit = true;
			if (getControlsManager()->miniGame_START_Pressed() || getControlsManager()->key_SPACE_Pressed())goback = true;

		}
		c->setToBeDeletedImmediately();

		if (quit)
		{
			if (hosting)
			{
				//send to all friends disconnected

				tellAllJoinedPeersIHaveCanceledMyHostedGame();
				tellAllPeersIAmNotHosting();
				
				tellServerIHaveCanceledTheGame(currentRoom->uuid);
			}
			else
			{
				tellAllJoinedPeersIHaveLeftTheGame();
			}

			BobNet::myStatus = BobNet::status_AVAILABLE;
			joinedPeers->clear();

			leaveMenu = true;
			networkMultiplayerLobbyMenuShowing = true;

			initPlayer();
		}
	}


	if (hosting)
	{
		if (players.size() > 1)
		{
			if (allPlayersConfirmed)
			{
				if (networkMultiplayerPlayerJoinMenuPressStartCaption == nullptr)
					networkMultiplayerPlayerJoinMenuPressStartCaption = 
						getCaptionManager()->newManagedCaption(Caption::CENTERED_X, (int)(getHeight() - 50), -1, "Press the Enter key or Start on your controller to start game.", BobFont::ttf_oswald_16, BobMenu::menuColor, BobMenu::clearColor, RenderOrder::OVER_GUI);
				networkMultiplayerPlayerJoinMenuPressStartCaption->flashing = true;
				networkMultiplayerPlayerJoinMenuPressStartCaption->flashingTicksPerFlash = 1000;

				if (getControlsManager()->miniGame_START_Pressed())
				{
					//start the game!
					tellAllJoinedPeersMyHostedGameHasStarted();

					tellAllPeersIAmPlayingAGame();

					tellServerIHaveStartedTheGame(currentRoom->uuid);

					leaveMenu = true;
				}
			}
		}

		if (players.size() <= 1 || allPlayersConfirmed == false)
		{
			if (networkMultiplayerPlayerJoinMenuPressStartCaption != nullptr)
			{
				networkMultiplayerPlayerJoinMenuPressStartCaption->setToBeDeletedImmediately();
				networkMultiplayerPlayerJoinMenuPressStartCaption = nullptr;
			}
		}
	}


	if (hostStartedGame)
	{
		hostStartedGame = false;
		leaveMenu = true;
	}

	if (leaveMenu)
	{

		networkMultiplayerPlayerJoinMenuShowing = false;

		if (networkMultiplayerPlayerJoinMenu != nullptr)
		{
			delete networkMultiplayerPlayerJoinMenu;
			networkMultiplayerPlayerJoinMenu = nullptr;

			delete networkMultiplayerRoomRulesMenu;
			networkMultiplayerRoomRulesMenu = nullptr;

			delete networkMultiplayerJoinedPeersMenu;
			networkMultiplayerJoinedPeersMenu = nullptr;


			if (networkMultiplayerPlayerJoinMenuPressStartCaption != nullptr)
			{
				networkMultiplayerPlayerJoinMenuPressStartCaption->setToBeDeletedImmediately();
				networkMultiplayerPlayerJoinMenuPressStartCaption = nullptr;
			}
		}

		if (statusLabel != nullptr)
		{
			statusLabel->setToBeDeletedImmediately();
			statusLabel = nullptr;
		}

		if (errorLabel != nullptr)
		{
			errorLabel->setToBeDeletedImmediately();
			errorLabel = nullptr;
		}
	}

}

//=========================================================================================================================
void BobsGame::networkMultiplayerPlayerJoinMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(BobMenu::bgColor->ri(), BobMenu::bgColor->gi(), BobMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);


	BobTexture* kt = keyboardIconTexture;
	BobTexture* gt = controllerIconTexture;
	BobTexture* nt = networkIconTexture;

	if (networkMultiplayerPlayerJoinMenu == nullptr)return;
	if (networkMultiplayerRoomRulesMenu == nullptr)return;
	if (networkMultiplayerJoinedPeersMenu == nullptr)return;

	int bottomY = 0;
	int bottomY2 = 0;
	int bottomY3 = 0;
	networkMultiplayerPlayerJoinMenu->render(0, 0, GLUtils::getViewportHeight(), true, nullptr, &bottomY);
	networkMultiplayerRoomRulesMenu->render(bottomY, GLUtils::getViewportWidth() / 5 * 1, GLUtils::getViewportHeight(), true, nullptr, &bottomY2);
	networkMultiplayerJoinedPeersMenu->render(bottomY, GLUtils::getViewportWidth() / 5 * 3, GLUtils::getViewportHeight(), true, nullptr, &bottomY3);
	if (bottomY2 > bottomY)bottomY = bottomY2;
	if (bottomY3 > bottomY)bottomY = bottomY3;

	if (statusLabel != nullptr && errorLabel != nullptr)
	{
		statusLabel->screenY = (float)(getHeight() / 4 * 3);
		errorLabel->screenY = (float)((getHeight() / 4 * 3) + 20);
	}

	for (int i = 0; i < players.size(); i++)
	{
		PuzzlePlayer *p = players.get(i);

		BobTexture *t = nullptr;

		if (p->useKeyboard)t = kt;
		else
			if (p->gameController != nullptr)t = gt;
			else if (p->isNetworkPlayer())t = nt;

			float sx0 = 0;
			float sx1 = 0;
			float sy0 = 0;
			float sy1 = 0;

			if (t != nullptr)
			{
				int slot = players.size();
				if (slot < 2)slot = 2;

				float tx0 = 0;
				float tx1 = (float)(t->getImageWidth()) / (float)(t->getTextureWidth());
				float ty0 = 0;
				float ty1 = (float)((float)(t->getImageHeight()) / (float)(t->getTextureHeight()));

				float ratio = (float)(getWidth() / slot / 6 * 2) / (float)(t->getImageWidth());

				sx0 = (float)((int)(getWidth() / slot*i + getWidth() / slot / 6 * 2));
				sx1 = sx0 + (int)((getWidth() / slot) / 6 * 2);
				sy0 = (float)((int)(bottomY + 20));
				sy1 = sy0 + (float)((int)(t->getImageHeight() * ratio));

				GLUtils::drawTexture(t, tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_NEAREST);
			}

			float x = (float)((int)sx0);
			float y = (float)((int)sy1 + 6);
			if (p->confirmed == false && p->isNetworkPlayer() == false)
			{
				playerDifficultyMiniMenuRender(p, x, y);
			}
			else
				if (p->confirmed == true)
				{
					//draw greencheck mark or green box or something?
					GLUtils::drawFilledRect(0, 255, 0, sx0, sx1, sy0, sy1, 0.2f);

					if (p->gameCaption != nullptr)
					{
						p->gameCaption->screenX = sx0;
						p->gameCaption->screenY = sy1 + 4;
						//p->gameCaption->render();
					}
					if (p->difficultyCaption != nullptr)
					{
						p->difficultyCaption->screenX = sx0;
						p->difficultyCaption->screenY = sy1 + 4 + 16;
						//p->difficultyCaption->render();
					}
				}

			//need to render friend name and player number
			if (p->nameCaption != nullptr)
			{
				p->nameCaption->screenX = sx0;
				p->nameCaption->screenY = sy1 - 12;
				//p->nameCaption->render();
			}
	}



}
