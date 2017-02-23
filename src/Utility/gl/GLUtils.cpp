#include "stdafx.h"
#include <iostream>

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

Logger GLUtils::log = Logger("GLUtils");

//#define SDL_STBIMAGE_IMPLEMENTATION
//#include "../../../lib/SDL_stbimage.h"
//#define STB_IMAGE_IMPLEMENTATION

HashMap<string, BobTexture*> GLUtils::textureCache;

//-----------------------------------------------
//OLD STUFF
//-----------------------------------------------

SDL_Window *GLUtils::window = nullptr;
SDL_Renderer *GLUtils::renderer = nullptr;

void(*glDrawTexiES)(int, int, int, int, int);

//unsigned char* GLUtils::rgba_fbo_data = NULL; //framebuffer array
//unsigned char* GLUtils::filtered_rgba_fbo_data = NULL;

Uint32 GLUtils::rmask = 0;
Uint32 GLUtils::gmask = 0;
Uint32 GLUtils::bmask = 0;
Uint32 GLUtils::amask = 0;

//-----------------------------
//render flags
//-----------------------------
//bool GLUtils::framebuffer = true;

//bool GLUtils::GLOBAL_bg_layer_enabled[4] = { true,true,true,true };
//bool GLUtils::GLOBAL_sprite_layer_enabled = true;

//int GLUtils::fade_alpha = 0;
//int GLUtils::fade_layer = 0;

int GLUtils::GLOBAL_FRAMEBUFFER_FILTER_TYPE = GL_LINEAR;

//int GLUtils::fade_vbl_counter = 0;

SDL_Surface GLUtils::SDLSurface_screen;


bool GLUtils::ZOOMlock = 0;

float GLUtils::ZOOM = 1.0f;
float GLUtils::ZOOMto = 1.0f;

//-----------------------------------------------
//END OLD STUFF
//-----------------------------------------------

bool GLUtils::antiAlias = true;
int GLUtils::texturesLoaded = 0;
long long GLUtils::textureBytesLoaded = 0;
BobTexture* GLUtils::blankTexture = nullptr;
BobTexture* GLUtils::boxTexture = nullptr;
float GLUtils::globalDrawScale = 1.0f;


BobTexture* GLUtils::rect = nullptr;


//static float* boxBuffer = BufferUtils.newFloatBuffer(12);
//static float* colBuffer = BufferUtils.newFloatBuffer(16);
//static float* texBuffer = BufferUtils.newFloatBuffer(8);

GLfloat* GLUtils::box = new GLfloat[12];
GLfloat* GLUtils::col = new GLfloat[16];
GLfloat* GLUtils::tex = new GLfloat[8];

int GLUtils::windowWidth = 0;
int GLUtils::windowHeight = 0;

int GLUtils::lastWindowWidth = 0;
int GLUtils::lastWindowHeight = 0;

SDL_DisplayMode GLUtils::currentDisplayMode;
ArrayList<SDL_DisplayMode*> GLUtils::displayModes;
int GLUtils::monitorWidth = 0;
int GLUtils::monitorHeight = 0;

//int GLUtils::getViewportWidth() = 1280;
//int GLUtils::getViewportHeight() = 720;


bool GLUtils::usingVSync = true;
bool GLUtils::disableVSync = false;
bool GLUtils::noVSync_UpdateAndRenderEveryFrame = false;
bool GLUtils::noVSync_DelayOff = true;


bool GLUtils::useShaders = true;
int GLUtils::lightShader = 0;
int GLUtils::colorShader = 0;

GLuint GLUtils::gaussianShader = 0;
GLuint GLUtils::bloomMaskShader = 0;
GLuint GLUtils::bloomShader = 0;
//bool GLUtils::useFBO = true;
int GLUtils::glVersionMajor = 0;




GLuint GLUtils::postColorFilterFBO = 0;
GLuint GLUtils::postColorFilterFBO_Texture_Attachment0 = 0;
GLuint GLUtils::postColorFilterFBO_Texture_Attachment1_PreLighting = 0;

GLuint GLUtils::preColorFilterFBO = 0;
GLuint GLUtils::preColorFilterFBO_Texture_Attachment0 = 0;
GLuint GLUtils::preColorFilterFBO_Texture_Attachment1_BloomMask = 0;


GLuint GLUtils::bobsGame_mainGameFBO = 0;
GLuint GLUtils::bobsGame_mainGameFBO_Texture_Attachment0 = 0;
GLuint GLUtils::bobsGame_mainGameFBO_Texture_Attachment1_BloomMask = 0;

GLuint GLUtils::bobsGame_bloomFBO = 0;
GLuint GLUtils::bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0 = 0;
GLuint GLUtils::bobsGame_bloomFBO_PingPongBlur_Texture_Attachment1 = 0;

int GLUtils::bobsGameFBO_Width = 0;
int GLUtils::bobsGameFBO_Height = 0;


GLuint GLUtils::bobsGame_bgShaderFBO = 0;
GLuint GLUtils::bobsGame_bgShaderFBO_Texture_Attachment0 = 0;
GLuint GLUtils::bobsGame_bgShaderFBO_Texture_Attachment1 = 0;








ArrayList<Integer*> GLUtils::bgShaders;
//ArrayList<int> GLUtils::bgShaders;
int GLUtils::bgShaderCount = 80;

//=========================================================================================================================
GLUtils::GLUtils()
{//=========================================================================================================================

}

//=========================================================================================================================
void GLUtils::cleanup()
{//=========================================================================================================================

}


//=========================================================================================================================
void GLUtils::initGL(char* windowName)
{ //=========================================================================================================================

	//-----------------------------
	//set up display mode
	//-----------------------------

	SDL_DisplayMode dm;
	if (SDL_GetDesktopDisplayMode(0, &dm) != 0) 
	{
		SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
	}
	monitorWidth = dm.w;
	monitorHeight = dm.h;
	log.debug("Desktop display mode is "+to_string(dm.w)+"x" + to_string(dm.h) + "px @ " + to_string(dm.refresh_rate) + "hz.");


	checkSDLError("Get desktop display mode");

	getAvailableDisplayModes();

	//-----------------------------
	//set up window
	//-----------------------------

	//	setTitle(windowName); //ULTRA \"bob's game\" ONLINE");//world of \"bob's game\"");


	log.info("Setting up SDL window...");

	window = SDL_CreateWindow(windowName,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		(int)monitorWidth/2, (int)monitorHeight/2,
//#ifndef _DEBUG
//		SDL_WINDOW_FULLSCREEN_DESKTOP |
//#endif
		SDL_WINDOW_RESIZABLE |
		SDL_WINDOW_OPENGL);
	checkSDLError("SDL_CreateWindow");

	string path = Main::getPath() + "bobsgame.bmp";
	SDL_SetWindowIcon(window, SDL_LoadBMP(path.c_str()));
	checkSDLError("SDL_SetWindowIcon");

	if (window == nullptr)
	{
		cerr << "There was an error creating the window: " << SDL_GetError() << endl;
		exit(1);
	}

	getCurrentDisplayMode();

	SDL_GetWindowSize(window,&windowWidth,&windowHeight);


	log.info("Window Width: " + to_string(windowWidth));
	log.info("Window Height: " + to_string(windowHeight));

	//-----------------------------
	//set up GL
	//-----------------------------

	log.info("Setting up GL context...");


	//						  //if we want to disable deprecated GL functions below GL 3.3
	//						  //			ContextAttribs ctxAttr = new ContextAttribs(3, 3);
	//						  //			ctxAttr = ctxAttr.withForwardCompatible(true);
	//						  //			ctxAttr = ctxAttr.withProfileCore(true);
	//						  //			ctxAttr = ctxAttr.withProfileCompatibility(false);
	//						  //			ctxAttr = ctxAttr.withDebug(true);
	//
	//	createGLContext(); //new PixelFormat(),ctxAttr);

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	if (context == nullptr)
	{
		cerr << "There was an error creating OpenGL context: " << SDL_GetError() << endl;
		exit(1);
	}

	const unsigned char* version = glGetString(GL_VERSION);
	if (version == nullptr)
	{
		cerr << "There was an error with OpenGL configuration:" << endl;
		exit(1);
	}

	e("Created GL Context");

	SDL_GL_MakeCurrent(window, context);

	e("SDL_GL_MakeCurrent");
	

	SDL_ShowCursor(1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	//set screen black here and swap buffer before loading
	SDL_GL_SwapWindow(window);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif


	log.info("GL info");

	//log.info(string((char*)(nullptr)));
	char* vendorString = (char*)glGetString(GL_VENDOR);
	char* versionString = (char*)glGetString(GL_VERSION);
	char* rendererString = (char*)glGetString(GL_RENDERER);
	char* shaderVersionString = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	char* extensionsString = (char*)glGetString(GL_EXTENSIONS);

	if (vendorString !=NULL)log.info(string("GL vendor: ") + string(vendorString));
	if (versionString != NULL)log.info(string("GL version: ") + string(versionString));
	if (rendererString != NULL)log.info(string("Renderer: ") + string(rendererString));
	if (shaderVersionString != NULL)log.info(string("Shader version: ") + string(shaderVersionString));
	if (extensionsString != NULL)log.info(string("Extensions: ") + string(extensionsString));

	int redBits;
	int greenBits;
	int blueBits;
	int alphaBits;
	int depthBits;
	int stencilBits;
	int maxTextureSize;
	int maxLights;
	int maxAttribStacks;
	int maxModelViewStacks;
	int maxProjectionStacks;
	int maxClipPlanes;
	int maxTextureStacks;

	// get number of color bits
	glGetIntegerv(GL_RED_BITS, &redBits);
	glGetIntegerv(GL_GREEN_BITS, &greenBits);
	glGetIntegerv(GL_BLUE_BITS, &blueBits);
	glGetIntegerv(GL_ALPHA_BITS, &alphaBits);

	// get depth bits
	glGetIntegerv(GL_DEPTH_BITS, &depthBits);

	// get stecil bits
	glGetIntegerv(GL_STENCIL_BITS, &stencilBits);

	// get max number of lights allowed
	glGetIntegerv(GL_MAX_LIGHTS, &maxLights);

	// get max texture resolution
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);

	// get max number of clipping planes
	glGetIntegerv(GL_MAX_CLIP_PLANES, &maxClipPlanes);

	// get max modelview and projection matrix stacks
	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &maxModelViewStacks);
	glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &maxProjectionStacks);
	glGetIntegerv(GL_MAX_ATTRIB_STACK_DEPTH, &maxAttribStacks);

	// get max texture stacks
	glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH, &maxTextureStacks);


	log.info("Color Bits(R,G,B,A): (" + to_string(redBits) + ", " + to_string(greenBits)+ ", " + to_string(blueBits) + ", " + to_string(alphaBits) + ")");
	log.info("Depth Bits: " + to_string(depthBits));
	log.info("Stencil Bits: " + to_string(stencilBits));
	log.info("Max Texture Size: " + to_string(maxTextureSize) + "x" + to_string(maxTextureSize));
	log.info("Max Lights: " + to_string(maxLights));
	log.info("Max Clip Planes: " + to_string(maxClipPlanes));
	log.info("Max Modelview Matrix Stacks: " + to_string(maxModelViewStacks));
	log.info("Max Projection Matrix Stacks: " + to_string(maxProjectionStacks));
	log.info("Max Attribute Stacks: " + to_string(maxAttribStacks));
	log.info("Max Texture Stacks: " + to_string(maxTextureStacks));

	
	//-----------------------------
	//set up GL state
	//-----------------------------
	log.info("Setting up GL state...");

	//NEW GL SETUP---------------------------------------------------------------

	//glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	//glEnable(GL_LINE_SMOOTH);
	//glShadeModel(GL_SMOOTH);
	glColor4f(1, 1, 1, 1);

	//glColor4f(0.0f,0.0f,0.0f,0.0f);
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//GLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClearDepth(1);


	glDisable(GL_SCISSOR_TEST);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	//glPushAttrib(GL_ENABLE_BIT|GL_TRANSFORM_BIT|GL_HINT_BIT|GL_COLOR_BUFFER_BIT|GL_SCISSOR_BIT|GL_LINE_BIT|GL_TEXTURE_BIT);

	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	//glLoadIdentity();

	setPostColorFilterViewport();
//	{
//		glViewport(0, 0, getViewportWidth(), getViewportHeight());
//		glLoadIdentity();
//		glOrtho(0, getViewportWidth(), getViewportHeight(), 0, -1, 1);
//	}

	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glLoadIdentity();
	//glViewport(0, 0, getViewportWidth(), getViewportHeight());



	//OLD GL SETUP---------------------------------------------------------------
	//	glMatrixMode(GL_PROJECTION);
	//	glLoadIdentity();
	//	glOrtho(0, getViewportWidth(), getViewportHeight(), 0, -1, 1);
	//
	//	glViewport(0, 0, (GLsizei)getViewportWidth(), (GLsizei)getViewportHeight());
	//
	//	glMatrixMode(GL_MODELVIEW);
	//	glLoadIdentity();
	//	glClearColor(0, 0, 0, 0);
	//	glDisable(GL_DEPTH_TEST);
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	//	glGenTextures(1, &screen); // make a new texture

	e("Set GL state");



	//-----------------------------
	//set up swap
	//-----------------------------

	log.info("Setting up swap...");


	glewInit();

    usingVSync=false;

#ifdef __WINDOWS__

	if (wglewIsSupported("WGL_EXT_swap_control_tear")
		|| WGLEW_EXT_swap_control_tear
		)
	{
		wglSwapIntervalEXT(-1);//adaptive vsync, see -1
		usingVSync=true;
		log.info("Adaptive vsync supported.");

		if(disableVSync)
		{
			wglSwapIntervalEXT(0);
			usingVSync = false;
		}
	}
	else
	if (wglewIsSupported("WGL_EXT_swap_control")
		|| WGLEW_EXT_swap_control
		)
	{
		wglSwapIntervalEXT(1);
	    usingVSync=true;

		if (disableVSync)
		{
			wglSwapIntervalEXT(0);
			usingVSync = false;
		}
	}
	else
	{
		string extensions = string((char*)(glGetString(GL_EXTENSIONS)));


		if (extensions.find("WGL_EXT_swap_control_tear") != string::npos//adaptive vsync
			|| WGLEW_EXT_swap_control_tear
			)
		{
			wglSwapIntervalEXT(-1);//adaptive vsync, see -1
			usingVSync = true;
			log.info("Adaptive vsync supported.");

			if (disableVSync)
			{
				wglSwapIntervalEXT(0);
				usingVSync = false;
			}
		}
		else
			if (extensions.find("WGL_EXT_swap_control") != string::npos
				|| WGLEW_EXT_swap_control
				)
			{
				wglSwapIntervalEXT(1);
				usingVSync = true;

				if (disableVSync)
				{
					wglSwapIntervalEXT(0);
					usingVSync = false;
				}
			}


	}

#endif
#if defined(__LINUX__)

	if (glxewIsSupported("GLX_EXT_swap_control_tear")
		|| GLXEW_EXT_swap_control_tear
		)
	{
		glXSwapIntervalEXT(glXGetCurrentDisplay(),glXGetCurrentDrawable(),-1);//adaptive vsync, see -1
		usingVSync=true;
		log.info("Adaptive vsync supported.");

		if (disableVSync)
		{
			glXSwapIntervalEXT(glXGetCurrentDisplay(), glXGetCurrentDrawable(), 0);
			usingVSync = false;
		}
	}
	else
	if (glxewIsSupported("GLX_EXT_swap_control")
		|| GLXEW_EXT_swap_control
		)
	{
		glXSwapIntervalEXT(glXGetCurrentDisplay(),glXGetCurrentDrawable(),1);
		usingVSync=true;
		log.info("GLX_EXT_swap_control supported.");

		if (disableVSync)
		{
			glXSwapIntervalEXT(glXGetCurrentDisplay(), glXGetCurrentDrawable(), 0);
			usingVSync = false;
		}
	}
	else
	if (glxewIsSupported("GLX_SGI_swap_control")
		|| GLXEW_SGI_swap_control
		)
	{
		glXSwapIntervalSGI(1);
		usingVSync=true;
		log.info("GLX_SGI_swap_control supported.");

		if (disableVSync)
		{
			glXSwapIntervalSGI(0);
			usingVSync = false;
		}
	}
	else
	{

		string extensions =  glXQueryExtensionsString(glXGetCurrentDisplay(), 0);

		if (extensions.find("GLX_EXT_swap_control_tear") != string::npos//adaptive vsync
			)
		{
			glXSwapIntervalEXT(glXGetCurrentDisplay(),glXGetCurrentDrawable(),-1);//adaptive vsync, see -1
			usingVSync=true;
			log.info("Adaptive vsync supported.");

			if (disableVSync)
			{
				glXSwapIntervalEXT(glXGetCurrentDisplay(), glXGetCurrentDrawable(), 0);
				usingVSync = false;
			}
		}
		else
		if (extensions.find("GLX_EXT_swap_control") != string::npos
			)
		{
			glXSwapIntervalEXT(glXGetCurrentDisplay(),glXGetCurrentDrawable(),1);
			usingVSync=true;
			log.info("GLX_EXT_swap_control supported.");

			if (disableVSync)
			{
				glXSwapIntervalEXT(glXGetCurrentDisplay(), glXGetCurrentDrawable(), 0);
				usingVSync = false;
			}
		}
		else
		if (extensions.find("GLX_SGI_swap_control") != string::npos
			)
		{
			glXSwapIntervalSGI(1);
			usingVSync=true;
			log.info("GLX_SGI_swap_control supported.");

			if (disableVSync)
			{
				glXSwapIntervalSGI(0);
				usingVSync = false;
			}
		}

	}

#endif
#if defined(__MACOSX__)
    {
        //GLint sync = 1;
        
        //usingVSync = false;
        
        if(SDL_GL_SetSwapInterval(-1)==-1)
        {
            if(SDL_GL_SetSwapInterval(1)==-1)
            {
                usingVSync = false;
            }
            else
            {
                usingVSync=true;
                log.info("Vsync supported.");
            }
        }
        else
        {
            usingVSync=true;
            log.info("Adaptive vsync supported.");

        }
        //#include <OpenGL/OpenGL.h>
        // ctx must be a valid context
        //CGLGetCurrentContext();
        //SDL_GL_GetCurrentContext();
        //CGLSetParameter (context, kCGLCPSwapInterval, &sync);
    }
    
#endif
	e("Vsync check");

	if (usingVSync)log.info("Using vsync.");
	else log.warn("No vsync.");


	//-----------------------------
	//set up framebuffer
	//-----------------------------

	log.info("Setting up FBO...");


	//ARB is newer than EXT for some reason I think, uses glFramebuffer() and not glFramebufferEXT()
	if (glewIsSupported("GL_ARB_framebuffer_object")
		|| GLEW_ARB_framebuffer_object
		)
	{
		//useFBO = true;
		ARBFBO = true;

		log.info("GL_ARB_framebuffer_object supported.");
	}
	else
	{
		if (glewIsSupported("GL_EXT_framebuffer_object")
			|| GLEW_EXT_framebuffer_object
			)
		{
			//useFBO = true;
			ARBFBO = false;

			log.info("GL_ARB_framebuffer_object not supported. Using GL_EXT_framebuffer_object.");
		}

		else
		{
			log.warn("FBO not supported.");

			log.info("This game requires a newer graphics card that supports FBO.");
			Caption* c = new Caption(nullptr, (int)(Caption::CENTERED_SCREEN), 0, -1, "This game requires a newer graphics card that supports FBO.", BobFont::ttf_12, BobColor::white, BobColor::black);

			System::updateRenderTimers();
			System::updateDebugInfo();
			System::updateUpdateTimers();
			c->update();
			c->render();

			Main::delay(5000);
			Main::quit = true;
			return;
			//useFBO = false;

		}
	}


	//if (GLUtils::useFBO)
	{
		//generate FBOs
		postColorFilterFBO = GLUtils::genFBO();
		GLUtils::bindFBO(postColorFilterFBO);

		GLuint texID;
		glGenTextures(1, &texID);
		postColorFilterFBO_Texture_Attachment0 = GLUtils::setupFBOTexture(texID, getViewportWidth(), getViewportHeight());
		GLUtils::attachTextureToFBO(0, postColorFilterFBO_Texture_Attachment0);

		glGenTextures(1, &texID);
		postColorFilterFBO_Texture_Attachment1_PreLighting = GLUtils::setupFBOTexture(texID, getViewportWidth(), getViewportHeight());
		GLUtils::attachTextureToFBO(1, postColorFilterFBO_Texture_Attachment1_PreLighting);


		//=================================


		preColorFilterFBO = GLUtils::genFBO();
		GLUtils::bindFBO(preColorFilterFBO);

		glGenTextures(1, &texID);
		preColorFilterFBO_Texture_Attachment0 = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE));
		GLUtils::attachTextureToFBO(0, preColorFilterFBO_Texture_Attachment0);

		glGenTextures(1, &texID);
		preColorFilterFBO_Texture_Attachment1_BloomMask = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE));
		GLUtils::attachTextureToFBO(1, preColorFilterFBO_Texture_Attachment1_BloomMask);

		//=================================


		bobsGame_mainGameFBO = GLUtils::genFBO();
		GLUtils::bindFBO(bobsGame_mainGameFBO);

		glGenTextures(1, &texID);
		bobsGame_mainGameFBO_Texture_Attachment0 = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE));
		GLUtils::attachTextureToFBO(0, bobsGame_mainGameFBO_Texture_Attachment0);

		glGenTextures(1, &texID);
		bobsGame_mainGameFBO_Texture_Attachment1_BloomMask = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE));
		GLUtils::attachTextureToFBO(1, bobsGame_mainGameFBO_Texture_Attachment1_BloomMask);


		bobsGameFBO_Width = getViewportWidth() * GLUtils::FBO_SCALE;
		bobsGameFBO_Height = getViewportHeight() * GLUtils::FBO_SCALE;

		//=================================


		bobsGame_bloomFBO = GLUtils::genFBO();
		GLUtils::bindFBO(bobsGame_bloomFBO);

		glGenTextures(1, &texID);
		bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0 = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE * GLUtils::BLOOM_FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE * GLUtils::BLOOM_FBO_SCALE));
		GLUtils::attachTextureToFBO(0, bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0);

		glGenTextures(1, &texID);
		bobsGame_bloomFBO_PingPongBlur_Texture_Attachment1 = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE * GLUtils::BLOOM_FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE * GLUtils::BLOOM_FBO_SCALE));
		GLUtils::attachTextureToFBO(1, bobsGame_bloomFBO_PingPongBlur_Texture_Attachment1);

		

		//=================================


		bobsGame_bgShaderFBO = GLUtils::genFBO();
		GLUtils::bindFBO(bobsGame_bgShaderFBO);

		glGenTextures(1, &texID);
		bobsGame_bgShaderFBO_Texture_Attachment0 = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth()* GLUtils::FBO_SCALE*GLUtils::SHADER_FBO_SCALE ), (int)(getViewportHeight() * GLUtils::FBO_SCALE*GLUtils::SHADER_FBO_SCALE));
		GLUtils::attachTextureToFBO(0, bobsGame_bgShaderFBO_Texture_Attachment0);

		glGenTextures(1, &texID);
		bobsGame_bgShaderFBO_Texture_Attachment1 = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth()* GLUtils::FBO_SCALE*GLUtils::SHADER_FBO_SCALE ), (int)(getViewportHeight() * GLUtils::FBO_SCALE*GLUtils::SHADER_FBO_SCALE));
		GLUtils::attachTextureToFBO(1, bobsGame_bgShaderFBO_Texture_Attachment1);


		//bind the depth renderbuffer
		//glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBufferID);
		//get the data space for it
		//glRenderbufferStorage(GL_RENDERBUFFER, GL14.GL_DEPTH_COMPONENT24, 512, 512);
		//bind it to the renderbuffer
		//glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER, depthRenderBufferID);

		//switch back to normal framebuffer
		GLUtils::bindFBO(0);

		e();

		e("Framebuffer creation");

	}




	//-----------------------------
	//set up shaders
	//-----------------------------

	log.info("Setting up shaders...");


	string glVersion = string((char*)glGetString(GL_VERSION));
	
	try
	{
		glVersionMajor = stoi(glVersion.substr(0, glVersion.find(".")));
	}
	catch (exception)
	{
		log.error("Could not parse glVersionMajor in initGL");
	}

	log.info(string("glVersionMajor:") + to_string(glVersionMajor));

	if (glVersionMajor < 2)
	{
		useShaders = false;
	}

	if (useShaders)
	{

		//String shaderVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
		//String glExtensions = glGetString(GL_EXTENSIONS);

		GLboolean hasARBShadingLanguage100 = glewIsSupported("GL_ARB_shading_language_100");//alt: if(GLEW_ARB_shading_language_100); notice replace GL_ with GLEW_
		GLboolean hasARBFragmentShader = glewIsSupported("GL_ARB_fragment_shader");
		GLboolean hasARBVertexShader = glewIsSupported("GL_ARB_vertex_shader");
		GLboolean hasARBShaderObjects = glewIsSupported("GL_ARB_shader_objects");
		GLboolean hasARBFragmentProgram = glewIsSupported("GL_ARB_fragment_program");
		GLboolean hasNVVertexProgram3 = glewIsSupported("GL_NV_vertex_program3");
		GLboolean hasNVGPUProgram4 = glewIsSupported("GL_NV_gpu_program4");


		//			boolean extensionsStringHasARBShadingLanguage = glExtensions.contains("GL_ARB_shading_language_100");
		//			boolean extensionsStringHasARBFragmentShader = glExtensions.contains("GL_ARB_fragment_shader");
		//			boolean extensionsStringHasARBVertexShader = glExtensions.contains("GL_ARB_vertex_shader");
		//			boolean extensionsStringHasARBShaderObjects = glExtensions.contains("GL_ARB_shader_objects");
		//			boolean extensionsStringHasARBFragmentProgram = glExtensions.contains("GL_ARB_fragment_program");
		//			boolean extensionsStringHasNVVertexProgram3 = glExtensions.contains("GL_NV_vertex_program3");
		//			boolean extensionsStringHasNVGPUProgram4 = glExtensions.contains("GL_NV_gpu_program4");

		log.info(string("Shader version: ") + string((char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));

		log.info(string("hasARBShadingLanguage100 (GLSL 1.00):") + to_string(hasARBShadingLanguage100));
		log.info(string("hasARBFragmentShader (GLSL 1.00):") + to_string(hasARBFragmentShader));
		log.info(string("hasARBVertexShader (GLSL 1.00):") + to_string(hasARBVertexShader));
		log.info(string("hasARBShaderObjects (GLSL 1.00):") + to_string(hasARBShaderObjects));
		log.info(string("shadingVersionExists (GLSL 1.051):") + to_string((string((char*)(glGetString(GL_SHADING_LANGUAGE_VERSION))) != ("0"))));

		log.info(string("hasARBFragmentProgram (SM 2):") + to_string(hasARBFragmentProgram));
		log.info(string("hasNVVertexProgram3 (SM 3):") + to_string(hasNVVertexProgram3));
		log.info(string("hasNVGPUProgram4 (SM 4):") + to_string(hasNVGPUProgram4));
		//			log.info("extensionsStringHasARBShadingLanguage:"+extensionsStringHasARBShadingLanguage);
		//			log.info("extensionsStringHasARBFragmentShader:"+extensionsStringHasARBFragmentShader);
		//			log.info("extensionsStringHasARBVertexShader:"+extensionsStringHasARBVertexShader);
		//			log.info("extensionsStringHasARBShaderObjects:"+extensionsStringHasARBShaderObjects);
		//			log.info("extensionsStringHasARBFragmentProgram:"+extensionsStringHasARBFragmentProgram);
		//			log.info("extensionsStringHasNVVertexProgram3:"+extensionsStringHasNVVertexProgram3);
		//			log.info("extensionsStringHasNVGPUProgram4:"+extensionsStringHasNVGPUProgram4);



		//log.debug("createProgramObject");
		lightShader = GLUtils::createProgramObject();
		colorShader = GLUtils::createProgramObject();
		gaussianShader = GLUtils::createProgramObject();
		bloomMaskShader = GLUtils::createProgramObject();
		bloomShader = GLUtils::createProgramObject();
		e("createProgramObject");

		//log.debug("makeShader");
		if (GLUtils::makeShader("lightShader", lightShader, "data/shaders/texCoord.vert", "data/shaders/lightBlend.frag") == false)
		{
			useShaders = false;
		}
		if (GLUtils::makeShader("colorShader", colorShader, "data/shaders/texCoord.vert", "data/shaders/colorAdjust.frag") == false)
		{
			useShaders = false;
		}
		if (GLUtils::makeShader("gaussianShader", gaussianShader, "data/shaders/bloom_blurspace.vert", "data/shaders/bloom_alpha_gaussian.frag") == false)
		{
			useShaders = false;
		}
		if (GLUtils::makeShader("maskShader", bloomMaskShader, "data/shaders/bloom_screenspace.vert", "data/shaders/bloom_alpha_threshold.frag") == false)
		{
			useShaders = false;
		}
		if (GLUtils::makeShader("bloomShader", bloomShader, "data/shaders/bloom_screenspace.vert", "data/shaders/bloom_alpha_bloom.frag") == false)
		{
			useShaders = false;
		}

		//log.debug("createProgramObject bgShaderCount " + to_string(bgShaderCount));
		if (useShaders)
		{
			for (int i = 0; i < bgShaderCount; i++)
			{
				int p = GLUtils::createProgramObject();
				//log.debug("createProgramObject bg " + to_string(p));
				e("createProgramObject");
				bgShaders.add(new Integer(p));
			}

			int count = 0;

			//log.debug("makeShader bg bgShaders size "+to_string(bgShaders.size()));
			for (int i = 0; i < bgShaderCount; i++)
			{
				string name = to_string(count) + string(".frag");
				if (count < 10)
				{
					name = string("0") + name;
				}

				if (GLUtils::makeShader(name, bgShaders.get(i)->value(), "data/shaders/texCoord.vert", string("data/shaders/bg/") + name) == false)
				{
					log.debug("Could not make bg shader "+name);
					bgShaderCount--;
					bgShaders.removeAt(i);
					i--;
				}

				count++;
			}
		}



		//-----------------------------
		//set up shaders
		//-----------------------------
		/*
		char *fs, *vs;

		vert[0] = glCreateShader(GL_VERTEX_SHADER);
		vs = textFileRead("shaders/coord.vert");
		glShaderSource(vert[0], 1, (const char **)&vs, nullptr);
		free(vs);
		glCompileShader(vert[0]);

		frag[0] = glCreateShader(GL_FRAGMENT_SHADER);
		fs = textFileRead("shaders/nothing.frag");
		glShaderSource(frag[0], 1, (const char **)&fs, nullptr);
		free(fs);
		glCompileShader(frag[0]);


		p[0] = glCreateProgram();
		glAttachShader(p[0], vert[0]);
		glAttachShader(p[0], frag[0]);
		glLinkProgram(p[0]);


		vert[1] = glCreateShader(GL_VERTEX_SHADER);
		vs = textFileRead("shaders/coord.vert");
		glShaderSource(vert[1], 1, (const char **)&vs, nullptr);
		free(vs);
		glCompileShader(vert[1]);

		frag[1] = glCreateShader(GL_FRAGMENT_SHADER);
		fs = textFileRead("shaders/gamma.frag");
		glShaderSource(frag[1], 1, (const char **)&fs, nullptr);
		free(fs);
		glCompileShader(frag[1]);

		p[1] = glCreateProgram();
		glAttachShader(p[1], vert[1]);
		glAttachShader(p[1], frag[1]);
		glLinkProgram(p[1]);
		*/


		e("Shaders");

	
	}

	if (useShaders == false)
	{
		log.warn("Shaders not supported.");
	}



	log.info("GL setup complete.");


	log.info("Loading graphics");
	blankTexture = GLUtils::getTextureFromPNG("data/misc/blank.png");
	boxTexture = GLUtils::getTextureFromPNG("data/misc/box.png");


}


//char GLUtils::sdlErrorMessageString[1024] = { '\0' };
//char GLUtils::lastSDLErrorMessageString[1024] = { '\0' };

//===========================================================================================================================
void GLUtils::checkSDLError(const string &whereErrorOccurredString)
{//===========================================================================================================================
	

	const char *error = SDL_GetError();
	if (*error) 
	{
		log.error("SDL error: " + string(error));
		SDL_ClearError();
	}


//
//	char sdlErrorMessageString[1024];
//	//check SDL errors
//	strcpy(sdlErrorMessageString, SDL_GetError());
//	//if (strcmp(lastSDLErrorMessageString, sdlErrorMessageString) != 0)
//	{
//		//strcpy(lastSDLErrorMessageString, sdlErrorMessageString);
//		SDL_ClearError();
//		if (whereErrorOccurredString.length()>0)log.error(whereErrorOccurredString);
//		log.error(sdlErrorMessageString);
//	}
}


//===========================================================================================================================
void GLUtils::checkGLError(const string &whereErrorOccurredString)
{//===========================================================================================================================

	int glErrorEnumArray[128] = { GL_NO_ERROR };

	int i = 0;

	//fill errorEnumArray with GL errors until the last error is GL_NO_ERROR
	do
	{
		glErrorEnumArray[i] = glGetError();
		i++;
	} while (glErrorEnumArray[i - 1] != GL_NO_ERROR);


	i = 0;
	while (glErrorEnumArray[i] != GL_NO_ERROR)
	{
		int val = glErrorEnumArray[i];
		string errorString;

		if (val == GL_INVALID_ENUM)errorString = "GL_INVALID_ENUM";
		else if (val == GL_INVALID_VALUE)errorString = "GL_INVALID_VALUE";
		else if (val == GL_INVALID_OPERATION)errorString = "GL_INVALID_OPERATION";
		else if (val == GL_STACK_OVERFLOW)errorString = "GL_STACK_OVERFLOW";
		else if (val == GL_STACK_UNDERFLOW)errorString = "GL_STACK_UNDERFLOW";
		else if (val == GL_OUT_OF_MEMORY)errorString = "GL_OUT_OF_MEMORY";
		//else if(val==GL_TABLE_TOO_LARGE)errorString = "GL_TABLE_TOO_LARGE";//deprecated
		else errorString = "Unknown GL error";

		log.error(whereErrorOccurredString + ": "+errorString);

		i++;
	}
}

//===========================================================================================================================
void GLUtils::e(const string &whereErrorOccurredString)
{//===========================================================================================================================

	checkGLError(whereErrorOccurredString);
	checkSDLError(whereErrorOccurredString);

}

//===========================================================================================================================
void GLUtils::e()
{//===========================================================================================================================

	e("");

}


////=========================================================================================================================
//float GLUtils::getViewportWidth()
//{//=========================================================================================================================
//	return (float)getWindowWidth() / 2.0f / ZOOM;
//}
////=========================================================================================================================
//float GLUtils::getViewportHeight()
//{//=========================================================================================================================
//	return (float)getWindowHeight() / 2.0f / ZOOM;
//}

//=========================================================================================================================
int GLUtils::getRealWindowWidth()
{//=========================================================================================================================
	return windowWidth;
}
//=========================================================================================================================
int GLUtils::getRealWindowHeight()
{//=========================================================================================================================
	return windowHeight;
}
//=========================================================================================================================
int GLUtils::getViewportWidth()
{//=========================================================================================================================
	if (fullscreen)return windowWidth;// / 2;
	return windowWidth;
}
//=========================================================================================================================
int GLUtils::getViewportHeight()
{//=========================================================================================================================
	if (fullscreen)return windowHeight;// / 2;
	return windowHeight;
}

//=========================================================================================================================
int GLUtils::getMonitorWidth()
{//=========================================================================================================================
	return monitorWidth;
}
//=========================================================================================================================
int GLUtils::getMonitorHeight()
{//=========================================================================================================================
	return monitorHeight;
}

//=========================================================================================================================
SDL_DisplayMode GLUtils::getCurrentDisplayMode()
{//=========================================================================================================================

 // Get current display mode of all displays.
	for (int i = 0; i < SDL_GetNumVideoDisplays(); i++)
	{
		int should_be_zero = SDL_GetCurrentDisplayMode(i, &currentDisplayMode);

		if (should_be_zero != 0)
		{
			// In case of error...
			//SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
		}
		else
		{
			// On success, print the current display mode.
			SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, currentDisplayMode.w, currentDisplayMode.h, currentDisplayMode.refresh_rate);
		}
	}
	checkSDLError("getCurrentDisplayMode");
	return currentDisplayMode;
}

//=========================================================================================================================
ArrayList<SDL_DisplayMode*> GLUtils::getAvailableDisplayModes()
{//=========================================================================================================================

	if (displayModes.size() > 0)return displayModes;
	int displayCount = 0;

	displayCount = SDL_GetNumVideoDisplays();
	if (displayCount < 1)
		SDL_Log("SDL_GetNumVideoDisplays returned: %i", displayCount);

	for (int d = 0; d < displayCount; d++)
	{
		int numDisplayModes = SDL_GetNumDisplayModes(d);
		for (int m = 0; m < numDisplayModes; m++)
		{
			SDL_DisplayMode *mode = new SDL_DisplayMode();

			if (SDL_GetDisplayMode(d, m, mode) != 0)
				SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());

			SDL_Log("SDL_GetDisplayMode:\t\t%i bpp\t%i x %i",
				SDL_BITSPERPIXEL(mode->format), mode->w, mode->h);

			displayModes.add(mode);
		}
	}
	checkSDLError("getAvailableDisplayModes");

	return displayModes;
}

//=========================================================================================================================
void GLUtils::setFullscreenCompatibleDisplayMode(int width, int height, bool fullscreen)
{ //=========================================================================================================================

	currentDisplayMode = getCurrentDisplayMode();


	//return if requested DisplayMode is already set
	if ((currentDisplayMode.w == width) && (currentDisplayMode.h == height))// && (isFullscreen() == fullscreen))
	{
		return;
	}

	//	try
	//	{
	SDL_DisplayMode* targetDisplayMode = nullptr;

	ArrayList<SDL_DisplayMode*> modes = getAvailableDisplayModes();

	{
		//if(fullscreen)


		int freq = 0;
		for (int i = 0; i < modes.size(); i++)
		{
			SDL_DisplayMode* m = modes.get(i);

			if ((m->w == width) && (m->h == height))
			{
				if ((targetDisplayMode == nullptr) || (m->refresh_rate >= freq))
				{
					if ((targetDisplayMode == nullptr) || (SDL_BITSPERPIXEL(m->format) > SDL_BITSPERPIXEL(targetDisplayMode->format)))
					{
						targetDisplayMode = m;
						freq = targetDisplayMode->refresh_rate;
					}
				}

				//if we've found a match for bpp and frequence against the original display mode
				//then it's probably best to go for this one since it's most likely compatible with the monitor
				//if ((SDL_BITSPERPIXEL(m->format) == SDL_BITSPERPIXEL(getDesktopDisplayMode()->format))) //&& (m->getFrequency() == getDesktopDisplayMode()->getFrequency()))
				//					{
				//						targetDisplayMode = m;
				//						break;
				//					}
			}
		}
	}


	if (targetDisplayMode == nullptr)
	{
		log.warn(string("Could not find video mode : ") + to_string(width) + string("x") + to_string(height) + string(" fullscreen: ") + StringConverterHelper::toString(fullscreen));
		return;
	}



	for (int i = 0; i < modes.size(); i++)
	{
		SDL_DisplayMode* m = modes.get(i);

		log.debug(to_string(m->w) + "x" + to_string(m->h) + " BPP: " + to_string(SDL_BITSPERPIXEL(m->format)));// +" Frequency: " + to_string(m->getFrequency()) + "Hz");
	}

	//TODO: get the browser window/current frame size using javascript
	//set the applet size to this using javascript
	//set the windowed display to this


	int halfSizeWidth = getMonitorWidth() / 2;
	int halfSizeHeight = getMonitorHeight() / 2;

	//TODO:
	//get monitor resolution ??
	//get cpu, gpu, ram
	//if fast enough, set to full resolution fullscreen
	//if not so fast, set to half resolution fullscreen

	bool useHalfSizeRes = true;
	if (useHalfSizeRes)setFullscreenCompatibleDisplayMode(halfSizeWidth, halfSizeHeight, false);

	//getViewportWidth() = halfSizeWidth;
	//getViewportHeight() = halfSizeHeight;

	//else
	//setFullscreenCompatibleDisplayMode(desktopDisplayWidth, desktopDisplayHeight, false);
	//Display.setFullscreen(true);




	//setFullscreen(fullscreen);
	//	}
	//	catch (exception e)//LWJGLException e)
	//	{
	//		log.warn(string("Could not set video mode: ") + to_string(width) + string("x") + to_string(height) + string(" fullscreen: ") + StringConverterHelper::toString(fullscreen));
	//	}
}



//=========================================================================================================================
void GLUtils::attachTextureToFBO(int attachment, int textureID)
{ //=========================================================================================================================

	if (ARBFBO)
	{
		if (attachment == 0)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
		}
		else
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, textureID, 0);
		}
	}
	else
	{
		if (attachment == 0)
		{
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, textureID, 0);
		}
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, textureID, 0);
	}
}

bool GLUtils::ARBFBO = false;

//=========================================================================================================================
void GLUtils::bindFBO(int fboID)
{ //=========================================================================================================================

	if (ARBFBO)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	}
	else
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboID);
	}
}

//=========================================================================================================================
void GLUtils::drawIntoFBOAttachment(int i)
{ //=========================================================================================================================
	if (ARBFBO)
	{
		if (i == 0)
		{
			glDrawBuffer(GL_COLOR_ATTACHMENT0);
		}
		else
		{
			glDrawBuffer(GL_COLOR_ATTACHMENT1);
		}
	}
	else
	{
		if (i == 0)
		{
			glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
		}
		else
		{
			glDrawBuffer(GL_COLOR_ATTACHMENT1_EXT);
		}
	}
}

//=========================================================================================================================
int GLUtils::genFBO()
{ //=========================================================================================================================
	GLuint fbID = 0;

	if (ARBFBO)
	{
		glGenFramebuffers(1, &fbID);//If the OpenGL version is >= 3.0 (in this version the FBO extension was added to the core)
		return (int)fbID;
	}
	else
	//if ( check GL_EXT_framebuffer_object )
	{
		glGenFramebuffersEXT(1, &fbID);//If the extension GL_EXT_framebuffer_object is present
		return (int)fbID;
	}


	glGenFramebuffers(1, &fbID);//If the OpenGL version is >= 3.0 (in this version the FBO extension was added to the core)
	return (int)fbID;
}

//=========================================================================================================================
int GLUtils::setupFBOTexture(int tex, int width, int height)
{ //=========================================================================================================================

	const int s = width * height * 4;
	u8* data = new u8[s];

	//init FBO texture
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	delete data;

	return tex;
}


bool GLUtils::ARBShader = false;

//=========================================================================================================================
int GLUtils::createProgramObject()
{ //=========================================================================================================================
	int i = 0;

	if (useShaders == true)
	{
		if (ARBShader == false)
		{
			i = glCreateProgram();
			e("glCreateProgram");
			if (i == 0)
			{
				ARBShader = true;
				log.warn("Core shaders failed. Trying ARB shaders.");
			}
		}

		if (ARBShader)
		{
			i = glCreateProgramObjectARB();
			e("glCreateProgramObjectARB");
			if (i == 0)
			{
				useShaders = false;
				log.warn("ARB shaders failed. Using no shaders.");
			}
		}
	}

	return i;

}


//=========================================================================================================================
int GLUtils::compileShaderObject(const string& filename, int type)
{ //=========================================================================================================================
	//will be non zero if successfully created
	int shader = 0;


	if (type == FRAG)
	{
		if (ARBShader)
		{
		    shader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
		}
		else
		{
			shader = glCreateShader(GL_FRAGMENT_SHADER);
		}
	}
	else
	{
		if (ARBShader)
		{
		    shader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
		}
		else
		{
			shader = glCreateShader(GL_VERTEX_SHADER);
		}
	}

	e("glCreateShader");

	//if created, convert the shader code to a String
	if (shader == 0)
	{
		return 0;
	}

	string code = "";
	string line;
	try
	{
		code = FileUtils::loadTextFileFromExePathAndTrim(filename);
	}
	catch (exception& e)
	{
		log.error(string("Could not read code: ") + filename);
		log.error(string("Standard exception: ") + e.what());
		return 0;
	}


	if (ARBShader)
	{
		const char* c_str = code.c_str();

		//void glShaderSourceARB( GLhandleARB shader,GLsizei nstrings,const GLcharARB **strings,const GLint *lengths)
		glShaderSourceARB(shader, 1, &c_str, NULL);
		e();
		glCompileShaderARB(shader);
		e();

		//if there was a problem compiling, reset to zero
		GLint p;
		glGetObjectParameterivARB(shader, GL_OBJECT_COMPILE_STATUS_ARB, &p);
		if (p == GL_FALSE)
		{
			e();

			GLint logLength; 
			glGetObjectParameterivARB(shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);
			e();
			if (logLength > 0)
			{
				char infoLog[1024];
				GLint logLen;
				glGetInfoLogARB(shader, 1024, &logLen, infoLog);
				string out = string(infoLog);
				e();
				if (out.length() > 0)
				{
					out = out.substr(0, out.length() - 1); //remove extra newline
				}
				log.warn(string("ShaderInfoLogARB: ") + out);
			}

			shader = 0;
		}
	}
	else
	{
		const char* c_str = code.c_str();
		glShaderSource(shader, 1, &c_str, NULL);
		e("glShaderSource");
		glCompileShader(shader);
		e("glCompileShader");

		//if there was a problem compiling, reset to zero
		GLint p;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &p);
		if (p == GL_FALSE)
		{
			e();
		
			GLint logLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
			e();
			if (logLength > 0)
			{
				char infoLog[1024];
				GLint logLen;
				glGetShaderInfoLog(shader, 1024, &logLen, infoLog);
				string out = string(infoLog);
				e();
				if (out.length() > 0)
				{
					out = out.substr(0, out.length() - 1); //remove extra newline
				}
				log.warn(string("ShaderInfoLog: ") + out);
			}
		
			shader = 0;
		}
	}


	//if zero we won't be using the shader
	return shader;
}

//=========================================================================================================================
bool GLUtils::makeShader(const string& name, int shaderProgram, const string& vertPath, const string& fragPath)
{ //=========================================================================================================================

	int vertShader = 0;
	int fragShader = 0;

	//log.debug("compileShaderObject");
	vertShader = GLUtils::compileShaderObject(vertPath, VERT);
	fragShader = GLUtils::compileShaderObject(fragPath, FRAG);

	if (vertShader != 0 && fragShader != 0)
	{

		//log.debug("glAttachShader");
		if (ARBShader)
		{
			glAttachObjectARB(shaderProgram, vertShader);
			e("glAttachObjectARB");

			glAttachObjectARB(shaderProgram, fragShader);
			e("glAttachObjectARB");

			glLinkProgramARB(shaderProgram);
			e("glLinkProgramARB");

			glValidateProgramARB(shaderProgram);
			e("glValidateProgramARB");
		}
		else
		{
			glAttachShader(shaderProgram, vertShader);
			e("glAttachShader");

			glAttachShader(shaderProgram, fragShader);
			e("glAttachShader");

			glLinkProgram(shaderProgram);
			e("glLinkProgram");

			glValidateProgram(shaderProgram);
			e("glValidateProgram");
		}

		string out = "";

		if (ARBShader)
		{
			int logLength = 0;
			glGetObjectParameterivARB(shaderProgram, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);//glGetObjectParameteriARB
			e("glGetObjectParameterivARB");
			if (logLength > 0)
			{
				GLsizei returnLength = 0;
				GLchar returnLog[1024];
				glGetInfoLogARB(shaderProgram, 1024, &returnLength, returnLog);
				out = string(returnLog);


				e("glGetInfoLogARB");
				if (out.length() > 0)
				{
					out = out.substr(0, out.length() - 1); //remove extra newline
				}
				out = (string("ProgramInfoLog: ") + out);
			}
		}
		else
		{
			int logLength = 0;
			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
			e("glGetProgramiv");
			if (logLength > 0)
			{
				GLsizei returnLength = 0;
				GLchar returnLog[1024];
				glGetProgramInfoLog(shaderProgram, 1024, &returnLength, returnLog);
				out = string(returnLog);

				e("glGetProgramInfoLog");
				if (out.length() > 0)
				{
					out = out.substr(0, out.length() - 1); //remove extra newline
				}
				out = (string("ProgramInfoLog: ") + out);
			}
		}

		//log.info(name + string(" status: ") + out);
		string lower = out;
		transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

//		if (
//			lower.find("warning") != string::npos
//			) //startsWith("Validation successful")==false && String::startsWith(status,"Validation warning! - Sampler")==false)
//		{
//			log.warn(name + string(" status: ") + out);
//			return true;
//		}
//		else
		if (
			lower.find("error") != string::npos
			||
			lower.find("failed") != string::npos
			)
		{
			log.error(name + string(" status: ") + out);
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		log.warn(name + string(" did not compile!"));
		return false;
	}
}


//=========================================================================================================================
void GLUtils::useShader(int shader)
{ //=========================================================================================================================

	//if(useShader==false)return;

	if (ARBShader)
	{
		glUseProgramObjectARB(shader);
	}
	else
	{
		glUseProgram(shader);
	}
	e("glUseProgram");
}


bool GLUtils::fullscreen = false;

//=========================================================================================================================
void GLUtils::toggleFullscreen()
{//=========================================================================================================================
	
	fullscreen = !fullscreen;

	if (fullscreen)SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else SDL_SetWindowFullscreen(window, 0);

	doResize();
}





int GLUtils::DEFAULT_SHADER_FBO_FILTER = FILTER_FBO_NEAREST_NO_MIPMAPPING;
int GLUtils::DEFAULT_ND_FBO_FILTER = FILTER_FBO_NEAREST_NO_MIPMAPPING;
int GLUtils::DEFAULT_BLOOM_FBO_FILTER = FILTER_FBO_LINEAR_NO_MIPMAPPING;
float GLUtils::SHADER_FBO_SCALE = 1.0f;
float GLUtils::FBO_SCALE = 1.0f;
float GLUtils::BLOOM_FBO_SCALE = 0.25f;

//=========================================================================================================================
void GLUtils::setRealWindowViewport()
{ //=========================================================================================================================
  //	glViewport(0, 0, windowWidth, windowHeight);
  //	glLoadIdentity();
  //	glOrtho(0, windowWidth, windowHeight, 0, -1, 1);

  //order does matter
	glLoadIdentity(); //reset selected transform matrix
	glOrtho(0, getRealWindowWidth(), getRealWindowHeight(), 0, -1, 1);

	glViewport(0, 0, getRealWindowWidth(), getRealWindowHeight()); //order doesn't matter

}
//=========================================================================================================================
void GLUtils::setPostColorFilterViewport()
{ //=========================================================================================================================
  //	glViewport(0, 0, windowWidth, windowHeight);
  //	glLoadIdentity();
  //	glOrtho(0, windowWidth, windowHeight, 0, -1, 1);

  //order does matter
	glLoadIdentity(); //reset selected transform matrix
	glOrtho(0, getViewportWidth(), getViewportHeight(), 0, -1, 1);

	glViewport(0, 0, getViewportWidth(), getViewportHeight()); //order doesn't matter

}

void GLUtils::setPreColorFilterViewport()
{ //=========================================================================================================================
	glViewport(0, 0, (int)(getViewportWidth() * FBO_SCALE), (int)(getViewportHeight() * FBO_SCALE));
	glLoadIdentity();
	glOrtho(0, getViewportWidth() * FBO_SCALE, getViewportHeight() * FBO_SCALE, 0, -1, 1);
}

void GLUtils::setBobsGameMainFBOFilterViewport()
{ //=========================================================================================================================

	glViewport(0, 0, (int)(bobsGameFBO_Width * FBO_SCALE), (int)(bobsGameFBO_Height * FBO_SCALE));
	glLoadIdentity();
	glOrtho(0, bobsGameFBO_Width * FBO_SCALE, bobsGameFBO_Height * FBO_SCALE, 0, -1, 1);
}
void GLUtils::setBloomViewport()
{ //=========================================================================================================================
	glViewport(0, 0, (int)(bobsGameFBO_Width * FBO_SCALE * BLOOM_FBO_SCALE), (int)(bobsGameFBO_Height * FBO_SCALE * BLOOM_FBO_SCALE));
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
}

void GLUtils::setShaderViewport()
{ //=========================================================================================================================
	glViewport(0, 0, (int)(getViewportWidth() * FBO_SCALE * SHADER_FBO_SCALE), (int)(getViewportHeight() * FBO_SCALE * SHADER_FBO_SCALE));
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
}

//=========================================================================================================================
void GLUtils::resizeBobsGameFBO(float w, float h)
{ //=========================================================================================================================

	if (w == 0)w = 10;
	if (h == 0)h = 10;

	bobsGameFBO_Width = w;
	bobsGameFBO_Height = h;

	GLuint texID;

	bindFBO(bobsGame_mainGameFBO);

	texID = bobsGame_mainGameFBO_Texture_Attachment0;
	glDeleteTextures(1, &texID);
	glGenTextures(1, &texID);
	bobsGame_mainGameFBO_Texture_Attachment0 = setupFBOTexture(texID, (int)(w * FBO_SCALE), (int)(h * FBO_SCALE));
	attachTextureToFBO(0, bobsGame_mainGameFBO_Texture_Attachment0);

	texID = bobsGame_mainGameFBO_Texture_Attachment1_BloomMask;
	glDeleteTextures(1, &texID);
	glGenTextures(1, &texID);
	bobsGame_mainGameFBO_Texture_Attachment1_BloomMask = setupFBOTexture(texID, (int)(w * FBO_SCALE), (int)(h * FBO_SCALE));
	attachTextureToFBO(1, bobsGame_mainGameFBO_Texture_Attachment1_BloomMask);


	//=================================

	bindFBO(bobsGame_bloomFBO);

	texID = bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0;
	glDeleteTextures(1, &texID);
	glGenTextures(1, &texID);
	bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0 = setupFBOTexture(texID, (int)(w * FBO_SCALE * BLOOM_FBO_SCALE), (int)(h * FBO_SCALE * BLOOM_FBO_SCALE));
	attachTextureToFBO(0, bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0);

	texID = bobsGame_bloomFBO_PingPongBlur_Texture_Attachment1;
	glDeleteTextures(1, &texID);
	glGenTextures(1, &texID);
	bobsGame_bloomFBO_PingPongBlur_Texture_Attachment1 = setupFBOTexture(texID, (int)(w * FBO_SCALE * BLOOM_FBO_SCALE), (int)(h * FBO_SCALE * BLOOM_FBO_SCALE));
	attachTextureToFBO(1, bobsGame_bloomFBO_PingPongBlur_Texture_Attachment1);


}

//=========================================================================================================================
void GLUtils::doResize()
{ //=========================================================================================================================


	lastWindowWidth = windowWidth;
	lastWindowHeight = windowHeight;

	int w;
	int h;
	SDL_GL_GetDrawableSize(window, &w, &h);

	windowWidth = w;
	windowHeight = h;


	//glMatrixMode(GL_MODELVIEW);//worldview transform (how far from 0,0,0 are we)
	//glLoadIdentity();//reset selected transform matrix
	//glMatrixMode(GL_PROJECTION);//perspective transform matrix (for 3f->2f perspective, etc)


	GLUtils::setPostColorFilterViewport();

	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();


	//fix FBO sizes

	GLuint texID;


	GLUtils::bindFBO(postColorFilterFBO);

	
	texID = postColorFilterFBO_Texture_Attachment0;
	glDeleteTextures(1, &texID);
	glGenTextures(1, &texID);
	postColorFilterFBO_Texture_Attachment0 = GLUtils::setupFBOTexture(texID, getViewportWidth(), getViewportHeight());
	GLUtils::attachTextureToFBO(0, postColorFilterFBO_Texture_Attachment0);

	texID = postColorFilterFBO_Texture_Attachment1_PreLighting;
	glDeleteTextures(1, &texID);
	glGenTextures(1, &texID);
	postColorFilterFBO_Texture_Attachment1_PreLighting = GLUtils::setupFBOTexture(texID, getViewportWidth(), getViewportHeight());
	GLUtils::attachTextureToFBO(1, postColorFilterFBO_Texture_Attachment1_PreLighting);


	//=================================

	GLUtils::bindFBO(preColorFilterFBO);

	texID = preColorFilterFBO_Texture_Attachment0;
	glDeleteTextures(1, &texID);
	glGenTextures(1, &texID);
	preColorFilterFBO_Texture_Attachment0 = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE));
	GLUtils::attachTextureToFBO(0, preColorFilterFBO_Texture_Attachment0);

	texID = preColorFilterFBO_Texture_Attachment1_BloomMask;
	glDeleteTextures(1, &texID);
	glGenTextures(1, &texID);
	preColorFilterFBO_Texture_Attachment1_BloomMask = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE));
	GLUtils::attachTextureToFBO(1, preColorFilterFBO_Texture_Attachment1_BloomMask);

	//=================================

//	GLUtils::bindFBO(bobsGame_mainGameFBO);
//
//	textureID = bobsGame_mainGameFBO_Texture_Attachment0;
//	glDeleteTextures(1, &textureID);
//	glGenTextures(1, &texID);
//	bobsGame_mainGameFBO_Texture_Attachment0 = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE));
//	GLUtils::attachTextureToFBO(0, bobsGame_mainGameFBO_Texture_Attachment0);
//
//	textureID = bobsGame_mainGameFBO_Texture_Attachment1_BloomMask;
//	glDeleteTextures(1, &textureID);
//	glGenTextures(1, &texID);
//	bobsGame_mainGameFBO_Texture_Attachment1_BloomMask = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE));
//	GLUtils::attachTextureToFBO(1, bobsGame_mainGameFBO_Texture_Attachment1_BloomMask);
//
//	bobsGameFBO_Width = getViewportWidth() * GLUtils::FBO_SCALE;
//	bobsGameFBO_Height = getViewportHeight() * GLUtils::FBO_SCALE;
//	//=================================
//
//	GLUtils::bindFBO(bobsGame_bloomFBO);
//
//
//	textureID = bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0;
//	glDeleteTextures(1, &textureID);
//	glGenTextures(1, &texID);
//	bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0 = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE * GLUtils::BLOOM_FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE * GLUtils::BLOOM_FBO_SCALE));
//	GLUtils::attachTextureToFBO(0, bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0);
//
//	textureID = bobsGame_bloomFBO_PingPongBlur_Texture_Attachment1;
//	glDeleteTextures(1, &textureID);
//	glGenTextures(1, &texID);
//	bobsGame_bloomFBO_PingPongBlur_Texture_Attachment1 = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE * GLUtils::BLOOM_FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE * GLUtils::BLOOM_FBO_SCALE));
//	GLUtils::attachTextureToFBO(1, bobsGame_bloomFBO_PingPongBlur_Texture_Attachment1);


	//=================================

	GLUtils::bindFBO(bobsGame_bgShaderFBO);

	texID = bobsGame_bgShaderFBO_Texture_Attachment0;
	glDeleteTextures(1, &texID);
	glGenTextures(1, &texID);
	bobsGame_bgShaderFBO_Texture_Attachment0 = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE*GLUtils::SHADER_FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE*GLUtils::SHADER_FBO_SCALE));
	GLUtils::attachTextureToFBO(0, bobsGame_bgShaderFBO_Texture_Attachment0);

	texID = bobsGame_bgShaderFBO_Texture_Attachment1;
	glDeleteTextures(1, &texID);
	glGenTextures(1, &texID);
	bobsGame_bgShaderFBO_Texture_Attachment1 = GLUtils::setupFBOTexture(texID, (int)(getViewportWidth() * GLUtils::FBO_SCALE*GLUtils::SHADER_FBO_SCALE), (int)(getViewportHeight() * GLUtils::FBO_SCALE*GLUtils::SHADER_FBO_SCALE));
	GLUtils::attachTextureToFBO(1, bobsGame_bgShaderFBO_Texture_Attachment1);


	//bind the depth renderbuffer
	//glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBufferID);
	//get the data space for it
	//glRenderbufferStorage(GL_RENDERBUFFER, GL14.GL_DEPTH_COMPONENT24, 512, 512);
	//bind it to the renderbuffer
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER, depthRenderBufferID);

	//switch back to normal framebuffer
	GLUtils::bindFBO(0);


}


//=========================================================================================================================
void GLUtils::setBlendMode(int src, int dst)
{ //=========================================================================================================================

	//if(Keyboard.isKeyDown(Keyboard.KEY_COMMA))glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//else
	//if(Keyboard.isKeyDown(Keyboard.KEY_PERIOD))glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	//else
	glBlendFunc(src, dst);
}

//=========================================================================================================================
void GLUtils::setShaderVar1i(int shader, char* s, int i)
{ //=========================================================================================================================


	if (ARBShader)
	{
		glUniform1iARB(glGetUniformLocationARB(shader, s), i);
	}
	else
	{
		glUniform1i(glGetUniformLocation(shader, s), i);
	}
}

//=========================================================================================================================
void GLUtils::setShaderVar1f(int shader, char* s, float f)
{ //=========================================================================================================================
	if (ARBShader)
	{
		glUniform1fARB(glGetUniformLocationARB(shader, s), f);
	}
	else
	{
		glUniform1f(glGetUniformLocation(shader, s), f);
	}
}

//=========================================================================================================================
void GLUtils::setShaderVar2f(int shader, char* s, float f1, float f2)
{ //=========================================================================================================================
	if (ARBShader)
	{
		glUniform2fARB(glGetUniformLocationARB(shader, s), f1, f2);
	}
	else
	{
		glUniform2f(glGetUniformLocation(shader, s), f1, f2);
	}
}

//=========================================================================================================================
int GLUtils::getOutlinedTextWidth(string cs)
{//=========================================================================================================================
	return 50;
}

//=========================================================================================================================
void GLUtils::setDefaultTextureParams()
{ //=========================================================================================================================

  //THIS WAS THE PROBLEM WITH TEXTURES SHOWING UP WHITE, NEEDED TO GENERATE MIPMAPS FOR SOME REASON

  //why don't i need to do this for captions????

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 2);//0=100% 1=50% 2=25%
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);


  //glTexEnvf(GL_TEXTURE_FILTER_CONTROL, GL_TEXTURE_LOD_BIAS, -1.5f);


  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 


  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //glTexEnv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL11.GL_NEAREST);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL11.GL_NEAREST);
}

//=========================================================================================================================
void GLUtils::drawTexture(BobTexture* texture, float sx0, float sy0, int filter)//static
{//=========================================================================================================================
	drawTexture(texture, sx0, sy0, 1.0f, filter);
}

//=========================================================================================================================
void GLUtils::drawTexture(BobTexture* texture, float sx0, float sy0, float alpha, int filter)//static
{//=========================================================================================================================

	float sx1 = sx0 + texture->getImageWidth();
	float sy1 = sy0 + texture->getImageHeight();

	drawTexture(texture, sx0, sx1, sy0, sy1, alpha, filter);
}

//===========================================================================================================================
void GLUtils::drawTexture(BobTexture* texture, float sx0, float sx1, float sy0, float sy1, float alpha, int filter)//static
{//===========================================================================================================================

	float tXRatio = (float)texture->getImageWidth() / (float)texture->getTextureWidth();
	float tYRatio = (float)texture->getImageHeight() / (float)texture->getTextureHeight();

	float ix0 = 0.0f;
	float ix1 = 1.0f;

	float iy0 = 0.0f;
	float iy1 = 1.0f;

	float tx0 = ix0 * tXRatio;
	float tx1 = ix1 * tXRatio;

	float ty0 = iy0 * tYRatio;
	float ty1 = iy1 * tYRatio;

	drawTexture(texture, tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, alpha, filter);
}

//===========================================================================================================================
void GLUtils::drawTexture(BobTexture* texture, float tx0, float tx1, float ty0, float ty1, float sx0, float sx1, float sy0, float sy1, float alpha, int filter)//static
{//===========================================================================================================================
	if (texture == nullptr)return;

	//Sprite s = new Sprite(texture);


	drawTexture(texture->getTextureID(), tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, alpha, filter);
}

//===========================================================================================================================
void GLUtils::drawTexture(int textureID, float tx0, float tx1, float ty0, float ty1, float sx0, float sx1, float sy0, float sy1, float alpha, int filter)
{//===========================================================================================================================

	glBindTexture(GL_TEXTURE_2D, textureID);
	drawTexture(tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, 1.0f, 1.0f, 1.0f, alpha, filter);
}

//===========================================================================================================================
void GLUtils::drawTexture(float tx0, float tx1, float ty0, float ty1, float sx0, float sx1, float sy0, float sy1, float alpha, int filter)
{//===========================================================================================================================

	drawTexture(tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, 1.0f, 1.0f, 1.0f, alpha, filter);
}

//===========================================================================================================================
void GLUtils::drawTexture(BobTexture* texture, float tx0, float tx1, float ty0, float ty1, float sx0, float sx1, float sy0, float sy1, float r, float g, float b, float a, int filter)
{//===========================================================================================================================

	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	drawTexture(tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, r, g, b, a, filter);
}

//int roundCoords = 0;

void roundMe(float &screenX0, float &screenX1, float &screenY0, float &screenY1)
{
	screenX1 = (float)ceil(screenX1);
	screenY1 = (float)ceil(screenY1);
}

//===========================================================================================================================
void GLUtils::drawTexture(float textureX0, float textureX1, float textureY0, float textureY1, float screenX0, float screenX1, float screenY0, float screenY1, float r, float g, float b, float a, int filter)
{//===========================================================================================================================

//#ifdef _DEBUG
//	if(Main::getMain()->controlsManager->key_NUM0_Pressed())
//	{
//		roundCoords++;
//		if (roundCoords > 1)roundCoords = 0;
//		log.debug("Round:" + to_string(roundCoords));
//	}
//
//#endif

	roundMe(screenX0, screenX1, screenY0, screenY1);

	screenX0 *= globalDrawScale;
	screenX1 *= globalDrawScale;
	screenY0 *= globalDrawScale;
	screenY1 *= globalDrawScale;

	glEnable(GL_TEXTURE_2D);
	

	if (filter == FILTER_FBO_LINEAR_NO_MIPMAPPING)//for FBO rendering only
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else if (filter == FILTER_FBO_NEAREST_NO_MIPMAPPING)//for FBO rendering only
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else if (filter == FILTER_NEAREST)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//if(Keyboard.isKeyDown(Keyboard.KEY_1))glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	}
	else if (filter == FILTER_LINEAR)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//if(Keyboard.isKeyDown(Keyboard.KEY_1))glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); //TODO:what does this do and why did i comment it out? i forget.


	if (glVersionMajor < 2)
	{	 		   

		glColor4f(r,g,b,a);
		glBegin(GL_QUADS);

		glTexCoord2f(textureX0, textureY0);
		glVertex2f(screenX0, screenY0);

		glTexCoord2f(textureX1, textureY0);
		glVertex2f(screenX1, screenY0);

		glTexCoord2f(textureX1, textureY1);
		glVertex2f(screenX1, screenY1);

		glTexCoord2f(textureX0, textureY1);
		glVertex2f(screenX0, screenY1);

		glEnd();

		return;
	}


	box[0] = screenX0;
	box[1] = screenY0;
	box[2] = 0.0f;
	box[3] = screenX0;
	box[4] = screenY1;
	box[5] = 0.0f;
	box[6] = screenX1;
	box[7] = screenY1;
	box[8] = 0.0f;
	box[9] = screenX1;
	box[10] = screenY0;
	box[11] = 0.0f;

	col[0] = r;
	col[1] = g;
	col[2] = b;
	col[3] = a;

	col[4] = r;
	col[5] = g;
	col[6] = b;
	col[7] = a;

	col[8] = r;
	col[9] = g;
	col[10] = b;
	col[11] = a;

	col[12] = r;
	col[13] = g;
	col[14] = b;
	col[15] = a;

	tex[0] = textureX0;
	tex[1] = textureY0;
	tex[2] = textureX0;
	tex[3] = textureY1;
	tex[4] = textureX1;
	tex[5] = textureY1;
	tex[6] = textureX1;
	tex[7] = textureY0;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 3 * 4, box);
	glColorPointer(4, GL_FLOAT, 4 * 4, col);
	glTexCoordPointer(3, GL_FLOAT, 2 * 4, tex);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);



	//		glColor4f(1,1,1,1);
	//
	//		glEnable(GL_COLOR_MATERIAL);
	//
	//		glColor4f(1,1,1,a);
	//
	//
	//		if(Keyboard.isKeyDown(Keyboard.KEY_1))glTexEnvi(GL11.GL_TEXTURE_ENV, GL11.GL_TEXTURE_ENV_MODE, GL13.GL_COMBINE);
	//		if(Keyboard.isKeyDown(Keyboard.KEY_2))glTexEnvi(GL11.GL_TEXTURE_ENV, GL11.GL_TEXTURE_ENV_MODE, GL11.GL_BLEND);
	//		if(Keyboard.isKeyDown(Keyboard.KEY_3))glTexEnvi(GL11.GL_TEXTURE_ENV, GL11.GL_TEXTURE_ENV_MODE, GL11.GL_MODULATE);
	//
	//
	//		if(Keyboard.isKeyDown(Keyboard.KEY_4))a=0.5f;
	//


	//		glEnableClientState(GL_COLOR_ARRAY);
	//		glEnable(GL_COLOR_MATERIAL);
	//		glColor4f(r,g,b,a);
	//
	//		//glEnable(GL11.GL_BLEND);
	//
	//		//glTexEnvi(GL11.GL_TEXTURE_ENV, GL11.GL_TEXTURE_ENV_MODE, GL_COMBINE);
	//		//glTexEnvi(GL11.GL_TEXTURE_ENV, GL11.GL_TEXTURE_ENV_MODE, GL_MODULATE);//GL_BLEND//GL_COMBINE
	//		//glTexEnvi(GL11.GL_TEXTURE_ENV, GL11.GL_TEXTURE_ENV_MODE, GL_REPLACE);
	////		glTexEnvi(GL11.GL_TEXTURE_ENV, GL11.GL_TEXTURE_ENV_MODE, GL11.GL_REPLACE);
	////		glTexEnvi(GL11.GL_TEXTURE_ENV, GL11.GL_TEXTURE_ENV_MODE, GL11.GL_MODULATE);
	//
	//		glTexEnvi(GL11.GL_TEXTURE_ENV, GL11.GL_TEXTURE_ENV_MODE, GL11.GL_BLEND);
	//
	//
	//
	//
	//		if(Keyboard.isKeyDown(Keyboard.KEY_4))glTexEnvi(GL11.GL_TEXTURE_ENV, GL13.GL_COMBINE_RGB, GL11.GL_MODULATE);
	//		if(Keyboard.isKeyDown(Keyboard.KEY_5))glTexEnvi(GL11.GL_TEXTURE_ENV, GL13.GL_COMBINE_ALPHA, GL11.GL_MODULATE);
	//
	//		if(Keyboard.isKeyDown(Keyboard.KEY_6))glTexEnvi(GL11.GL_TEXTURE_ENV, GL13.GL_COMBINE_RGB, GL11.GL_BLEND);
	//		if(Keyboard.isKeyDown(Keyboard.KEY_7))glTexEnvi(GL11.GL_TEXTURE_ENV, GL13.GL_COMBINE_ALPHA, GL11.GL_BLEND);
	//
	//		if(Keyboard.isKeyDown(Keyboard.KEY_8))glTexEnvi(GL11.GL_TEXTURE_ENV, GL13.GL_COMBINE_RGB, GL13.GL_COMBINE);
	//		if(Keyboard.isKeyDown(Keyboard.KEY_9))glTexEnvi(GL11.GL_TEXTURE_ENV, GL13.GL_COMBINE_ALPHA, GL13.GL_COMBINE);
	//
	//
	////		glTexEnvi(GL11.GL_TEXTURE_ENV, GL13.GL_SOURCE0_RGB, GL13.GL_CONSTANT);
	////		glTexEnvi(GL11.GL_TEXTURE_ENV, GL13.GL_OPERAND0_RGB, GL11.GL_SRC_COLOR);
	//
	//
	//		if(Keyboard.isKeyDown(Keyboard.KEY_0))glTexEnvi(GL11.GL_TEXTURE_ENV, GL13.GL_SOURCE0_ALPHA, GL11.GL_TEXTURE);
	//		if(Keyboard.isKeyDown(Keyboard.KEY_0))glTexEnvi(GL11.GL_TEXTURE_ENV, GL13.GL_SOURCE1_ALPHA, GL13.GL_CONSTANT);
	////		glTexEnvi(GL11.GL_TEXTURE_ENV, GL13.GL_OPERAND0_RGB, GL11.GL_SRC_ALPHA);
	////		glTexEnvi(GL11.GL_TEXTURE_ENV, GL13.GL_OPERAND0_RGB, GL11.GL_SRC_ALPHA);
	//
	//
	//		glBegin(GL_QUADS);
	//			glTexCoord2f(textureX0, textureY0); glVertex3f(screenX0, screenY0,  0.0f);
	//			glTexCoord2f(textureX0, textureY1); glVertex3f(screenX0, screenY1,  0.0f);
	//			glTexCoord2f(textureX1, textureY1); glVertex3f(screenX1, screenY1,  0.0f);
	//			glTexCoord2f(textureX1, textureY0); glVertex3f(screenX1, screenY0,  0.0f);
	//		glEnd();
	//
	//
	//		glDisableClientState(GL_COLOR_ARRAY);
	//		glDisable(GL_COLOR_MATERIAL);

	//glDisable(GL_TEXTURE_2D);
}


////=========================================================================================================================
//int GLUtils::getTextWidth(string text)
//{//=========================================================================================================================
//	return 0;
//}

//=========================================================================================================================
void GLUtils::drawOutlinedString(string text, float screenX, float screenY, BobColor* color)//static
{//=========================================================================================================================
	drawOutlinedString(screenX, screenY, text, color);
}


//=========================================================================================================================
void GLUtils::drawOutlinedString(float screenX0, float screenY0, string text, BobColor* color)//static
{//=========================================================================================================================

 //
 //		if(font==null)
 //		{
 //			try
 //			{
 //				InputStream inputStream = FileUtils::getResourceAsStream("res/fonts/BobsGame::ttf");
 //
 //				BobFont awtFont = BobFont.createFont(BobFont.TRUETYPE_FONT, inputStream);
 //				awtFont = awtFont.deriveFont(8f); // set font size
 //				font = new TrueTypeFont(awtFont, antiAlias);
 //			}
 //			catch (Exception e)
 //			{
 //				e.printStackTrace();
 //			}
 //		}

 //if(font==null){log.error("BobFont is null");return;}
 //if(getText==null){log.error("Text is null");return;}

	screenX0 *= globalDrawScale;
	//screenX1*=globalDrawScale;
	screenY0 *= globalDrawScale;
	//screenY1*=globalDrawScale;
	//
	//Renderer.setRenderer(1);

	//glEnable(GL_TEXTURE_2D);

	//Color.white.bind();
	//GL11.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);


	//	SlickCallable.enterSafeBlock();
	//	{
	//		font.drawString(screenX0-1,screenY0-1, getText, Color.black);
	//		font.drawString(screenX0+1,screenY0-1, getText, Color.black);
	//		font.drawString(screenX0-1,screenY0+1, getText, Color.black);
	//		font.drawString(screenX0+1,screenY0+1, getText, Color.black);
	//		font.drawString(screenX0+1,screenY0, getText, Color.black);
	//		font.drawString(screenX0-1,screenY0, getText, Color.black);
	//		font.drawString(screenX0,screenY0+1, getText, Color.black);
	//		font.drawString(screenX0,screenY0-1, getText, Color.black);
	//		font.drawString(screenX0,screenY0, getText, new Color(color.r(),color.g(),color.b()));
	//
	//
	//		//glEnable(GL_TEXTURE_2D);
	//	}
	//	SlickCallable.leaveSafeBlock();
}

//=========================================================================================================================
void GLUtils::drawLine(float screenX0, float screenY0, float screenX1, float screenY1, int r, int g, int b)
{//=========================================================================================================================
	drawLine(screenX0, screenY0, screenX1, screenY1, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}

//=========================================================================================================================
void GLUtils::drawLine(float screenX0, float screenY0, float screenX1, float screenY1, float r, float g, float b)
{//=========================================================================================================================
	drawLine(screenX0, screenY0, screenX1, screenY1, r, g, b, 1.0f);
}

//=========================================================================================================================
void GLUtils::drawLine(float screenX0, float screenY0, float screenX1, float screenY1, float r, float g, float b, float a)
{//=========================================================================================================================

	roundMe(screenX0, screenX1, screenY0, screenY1);

	screenX0 *= globalDrawScale;
	screenX1 *= globalDrawScale;
	screenY0 *= globalDrawScale;
	screenY1 *= globalDrawScale;

	glDisable(GL_TEXTURE_2D);

	glColor4f(r, g, b, a);


	glBegin(GL_LINES);
	glVertex2f(screenX0, screenY0);
	glVertex2f(screenX1, screenY1);
	glEnd();
}

//===============================================================================================
void GLUtils::drawArrowLine(float screenX0, float screenY0, float screenX1, float screenY1, int r, int g, int b)
{//===============================================================================================

	drawLine(screenX0, screenY0, screenX1, screenY1, r, g, b);


	screenX0 *= globalDrawScale;
	screenX1 *= globalDrawScale;
	screenY0 *= globalDrawScale;
	screenY1 *= globalDrawScale;


	//get distance
	float dx = (screenX1 - screenX0);
	float dy = (screenY1 - screenY0);

	//get midpoint from distance
	float midX = (screenX0 + dx / 2);
	float midY = (screenY0 + dy / 2);

	//make distance half since we are using midpoint
	dx /= 2;
	dy /= 2;

	//get actual distance to midpoint
	float dist = (float)sqrt(dx * dx + dy * dy);

	//get distance ratio
	float distXRatio = dx / dist;
	float distYRatio = dy / dist;

	int arrowWidth = 12;

	//get perpendicular points to midpoint
	float midXPerpX1 = (midX + (arrowWidth / 2) * distYRatio);
	float midYPerpY1 = (midY - (arrowWidth / 2) * distXRatio);
	float midXPerpX2 = (midX - ((arrowWidth) / 2) * distYRatio);
	float midYPerpY2 = (midY + ((arrowWidth) / 2) * distXRatio);


	//get point 10 pixels past midpoint
	float pastMidX = (screenX0 + (dist + 16) * distXRatio);
	float pastMidY = (screenY0 + (dist + 16) * distYRatio);

	drawLine(midXPerpX1, midYPerpY1, midXPerpX2, midYPerpY2, r, g, b);
	drawLine(midXPerpX1, midYPerpY1, pastMidX, pastMidY, r, g, b);
	drawLine(midXPerpX2, midYPerpY2, pastMidX, pastMidY, r, g, b);
}


//=========================================================================================================================
void GLUtils::drawBox(float screenX0, float screenX1, float screenY0, float screenY1, int r, int g, int b)
{//=========================================================================================================================

	roundMe(screenX0, screenX1, screenY0, screenY1);


	screenX0 *= globalDrawScale;
	screenX1 *= globalDrawScale;
	screenY0 *= globalDrawScale;
	screenY1 *= globalDrawScale;


	glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);

	//top
	glBegin(GL_LINES);
	glVertex2f(screenX0, screenY0);
	glVertex2f(screenX1, screenY0);
	//glEnd();

	//bottom
	//glBegin(GL_LINES);
	glVertex2f(screenX0, screenY1);
	glVertex2f(screenX1, screenY1);
	//glEnd();


	//left
	//glBegin(GL_LINES);
	glVertex2f(screenX0, screenY0);
	glVertex2f(screenX0, screenY1);
	//glEnd();

	//right
	//glBegin(GL_LINES);
	glVertex2f(screenX1, screenY0);
	glVertex2f(screenX1, screenY1);
	glEnd();


	/*

	glBindTexture(GL_TEXTURE_2D, FileUtils::boxTexture.getTextureID());

	float tx0;
	float tx1;
	float ty0;
	float ty1;

	float x0;
	float x1;
	float y0;
	float y1;


	//top left
	tx0 = 0.0f;
	tx1 = 3.0f/FileUtils::boxTexture.getTextureWidth();
	ty0 = 0.0f;
	ty1 = 3.0f/FileUtils::boxTexture.getTextureHeight();

	x0 = getScreenLeft-3;
	x1 = getScreenLeft;
	y0 = getScreenTop-3;
	y1 = getScreenTop;

	GL.drawTexture(r,g,b,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,0);

	//top

	tx0 = 3.0f/FileUtils::boxTexture.getTextureWidth();
	tx1 = 6.0f/FileUtils::boxTexture.getTextureWidth();
	ty0 = 0.0f/FileUtils::boxTexture.getTextureHeight();
	ty1 = 3.0f/FileUtils::boxTexture.getTextureHeight();

	x0 = getScreenLeft;
	x1 = screenRight;
	y0 = getScreenTop-3;
	y1 = getScreenTop;

	GL.drawTexture(r,g,b,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,0);

	//top right

	tx0 = 6.0f/FileUtils::boxTexture.getTextureWidth();
	tx1 = 9.0f/FileUtils::boxTexture.getTextureWidth();
	ty0 = 0.0f/FileUtils::boxTexture.getTextureHeight();
	ty1 = 3.0f/FileUtils::boxTexture.getTextureHeight();

	x0 = screenRight;
	x1 = screenRight+3;
	y0 = getScreenTop-3;
	y1 = getScreenTop;

	GL.drawTexture(r,g,b,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,0);


	//left
	tx0 = 0.0f;
	tx1 = 3.0f/FileUtils::boxTexture.getTextureWidth();
	ty0 = 3.0f/FileUtils::boxTexture.getTextureHeight();
	ty1 = 6.0f/FileUtils::boxTexture.getTextureHeight();

	x0 = getScreenLeft-3;
	x1 = getScreenLeft;
	y0 = getScreenTop;
	y1 = screenBottom;

	GL.drawTexture(r,g,b,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,0);


	//right
	tx0 = 6.0f/FileUtils::boxTexture.getTextureWidth();
	tx1 = 9.0f/FileUtils::boxTexture.getTextureWidth();
	ty0 = 3.0f/FileUtils::boxTexture.getTextureHeight();
	ty1 = 6.0f/FileUtils::boxTexture.getTextureHeight();

	x0 = screenRight;
	x1 = screenRight+3;
	y0 = getScreenTop;
	y1 = screenBottom;

	GL.drawTexture(r,g,b,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,0);


	//bottom left
	tx0 = 0.0f;
	tx1 = 3.0f/FileUtils::boxTexture.getTextureWidth();
	ty0 = 6.0f/FileUtils::boxTexture.getTextureHeight();
	ty1 = 9.0f/FileUtils::boxTexture.getTextureHeight();

	x0 = getScreenLeft-3;
	x1 = getScreenLeft;
	y0 = screenBottom;
	y1 = screenBottom+3;

	GL.drawTexture(r,g,b,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,0);


	//bottom
	tx0 = 3.0f/FileUtils::boxTexture.getTextureWidth();
	tx1 = 6.0f/FileUtils::boxTexture.getTextureWidth();
	ty0 = 6.0f/FileUtils::boxTexture.getTextureHeight();
	ty1 = 9.0f/FileUtils::boxTexture.getTextureHeight();

	x0 = getScreenLeft;
	x1 = screenRight;
	y0 = screenBottom;
	y1 = screenBottom+3;

	GL.drawTexture(r,g,b,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,0);


	//bottom right
	tx0 = 6.0f/FileUtils::boxTexture.getTextureWidth();
	tx1 = 9.0f/FileUtils::boxTexture.getTextureWidth();
	ty0 = 6.0f/FileUtils::boxTexture.getTextureHeight();
	ty1 = 9.0f/FileUtils::boxTexture.getTextureHeight();

	x0 = screenRight;
	x1 = screenRight+3;
	y0 = screenBottom;
	y1 = screenBottom+3;

	GL.drawTexture(r,g,b,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,0);

	*/
}

//===========================================================================================================================
void GLUtils::drawFilledRect(int ri, int gi, int bi, float screenX0, float screenX1, float screenY0, float screenY1, float alpha)
{//===========================================================================================================================


	roundMe(screenX0, screenX1, screenY0, screenY1);


	screenX0 *= GLUtils::globalDrawScale;
	screenX1 *= GLUtils::globalDrawScale;
	screenY0 *= GLUtils::globalDrawScale;
	screenY1 *= GLUtils::globalDrawScale;


	glDisable(GL_TEXTURE_2D);

	// glColor4f(ri/255.0f,gi/255.0f,bi/255.0f, alpha);
	glColor4ub(ri, gi, bi, (GLubyte)(alpha * 255));

	if (glVersionMajor < 2)
	{
		//top
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(screenX0, screenY0);
		glVertex2f(screenX1, screenY0);
		//glEnd();		 		   
						 		   
		//bottom		 		   
		glVertex2f(screenX0, screenY1);
		glVertex2f(screenX1, screenY1);
		//glEnd();		 		   
						 		   
						 		   
		//left			 		   
		glVertex2f(screenX0, screenY0);
		glVertex2f(screenX0, screenY1);
		//glEnd();		 		   
						 		   
		//right			 		   
		glVertex2f(screenX1, screenY0);
		glVertex2f(screenX1, screenY1);
		glEnd();
		return;
	}

	box[0] = screenX0;
	box[1] = screenY0;
	box[2] = 0.0f;
	box[3] = screenX0;
	box[4] = screenY1;
	box[5] = 0.0f;
	box[6] = screenX1;
	box[7] = screenY1;
	box[8] = 0.0f;
	box[9] = screenX1;
	box[10] = screenY0;
	box[11] = 0.0f;

	//boxBuffer.put(box);
	//boxBuffer.position(0);

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 3 * 4, box);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
}

//=========================================================================================================================
void GLUtils::drawFilledRectXYWH(float x, float y, float w, float h, float r, float g, float b, float a)
{//=========================================================================================================================


	drawFilledRect((int)(r * 255.0f), (int)(g * 255.0f), (int)(b * 255.0f), x, x + w, y, y + h, a);


	//		glDisable(GL_TEXTURE_2D);
	//
	//
	//		float screen_x0 = x;
	//		float screen_x1 = x+w;
	//		float screen_y0 = y;
	//		float screen_y1 = y+h;
	//
	//
	//		box->get(0)=screen_x0;
	//		box[1]=screen_y0;
	//		box[2]=0.0f;
	//		box[3]=screen_x0;
	//		box[4]=screen_y1;
	//		box[5]=0.0f;
	//		box[6]=screen_x1;
	//		box[7]=screen_y1;
	//		box[8]=0.0f;
	//		box[9]=screen_x1;
	//		box[10]=screen_y0;
	//		box[11]=0.0f;
	//
	//		boxBuffer.put(box);
	//		boxBuffer.position(0);
	//
	//		col->get(0) = r;
	//		col[1] = g;
	//		col[2] = b;
	//		col[3] = a;
	//
	//		col[4] = r;
	//		col[5] = g;
	//		col[6] = b;
	//		col[7] = a;
	//
	//		col[8] = r;
	//		col[9] = g;
	//		col[10] = b;
	//		col[11] = a;
	//
	//		col[12] = r;
	//		col[13] = g;
	//		col[14] = b;
	//		col[15] = a;
	//
	//
	//		colBuffer.put(col);
	//		colBuffer.position(0);
	//
	//		glEnableClientState(GL_VERTEX_ARRAY);
	//		glEnableClientState(GL_COLOR_ARRAY);
	//
	//		glVertexPointer(3, 3*4,  boxBuffer);
	//		glColorPointer(4, 4*4,  colBuffer);
	//		glDrawArrays(GL_TRIANGLE_FAN,0,4);
	//
	//		glDisableClientState(GL_COLOR_ARRAY);
	//		glDisableClientState(GL_VERTEX_ARRAY);
	//
	//		glEnable(GL_TEXTURE_2D);
}


////=========================================================================================================================
//void GLUtils::drawLineRect(float x,float y,float width,float height,int thickness)
//{//=========================================================================================================================
//
//	if(rect==null)
//	{
//
//		Pixmap pixmap = new Pixmap( 1, 1, Format.RGBA8888 );
//		pixmap.setColor( 1f, 1f, 1f, 1f );
//		pixmap.fill();
//		rect = new Texture( pixmap );
//		pixmap.dispose();
//
////			//int width = 1; //1 pixel wide
////			//int height = 1; //1 pixel high
////			//int bpp = 4; //4 bytes per pixel (RGBA)
////
////			//create our buffer
////			ByteBuffer buffer = BufferUtils.newByteBuffer(1 * 1 * 4);
////
////			//put the Red, Green, Blue, and Alpha bytes
////			buffer.put((byte)0xFF).put((byte)0xFF).put((byte)0xFF).put((byte)0xFF);
////
////			//flip the buffer !!! this needs to be done before it can be read by GL
////			buffer.flip();
////
////
////
////			//here is an example of sending data to GL... we will talk
////			//more about this method in the Texture section
////			Gdx.gl.glTexImage2D(GL20.GL_TEXTURE_2D, 0, GL20.GL_RGBA, width, height, 0, GL20.GL_RGBA,
////			GL20.GL_UNSIGNED_BYTE, buffer);
//	}
//
//
//	SpriteBatch batch=BobsGame::spriteBatch;
//
//	batch->begin();
//	batch.draw(rect,x,y,width,thickness);
//	batch.draw(rect,x,y,thickness,height);
//	batch.draw(rect,x,y+height-thickness,width,thickness);
//	batch.draw(rect,x+width-thickness,y,thickness,height);
//	batch->end();
//
//
//}


////=========================================================================================================================
//void GLUtils::drawFilledRectXYWH(float x, float y, float width, float height, float r, float g, float b, float a)
//{ //=========================================================================================================================
//
//
//	if (rect == nullptr)
//	{
//
//		//Pixmap *pixmap = new Pixmap(1, 1, Pixmap::Format::RGBA8888);
//		//pixmap->setColor(1.0f, 1.0f, 1.0f, 1.0f);
//		//pixmap->fill();
//		//rect = new Texture(pixmap);
//		//pixmap->dispose();
//	}
//
//
//	float w = (float)BobsGame::FBOWidth;
//	float h = (float)BobsGame::FBOHeight;
//	float heightWidthRatio = h / w;
//
//	x = x / w;
//	y = y / h; // * heightWidthRatio;
//	width = width / w;
//	height = height / h; // * heightWidthRatio;
//
//
//	//SpriteBatch *spriteBatch = BobsGame::spriteBatch;
//	//spriteBatch->setColor(r, g, b, a);
//	//spriteBatch->draw(rect,x,y,width,height);
//
//}


//=========================================================================================================================
void GLUtils::drawLine(float x1, float y1, float x2, float y2, int thickness)
{//=========================================================================================================================
	//float dx = x2 - x1;
	//float dy = y2 - y1;
	//float dist = (float)sqrt(dx * dx + dy * dy);
	//float rad = (float)atan2(dy, dx);
	//batch.draw(rect, x1, y1, dist, thickness, 0, 0, rad);
}


//	//=========================================================================================================================
//	public static void drawFilledRectXYWH(float x,float y,float width,float height,float r,float g,float b,float a)
//	{//=========================================================================================================================
//
//
//		float w = BobsGame::FBOWidth;
//		float h = BobsGame::FBOHeight;
//		float heightWidthRatio = h / w;
//
//		x = x/w;
//		y = y/h;// * heightWidthRatio;
//		width = width/w;
//		height = height/h;// * heightWidthRatio;
//
//		//Camera camera = BobsGame::camera;
//		//camera.update();
//
//
//
//
//
//		ShapeRenderer shapeRenderer = BobsGame::shapeRenderer;
//
//		//shapeRenderer.setProjectionMatrix(camera.combined);
//
////		 shapeRenderer.begin(ShapeType.Line);
////		 shapeRenderer.color(1, 1, 0, 1);
////		 shapeRenderer.line(x, y, x2, y2);
////		 shapeRenderer.rect(x, y, width, height);
////		 shapeRenderer.circle(x, y, radius);
////		 shapeRenderer->end();
//
//		shapeRenderer.begin(ShapeType.Filled);
//		shapeRenderer.setColor(r, g, b, a);
//		shapeRenderer.rect(x, y, width, height);
//		//shapeRenderer.circle(x, y, radius);
//		shapeRenderer->end();
//
//	}


//===========================================================================================================================
void GLUtils::old_clear()
{//===========================================================================================================================
	//if (useFBO)
	{
		//attach a texture to a framebuffer, render directly into texture
		glBindFramebuffer(GL_FRAMEBUFFER, postColorFilterFBO);//glBindFramebufferEXT, GL_FRAMEBUFFER_EXT
	}
	glClear(GL_COLOR_BUFFER_BIT);


	glColor4f(1, 1, 1, 1);

}


//===========================================================================================================================
void GLUtils::old_render()
{//===========================================================================================================================

 //GLint loc;
 //loc = glGetUniformLocation(p->get(0), "Tex0");
 //glUniform1i(loc, screen);

 //glUseProgram(p->get(0));





 //GLUtils::drawFilledRectXYWH(0, 0, 640, 480, 1.0f, 0, 1.0f, 1.0f);


 //i wanted to draw everything into a single texture so i could zoom into it? i think thats why
 //i think i wanted to double the resolution and draw everything at 2x


//	if (!useFBO)
//	{
//		//=====================
//		//Copy texture from back buffer manually (slow)
//		//=====================
//
//		float pw = (float)getViewportWidth();
//		float ph = (float)getViewportHeight();
//		if (Math::IsNPOT((int)pw, (int)ph))
//		{
//			pw = (float)powf(2.0, ceilf(logf((float)pw) / logf(2.0f)));
//			ph = (float)powf(2.0, ceilf(logf((float)ph) / logf(2.0f)));
//		}
//
//		float pwdiff = pw - getViewportWidth();
//		float phdiff = ph - getViewportHeight();
//
//		//bind screen texture to 2d
//		glBindTexture(GL_TEXTURE_2D, postColorFilterFBO_Texture_Attachment0);
//
//		//copy back buffer image into screen texture
//		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLint)0, (GLint)(getViewportHeight() / 2 - getViewportHeight()), (GLsizei)pw, (GLsizei)ph, 0);
//		//clear back buffer
//		glClear(GL_COLOR_BUFFER_BIT);
//		//draw screen to back buffer, but flipped because its upside down for some reason
//		gl_draw_flipped(postColorFilterFBO_Texture_Attachment0, 0, -(phdiff * ZOOM), getViewportWidth() / 2 + (pwdiff * ZOOM), getViewportHeight() / 2 + (phdiff * ZOOM));
//	}


	//if (useFBO)
	{
		//Be sure to reset the rendering state afterwards by binding the zero framebuffer object (the screen):
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

		//clear the screen
		glClear(GL_COLOR_BUFFER_BIT);


		/*
		GLint loc;
		loc = glGetUniformLocation(p[1], "Tex0");
		glUniform1i(loc, 0);

		loc = glGetUniformLocation(p[1], "Gamma");
		glUniform1f(loc, 0.9f);

		glUseProgram(p[1]);
		*/

		gl_draw_flipped(postColorFilterFBO_Texture_Attachment0, 0, 0//-(((getViewportHeight()/4)*((float)((float)(getViewportHeight()*2)/(float)(getViewportHeight()*2)))))
			,
			(getViewportWidth() * ZOOM)//*2*((float)((float)(getViewportWidth()*2)/(float)(getViewportWidth()*2))))
			,
			(getViewportHeight() * ZOOM)//*2*((float)((float)(getViewportHeight()*2)/(float)(getViewportHeight()*2))))
		);
	}



}




//===========================================================================================================================
BobTexture* GLUtils::loadTextureFromSurface(string filename, SDL_Surface* surfacein)
{//===========================================================================================================================

	SDL_Surface* surface = surfacein;

	glEnable(GL_TEXTURE_2D);

	BobTexture *tex = nullptr;

	if (textureCache.containsKey(filename))
	{
		tex = textureCache.get(filename);
		if (tex != nullptr)
		{
			return tex;
		}
	}


	GLuint textureID = createTextureID();
	tex = new BobTexture(filename, textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	int imageWidth = surface->w;
	int imageHeight = surface->h;

	bool hasAlpha = true;// surface->format->BytesPerPixel == 4;
	int texWidth = Math::get2Fold(imageWidth);
	int texHeight = Math::get2Fold(imageHeight);

	tex->setImageWidth(imageWidth);
	tex->setImageHeight(imageHeight);
	tex->setTextureWidth(texWidth);
	tex->setTextureHeight(texHeight);
	tex->setAlpha(hasAlpha);


	GLint *maxTexSizeArray = new GLint[16];
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, maxTexSizeArray);
	int max = maxTexSizeArray[0];
	if ((texWidth > max) || (texHeight > max))
	{
		log.error("Allocating a texture too big for the current hardware");
	}
	delete [] maxTexSizeArray;
	//int srcPixelFormat = hasAlpha ? GL_RGBA : GL_RGB;



	//have to do this because the surface is not power of 2
	SDL_Surface* temp = nullptr;
	//bool freeTemp = false;

	//if (surface->format->BytesPerPixel < 4)
	{
		//freeTemp = true;

		//blit from bitmap to a temporary surface with 32 bits per pixel
		temp = SDL_CreateRGBSurface(SDL_SWSURFACE, texWidth, texHeight, 32, rmask, gmask, bmask, amask);

		SDL_Rect srcArea;
		srcArea.x = 0;
		srcArea.y = 0;
		srcArea.w = imageWidth;
		srcArea.h = imageHeight;

		SDL_BlitSurface(surface, &srcArea, temp, NULL);

		surface = temp;
	}


	GLUtils::setDefaultTextureParams();


	if (SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);

	/*
	void glTexImage2D(GLenum target,
	GLint level,
	GLint internalFormat,
	GLsizei width,
	GLsizei height,
	GLint border,
	GLenum format,
	GLenum type,
	const GLvoid * data);
	*/
	GLint level = 0;
	GLint border = 0;
	glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, texWidth, texHeight, border, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);


	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);

	//tex->setCacheName(filename);
	textureCache.put(filename, tex);

	GLUtils::texturesLoaded++;
	GLUtils::textureBytesLoaded += (tex->getTextureWidth()*tex->getTextureHeight() * 4);


	//free temporary surface
	//if(freeTemp)
		SDL_FreeSurface(temp);


	return tex;

}

////===========================================================================================================================
//void GLUtils::delete_texture(texture_STRUCT* temp_TEXTURE)
//{//===========================================================================================================================
//
//
//	temp_TEXTURE->image_w = 0;
//	temp_TEXTURE->image_h = 0;
//	temp_TEXTURE->texture_w = 0;
//	temp_TEXTURE->texture_h = 0;
//
//
//	if (glIsTexture(temp_TEXTURE->texture_id))
//	{
//		glDeleteTextures(1, &temp_TEXTURE->texture_id);
//		//glFlush();
//	}
//
//	free(temp_TEXTURE);
//}




//=========================================================================================================================
void GLUtils::clearCache(const string &name)
{//=========================================================================================================================
 //texturesLinear->erase(name);
	textureCache.removeAt(name);
}

//=========================================================================================================================
void GLUtils::clearCache()
{//=========================================================================================================================
 //texturesLinear->clear();
	textureCache.clear();
}

//=========================================================================================================================
GLuint GLUtils::createTextureID()
{//=========================================================================================================================
	GLuint *tmp = new GLuint[1];
	glGenTextures(1, tmp);
	return tmp[0];
}

//=========================================================================================================================
BobTexture *GLUtils::getTextureFromData(string textureName, int imageWidth, int imageHeight, u8* data)
{//=========================================================================================================================


	glEnable(GL_TEXTURE_2D);

	BobTexture *tex = nullptr;

	if (textureCache.containsKey(textureName))
	{
		tex = textureCache.get(textureName);
		if (tex != nullptr)
		{
			return tex;
		}
	}


	GLuint textureID = createTextureID();
	tex = new BobTexture(textureName, textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);


	//int imageWidth = imageData->w;
	//int imageHeight = imageData->h;
	bool hasAlpha = true;
	int texWidth = Math::get2Fold(imageWidth);
	int texHeight = Math::get2Fold(imageHeight);

	tex->setImageWidth(imageWidth);
	tex->setImageHeight(imageHeight);
	tex->setTextureWidth(texWidth);
	tex->setTextureHeight(texHeight);
	tex->setAlpha(hasAlpha);


	GLint maxTexSize[16];
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, maxTexSize);
	int max = maxTexSize[0];
	if ((texWidth > max) || (texHeight > max))
	{
		log.error("Allocating a texture too big for the current hardware");
	}



	u8* t = new u8[texWidth*texHeight * 4];

	for (int y = 0; y<imageHeight; y++)
		for (int x = 0; x<imageWidth; x++)
		{
			t[(((y*texWidth) + x) * 4) + 0] = data[(((y*imageWidth) + x) * 4) + 0];//bgra
			t[(((y*texWidth) + x) * 4) + 1] = data[(((y*imageWidth) + x) * 4) + 1];
			t[(((y*texWidth) + x) * 4) + 2] = data[(((y*imageWidth) + x) * 4) + 2];//bgra
			t[(((y*texWidth) + x) * 4) + 3] = data[(((y*imageWidth) + x) * 4) + 3];

		}
	GLUtils::setDefaultTextureParams();

	data = t;

	/*
	void glTexImage2D(GLenum target,
	GLint level,
	GLint internalFormat,
	GLsizei width,
	GLsizei height,
	GLint border,
	GLenum format,
	GLenum type,
	const GLvoid * data);
	*/
	GLint level = 0;
	GLint border = 0;
	glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, texWidth, texHeight, border, GL_RGBA, GL_UNSIGNED_BYTE, data);

	delete[] t;


	//tex->setCacheName(textureName);
	textureCache.put(textureName, tex);

	GLUtils::texturesLoaded++;
	GLUtils::textureBytesLoaded += (tex->getTextureWidth()*tex->getTextureHeight() * 4);


	return tex;
}



//=========================================================================================================================
BobTexture *GLUtils::getTextureFromPNG(string filename)// , const string &resourceName)//, int target, int magFilter, int minFilter, bool flipped)//, ArrayList<int> &transparentRGB)
{//=========================================================================================================================


	filename = Main::getPath() + filename;

	glEnable(GL_TEXTURE_2D);

	BobTexture *tex = nullptr;


	if (textureCache.containsKey(filename))
	{
		tex = textureCache.get(filename);
		if (tex != nullptr)
		{
			return tex;
		}
	}


	GLuint textureID = createTextureID();
	tex = new BobTexture(filename, textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);


	SDL_Surface* imageSurface = IMG_Load(filename.c_str());
	//SDL_Surface* imageSurface = STBIMG_Load(filename.c_str());
	if (imageSurface == NULL)
	{
		log.error("ERROR: Couldn't load "+ filename +": "+string(SDL_GetError()));
		//exit(1);
		return nullptr;
	}


	int imageWidth = imageSurface->w;
	int imageHeight = imageSurface->h;
	bool hasAlpha = imageSurface->format->BytesPerPixel == 4;
	int texWidth = Math::get2Fold(imageWidth);
	int texHeight = Math::get2Fold(imageHeight);

	tex->setImageWidth(imageWidth);
	tex->setImageHeight(imageHeight);
	tex->setTextureWidth(texWidth);
	tex->setTextureHeight(texHeight);
	tex->setAlpha(true);


	GLint maxTexSizeArray[16];
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, maxTexSizeArray);
	int max = maxTexSizeArray[0];
	if ((texWidth > max) || (texHeight > max))
	{
		log.error("Allocating a texture too big for the current hardware");
	}
	
	

	u8* data = (u8*)imageSurface->pixels;
	u8* t = new u8[texWidth*texHeight * 4];

	//for(int i=0;i<texWidth*texHeight * 4;i++)t[i]=0;

	if (hasAlpha)
	{
		for (int y = 0; y < imageHeight; y++)
			for (int x = 0; x < imageWidth; x++)
			{
				bool flip = false;
				if (flip == false)
				{
					t[(((y*texWidth) + x) * 4) + 0] = data[(((y*imageWidth) + x) * 4) + 0];//bgra
					t[(((y*texWidth) + x) * 4) + 1] = data[(((y*imageWidth) + x) * 4) + 1];
					t[(((y*texWidth) + x) * 4) + 2] = data[(((y*imageWidth) + x) * 4) + 2];//bgra
					t[(((y*texWidth) + x) * 4) + 3] = data[(((y*imageWidth) + x) * 4) + 3];
				}
				else
				{

					t[(((y*texWidth) + x) * 4) + 0] = data[((((imageHeight - (y + 1))*imageWidth) + x) * 4) + 0];
					t[(((y*texWidth) + x) * 4) + 1] = data[((((imageHeight - (y + 1))*imageWidth) + x) * 4) + 1];
					t[(((y*texWidth) + x) * 4) + 2] = data[((((imageHeight - (y + 1))*imageWidth) + x) * 4) + 2];
					t[(((y*texWidth) + x) * 4) + 3] = data[((((imageHeight - (y + 1))*imageWidth) + x) * 4) + 3];
				}
			}
	}
	else
	{
		for (int y = 0; y<imageHeight; y++)
			for (int x = 0; x<imageWidth; x++)
			{

				t[(((y*texWidth) + x) * 4) + 0] = data[(((y*imageWidth) + x) * 3) + 0];//bgra
				t[(((y*texWidth) + x) * 4) + 1] = data[(((y*imageWidth) + x) * 3) + 1];
				t[(((y*texWidth) + x) * 4) + 2] = data[(((y*imageWidth) + x) * 3) + 2];//bgra
				t[(((y*texWidth) + x) * 4) + 3] = 255;
			}
	}
	GLUtils::setDefaultTextureParams();

	//data = t;

	/*
	void glTexImage2D(GLenum target,
	GLint level,
	GLint internalFormat,
	GLsizei width,
	GLsizei height,
	GLint border,
	GLenum format,
	GLenum type,
	const GLvoid * data);
	*/
	GLint level = 0;
	GLint border = 0;
	glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, texWidth, texHeight, border, GL_RGBA, GL_UNSIGNED_BYTE, t);

	delete[] t;

	//log.info("SDL_FreeSurface");
	SDL_FreeSurface(imageSurface);




	//tex->setCacheName(filename);
	textureCache.put(filename, tex);


	GLUtils::texturesLoaded++;
	GLUtils::textureBytesLoaded += (tex->getTextureWidth()*tex->getTextureHeight() * 4);


	return tex;
}


//===========================================================================================================================
void GLUtils::draw_texture_struct(texture_STRUCT* PLAYER_TEXTURE, float x, float y)
{//===========================================================================================================================

	GLuint texture_id = PLAYER_TEXTURE->texture_id;
	float w = (float)PLAYER_TEXTURE->texture_w;
	float h = (float)PLAYER_TEXTURE->texture_h;


	glBindTexture(GL_TEXTURE_2D, texture_id);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);

	GLfloat box[] = { x,y + h,0, x + w,y + h,0, x + w, y, 0, x,y,0 };
	GLfloat tex[] = { 0,1, 1,1, 1,0, 0,0 };

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, box);
	glTexCoordPointer(2, GL_FLOAT, 0, tex);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


//===========================================================================================================================
void GLUtils::draw_texture_alpha(GLuint textureid, float x, float y, float w, float h, float tw, float th, float f, float a)
{//===========================================================================================================================


	if (a == 1.0f && glDrawTexiES != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, textureid);

		glActiveTexture(textureid);

		//have to copy from negative y inside the texture, otherwise its flipped upside down
		GLint param[4] = { 0,0,0,0 };
		param[0] = (int)(0);//0-(tw-w);
		param[1] = (int)(0 - (th - h));
		param[2] = (int)(w);
		param[3] = (int)(0 - h);

		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_CROP_RECT_OES, param);

		//glBindTexture(GL_TEXTURE_2D,textureid);
		glEnable(GL_TEXTURE_2D);
		glColor4f(1, 1, 1, 1);


		//draw it with mirrored coords
		glDrawTexiES((int)x, (int)(240 - (y + h)), (int)0, (int)w, (int)h);

		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textureid);


		if (f == 1)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}


		glEnable(GL_TEXTURE_2D);


		float tx = (float)w / (float)tw;
		float ty = (float)h / (float)th;


		GLfloat col[] = {
			1, 1, 1, a,
			1, 1, 1, a,
			1, 1, 1, a,
			1, 1, 1, a
		};


		GLfloat box[] = {
			x, y, 0,
			x, y + h, 0,
			x + w, y + h, 0,
			x + w, y, 0
		};

		GLfloat tex[] = {
			0,0,
			0,ty,
			tx,ty,
			tx,0
		};

		//GLfloat tex[] ={ //before flipping because drawtex is upside down
		//0,0,
		//0,ty,
		//tx,ty,
		//tx,0
		//};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, box);
		glColorPointer(4, GL_FLOAT, 0, col);
		glTexCoordPointer(2, GL_FLOAT, 0, tex);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glDisable(GL_TEXTURE_2D);
	}

	e("draw_texture_alpha");
}

//===========================================================================================================================
void GLUtils::draw_texture(GLuint textureid, float x, float y, float w, float h)
{//===========================================================================================================================
	draw_texture_alpha(textureid, x, y, w, h, w, h, 0, 1);

	//fprintf(stderr,"drawing texture: %d\n",textureid);
}

//===========================================================================================================================
void GLUtils::gl_draw_flipped(GLuint textureid, float x, float y, float w, float h)
{//===========================================================================================================================

	glBindTexture(GL_TEXTURE_2D, textureid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GLOBAL_FRAMEBUFFER_FILTER_TYPE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GLOBAL_FRAMEBUFFER_FILTER_TYPE);

	glEnable(GL_TEXTURE_2D);


	GLfloat box[] = {
		x, y, 0,
		x, y + h, 0,
		x + w, y + h, 0,
		x + w, y, 0
	};

	GLfloat tex[] = {
		0,1,
		0,0,
		1,0,
		1,1
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, box);
	glTexCoordPointer(2, GL_FLOAT, 0, tex);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	e("gl_draw_flipped");
}

//===========================================================================================================================
void GLUtils::draw_sprite(SPRITE* s)
{//===========================================================================================================================
	GLuint texid = s->texture_id;
	float x = s->screen_x * ZOOM;


	float y = s->screen_y * ZOOM;

	//we're sending in the sprite draw_size_y, not the texture_size_y, for the texture coords
	float w = (s->draw_size_x * (s->scale * (1.0f + (s->gfx->hq2x * -0.5f)))) * ZOOM;
	float h = (s->draw_size_y * (s->scale * (1.0f + (s->gfx->hq2x * -0.5f)))) * ZOOM;

	float tw = (s->gfx->texture_size_x * (s->scale * (1.0f + (s->gfx->hq2x * -0.5f)))) * ZOOM;
	float th = (s->gfx->texture_size_y * (s->scale * (1.0f + (s->gfx->hq2x * -0.5f)))) * ZOOM;

	bool f = 0;
	if ((s->scale != 1.0f && s->scale != 2.0f) || s->gfx->hq2x == 1)f = 1;//linear filter

	float a = s->alpha / 255.0f;


	draw_texture_alpha(texid, x, y, w, h, tw, th, f, a);


	//fprintf(stderr,"drawing sprite: %s\n",s->gfx->FileName);
}

//===========================================================================================================================
void GLUtils::gl_draw_sprites(int layer)
{//===========================================================================================================================

 /*
 int i=0;
 for(i=255;i>=0;i--)
 {

 //if(PLAYER_id_gfx_slot->get(i)!=-1&&((PLAYER_id_priority->get(i)==layer)||(layer==4&&PLAYER_id_priority->get(i)>=4)))
 if(HARDWARE_sprites->get(i)!=NULL)
 {

 SPRITE* sprite = HARDWARE_sprites->get(i);

 if((sprite->layer==layer)||(layer==4&&sprite->layer>=4))
 {
 if(GLOBAL_sprite_layer_enabled)
 {
 if(glIsTexture(sprite->texture_id))
 {
 draw_sprite(sprite);

 }
 else
 {
 ERROR_set_error("gl_draw_sprites:sprite has no texture! \n");//error
 }
 }
 }
 }
 }
 */
}


////===========================================================================================================================
//void GLUtils::gl_draw_bg(int bg)
//{//===========================================================================================================================
//
//	if(metatile_map==1)
//	{
//
//		if(
//		(bg==3&&GLOBAL_bg_layer_enabled[3])||
//		(bg==0&&GLOBAL_bg_layer_enabled->get(0))||
//		(bg==2&&GLOBAL_bg_layer_enabled[2])||
//		(bg==1&&GLOBAL_bg_layer_enabled[1])
//		)
//		{
//			if(HARDWARE_map_tileset!=NULL&&HARDWARE_map_palette!=NULL)
//			{
//				//check for each metatile coordinate that should be onscreen.
//				//if it's there, draw it. if it isn't, make it, and draw it.
//
//				int s=0;
//
//				//int x=0;
//				//int y=0;
//
//				//starting at first possible grid position off left of screen (metatiles will always be drawn at even intervals metatile_size * n)
//				///i dont really need to do this in order! big waste of cpu!
//				///for(y=(MAP_cam_y-(METATILE_SIZE/2))-((MAP_cam_y-(METATILE_SIZE/2))%METATILE_SIZE);y<(MAP_cam_y+(METATILE_SIZE/2))+GAME_VIEWPORT_HEIGHT_PIXELS;y+=METATILE_SIZE)
//					///for(x=(MAP_cam_x-(METATILE_SIZE/2))-((MAP_cam_x-(METATILE_SIZE/2))%METATILE_SIZE);x<(MAP_cam_x+(METATILE_SIZE/2))+GAME_VIEWPORT_WIDTH_PIXELS;x+=METATILE_SIZE)
//					{
//
//						for(s=0;s<METATILES_POSSIBLE;s++)
//							if(metatile_used[bg*METATILES_POSSIBLE+s]==1)
//							{
//								if(glIsTexture(GLTex_map_metatile[bg*METATILES_POSSIBLE+s]))
//								{
//									///if(metatile_x[bg*METATILES_POSSIBLE+s]==x&&metatile_y[bg*METATILES_POSSIBLE+s]==y)//if it exists, draw it.
//									{
//										draw_texture(GLTex_map_metatile[((bg*METATILES_POSSIBLE)+s)], ZOOM*(metatile_x[bg*METATILES_POSSIBLE+s]-MAP_cam_x), ZOOM*(metatile_y[bg*METATILES_POSSIBLE+s]-MAP_cam_y),ZOOM*METATILE_SIZE,ZOOM*METATILE_SIZE);
//									}
//								}
//								else
//								{
//									ERROR_set_error("trying to draw a metatile that doesnt exist!");
//
//								}
//							}
//					}
//			}
//		}
//
//	}
//	else
//	if(metatile_map==0)
//	{
//		//opengl
//		if(bg==3)if(GLOBAL_bg_layer_enabled[3])if(HARDWARE_map_3!=NULL)if(bg_is_on[3])if(glIsTexture(GLTex_bg[3]))draw_texture(GLTex_bg[3],ZOOM*(0-MAP_cam_x),ZOOM*(0-MAP_cam_y), ZOOM*bg_texture_size_x[3], ZOOM*bg_texture_size_y[3]);
//		if(bg==0)if(GLOBAL_bg_layer_enabled->get(0))if(HARDWARE_map_0!=NULL)if(bg_is_on->get(0))if(glIsTexture(GLTex_bg->get(0)))draw_texture(GLTex_bg->get(0),ZOOM*(0-MAP_cam_x),ZOOM*(0-MAP_cam_y), ZOOM*bg_texture_size_x->get(0), ZOOM*bg_texture_size_y->get(0));
//		if(bg==2)if(GLOBAL_bg_layer_enabled[2])if(HARDWARE_map_2!=NULL)if(bg_is_on[2])if(glIsTexture(GLTex_bg[2]))draw_texture(GLTex_bg[2],ZOOM*(0-MAP_cam_x),ZOOM*(0-MAP_cam_y), ZOOM*bg_texture_size_x[2], ZOOM*bg_texture_size_y[2]);
//		if(bg==1)if(GLOBAL_bg_layer_enabled[1])if(HARDWARE_map_1!=NULL)if(bg_is_on[1])if(glIsTexture(GLTex_bg[1]))draw_texture(GLTex_bg[1],ZOOM*(0-MAP_cam_x),ZOOM*(0-MAP_cam_y), ZOOM*bg_texture_size_x[1], ZOOM*bg_texture_size_y[1]);
//
//		//sdl
//		//if(SDLSurface_bg->get(0)!=NULL)
//		//SDL_BlitSurface( SDLSurface_bg->get(0), NULL, SDLSurface_screen, &mapxy->get(0) );
//
//	}
//
//}


//===========================================================================================================================
void GLUtils::draw_black_overlay()
{//===========================================================================================================================
 /*glDisable(GL_TEXTURE_2D);

 glColor4f(r,g,b,a);

 GLfloat box[] = {x,y + h,0, x + w,y + h,0, x + w, y, 0, x,y,0};
 GLfloat tex[] = {0,1, 1,1, 1,0, 0,0};

 glEnableClientState(GL_VERTEX_ARRAY);
 glEnableClientState(GL_TEXTURE_COORD_ARRAY);

 glVertexPointer(3, GL_FLOAT, 0,box);
 glTexCoordPointer(2, GL_FLOAT, 0, tex);

 glDrawArrays(GL_TRIANGLE_FAN,0,4);

 glDisableClientState(GL_VERTEX_ARRAY);
 glDisableClientState(GL_TEXTURE_COORD_ARRAY);

 glEnable(GL_TEXTURE_2D);*/

	float x = 0;
	float y = 0;
	float w = (float)getViewportWidth();
	float h = (float)getViewportHeight();
	float r = 0;
	float g = 0;
	float b = 0;
	//float a = fade_alpha / 255.0f;
	float a = 1;

	glDisable(GL_TEXTURE_2D);

	GLfloat box[] = { x,y + h,0, x + w,y + h,0, x + w, y, 0, x,y,0 };

	GLfloat col[] = {
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, box);
	glColorPointer(4, GL_FLOAT, 0, col);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glEnable(GL_TEXTURE_2D);
}

//===========================================================================================================================
void GLUtils::set_zoom()
{//===========================================================================================================================

	if (ZOOM != ZOOMto)
	{
		if (ZOOM > ZOOMto)ZOOM -= 0.05f;
		if (ZOOM < ZOOMto)ZOOM += 0.05f;
	}

	//getViewportWidth() = getViewportWidth() / 2.0f / ZOOM;//256
	//getViewportHeight() = getViewportHeight() / 2.0f / ZOOM;//192

	//SCREEN_WIDTH_TILES = getViewportWidth() / 8.0f;//32
	//SCREEN_HEIGHT_TILES = getViewportHeight() / 8.0f;//24
}

