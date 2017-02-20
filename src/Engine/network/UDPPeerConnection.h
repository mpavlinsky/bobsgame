//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include <src/Engine/rpg/FriendCharacter.h>
#include "BobNet.h"
#include <src/Engine/EnginePart.h>
#include <queue>
#include <mutex>
class Logger;



class FriendData
{
public:
	static Logger log;
	int friendType = 0;

	string userName = "";
	string characterName = "???";
	string characterAppearance = "";
	int accountRank = 0;

	long long accountCreatedTime = 0;
	int timesLoggedIn = 0;
	long long totalTimePlayed = 0;
	string postalCode = "";
	string countryName = "";
	string isoCountryCode = "";
	string placeName = "";
	string stateName = "";
	float lat = 0;
	float lon = 0;

	int miniGamesTimesPlayed = 0;
	int miniGamesTimesBattled = 0;
	int miniGamesTimesChallenged = 0;
	int miniGamesTimesChallenger = 0;
	int miniGamesTimesWon = 0;
	int miniGamesTimesLost = 0;
	int miniGamesTimesTied = 0;


	string facebookID = "";
	string facebookEmail = "";
	//string facebookBirthday = "";
	string facebookFirstName = "";
	string facebookLastName = "";
	string facebookGender = "";
	//string facebookLocale = "";
	//float facebookTimeZone = 0.0f;
	//string facebookUsername = "";
	//string facebookWebsite = "";
	//string googlePlusID = "";


	void initWithGameSave(GameSave &g);

	string encode(int friendType);

	void decode(string s);

};




class UDPPeerConnection
{
//private:
//	typedef EnginePart super;
public:

	static Logger log;
	

	UDPPeerConnection(long long friendUserID, int type);
	~UDPPeerConnection();


	void setDisconnectedFromPeer_S(string reason);
	bool udpPeerMessageReceived(string e);
	void writeUnreliable_S(string s);
	bool writeReliable_S(string s);

	long long peerUserID = -1;
	int peerType = -1;
	int peerStatus = BobNet::status_AVAILABLE;// TODO need to send current status, away, busy, private, do not disturb, playing nD game, etc.


	static const int FACEBOOK_TYPE = 0;
	static const int USERNAME_TYPE = 1;
	static const int EMAIL_TYPE = 2;
	static const int ZIP_TYPE = 3;
	static const int ANON_TYPE = 4;

	void update();
	


private:
	static int lastUsedUDPPort;
	int localUDPPort = -1;

	string partialPacketString = "";

	//------------------------------------
	//threading
	//------------------------------------

	bool threadStarted = false;
	thread t;
public:
	static void updateThreadLoop(UDPPeerConnection *u);
	//------------------------------------
private:
	static Logger* _threadLog;
	mutex threadLog_Mutex;
public:
	void threadLogDebug_S(string s)
	{
		lock_guard<mutex> lock(threadLog_Mutex);
		_threadLog->debug(s);
	}
	void threadLogWarn_S(string s)
	{
		lock_guard<mutex> lock(threadLog_Mutex);
		_threadLog->warn(s);
	}
	void threadLogInfo_S(string s)
	{
		lock_guard<mutex> lock(threadLog_Mutex);
		_threadLog->info(s);
	}
	void threadLogError_S(string s)
	{
		lock_guard<mutex> lock(threadLog_Mutex);
		_threadLog->error(s);
	}
	//------------------------------------
private:
	long long _packetCounter = 0;
	mutex _packetCounter_Mutex;
public:
	long long getPacketCounter_S()
	{
		lock_guard<mutex> lock(_packetCounter_Mutex);
		return _packetCounter;
	}
	void packetCounterIncrement_S()
	{
		lock_guard<mutex> lock(_packetCounter_Mutex);
		_packetCounter++;
	}

	//------------------------------------
private:
	UDPsocket _socket = UDPsocket();
	mutex _socket_Mutex;
public:
	UDPsocket getSocket_S()
	{
		lock_guard<mutex> lock(_socket_Mutex);
		return _socket;
	}
	void setSocket_S(UDPsocket s)
	{
		lock_guard<mutex> lock(_socket_Mutex);
		_socket = s;
	}

	//------------------------------------
private:
	SDLNet_SocketSet _socketSet = SDLNet_AllocSocketSet(1);
	mutex _socketSet_Mutex;
public:
	SDLNet_SocketSet getSocketSet_S()
	{
		lock_guard<mutex> lock(_socketSet_Mutex);
		return _socketSet;
	}
	void setSocketSet_S(SDLNet_SocketSet s)
	{
		lock_guard<mutex> lock(_socketSet_Mutex);
		_socketSet = s;
	}

	//------------------------------------
private:
	bool _socketAddedToSet = false;
	mutex _socketAddedToSet_Mutex;
public:
	bool getSocketAddedToSet_S()
	{
		lock_guard<mutex> lock(_socketAddedToSet_Mutex);
		return _socketAddedToSet;
	}
	void setSocketAddedToSet_S(bool s)
	{
		lock_guard<mutex> lock(_socketAddedToSet_Mutex);
		_socketAddedToSet = s;
	}
	//------------------------------------
private:
	bool _socketIsOpen = false;
	mutex _socketIsOpen_Mutex;
public:
	bool getSocketIsOpen_S()
	{
		lock_guard<mutex> lock(_socketIsOpen_Mutex);
		return _socketIsOpen;
	}
	void setSocketIsOpen_S(bool s)
	{
		lock_guard<mutex> lock(_socketIsOpen_Mutex);
		_socketIsOpen = s;
	}

	//------------------------------------
private:
	IPaddress* _peerIPAddress_S = nullptr;
	int _peerPort_S = -1;
	mutex _peerIPAddress_Mutex;
public:
	IPaddress* getPeerIPAddress_S()
	{
		lock_guard<mutex> lock(_peerIPAddress_Mutex);
		return _peerIPAddress_S;
	}
	void setPeerIPAddress_S(string ipAddressString, int port)
	{

		lock_guard<mutex> lock(_peerIPAddress_Mutex);

		if (ipAddressString == "")
		{
#ifdef _DEBUG
			threadLogDebug_S("Set peer address to null");
#endif
			if (_peerIPAddress_S != nullptr)
			{
				delete _peerIPAddress_S;
				_peerIPAddress_S = nullptr;
			}
			_peerPort_S = port;
		}
		else
		{
			_peerIPAddress_S = new IPaddress();
			_peerPort_S = port;

			if (SDLNet_ResolveHost(_peerIPAddress_S, ipAddressString.c_str(), port) < 0)
			{
				threadLogWarn_S("Could not resolve peer host: " + string(SDLNet_GetError()));
				SDL_ClearError();
			}

			threadLogDebug_S("Set peer address to " + ipAddressString + ":" + to_string(port));
			//threadLogDebug_S("Internal address looks like " + to_string(_peerIPAddress_S->host) + ":" + to_string(_peerIPAddress_S->port));
		}
	}
	//------------------------------------

private:
	queue<string> *_packetMessageQueue = new queue<string>();
	mutex _packetMessageQueue_Mutex;
public:
	string packetMessageQueueFront_S()
	{
		lock_guard<mutex> lock(_packetMessageQueue_Mutex);
		return _packetMessageQueue->front();
	}
	int packetMessageQueueSize_S()
	{
		lock_guard<mutex> lock(_packetMessageQueue_Mutex);
		return (int)_packetMessageQueue->size();
	}
	void packetMessageQueuePop_S()
	{
		lock_guard<mutex> lock(_packetMessageQueue_Mutex);
		_packetMessageQueue->pop();
	}
	void packetMessageQueuePush_S(string p)
	{
		lock_guard<mutex> lock(_packetMessageQueue_Mutex);
		_packetMessageQueue->push(p);
	}

	//------------------------------------

private:
	queue<UDPpacket*> *_sentPacketQueue = new queue<UDPpacket*>();
	mutex _sentPacketQueue_Mutex;
public:
	UDPpacket* sentPacketQueueFront_S()
	{
		lock_guard<mutex> lock(_sentPacketQueue_Mutex);
		return _sentPacketQueue->front();
	}
	int sentPacketQueueSize_S()
	{
		lock_guard<mutex> lock(_sentPacketQueue_Mutex);
		return (int)_sentPacketQueue->size();
	}
	void sentPacketQueuePop_S()
	{
		lock_guard<mutex> lock(_sentPacketQueue_Mutex);
		_sentPacketQueue->pop();
	}
	void sentPacketQueuePush_S(UDPpacket* p)
	{
		lock_guard<mutex> lock(_sentPacketQueue_Mutex);
		_sentPacketQueue->push(p);
	}
	//------------------------------------

private:
	queue<string> *_unjoinedMessageQueue = new queue<string>();
	mutex _unjoinedMessageQueue_Mutex;
public:
	string unjoinedMessageQueueFront_S()
	{
		lock_guard<mutex> lock(_unjoinedMessageQueue_Mutex);
		return _unjoinedMessageQueue->front();
	}
	int unjoinedMessageQueueSize_S()
	{
		lock_guard<mutex> lock(_unjoinedMessageQueue_Mutex);
		return (int)_unjoinedMessageQueue->size();
	}
	void unjoinedMessageQueuePop_S()
	{
		lock_guard<mutex> lock(_unjoinedMessageQueue_Mutex);
		_unjoinedMessageQueue->pop();
	}
	void unjoinedMessageQueuePush_S(string p)
	{
		lock_guard<mutex> lock(_unjoinedMessageQueue_Mutex);
		_unjoinedMessageQueue->push(p);
	}
	//------------------------------------
private:
	long long _averageRoundaboutTicks = 100;
	mutex _averageRoundaboutTicks_Mutex;
public:
	long long getAverageRoundaboutTicks_S()
	{
		lock_guard<mutex> lock(_averageRoundaboutTicks_Mutex);
		return _averageRoundaboutTicks;
	}
	void setAverageRoundaboutTicks_S(long long s)
	{
		lock_guard<mutex> lock(_averageRoundaboutTicks_Mutex);
		_averageRoundaboutTicks = s;
	}

	//------------------------------------
private:
	bool _connectedToPeer = false;
	mutex _connectedToPeer_Mutex;
public:
	bool getConnectedToPeer_S()
	{
		lock_guard<mutex> lock(_connectedToPeer_Mutex);
		return _connectedToPeer;
	}

	void setConnectedToPeer_S(bool b)
	{
		lock_guard<mutex> lock(_connectedToPeer_Mutex);
		_connectedToPeer = b;
	}


	//------------------------------------
private:
	bool _gotPeerConnectResponse = false;
	mutex gotPeerConnectResponse_Mutex;
public:
	bool getGotPeerConnectResponse_S()
	{
		lock_guard<mutex> lock(gotPeerConnectResponse_Mutex);
		return _gotPeerConnectResponse;
	}

	void setGotPeerConnectResponse_S(bool b)
	{
		lock_guard<mutex> lock(gotPeerConnectResponse_Mutex);
		_gotPeerConnectResponse = b;
	}

	//------------------------------------

private:
	queue<string> _peerMessageQueue;
	mutex _peerMessageQueue_Mutex;
public:
	string peerMessageQueueFront_S()
	{
		lock_guard<mutex> lock(_peerMessageQueue_Mutex);
		return _peerMessageQueue.front();
	}
	int peerMessageQueueSize_S()
	{
		lock_guard<mutex> lock(_peerMessageQueue_Mutex);
		return (int)_peerMessageQueue.size();
	}
	void peerMessageQueuePop_S()
	{
		lock_guard<mutex> lock(_peerMessageQueue_Mutex);
		_peerMessageQueue.pop();
	}
	void peerMessageQueuePush_S(string &p)
	{
		lock_guard<mutex> lock(_peerMessageQueue_Mutex);
		_peerMessageQueue.push(p);
	}

	//------------------------------------

private:
	FriendData _friendData;
	mutex _friendData_Mutex;
public:
	FriendData getFriendData_S()
	{
		lock_guard<mutex> lock(_friendData_Mutex);
		return _friendData;
	}
	void setFriendData_S(FriendData f)
	{
		lock_guard<mutex> lock(_friendData_Mutex);
		_friendData = f;
	}

	//------------------------------------

private:
	string _userName = "";
	public:
	string getUserName()
	{
		if(_userName=="")
		{
			if(getGotFriendData_S()==false)
			{
				return "";
			}
			else
			{
				_userName = getFriendData_S().userName;
			}
		}
		return _userName;
	}

	//------------------------------------

private:
	bool _gotFriendData = false;
	mutex _getGotFriendData_Mutex;
public:
	bool getGotFriendData_S()
	{
		lock_guard<mutex> lock(_getGotFriendData_Mutex);
		return _gotFriendData;
	}
	void setGotFriendData_S(bool b)
	{
		lock_guard<mutex> lock(_getGotFriendData_Mutex);
		_gotFriendData = b;
	}
	//------------------------------------
private:
	bool _stopThread = false;
	mutex _stopThread_Mutex;
public:
	bool getStopThread_S()
	{
		lock_guard<mutex> lock(_stopThread_Mutex);
		return _stopThread;
	}
	void setStopThread_S(bool b)
	{
		lock_guard<mutex> lock(_stopThread_Mutex);
		_stopThread = b;
	}
private:
	//------------------------------------
	//thread only variables
	//------------------------------------
	long long _lastQueuedPacketTime = 0;
	long long _lastWrotePacketTime = 0;
	long long _writePacketWait = 0;
	long long _lastConnectAttemptTime = 0;
	int _connectTries = 0;
	long long _lastSentPingTime = 0;
	long long _lastSentFriendDataRequestTime = 0;
	bool _gotFriendData_NonThreaded = false;
	long long _lastReceivedDataTime = 0;
	long long _lastPacketIDReceived = -1;

	string _truncatedPacketString = "";

	class FrameTimes
	{
	public:
		long long timeSentPacket = 0;
		long long timeGotACK = 0;
	};
	typedef HashMap<long long, long long> HashMapLongLongLongLong;
	HashMapLongLongLongLong *_frameSentTimes = new HashMapLongLongLongLong();
	ArrayList<long long> *_frameRoundaboutTicks = new ArrayList<long long>();
	//------------------------------------
	//thread only functions
	//------------------------------------
	bool _ensureSocketIsOpen();
	void _checkForIncomingPeerTraffic();
	UDPpacket* makePacket(string s);
	void _processQueuedMessagesIntoPackets();
	void _writeQueuedPackets();
	void _getAddressFromSTUNServer();
	void _sendKeepAlivePing();
	void _checkForTimeout();
	void _getFriendData();


	//------------------------------------
	//non-threaded
	//------------------------------------

	void incomingPeerConnectResponse(string e);
	void sendPeerConnectResponse();
	void incomingFriendDataRequest(string e);
	void incomingFriendDataResponse(string e);

public:

	//int bobsGamePlayers = 0;
	//bool bobsGameHosting = false;
	//bool bobsGamePlaying = false;
	//string hostedRoomUUID = "";
	//Caption *caption = nullptr;
	//bool multiplayer_AllowDifferentDifficulties = true;
	//bool multiplayer_AllowDifferentGameSequences = true;
	//bool multiplayer_GameEndsWhenOnePlayerRemains = true;
	//bool multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = true;
	//bool multiplayer_DisableVSGarbage = false;
	//GameSequence *multiplayer_SelectedGameSequence = nullptr;
	//string multiplayer_SelectedDifficultyName = "Beginner";


	//engine parts to forward udp messages to, they also get forwarded to engines which dispatch them
	ArrayList<EnginePart*> engineParts;
	void addEnginePartToForwardMessagesTo(EnginePart* e);
	void removeEnginePartToForwardMessagesTo(EnginePart* e);

	static TCPServerConnection* getServerConnection();

};