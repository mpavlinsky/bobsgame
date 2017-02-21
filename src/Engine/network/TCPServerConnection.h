
#pragma once
#include "bobtypes.h"
#include <src/Engine/EnginePart.h>
#include <src/Utility/ArrayList.h>
class Logger;

class TCPServerConnection
{
public:
	


	static Logger log;

	TCPServerConnection();
	virtual ~TCPServerConnection();

	void update();

	

	bool threadStarted = false;
	thread t;

	string _truncatedPacketString = "";

	//------------------------------------
public:
	static void updateThreadLoop(TCPServerConnection *u);

private:
	void _sendKeepAlivePing();
	void _checkForTimeout();
	void _getInitialGameSave();
	void _checkForIncomingTraffic();

	string partialPacketString = "";
	
	long long _lastLoadBalancerConnectTime = 0;
	bool _couldNotResolveLoadBalancer = false;
	int _couldNotOpenConnectionToLoadBalancerCount = 0;
	IPaddress * _loadBalancerAddress = nullptr;
	
	long long _lastServerConnectTime = 0;
	long long _lastSentServerIPRequestTime = 0;
	int _couldNotOpenConnectionToServerCount = 0;
	long long _lastSentPingTime = 0;

	long long _checkInitialGameSaveReceivedDelayTime = 0;
	
	bool _initialGameSaveReceived_nonThreaded = false;
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

	//------------------------------------
private:
	long long _lastReceivedDataTime = 0;
	mutex _lastReceivedDataTime_Mutex;
public:
	long long getLastReceivedDataTime_S()
	{
		lock_guard<mutex> lock(_lastReceivedDataTime_Mutex);
		return _lastReceivedDataTime;
	}
	void setLastReceivedDataTime_S(long long b)
	{
		lock_guard<mutex> lock(_lastReceivedDataTime_Mutex);
		_lastReceivedDataTime = b;
	}


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
	TCPsocket _socket = TCPsocket();
	mutex _socket_Mutex;
public:
	TCPsocket getSocket_S()
	{
		lock_guard<mutex> lock(_socket_Mutex);
		return _socket;
	}
	void setSocket_S(TCPsocket s)
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
	queue<string> *_incomingMessageQueue = new queue<string>();
	mutex _incomingMessageQueue_Mutex;
public:
	string incomingMessageQueueFront_S()
	{
		lock_guard<mutex> lock(_incomingMessageQueue_Mutex);
		return _incomingMessageQueue->front();
	}
	int incomingMessageQueueSize_S()
	{
		lock_guard<mutex> lock(_incomingMessageQueue_Mutex);
		return (int)_incomingMessageQueue->size();
	}
	void incomingMessageQueuePop_S()
	{
		lock_guard<mutex> lock(_incomingMessageQueue_Mutex);
		_incomingMessageQueue->pop();
	}
	void incomingMessageQueuePush_S(string &p)
	{
		lock_guard<mutex> lock(_incomingMessageQueue_Mutex);
		_incomingMessageQueue->push(p);
	}
	//------------------------------------

private:
	queue<string> _outgoingAuthorizedMessageQueue;
	mutex _outgoingAuthorizedMessageQueue_Mutex;
public:
	string outgoingAuthorizedMessageQueueFront_S()
	{
		lock_guard<mutex> lock(_outgoingAuthorizedMessageQueue_Mutex);
		return _outgoingAuthorizedMessageQueue.front();
	}
	int outgoingAuthorizedMessageQueueSize_S()
	{
		lock_guard<mutex> lock(_outgoingAuthorizedMessageQueue_Mutex);
		return (int)_outgoingAuthorizedMessageQueue.size();
	}
	void outgoingAuthorizedMessageQueuePop_S()
	{
		lock_guard<mutex> lock(_outgoingAuthorizedMessageQueue_Mutex);
		_outgoingAuthorizedMessageQueue.pop();
	}
	void outgoingAuthorizedMessageQueuePush_S(string &p)
	{
		lock_guard<mutex> lock(_outgoingAuthorizedMessageQueue_Mutex);
		_outgoingAuthorizedMessageQueue.push(p);
	}
	//------------------------------------

private:
	bool _connectedToServer = false;
	mutex _connectedToServer_Mutex;
public:
	bool getConnectedToServer_S()
	{
		lock_guard<mutex> lock(_connectedToServer_Mutex);
		return _connectedToServer;
	}
	void setConnectedToServer_S(bool b)
	{
		lock_guard<mutex> lock(_connectedToServer_Mutex);
		_connectedToServer = b;
	}
	//------------------------------------



	IPaddress * _serverAddress = nullptr;
	mutex _serverAddress_Mutex;
	IPaddress* getServerAddress_S()
	{
		lock_guard<mutex> lock(_serverAddress_Mutex);
		return _serverAddress;
	}
	void setServerAddress_S(IPaddress *b)
	{
		lock_guard<mutex> lock(_serverAddress_Mutex);
		_serverAddress = b;
	}
	void deleteServerAddress_S()
	{
		lock_guard<mutex> lock(_serverAddress_Mutex);
		if (_serverAddress != nullptr)
		{
			delete _serverAddress;
			_serverAddress = nullptr;
		}
	}

	//------------------------------------

	string _serverIPAddressString = "";
	mutex _serverIPAddressString_Mutex;
	string getServerIPAddressString_S()
	{
		lock_guard<mutex> lock(_serverIPAddressString_Mutex);
		return _serverIPAddressString;
	}

	void setServerIPAddressString_S(string s)
	{
		lock_guard<mutex> lock(_serverIPAddressString_Mutex);
		if (s == "")
		{
#ifdef _DEBUG
			threadLogDebug_S("Set server address to null");
#endif
			deleteServerAddress_S();
			_serverIPAddressString = "";
		}
		else
		{
			deleteServerAddress_S();

			threadLogDebug_S("Server IP:" + s);

			if (s == "localhost")s = "127.0.0.1";

			_serverIPAddressString = s;
		}

	}
	
	//------------------------------------

	bool messageReceived(string &s);
	bool write_S(string s);
private:
	void incomingServerIPAddressResponse(string s);










	//------------------------------------

	//------------------------------------
	//LOGIN
	//------------------------------------
private:
	bool statsAllowed = false;



	//------------------------------------
private:
	bool _gotLoginResponse_S = false;
	mutex _gotLoginResponse_Mutex;
public:
	void setGotLoginResponse_S(bool b)
	{
		lock_guard<mutex> lock(_gotLoginResponse_Mutex);
		_gotLoginResponse_S = b;
	}
	bool getGotLoginResponse_S()
	{
		lock_guard<mutex> lock(_gotLoginResponse_Mutex);
		return _gotLoginResponse_S;
	}


	//------------------------------------
private:
	bool _loginWasValid_S = false;
	mutex _loginWasValid_Mutex;
public:
	void setLoginResponse_S(bool gotReponse, bool wasValid)
	{
		lock_guard<mutex> lock(_loginWasValid_Mutex);
		setGotLoginResponse_S(gotReponse);
		_loginWasValid_S = wasValid;
	}
	bool getWasLoginResponseValid_S()
	{
		lock_guard<mutex> lock(_loginWasValid_Mutex);
		return _loginWasValid_S;
	}


	//------------------------------------
private:
	bool _gotReconnectResponse_S = false;
	mutex _gotReconnectResponse_Mutex;
public:
	void setGotReconnectResponse_S(bool b)
	{
		lock_guard<mutex> lock(_gotReconnectResponse_Mutex);
		_gotReconnectResponse_S = b;
	}
	bool getGotReconnectResponse_S()
	{
		lock_guard<mutex> lock(_gotReconnectResponse_Mutex);
		return _gotReconnectResponse_S;
	}



	//------------------------------------
private:
	bool _reconnectWasValid_S = false;
	mutex _reconnectWasValid_Mutex;
public:
	void setReconnectResponse_S(bool gotReponse, bool wasValid)
	{
		lock_guard<mutex> lock(_reconnectWasValid_Mutex);
		setGotReconnectResponse_S(gotReponse);
		_reconnectWasValid_S = wasValid;
	}
	bool getWasReconnectResponseValid_S()
	{
		lock_guard<mutex> lock(_reconnectWasValid_Mutex);
		return _reconnectWasValid_S;
	}



	//------------------------------------
private:
	string _sessionToken = "";
	mutex _sessionToken_Mutex;
public:
	void setSessionToken_S(string s)
	{
		lock_guard<mutex> lock(_sessionToken_Mutex);
		_sessionToken = s;
	}
	string getSessionToken_S()
	{
		lock_guard<mutex> lock(_sessionToken_Mutex);
		return _sessionToken;
	}
	//------------------------------------



	//------------------------------------
private:
	string _lastUserNameOrEmail = "";
	mutex _lastUserNameOrEmail_Mutex;
public:
	void setLastUserNameOrEmail_S(string s)
	{
		lock_guard<mutex> lock(_lastUserNameOrEmail_Mutex);
		_lastUserNameOrEmail = s;
	}
	string getLastUserNameOrEmail_S()
	{
		lock_guard<mutex> lock(_lastUserNameOrEmail_Mutex);
		return _lastUserNameOrEmail;
	}
	//------------------------------------

	//------------------------------------
private:
	string _lastPassword = "";
	mutex _lastPassword_Mutex;
public:
	void setLastPassword_S(string s)
	{
		lock_guard<mutex> lock(_lastPassword_Mutex);
		_lastPassword = s;
	}
	string getLastPassword_S()
	{
		lock_guard<mutex> lock(_lastPassword_Mutex);
		return _lastPassword;
	}
	//------------------------------------


	void setNotAuthorizedOnServer_S()
	{//===============================================================================================
		setLoginResponse_S(false, false); //may have to reinitialize if we connect to a different server
		setReconnectResponse_S(false, false);
	}

	bool getAuthorizedOnServer_S()
	{//===============================================================================================
		if (getWasLoginResponseValid_S() == true || getWasReconnectResponseValid_S() == true)
		{
			return true;
		}
		return false;
	}

	void setDisconnectedFromServer_S(string reason);
	bool ensureConnectedToServerThreadBlock_S();
	//bool ensureAuthorizedOnServerThreadBlock_S();
	bool connectAndWriteToChannelBeforeAuthorization_S(string s);
	bool connectAndAuthorizeAndQueueWriteToChannel_S(string s);

	void sendLoginRequest(string email, string password, bool stats);
	void sendReconnectRequest(long long userID, string sessionToken, bool stats);


private:
	void incomingLoginResponse(string s);
	void incomingReconnectResponse(string s);

public:
	void setUserID_S(long long userID)
	{
		GameSave g = getGameSave_S();
		g.userID = userID;
		setGameSave_S(g);
	}
	long long getUserID_S()
	{
		GameSave g = getGameSave_S();
		return g.userID;
	}


private:
	void incomingSessionWasLoggedOnSomewhereElse(string s);
	void incomingServersAreShuttingDown(string s);
	void incomingServersHaveShutDown(string s);





	
	

public:



//	bool gotFacebookLoginResponse_S = false;
//	bool getGotFacebookLoginResponse_S()
//	{
//		return gotFacebookLoginResponse_S;
//	}
//	void setGotFacebookLoginResponse_S(bool b)
//	{
//		gotFacebookLoginResponse_S = b;
//	}
//
//	bool facebookLoginWasValid_S = false;
//	bool getWasFacebookLoginResponseValid_S()
//	{
//		return facebookLoginWasValid_S;
//	}
//	void setFacebookLoginResponse_S(bool gotReponse, bool wasValid)
//	{
//		gotFacebookLoginResponse_S = gotReponse;
//		facebookLoginWasValid_S = wasValid;
//	}

	//void sendFacebookLoginCreateAccountIfNotExist(string facebookID, string accessToken, bool stats);
private:
	//void incomingFacebookCreateAccountOrLoginResponse(string s);



	//------------------------------------
	//CREATE ACCOUNT
	//------------------------------------
public:
	string _gotCreateAccountResponse = "";
	mutex _gotCreateAccountResponse_Mutex;
	void setGotCreateAccountResponse_S(string b)
	{
		lock_guard<mutex> lock(_gotCreateAccountResponse_Mutex);
		_gotCreateAccountResponse = b;
	}
	string getGotCreateAccountResponse_S()
	{
		lock_guard<mutex> lock(_gotCreateAccountResponse_Mutex);
		return _gotCreateAccountResponse;
	}


	virtual void sendCreateAccountRequest(string userName, string email, string password);

private:
	void incomingCreateAccountResponse(string s);



	//------------------------------------
	//PASSWORD RECOVERY
	//------------------------------------
public:
	bool _gotPasswordRecoveryResponse = false;
	mutex _gotPasswordRecoveryResponse_Mutex;
	void setGotPasswordRecoveryResponse_S(bool b)
	{
		lock_guard<mutex> lock(_gotPasswordRecoveryResponse_Mutex);
		_gotPasswordRecoveryResponse = b;
	}
	bool getGotPasswordRecoveryResponse_S()
	{
		lock_guard<mutex> lock(_gotPasswordRecoveryResponse_Mutex);
		return _gotPasswordRecoveryResponse;
	}




	virtual void sendPasswordRecoveryRequest(string email);
private:
	void incomingPasswordRecoveryResponse(string s);




	//------------------------------------
	//GAME SAVE UPDATES
	//------------------------------------
	//INITIAL GAME SAVE
	//------------------------------------
public:
	long long lastInitialGameSaveRequestTime = 0;
	virtual void sendInitialGameSaveRequest();

private:
	void incomingInitialGameSaveResponse(string s);

	//each game save needs to have an ID so we know for sure which one is being replied to.

public:
	class GameSaveUpdateRequest
	{
	public:
		string requestString = "";
		int requestID = -1;
		long long timeLastSent = 0;
		bool sent = false;

		GameSaveUpdateRequest(){}
		GameSaveUpdateRequest(string request, int requestID)
		{ //=========================================================================================================================
			this->requestString = request;
			this->requestID = requestID;
		}


	};

private:
	ArrayList<GameSaveUpdateRequest> _gameSaveUpdateRequestQueue;
	int _requestCounter = 0;
	mutex _gameSaveUpdateRequestQueue_Mutex;
public:
	GameSaveUpdateRequest getQueuedGameSaveUpdateRequest_S(int i)
	{ //=========================================================================================================================
		lock_guard<mutex> lock(_gameSaveUpdateRequestQueue_Mutex);
		int size = _gameSaveUpdateRequestQueue.size();
		if (i >= size)return GameSaveUpdateRequest();
		return _gameSaveUpdateRequestQueue.get(i);
	}
	void addQueuedGameSaveUpdateRequest_S(string value)
	{
		lock_guard<mutex> lock(_gameSaveUpdateRequestQueue_Mutex);
	  //all game save updates should be instantly queued
	  //any changes to the game save should happen instantly on the client
		GameSaveUpdateRequest g = GameSaveUpdateRequest(value, _requestCounter);
		_gameSaveUpdateRequestQueue.add(g);
		_requestCounter++;
	}
	void removeQueuedGameSaveUpdateRequestByID_S(int requestID)
	{
		lock_guard<mutex> lock(_gameSaveUpdateRequestQueue_Mutex);
		int size = _gameSaveUpdateRequestQueue.size();
		for (int i = 0; i < size; i++)
			if (_gameSaveUpdateRequestQueue.get(i).requestID == requestID)
			{
				_gameSaveUpdateRequestQueue.removeAt(i);
				i = size;
				break;
			}
	}




	//------------------------------------
	string _encryptedGameSave = "";
	mutex _encryptedGameSave_Mutex;
	string getEncryptedGameSave_S()
	{
		lock_guard<mutex> lock(_encryptedGameSave_Mutex);
		return _encryptedGameSave;
	}
	void setEncryptedGameSave_S(string s)
	{
		lock_guard<mutex> lock(_encryptedGameSave_Mutex);
		_encryptedGameSave = s;
	}
	virtual void sendQueuedGameSaveUpdates();
private:
	void incomingGameSaveUpdateResponse(string s);
	

	




	
	//------------------------------------
private:
	bool _initialGameSaveRecieved = false;
	mutex _initialGameSaveRecieved_Mutex;
public:
	bool getInitialGameSaveReceived_S()
	{
		lock_guard<mutex> lock(_initialGameSaveRecieved_Mutex);
		return _initialGameSaveRecieved;
	}
	void setInitialGameSaveReceived_S(bool b)
	{
		lock_guard<mutex> lock(_initialGameSaveRecieved_Mutex);
		_initialGameSaveRecieved = b;
	}



	//------------------------------------
private:
	GameSave _gameSave;
	mutex _gameSave_Mutex;
public:
	GameSave getGameSave_S()
	{
		lock_guard<mutex> lock(_gameSave_Mutex);
		return _gameSave;
	}
	void setGameSave_S(GameSave &s)
	{
		lock_guard<mutex> lock(_gameSave_Mutex);
		_gameSave = s;
	}





	//------------------------------------
	//FACEBOOK TRASH
	//------------------------------------
private:
	bool _gotFacebookAccountUpdateResponse = false;
	mutex _gotFacebookAccountUpdateResponse_Mutex;
public:
	void setGotFacebookAccountUpdateResponse_S(bool b)
	{
		lock_guard<mutex> lock(_gotFacebookAccountUpdateResponse_Mutex);
		_gotFacebookAccountUpdateResponse = b;
	}
	bool getFacebookAccountUpdateResponseReceived_S()
	{
		lock_guard<mutex> lock(_gotFacebookAccountUpdateResponse_Mutex);
		return _gotFacebookAccountUpdateResponse;
	}

	//------------------------------------
private:
	bool _facebookAccountUpdateResponseWasValid = false;
	mutex _facebookAccountUpdateResponseWasValid_Mutex;
public:
	void setFacebookAccountUpdateResponseWasValid_S(bool b)
	{
		lock_guard<mutex> lock(_facebookAccountUpdateResponseWasValid_Mutex);
		_facebookAccountUpdateResponseWasValid = b;
	}
	bool getFacebookAccountUpdateResponseWasValid_S()
	{
		lock_guard<mutex> lock(_facebookAccountUpdateResponseWasValid_Mutex);
		return _facebookAccountUpdateResponseWasValid;
	}
	void setFacebookAccountUpdateResponseState_S(bool gotResponse, bool wasValid)
	{
		setGotFacebookAccountUpdateResponse_S(gotResponse);
		_facebookAccountUpdateResponseWasValid = wasValid;
	}
	//------------------------------------
	void sendUpdateFacebookAccountInDBRequest_S();
private:
	void incomingUpdateFacebookAccountInDBResponse(string s);



public:
	void sendOnlineFriendListRequest_S();


	void sendBobsGameGameTypesAndSequencesDownloadRequest_S();
	void incomingBobsGameGameTypesAndSequencesDownloadResponse(string &s);
	void incomingBobsGameGameTypesAndSequencesUploadResponse(string &s);
	void incomingBobsGameGameTypesAndSequencesVoteResponse(string &s);
	//------------------------------------
	private:
		bool _gotBobsGameGameTypesAndSequencesDownloadResponse = false;
		mutex _gotBobsGameGameTypesAndSequencesDownloadResponse_Mutex;
public:
	void setGotBobsGameGameTypesAndSequencesDownloadResponse_S(bool b)
	{
		lock_guard<mutex> lock(_gotBobsGameGameTypesAndSequencesDownloadResponse_Mutex);
		_gotBobsGameGameTypesAndSequencesDownloadResponse = b;
	}
	bool getAndResetBobsGameGameTypesAndSequencesDownloadResponseReceived_S()
	{
		lock_guard<mutex> lock(_gotBobsGameGameTypesAndSequencesDownloadResponse_Mutex);
		bool temp = _gotBobsGameGameTypesAndSequencesDownloadResponse;
		_gotBobsGameGameTypesAndSequencesDownloadResponse = false;
		return temp;
	}
	//------------------------------------
	//------------------------------------
	private:
		string _gotBobsGameGameTypesAndSequencesUploadResponse = "";
		mutex _gotBobsGameGameTypesAndSequencesUploadResponse_Mutex;
public:
	void setGotBobsGameGameTypesAndSequencesUploadResponse_S(string s)
	{
		lock_guard<mutex> lock(_gotBobsGameGameTypesAndSequencesUploadResponse_Mutex);
		_gotBobsGameGameTypesAndSequencesUploadResponse = s;
	}
	string getAndResetBobsGameGameTypesAndSequencesUploadResponse_S()
	{
		lock_guard<mutex> lock(_gotBobsGameGameTypesAndSequencesUploadResponse_Mutex);
		string s = _gotBobsGameGameTypesAndSequencesUploadResponse;
		_gotBobsGameGameTypesAndSequencesUploadResponse = "";
		return s;
	}
	//------------------------------------
	private:
		string _gotBobsGameGameTypesAndSequencesVoteResponse = "";
		mutex _gotBobsGameGameTypesAndSequencesVoteResponse_Mutex;
public:
	void setGotBobsGameGameTypesAndSequencesVoteResponse_S(string s)
	{
		lock_guard<mutex> lock(_gotBobsGameGameTypesAndSequencesVoteResponse_Mutex);
		_gotBobsGameGameTypesAndSequencesVoteResponse = s;
	}
	string getAndResetBobsGameGameTypesAndSequencesVoteResponse_S()
	{
		lock_guard<mutex> lock(_gotBobsGameGameTypesAndSequencesVoteResponse_Mutex);
		string s = _gotBobsGameGameTypesAndSequencesVoteResponse;
		_gotBobsGameGameTypesAndSequencesVoteResponse = "";
		return s;
	}
	//------------------------------------



	void sendBobsGameRoomListRequest_S();
	void incomingBobsGameRoomListResponse(string &s);
	void tellBobsGameRoomHostMyUserID_S(string roomUUID);
	void tellServerBobsGameHostingPublicGameUpdate_S(string roomDescription);
	void tellServerBobsGameIHaveCanceledTheGame_S(string roomUUID);
	void tellServerBobsGameIHaveStartedTheGame_S(string roomUUID);
	void tellServerBobsGameTheGameHasEnded_S(string roomUUID, string results);
	void sendBobsGameGameStats_S(string &statsString);
	void incomingBobsGameUserStatsForSpecificGameAndDifficulty(string &s);
	void incomingBobsGameLeaderBoardByTotalTimePlayed(string &s);
	void incomingBobsGameLeaderBoardByTotalBlocksCleared(string &s);
	void incomingBobsGameLeaderBoardByPlaneswalkerPoints(string &s);
	void incomingBobsGameLeaderBoardByEloScore(string &s);
	void incomingBobsGameHighScoreBoardsByTimeLasted(string &s);
	void incomingBobsGameHighScoreBoardsByBlocksCleared(string &s);
	//------------------------------------
	private:
		string _bobsGameRoomListResponse = "";
		mutex _bobsGameRoomListResponse_Mutex;
public:
	void setBobsGameRoomListResponse_S(string s)
	{
		lock_guard<mutex> lock(_bobsGameRoomListResponse_Mutex);
		_bobsGameRoomListResponse = s;
	}
	string getAndResetBobsGameRoomListResponse_S()
	{
		lock_guard<mutex> lock(_bobsGameRoomListResponse_Mutex);
		string s = _bobsGameRoomListResponse;
		_bobsGameRoomListResponse = "";
		return s;
	}
	//------------------------------------
	


private:
	void incomingOnlineFriendsListResponse(string s);
	void incomingFriendOnlineNotification(string s);

public:
	void sendAddFriendByUserNameRequest_S(string friendUserName);
	void incomingAddFriendByUserNameResponse(string s);
	string getAddFriendByUserNameResponse();
	void setAddFriendByUserNameResponse(string b);
	string addFriendByUserNameResponse = "";


	bool _doLoginNoCaptions(string &userNameOrEmail, string &password, bool stayLoggedIn);
	bool doLogin(Caption *statusLabel, Caption *errorLabel, string &userNameOrEmail, string &password, bool stayLoggedIn);
	bool doCreateAccount(Caption *statusLabel, Caption *errorLabel, string &userName, string &email, string &password, string &confirmPassword);
	bool checkForSessionTokenAndLogInIfExists();
	bool doForgotPassword(Caption *statusLabel, Caption *errorLabel, string &userNameOrEmail);
	bool linkFacebookAccount(Caption *statusLabel, Caption *errorLabel);
	bool doAddFriendByUsername(Caption *statusLabel, Caption *errorLabel, string &friendUserName);
};