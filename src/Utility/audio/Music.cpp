#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Music::log = Logger("Music");


Music::Music(Engine* g, int id)
{ //=========================================================================================================================
	this->e = g;

	this->data = new MusicData(id, "", "");

	for (int i = 0; i < (int)getAudioManager()->musicList->size(); i++)
	{
		if (getAudioManager()->musicList->get(i)->getID() == data->getID())
		{
			log.error(string("Music already exists:") + data->getName());
			return;
		}
	}
	getAudioManager()->musicList->add(this);
}

Music::Music(Engine* g, MusicData* data)
{ //=========================================================================================================================
	this->e = g;

	this->data = data;
	setInitialized_S(true);

	for (int i = 0; i < (int)getAudioManager()->musicList->size(); i++)
	{
		if (getAudioManager()->musicList->get(i)->getID() == data->getID())
		{
			log.error(string("Music already exists:") + data->getName());
			return;
		}
	}
	getAudioManager()->musicList->add(this);
}


Music::Music(Engine *g, string filename)
{ //=========================================================================================================================
	
	

	this->e = g;

	string name = string(filename);
	int found = (int)name.find('/');
	while (found != string::npos)
	{
		name = name.substr(found + 1, name.length());
		found = (int)name.find('/');
	}

	found = (int)name.find('.');
	if (found != string::npos)
		name = name.substr(0, found);

	this->data = new MusicData(-1, name, filename);

	byteData = FileUtils::loadByteFileFromExePath(filename);


#ifdef USE_SOLOUD
	filename = Main::getPath() + filename;
	//soLoudWave = new SoLoud::WavStream();
	//soLoudWave->load(filename.c_str());

	soLoudMod = new SoLoud::Modplug();
	soLoudMod->load(filename.c_str());

#endif
#ifdef USE_SDL_MIXER
	filename = Main::getPath() + filename;
	mixMusic = Mix_LoadMUS(filename.c_str());
#endif

	loadedInfoDataFromServer = true;
	fileExists = true;
	setInitialized_S(true);

	getAudioManager()->musicList->add(this);

}



MusicData* Music::getData()
{
	return data;
}

int Music::getID()
{
	return data->getID();
}

string Music::getName()
{
	return data->getName();
}

string Music::getFileName()
{
	return data->getFileName();
}

string Music::getMD5Name()
{
	return data->getMD5Name();
}

string Music::getTYPEIDString()
{
	return data->getTYPEIDString();
}

void Music::setID(int id)
{
	data->setID(id);
}

void Music::setName(const string& name)
{
	data->setName(name);
}

void Music::setFileName(const string& fileName)
{
	data->setFileName(fileName);
}

void Music::setMD5Name(const string& s)
{
	data->setMD5Name(s);
}

bool Music::getFileExists()
{ //=========================================================================================================================
	return _fileExists;
}

void Music::setFileExists(bool i)
{ //=========================================================================================================================
	_fileExists = i;
}

u8* Music::getByteData()
{ //=========================================================================================================================
	return byteData;
}

//The following method was originally marked 'synchronized':
void Music::setData_S(MusicData* data)
{ //=========================================================================================================================
	this->data = data;
	setInitialized_S(true);
}

void Music::update()
{ //=========================================================================================================================

	//get the name and filename from the server
	ServerObject::update();

	if (loadedInfoDataFromServer == false)
	{
		return;
	}

	//download the file to the cache if it doesnt exist
	if (fileExists == false && getByteData() != nullptr)
	{
		if (getFileExists() == false)
		{
			if (startedDownloadThread == false)
			{
				startedDownloadThread = true;

				//check cache FIRST before start thread.
				//only start thread if not in cache.
				if (FileUtils::checkIfFileExistsInCache(getMD5Name()))
				{
					setFileExists(true);
				}
				//            else
				//            {
				//               downloadThread = new Thread([&] ()
				//                  {
				//                     try
				//                     {
				//                        Thread::currentThread().setName("Music_downloadToCache");
				//                     }
				//                     catch (SecurityException e)
				//                     {
				//                        e->printStackTrace();
				//                     }
				//                     //now check the cache and download the mp3/ogg/xm/s3m from the s3 bucket in a new thread if not exist.
				//                     Cache::downloadBigFileToCacheIfNotExist(getMD5Name());
				//                  }
				//               );
				//
				//               downloadThread->start();
				//            }
			}
			//         else
			//         {
			//            if (downloadThread != nullptr && downloadThread->isAlive() == false)
			//            {
			//               if (Cache::checkIfFileExistsInCache(getMD5Name()))
			//               {
			//                  setFileExists(true);
			//               }
			//               else
			//               {
			//                  log.warn(string("Download thread timed out for Sound: ") + name());
			//                  downloadThread->start();
			//               }
			//            }
			//         }
		}
		else
		{
			fileExists = true;
		}
	}


	if (fileExists == true || getByteData() != nullptr)
	{
		if (shouldBePlaying == true)
		{




			            if (playingStarted == false)
			            {
#ifdef USE_SOLOUD
							AudioManager::soLoud->play(*soLoudMod);
#endif
#ifdef USE_SDL_MIXER
							Mix_PlayMusic(mixMusic, -1);
#endif

			               playingStarted = true;
			            }
			            else
			            {
			               if (playingStarted == true)
			               {
			                  
			               }
			            }
			//
			//            //resetOrLoopAudioIfDonePlaying();
			//            if (channel->isDone() == true) //this should never happen for looping music, the channel just repeats
			//            {
			//               if (loop == false)
			//               {
			//                  stop();
			//               }
			//            }
			//         }
		}
		else
		{
			stop();
		}


		if (ticksToFadeOutTotal != -1)
		{
			ticksToFadeOutCounter -= (int)getEngine()->engineTicksPassed();

			if (ticksToFadeOutCounter <= 0)
			{
				stop();
			}
			else
			{
				setVolume(((float)(ticksToFadeOutCounter) / (float)(ticksToFadeOutTotal)) * volumeWhenStartedFade);
			}
		}
	}
}


void Music::loadDataIntoChannel()
{ //=========================================================================================================================
	//
	//   if (channel == nullptr)
	//   {
	//      if (getByteData()->empty())
	//      {
	//         channel = AudioUtils::open(getFileName(), Cache::cacheDir + getMD5Name());
	//      }
	//      else
	//      {
	//         channel = AudioUtils::open(getFileName(), getMD5Name(), getByteData());
	//      }
	//   }
}


void Music::play()
{ //=========================================================================================================================
	play(1.0f, getVolume(), true);
}

void Music::play(float pitch, float volume, bool loop)
{ //=========================================================================================================================

	if (this->pitch != pitch || this->volume != volume || this->loop != loop)
	{
		this->pitch = pitch;
		this->volume = volume;
		this->loop = loop;

		//      if (channel != nullptr)
		//      {
		//         channel->setVolume(volume);
		//         channel->setLoop(loop);
		//         channel->setPitch(pitch);
		//      }
	}

	shouldBePlaying = true;

	update();
}

void Music::fadeOutAndStop(int ticksToFadeOut)
{ //=========================================================================================================================

	this->ticksToFadeOutTotal = ticksToFadeOut;
	this->ticksToFadeOutCounter = ticksToFadeOut;
	this->volumeWhenStartedFade = volume;
}

bool Music::isFadingOut()
{ //=========================================================================================================================
	if (ticksToFadeOutTotal != -1)
	{
		return true;
	}

	return false;
}

void Music::pause()
{ //=========================================================================================================================
	//   if (channel != nullptr)
	//   {
	//      channel->pause();
	//   }
}

void Music::unpause()
{ //=========================================================================================================================
	//   if (channel != nullptr)
	//   {
	//      channel->unPause();
	//   }
}

void Music::stop()
{ //=========================================================================================================================
	pitch = 1.0f;
	volume = 1.0f;
	loop = false;
	ticksToFadeOutCounter = -1;
	ticksToFadeOutTotal = -1;
	volumeWhenStartedFade = 0;


	shouldBePlaying = false;

	if (playingStarted)
	{
		//      if (channel != nullptr)
		//      {
		//         channel->closeChannelAndFlushBuffers();
		//         playingStarted = false;
		//      }
	}
}

void Music::setLoop(bool b)
{ //=========================================================================================================================
	this->loop = b;
	//   if (channel != nullptr)
	//   {
	//      channel->setLoop(b);
	//   }
}

bool Music::getLoop()
{ //=========================================================================================================================
	return loop;
}

bool Music::isPlaying()
{ //=========================================================================================================================

	//   if (channel != nullptr)
	//   {
	//      if (channel->isPaused())
	//      {
	//         return false;
	//      }
	//
	//      if (channel->isPlaying())
	//      {
	//         return true;
	//      }
	//   }

	return shouldBePlaying;
}

void Music::setVolume(float v)
{ //=========================================================================================================================
	volume = v;
#ifdef USE_SDL_MIXER
	Mix_VolumeMusic((int)(volume*128));
	
#endif
}
float Music::getVolume()
{
	return volume;

}
float Music::getPitch()
{
	return pitch;

}
void Music::setPitch(float p)
{ //=========================================================================================================================

	pitch = p;
	//   if (channel != nullptr)
	//   {
	//      channel->setPitch(p);
	//   }
}

