// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FBHALPER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FBHALPER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef FBHALPER_EXPORTS
#define FBHALPER_API __declspec(dllexport)
#else
#define FBHALPER_API __declspec(dllimport)
#endif
#include <string>
#include <map>
 
using namespace std;
// This class is exported from the fbHalper.dll
class FBHALPER_API CfbHalper {
public:
	CfbHalper(void);
	// TODO: add your methods here.
	   
      int  add(int a,int b);
      int  mul(int a,int b);
      int  sub(int a,int b);
      string returnToken();
      bool getUserInfo(map<std::string,std::string>& userDate);
      bool sendToAppWall(std::string str);
      bool sendToUserWall(std::string str);
};

extern FBHALPER_API int nfbHalper;
FBHALPER_API int fnWin32DLL(void);



 
