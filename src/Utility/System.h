//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;

class ConsoleText;

class System
{
public:

	//const static char pathSeparator = '/';
	
	static Logger log;


	string sessionToken = "";


	//InetAddress addr = InetAddress.getByName(refAddr);
	//String name = addr.getHostName();


	//TODO:
	static int downloadRate;// = 0;
	static int uploadRate;// = 0;
	static int ping;// = 0;


	static string internetProviderString;// = "";

	//TODO: resolve this somehow by the IP somewhere, probably from the client is better.
	//s.internetProviderString =


	static string browserUserAgentString;// = "";
	static string browserAppNameVersionString;// = "";
	static string browserReferrerString;// = "";

	static string getEnvProcessorIdentifier;// = "";
	static string getEnvProcessorArchitecture;// = "";
	static string getEnvNumberOfProcessors;// = "";


	static float timeZoneGMTOffset;// = 0.0f;


	//TODO: SIGAR stuff
	//cpu clock speed
	//actual GPU hardware name, i.e. radeon hd 4700, 512 mb


	//public String operatingSystemString = "";
	//public String javaInfoString = "";
	//public String cpuString = "";
	//public String gpuString = "";
	//public String memoryString = "";
	//public String joysticksString = "";
	//public String soundDeviceString = "";
	//public String webcamString = "";
	//public String diskSpaceString = "";
	//public String homeDirString = "";
	//public String cacheSizeString = "";


	//done

	static string jreVersion;
	static string jreVendor;
	//public String jreVendorURL;
	static string jreHomeDir;
	//public String jvmSpecVersion;
	//public String jvmSpecVendor	;
	//public String jvmSpecName;
	static string jvmVersion;
	//public String jvmVendor	;
	static string jvmName;
	//public String jreSpecVersion;
	//public String jreSpecVendor	;
	//public String jreSpecName;
	static string javaClassVersion;
	static string javaClassPath;
	static string javaLibraryPath;
	static string javaTempDir;
	//public String javaJITCompiler;
	//public String javaExtensionPath	;
	static string osName;
	static string osArch;
	static string osVersion;
	static string osUserAccountName;
	static string osHomeDir;
	static string workingDir;

	static int displayWidth;// = -1;
	static int displayHeight;// = -1;
	static int displayBPP;// = -1;
	static int displayFreq;// = -1;
	static bool shaderCompiled;// = false;
	static bool canUseFBO;// = false;
	static bool usingVSync;// = false;
	static string displayAdapter;
	static string displayDriver;
	static string lwjglVersion;
	static bool lwjglIs64Bit;// = false;
	static string lwjglPlatformName;
	static int numCPUs;// = -1;

	static int numControllersFound;// = -1;
	static string controllersNames;

	static string glVendor;
	static string glVersion;
	static string glRenderer;
	static string shaderVersion;
	static string glExtensions;

	static void initSystemInfo();
	static void initClockAndTimeZone();

	virtual string split(const string& in);


	virtual string printString();


	virtual string encode();


	virtual void decode(string& s);


	//virtual PreparedStatement *getInsertStatement(Connection *databaseConnection, const string &emailAddress, Client *cc, const string &ipAddress);

	static void logSystemInfo();


public:


	static ConsoleText* totalRendersText;
	static ConsoleText* totalUpdatesText;
	static ConsoleText* rendersPerSecondText;
	static ConsoleText* averageRendersPerSecondText;
	static ConsoleText* updatesPerSecondText;
	static ConsoleText* rendersSkippedText;
	static ConsoleText* updatesSkippedText;
	static ConsoleText* averageTicksPerFrameText;
	static ConsoleText* averageTicksPerUpdateText;

	static ConsoleText* upTimeText;

	const static int amtTicksTexts = 10;
	static ConsoleText* ticksText[amtTicksTexts];


private:
	static long long lastRenderTime;
	static long long lastUpdateTime;
	static int ticksTextCount;
	static long long averageTicksPerRenderLastSecond;
	static long long averageTicksPerUpdateLastSecond;


public:


	static void initFrameStats();


	static void updateFrameStats();


	static ConsoleText* mxThreadCountText;


	static void initThreadStats();


	static void updateThreadStats();


	static ConsoleText* memoryText;
	static ConsoleText* texturesLoadedText;// = Console::debug("texturesLoadedText");
	static ConsoleText* textureBytesLoadedText;// = Console::debug("textureBytesLoadedText");


	static int mb;

	static long long usedMemory;
	static long long maxUsedMemory;
	static long long totalMemory;
	static long long freeMemory;
	static long long maxMemory;

	//mxbean
	//DebugText mxBeanHeapMemoryText;
	//DebugText mxBeanNonHeapMemoryText;
	//DebugText mxBeanUnfinalizedObjectsText;
	//DebugText memPoolThresholdCountText;
	//DebugText mxOSInfoSystemLoadText;

	ConsoleText* vramText;


	//mxbean
	//long committedNonHeapMemory = 0;
	//long initNonHeapMemory = 0;
	//long maxNonHeapMemory = 0;
	//long usedNonHeapMemory = 0;

	//GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
	//GraphicsDevice[] gs = ge.getScreenDevices();
	//GraphicsDevice gd = gs->get(0);


	static void initMemoryStats();


	static void updateMemoryStats();


	static void initDebugInfo();


	static void updateDebugInfo();


private:

	//-----------------------------
	//old timer stuff
	//-----------------------------
	//static void calculate_fps();
	//	static int framesrendered;
	//	static int secondspassed;
	//	static int lastsecondspassed;
	//	static int fps;
	//static int vbl_ticks;
	//static int render_ticks;
	//static LARGE_INTEGER highResolutionTicksPerSecond;//=0;
	//static LARGE_INTEGER newvbltimer;//=0;
	//static LARGE_INTEGER lastvbltimer;//=0;
	//static int timer_ticks;


	//static LARGE_INTEGER highResTimer;//=0;
	//static LARGE_INTEGER highResolutionTicksPerSecond;//=0;
	static long long highResTimer;//=0;
	static long long highResolutionTicksPerSecond;//=0;
	static long long timerOffset;


	static int totalSecondsPassed;
	static int averageFPSTestSecondsPassed;
	static int averageRendersPerSecond;
	static int totalUpdates;
	static int totalRenders;
	static int averageFPSTestTotalRenders;
	static long long lastUpdateHighResTime; //Sys.getTime();
	static long long lastRenderHighResTime; //Sys.getTime();
	static long long currentHighResTime;

	

	static int updatesThisSecond;
	static int rendersThisSecond;
	static long long lastSecondTime;
	//private static long last100Ticks=lastRenderHighResTime;

	static long long totalUpdateTicks;
	static long long totalRenderTicks;//only for whilefix and no vsync
	static int rendersSkipped;
	static int updatesSkipped;
	


public:
	static int ticksPassedThisRender;
	static int ticksPassedThisUpdate;
	static double cpuFreq;
	static void initTimers();


	static void updateRenderTimers();
	static void updateUpdateTimers();


	//static long long nanoTime();

	static double getTicksBetweenTimes(long long start, long long finish);
	static long long currentHighResTimer();
	
	static int getTotalRenderTicksPassed();
	static void resetTotalRenderTicksPassed();

private:
	static long long getPerformanceCounter();
};

