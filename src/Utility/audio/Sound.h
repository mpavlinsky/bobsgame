//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "src/Engine/network/ServerObject.h"

class SoundData;
class Logger;

class Sound : public ServerObject
{
public:
	static Logger log;

protected:
	bool fileExists = false;
	bool _fileExists = false;
	bool startedDownloadThread = false;


private:
	SoundData* data = nullptr;
public:
	u8* byteData = nullptr;


#ifdef USE_SOLOUD
	SoLoud::Wav *soLoudWave = nullptr;
#endif
#ifdef USE_SDL_MIXER
	Mix_Chunk* mixChunk = nullptr;
#endif
protected:
	//ArrayList<SoundChannel*>* soundChannels;


public:
	Sound(Engine* g, int id);


	Sound(Engine* g, SoundData* data);


	//Only for use for preloading sound files not on server, they do not have IDs
	Sound(Engine* g, string filename);


	virtual SoundData* getData();

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
	virtual void setData_S(SoundData* data);

	//Thread* downloadThread = nullptr;


	virtual void update() override;


	virtual void play();


	virtual void play(float pitch, float volume, int timesToPlay);





	protected:
		bool shouldBePlaying = false;
		bool playingStarted = false;
		float pitch = 1.0f;
		float volume = 1.0f;
		bool loop = false;
	public:
		int timesToPlay = 1;
		bool deleting = false;




		virtual void handlePlaying();

};

