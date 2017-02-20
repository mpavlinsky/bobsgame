#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger GameDataLoader::log = Logger("GameDataLoader");


GameDataLoader::GameDataLoader(Engine* g)
{ //=========================================================================================================================
	this->e = g;


	loadGameData();
}

void GameDataLoader::loadGameData()
{ //=========================================================================================================================
	//
	//   Cache::downloadBigFileToCacheIfNotExist("gameData");
	//
	//   ArrayList<string> stringList;
	//
	//   try
	//   {
	//      //stringList = IOUtils.readLines(gameDataLoader.getClass().getClassLoader().getResourceAsStream("gameData"));
	//      stringList = IOUtils::readLines(Utils::getResourceAsStream(Cache::cacheDir + string("gameData")));
	//   }
	//   catch (IOException e)
	//   {
	//      e->printStackTrace();
	//   }
	//
	//   if (stringList->size() > 0)
	//   {
	//      for (int i = 0; i < stringList->size(); i++)
	//      {
	//         string s = stringList[i];
	//
	//         if (s.length() > 0)
	//         {
	//            if (s == "Sprites")
	//            {
	//               s = stringList[++i]; //spriteData base64 GZipped GSON
	//               while (s.length() > 1)
	//               {
	//                  if (s.length() > 0)
	//                  {
	//                     s = s.substr(s.find(":") + 1);
	//                     SpriteData* data = SpriteData::fromBase64ZippedJSON(s);
	//
	//                     Sprite* sprite = new Sprite(Engine());
	//                     sprite->initializeWithSpriteData(data);
	//
	//                     SpriteManager()->spriteByIDHashMap.put(sprite->id(), sprite);
	//                     SpriteManager()->spriteByNameHashMap.put(sprite->name(), sprite);
	//
	//                     s = stringList[++i]; //spriteData base64 GZipped intArray
	//                     sprite->indexDataIntArray = Utils::getIntArrayFromByteArray(Utils::unzipBase64StringToByteArray(Utils::decodeBase64String(s)));
	//
	//                     //								for(int b=0;b<sprite.indexDataIntArray.length/(sprite.width()/2);b++)
	//                     //								{
	//                     //									String r = "";
	//                     //									for(int x=0;x<sprite.width()/2;x++)
	//                     //									{
	//                     //										r = r+sprite.indexDataIntArray[(b*sprite.width()/2)+x];
	//                     //									}
	//                     //									System.out.println(r);
	//                     //								}
	//
	//                     s = stringList[++i]; //spritePalette base64 GZipped rgbByteArray
	//                     sprite->paletteRGBByteArray = Utils::unzipBase64StringToByteArray(Utils::decodeBase64String(s));
	//
	//                     //save to cache folder as md5 name
	//                     u8* byteArray = Utils::getByteArrayFromIntArray(sprite->indexDataIntArray);
	//                     string md5FileName = Utils::getByteArrayMD5Checksum(byteArray);
	//                     Cache::saveByteArrayToCache(byteArray, md5FileName);
	//                     data->setDataMD5(md5FileName);
	//
	//                     byteArray = sprite->paletteRGBByteArray;
	//                     md5FileName = Utils::getByteArrayMD5Checksum(byteArray);
	//                     Cache::saveByteArrayToCache(byteArray, md5FileName);
	//                     data->setPaletteMD5(md5FileName);
	//
	//                     sprite->loadTextures();
	//
	//                     if (debug)
	//                     {
	//                        log.debug(string("Loaded Sprite: ") + data->name());
	//                     }
	//                     for (int n = 0; n < data->getAnimationList()->size(); n++)
	//                     {
	//                        SpriteAnimationSequence* a = data->getAnimationList()->get(n);
	//                        if (debug)
	//                        {
	//                           log.debug(string("Loaded Animation: ") + a->frameSequenceName);
	//                        }
	//                     }
	//
	//                     s = stringList[++i]; //blank line or another spriteData
	//                  }
	//               }
	//            }
	//
	//
	//            if (s == "Maps")
	//            {
	//               s = stringList[++i]; //mapData base64 GZipped GSON
	//               while (s.length() > 1)
	//               {
	//                  if (s.length() > 0)
	//                  {
	//                     s = s.substr(s.find(":") + 1);
	//                     MapData* data = MapData::fromBase64ZippedJSON(s);
	//
	//                     Map* map = new Map(Engine(), data);
	//
	//
	//                     getMapManager()->mapList.push_back(map);
	//                     getMapManager()->mapByIDHashMap.put(map->id(), map);
	//                     getMapManager()->mapByNameHashMap.put(map->name(), map);
	//
	//                     s = stringList[++i]; //tileData base64 GZipped intArray
	//                     map->tilesetIntArray = Utils::getIntArrayFromByteArray(Utils::unzipBase64StringToByteArray(Utils::decodeBase64String(s)));
	//
	//                     s = stringList[++i]; //paletteData base64 GZipped rgbByteArray
	//                     map->paletteRGBByteArray = Utils::unzipBase64StringToByteArray(Utils::decodeBase64String(s));
	//
	//                     s = stringList[++i]; //mapLayerData base64 GZipped intArray
	//                     map->saveDataToCache(Utils::getIntArrayFromByteArray(Utils::unzipBase64StringToByteArray(Utils::decodeBase64String(s))), map->tilesetIntArray, map->paletteRGBByteArray);
	//
	//
	//                     if (debug)
	//                     {
	//                        log.debug(string("Loaded Map: ") + data->name());
	//                     }
	//
	//                     s = stringList[++i]; //blank line or another mapData
	//                  }
	//               }
	//            }
	//
	//            if (s == "Sounds")
	//            {
	//               s = stringList[++i];
	//               while (s.length() > 1)
	//               {
	//                  if (s.length() > 0)
	//                  {
	//                     s = s.substr(s.find(":") + 1);
	//                     SoundData* data = SoundData::fromBase64ZippedJSON(s);
	//
	//                     Sound* sound = new Sound(Engine(), data);
	//
	//
	//                     s = stringList[++i]; //tileData base64 GZipped intArray
	//                     sound->byteData = Utils::unzipBase64StringToByteArray(Utils::decodeBase64String(s));
	//
	//
	//                     if (debug)
	//                     {
	//                        log.debug(string("Loaded Sound: ") + data->name());
	//                     }
	//
	//                     s = stringList[++i]; //blank line or another soundData
	//                  }
	//               }
	//            }
	//
	//
	//            if (s == "Music")
	//            {
	//               s = stringList[++i];
	//               while (s.length() > 1)
	//               {
	//                  if (s.length() > 0)
	//                  {
	//                     s = s.substr(s.find(":") + 1);
	//                     MusicData* data = MusicData::fromBase64ZippedJSON(s);
	//
	//                     Music* music = new Music(Engine(), data);
	//
	//
	//                     s = stringList[++i]; //tileData base64 GZipped intArray
	//                     music->byteData = Utils::unzipBase64StringToByteArray(Utils::decodeBase64String(s));
	//
	//
	//                     if (debug)
	//                     {
	//                        log.debug(string("Loaded Music: ") + data->name());
	//                     }
	//
	//                     s = stringList[++i]; //blank line or another soundData
	//                  }
	//               }
	//            }
	//         }
	//      }
}

