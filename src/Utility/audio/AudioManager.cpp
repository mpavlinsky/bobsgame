
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------





#include "SDL_mixer.h"

Logger AudioManager::log = Logger("AudioManager");


int G_mute = 0;//GLOBAL MUTE

int current_bgm_volume = 0;

Mix_Music* song_playing = nullptr;


int* current_mod_data_pointer = nullptr;


string playingname = "";// [128];


Mix_Chunk* mixchunks[32] = { nullptr };
string mixchunkfilename[32] = { "" };



//==========================================================================================================================
char* HARDWARE_get_sound_filename_from_name(string &name, int freq)
{//==========================================================================================================================

	char* filename = NULL;

	//if(strcmp(name,"footstep")==0)filename=footstep_FileName;

	return filename;
}


//==========================================================================================================================
Mix_Chunk* HARDWARE_get_sound_data_pointer_from_name(string &name, int freq)
{//==========================================================================================================================

	char* filename = NULL;


	filename = HARDWARE_get_sound_filename_from_name(name, freq);
	if (filename == NULL)return NULL;

	//search mixchunkfilenames 0-31 for matches with filename
	int d = -1;
	int x = 0;
	for (x = 0; x < MAX_SOUNDS_PLAYING; x++)
	{
		if (mixchunkfilename[x] == filename)
		{
			d = x;
			x = MAX_SOUNDS_PLAYING;
			break;
		}
	}

	if (d == -1)
	{
		//find open filename slot
		for (x = 0; x < MAX_SOUNDS_PLAYING; x++)
		{
			if (mixchunkfilename[x] == "")
			{
				d = x;
				mixchunkfilename[d] = filename;//set slot to filename
				mixchunks[d] = Mix_LoadWAV(mixchunkfilename[d].c_str());//load wav
				x = MAX_SOUNDS_PLAYING;
				break;
			}
		}
	}

	return mixchunks[d];
}


//==========================================================================================================================
bool HARDWARE_play_sound(string &name, int vol, int freq, int loop)//if(!HARDWARE_is_sound_channel_busy(chan))//HARDWARE_PlayFSSoundEx2(chan,HARDWARE_FSGetFile(0,name,""),vol,freq,0,loop,0);
{//==========================================================================================================================

	if (G_mute)vol = 0;


	Mix_Chunk* data = NULL;
	data = HARDWARE_get_sound_data_pointer_from_name(name, freq);

	if (data != NULL)
	{
		if (loop == 1)loop = -1;//infinite loops
		Mix_VolumeChunk(data, (int)(MIX_MAX_VOLUME * ((float)((float)vol / 256.0f))));
		Mix_PlayChannel(-1, data, loop);
	}
	else
	{
		ERROR_set_error(name);
		ERROR_set_error(" could not be played.\n");
	}


	return true;
}

//==========================================================================================================================
bool HARDWARE_play_sound_if_not_playing(string &name, int vol, int freq, int loop)
{//==========================================================================================================================


	if (G_mute)vol = 0;


	char* filename = nullptr;
	filename = HARDWARE_get_sound_filename_from_name(name, freq);
	if (filename == nullptr)return 0;

	int x = 0;
	for (x = 0; x < MAX_SOUNDS_PLAYING; x++)
	{
		if (mixchunkfilename[x] != "")
			if (mixchunkfilename[x]==filename)
			{
				return 0;
			}
	}

	HARDWARE_play_sound(name, vol, freq, loop);


	return 1;
}

//==========================================================================================================================
void HARDWARE_stop_sound(string &name)//if(HARDWARE_is_sound_channel_busy(chan))HARDWARE_StopSound(chan);
{//==========================================================================================================================

	Mix_Chunk* data = NULL;
	data = HARDWARE_get_sound_data_pointer_from_name(name, 44100);

	//go through all playing channels, if channel is playing data, stop channel
	if (data != NULL)
	{
		int channel = 0;
		int maxchannels = Mix_AllocateChannels(-1);

		for (channel = 0; channel < maxchannels; channel++)
		{
			if (data == Mix_GetChunk(channel))Mix_HaltChannel(channel);
		}
	}
}

//==========================================================================================================================
void HARDWARE_unload_wavs_done_playing()
{//==========================================================================================================================

	//go through each mixchunk->get(d)
	//see if still playing
	//if not playing, unload mixchunk->get(d) and set mixchunkfilename->get(d) to NULL

	int x = 0;
	for (x = 0; x < MAX_SOUNDS_PLAYING; x++)
	{
		if (mixchunks[x] != nullptr && mixchunkfilename[x] != "")
		{
			int channel = 0;
			int playing = 0;
			int maxchannels = Mix_AllocateChannels(-1);
			for (channel = 0; channel < maxchannels; channel++)
			{
				if (mixchunks[x] == Mix_GetChunk(channel))playing = 1;
			}

			if (playing == 0)
			{
				if (
					mixchunkfilename[x]=="data/sfx/footstepnormal.wav"//dont unload footstep, its used a lot
				)
				{
					Mix_FreeChunk(mixchunks[x]);
					mixchunks[x] = nullptr;
					mixchunkfilename[x] = "";
				}
			}
		}
	}
}

//==========================================================================================================================
void HARDWARE_set_channel_volume(int chan, int vol)//if(HARDWARE_is_sound_channel_busy(chan))HARDWARE_StopSound(chan);
{//==========================================================================================================================

	if (G_mute)vol = 0;
	else
		Mix_Volume(chan, (int)(MIX_MAX_VOLUME * ((float)((float)vol / 256.0f))));
}


//==========================================================================================================================
void HARDWARE_set_music_volume(int vol)//if(HARDWARE_is_sound_channel_busy(chan))HARDWARE_StopSound(chan);
{//==========================================================================================================================

	if (G_mute)vol = 0;

	if (current_bgm_volume != vol)
	{
		current_bgm_volume = vol;
		if (song_playing != NULL)Mix_VolumeMusic((int)(MIX_MAX_VOLUME * ((float)((float)vol / 64.0f))));
	}
}


//==========================================================================================================================
void HARDWARE_play_music(string &name, int vol)//HARDWARE_PlayFSMod(mod);
{//==========================================================================================================================

	if (G_mute)vol = 0;


	if (name==playingname || song_playing == NULL)
	{
		//copy string into playing string
		//strcpy(playingname, name);
		playingname = name;

		//free the previous song
		if (song_playing != NULL)
		{
			Mix_HookMusicFinished(NULL);
			Mix_HaltMusic();
			while (Mix_PlayingMusic())
			{
			};
			Mix_FreeMusic(song_playing);
			while (Mix_PlayingMusic())
			{
			};
			song_playing = NULL;
		}

		//load the new one
		if (name=="nice") song_playing = Mix_LoadMUS("data/bgm/snappy_nice_v01.s3m");

		if (song_playing == NULL)
		{
			ERROR_set_error(name);
			ERROR_set_error(" could not be loaded.\n");
		}
		else
			Mix_PlayMusic(song_playing, -1);
	}


	if (vol != current_bgm_volume)
	{
		current_bgm_volume = vol;
		if (song_playing != NULL)Mix_VolumeMusic((int)(MIX_MAX_VOLUME * ((float)((float)vol / 64.0f))));
	}
}


//==========================================================================================================================
void HARDWARE_stop_music()//HARDWARE_StopMod();
{//==========================================================================================================================

	if (song_playing != NULL)
	{
		Mix_HookMusicFinished(NULL);
		Mix_HaltMusic();
		while (Mix_PlayingMusic())
		{

		}

		Mix_FreeMusic(song_playing);
		while (Mix_PlayingMusic())
		{

		}

		song_playing = NULL;
	}
}

#ifdef USE_SOLOUD
SoLoud::Soloud *AudioManager::soLoud = nullptr;
#endif



//=========================================================================================================================
AudioManager::AudioManager()
{ //=========================================================================================================================

	soundByNameHashMap = new HashMap<string, Sound*>();

}

//=========================================================================================================================
AudioManager::AudioManager(Engine* g)
{ //=========================================================================================================================

	this->e = g;
	soundByNameHashMap = new HashMap<string, Sound*>();
}

//=========================================================================================================================
void AudioManager::initAudio()
{//=========================================================================================================================




#ifdef USE_SDL_MIXER
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
		{
			log.error("Couldn't set up audio: " + string(SDL_GetError()));
		}
		Mix_AllocateChannels(32);
#endif


#ifdef USE_SOLOUD
	soLoud = new SoLoud::Soloud();
	soLoud->init();
#endif
}


//=========================================================================================================================
void AudioManager::cleanup()
{//=========================================================================================================================

	log.info("Cleaning up audio...");
#ifdef USE_SDL_MIXER
 //	if(Mix_PlayingMusic())
 //	{
 //		Mix_FadeOutMusic(1000);
 //		Mix_FreeMusic(background_MUS);
 //	}
	int numtimesopened, frequency, channels;
	Uint16 format;
	numtimesopened=Mix_QuerySpec(&frequency, &format, &channels);
	for(int i=0;i<numtimesopened;i++)Mix_CloseAudio();
#endif
#ifdef USE_SOLOUD
	soLoud->deinit();
#endif

}

//Sound* AudioManager::loadSoundFileByName(const string& fileName)
//{ //=========================================================================================================================
//
//	Sound* s = nullptr;
//
//	for(int i=0;i<soundList->size();i++)if(soundList->get(i)->getName() == fileName)s = soundList->get(i);
//
//	if (s == nullptr)
//	{
//		HashMap<string, Sound *>::const_iterator got = soundByNameHashMap->find(fileName);
//		if (got != soundByNameHashMap->end())
//			s = soundByNameHashMap->get(fileName);
//	}
//
//	if (s == nullptr)
//	{
//	    s = new Sound(fileName);
//	    soundByNameHashMap->insert_or_assign(s->getName(),s);
//	}
//
//	return s;
//}

void AudioManager::update()
{ //=========================================================================================================================


	for (int i = 0; i < musicList->size(); i++)
	{
		musicList->get(i)->update();
	}
	for (int i = 0; i < soundList->size(); i++)
	{
		soundList->get(i)->update();
	}
}

Music* AudioManager::getMusicByName(const string& musicName)
{ //=========================================================================================================================
	if (musicName == "" || musicName.length() == 0)
	{
		return nullptr;
	}

	for (int i = 0; i < musicList->size(); i++)
	{
		if (musicList->get(i)->getName() == musicName)
		{
			return musicList->get(i);
		}
	}

	string clippedName = musicName;
	if (clippedName.find("_v") != -1)
	{
		clippedName.substr(0, clippedName.find("_v"));
	}

	for (int i = 0; i < musicList->size(); i++)
	{
		string name = musicList->get(i)->getName();
		if (name.find("_v") != -1)
		{
			name = name.substr(0, name.find("_v"));
		}

		if (name == clippedName)
		{
			log.error(string("Could not find music: ") + musicName + string(" so returned closest match: ") + name);
			return musicList->get(i);
		}
	}

	return nullptr;
}

Music* AudioManager::getMusicByID(int musicID)
{ //=========================================================================================================================
	for (int i = 0; i < musicList->size(); i++)
	{
		if (musicList->get(i)->getID() == musicID)
		{
			return musicList->get(i);
		}
	}
	return nullptr;
}

bool AudioManager::isAnyMusicPlaying()
{ //=========================================================================================================================
	for (int i = 0; i < musicList->size(); i++)
	{
		Music* m = musicList->get(i);
		if (m->isPlaying())
		{
			return true;
		}
	}
	return false;
}

bool AudioManager::isMusicPlaying(Music* m)
{ //=========================================================================================================================
	return m->isPlaying();
}

bool AudioManager::isMusicPlaying(const string& musicName)
{ //=========================================================================================================================
	Music* m = getMusicByName(musicName);
	if (m != nullptr)
	{
		return m->isPlaying();
	}
	return false;
}

void AudioManager::playMusic(Music* m)
{ //=========================================================================================================================
	m->play();
}

void AudioManager::playMusic(const string& musicName)
{ //=========================================================================================================================
	Music* m = getMusicByName(musicName);
	if (m != nullptr)
	{
		m->play();
	}
}

void AudioManager::playMusic(Music* m, float volume, float pitch, bool loop)
{ //=========================================================================================================================

	if (m != nullptr)
	{
		m->play(pitch, volume, loop);
	}
}

void AudioManager::playMusicByName(const string& musicName)
{ //=========================================================================================================================
	Music* m = getMusicByName(musicName);
	if (m != nullptr)
	{
		m->play();
	}
}

void AudioManager::playMusic(const string& musicName, float volume, float pitch, bool loop)
{ //=========================================================================================================================
	Music* m = getMusicByName(musicName);
	if (m != nullptr)
	{
		m->play(pitch, volume, loop);
	}
}

void AudioManager::stopMusic(Music* m)
{ //=========================================================================================================================
	m->stop();
}

void AudioManager::stopMusic(const string& musicName)
{ //=========================================================================================================================
	Music* m = getMusicByName(musicName);
	if (m != nullptr)
	{
		m->stop();
	}
}

void AudioManager::fadeOutMusic(const string& musicName, int ticks)
{ //=========================================================================================================================
	Music* m = getMusicByName(musicName);
	m->fadeOutAndStop(ticks);
}

void AudioManager::fadeOutMusic(Music* m, int ticks)
{ //=========================================================================================================================
	m->fadeOutAndStop(ticks);
}

void AudioManager::stopAllMusic()
{ //=========================================================================================================================
	for (int i = 0; i < musicList->size(); i++)
	{
		musicList->get(i)->stop();
	}
}

void AudioManager::fadeOutAllMusic(int ticks)
{ //=========================================================================================================================
	for (int i = 0; i < musicList->size(); i++)
	{
		Music* m = musicList->get(i);
		if (m->isPlaying() == true)
		{
			m->fadeOutAndStop(ticks);
		}
	}
}

void AudioManager::setAllLoopingMusicThatIsNotFadingOutToNotLoop()
{ //=========================================================================================================================
	for (int i = 0; i < musicList->size(); i++)
	{
		Music* m = musicList->get(i);
		if (m->isPlaying() == true && m->getLoop() == true)
		{
			if (m->isFadingOut() == false)
			{
				m->setLoop(false);
			}
		}
	}
}

void AudioManager::pauseAllMusic()
{ //=========================================================================================================================
	for (int i = 0; i < musicList->size(); i++)
	{
		musicList->get(i)->stop();
	}
}

void AudioManager::unpauseAllMusic()
{ //=========================================================================================================================
	for (int i = 0; i < musicList->size(); i++)
	{
		musicList->get(i)->stop();
	}
}

Sound* AudioManager::getSoundByName(const string& soundName)
{ //=========================================================================================================================

	if (soundName == "" || soundName.length() == 0)
	{
		return nullptr;
	}

	//Sound* s = nullptr;




//	HashMap<string, Sound *>::const_iterator got = soundByNameHashMap->find(soundName);
//	if (got != soundByNameHashMap->end())
//		s = soundByNameHashMap->get(soundName);
//
//	if (s != nullptr)
//	{
//		return s;
//	}



	//cheap check for soundname first
	for (int i = 0; i < soundList->size(); i++)
	{
		if (soundList->get(i)->getName() == soundName)
		{
			return soundList->get(i);
		}
	}


	//clip the filename of . and _v and look again, more expensive
	string clippedName = soundName;
	if (clippedName.find("_v") != -1)
	{
		clippedName = clippedName.substr(0, clippedName.find("_v"));
	}

	if (clippedName.find(".") != -1)
	{
		clippedName = clippedName.substr(0, clippedName.find("."));
	}

	for (int i = 0; i < soundList->size(); i++)
	{
		string name = soundList->get(i)->getName();

		if (name.find("_v") != -1)
		{
			name = name.substr(0, name.find("_v"));
		}
		if (name.find(".") != -1)
		{
			name = name.substr(0, name.find("."));
		}

		if (name == clippedName)
		{
			log.error(string("Could not find sound: ") + soundName + string(" so returned closest match: ") + name);
			return soundList->get(i);
		}
	}

	//not found at all
	return nullptr;
}


//=========================================================================================================================
void AudioManager::playSound(const string& soundName, float volume, float pitch)
{ //=========================================================================================================================

	Sound* s = getSoundByName(soundName);
	if (s != nullptr)
	{
		s->play(pitch, volume, 1); //,times);
	}

	//Exception e = new Exception();e.printStackTrace();
}


//=========================================================================================================================
void AudioManager::playSound(const string& soundName, float volume, float pitch, int times)
{ //=========================================================================================================================

	Sound* s = getSoundByName(soundName);
	if (s != nullptr)
	{
		s->play(pitch, volume, times);
	}

	//Exception e = new Exception();e.printStackTrace();
}


//=========================================================================================================================
void AudioManager::playSound(const string& soundName)
{ //=========================================================================================================================

	Sound* s = getSoundByName(soundName);
	if (s != nullptr)
	{
		s->play();
	}
}


//=========================================================================================================================
void AudioManager::playSound(Sound* s)
{ //=========================================================================================================================
	if (s != nullptr)
	{
		s->play();
	}
}

//=========================================================================================================================
void AudioManager::playSound(Sound* s, float vol)
{ //=========================================================================================================================
	if (s != nullptr)
	{
		s->play(1.0f, vol, 1); //,1);
	}
}


//=========================================================================================================================
void AudioManager::playSound(Sound* s, float vol, float pitch)
{ //=========================================================================================================================
	if (s != nullptr)
	{
		s->play(pitch, vol, 1); //,times);
	}
}


//=========================================================================================================================
void AudioManager::playSound(Sound* s, float vol, float pitch, int times)
{ //=========================================================================================================================
	if (s != nullptr)
	{
		s->play(pitch, vol, times);
	}
}


//=========================================================================================================================
Music* AudioManager::getMusicByIDCreateIfNotExist(int id)
{//=========================================================================================================================
	for (int i = 0; i < musicList->size(); i++)
	{
		Music* s = musicList->get(i);
		if (s->getID() == id)return s;
	}
	return nullptr;
}

//=========================================================================================================================
Sound* AudioManager::getSoundByIDCreateIfNotExist(int id)
{//=========================================================================================================================
	for (int i = 0; i < soundList->size(); i++)
	{
		Sound* s = soundList->get(i);
		if (s->getID() == id)return s;
	}
	return nullptr;
}


