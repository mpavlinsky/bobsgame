#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Sprite::log = Logger("Sprite");


//java::util::concurrent::ExecutorService *Sprite::generatePNGExecutorService = nullptr;

Sprite::Sprite()
{ //=========================================================================================================================
	//only for PreloadedSprite use
}

Sprite::Sprite(Engine* g)
{ //=========================================================================================================================
	this->e = g;
}

//=========================================================================================================================
void Sprite::preloadFromFile(string name)
{//=========================================================================================================================

	//log.info("new SpriteData "+name);
	this->data = new SpriteData(-1, name, name, 0, 0, 1, false, false, false, false, false, false, false, false, false, false, false, false, false, false, -1, "", 0, 0, 0, "", "");


	int width = 0;
	int height = 0;
	int frames = 0;
	int id = -1;

	//load txt, parse id,width,height,frames,animations

	//log.info("loadTextFileFromExePathIntoVectorOfStringsAndTrim "+name);
	ArrayList<string>* stringList = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/sprite/" + name + ".txt");


	if (stringList->size() > 0)
	{
		for (int i = 0; i < stringList->size(); i++)
		{
			string s = stringList->get(i);

			if (s.length() > 0)
			{
				try
				{
					if (String::startsWith(s, "id:"))
					{
						id = stoi(s.substr(s.find(":") + 1));
					}
					if (String::startsWith(s, "width:"))
					{
						width = stoi(s.substr(s.find(":") + 1));
					}
					if (String::startsWith(s, "height:"))
					{
						height = stoi(s.substr(s.find(":") + 1));
					}
					if (String::startsWith(s, "frames:"))
					{
						frames = stoi(s.substr(s.find(":") + 1));
					}
					//if(String::startsWith(s,"name:"))this.name = s.substring(s.indexOf(":")+1);
					if (String::startsWith(s, "animation:"))
					{

						s = s.substr(s.find(":") + 1);
						string frameSequenceName = s.substr(0, s.find(":"));
						s = s.substr(s.find(":") + 1);
						int frameStart = stoi(s);

						//log.info("new SpriteAnimationSequence " + frameSequenceName);
						getAnimationList()->add(new SpriteAnimationSequence(frameSequenceName, frameStart, 0, 0, 0, 0));
						//log.debug("Animation:"+frameSequenceName+":"+to_string(frameStart));
					}
				}
				catch(exception)
				{
					log.error("Could not parse sprite file: "+name);
				}

			}
		}
	}
	delete stringList;

	getData()->setID(id);
	getData()->setWidthPixels1X(width);
	getData()->setHeightPixels1X(height);
	getData()->setFrames(frames);

	this->_isInitialized = true;

	//		System.out.println("id:"+id);
	//		System.out.println("height:"+height);
	//		System.out.println("width:"+width);
	//		System.out.println("frames:"+frames);




	//log.info("Loading " + name);
	texture = GLUtils::getTextureFromPNG("data/sprite/" + name + ".png");



	//System.out.println("Texture Size:"+texture.getWidth()+","+texture.getHeight());

	//      
	//	int framesPerRow = texture->getWidth() / getWidth();
	//   
	//   
	//	for (int frame = 0;frame < getNumFrames();frame++)
	//	{
	//   
	//   
	//	         //			int tx0 = ((int)(frame%framesPerRow))*getWidth();
	//	         //			int tx1 = tx0+getWidth();
	//	         //			int ty0 = ((int)(frame/framesPerRow))*getHeight();
	//	         //			int ty1 = ty0+getHeight();
	//   
	//   
	//	   int x = ((int)(frame % framesPerRow))*getWidth();
	//	   int y = ((int)(frame / framesPerRow))*getHeight();
	//   
	//   
	//	   //tx0=0;
	//	   //tx1=getWidth();
	//   
	//	   //ty0=0;
	//	   //ty1=getHeight();
	//   
	//	         //			tx0 = (float)((float)tx0/(float)texture.getWidth());
	//	         //			tx1 = (float)((float)tx1/(float)texture.getWidth());
	//	         //			ty0 = (float)((float)ty0/(float)texture.getHeight());
	//	         //			ty1 = (float)((float)ty1/(float)texture.getHeight());
	//   
	//	   frameTextureRegionList->add(new TextureRegion(texture,x,y,getWidth(),getHeight()));
	//   
	//	}
	//   
}


//The following method was originally marked 'synchronized':
void Sprite::initializeWithSpriteData(SpriteData* spriteData)
{ //=========================================================================================================================

	if (this->data != nullptr)
	{
		return;
	}

	_isInitialized = true;

	if (spriteData == nullptr)
	{

		spriteData = new SpriteData();

		log.warn("Sprite::initializeWithSpriteData spriteData was null");
	}

	this->data = spriteData;


	if (getName() == "" || getName() == "none" || getName().length() == 0)
	{
		this->texture = GLUtils::blankTexture;
	}


	if (getIsCar())
	{
		useHQ2X = true;
	}
	if (getForceHQ2X())
	{
		useHQ2X = true;
	}

	if (getIsItem() || getIsGame())
	{
		new Item(getEngine(), this);
	}
}


//=========================================================================================================================
void Sprite::sendDataRequest(const string &spriteName)
{//=========================================================================================================================
	//if engine is NOT gameEngine return, i.e. it is BobsGame and all the sprites are preloaded, should never get here though because it only calls this is sprite isnt initialized, etc.
	if ((dynamic_cast<BGClientEngine*>(getEngine()) != nullptr) == false)return;

	long long startTime = lastSentDataRequestTime;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	if (ticksPassed>1000)
	{
		lastSentDataRequestTime = currentTime;

		getEngine()->sendSpriteDataRequestByName(spriteName);
	}
}
//=========================================================================================================================
void Sprite::sendDataRequest(int id)
{//=========================================================================================================================

	if ((dynamic_cast<BGClientEngine*>(getEngine()) != nullptr) == false)return;

	long long startTime = lastSentDataRequestTime;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed>1000)
	{
		lastSentDataRequestTime = currentTime;

		getEngine()->sendSpriteDataRequestByID(id);
	}
}


//=========================================================================================================================
//The following method was originally marked 'synchronized':
bool Sprite::getInitialized_S()
{ //=========================================================================================================================
	return _isInitialized;
}


//=========================================================================================================================
//The following method was originally marked 'synchronized':
void Sprite::setInitialized_S(bool i)
{ //=========================================================================================================================
	_isInitialized = i;
}

//=========================================================================================================================
void Sprite::drawFrame(const string& animationName, float x0, float x1, float y0, float y1, float r, float g, float b, float a, int filter)
{ //===============================================================================================

	SpriteAnimationSequence* s = getAnimationByName(animationName);

	if (s != nullptr)
	{
		drawFrame(this->texture, s->frameStart, x0, x1, y0, y1, r, g, b, a, filter);
	}
	else
	{
		//log.error("Could not find animation: "+animationName+" in Sprite: "+getName());
		drawFrame(this->texture, 0, x0, x1, y0, y1, r, g, b, a, filter);
	}
}

//=========================================================================================================================
void Sprite::drawFrameXYWH(const string& animationName, float x, float y, float w, float h, float r, float g, float b, float a, int filter)
{ //===============================================================================================

	drawFrame(animationName, x, x+w, y, y+h, r,g,b,a,filter);

}

//=========================================================================================================================
void Sprite::drawFrame(int frame, float x0, float x1, float y0, float y1, float a, int filter)
{ //===============================================================================================
	drawFrame(this->texture, frame, x0, x1, y0, y1, 1.0f, 1.0f, 1.0f, a, filter);
}

//=========================================================================================================================
void Sprite::drawFrame(BobTexture* texture, int frame, float x0, float x1, float y0, float y1, float a, int filter)
{ //===============================================================================================
	drawFrame(texture, frame, x0, x1, y0, y1, 1.0f, 1.0f, 1.0f, a, filter);
}

//=========================================================================================================================
void Sprite::drawFrame(int frame, float x0, float x1, float y0, float y1, float r, float g, float b, float a, int filter)
{ //===============================================================================================
	if (spriteTextureInitialized == true && this->texture != nullptr)
	{
		drawFrame(this->texture, frame, x0, x1, y0, y1, r, g, b, a, filter);
	}
}

//=========================================================================================================================
void Sprite::drawFrame(BobTexture* texture, int frame, float x0, float x1, float y0, float y1, float r, float g, float b, float a, int filter)
{ //===============================================================================================

	if (texture != nullptr)
	{


		//this is for animations that have one frame per row stacked vertically
//		float tx0 = 0.0f;
//		float tx1 = ((float)(getWidth()) / (float)(texture->getTextureWidth()));
//		float ty0 = (((float)(getHeight())) * frame) / (float)(texture->getTextureHeight());
//		float ty1 = (((float)(getHeight())) * (frame + 1)) / (float)(texture->getTextureHeight());


		int w = getImageWidth();
		int h = getImageHeight();

		int framesPerRow = texture->getTextureWidth() / (w+1);


		int px0 = 1+(frame % framesPerRow)*(w+1);
		int px1 = px0 + w;
		int py0 = 1+(frame / framesPerRow)*(h+1);
		int py1 = py0 + h;

		//tx0=0;
		//tx1=getWidth();

		//ty0=0;
		//ty1=getHeight();

		float tx0 = ((float)px0 / (float)texture->getTextureWidth());
		float tx1 = ((float)px1 / (float)texture->getTextureWidth());
		float ty0 = ((float)py0 / (float)texture->getTextureHeight());
		float ty1 = ((float)py1 / (float)texture->getTextureHeight());

		float tw = tx1 - tx0;
		float th = ty1 - ty0;

		//TODO: fix this by making 1 pixel transparent border around textures, for now i'm removing 1% of the texture width
		tx0 += 0.01f*tw;
		tx1 -= 0.01f*tw;
		ty0 += 0.01f*th;
		ty1 -= 0.01f*th;


		GLUtils::drawTexture(texture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, r, g, b, a, filter);

	}
}


//===============================================================================================
void Sprite::draw(float tx0, float tx1, float ty0, float ty1, float x0, float x1, float y0, float y1, float r, float g, float b, float a, int filter)
{//===============================================================================================

	if (texture != nullptr)
	{

		GLUtils::drawTexture(texture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, r, g, b, a, filter);


		//set frame in texture
		//			float tx = tx0;
		//			float ty = ty0;
		//			float tw = tx1-tx0;
		//			float th = ty1-ty0;

		//ty = 1.0f - ty;//flipped texture because libgdx has weird coordinate stuff
		//th = -th;

		//sprite->setRegion(tx0,ty0,tx1,ty1);
		//sprite->flip(false,true);


		/*


		float sx = x0;
		float sy = y0;
		float sw = x1 - x0;
		float sh = y1 - y0;


		float w = BobsGame::FBOWidth;
		float h = BobsGame::FBOHeight;
		//float heightWidthRatio = h / w;

		sx = sx / w;
		sy = sy / h; // * heightWidthRatio;
		sw = sw / w;
		sh = sh / h; // * heightWidthRatio;


		//sprite->setBounds(sx,sy,sw,sh);
		//sprite->setColor(r,g,b,a);


		//if(filter==GLUtils::FILTER_NEAREST)sprite.getTexture().setFilter(TextureFilter.Nearest,TextureFilter.Nearest);

		//Camera camera = BobsGame::camera;
		//camera.update();

		SpriteBatch *spriteBatch = BobsGame::spriteBatch;

		//spriteBatch.setProjectionMatrix(camera.combined);
		//spriteBatch->begin();
		//BobsGame::spriteBatch.setColor(r,g,b,a);

		sprite->draw(spriteBatch);

		//BobsGame::spriteBatch.setColor(1,1,1,1);
		//spriteBatch->end();

		*/
	}
}


//=========================================================================================================================
void Sprite::update()
{ //=========================================================================================================================

	if (getEventID() != -1)
	{
		Event* event = getEventManager()->getEventByIDCreateIfNotExist(getEventID());
		getEventManager()->addToEventQueueIfNotThere(event); //events update their own network data inside their run function
	}


	{
		if (spriteTextureInitialized == false)
		{


			long long startTime = lastCheckedSpriteTextureTime;
			long long currentTime = System::currentHighResTimer();
			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

			//small delay to prevent thread locking on synchronized functions.
			if (ticksPassed > 200)
			{
				lastCheckedSpriteTextureTime = currentTime;

				if (texture == nullptr)
				{
					//this has its own timer delay (when send network request)
					if (getDataMD5() != "" && getDataMD5().length() > 0)
					{
						loadTextures();
					}
					else
					{
						spriteTextureInitialized = true;
					}
				}
				else
				{
					spriteTextureInitialized = true;
				}
			}
		}
	}
}


//=========================================================================================================================
void Sprite::loadTextures()
{ //=========================================================================================================================


	if (getIsRandom() == true)
	{
		//random bin MD5s are initialized already in the spriteAssetIndex, don't need to get them from the server.


		//we always need the bin byte arrays loaded for randoms, since we will be using them each time we make a new random

		if (indexDataIntArray == nullptr)
		{
			indexDataIntArray = FileUtils::loadIntFileFromCacheOrDownloadIfNotExist(string("") + getDataMD5());
		}
		if (paletteRGBByteArray == nullptr)
		{
			paletteRGBByteArray = FileUtils::loadByteFileFromCacheOrDownloadIfNotExist(string("") + getPaletteMD5());
		}


		//TODO: check for 1x shadow png as well if not multicore


		//check if hq2x shadow png exists under md5 name folder

		//construct shadow texture if it doesn't exist (if getHasShadow)

		//we don't need to construct a normal hq2x png for randoms because it will never be used.


		if (texture == nullptr)
		{
			if (getHasShadow() == true)
			{
				if (checkedIfExist == false) //only check once if file exists already
				{
					checkedIfExist = true;

					BobFile* textureFile = nullptr;
					if (useHQ2X)
					{
						textureFile = new BobFile(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("2x") + "/" + getDataMD5() + string("s"));
					}
					else
					{
						textureFile = new BobFile(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("1x") + "/" + getDataMD5() + string("s"));
					}

					if (textureFile->exists())
					{
						setSpritePNGFileExists_S(true);
					}
				}


				if (getSpritePNGFileExists_S() == true)
				{
					texture = GLUtils::blankTexture;
					if (useHQ2X)
					{
						shadowTexture = GLUtils::getTextureFromPNG(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("2x") + "/" + getDataMD5() + string("s"));
					}
					else
					{
						shadowTexture = GLUtils::getTextureFromPNG(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("1x") + "/" + getDataMD5() + string("s"));
					}

					//incrementSpriteTexturesLoaded();
				}
				else
				{
					// if neither exist, load the byte arrays and make them depending on settings (cpu multicore required for hq2x)

					if (threadCreated == false)
					{
						threadCreated = true;

						FileUtils::makeDir(FileUtils::appDataPath + string("_") + getDataMD5());
						FileUtils::makeDir(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("1x") + "/");
						FileUtils::makeDir(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("2x") + "/");

						//                  if (MapManager::useThreads == true && generatePNGExecutorService == nullptr)
						//                  {
						//                     generatePNGExecutorService = Executors::newFixedThreadPool(1);
						//                  }
						//
						//                  if (MapManager::useThreads == true)
						//                  {
						//                     //incrementSpritePNGThreadsCreated_S();
						//
						//                     generatePNGExecutorService->execute([&] ()
						//                        {
						//                           try
						//                           {
						//                              Thread::currentThread().setName("Sprite_createSpriteRandomShadowTexturePNG");
						//                           }
						//                           catch (SecurityException e)
						//                           {
						//                              e->printStackTrace();
						//                           }
						//                           //createSpriteTexturePNG();
						//
						//                           if (getHasShadow() == true)
						//                           {
						//                              createSpriteShadowTexturePNG_S();
						//                           }
						//
						//                           setSpritePNGFileExists_S(true);
						//                           //decrementSpritePNGThreadsCreated_S();
						//                        }
						//                     );
						//                  }
						//                  else
						{
							//do it linearly, waiting for all chunks to finish before continuing
							//createSpriteTexturePNG();

							if (getHasShadow() == true)
							{
								createSpriteShadowTexturePNG_S();
							}

							setSpritePNGFileExists_S(true);
						}
					}
				}
			}
			else
			{
				texture = GLUtils::blankTexture;
				shadowTexture = GLUtils::blankTexture;
			}
		}
	}
	else
	{
		//should always have this now since we are loading the spriteData from server instead of just the MD5
		//so if the spriteAsset exists, it has MD5s, or the texture is blankTexture if it was initialized with null


		//			if(hasDataMD5==false)//unsynchronized check to avoid locking on synchronized function
		//			{
		//				if(getDataMD5()==null)
		//				{
		//					requestDataMD5sFromServer();
		//				}
		//				else
		//				{
		//					hasDataMD5=true;
		//				}
		//			}
		//			else


		if (texture == nullptr)
		{
			//we've gotten the bin MD5s from the server. now we have to construct the PNGs

			//check if hq2x png exists under md5 name folder

			//TODO: check if 1x png exists under md5 name folder


			if (checkedIfExist == false) //only check once if file exists already
			{
				checkedIfExist = true;

				BobFile* textureFile = nullptr;
				if (useHQ2X)
				{
					textureFile = new BobFile(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("2x") + "/" + getDataMD5());
				}
				else
				{
					textureFile = new BobFile(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("1x") + "/" + getDataMD5());
				}
				if (textureFile->exists())
				{
					setSpritePNGFileExists_S(true);
				}
			}


			if (getSpritePNGFileExists_S() == true)
			{
				if (useHQ2X == true)
				{
					texture = GLUtils::getTextureFromPNG(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("2x") + "/" + getDataMD5());
				}
				else
				{
					texture = GLUtils::getTextureFromPNG(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("1x") + "/" + getDataMD5());
				}

				if (getHasShadow() == true)
				{
					if (useHQ2X)
					{
						shadowTexture = GLUtils::getTextureFromPNG(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("2x") + "/" + getDataMD5() + string("s"));
					}
					else
					{
						shadowTexture = GLUtils::getTextureFromPNG(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("1x") + "/" + getDataMD5() + string("s"));
					}
				}
				else
				{
					shadowTexture = GLUtils::blankTexture;
				}

				//incrementSpriteTexturesLoaded();
			}
			else
			{
				// if neither exist, load the byte arrays and make them depending on settings (cpu multicore required for hq2x)

				if (threadCreated == false)
				{
					threadCreated = true;


					//make thread

					if (indexDataIntArray == nullptr)
					{
						indexDataIntArray = FileUtils::loadIntFileFromCacheOrDownloadIfNotExist(string("") + getDataMD5());
					}
					if (paletteRGBByteArray == nullptr)
					{
						paletteRGBByteArray = FileUtils::loadByteFileFromCacheOrDownloadIfNotExist(string("") + getPaletteMD5());
					}


					FileUtils::makeDir(FileUtils::appDataPath + string("_") + getDataMD5());
					FileUtils::makeDir(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("1x") + "/");
					FileUtils::makeDir(FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("2x") + "/");


					//               if (MapManager::useThreads == true && generatePNGExecutorService == nullptr)
					//               {
					//                  generatePNGExecutorService = Executors::newFixedThreadPool(3);
					//               }
					//
					//               if (MapManager::useThreads == true)
					//               {
					//                  //incrementSpritePNGThreadsCreated_S();
					//
					//                  generatePNGExecutorService->execute([&] ()
					//                     {
					//                        try
					//                        {
					//                           Thread::currentThread().setName("Sprite_createSpriteTexturePNG");
					//                        }
					//                        catch (SecurityException e)
					//                        {
					//                           e->printStackTrace();
					//                        }
					//
					//                        createSpriteTexturePNG_S();
					//
					//                        if (getHasShadow() == true)
					//                        {
					//                           createSpriteShadowTexturePNG_S();
					//                        }
					//
					//                        setSpritePNGFileExists_S(true);
					//                        //decrementSpritePNGThreadsCreated_S();
					//                     }
					//                  );
					//               }
					//               else
					{
						//do it linearly, waiting for all chunks to finish before continuing
						createSpriteTexturePNG_S();

						if (getHasShadow() == true)
						{
							createSpriteShadowTexturePNG_S();
						}

						setSpritePNGFileExists_S(true);
					}
				}
			}
		}
	}
}


//=========================================================================================================================
u8* Sprite::getReplacementRGBFromSet(int r, int g, int b, Sprite* s, int set)
{ //=========================================================================================================================

	u8* rgb = new u8[3];
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;


	int w = s->getScreenWidth() / 2;

	for (int x = 0; x < w; x++)
	{
		int oldIndex = s->indexDataIntArray[x] & 0xFF;

		int oldR = s->paletteRGBByteArray[oldIndex * 3 + 0] & 0xFF;
		int oldG = s->paletteRGBByteArray[oldIndex * 3 + 1] & 0xFF;
		int oldB = s->paletteRGBByteArray[oldIndex * 3 + 2] & 0xFF;

		if (r == oldR && g == oldG && b == oldB)
		{
			int newIndex = s->indexDataIntArray[(w * set) + x];


			rgb[0] = s->paletteRGBByteArray[newIndex * 3 + 0] & 0xFF;
			rgb[1] = s->paletteRGBByteArray[newIndex * 3 + 1] & 0xFF;
			rgb[2] = s->paletteRGBByteArray[newIndex * 3 + 2] & 0xFF;

			return rgb;
		}
	}

	return rgb;
}

//The following method was originally marked 'synchronized':
u8* Sprite::createRandomSpriteTextureByteBuffer_S(int eyeSet, int skinSet, int hairSet, int shirtSet, int pantsSet, int shoeSet, int carSet)
{ //=========================================================================================================================


	int* data = indexDataIntArray;
	u8* pal = paletteRGBByteArray;


	//create bytebuffer


	//-----------------------------
	//allocate the indexed gfx data array, buffer, and texture
	//-----------------------------

	int imageWidth = getScreenWidth();
	int imageHeight = getScreenHeight() * getNumFrames();

	int texWidth = Math::getClosestPowerOfTwo(imageWidth);
	int texHeight = Math::getClosestPowerOfTwo(imageHeight);


	u8* textureByteArray = new u8[texWidth * texHeight * 4];

	//direct method, uses ram outside of the JVM
	//   u8* textureByteBuffer = ByteBuffer::allocateDirect(textureByteArray->size());
	//   textureByteBuffer->order(ByteOrder::nativeOrder());


	//for each pixel in data
	//check palette for this index
	//if it is 0, bytebuffer is clear
	//if it is black, bytebuffer is black

	int w = getScreenWidth() / 2; //because width is widthHQ, which is floatd because we draw everything at 2x. actual width of data is width/2
	int h = getScreenHeight() / 2;

	BufferedImage* spriteBufferedImage = nullptr;
	if (useHQ2X)
	{
		spriteBufferedImage = new BufferedImage(w, h * getNumFrames(), BufferedImage::TYPE_INT_ARGB);
	}
	else
	{
		spriteBufferedImage = new BufferedImage(w * 2, h * 2 * getNumFrames(), BufferedImage::TYPE_INT_ARGB);
	}

	for (int f = 0; f < getNumFrames(); f++)
	{
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				int r = 0;
				int g = 0;
				int b = 0;
				int a = 255;


				int index = data[(f * w * h) + y * w + x]; // & 0xFF;


				if (index == 0)
				{
					a = 0; //clear
				}
				else
				{
					if (index == 1) //black
					{
						r = 0;
						g = 0;
						b = 0;
					}
					else
					{
						if (index == 2) //white
						{
							r = 255;
							g = 255;
							b = 255;
						}
						else
						{
							r = pal[index * 3 + 0] & 0xFF;
							g = pal[index * 3 + 1] & 0xFF;
							b = pal[index * 3 + 2] & 0xFF;


							if (r != g || g != b) //skip gray colors, lots of hair is this color.
							{
								//TODO: need a standard amount of variations so i can randomly select one.

								//if this color is an eye color

								//get the correct replacement color.

								//dont need to get random stuff from the server. just put the MD5s straight into SpriteAssetList
								//then i can load the random color variations on program start


								//DONE: have these in memory on load.
								//random sprites should contain their own data and pal.

								u8* rgb;

								if (carSet != -1)
								{
									rgb = getReplacementRGBFromSet(r, g, b, getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMcarColors"), carSet);

									if (rgb != nullptr)
									{
										r = rgb[0];
										g = rgb[1];
										b = rgb[2];
									}
								}
								else
								{
									rgb = getReplacementRGBFromSet(r, g, b, getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMeyeColors"), eyeSet);

									if (rgb != nullptr)
									{
										r = rgb[0];
										g = rgb[1];
										b = rgb[2];
									}
									else
									{
										rgb = getReplacementRGBFromSet(r, g, b, getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMskinColors"), skinSet);
									}

									if (rgb != nullptr)
									{
										r = rgb[0];
										g = rgb[1];
										b = rgb[2];
									}
									else
									{
										rgb = getReplacementRGBFromSet(r, g, b, getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMhairColors"), hairSet);
									}

									if (rgb != nullptr)
									{
										r = rgb[0];
										g = rgb[1];
										b = rgb[2];
									}
									else
									{
										rgb = getReplacementRGBFromSet(r, g, b, getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshirtColors"), shirtSet);
									}

									if (rgb != nullptr)
									{
										r = rgb[0];
										g = rgb[1];
										b = rgb[2];
									}
									else
									{
										rgb = getReplacementRGBFromSet(r, g, b, getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMpantsColors"), pantsSet);
									}

									if (rgb != nullptr)
									{
										r = rgb[0];
										g = rgb[1];
										b = rgb[2];
									}
									else
									{
										rgb = getReplacementRGBFromSet(r, g, b, getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshoeColors"), shoeSet);
									}

									if (rgb != nullptr)
									{
										r = rgb[0];
										g = rgb[1];
										b = rgb[2];
									}
								}
							}
						}
					}
				}

				if (useHQ2X)
				{
					spriteBufferedImage->setRGB(x, y + (f * h), (new BobColor(r, g, b, a))->getRGB());
				}
				else
				{
					//now fill textureByteArray with this color
					for (int yy = 0; yy < 2; yy++)
					{
						for (int xx = 0; xx < 2; xx++)
						{
							textureByteArray[(f * texWidth * h * 2 + ((y * 2 + yy) * texWidth + (x * 2 + xx))) * 4 + 0] = static_cast<char>(r);
							textureByteArray[(f * texWidth * h * 2 + ((y * 2 + yy) * texWidth + (x * 2 + xx))) * 4 + 1] = static_cast<char>(g);
							textureByteArray[(f * texWidth * h * 2 + ((y * 2 + yy) * texWidth + (x * 2 + xx))) * 4 + 2] = static_cast<char>(b);
							textureByteArray[(f * texWidth * h * 2 + ((y * 2 + yy) * texWidth + (x * 2 + xx))) * 4 + 3] = static_cast<char>(a);
						}
					}
				}
			}
		}
	}

	if (useHQ2X)
	{
		BufferedImage* hq2xSpriteBufferedImage = (new HQ2X())->hq2x(spriteBufferedImage);

		setHQ2XAlphaFromOriginal(hq2xSpriteBufferedImage, spriteBufferedImage);

		//spriteBufferedImage.flush();
		delete spriteBufferedImage;

		antialiasBufferedImage(hq2xSpriteBufferedImage);


		//now fill textureByteArray with this bufferedimage
		for (int y = 0; y < imageHeight; y++)
		{
			for (int x = 0; x < imageWidth; x++)
			{
				BobColor* c = new BobColor(hq2xSpriteBufferedImage->getRGB(x, y));// , true);

				textureByteArray[(y * texWidth + x) * 4 + 0] = static_cast<u8>(c->ri());
				textureByteArray[(y * texWidth + x) * 4 + 1] = static_cast<u8>(c->gi());
				textureByteArray[(y * texWidth + x) * 4 + 2] = static_cast<u8>(c->bi());
				textureByteArray[(y * texWidth + x) * 4 + 3] = static_cast<u8>(c->ai());
			}
		}

		delete hq2xSpriteBufferedImage;

		//make texture out of the bytebuffer
	}


	return textureByteArray;
}


//=========================================================================================================================
//The following method was originally marked 'synchronized':
void Sprite::createSpriteTexturePNG_S()
{ //=========================================================================================================================

	// construct texture
	// construct shadow texture (if getHasShadow)


	int w = getScreenWidth() / 2;
	int h = getScreenHeight() / 2;


	//---------------------------
	//make bufferedimage the size of all sprite frames and fill it
	//---------------------------
	BufferedImage* spriteBufferedImage = nullptr;
	if (useHQ2X)
	{
		spriteBufferedImage = new BufferedImage(w, h * getNumFrames(), BufferedImage::TYPE_INT_ARGB);
	}
	else
	{
		spriteBufferedImage = new BufferedImage(w * 2, h * 2 * getNumFrames(), BufferedImage::TYPE_INT_ARGB);
	}

	for (int f = 0; f < getNumFrames(); f++)
	{
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				int r = 0;
				int g = 0;
				int b = 0;
				int a = 255;


				int index = indexDataIntArray[(f * w * h) + (y * w) + x]; // & 0xFF;


				if (index == 0)
				{
					a = 0; //clear
				}
				else
				{
					if (index == 1) //black
					{
						r = 0;
						g = 0;
						b = 0;
					}
					else
					{
						if (index == 2) //white
						{
							r = 255;
							g = 255;
							b = 255;
						}
						else
						{
							r = paletteRGBByteArray[index * 3 + 0] & 0xFF;
							g = paletteRGBByteArray[index * 3 + 1] & 0xFF;
							b = paletteRGBByteArray[index * 3 + 2] & 0xFF;
						}
					}
				}

				if (useHQ2X)
				{
					spriteBufferedImage->setRGB(x, y + (f * h), (new BobColor(r, g, b, a))->getRGB());
				}
				else
				{
					for (int yy = 0; yy < 2; yy++)
					{
						for (int xx = 0; xx < 2; xx++)
						{
							spriteBufferedImage->setRGB(x * 2 + xx, y * 2 + yy + (f * h * 2), (new BobColor(r, g, b, a))->getRGB());
						}
					}
				}
			}
		}
	}

	if (useHQ2X)
	{
		BufferedImage* hq2xSpriteBufferedImage = (new HQ2X())->hq2x(spriteBufferedImage);

		setHQ2XAlphaFromOriginal(hq2xSpriteBufferedImage, spriteBufferedImage);

		delete spriteBufferedImage;

		antialiasBufferedImage(hq2xSpriteBufferedImage);

		//---------------------------
		//save to png
		//---------------------------
		FileUtils::saveImage(string("") + FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("2x") + "/" + getDataMD5(), hq2xSpriteBufferedImage);

		delete hq2xSpriteBufferedImage;
	}
	else
	{
		FileUtils::saveImage(string("") + FileUtils::appDataPath + string("_") + getDataMD5() + "/" + string("1x") + "/" + getDataMD5(), spriteBufferedImage);
	}
}


//=========================================================================================================================
//The following method was originally marked 'synchronized':
void Sprite::createSpriteShadowTexturePNG_S()
{ //=========================================================================================================================

	//---------------------------
	//write shadow frames
	//---------------------------


	int width = getScreenWidth() / 2;
	int height = getScreenHeight() / 2;


	BufferedImage* spriteBufferedImage = nullptr;
	if (useHQ2X)
	{
		spriteBufferedImage = new BufferedImage(width, height * getNumFrames(), BufferedImage::TYPE_INT_ARGB);
	}
	else
	{
		spriteBufferedImage = new BufferedImage(width * 2, height * 2 * getNumFrames(), BufferedImage::TYPE_INT_ARGB);
	}

	for (int f = 0; f < getNumFrames(); f++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int index = indexDataIntArray[(f * width * height) + y * width + x]; // & 0xFF;

				if (index != 0)
				{
					int bottom_pixel_y = height - 1;

					//find bottom pixel to start copying shadow from so feet are exactly at the top of the frame
					for (int yy = height - 1; yy >= 0; yy--)
					{
						for (int xx = 0; xx < width; xx++)
						{
							if ((indexDataIntArray[(f * width * height) + yy * width + xx]) != 0) // & 0xFF
							{
								bottom_pixel_y = yy;
								yy = -1;
								break;
							}
						}
					}

					//since we're not copying from the bottom, we need to stop when we reach the top, not copy the full height
					if (bottom_pixel_y - y < 0)
					{
						y = height;
						break;
					}

					int nx = x;
					int ny = (height * f) + ((bottom_pixel_y) - y);
					int col = BobColor::black->getRGB();

					if (useHQ2X)
					{
						spriteBufferedImage->setRGB(nx, ny, col);
					}
					else
					{
						for (int yy = 0; yy < 2; yy++)
						{
							for (int xx = 0; xx < 2; xx++)
							{
								spriteBufferedImage->setRGB(nx * 2 + xx, ny * 2 + yy, col);
							}
						}
					}
				}
			}
		}
	}

	//   if (useHQ2X)
	//   {
	//      BufferedImage* hq2xShadowBufferedImage = (new HQ2X())->hq2x(spriteBufferedImage);
	//
	//      setHQ2XAlphaFromOriginal(hq2xShadowBufferedImage, spriteBufferedImage);
	//
	//      //spriteBufferedImage.flush();
	//      //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//      delete spriteBufferedImage;
	//
	//      antialiasBufferedImage(hq2xShadowBufferedImage);
	//
	//      //---------------------------
	//      //save to png
	//      //---------------------------
	//
	//      FileUtils::saveImage(string("") + FileUtils::cacheDir + string("_") + getDataMD5() + "/" + string("2x") + "/" + getDataMD5() + string("s"), hq2xShadowBufferedImage);
	//
	//      //hq2xShadowBufferedImage.flush();
	//      //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	//      delete hq2xShadowBufferedImage;
	//   }
	//   else
	//   {
	//      FileUtils::saveImage(string("") + FileUtils::cacheDir + string("_") + getDataMD5() + "/" + string("1x") + "/" + getDataMD5() + string("s"), spriteBufferedImage);
	//   }
}

//The following method was originally marked 'synchronized':
void Sprite::releaseSpriteTexture_S()
{ //=========================================================================================================================

	texture->release();
	texture = nullptr;

	shadowTexture->release();
	shadowTexture = nullptr;

}

//The following method was originally marked 'synchronized':
bool Sprite::getSpritePNGFileExists_S()
{ //=========================================================================================================================
	return _texturePNGExists;
}

//The following method was originally marked 'synchronized':
void Sprite::setSpritePNGFileExists_S(bool done)
{ //=========================================================================================================================
	_texturePNGExists = done;
}

int Sprite::getNumberOfAnimations()
{ //=========================================================================================================================
	return getAnimationList()->size();
}


//=========================================================================================================================
SpriteAnimationSequence* Sprite::getFirstAnimation()
{ //=========================================================================================================================
	//go through getAnimationList

	if (getAnimationList()->size() > 0)
	{
		return getAnimationByFrame(0); //getAnimationList().get(0);
	}
	else
	{
		getAnimationList()->add(new SpriteAnimationSequence("Default", 0, 0, 0, 0, 0));
		log.warn(string("First animation sequence not found in SpriteAsset: ") + getName());
	}

	return getAnimationList()->get(0);
}

SpriteAnimationSequence* Sprite::getAnimationByName(const string& name)
{ //=========================================================================================================================

	for (int i = 0; i < getAnimationList()->size(); i++)
	{
		if (getAnimationList()->get(i)->frameSequenceName == name)
		{
			return getAnimationList()->get(i);
		}
	}

	return nullptr;
}

SpriteAnimationSequence* Sprite::getAnimationByFrame(int frame)
{ //=========================================================================================================================


	if (getAnimationList()->isEmpty())
	{
		return nullptr;
	}

	SpriteAnimationSequence* a = getAnimationList()->get(0);
	if (a->frameStart == frame)return a;

	for (int i = 0; i < getAnimationList()->size(); i++)
	{
		SpriteAnimationSequence* temp = getAnimationList()->get(i);
		if (temp->frameStart == frame)return temp;
		if (temp->frameStart <= frame && temp->frameStart >= a->frameStart)
		{
			a = temp;
		}
	}

	return a;
}

SpriteAnimationSequence* Sprite::getAnimationByIndex(int index)
{ //=========================================================================================================================
	if (index < 0 || index >= getAnimationList()->size())
	{
		return nullptr;
	}

	return getAnimationList()->get(index);
}

int Sprite::getAnimationNumFramesByIndex(int index)
{ //=========================================================================================================================
	return getAnimationNumFramesByAnimation(getAnimationByIndex(index));
}

int Sprite::getAnimationNumFramesByName(const string& name)
{ //=========================================================================================================================

	return getAnimationNumFramesByAnimation(getAnimationByName(name));
}

int Sprite::getAnimationNumFramesByFrame(int frame)
{ //=========================================================================================================================

	return getAnimationNumFramesByAnimation(getAnimationByFrame(frame));
}



//=========================================================================================================================
int Sprite::getAnimationNumFramesByAnimation(SpriteAnimationSequence* a)
{ //=========================================================================================================================

	if (a == nullptr)
	{
		log.error("Animation was null in getAnimationNumFramesByAnimation");
		return getNumFrames();
	}
	if (a->cachedNumFrames > -1)return a->cachedNumFrames;

	//get animation frames
	int endFrame = getNumFrames();

	for (int i = 0; i < getAnimationList()->size(); i++)
	{
		SpriteAnimationSequence* temp = getAnimationList()->get(i);
		if (temp->frameStart > a->frameStart && temp->frameStart < endFrame)
		{
			endFrame = temp->frameStart;
		}
	}


	a->cachedNumFrames = endFrame - a->frameStart;
	return a->cachedNumFrames;
}

int Sprite::getAnimationIndexByName(const string& name)
{ //=========================================================================================================================

	if (getAnimationList()->isEmpty())
	{
		return -1;
	}

	for (int i = 0; i < getAnimationList()->size(); i++)
	{
		if (getAnimationList()->get(i)->frameSequenceName == name)
		{
			return i;
		}
	}

	return -1;
}

int Sprite::getAnimationIndexByAnimation(SpriteAnimationSequence* a)
{ //=========================================================================================================================

	for (int i = 0; i < getAnimationList()->size(); i++)
	{
		if (getAnimationList()->get(i) == a)
		{
			return i;
		}
	}

	return -1;
}

int Sprite::getAnimationIndexByFrame(int frame)
{ //=========================================================================================================================

	return getAnimationIndexByAnimation(getAnimationByFrame(frame));
}

string Sprite::getAnimationNameByIndex(int index)
{ //=========================================================================================================================
	if (index < 0 || index >= getAnimationList()->size())
	{
		return "";
	}

	return getAnimationList()->get(index)->frameSequenceName;
}

string Sprite::getAnimationNameByFrame(int frame)
{ //=========================================================================================================================

	return getAnimationNameByIndex(getAnimationIndexByFrame(frame));
}

void Sprite::antialiasBufferedImage(BufferedImage* bufferedImage)
{ //===============================================================================================

	//go through hq2x image
	//if pixel is transparent, and the pixel right and down, down and left, left and up, or up and right are black, this one is black

	//have to make a copy otherwise the algorithm becomes recursive
	BufferedImage* copy = new BufferedImage(bufferedImage->getWidth(), bufferedImage->getHeight(), BufferedImage::TYPE_INT_ARGB);
	for (int y = 0; y < bufferedImage->getHeight(); y++)
	{
		for (int x = 0; x < bufferedImage->getWidth(); x++)
		{
			copy->setRGB(x, y, bufferedImage->getRGB(x, y));
		}
	}

	int clear = (new BobColor(0, 0, 0, 0))->getRGB();

	for (int y = 0; y < bufferedImage->getHeight(); y++)
	{
		for (int x = 0; x < bufferedImage->getWidth(); x++)
		{
			if (copy->getRGB(x, y) == clear)
			{
				int black = 0;

				//check right and down
				if (x + 1 < bufferedImage->getWidth() && y + 1 < bufferedImage->getHeight())
				{
					if (copy->getRGB(x + 1, y) != clear && copy->getRGB(x, y + 1) != clear)
					{
						black = 1;
					}
				}

				//check right and up
				if (x + 1 < bufferedImage->getWidth() && y - 1 >= 0)
				{
					if (copy->getRGB(x + 1, y) != clear && copy->getRGB(x, y - 1) != clear)
					{
						black = 1;
					}
				}


				//check left and down
				if (x - 1 >= 0 && y + 1 < bufferedImage->getHeight())
				{
					if (copy->getRGB(x - 1, y) != clear && copy->getRGB(x, y + 1) != clear)
					{
						black = 1;
					}
				}

				//check left and up
				if (x - 1 >= 0 && y - 1 >= 0)
				{
					if (copy->getRGB(x - 1, y) != clear && copy->getRGB(x, y - 1) != clear)
					{
						black = 1;
					}
				}

				if (black == 1)
				{
					bufferedImage->setRGB(x, y, (new BobColor(0, 0, 0, 127))->getRGB());
				}
			}
		}
	}
}

void Sprite::setHQ2XAlphaFromOriginal(BufferedImage* hq2xBufferedImage, BufferedImage* bufferedImage)
{ //===============================================================================================
	//now go through original image again. take each transparent pixel and set the hq2x one with it at 2x
	for (int y = 0; y < bufferedImage->getHeight(); y++)
	{
		for (int x = 0; x < bufferedImage->getWidth(); x++)
		{
			if (bufferedImage->getRGB(x, y) == 0)
			{
				for (int xx = 0; xx < 2; xx++)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						hq2xBufferedImage->setRGB((x * 2) + xx, ((y * 2) + yy), (new BobColor(0, 0, 0, 0))->getRGB());
					}
				}
			}
		}
	}
}

/*
*

public void outputHQ2XPNG(String dirpath)
{

//---------------------------
//create directory if doesn't exist
//---------------------------
if(dirpath==null)dirpath = System.getProperties().getProperty("user.home")+"\\Desktop\\bgEditor_Output\\";
CacheManager.makeDir(dirpath + "png\\sprite\\");


int w = (getWidthPixelsHQ/2);
int h = (getHeightPixelsHQ/2);

//---------------------------
//make bufferedimage the size of all sprite frames and fill it
//---------------------------
//BufferedImage bufferedImage = (new Frame()).getGraphicsConfiguration().createCompatibleImage(width, (height) * num_Frames, Transparency.TRANSLUCENT);
BufferedImage bufferedImage = new BufferedImage( w, h * frames, BufferedImage.TYPE_INT_ARGB);
for(int f = 0; f < frames; f++)
{
for(int y = 0; y < h; y++)
{
for(int x = 0; x < w; x++)
{
if(getPixel(f, x, y)!=0)
bufferedImage.setRGB(x, y + (h * f), (E.project.getSelectedSpritePalette().getColor(getPixel(f, x, y))).getRGB());
}
}
}

BufferedImage hq2xBufferedImage = new HQ2X().HQ2X(bufferedImage);

setHQ2XAlphaFromOriginal(hq2xBufferedImage,bufferedImage);

antialiasBufferedImage(hq2xBufferedImage);

bufferedImage = hq2xBufferedImage;

//---------------------------
//save to png
//---------------------------

CacheManager.saveImage(dirpath + "png\\sprite\\" + name + "_Sprite_HQ2X_" + width*2 + "x" + height*2 + "x" + num_Frames + ".png",bufferedImage);


//---------------------------
//write shadow frames
//---------------------------

bufferedImage = new BufferedImage(width, height* num_Frames, BufferedImage.TYPE_INT_ARGB);
for(int f = 0; f < num_Frames; f++)
{
for(int y = 0; y < height; y++)
{
for(int x = 0; x < width; x++)
{
if(getPixel(f, x, y)!=0)
{

int bottom_pixel_y=height-1;

//find bottom pixel to start copying shadow from so feet are exactly at the top of the frame
for(int yy=height-1;yy>=0;yy--)
for(int xx=0;xx<width;xx++)
{

if(getPixel(f, xx, yy)!=0)
{
bottom_pixel_y = yy;
yy=-1;
break;
}
}

//since we're not copying from the bottom, we need to stop when we reach the top, not copy the full height
if(bottom_pixel_y-y<0)
{
y=height;
break;
}

int nx = x;
int ny = (height * f) + ((bottom_pixel_y)-y);
int col = Color.black.getRGB();

bufferedImage.setRGB(nx, ny, col);
}
}
}
}

BufferedImage hq2xShadowBufferedImage = new HQ2X().HQ2X(bufferedImage);

setHQ2XAlphaFromOriginal(hq2xShadowBufferedImage,bufferedImage);

antialiasBufferedImage(hq2xShadowBufferedImage);

bufferedImage = hq2xShadowBufferedImage;
//---------------------------
//save to png
//---------------------------

CacheManager.saveImage(dirpath + "png\\sprite\\" + name + "_SpriteShadow_HQ2X_" + width*2 + "x" + height*2 + "x" + num_Frames + ".png",bufferedImage);


}
*/

SpriteData* Sprite::getData()
{
	return data;
}

int Sprite::getID()
{
	return getData()->getID();
}

string Sprite::getName()
{
	return getData()->getName();
}

string Sprite::getTYPEIDString()
{
	return getData()->getTYPEIDString();
}

string Sprite::getDataMD5()
{
	return getData()->getDataMD5();
}

string Sprite::getPaletteMD5()
{
	return getData()->getPaletteMD5();
}

string Sprite::getComment()
{
	return getData()->getComment();
}

int Sprite::getImageWidth()
{
	return getData()->getWidthPixels1X();
}

int Sprite::getImageHeight()
{
	return getData()->getHeightPixels1X();
}

int Sprite::getScreenWidth()
{
	return getData()->getWidthPixelsHQ();
}

int Sprite::getScreenHeight()
{
	return getData()->getHeightPixelsHQ();
}

int Sprite::getNumFrames()
{
	return getData()->getNumFrames();
}

string Sprite::getDisplayName()
{
	return getData()->getDisplayName();
}

bool Sprite::getIsNPC()
{
	return getData()->getIsNPC();
}

bool Sprite::getIsKid()
{
	return getData()->getIsKid();
}

bool Sprite::getIsAdult()
{
	return getData()->getIsAdult();
}

bool Sprite::getIsMale()
{
	return getData()->getIsMale();
}

bool Sprite::getIsFemale()
{
	return getData()->getIsFemale();
}

bool Sprite::getIsCar()
{
	return getData()->getIsCar();
}

bool Sprite::getIsAnimal()
{
	return getData()->getIsAnimal();
}

bool Sprite::getHasShadow()
{
	return getData()->getHasShadow();
}

bool Sprite::getIsRandom()
{
	return getData()->getIsRandom();
}

bool Sprite::getIsDoor()
{
	return getData()->getIsDoor();
}

bool Sprite::getIsGame()
{
	return getData()->getIsGame();
}

bool Sprite::getIsItem()
{
	return getData()->getIsItem();
}

bool Sprite::getForceHQ2X()
{
	return getData()->getForceHQ2X();
}

bool Sprite::getForceMD5Export()
{
	SpriteData* s = getData();
	return s->getForceMD5Export();
}

int Sprite::getEventID()
{
	SpriteData* s = getData();
	return s->getEventID();
}

string Sprite::getItemGameDescription()
{
	SpriteData* s = getData();
	return s->getItemGameDescription();
}

float Sprite::getGamePrice()
{
	SpriteData* s = getData();
	return s->getGamePrice();
}

int Sprite::getUtilityOffsetXPixelsHQ()
{
	SpriteData* s = getData();
	return s->getUtilityOffsetXPixelsHQ();
}

int Sprite::getUtilityOffsetYPixelsHQ()
{
	SpriteData* s = getData();
	return s->getUtilityOffsetYPixelsHQ();
}

ArrayList<SpriteAnimationSequence*>* Sprite::getAnimationList()
{
	SpriteData* s = getData();


	return s->getAnimationList();
}

