#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


const int BobNet::clientUDPPortStartRange = 6434;


const string BobNet::endline = ":END:\r\n";
//const bool BobNet::debugMode = true;
const string BobNet::debugServerAddress = "localhost";
const string BobNet::releaseServerAddress = "server.bobsgame.com";
const int BobNet::serverTCPPort = 6065;
const string BobNet::debugSTUNServerAddress = "localhost";
const string BobNet::releaseSTUNServerAddress = "stun.bobsgame.com";
const int BobNet::STUNServerUDPPort = 6433;
const string BobNet::debugBigDataURL = "http://localhost/z/";
const string BobNet::releaseBigDataURL = "https://bobsgame.s3.amazonaws.com/z/";
const string BobNet::debugSmallDataURL = "http://localhost/assets/";
const string BobNet::releaseSmallDataURL = "http://bobsgame.com/assets/";
const string BobNet::debugINDEXServerAddress = "localhost";
const string BobNet::releaseINDEXServerAddress = "index.bobsgame.com";
const int BobNet::INDEXServerTCPPort = 606;
const string BobNet::Server_IP_Address_Request = "Server_IP_Address_Request:";
const string BobNet::Server_IP_Address_Response = "Server_IP_Address_Response:";
const string BobNet::Login_Request = "Login_Request:";
const string BobNet::Login_Response = "Login_Response:";
const string BobNet::Reconnect_Request = "Reconnect_Request:";
const string BobNet::Reconnect_Response = "Reconnect_Response:";
const string BobNet::Facebook_Login_Request = "Facebook_Login_Request:";
const string BobNet::Facebook_Login_Response = "Facebook_Login_Response:";
const string BobNet::Password_Recovery_Request = "Password_Recovery_Request:";
const string BobNet::Password_Recovery_Response = "Password_Recovery_Response:";
const string BobNet::Create_Account_Request = "Create_Account_Request:";
const string BobNet::Create_Account_Response = "Create_Account_Response:";
const string BobNet::Initial_GameSave_Request = "Initial_GameSave_Request:";
const string BobNet::Initial_GameSave_Response = "Initial_GameSave_Response:";
const string BobNet::Encrypted_GameSave_Update_Request = "Encrypted_GameSave_Update_Request:";
const string BobNet::Encrypted_GameSave_Update_Response = "Encrypted_GameSave_Update_Response:";
const string BobNet::Postal_Code_Update_Request = "Postal_Code_Update_Request:";
const string BobNet::Postal_Code_Update_Response = "Postal_Code_Update_Response:";
const string BobNet::Player_Coords = "Player_Coords:";
const string BobNet::Map_Request_By_Name = "Map_Request_By_Name:";
const string BobNet::Map_Request_By_ID = "Map_Request_By_ID:";
const string BobNet::Map_Response = "Map_Response:";
const string BobNet::Sprite_Request_By_Name = "Sprite_Request_By_Name:";
const string BobNet::Sprite_Request_By_ID = "Sprite_Request_By_ID:";
const string BobNet::Sprite_Response = "Sprite_Response:";
const string BobNet::Dialogue_Request = "Dialogue_Request:";
const string BobNet::Dialogue_Response = "Dialogue_Response:";
const string BobNet::Load_Event_Request = "Load_Event_Request:";
const string BobNet::Load_Event_Response = "Load_Event_Response:";
const string BobNet::Event_Request = "Event_Request:";
const string BobNet::Event_Response = "Event_Response:";
const string BobNet::GameString_Request = "GameString_Request:";
const string BobNet::GameString_Response = "GameString_Response:";
const string BobNet::Flag_Request = "Flag_Request:";
const string BobNet::Flag_Response = "Flag_Response:";
const string BobNet::Skill_Request = "Skill_Request:";
const string BobNet::Skill_Response = "Skill_Response:";
const string BobNet::Music_Request = "Music_Request:";
const string BobNet::Music_Response = "Music_Response:";
const string BobNet::Sound_Request = "Sound_Request:";
const string BobNet::Sound_Response = "Sound_Response:";
const string BobNet::Add_Friend_By_UserName_Request = "Add_Friend_By_UserName_Request:";
const string BobNet::Add_Friend_By_UserName_Response = "Add_Friend_By_UserName_Response:";
const string BobNet::Update_Facebook_Account_In_DB_Request = "Update_Facebook_Account_In_DB_Request:";
const string BobNet::Update_Facebook_Account_In_DB_Response = "Update_Facebook_Account_In_DB_Response:";
const string BobNet::Online_Friends_List_Request = "Online_Friends_List_Request:";
const string BobNet::Online_Friends_List_Response = "Online_Friends_List_Response:";
const string BobNet::Friend_Is_Online_Notification = "Friend_Is_Online_Notification:";
const string BobNet::Tell_Client_Their_Session_Was_Logged_On_Somewhere_Else = "Tell_Client_Their_Session_Was_Logged_On_Somewhere_Else:";
const string BobNet::Tell_Client_Servers_Are_Shutting_Down = "Tell_Client_Servers_Are_Shutting_Down:";
const string BobNet::Tell_Client_Servers_Have_Shut_Down = "Tell_Client_Servers_Have_Shut_Down:";
const string BobNet::STUN_Request = "STUN_Request:";
const string BobNet::STUN_Response = "STUN_Response:";
const string BobNet::Friend_Connect_Request = "Friend_Connect_Request:";
const string BobNet::Friend_Connect_Response = "Friend_Connect_Response:";
const string BobNet::Friend_Data_Request = "Friend_Data_Request:";
const string BobNet::Friend_Data_Response = "Friend_Data_Response:";
const string BobNet::Friend_LocationStatus_Update = "Friend_Location_Update:";
const string BobNet::Game_Connect_Request = "Game_Connect_Request:";
const string BobNet::Game_Connect_Response = "Game_Connect_Response:";
const string BobNet::Game_Challenge_Request = "Game_Challenge_Request:";
const string BobNet::Game_Challenge_Response = "Game_Challenge_Response:";
const string BobNet::INDEX_Register_Server_With_INDEX_Request = "INDEX_Register_Server_With_INDEX_Request:";
const string BobNet::INDEX_Tell_ServerID_To_Tell_UserID_That_UserIDs_Are_Online = "INDEX_Tell_ServerID_To_Tell_UserID_That_UserIDs_Are_Online:";
const string BobNet::INDEX_Tell_All_Servers_To_Tell_FacebookIDs_That_UserID_Is_Online = "INDEX_Tell_All_Servers_To_Tell_FacebookIDs_That_UserID_Is_Online:";
const string BobNet::INDEX_UserID_Logged_On_This_Server_Log_Them_Off_Other_Servers = "INDEX_UserID_Logged_On_This_Server_Log_Them_Off_Other_Servers:";
const string BobNet::Server_Register_Server_With_INDEX_Response = "Server_Registered_With_INDEX_Response:";
const string BobNet::Server_Tell_All_FacebookIDs_That_UserID_Is_Online = "Server_Tell_All_FacebookIDs_That_UserID_Is_Online:";
const string BobNet::Server_Tell_UserID_That_UserIDs_Are_Online = "Server_Tell_UserID_That_UserIDs_Are_Online:";
const string BobNet::Server_UserID_Logged_On_Other_Server_So_Log_Them_Off = "Server_UserID_Logged_On_Other_Server_So_Log_Them_Off:";
const string BobNet::Server_Tell_All_Users_Servers_Are_Shutting_Down = "Server_Tell_All_Users_Servers_Are_Shutting_Down:";
const string BobNet::Server_Tell_All_Users_Servers_Have_Shut_Down = "Server_Tell_All_Users_Servers_Have_Shut_Down:";
const string BobNet::Bobs_Game_GameTypesAndSequences_Download_Request = "Bobs_Game_GameTypesAndSequences_Download_Request:";
const string BobNet::Bobs_Game_GameTypesAndSequences_Download_Response = "Bobs_Game_GameTypesAndSequences_Download_Response:";
const string BobNet::Bobs_Game_GameTypesAndSequences_Upload_Request = "Bobs_Game_GameTypesAndSequences_Upload_Request:";
const string BobNet::Bobs_Game_GameTypesAndSequences_Upload_Response = "Bobs_Game_GameTypesAndSequences_Upload_Response:";

const string BobNet::Bobs_Game_GameTypesAndSequences_Vote_Request = "Bobs_Game_GameTypesAndSequences_Vote_Request:";
const string BobNet::Bobs_Game_GameTypesAndSequences_Vote_Response = "Bobs_Game_GameTypesAndSequences_Vote_Response:";



const string BobNet::Bobs_Game_RoomList_Request = "Bobs_Game_RoomList_Request:";
const string BobNet::Bobs_Game_RoomList_Response = "Bobs_Game_RoomList_Response:";
const string BobNet::Bobs_Game_TellRoomHostToAddMyUserID = "Bobs_Game_TellRoomHostToAddMyUserID:";

const string BobNet::Bobs_Game_HostingPublicRoomUpdate = "Bobs_Game_HostingPublicRoomUpdate:";
const string BobNet::Bobs_Game_HostingPublicRoomStarted = "Bobs_Game_HostingPublicRoomStarted:";
const string BobNet::Bobs_Game_HostingPublicRoomCanceled = "Bobs_Game_HostingPublicRoomCanceled:";
const string BobNet::Bobs_Game_HostingPublicRoomEnded = "Bobs_Game_HostingPublicRoomEnded:";

const string BobNet::Bobs_Game_GameStats = "Bobs_Game_GameStats:";


const string BobNet::Bobs_Game_UserStatsForSpecificGameAndDifficulty = "Bobs_Game_UserStatsForSpecificGameAndDifficulty:";
const string BobNet::Bobs_Game_LeaderBoardsByTotalTimePlayed = "Bobs_Game_LeaderBoardsByTotalTimePlayed:";
const string BobNet::Bobs_Game_LeaderBoardsByTotalBlocksCleared = "Bobs_Game_LeaderBoardsByTotalBlocksCleared:";
const string BobNet::Bobs_Game_LeaderBoardsByPlaneswalkerPoints = "Bobs_Game_LeaderBoardsByPlaneswalkerPoints:";
const string BobNet::Bobs_Game_LeaderBoardsByEloScore = "Bobs_Game_LeaderBoardsByEloScore:";
const string BobNet::Bobs_Game_HighScoreBoardsByTimeLasted = "Bobs_Game_HighScoreBoardsByTimeLasted:";
const string BobNet::Bobs_Game_HighScoreBoardsByBlocksCleared = "Bobs_Game_HighScoreBoardsByBlocksCleared:";









Logger BobNet::log = Logger("BobNet");
Logger* BobNet::_threadLog = new Logger("BobNet");

ArrayList<UDPPeerConnection*> BobNet::udpConnections;
TCPServerConnection BobNet::tcpServerConnection;
int BobNet::myStatus = status_AVAILABLE;
ArrayList<State*> BobNet::engines;


bool BobNet::threadStarted = false;

BobNet::BobNet()
{

}

BobNet::~BobNet()
{
	if (threadStarted)
	{
		setStopThread_S(true);
		t.join();
	}

	for(int i=0;i<udpConnections.size();i++)
	{
		UDPPeerConnection *c = udpConnections.get(i);
		delete c;
	}
	udpConnections.clear();

	//delete tcpServerConnection;
}


mutex BobNet::threadLog_Mutex;
thread BobNet::t;

UDPsocket BobNet::_socket = UDPsocket();
mutex BobNet::_socket_Mutex;

SDLNet_SocketSet BobNet::_socketSet = SDLNet_AllocSocketSet(1);
mutex BobNet::_socketSet_Mutex;

bool BobNet::_socketAddedToSet = false;
mutex BobNet::_socketAddedToSet_Mutex;

bool BobNet::_socketIsOpen = false;
mutex BobNet::_socketIsOpen_Mutex;

bool BobNet::_stopThread = false;
mutex BobNet::_stopThread_Mutex;

int BobNet::_stunChannel = -1;
mutex BobNet::_stunChannel_Mutex;

IPaddress* BobNet::_stunServerIPAddress_S = nullptr;
int BobNet::_stunServerPort_S = -1;
mutex BobNet::_stunServerIPAddress_Mutex;

queue<string> BobNet::_stunMessageQueue;
mutex BobNet::_stunMessageQueue_Mutex;

//===============================================================================================
void BobNet::addEngineToForwardMessagesTo(State* e)
{//===============================================================================================
	if(engines.contains(e)==false)
	engines.add(e);
}
//===============================================================================================
void BobNet::update()
{//===============================================================================================

	if (threadStarted == false)
	{
		log.debug("Created STUN thread");
		t = thread(&BobNet::updateThreadLoop);
		threadStarted = true;
	}

	while (stunMessageQueueSize_S()>0)
	{
		string s = stunMessageQueueFront_S();
		stunMessageQueuePop_S();
		udpSTUNMessageReceived(s);
	}


	tcpServerConnection.update();

	for (int i = 0; i < udpConnections.size(); i++)
	{
		UDPPeerConnection *p = udpConnections.get(i);
		p->update();
	}
}



//===============================================================================================
void BobNet::updateThreadLoop()
{//===============================================================================================

	//long long _queuedSaveGameUpdateDelayTime = 0;
	//long long _sendOnlineFriendListRequestTime = 0;
	//long long _sendOutgoingAuthorizedMessageQueueTime = 0;
	//bool _checkedSessionToken = false;

	while (getStopThread_S() == false)
	{
		this_thread::sleep_for(chrono::milliseconds(10));
		//SDL_Delay(10);

		_checkForIncomingSTUNTraffic();

	}
}


//===============================================================================================
bool BobNet::_ensureSocketIsOpen()
{//===============================================================================================
	if (getStunServerIPAddress_S() == nullptr)
	{
		setStunServerIPAddress_S(Main::STUNServerAddressString.c_str(), BobNet::STUNServerUDPPort);

		if (getStunServerIPAddress_S() == nullptr)return false;
	}

	if (getSocketIsOpen_S() == false)
	{
		if (getSocketAddedToSet_S())
		{
			if (SDLNet_UDP_DelSocket(getSocketSet_S(), getSocket_S()) < 0)
			{
				threadLogDebug_S("SDLNet_UDP_DelSocket: " + string(SDLNet_GetError()) + string(SDL_GetError()));
				SDL_ClearError();
			}
			setSocketAddedToSet_S(false);
		}

		setSocket_S(SDLNet_UDP_Open(BobNet::STUNServerUDPPort));
		log.debug("Opened socket to STUN server on port " + to_string(BobNet::STUNServerUDPPort));
		if (!getSocket_S())
		{
			//SDLNet_FreeSocketSet(set);
			threadLogError_S("SDLNet_UDP_Open stunServerAddress: " + string(SDLNet_GetError()) + string(SDL_GetError()));
			SDL_ClearError();
			return false;
		}

		if (getSocketAddedToSet_S() == false)
		{
			if (SDLNet_UDP_AddSocket(getSocketSet_S(), getSocket_S()) < 0)
			{
				threadLogDebug_S("SDLNet_UDP_AddSocket: " + string(SDLNet_GetError()) + string(SDL_GetError()));
				SDL_ClearError();
			}
			else
				setSocketAddedToSet_S(true);
		}

		setStunChannel_S(SDLNet_UDP_Bind(getSocket_S(), -1, getStunServerIPAddress_S()));

		setSocketIsOpen_S(true);
		return true;
	}
	return true;
}
//===============================================================================================
bool BobNet::_checkForIncomingSTUNTraffic()
{//===============================================================================================

	if (_ensureSocketIsOpen() == false)return false;

	int numReady = SDLNet_CheckSockets(getSocketSet_S(), 0);
	if (numReady < 0)
	{
		threadLogDebug_S("SDLNet_CheckSockets: " + string(SDLNet_GetError()) + string(SDL_GetError()));
		SDL_ClearError();
	}

	int numPacketsReceived = 0;

	if (numReady > 0)
	{

		int rd = SDLNet_SocketReady(getSocket_S());

		if (rd > 0)
		{
			UDPpacket *packet = SDLNet_AllocPacket(10000);
			numPacketsReceived = SDLNet_UDP_Recv(getSocket_S(), packet);

			if (numPacketsReceived > 0)
			{
				if (packet->address.host != getStunServerIPAddress_S()->host)
				{
					threadLogError_S("STUN address didn't match in incoming packet.");
				}

				string s = string((char*)packet->data, packet->len);

				SDLNet_FreePacket(packet);

				//return udpSTUNMessageReceived(s);
				stunMessageQueuePush_S(s);
				return true;

			}
			else if (numPacketsReceived < 0)
			{
				SDLNet_FreePacket(packet);
				//connection lost
				SDLNet_UDP_Close(getSocket_S());

				if (getSocketAddedToSet_S())
				{
					if (SDLNet_UDP_DelSocket(getSocketSet_S(), getSocket_S()) < 0)
					{
						threadLogDebug_S("SDLNet_UDP_DelSocket: " + string(SDLNet_GetError()) + string(SDL_GetError()));
						SDL_ClearError();
					}

					setSocketAddedToSet_S(false);
				}
				setSocketIsOpen_S(false);
				return false;
			}
			SDLNet_FreePacket(packet);
		}
		else
		if (rd < 0)
		{
			threadLogError_S("SDLNet_TCP_Recv Error: " + string(SDLNet_GetError()) + string(SDL_GetError()));
			SDL_ClearError();
			return false;
		}
	}
	return false;
}
//===============================================================================================
bool BobNet::udpSTUNMessageReceived(string e)
{//===============================================================================================

	if (String::startsWith(e, BobNet::STUN_Response))
	{

		//make sure it is from the correct IP

		//	if (e->getRemoteAddress()->toString()->equals(stunServerAddress->toString()) == false)
		//	{
		//		log.error("STUN IP address didn't match stunServerAddress");
		//		return;
		//	}

		string s = e;

		if (s.find(BobNet::endline) == string::npos)
		{
			log.error("Message doesn't end with endline");
			s = s + BobNet::endline;
		}

		//strip off endline
		s = s.substr(0, s.find(BobNet::endline));

#ifdef _DEBUG
		log.debug(s);
#endif
		string friendIPString = "";
		int friendPort = -1;

		//STUNResponse:userID,/127.0.0.1:stunport,peerPort,
		s = s.substr(s.find(":") + 1); //userID,/127.0.0.1:stunport,peerPort,
		int replyFriendUserID = -1;

		try
		{
			replyFriendUserID = stoi(s.substr(0, s.find(",")));
		}
		catch(exception)
		{
			log.error("Could not parse friend User ID in STUN reply");
			return false;
		}

		s = s.substr(s.find(",") + 1);//socketString looks like /127.0.0.1:stunport,peerPort,
		s = s.substr(s.find("/") + 1);//skip over /
		friendIPString = s.substr(0, s.find(":"));
		s = s.substr(s.find(",") + 1); //skip stunport

		string portString = s.substr(0,s.find(","));//peerPort
		try
		{
			friendPort = stoi(portString);
		}
		catch(exception)
		{
			log.error("Could not parse friend port in STUN reply");
			return false;
		}

		if (friendIPString.length() == 0)
		{
			return false;
		}
		if (friendPort == -1)
		{
			return false;
		}
		//log.debug("STUN reply:"+to_string(replyFriendUserID)+":" + friendIPString + ":" + to_string(friendPort));

		//find udpPeerConnection with that userID
		bool found = false;
		for(int i=0;i<udpConnections.size();i++)
		{
			UDPPeerConnection *c = udpConnections.get(i);
			if(c->peerUserID==replyFriendUserID)
			{
				c->setPeerIPAddress_S(friendIPString, friendPort);
				found = true;
			}
		}
		if(!found)
		{
			log.error("Could not find peer with STUN reply userID");
		}
		
		
		return true;
	}
	return false;
}


//===============================================================================================
void BobNet::sendSTUNRequest(long long myUserID, long long friendUserID, int myPort)
{ //===============================================================================================

	if (_ensureSocketIsOpen() == false)return;

	string s = (BobNet::STUN_Request + to_string(myUserID) + string(",") + to_string(friendUserID) + string(",") + to_string(myPort) + string(",") + BobNet::endline);

#ifdef _DEBUG
		log.debug(string("SEND STUN SERVER:") + s.substr(0, s.length() - BobNet::endline.length()));
#endif

	const char* buf = s.c_str();

	int sent = 0;

	//UDPpacket * packet = SDLNet_AllocPacket(s.length());
	UDPpacket packet;
	packet.channel = -1;
	packet.address = *getStunServerIPAddress_S();
	packet.data = (Uint8*)buf;
	packet.len = (int)s.length();
	//SDLNet_FreePacket(packet);

	sent += SDLNet_UDP_Send(getSocket_S(), -1, &packet);

	if (sent==0)
	{
		log.error("Could not send UDP packet to STUN server");
	}
}


//===============================================================================================
UDPPeerConnection* BobNet::addFriendID(long long friendID, int type)
{//===============================================================================================

	//if (type == UDPPeerConnection::FACEBOOK_TYPE)
	{
		for (int i = 0; i < udpConnections.size(); i++)
		{
			if (udpConnections.get(i)->peerUserID == friendID)
			{
				return udpConnections.get(i);
			}
		}

		UDPPeerConnection* f = new UDPPeerConnection(friendID,type);
		udpConnections.add(f);
		log.debug("Added peer: " + to_string(friendID));
		return f;
	}
}

//===============================================================================================
void BobNet::sendAllPeers(string s)
{//===============================================================================================
	for (int i = 0; i < udpConnections.size(); i++)
	{
		UDPPeerConnection* c = udpConnections.get(i);
		if (c->getConnectedToPeer_S())
		{
			c->writeReliable_S(s);
		}
	}
}

