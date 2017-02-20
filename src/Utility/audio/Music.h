//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



#include "src/Engine/network/ServerObject.h"


class MusicData;
class Logger;

class Music : public ServerObject
{
public:
	static Logger log;


protected:
	bool fileExists = false;
	bool _fileExists = false;
	bool startedDownloadThread = false;


private:
	MusicData* data;
public:
	u8* byteData;


	

#ifdef USE_SOLOUD
		SoLoud::WavStream *soLoudWave = nullptr;
		SoLoud::Modplug *soLoudMod = nullptr;
#endif
#ifdef USE_SDL_MIXER
	Mix_Music* mixMusic = nullptr;
#endif



protected:
	//AudioChannel *channel = nullptr;
private:
	float pitch = 1.0f;
	float volume = 1.0f;
	bool loop = false;


	bool shouldBePlaying = false;
	bool playingStarted = false;
	int ticksToFadeOutTotal = -1;
	int ticksToFadeOutCounter = -1;
	float volumeWhenStartedFade = 0;


public:
	Music(Engine* g, int id);


	Music(Engine* g, MusicData* data);
	Music(Engine *g, string filename);

	virtual MusicData* getData();

	virtual int getID();
	virtual string getName();
	virtual string getFileName();
	//public String getFullFilePath(){return data.getFullFilePath();}
	virtual string getMD5Name();


	virtual string getTYPEIDString();


	virtual void setID(int id);
	virtual void setName(const string& name);
	virtual void setFileName(const string& fileName);
	//public void setFullFilePath(String getFullFilePath){data.setFullFilePath(getFullFilePath);}
	virtual void setMD5Name(const string& s);


protected:
	virtual bool getFileExists();

	virtual void setFileExists(bool i);


public:
	virtual u8* getByteData();


	//The following method was originally marked 'synchronized':
	virtual void setData_S(MusicData* data);

	//Thread* downloadThread = nullptr;


	virtual void update() override;


	virtual void loadDataIntoChannel();


	virtual void play();


	virtual void play(float pitch, float volume, bool loop);


	virtual void fadeOutAndStop(int ticksToFadeOut);


	virtual bool isFadingOut();


	virtual void pause();


	virtual void unpause();


	virtual void stop();


	virtual void setLoop(bool b);


	virtual bool getLoop();


	virtual bool isPlaying();


	virtual void setVolume(float v);
	float getVolume();
	float getPitch();


	virtual void setPitch(float p);
};

