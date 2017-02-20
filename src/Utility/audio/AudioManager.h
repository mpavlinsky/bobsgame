//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "../../Engine/Engine.h"
#include "../../Engine/EnginePart.h"
#include "./Sound.h"
#include "./Music.h"
class Logger;


#define MAX_SOUNDS_PLAYING 32


extern int G_mute;//GLOBAL MUTE


bool HARDWARE_play_sound(string &name, int vol, int freq, int loop);
void HARDWARE_stop_music();
void HARDWARE_play_music(string &name, int vol);
void HARDWARE_stop_sound(string &name);
void HARDWARE_set_music_volume(int vol);
bool HARDWARE_play_sound_if_not_playing(string &name, int vol, int freq, int loop);
void HARDWARE_unload_wavs_done_playing();
void HARDWARE_sound_init();


class AudioManager : EnginePart
{
public:
	static Logger log;

	ArrayList<Music*>* musicList = new ArrayList<Music*>();
	ArrayList<Sound*>* soundList = new ArrayList<Sound*>();
	HashMap<string, Sound*>* soundByNameHashMap = nullptr;// = new HashMap<string, Sound*>();


#ifdef USE_SOLOUD
	static SoLoud::Soloud *soLoud;// = nullptr;
#endif



	AudioManager();
	AudioManager(Engine* g);	
	static void initAudio();
	static void cleanup();

	//virtual Sound* loadSoundFileByName(const string& name);
	int getMusicVolume();
	void setMusicVolume();
	virtual void update();
	virtual Music* getMusicByName(const string& musicName);
	virtual Music* getMusicByID(int musicID);
	virtual bool isAnyMusicPlaying();
	virtual bool isMusicPlaying(Music* m);
	virtual bool isMusicPlaying(const string& musicName);
	virtual void playMusic(Music* m);
	virtual void playMusic(const string& musicName);
	virtual void playMusic(Music* m, float volume, float pitch, bool loop);
	virtual void playMusicByName(const string& musicName);
	virtual void playMusic(const string& musicName, float volume, float pitch, bool loop);
	virtual void stopMusic(Music* m);
	virtual void stopMusic(const string& musicName);
	virtual void fadeOutMusic(const string& musicName, int ticks);
	virtual void fadeOutMusic(Music* m, int ticks);
	virtual void stopAllMusic();
	virtual void fadeOutAllMusic(int ticks);
	virtual void setAllLoopingMusicThatIsNotFadingOutToNotLoop();
	virtual void pauseAllMusic();
	virtual void unpauseAllMusic();
	virtual Sound* getSoundByName(const string& soundName);
	virtual void playSound(const string& soundName, float volume, float pitch); //, int times)
	virtual void playSound(const string& soundName, float volume, float pitch, int times);
	virtual void playSound(const string& soundName);
	virtual void playSound(Sound* s);
	virtual void playSound(Sound* s, float vol);
	virtual void playSound(Sound* s, float vol, float pitch); //, int times)
	virtual void playSound(Sound* s, float vol, float pitch, int times);
	Music* getMusicByIDCreateIfNotExist(int id);
	Sound* getSoundByIDCreateIfNotExist(int id);
};
