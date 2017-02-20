#pragma once
#include "bobtypes.h"
class Logger;



	class BobTexture
	{



	public:
		static BobTexture *lastBoundTexture;

		static BobTexture *getLastBoundTexture();


	private:
		int glTargetType = 0;
		GLuint textureID = 0;

		int imageHeight = 0;
		int imageWidth = 0;

		int texWidth = 0;
		int texHeight = 0;

		//The ratio of the width of the image to the texture
		float widthRatio = 0;

		// The ratio of the height of the image to the texture
		float heightRatio = 0;

		bool alpha = false;

	
		// The name the texture has in the cache
		string cacheName = "";



	public:

		BobTexture(const string &ref, GLuint textureID);


		virtual bool hasAlpha();


		virtual void setAlpha(bool alpha);


		//Clear the binding of the texture
		static void bindNone();


		//Clear caching of the last bound texture so that an external texture binder can play with the context before returning control to slick.
		static void unbind();

		virtual void bind();

		//Set the height of the image
		virtual void setImageHeight(int height);


		//Set the width of the image
		virtual void setImageWidth(int width);

		virtual int getImageHeight();

		virtual int getImageWidth();

		virtual float getHeightRatio();


		virtual float getWidthRatio();

		virtual int getTextureHeight();

		virtual int getTextureWidth();

		virtual void setTextureHeight(int texHeight);

		virtual void setTextureWidth(int texWidth);

		

	private:
		//Set the height of the texture. This will update the ratio also.
		void setHeightRatio();


		//Set the width of the texture. This will update the ratio also.
		void setWidthRatio();

	public:
		virtual void release();

		virtual GLuint getTextureID();

		virtual void setTextureID(GLuint textureID);


	public:
		u8* getTextureData();
	};
