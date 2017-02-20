#include "stdafx.h"
#include <thread>
#include <mutex>

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


Logger FriendData::log = Logger("FriendData");
Logger UDPPeerConnection::log = Logger("UDPPeerConnection");
Logger* UDPPeerConnection::_threadLog = new Logger("UDPPeerConnection");



int UDPPeerConnection::lastUsedUDPPort = BobNet::clientUDPPortStartRange;



UDPPeerConnection::UDPPeerConnection(long long friendUserID, int type)
{ //===============================================================================================
	lastUsedUDPPort++;
	this->localUDPPort = lastUsedUDPPort - 1;
	this->peerUserID = friendUserID;
	this->peerType = type;

	//   log.info(string("UDP Channel: ") + channel->getId()->toString());

}

UDPPeerConnection::~UDPPeerConnection()
{
	if(threadStarted)
	{
		setStopThread_S(true);
		t.join();
	}

}

void UDPPeerConnection::addEnginePartToForwardMessagesTo(EnginePart* e)
{
	if (engineParts.contains(e) == false)
		engineParts.add(e);
}

void UDPPeerConnection::removeEnginePartToForwardMessagesTo(EnginePart* e)
{
	if (engineParts.contains(e) == true)
		engineParts.remove(e);
}



void UDPPeerConnection::update()
{ //===============================================================================================

	if (threadStarted == false)
	{
		log.debug("Created peer thread");
		t = thread(&UDPPeerConnection::updateThreadLoop, this);
		threadStarted = true;
	}



	//handle incoming messages queue which is populated from the thread
	while(peerMessageQueueSize_S()>0)
	{
		string s = peerMessageQueueFront_S();
		peerMessageQueuePop_S();


		if (String::startsWith(s, "PARTIAL:"))
		{
			s = s.substr(s.find(":") + 1);
			partialPacketString += s;
		}
		else
			if (String::startsWith(s, "FINAL:"))
			{
				s = s.substr(s.find(":") + 1);
				partialPacketString += s;
				udpPeerMessageReceived(partialPacketString);
				partialPacketString = "";
			}
			else
				if (partialPacketString.length()>0)
				{
					log.error("Partial packet from client was not completed! Client:"+to_string(peerUserID));
				}
				else
				{
					udpPeerMessageReceived(s);
				}

		
	}

}

void UDPPeerConnection::updateThreadLoop(UDPPeerConnection *u)
{//===============================================================================================

	//threadLogDebug_S("Starting peer thread");
	while (u->getStopThread_S()==false)
	{

		this_thread::sleep_for(chrono::milliseconds(10));
		//SDL_Delay(10);

		u->_checkForIncomingPeerTraffic();

		u->_processQueuedMessagesIntoPackets();

		u->_writeQueuedPackets();

		u->_getAddressFromSTUNServer();

		if (u->getConnectedToPeer_S() == true)
		{
			//threadLogDebug_S("Connected to peer");
			//-----------------------------
			//connection is established!
			//-----------------------------

			u->_sendKeepAlivePing();

			u->_checkForTimeout();

			u->_getFriendData();

			//ON SERVER
			//get from DB friends online by social ID
			//send list of friendUserIDs to client

			//tell other servers to alert friends we are online (and our userid)
			//go through connections, match friend userID in sessionHashtable, tell them we are online
			//TODO: could store which server they are connected to in ElasticCache so no messing around, could store channel ID in ElasticCache too so no lookups.

			//for each friend, client makes a udp connection
			//makes request to stun server
			//stun server replies with udp with friends IP/port


			//client pings other clients, vice versa, open tunnel
			//connections made

			//the stun server holds onto requests for a minute and then deletes them
			//if the stun server replies with their ip/udp port, start sending packets on the same udp connection to that ip/port.
			//if we receive a packet from the friends, the connection is established.


			//TODO: server should send TCP friend offline, remove this from friendManager

		}
	}
}


//===============================================================================================
bool UDPPeerConnection::_ensureSocketIsOpen()
{//===============================================================================================
	if (getPeerIPAddress_S() == nullptr)
	{
		return false;
	}
	bool somethingFailed = false;
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

		setSocket_S(SDLNet_UDP_Open(localUDPPort));

		threadLogDebug_S("Opened socket to peer on port " + to_string(localUDPPort));
		if (!getSocket_S())
		{
			//SDLNet_FreeSocketSet(set);
			threadLogError_S("Could not open socket to peer: " + string(SDLNet_GetError()) + string(SDL_GetError()));
			SDL_ClearError();
			somethingFailed = true;
		}
		else
		{
			if (getSocketAddedToSet_S() == false)
			{
				if (SDLNet_UDP_AddSocket(getSocketSet_S(), getSocket_S()) < 0)
				{
					threadLogDebug_S("SDLNet_UDP_AddSocket: " + string(SDLNet_GetError()) + string(SDL_GetError()));
					SDL_ClearError();
					somethingFailed = true;
				}
				else
					setSocketAddedToSet_S(true);
			}

			//SDLNet_UDP_SetPacketLoss(getSocket_S(), 20);

			int channel = SDLNet_UDP_Bind(getSocket_S(), -1, getPeerIPAddress_S());
			if (channel < 0)
			{
				threadLogError_S("Could not bind socket: " + string(SDLNet_GetError()) + string(SDL_GetError()));
				somethingFailed = true;
			}
		}

		if (somethingFailed == false)
		{
			setSocketIsOpen_S(true);
		}
	}

	if (somethingFailed)return false;
	return true;
}


//===============================================================================================
void UDPPeerConnection::_checkForIncomingPeerTraffic()
{//===============================================================================================
	if (_ensureSocketIsOpen())
	{

		int numReady = SDLNet_CheckSockets(getSocketSet_S(), 0);
		if (numReady < 0)
		{
			threadLogDebug_S("SDLNet_CheckSockets: " + string(SDLNet_GetError()) + string(SDL_GetError()));
			SDL_ClearError();
		}


		int numPacketsReceived = 1;
		if (numReady > 0)
		{
			int rd = SDLNet_SocketReady(getSocket_S());

			if (rd > 0)
			{

				queue<string*> packetsToProcess;

				while (numPacketsReceived > 0)
				{
					UDPpacket *packet = SDLNet_AllocPacket(65535);
					numPacketsReceived = SDLNet_UDP_Recv(getSocket_S(), packet);

					if (numPacketsReceived > 0)
					{
						//this doesn't work for some reason, don't uncomment it!!!
//#ifndef _DEBUG
//						if (packet->address.host != getPeerIPAddress_S()->host)
//						{
//							log.warn("Peer address didn't match in incoming packet. Peer IP:" + to_string(getPeerIPAddress_S()->host) + " Packet IP:" + to_string(packet->address.host));
//							break;
//						}
//#endif

						string* packetData = new string((char*)packet->data, packet->len);
						SDLNet_FreePacket(packet);

						packetsToProcess.push(packetData);
						
					}
					else if (numPacketsReceived < 0)
					{
						SDLNet_FreePacket(packet);

						//connection lost
						setDisconnectedFromPeer_S("Error receiving data.");
					}
					else
						SDLNet_FreePacket(packet);
				}

				if (packetsToProcess.size() > 0)
				{
					_lastReceivedDataTime = System::currentHighResTimer();
				}

				while (packetsToProcess.size() > 0)
				{
					string *sp = packetsToProcess.front();
					packetsToProcess.pop();
					string &s = *sp;

					if (_truncatedPacketString != "")
					{
						string *temp = new string(_truncatedPacketString + *sp);
						delete sp;
						sp = temp;
						s = *sp;
						_truncatedPacketString = "";
					}


					if (s.find(BobNet::endline) == string::npos)
					{
						threadLogWarn_S("Packet doesn't contain endline, waiting for next packet to append to.");
						_truncatedPacketString += s;
					}
					else
					{

						if (String::startsWith(s, "ping"))
						{
							if (getPeerIPAddress_S() != nullptr)
							{
								writeUnreliable_S(string("pong") + BobNet::endline);
							}
							else
							{
								threadLogWarn_S("peerAddress was null, but got ping.");
							}
							delete sp;
							continue;
						}

						if (String::startsWith(s, "pong"))
						{
							delete sp;
							continue;
						}

						//if starts with ACK, compare id to front of queue, remove, SDL_FreePacket
						//set lastSentPacketTime to currentTime if we remove a packet from hashmap
						if (String::startsWith(s, "ACK:"))
						{
							string ackPacketIDString = s.substr(s.find(":") + 1);
							long long ackPacketID = -1;
							try
							{
								ackPacketID = stoll(ackPacketIDString);
							}
							catch (exception)
							{
								threadLogError_S("Could not parse ACK packet ID");
								delete sp;
								continue;
							}

							if (sentPacketQueueSize_S() > 0)
							{
								UDPpacket *q = sentPacketQueueFront_S();
								string queuedIDString = string((char*)q->data);
								queuedIDString = queuedIDString.substr(0, queuedIDString.find(":"));
								long long queuedID = -1;
								try
								{
									queuedID = stoll(queuedIDString);
								}
								catch (exception)
								{
									threadLogError_S("Could not parse queued packet ID");
									delete sp;
									continue;
								}
								if (queuedID == ackPacketID)
								{
									//gotACK = true;
									sentPacketQueuePop_S();
									SDLNet_FreePacket(q);
									//lastSentPacketTime = System::currentHighResTimer();

									if (_frameSentTimes->containsKey(queuedID))
									{
										long long timeSentPacket = _frameSentTimes->get(queuedID);
										_frameSentTimes->removeAt(queuedID);

										long long roundaboutTicks = (long long)System::getTicksBetweenTimes(timeSentPacket, System::currentHighResTimer());
										_frameRoundaboutTicks->add(roundaboutTicks);

										long long totalRoundaboutTicks = 0;
										for (int i = 0; i < _frameRoundaboutTicks->size(); i++)
										{
											totalRoundaboutTicks += _frameRoundaboutTicks->get(i);
										}
										setAverageRoundaboutTicks_S(totalRoundaboutTicks / _frameRoundaboutTicks->size());
									}
								}
								else
								{
									threadLogError_S("Got ACK for packet ID which is not the last packet sent.  Last sent packet ID:" + to_string(queuedID) + " ACK packet ID:" + to_string(ackPacketID));
								}
							}
							delete sp;
							continue;
						}


						//if starts with id, send ACK without queueing, went to udpPeerMessageReceived
						string packetIDString = s.substr(0, s.find(":"));
						s = s.substr(s.find(":") + 1);
						long long packetID = -1;
						try
						{
							packetID = stoll(packetIDString);
						}
						catch (exception)
						{
							threadLogError_S("Could not parse incoming packet ID");
							delete sp;
							continue;
						}

						//send ACK
						writeUnreliable_S("ACK:" + to_string(packetID) + BobNet::endline);

						if (packetID < _lastPacketIDReceived)//don't process packets multiple times
						{
							if(packetID < 10 && _lastPacketIDReceived > 10)
							{
								threadLogError_S("Received packet with ID less than 10 but last packet ID received was greater than 10.  Client probably restarted, resetting lastPacketID to this packet ID.  Last packet ID:" + to_string(_lastPacketIDReceived) + " This packet ID:" + to_string(packetID));
							}
							else
							{
								threadLogError_S("Received packet with ID less than already processed, peer probably didn't get ACK in time. Last packet ID:" + to_string(_lastPacketIDReceived) + " This packet ID:" + to_string(packetID));
								delete sp;
								continue;
							}
						}

						if (packetID == _lastPacketIDReceived)
						{
							threadLogError_S("Received save packet twice, peer probably didn't get ACK in time. Last packet ID:" + to_string(_lastPacketIDReceived) + " This packet ID:" + to_string(packetID));

							delete sp;
							continue;
						}

						if (packetID - 1 > _lastPacketIDReceived)
						{
							threadLogError_S("Received packet with ID greater than last packet ID + 1, missed a packet? Last packet ID:" + to_string(_lastPacketIDReceived) + " This packet ID:" + to_string(packetID));
							delete sp;
							continue;
						}

						//packets should always be in order because they are popped from queue on ACK
						_lastPacketIDReceived = packetID;

						//process the packet into messages
						while (s.find(BobNet::endline) != string::npos)
						{

							//strip off message
							string message = s.substr(0, s.find(BobNet::endline));
							//skip endline
							s = s.substr(s.find(BobNet::endline) + BobNet::endline.length());

							peerMessageQueuePush_S(message);

						}

						if(s.length()>0)
						{
							_truncatedPacketString += s;
						}
					}

					delete sp;
				}
			}
			else
				if (rd < 0)
				{
					threadLogError_S("SDLNet_SocketReady Error: " + string(SDLNet_GetError()) + string(SDL_GetError()));
					SDL_ClearError();

					setDisconnectedFromPeer_S("Error receiving data.");
				}
		}
	}
}

//===============================================================================================
UDPpacket* UDPPeerConnection::makePacket(string s)
{//===============================================================================================

	IPaddress* peerAddress = getPeerIPAddress_S();
	if (peerAddress == nullptr)
	{
		threadLogWarn_S("peerAddress was null.");
		return nullptr;
	}

	UDPpacket * packet = SDLNet_AllocPacket((int)s.length());
	packet->channel = -1;
	packet->address = *peerAddress;
	for (int i = 0; i < (int)s.length(); i++)
	{
		packet->data[i] = s[i];
	}
	packet->len = (int)s.length();
	//SDLNet_FreePacket(packet);

	//packet gets freed when ack received

	return packet;

}



//===============================================================================================
void UDPPeerConnection::_processQueuedMessagesIntoPackets()
{//===============================================================================================

	if (unjoinedMessageQueueSize_S() == 0)return;

	bool debug = false;
#ifdef _DEBUG
	debug = true;
#endif

	long long currentTime = System::currentHighResTimer();
	long long startTime = _lastQueuedPacketTime;
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	//TODO: get roundabout time from packet to ack and set this to maybe half that
	//it's possible that the packet queue will get huge and the network traffic will never send quickly enough so i need to do some thinking about this

	if (ticksPassed > getAverageRoundaboutTicks_S())
	{
		_lastQueuedPacketTime = currentTime;
		string s = unjoinedMessageQueueFront_S();
		unjoinedMessageQueuePop_S();

		//split messages more than 1400 bytes
		if (s.length() > 1400)
		{
			s = s.substr(0, s.find(BobNet::endline));

			while (s.length() > 1380)
			{
				string partial = "PARTIAL:" + s.substr(0, 1380) + BobNet::endline;
				s = s.substr(1380);

				long long packetID = getPacketCounter_S();
				partial = to_string(packetID) + ":" + partial;
				packetCounterIncrement_S();
				packetMessageQueuePush_S(partial);
			}

			string finalString = "FINAL:" + s + BobNet::endline;

			long long packetID = getPacketCounter_S();
			finalString = to_string(packetID) + ":" + finalString;
			packetCounterIncrement_S();
			packetMessageQueuePush_S(finalString);
		}
		else
		{
			//join messages into one packet up to ~1400 bytes
			while (s.length() < 1380 && unjoinedMessageQueueSize_S() > 0)
			{
				string next = unjoinedMessageQueueFront_S();
				if (s.length() + next.length() > 1380)
				{
					break;
				}
				else
				{
					s += next;
					unjoinedMessageQueuePop_S();
				}
			}
			long long packetID = getPacketCounter_S();
			s = to_string(packetID) + ":" + s;
			packetCounterIncrement_S();
			packetMessageQueuePush_S(s);
		}
	}

}

//===============================================================================================
void UDPPeerConnection::_writeQueuedPackets()
{//===============================================================================================

	if (packetMessageQueueSize_S() == 0)return;

	long long currentTime = System::currentHighResTimer();
	long long startTime = _lastWrotePacketTime;
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	if (ticksPassed > _writePacketWait)
	{
		_lastWrotePacketTime = currentTime;
		_writePacketWait = 0;

		string s = packetMessageQueueFront_S();


		UDPpacket *packet = makePacket(s);
		if (packet == nullptr)
		{
			_writePacketWait += 2000;
			threadLogWarn_S("Could not create UDP packet");
			return;
		}

		if (SDLNet_UDP_Send(getSocket_S(), -1, packet) == 0)
		{
			_writePacketWait += 2000;
			SDLNet_FreePacket(packet);
			threadLogWarn_S("Could not send UDP packet");
		}
		else
		{
			packetMessageQueuePop_S();
			sentPacketQueuePush_S(packet);
#ifdef _DEBUG


			if (s.find("PARTIAL:")!=string::npos || s.find("FINAL:") != string::npos || s.find("BOBSGAME:FRAME:") != string::npos)
			{
				string c = s.substr(0, 160);
				threadLogDebug_S(string("SENT PEER: ") + c);
			}
			else
			threadLogDebug_S(string("SENT PEER: ") + s.substr(0,s.find(BobNet::endline)));
#endif

			string packetIDString = s.substr(0, s.find(":"));
			long long packetID = -1;
			try
			{
				packetID = stoll(packetIDString);
			}
			catch (exception)
			{
				threadLogError_S("Could not parse packet id");
			}

			if (packetID != -1)
			{
				if (_frameSentTimes->containsKey(packetID) == false)
				{
					_frameSentTimes->put(packetID, currentTime);
				}
			}
		}

	}
			
	

}
//===============================================================================================
void UDPPeerConnection::_getAddressFromSTUNServer()
{//===============================================================================================
	//see if we have a udp connection to them established
	if (getConnectedToPeer_S() == false)
	{
		//if we don't, keep pinging the stun server with our request. they should be doing the same thing.
		long long currentTime = System::currentHighResTimer();
		long long startTime = _lastConnectAttemptTime;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (ticksPassed > 2000)
		{
			_lastConnectAttemptTime = currentTime;

			if (getPeerIPAddress_S() == nullptr)
			{
				//threadLogDebug_S("Sending STUN request");
				BobNet::sendSTUNRequest(getServerConnection()->getUserID_S(), peerUserID, localUDPPort);
			}
			else
			{
				if (getGotPeerConnectResponse_S() == false)
				{

					writeReliable_S(BobNet::Friend_Connect_Request + to_string(getServerConnection()->getUserID_S()) + BobNet::endline);
					_connectTries++;
					if (_connectTries > 30)
					{
						_connectTries = 0;
						setDisconnectedFromPeer_S("Did not get a response to connect request.");
					}
				}
				else
				{
					threadLogInfo_S("Got connect request response from "+to_string(peerUserID));
					setConnectedToPeer_S(true);
				}
			}
		}
	}
}

void UDPPeerConnection::_sendKeepAlivePing()
{//===============================================================================================
	//send keepalive
	//keep last got friend keepalive ping/pong
	long long currentTime = System::currentHighResTimer();
	long long startTime = _lastReceivedDataTime;
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed > 10000) //10 seconds
	{
		//send ping
		startTime = _lastSentPingTime;
		int pingTicksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (pingTicksPassed > 10000)
		{
			_lastSentPingTime = currentTime;
			writeUnreliable_S(string("ping") + BobNet::endline);
		}
	}

}

void UDPPeerConnection::_checkForTimeout()
{//===============================================================================================
	long long currentTime = System::currentHighResTimer();
	long long startTime = _lastReceivedDataTime;
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed > 15000)
	{
		//assume peer has gone offline
		//close if no keepalive
		setDisconnectedFromPeer_S("Timed out.");

		if (getGotFriendData_S() == true)
		{
			Console::add(string("") + getFriendData_S().userName + string(" has gone offline."), BobColor::lightRed, 5000);//" escaped from reality and has descended into the inferior meat world. What a traitor."
		}
	}

}

void UDPPeerConnection::_getFriendData()
{//===============================================================================================
	long long currentTime = System::currentHighResTimer();
	if (_gotFriendData_NonThreaded == false)
	{
		//trade info, name, etc

		long long startTime = _lastSentFriendDataRequestTime;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (ticksPassed > 5000)
		{
			if (getGotFriendData_S() == false)
			{
				_lastSentFriendDataRequestTime = currentTime;
				writeReliable_S(BobNet::Friend_Data_Request + BobNet::endline);
			}
			else
			{
				_gotFriendData_NonThreaded = true;
			}
		}
	}
}



//===============================================================================================
void UDPPeerConnection::setDisconnectedFromPeer_S(string reason)
{//===============================================================================================
	setConnectedToPeer_S(false);
	setPeerIPAddress_S("", -1);

	threadLogWarn_S(string("Disconnected from " + getFriendData_S().userName + ": " + reason));
	Console::add("Disconnected from " + getFriendData_S().userName + ": " + reason, BobColor::red, 5000);

	SDLNet_UDP_Close(getSocket_S());

	if (getSocketAddedToSet_S())
	{
		if (SDLNet_UDP_DelSocket(getSocketSet_S(), getSocket_S()) < 0)
		{
			threadLogWarn_S("SDLNet_TCP_DelSocket: " + string(SDLNet_GetError()) + string(SDL_GetError()));
			SDL_ClearError();
		}

		setSocketAddedToSet_S(false);
	}
	setSocketIsOpen_S(false);


}



//===============================================================================================
bool UDPPeerConnection::udpPeerMessageReceived(string s)// ChannelHandlerContext* ctx, MessageEvent* e)
{ //===============================================================================================


#ifdef _DEBUG

  //BOBSGAME:FRAME:1.2078078643:195,e43d6f5f2951a1f767d634346812ad73:
	if (s.find("BOBSGAME:FRAME:")!=string::npos)
	{
		string c = s;
		string command = c.substr(0, c.find(":") + 1);//BOBSGAME:
		c = c.substr(c.find(":") + 1);
		string frame = c.substr(0, c.find(":") + 1);//FRAME:
		c = c.substr(c.find(":") + 1);
		string playerid = c.substr(0, c.find(":") + 1);//1.2078078643:
		c = c.substr(c.find(":") + 1);
		string idmd5 = c.substr(0, c.find(":") + 1);//195,e43d6f5f2951a1f767d634346812ad73:
		c = c.substr(c.find(":") + 1);

		log.warn(string("FROM PEER: ") + command + frame + playerid + idmd5);
	}
	else
	if(String::startsWith(s, "BOBSGAME:HOSTING:") || String::startsWith(s, "BOBSGAME:PLAYERCONFIRM:"))
	{

		//BOBSGAME:HOSTING:...:xml
		string c = s;
		string command = c.substr(0, c.find(":") + 1);//BOBSGAME:
		c = c.substr(c.find(":") + 1);
		string hosting = c.substr(0, c.find(":") + 1);//HOSTING:
		c = c.substr(c.find(":") + 1);
		string data = c.substr(0, c.find(":") + 1);//1.2078078643:
		c = c.substr(c.find(":") + 1);

		log.warn(string("FROM PEER: ") + command + hosting + data);
	}
	else
	if (String::startsWith(s, "Friend_Location_Update") == false && String::startsWith(s, "ACK:") == false)
	{
		log.warn(string("FROM PEER: ") + s);// +channel->getId() + string(" | ") + s);
	}
#endif

	//s = s.substr(s.find(":") + 1);

	if (String::startsWith(s, BobNet::Friend_Connect_Request))
	{
		sendPeerConnectResponse();
		return true;
	}
	if (String::startsWith(s, BobNet::Friend_Connect_Response))
	{
		incomingPeerConnectResponse(s);
		return true;
	}

	if (String::startsWith(s, BobNet::Friend_Data_Request))
	{
		incomingFriendDataRequest(s);
		return true;
	}
	if (String::startsWith(s, BobNet::Friend_Data_Response))
	{
		incomingFriendDataResponse(s);
		return true;
	}

	for (int i = 0; i < BobNet::engines.size(); i++)
	{
		if (BobNet::engines.get(i)->udpPeerMessageReceived(this, s))return true;
	}


	for (int i = 0; i < engineParts.size(); i++)
	{
		if (engineParts.get(i)->udpPeerMessageReceived(this, s))return true;
	}

	log.error("Did not handle UDP packet:" + s);
	return false;

}



void UDPPeerConnection::writeUnreliable_S(string s)
{ //===============================================================================================
	if (s.find(BobNet::endline) == string::npos)
	{
		threadLogError_S("Packet doesn't end with endline");
		s = s + BobNet::endline;
	}

	IPaddress* peerAddress = getPeerIPAddress_S();
	if (peerAddress == nullptr)
	{
		threadLogWarn_S("peerAddress was null.");
		return;
	}

	UDPpacket * packet = SDLNet_AllocPacket((int)s.length());
	packet->channel = -1;
	packet->address = *peerAddress;
	for (int i = 0; i < (int)s.length(); i++)
	{
		packet->data[i] = s[i];
	}
	packet->len = (int)s.length();

	if (SDLNet_UDP_Send(getSocket_S(), -1, packet) == 0)
	{
		threadLogWarn_S("Could not send UDP packet");
	}

	SDLNet_FreePacket(packet);

}

bool UDPPeerConnection::writeReliable_S(string s)
{ //===============================================================================================



   if (s.find(BobNet::endline) == string::npos)
   {
      threadLogError_S("Packet doesn't end with endline");
      s = s + BobNet::endline;
   }

//#ifdef _DEBUG
//   //BOBSGAME:FRAME:1.2078078643:195,e43d6f5f2951a1f767d634346812ad73:
//   if (String::startsWith(s, "BOBSGAME:FRAME:"))
//   {
//		string c = s;
//		string command = c.substr(0, c.find(":") + 1);//BOBSGAME:
//		c = c.substr(c.find(":") + 1);
//		string frame = c.substr(0, c.find(":") + 1);//FRAME:
//		c = c.substr(c.find(":") + 1);
//		string playerid = c.substr(0, c.find(":") + 1);//1.2078078643:
//		c = c.substr(c.find(":") + 1);
//		string idmd5 = c.substr(0, c.find(":") + 1);//195,e43d6f5f2951a1f767d634346812ad73:
//		c = c.substr(c.find(":") + 1);
//
//		threadLogDebug_S(string("Queued sending message: ") + command+frame+ playerid+idmd5);
//   }
//   else
//      //if (String::startsWith(s,"Friend_Location_Update") == false && String::startsWith(s,"Friend_Connect_Request") == false)
//      {
//#ifdef _DEBUG
//         threadLogDebug_S(string("Queued sending message: ") + s.substr(0, s.length() - 2));
//#endif
//      }
//#endif

   unjoinedMessageQueuePush_S(s);



//   if (SDLNet_UDP_Send(socket, -1, packet) == 0)
//   {
//	   log.warn("Could not send UDP packet");
//	   return false;
//   }
//   lastSentPacketTime = System::currentHighResTimer();


   return true;

}








void UDPPeerConnection::sendPeerConnectResponse()
{
	writeReliable_S(BobNet::Friend_Connect_Response + to_string(getServerConnection()->getUserID_S()) +":"+ BobNet::endline);
}

void UDPPeerConnection::incomingPeerConnectResponse(string e)//MessageEvent* e)
{

  //JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
	string s = e;// e->getMessage()->toString();

	//FriendConnectResponse:userID:
	s = s.substr(s.find(":") + 1);
	long long replyFriendUserID = -1;
	string friendUserIDString = s.substr(0,s.find(":"));
	try
	{
		replyFriendUserID = stoll(friendUserIDString);
	}
	catch (exception)
	{
		log.warn(friendUserIDString);
		log.error("Could not parse replyFriendUserID in incomingPeerConnectResponse");
	}

	if (peerUserID != replyFriendUserID)
	{
		log.error("Friend userID did not match in Friend reply.");

		return;
	}


	setGotPeerConnectResponse_S(true);
}



void UDPPeerConnection::incomingFriendDataRequest(string e)//MessageEvent* e)
{ //===============================================================================================

  //allowed info depends on type of friend, zip code friends should not get full name, etc.
  // send name,charAppearance, etc


	if (getServerConnection()->getInitialGameSaveReceived_S() == false)
	{
		return;
	}

	FriendData* myFriendData = new FriendData();

	GameSave g = getServerConnection()->getGameSave_S();
	myFriendData->initWithGameSave(g);

	string s = myFriendData->encode(peerType);

	writeReliable_S(BobNet::Friend_Data_Response + s +":"+ BobNet::endline);
}

void UDPPeerConnection::incomingFriendDataResponse(string e)//MessageEvent* e)
{ //===============================================================================================

  //JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
	string s = e;// ->getMessage()->toString();
	s = s.substr(s.find(":") + 1);

	string friendDataString = s.substr(0,s.find(":"));

	FriendData f;
	f.decode(friendDataString);

	setFriendData_S(f);
	setGotFriendData_S(true);
}


void FriendData::initWithGameSave(GameSave &g)
{ //===============================================================================================

	userName = g.userName;
	characterName = g.characterName;
	characterAppearance = g.characterAppearance;
	accountRank = g.accountRank;
	accountCreatedTime = g.accountCreatedTime;
	timesLoggedIn = g.timesLoggedIn;
	totalTimePlayed = g.totalTimePlayed;
	postalCode = g.postalCode;
	countryName = g.countryName;
	isoCountryCode = g.isoCountryCode;
	placeName = g.placeName;
	stateName = g.stateName;
	lat = g.lat;
	lon = g.lon;

	miniGamesTimesPlayed = g.miniGamesTimesPlayed;
	miniGamesTimesBattled = g.miniGamesTimesBattled;
	miniGamesTimesChallenged = g.miniGamesTimesChallenged;
	miniGamesTimesChallenger = g.miniGamesTimesChallenger;
	miniGamesTimesWon = g.miniGamesTimesWon;
	miniGamesTimesLost = g.miniGamesTimesLost;
	miniGamesTimesTied = g.miniGamesTimesTied;

	facebookID = g.facebookID;
	facebookEmail = g.facebookEmail;
	//facebookBirthday = g.facebookBirthday;
	facebookFirstName = g.facebookFirstName;
	facebookLastName = g.facebookLastName;
	facebookGender = g.facebookGender;
	//facebookLocale = g.facebookLocale;
	//facebookTimeZone = g.facebookTimeZone;
	//facebookUsername = g.facebookUsername;
	//facebookWebsite = g.facebookWebsite;
	//googlePlusID = g.googlePlusID;
}

string FriendData::encode(int friendType)
{ //===============================================================================================

	this->friendType = friendType;

	string s = string("") +
		to_string(friendType) + string(",") + string("`") +
		string(userName) + string("`") + string(",") + string("`") +
		string(characterName) + string("`") + string(",") + string("`") +
		string(characterAppearance) + string("`") + string(",") + string("`") +
		to_string(accountRank) + string("`") + string(",") + string("`") +
		to_string(accountCreatedTime) + string("`") + string(",") + string("`") +
		to_string(timesLoggedIn) + string("`") + string(",") + string("`") +
		to_string(totalTimePlayed) + string("`") + string(",") + string("`") +
		string(postalCode) + string("`") + string(",") + string("`") +
		string(countryName) + string("`") + string(",") + string("`") +
		string(isoCountryCode) + string("`") + string(",") + string("`") +
		string(placeName) + string("`") + string(",") + string("`") +
		string(stateName) + string("`") + string(",") + string("`") +
		to_string(lat) + string("`") + string(",") + string("`") +
		to_string(lon) + string("`") + string(",") + string("`") +
		to_string(miniGamesTimesPlayed) + string("`") + string(",") + string("`") +
		to_string(miniGamesTimesBattled) + string("`") + string(",") + string("`") +
		to_string(miniGamesTimesChallenged) + string("`") + string(",") + string("`") +
		to_string(miniGamesTimesChallenger) + string("`") + string(",") + string("`") +
		to_string(miniGamesTimesWon) + string("`") + string(",") + string("`") +
		to_string(miniGamesTimesLost) + string("`") + string(",") + string("`") +
		to_string(miniGamesTimesTied) + string("`");

	if (friendType != UDPPeerConnection::FACEBOOK_TYPE)
	{
		return s;
	}

	s = s + string(",") + string("`") +
		string(facebookID) + string("`") + string(",") + string("`") +
		string(facebookEmail) + string("`") + string(",") + string("`") +
		//string(facebookBirthday) + string("`") + string(",") + string("`") +
		string(facebookFirstName) + string("`") + string(",") + string("`") +
		string(facebookLastName) + string("`") + string(",") + string("`") +
		string(facebookGender) + string("`");
		//string(facebookLocale) + string("`") + string(",") + string("`") +
		//to_string(facebookTimeZone) + string("`") + string(",") + string("`") +
		//string(facebookUsername) + string("`") + string(",") + string("`") +
		//string(facebookWebsite) + string("`") + string(",") + string("`") +
		//string(googlePlusID) + string("`");

	return s;
}

void FriendData::decode(string s)
{ //===============================================================================================

	try
	{
		friendType = stoi(s.substr(0, s.find(",")));
	}
	catch (exception ex)//NumberFormatException ex)
	{
		log.error("Could not parse friendType");

	}
	s = s.substr(s.find(",") + 1);

	{
		//",userName:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			userName = t;
		}
		s = s.substr(s.find('`') + 1);
	}
	{
		//",characterName:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			characterName = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",characterAppearance:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			characterAppearance = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",accountType:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				accountRank = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse accountType");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",accountCreatedTime:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				accountCreatedTime = StringConverterHelper::fromString<long long>(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse accountCreatedTime");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",timesLoggedIn:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				timesLoggedIn = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse timesLoggedIn");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",totalTimePlayed:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				totalTimePlayed = StringConverterHelper::fromString<long long>(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse totalTimePlayed");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",postalCode:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			postalCode = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",countryName:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			countryName = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",isoCountryCode:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			isoCountryCode = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",placeName:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			placeName = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",stateName:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			stateName = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",lat:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				lat = stof(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse lat");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",lon:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				lon = stof(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse lon");
			}
		}
		s = s.substr(s.find('`') + 1);
	}


	{
		//",miniGamesTimesPlayed:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				miniGamesTimesPlayed = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse miniGamesTimesPlayed");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",miniGamesTimesBattled:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				miniGamesTimesBattled = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse miniGamesTimesBattled");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",miniGamesTimesChallenged:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				miniGamesTimesChallenged = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse miniGamesTimesChallenged");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",miniGamesTimesChallenger:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				miniGamesTimesChallenger = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse miniGamesTimesChallenger");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",miniGamesTimesWon:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				miniGamesTimesWon = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse miniGamesTimesWon");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",miniGamesTimesLost:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				miniGamesTimesLost = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse miniGamesTimesLost");
			}
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",miniGamesTimesTied:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			try
			{
				miniGamesTimesTied = stoi(t);
			}
			catch (exception ex)//NumberFormatException ex)
			{
				log.error("Could not parse miniGamesTimesTied");
			}
		}
		s = s.substr(s.find('`') + 1);
	}


	if (friendType == UDPPeerConnection::ZIP_TYPE)
	{
		return;
	}


	{
		//",facebookID:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			facebookID = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",facebookEmail:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			facebookEmail = t;
		}
		s = s.substr(s.find('`') + 1);
	}

//	{
//		//",facebookBirthday:"+
//		s = s.substr(s.find('`') + 1);
//		string t = s.substr(0, s.find('`'));
//		if (t.length() > 0)
//		{
//			facebookBirthday = t;
//		}
//		s = s.substr(s.find('`') + 1);
//	}

	{
		//",facebookFirstName:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			facebookFirstName = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",facebookLastName:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			facebookLastName = t;
		}
		s = s.substr(s.find('`') + 1);
	}

	{
		//",facebookGender:"+
		s = s.substr(s.find('`') + 1);
		string t = s.substr(0, s.find('`'));
		if (t.length() > 0)
		{
			facebookGender = t;
		}
		s = s.substr(s.find('`') + 1);
	}

//	{
//		//",facebookLocale:"+
//		s = s.substr(s.find('`') + 1);
//		string t = s.substr(0, s.find('`'));
//		if (t.length() > 0)
//		{
//			facebookLocale = t;
//		}
//		s = s.substr(s.find('`') + 1);
//	}
//
//	{
//		//",facebookTimeZone:"+
//		s = s.substr(s.find('`') + 1);
//		string t = s.substr(0, s.find('`'));
//		if (t.length() > 0)
//		{
//			try
//			{
//				facebookTimeZone = stof(t);
//			}
//			catch (exception ex)//NumberFormatException ex)
//			{
//				//ex->printStackTrace();
//				return;
//			}
//		}
//		s = s.substr(s.find('`') + 1);
//	}
//
//	{
//		//",facebookUsername:"+
//		s = s.substr(s.find('`') + 1);
//		string t = s.substr(0, s.find('`'));
//		if (t.length() > 0)
//		{
//			facebookUsername = t;
//		}
//		s = s.substr(s.find('`') + 1);
//	}
//
//	{
//		//",facebookWebsite:"+
//		s = s.substr(s.find('`') + 1);
//		string t = s.substr(0, s.find('`'));
//		if (t.length() > 0)
//		{
//			facebookWebsite = t;
//		}
//		s = s.substr(s.find('`') + 1);
//	}
//
//	{
//		//",googlePlusID:"+
//		s = s.substr(s.find('`') + 1);
//		string t = s.substr(0, s.find('`'));
//		if (t.length() > 0)
//		{
//			googlePlusID = t;
//		}
//		s = s.substr(s.find('`') + 1);
//	}
}


TCPServerConnection* UDPPeerConnection::getServerConnection()
{
	return &BobNet::tcpServerConnection;
}

