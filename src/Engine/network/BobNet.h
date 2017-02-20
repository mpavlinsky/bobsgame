//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class UDPPeerConnection;
class TCPServerConnection;
class State;
class Logger;


class BobNet
{
public:
	static Logger log;

	BobNet();
	~BobNet();
	

	static void addEngineToForwardMessagesTo(State* e);
	static void update();

	static ArrayList<UDPPeerConnection*> udpConnections;
	static TCPServerConnection tcpServerConnection;// = nullptr;

	static const int status_AVAILABLE = 0;
	static const int status_PLAYING_GAME = 1;
	static const int status_AWAY = 2;
	static const int status_DO_NOT_DISTURB = 3;
	static const int status_HOSTING_BOBSGAME = 4;
	static const int status_PLAYING_BOBSGAME = 5;

	static int myStatus;// = status_AVAILABLE;

	static void sendAllPeers(string s);
	static UDPPeerConnection* addFriendID(long long friendID, int type);

	static ArrayList<State*>engines;// = new ArrayList<State*>();



	static bool udpSTUNMessageReceived(string e);
	static void sendSTUNRequest(long long myUserID, long long friendUserID, int myPort);


	static bool threadStarted;
	static thread t;
public:
	static void updateThreadLoop();
	//------------------------------------
private:
	static Logger* _threadLog;
	static mutex threadLog_Mutex;
public:
	static void threadLogDebug_S(string s)
	{
		lock_guard<mutex> lock(threadLog_Mutex);
		_threadLog->debug(s);
	}
	static void threadLogWarn_S(string s)
	{
		lock_guard<mutex> lock(threadLog_Mutex);
		_threadLog->warn(s);
	}
	static void threadLogInfo_S(string s)
	{
		lock_guard<mutex> lock(threadLog_Mutex);
		_threadLog->info(s);
	}
	static void threadLogError_S(string s)
	{
		lock_guard<mutex> lock(threadLog_Mutex);
		_threadLog->error(s);
	}
	//------------------------------------
private:
	static bool _stopThread;
	static mutex _stopThread_Mutex;
public:
	static bool getStopThread_S()
	{
		lock_guard<mutex> lock(_stopThread_Mutex);
		return _stopThread;
	}
	static void setStopThread_S(bool b)
	{
		lock_guard<mutex> lock(_stopThread_Mutex);
		_stopThread = b;
	}
	
	//------------------------------------
private:
	static UDPsocket _socket;
	static mutex _socket_Mutex;
public:
	static UDPsocket getSocket_S()
	{
		lock_guard<mutex> lock(_socket_Mutex);
		return _socket;
	}
	static void setSocket_S(UDPsocket s)
	{
		lock_guard<mutex> lock(_socket_Mutex);
		_socket = s;
	}

	//------------------------------------
private:
	static SDLNet_SocketSet _socketSet;
	static mutex _socketSet_Mutex;
public:
	static SDLNet_SocketSet getSocketSet_S()
	{
		lock_guard<mutex> lock(_socketSet_Mutex);
		return _socketSet;
	}
	static void setSocketSet_S(SDLNet_SocketSet s)
	{
		lock_guard<mutex> lock(_socketSet_Mutex);
		_socketSet = s;
	}

	//------------------------------------
private:
	static bool _socketAddedToSet;
	static mutex _socketAddedToSet_Mutex;
public:
	static bool getSocketAddedToSet_S()
	{
		lock_guard<mutex> lock(_socketAddedToSet_Mutex);
		return _socketAddedToSet;
	}
	static void setSocketAddedToSet_S(bool s)
	{
		lock_guard<mutex> lock(_socketAddedToSet_Mutex);
		_socketAddedToSet = s;
	}
	//------------------------------------
private:
	static bool _socketIsOpen;
	static mutex _socketIsOpen_Mutex;
public:
	static bool getSocketIsOpen_S()
	{
		lock_guard<mutex> lock(_socketIsOpen_Mutex);
		return _socketIsOpen;
	}
	static void setSocketIsOpen_S(bool s)
	{
		lock_guard<mutex> lock(_socketIsOpen_Mutex);
		_socketIsOpen = s;
	}
	//------------------------------------
private:
	static int _stunChannel;
	static mutex _stunChannel_Mutex;
public:
	static int getStunChannel_S()
	{
		lock_guard<mutex> lock(_stunChannel_Mutex);
		return _stunChannel;
	}
	static void setStunChannel_S(int s)
	{
		lock_guard<mutex> lock(_stunChannel_Mutex);
		_stunChannel = s;
	}

	//------------------------------------
private:
	static IPaddress* _stunServerIPAddress_S;
	static int _stunServerPort_S;
	static mutex _stunServerIPAddress_Mutex;
public:
	static IPaddress* getStunServerIPAddress_S()
	{
		lock_guard<mutex> lock(_stunServerIPAddress_Mutex);
		return _stunServerIPAddress_S;
	}
	static void setStunServerIPAddress_S(string ipAddressString, int port)
	{

		lock_guard<mutex> lock(_stunServerIPAddress_Mutex);

		if (ipAddressString == "")
		{
#ifdef _DEBUG
			threadLogDebug_S("Set STUN address to null");
#endif
			if (_stunServerIPAddress_S != nullptr)
			{
				delete _stunServerIPAddress_S;
				_stunServerIPAddress_S = nullptr;
			}
			_stunServerPort_S = port;
		}
		else
		{
			_stunServerIPAddress_S = new IPaddress();
			_stunServerPort_S = port;

			if (SDLNet_ResolveHost(_stunServerIPAddress_S, ipAddressString.c_str(), port) < 0)
			{
				threadLogWarn_S("Could not resolve STUN host: " + string(SDLNet_GetError()));
				SDL_ClearError();
				_stunServerIPAddress_S = nullptr;
			}

			threadLogDebug_S("Set STUN address to " + ipAddressString + ":" + to_string(port));

		}
	}
	//------------------------------------

private:
	static queue<string> _stunMessageQueue;
	static mutex _stunMessageQueue_Mutex;
public:
	static string stunMessageQueueFront_S()
	{
		lock_guard<mutex> lock(_stunMessageQueue_Mutex);
		return _stunMessageQueue.front();
	}
	static int stunMessageQueueSize_S()
	{
		lock_guard<mutex> lock(_stunMessageQueue_Mutex);
		return (int)_stunMessageQueue.size();
	}
	static void stunMessageQueuePop_S()
	{
		lock_guard<mutex> lock(_stunMessageQueue_Mutex);
		_stunMessageQueue.pop();
	}
	static void stunMessageQueuePush_S(string &p)
	{
		lock_guard<mutex> lock(_stunMessageQueue_Mutex);
		_stunMessageQueue.push(p);
	}
	//------------------------------------
	static bool _checkForIncomingSTUNTraffic();
	static bool _ensureSocketIsOpen();






































	const static string endline;

	//=========================================================================================
	// GLOBAL DEBUG FOR BOTH CLIENT AND SERVER
	//=========================================================================================
	//const static bool debugMode;
	//=========================================================================================

	//=========================================================================================
	// SHARED NETWORK ADDRESSES FOR CLIENT AND SERVER
	//
	//  DO NOT PUT ANYTHING PRIVATE IN HERE - IT IS COMPILED INTO CLIENT
	//=========================================================================================

	const static string debugServerAddress;
	const static string releaseServerAddress;
	const static int serverTCPPort;

	//================================
	// used to connect to STUN and then for CLIENT P2P
	//================================
	const static int clientUDPPortStartRange;

	const static string debugSTUNServerAddress;
	const static string releaseSTUNServerAddress;
	const static int STUNServerUDPPort; // FOR STUN SERVER

	//================================
	// BIG DATA (zips, mp3, applet + libs (jars))
	//================================

	const static string debugBigDataURL;
	const static string releaseBigDataURL; //s3 storage.
	//cant use a CNAME for ssl on s3 because the cert comes from apache and s3.amazon.com sends its own cert,
	//but ONLY for s3.amazonaws.com, NOT assets.bobsgame.com.s3.amazonaws.com and CANT make a CNAME for s3.amazonaws.com/bobsgame
	//so i can only use https://bobsgame.s3.amazonaws.com OR s3.amazonaws.com/bobsgame, oh well.

	//================================
	// SMALL DATA (individual asset files (md5 names))
	//================================

	const static string debugSmallDataURL;
	const static string releaseSmallDataURL; //dreamhost storage


	//================================
	// HUB ADDRESS/PORT, should only be used by servers.
	//================================

	const static string debugINDEXServerAddress;
	const static string releaseINDEXServerAddress;
	const static int INDEXServerTCPPort;


	static const string Server_IP_Address_Request;
	static const string Server_IP_Address_Response;


	static const string Login_Request;
	static const string Login_Response;


	static const string Reconnect_Request;
	static const string Reconnect_Response;

	static const string Facebook_Login_Request;
	static const string Facebook_Login_Response;


	static const string Password_Recovery_Request;
	static const string Password_Recovery_Response;


	static const string Create_Account_Request;
	static const string Create_Account_Response;


	static const string Initial_GameSave_Request;
	static const string Initial_GameSave_Response;


	static const string Encrypted_GameSave_Update_Request;
	static const string Encrypted_GameSave_Update_Response;


	//deprecated, client side geolookup using google/yahoo API now.
	static const string Postal_Code_Update_Request;
	static const string Postal_Code_Update_Response;


	static const string Player_Coords;
	//no server response


	static const string Map_Request_By_Name;
	static const string Map_Request_By_ID;
	static const string Map_Response;


	static const string Sprite_Request_By_Name;
	static const string Sprite_Request_By_ID;
	static const string Sprite_Response;


	static const string Dialogue_Request;
	static const string Dialogue_Response;

	static const string Load_Event_Request;
	static const string Load_Event_Response;


	static const string Event_Request;
	static const string Event_Response;


	static const string GameString_Request;
	static const string GameString_Response;

	static const string Flag_Request;
	static const string Flag_Response;

	static const string Skill_Request;
	static const string Skill_Response;

	static const string Music_Request;
	static const string Music_Response;


	static const string Sound_Request;
	static const string Sound_Response;


	static const string Update_Facebook_Account_In_DB_Request; //this is sent from the client to the server with the FB sessionToken
	static const string Update_Facebook_Account_In_DB_Response;

	static const string Add_Friend_By_UserName_Request;
	static const string Add_Friend_By_UserName_Response;


	static const string Online_Friends_List_Request;
	static const string Online_Friends_List_Response;


	//no client request
	static const string Friend_Is_Online_Notification;


	//no client request
	static const string Tell_Client_Their_Session_Was_Logged_On_Somewhere_Else;


	//no client request
	static const string Tell_Client_Servers_Are_Shutting_Down;
	static const string Tell_Client_Servers_Have_Shut_Down;


	//UDP
	static const string STUN_Request;
	static const string STUN_Response;


	static const string Friend_Connect_Request;
	static const string Friend_Connect_Response;


	static const string Friend_Data_Request;
	static const string Friend_Data_Response;


	static const string Friend_LocationStatus_Update;


	static const string Game_Connect_Request;
	static const string Game_Connect_Response;

	static const string Game_Challenge_Request;
	static const string Game_Challenge_Response;


	//SERVER TO INDEX
	static const string INDEX_Register_Server_With_INDEX_Request;
	static const string INDEX_Tell_ServerID_To_Tell_UserID_That_UserIDs_Are_Online;
	static const string INDEX_Tell_All_Servers_To_Tell_FacebookIDs_That_UserID_Is_Online;
	static const string INDEX_UserID_Logged_On_This_Server_Log_Them_Off_Other_Servers;


	//INDEX TO SERVER
	static const string Server_Register_Server_With_INDEX_Response;
	static const string Server_Tell_All_FacebookIDs_That_UserID_Is_Online;
	static const string Server_Tell_UserID_That_UserIDs_Are_Online;
	static const string Server_UserID_Logged_On_Other_Server_So_Log_Them_Off;
	static const string Server_Tell_All_Users_Servers_Are_Shutting_Down;
	static const string Server_Tell_All_Users_Servers_Have_Shut_Down;


	//BOBS GAME
	static const string Bobs_Game_GameTypesAndSequences_Download_Request;
	static const string Bobs_Game_GameTypesAndSequences_Download_Response;

	static const string Bobs_Game_GameTypesAndSequences_Upload_Request;
	static const string Bobs_Game_GameTypesAndSequences_Upload_Response;

	static const string Bobs_Game_GameTypesAndSequences_Vote_Request;
	static const string Bobs_Game_GameTypesAndSequences_Vote_Response;

	static const string Bobs_Game_RoomList_Request;
	static const string Bobs_Game_RoomList_Response;
	static const string Bobs_Game_TellRoomHostToAddMyUserID;

	static const string Bobs_Game_HostingPublicRoomUpdate;
	static const string Bobs_Game_HostingPublicRoomStarted;
	static const string Bobs_Game_HostingPublicRoomCanceled;
	static const string Bobs_Game_HostingPublicRoomEnded;

	static const string Bobs_Game_GameStats;


	static const string Bobs_Game_UserStatsForSpecificGameAndDifficulty;
	static const string Bobs_Game_LeaderBoardsByTotalTimePlayed;
	static const string Bobs_Game_LeaderBoardsByTotalBlocksCleared;
	static const string Bobs_Game_LeaderBoardsByPlaneswalkerPoints;
	static const string Bobs_Game_LeaderBoardsByEloScore;
	static const string Bobs_Game_HighScoreBoardsByTimeLasted;
	static const string Bobs_Game_HighScoreBoardsByBlocksCleared;





















};

