#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------






Logger FileUtils::log = Logger("FileUtils");

//void FileUtils::fixPath( string &fullname )
//{
//	for ( int i = 0; i < (int)fullname.length(); i++ )
//	{
//		if ( fullname[ i ] == '\\' )
//		{
//			fullname[ i ] = '/';
//		}
//	}
//}












#include <iostream>

#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Delegate.h"
#include "Poco/Zip/Decompress.h"
#include "Poco/Process.h"
#include "Poco/DirectoryIterator.h"
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Process;
using Poco::Path;
using Poco::Delegate;
using Poco::Zip::Decompress;


void test()
{

	//some directory stuff
	Path tmpPath(Path::temp());
	tmpPath.pushDirectory("PocoFileSample");
	File tmpDir(tmpPath);
	tmpDir.createDirectories();
	//bool exists = tmpDir.exists();
	//bool isFile = tmpDir.isFile();
	//bool isDir = tmpDir.isDirectory();
	//bool canRead = tmpDir.canRead();
	bool canWrite = tmpDir.canWrite();


	//some file stuff
	File tmpFile(Path(tmpPath, string("PocoFileSample.dat")));
	if (tmpFile.createFile())
	{
		tmpFile.setSize(10000);
		File tmpFile2(Path(tmpPath, string("PocoFileSample2.dat")));
		tmpFile.copyTo(tmpFile2.path());
		Poco::Timestamp now;
		tmpFile.setLastModified(now);
		tmpFile.setReadOnly();
		canWrite = tmpFile.canWrite();
		tmpFile.setWriteable();
		canWrite = tmpFile.canWrite();
	}

	//show all files in dir
	{
		vector<string> files;
		tmpDir.list(files);
		vector<string>::iterator it = files.begin();
		for (; it != files.end(); ++it)
		{
			cout << *it << endl;
		}
		tmpDir.remove(true);
	}

	//directory iterator
	{
		string cwd(Path::current());
		DirectoryIterator it(cwd);
		DirectoryIterator end;
		while (it != end)
		{
			cout << it.name();
			if (it->isFile())
				cout << it->getSize();
			cout << endl;
			Path p(it.path());
			++it;
		}
	}
}


//==========================================================================================================================
string FileUtils::removeIllegalFilenameChars(string filename)
{//==========================================================================================================================

	string *s = &filename;
	string illegalChars = "\\/:?\"<>|*";
	for (auto it = s->begin(); it < s->end(); ++it) {
		bool found = illegalChars.find(*it) != string::npos;
		if (found) {
			*it = ' ';
		}
	}
	return filename;
}


//==========================================================================================================================
char* textFileRead(string filename)
{//==========================================================================================================================

	filename = Main::getPath() + filename;

	FILE* fp;
	char* content = nullptr;

	long count = 0;

	if (filename != "")
	{
		fp = fopen(filename.c_str(), "rt");

		if (fp != nullptr)
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0)
			{
				content = (char *)malloc(sizeof(char) * (count + 1));
				count = fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}


//==========================================================================================================================
void* HARDWARE_load_file(string filename)
{//==========================================================================================================================

	filename = Main::getPath() + filename;

	char* filepointer = NULL;
	FILE* file;
	long size;



	//FileUtils::fixPath(filename);

	file = fopen(filename.c_str(), "rb");

	if (file != NULL)
	{
		//get file size using stat
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		rewind(file);

		//fprintf(stdout,"loaded file: %s size: %d\n",fullname,size);

		filepointer = (char*)malloc(size * sizeof(char));

		if (filepointer == NULL)
		{
			ERROR_set_error(filename);
			ERROR_set_error(string(" malloc failed\n"));
		}

		//size_t bytesRead =
        fread(filepointer, 1, size, file);
	}
	if (file == NULL)
	{
		ERROR_set_error(filename);
		ERROR_set_error(string(" was not found\n"));
	}

	fclose(file);
	//HARDWARE_wait_for_vbl();


	return (void*)filepointer;
}

//==========================================================================================================================
void HARDWARE_unload_file(void** data_pointer)
{//==========================================================================================================================

	if (*data_pointer != NULL)
	{
		free(*data_pointer);

		*data_pointer = NULL;
	}
}

//==========================================================================================================================
long HARDWARE_get_file_size(string filename)//HARDWARE_FSFile[HARDWARE_FSGetFile(0,filename,"")].Length;
{//==========================================================================================================================

	filename = Main::getPath() + filename;

	//char* filepointer=NULL;
	FILE* file;
	long size = 0;


	file = fopen(filename.c_str(), "rb");
	if (file != NULL)
	{
		// get file size using stat
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		rewind(file);
	}
	if (file == NULL)
	{
		ERROR_set_error(filename);
		ERROR_set_error(string(" was not found\n"));
	}

	fclose(file);

	return size;
}


//FileUtils* FileUtils::fileUtils = nullptr;


string FileUtils::appDataPath = "";
//string "/" = "";
string FileUtils::bigDataURL = "";
string FileUtils::smallDataURL = "";


FileUtils::FileUtils()
{ //=========================================================================================================================


	//   if (System::debugMode == true) //DEBUG
	//   {
	//      bigDataURL = BobNet::debugBigDataURL;
	//      smallDataURL = BobNet::debugSmallDataURL;
	//   }
	//   else
	//   {
	//      bigDataURL = BobNet::releaseBigDataURL;
	//      smallDataURL = BobNet::releaseSmallDataURL;
	//   }
	//
	//   //cacheDir = "C:\\bobsGameCache\\";
	//


	//slash = "/";// prop->getProperty("file.separator"); //also File.separatorChar, File.separator
	//cacheDir = "";// prop->getProperty("user.home") + slash + string(".bobsGame") + slash;
	//fileUtils = this;
	appDataPath = string(SDL_GetPrefPath("Bob Corporation", "bob's game"));
}

BufferedImage* FileUtils::readBufferedImageFromFile(BobFile* file)
{
	return new BufferedImage();
}

ArrayList<string>* FileUtils::readLines(u8* get_resource_as_stream)
{
	return new ArrayList<string>;
}

void FileUtils::makeDir(const string& cs)
{
}


//
//
//u8* FileUtils::getResourceAsStream(const string& filename)
//{ //=========================================================================================================================
//
//	//
//	//   //don't use absolute paths starting from the folder we are in. /whatever.jpg
//	//   if (String::startsWith(filename, "/") == true && String::startsWith(filename, System::getProperty("user.home")) == false)
//	//   {
//	//      filename = filename.substr(1); //cut off the /
//	//      log.debug("Don't use absolute paths, fix this.");
//	//   }
//	//
//	//
//	//   //if we are using stuff from /res/ we should get them from the ClassLoader which gets them from inside the JAR (but removed from /res/ for some reason)
//	//   if (String::startsWith(filename, "res/") == true)
//	//   {
//	//      filename = filename.substr(4);
//	//      InputStream* is = utils->getClass().getClassLoader().getResourceAsStream(filename);
//	//
//	//      if (is == nullptr)
//	//      {
//	//         log.error(string("Could not find file in ClassLoader: ") + filename);
//	//      }
//	//
//	//      return is;
//	//   }
//	//   else //we are accessing from the hard disk. try the resource loader which will get it as a file.
//	//   {
//	//      FileInputStream* stream = nullptr;
//	//      try
//	//      {
//	//         File* file = new File(filename);
//	//
//	//         if (!file->exists())
//	//         {
//	//            file = new File(new File("."), filename);
//	//         }
//	//
//	//         if (!file->exists())
//	//         {
//	//            log.error(string("Could not find file: ") + filename);
//	//            return nullptr;
//	//         }
//	//         else
//	//         {
//	//            stream = new FileInputStream(file);
//	//         }
//	//      }
//	//      catch (IOException e)
//	//      {
//	//         log.error(string("Error opening file: ") + filename);
//	//         //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
//	//         delete stream;
//	//      }
//	//
//	//      if (stream == nullptr)
//	//      {
//	//      }
//	//
//	//
//	//      return stream;
//	//   }
//	return new u8;
//}

//
//string FileUtils::getResource(const string& filename)
//{ //=========================================================================================================================
//
//
//	//   //don't use absolute paths starting from the folder we are in. /whatever.jpg
//	//   if (String::startsWith(filename, "/") == true && String::startsWith(filename, System::getProperty("user.home")) == false)
//	//   {
//	//      filename = filename.substr(1); //cut off the /
//	//      log.debug("Don't use absolute paths, fix this.");
//	//   }
//	//
//	//
//	//   //if we are using stuff from /res/ we should get them from the ClassLoader which gets them from inside the JAR (but removed from /res/ for some reason)
//	//   if (String::startsWith(filename, "res/") == true)
//	//   {
//	//      filename = filename.substr(4);
//	//      URL* is = utils->getClass().getClassLoader().getResource(filename);
//	//
//	//      if (is == nullptr)
//	//      {
//	//         log.error(string("Could not find file in ClassLoader: ") + filename);
//	//      }
//	//
//	//      return is;
//	//   }
//	//   else //we are accessing from the hard disk. try the resource loader which will get it as a file.
//	//   {
//	//      try
//	//      {
//	//         File* file = new File(filename);
//	//         if (file->exists() == false)
//	//         {
//	//            file = new File(new File("."), filename);
//	//         }
//	//
//	//
//	//         if (file->exists() == false)
//	//         {
//	//            log.error(string("Could not find file: ") + filename);
//	//
//	//            //if(BobNet.debugMode)new Exception().printStackTrace();
//	//
//	//            return nullptr;
//	//         }
//	//         else
//	//         {
//	//            return file->toURI().toURL();
//	//         }
//	//      }
//	//      catch (IOException e)
//	//      {
//	//         log.error(string("Error opening file: ") + filename);
//	//         return nullptr;
//	//      }
//	//   }
//	return "";
//}


short* FileUtils::oldLoadShortIntFile(const string& filename)
{ //=========================================================================================================================
	//   File* file = new File(filename);
	//
	//
	//   int* intArray(((int)(file->length())) / 2);
	//
	//   BufferedInputStream* bin = new BufferedInputStream(FileUtils::getResourceAsStream(filename));
	//
	//   try
	//   {
	//      int sbyte1 = bin->read(); //signed byte 1
	//      int sbyte2 = bin->read();
	//      int i = 0;
	//
	//      while (sbyte1 != -1 || sbyte2 != -1)
	//      {
	//         int ubyte1 = sbyte1 & 0xFF;
	//         int ubyte2 = sbyte2 & 0xFF;
	//
	//         int result = (ubyte2 << 8) + ubyte1;
	//
	//         intArray->get(i) = result;
	//         i++;
	//         sbyte1 = bin->read();
	//         sbyte2 = bin->read();
	//      }
	//
	//      bin->close();
	//   }
	//   catch (IOException e)
	//   {
	//      e->printStackTrace();
	//   }
	//
	//   return intArray;
	return new short;
}


//=========================================================================================================================
short* FileUtils::loadShortIntFile(string filename)
{//=========================================================================================================================

	//		byte[] byteArray = loadByteFile(filename);
	//
	//		short[] shortArray = new short[byteArray.length/2];
	//
	//		for(int x=0;x<shortArray.length;x++)
	//		{
	//			short sbyte1=byteArray[x*2+0];//signed byte 1
	//			short sbyte2=byteArray[x*2+1];
	//
	//
	//			short ubyte1 = sbyte1 & 0xFF;
	//			short ubyte2 = sbyte2 & 0xFF;
	//
	//			short result = (ubyte2<<8) + ubyte1;
	//
	//			shortArray[x]=result;
	//		}

	//-------------------
	//alt
	//-------------------

	//return getIntArrayFromByteArray(loadByteFile(filename));

	return new short;
}
// ===============================================================================================
u8* FileUtils::getByteArrayFromIntArray(int* intArray)
{// ===============================================================================================
	return new u8[1];
}


//save 16 bit to binary
//load 16 bit


//load text file into read buffer?
//load text file into chars?
//load text file into one string
//load text file c way
//save strings to text file
//save string to text file
//save binary to text file


#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

// trim from start (copying)
static inline std::string ltrimmed(std::string s) {
	ltrim(s);
	return s;
}

// trim from end (copying)
static inline std::string rtrimmed(std::string s) {
	rtrim(s);
	return s;
}

// trim from both ends (copying)
static inline std::string trimmed(std::string s) {
	trim(s);
	return s;
}

//=========================================================================================================================
string FileUtils::loadTextFileFromExePathAndTrim(string filename)
{//=========================================================================================================================

	filename = Main::getPath() + filename;

	ifstream t(filename);
	string str;

	t.seekg(0, ios::end);
	str.reserve((size_t)t.tellg());
	t.seekg(0, ios::beg);

	str.assign((istreambuf_iterator<char>(t)),
		istreambuf_iterator<char>());

	rtrim(str);
	//str.erase(str.find_last_not_of(" \n\r\t") + 1);//right trim space tab return

	//log.debug("Loaded file: " + filename + " Size: " + to_string(str.length()));
	return str;
}

//=========================================================================================================================
ArrayList<string>* FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim(string filename)
{//=========================================================================================================================

	filename = Main::getPath() + filename;

	ArrayList<string>* lines = new ArrayList<string>();

	string line;
	stringstream dosString;
	ifstream inFile;
	inFile.open(filename);
	while (getline(inFile, line))
	{
		rtrim(line);
		//line.erase(line.find_last_not_of(" \n\r\t") + 1);
		lines->add(line);
	}
	return lines;
}


//=========================================================================================================================
u8* FileUtils::loadByteFileFromExePath(string filename)
{//=========================================================================================================================

	filename = Main::getPath() + filename;

//	char* cfilepointer = NULL;
//	FILE* cfile;
//	int csize;
//
//	cfile = fopen(fullname, "rb");
//	if (cfile != NULL)
//	{
//		//get file size using stat
//		fseek(cfile, 0, SEEK_END);
//		csize = ftell(cfile);
//		rewind(cfile);
//
//		//fprintf(stdout,"loaded file: %s size: %d\n",fullname,size);
//
//		cfilepointer = (char*)malloc(csize * sizeof(char));
//
//		if (cfilepointer == NULL)
//		{
//			//ERROR_set_error(fullname);
//			//log.error(string(fullname) + " malloc failed");
//		}
//
//		fread(cfilepointer, 1, csize, cfile);
//	}
//	if (cfile == NULL)
//	{
//		//ERROR_set_error(fullname);
//		log.error(string(fullname) + " could not be opened, probably not found");
//	}
//	fclose(cfile);
////	//HARDWARE_wait_for_vbl();
//





	char* cppfilepointer = NULL;
	streampos cppsize;

	ifstream cppfile(filename, ios::in | ios::binary | ios::ate);
	if (cppfile.is_open())
	{
		cppsize = cppfile.tellg();
		cppfilepointer = new char[(int)cppsize];
		cppfile.seekg(0, ios::beg);
		cppfile.read(cppfilepointer, cppsize);
		cppfile.close();

		//log.info("Loaded file: " + filename);
	}
	else
	{
		log.error("Could not open file: "+filename);
	}
	


	return (u8*)cppfilepointer;
}


constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7',
'8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

std::string byteArrayToHexString(u8 *data, unsigned long len)
{
	std::string s(len * 2, ' ');
	for (unsigned long i = 0; i < len; ++i) {
		s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
		s[2 * i + 1] = hexmap[data[i] & 0x0F];
	}
	return s;
}

u8* hexStringToByteArray(const string &hex)
{
	u8* bytes = new u8[hex.length()/2];

	for (unsigned int i = 0; i < hex.length(); i += 2) 
	{
		std::string byteString = hex.substr(i, 2);
		char byte = (char)strtol(byteString.c_str(), NULL, 16);
		bytes[i/2]=byte;
	}

	return bytes;
}


//#include <zip.h>

/*
base64.cpp and base64.h

Copyright (C) 2004-2008 René Nyffenegger

This source code is provided 'as-is', without any express or implied
warranty. In no event will the author be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
claim that you wrote the original source code. If you use this source code
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

René Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(u8 c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string encodeByteArrayToBase64String(u8 const* bytes_to_encode, unsigned long in_len)
{

	std::string ret;
	int i = 0;
	int j = 0;
	u8 char_array_3[3];
	u8 char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i <4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;

}
u8* decodeBase64StringToByteArray(std::string const& encoded_string, unsigned long &returnLength)
{
	long in_len = (long)encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	u8 char_array_4[4], char_array_3[3];
	std::vector<u8> ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = (u8)base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret.push_back(char_array_3[i]);
			i = 0;
		}
	}

	if (i) {
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = (u8)base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
	}

	u8* data = new u8[ret.size()];
	for(int x=0;x<ret.size();x++)
	{
		data[x] = ret.at(x);
	}
	
	returnLength = ret.size();
	return data;
}



#include "minilzo.h"
/* Work-memory needed for compression. Allocate memory in units
* of 'lzo_align_t' (instead of 'char') to make sure it is properly aligned.
*/

#define HEAP_ALLOC(var,size) \
    lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]

static HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);




#include "miniz.c"
typedef u8 uint8;
typedef unsigned short uint16;
typedef unsigned int uint;


bool zip = false;
bool lzo = true;

// ===============================================================================================
string FileUtils::zipByteArrayToBase64String(const u8* byteArray, unsigned long sourceLength)
{ // ===============================================================================================


	//   string outStr = "";
	//   try
	//   {
	//      ByteArrayOutputStream* out = new ByteArrayOutputStream();
	//
	//      GZIPOutputStream* gzip = new GZIPOutputStream(out);
	//      gzip->write(byteArray);
	//      gzip->close();
	//
	//      //JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
	//      outStr = out->toString("ISO-8859-1");
	//   }
	//   catch (exception& e)
	//   {
	//      e.printStackTrace();
	//   }
	//   return outStr;



//
//	
//	zip_source_t *src;
//	zip_t *za;
//	zip_error_t error;
//	void *data;
//	//size_t sourceLength;
//
//	zip_error_init(&error);
//	/* create source from buffer */
//	if ((src = zip_source_buffer_create(byteArray, sourceLength, 1, &error)) == NULL) {
//		fprintf(stderr, "can't create source: %s\n", zip_error_strerror(&error));
//		//free(byteArray);
//		zip_error_fini(&error);
//		return nullptr;
//	}
//
//	/* open zip archive from source */
//	if ((za = zip_open_from_source(src, ZIP_CREATE, &error)) == NULL) {
//		fprintf(stderr, "can't open zip from source: %s\n", zip_error_strerror(&error));
//		zip_source_free(src);
//		zip_error_fini(&error);
//		return nullptr;
//	}
//	zip_error_fini(&error);
//
//	/* we'll want to read the data back after zip_close */
//	zip_source_keep(src);
//
//
//	/* close archive */
//	if (zip_close(za) < 0) {
//		fprintf(stderr, "can't close zip archive: %s\n", zip_strerror(za));
//		return nullptr;
//	}
//
//	int zipsize = 0;
//
//	/* copy new archive to buffer */
//
//	if (zip_source_is_deleted(src)) {
//		/* new archive is empty, thus no data */
//		data = NULL;
//	}
//	else {
//		zip_stat_t zst;
//
//		if (zip_source_stat(src, &zst) < 0) {
//			fprintf(stderr, "can't stat source: %s\n", zip_error_strerror(zip_source_error(src)));
//			return nullptr;
//		}
//
//		zipsize = zst.sourceLength;
//
//		if (zip_source_open(src) < 0) {
//			fprintf(stderr, "can't open source: %s\n", zip_error_strerror(zip_source_error(src)));
//			return nullptr;
//		}
//		if ((data = malloc(zipsize)) == NULL) {
//			fprintf(stderr, "malloc failed: %s\n", strerror(errno));
//			zip_source_close(src);
//			return nullptr;
//		}
//		if ((zip_uint64_t)zip_source_read(src, data, zipsize) < zipsize) {
//			fprintf(stderr, "can't read data from source: %s\n", zip_error_strerror(zip_source_error(src)));
//			zip_source_close(src);
//			free(data);
//			return nullptr;
//		}
//		zip_source_close(src);
//	}
//
//	/* we're done with src */
//	zip_source_free(src);
//	delete[] byteArray;
//
	string zipDataHexString = "";

	if(zip)
	{
		//uint step = 0;
		int compressStatus;
		//uLong sourceLength = sourceLength;// (uLong)strlen(s_pStr);
		uLong compressedLength = compressBound(sourceLength);
		//uLong uncomp_len = sourceLength;
		u8 *compressedBytes;
		//uint total_succeeded = 0;


		//printf("miniz.c version: %s\n", MZ_VERSION);

		// Allocate buffers to hold compressed and uncompressed data.
		compressedBytes = (mz_uint8 *)malloc((size_t)compressedLength);
		if ((!compressedBytes))
		{
			log.error("Out of memory!");
			return "";
		}

		// Compress the string.
		compressStatus = compress(compressedBytes, &compressedLength, byteArray, sourceLength);
		if (compressStatus != Z_OK)
		{
			log.error("Compress failed");
			free(compressedBytes);
			
			return "";
		}

		//log.debug("Compressed from " + to_string(sourceLength) + " to " + to_string(compressedLength) + " bytes");

		zipDataHexString = encodeByteArrayToBase64String(compressedBytes, compressedLength);
		//log.debug("Encoded from " + to_string(compressedLength) + " to " + to_string(zipDataHexString.length()) + " bytes");

		free(compressedBytes);
	}


	if (lzo)
	{
		const unsigned long maximumCompressedLength = (sourceLength + sourceLength / 16 + 64 + 3);

		u8 * __LZO_MMODEL compressedBytes = new u8[maximumCompressedLength];


		int r;
		//lzo_uint in_len;
		lzo_uint compressedLength;
		//lzo_uint new_len;

		r = lzo1x_1_compress(byteArray, sourceLength, compressedBytes, &compressedLength, wrkmem);
		if (r == LZO_E_OK)
		{
			//log.debug("Compressed " + to_string(sourceLength) + " bytes into " + to_string(compressedLength) + " bytes");
		}
		else
		{
			/* this should NEVER happen */
			log.error("Compression failed:" + to_string(r));
			return  "";
		}
		/* check for an incompressible block */
		if (compressedLength >= sourceLength)
		{
			//log.debug("This block contains incompressible data.");
			//return "";
		}

		zipDataHexString = encodeByteArrayToBase64String(compressedBytes, compressedLength);
		//log.debug("Encoded from " + to_string(compressedLength) + " to " + to_string(zipDataHexString.length()) + " bytes");

		delete[] compressedBytes;
	}

	return zipDataHexString;
}


// ===============================================================================================
u8* FileUtils::unzipBase64StringToByteArray(const string &zippedBytesAsString, unsigned long &returnLength)
{// ===============================================================================================

	//   GZIPInputStream gis = null;
	//
	//   try
	//   {
	//      ByteArrayInputStream is = new ByteArrayInputStream(zippedBytesAsString.getBytes("ISO-8859-1"));
	//
	//      gis = new GZIPInputStream(is);
	//
	//      return IOUtils.toByteArray(new InputStreamReader(gis, "ISO-8859-1"), "ISO-8859-1");
	//   }
	//   catch (Exception e)
	//   {
	//      e.printStackTrace();
	//   }
	//   return null;



//
//	//unzip the byte array to a new byte array
//	zip_source_t *src;
//	zip_t *za;
//	zip_error_t error;
//	void *data;
//	//size_t size;
//
//	zip_error_init(&error);
//	/* create source from buffer */
//	if ((src = zip_source_buffer_create(byteArray, size, 1, &error)) == NULL) {
//		fprintf(stderr, "can't create source: %s\n", zip_error_strerror(&error));
//		//free(byteArray);
//		zip_error_fini(&error);
//		return nullptr;
//	}
//
//	/* open zip archive from source */
//	if ((za = zip_open_from_source(src, 0, &error)) == NULL) {
//		fprintf(stderr, "can't open zip from source: %s\n", zip_error_strerror(&error));
//		zip_source_free(src);
//		zip_error_fini(&error);
//		return nullptr;
//	}
//	zip_error_fini(&error);
//
//	/* we'll want to read the data back after zip_close */
//	zip_source_keep(src);
//
//
//	/* close archive */
//	if (zip_close(za) < 0) {
//		fprintf(stderr, "can't close zip archive: %s\n", zip_strerror(za));
//		return nullptr;
//	}
//
//	int zipsize = 0;
//
//	/* copy new archive to buffer */
//
//	if (zip_source_is_deleted(src)) {
//		/* new archive is empty, thus no data */
//		data = NULL;
//	}
//	else {
//		zip_stat_t zst;
//
//		if (zip_source_stat(src, &zst) < 0) {
//			fprintf(stderr, "can't stat source: %s\n", zip_error_strerror(zip_source_error(src)));
//			return nullptr;
//		}
//
//		zipsize = zst.size;
//
//		if (zip_source_open(src) < 0) {
//			fprintf(stderr, "can't open source: %s\n", zip_error_strerror(zip_source_error(src)));
//			return nullptr;
//		}
//		if ((data = malloc(zipsize)) == NULL) {
//			fprintf(stderr, "malloc failed: %s\n", strerror(errno));
//			zip_source_close(src);
//			return nullptr;
//		}
//		if ((zip_uint64_t)zip_source_read(src, data, zipsize) < zipsize) {
//			fprintf(stderr, "can't read data from source: %s\n", zip_error_strerror(zip_source_error(src)));
//			zip_source_close(src);
//			free(data);
//			return nullptr;
//		}
//		zip_source_close(src);
//	}
//
//	/* we're done with src */
//	zip_source_free(src);
	


	unsigned long zippedLength;
	u8* zippedBytes = (u8*)decodeBase64StringToByteArray(zippedBytesAsString, zippedLength);
	//log.debug("Decoded " + to_string(zippedBytesAsString.length()) + " bytes into " + to_string(zippedLength) + " bytes");

	if(zip)
	{

		//uint step = 0;
		int compressStatus;
		//uLong src_len = sourceLength;// (uLong)strlen(s_pStr);
		uLong uncompressedLength = zippedLength * 40;
		//uint total_succeeded = 0;


		u8 *uncompressedBytes;
		uncompressedBytes = (mz_uint8 *)malloc((size_t)uncompressedLength);
		if ((!uncompressedBytes))
		{
			log.error("Could not allocate memory for decompression");
			return nullptr;
		}

		compressStatus = uncompress(uncompressedBytes, &uncompressedLength, zippedBytes, zippedLength);
		//total_succeeded += (compressStatus == Z_OK);

		while(compressStatus == Z_BUF_ERROR)
		{
			free(uncompressedBytes);
			uncompressedLength *= 2;
			uncompressedBytes = (mz_uint8 *)malloc((size_t)uncompressedLength);
			compressStatus = uncompress(uncompressedBytes, &uncompressedLength, zippedBytes, zippedLength);
		}

		if (compressStatus != Z_OK)
		{
			log.error("Uncompress failed.");
			free(uncompressedBytes);
			return nullptr;
		}

		delete[] zippedBytes;

		//log.debug("Decompressed " + to_string(zippedLength) + " bytes into " + to_string(uncompressedLength) + " bytes");
		//printf("Decompressed from %u to %u bytes\n", (mz_uint32)size, (mz_uint32)uncomp_len);

//		// Ensure uncompress() returned the expected data.
//		if (uncomp_len != src_len)
//		{
//			printf("Decompression failed!\n");
//			free(pUncomp);
//			return nullptr;
//		}
	
		returnLength = uncompressedLength;
		return uncompressedBytes;

	}


	if(lzo)
	{
		int compressStatus;
		//lzo_uint in_len;
		lzo_uint uncompressedLength = zippedLength * 100;
		//lzo_uint new_len;

		u8 * __LZO_MMODEL uncompressedBytes = new u8[uncompressedLength];

		//new_len = in_len;
		compressStatus = lzo1x_decompress(zippedBytes, zippedLength, uncompressedBytes, &uncompressedLength, NULL);

		while (compressStatus == LZO_E_INPUT_OVERRUN)
		{
			delete[] uncompressedBytes;
			log.error("Decompression failed, increasing buffer.");
			uncompressedLength *= 2;
			uncompressedBytes = new u8[uncompressedLength];
			compressStatus = lzo1x_decompress(zippedBytes, zippedLength, uncompressedBytes, &uncompressedLength, NULL);
		}

		if (compressStatus == LZO_E_OK)
		{
			//log.debug("Decompressed " + to_string(zippedLength) + " bytes into " + to_string(out_len) + " bytes");
		}
		else
		{
			/* this should NEVER happen */
			log.error("Decompression failed:" + to_string(compressStatus));
			return nullptr;
		}

		delete[] zippedBytes;

		returnLength = uncompressedLength;
		return (u8*)uncompressedBytes;
	}

	return nullptr;
}


string FileUtils::zipStringToBase64String(const string& s)
{ // ===============================================================================================

	if (s == "" || s.length() == 0)
	{
	    return s;
	}

	u8 *val = new u8[s.length() + 1];
	strcpy((char *)val, s.c_str());

	return zipByteArrayToBase64String(val, s.length());
}

string FileUtils::unzipBase64StringToString(const string& s)
{ // ===============================================================================================

	if (s == "" || s.length() == 0)
	{
	    return s;
	}

	unsigned long returnLength = 0;
	u8* bytes = unzipBase64StringToByteArray(s, returnLength);
	string out((char*)bytes,returnLength);


	return out;
}


#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
using Poco::MD5Engine;



string FileUtils::getFileMD5Checksum(const string& filename)
{ //===============================================================================================


	u8* bytes = loadByteFileFromExePath(filename);
	string md5 = getByteArrayMD5Checksum(bytes);
	delete[] bytes;
	return md5;


}


string FileUtils::getByteArrayMD5Checksum(u8* bytes)
{ //===============================================================================================


	std::stringstream stringStream((char*)bytes);
	return getStringMD5(stringStream.str());


}

string FileUtils::getStringMD5(const string& stringToMD5)
{ //===============================================================================================


	Poco::MD5Engine md5;
	Poco::DigestOutputStream outstr(md5);
	outstr << stringToMD5;
	outstr.flush(); //to pass everything to the digest engine
	const Poco::DigestEngine::Digest& digest = md5.digest();
	std::string md5string = Poco::DigestEngine::digestToHex(digest);
	return md5string;
}

void FileUtils::saveImage(const string& s, BufferedImage* bufferedImage)
{ //===============================================================================================

	//		Iterator<ImageWriter> imageWritersIterator = ImageIO.getImageWritersByFormatName("png");
	//		ImageWriter imageWriter = (ImageWriter) imageWritersIterator.next();
	//
	//		FileOutputStream fileOutputStream = null;
	//		File file = null;
	//		MemoryCacheImageOutputStream memoryCacheImageOutputStream = null;
	//
	//		try
	//		{
	//			file = new File(s);
	//			fileOutputStream = new FileOutputStream(file);
	//			memoryCacheImageOutputStream = new MemoryCacheImageOutputStream(fileOutputStream);
	//		}
	//		catch(FileNotFoundException e){log.error("Could not create PNG file. Error: "+e.getMessage());e.printStackTrace();return;}
	//
	//		imageWriter.setOutput(memoryCacheImageOutputStream);
	//		ImageWriteParam iwp = imageWriter.getDefaultWriteParam();
	//		try
	//		{
	//			imageWriter.write(null, new IIOImage(bufferedImage, null, null), iwp);//param);
	//		}
	//		catch(IOException e){log.error("An error occured during writing PNG file. Error: "+e.getMessage());e.printStackTrace();return;}
	//
	//		imageWriter.dispose();
	//
	//		try
	//		{
	//			memoryCacheImageOutputStream.close();
	//			fileOutputStream.close();
	//		}
	//		catch(IOException e){e.printStackTrace();}

	//-------------------
	//alt
	//-------------------

	//   try
	//   {
	//      ImageIO::write(bufferedImage, "PNG", new File(s));
	//   }
	//   catch (IOException e)
	//   {
	//      e->printStackTrace();
	//   }
}






void FileUtils::writeSessionTokenToCache(long long userID, const string& sessionToken, bool statsAllowed)
{ //===============================================================================================

//	File* sessionFile = new File(cacheDir + string("session.txt"));
//	
//	if (sessionFile->exists() == false)
//	{
//	    sessionFile->createFile();
//	}
//	
//	try
//	{
//		sessionFile->write(string("") + to_string(userID) + string(",`") + sessionToken + string("`,") + StringConverterHelper::toString(statsAllowed));
//		sessionFile->closeFile();
//	}
//	catch (exception)
//	{
//	    
//	}

	ofstream outputFile;
	outputFile.open(appDataPath + "session.txt", ofstream::out);//leave this without runpath, will always be run in windows debug in the proper cwd /bobsgame/
	outputFile << string("") + to_string(userID) + string(",`") + sessionToken + string("`,") + StringConverterHelper::toString(statsAllowed);
	outputFile.close();
}

string FileUtils::readSessionTokenFromCache()
{ //===============================================================================================

//	File* sessionFile = new File(cacheDir + string("session.txt"));
//	
//	if (sessionFile->exists() == false)
//	{
//	    return "";
//	}
//	
//	string line = "";
//	
//	try
//	{
//	    BufferedReader* input = new BufferedReader(new FileReader(sessionFile));
//	    line = input->readLine();
//	    input->close();
//	}
//	catch (IOException e)
//	{
//	    e->printStackTrace();
//	}
//	
//	if (line != "")
//	{
//	    //log.debug(line);
//	
//	    if (line.length() > 0)
//	    {
//	        return line;
//	    }
//	}

	File f(appDataPath + string("session.txt"));
	if (f.exists())
	{
		ifstream t(appDataPath + string("session.txt"));
		string str;

		t.seekg(0, ios::end);
		str.reserve((size_t)t.tellg());
		t.seekg(0, ios::beg);

		str.assign((istreambuf_iterator<char>(t)),
			istreambuf_iterator<char>());

		rtrim(str);

		return str;
	}
	return "";
}

void FileUtils::deleteSessionTokenFromCache()
{ //===============================================================================================

	File* sessionFile = new File(appDataPath + string("session.txt"));
	if(sessionFile->exists())sessionFile->remove();


}


void FileUtils::setStatusText(const string& text)
{ //===============================================================================================


	   if (statusConsoleText == nullptr)
	   {
	      statusConsoleText = Console::add("", GLUtils::getViewportWidth() / 2 - 50, GLUtils::getViewportHeight() / 2 - 10);
	   }
	
	   statusConsoleText->x = (int)(GLUtils::getViewportWidth() / 2 - ((statusConsoleText->getWidth() + 3) / 2));
	   statusConsoleText->y = (int)(GLUtils::getViewportHeight() / 2 - 10);
	
	   statusConsoleText->text = text;
	
	   glClear(GL_COLOR_BUFFER_BIT);
	
	   Main::mainObject->console->render();
	   Main::mainObject->whilefix();
}

void FileUtils::deleteStatusText()
{ //===============================================================================================

	   if (statusConsoleText != nullptr)
	   {
	      statusConsoleText->text = "";
	      statusConsoleText->x = GLUtils::getViewportWidth();
	      statusConsoleText->y = GLUtils::getViewportHeight();
	
	      statusConsoleText->ticks = 1; //will be deleted from the console after 1 tick
	
	      //Java to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
	      delete statusConsoleText;
	
	      glClear(GL_COLOR_BUFFER_BIT);
		  Main::mainObject->console->render();
		  Main::mainObject->whilefix();
	   }
}

//
//FileUtils::ProgressListener::ProgressListener(FileUtils* outerInstance) : outerInstance(outerInstance)
//{
//}
//
//void FileUtils::ProgressListener::actionPerformed(ActionEvent* e)
//{
//   // e.getSource() gives you the object of DownloadCountingOutputStream because you set it in the overriden method, afterWrite().
//   outerInstance->setStatusText(string("Downloading ") + outerInstance->downloadingDataNiceName + string(": ") + (static_cast<DownloadCountingOutputStream*>(e->getSource()))->getByteCount() / 1024 + string(" kB / ") + outerInstance->downloadingFileSize / 1024 + string(" kB"));
//}
//
//FileUtils::DownloadCountingOutputStream::DownloadCountingOutputStream(FileUtils* outerInstance, OutputStream* out) : org::apache::commons::io::output::CountingOutputStream(out), outerInstance(outerInstance)
//{
//}
//
//void FileUtils::DownloadCountingOutputStream::setListener(ActionListener* listener)
//{
//   this->listener = listener;
//}
//
//void FileUtils::DownloadCountingOutputStream::afterWrite(int n) throw(IOException)
//{
////   CountingOutputStream::afterWrite(n);
////   if (listener != nullptr)
////   {
////      listener->actionPerformed(new ActionEvent(this, 0, nullptr));
////   }
//}

void FileUtils::downloadFileToCacheWithProgressListener(const string& fileName, const string& niceName)
{ //===============================================================================================
	//
	//   downloadingDataNiceName = niceName;
	//
	//   File* outputFile = new File(cacheDir + getFileName);
	//   //download sprites.zip and maps.zip from http://localhost/z/ and save to directory
	//
	//   URL* fileURL = nullptr;
	//
	//   try
	//   {
	//      fileURL = new URL(bigDataURL + getFileName);
	//   }
	//   catch (MalformedURLException e1)
	//   {
	//      e1->printStackTrace();
	//   }
	//
	//   //		try
	//   //		{
	//   //			org.apache.commons.io.FileUtils::copyURLToFile(fileURL, file, 60000, 60000);
	//   //		}
	//   //		catch (IOException e1)
	//   //		{
	//   //			e1.printStackTrace();
	//   //		}
	//
	//
	//   OutputStream* os = nullptr;
	//   InputStream* is = nullptr;
	//   ProgressListener* progressListener = new ProgressListener(this);
	//
	//
	//   try
	//   {
	//      os = new FileOutputStream(outputFile);
	//      is = fileURL->openStream();
	//
	//      DownloadCountingOutputStream* dcount = new DownloadCountingOutputStream(this, os);
	//
	//      dcount->setListener(progressListener);
	//
	//      // this line give you the total length of source stream as a String.
	//      // you may want to convert to integer and store this value to
	//      // calculate percentage of the progression.
	//
	//      //setStatusText("Connecting to asset server...");
	//
	//
	//      string fileSizeString = fileURL->openConnection().getHeaderField("Content-Length");
	//
	//      if (fileSizeString != "")
	//      {
	//         downloadingFileSize = -1;
	//         try
	//         {
	//            downloadingFileSize = StringConverterHelper::fromString<long long>(fileSizeString);
	//         }
	//         catch (NumberFormatException ex)
	//         {
	//            ex->printStackTrace();
	//            return;
	//         }
	//      }
	//
	//      // begin transfer by writing to dcount, not os.
	//      IOUtils::copy(is, dcount);
	//   }
	//   catch (exception& e)
	//   {
	//      log.error(string("Error downloading file to cache! File: ") + getFileName + string(" Error: ") + e.what());
	//      e.printStackTrace();
	//   }
	//   //JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
	//   finally
	//      {
	//
	//         try
	//         {
	//            if (os != nullptr)
	//            {
	//               os->close();
	//            }
	//            if (is != nullptr)
	//            {
	//               is->close();
	//            }
	//         }
	//         catch (IOException e)
	//         {
	//            e->printStackTrace();
	//         }
	//
	//      }
	//
	//   //deleteStatusText();
}

void FileUtils::decompressZipInCache(const string& fileName, const string& niceName)
{ //===============================================================================================
	//
	//   setStatusText(string("Decompressing ") + niceName + string("..."));
	//
	//   try
	//   {
	//      File* inputFile = new File(cacheDir + getFileName);
	//
	//      ZipInputStream* zipInputStream = new ZipInputStream(new FileInputStream(inputFile));
	//      BufferedInputStream* bufferedInputStream = new BufferedInputStream(zipInputStream);
	//
	//      ZipEntry* zipEntry = zipInputStream->getNextEntry();
	//
	//      while (zipEntry != nullptr)
	//      {
	//         BufferedOutputStream* bufferedOutputStream = new BufferedOutputStream(new FileOutputStream(new File(cacheDir + zipEntry->getName())));
	//
	//         //int zipSize = (int)zipEntry.getCompressedSize();
	//
	//         int bytesRead = 0;
	//
	//         u8* b(1024);
	//
	//         while ((bytesRead = bufferedInputStream->read(b)) != -1)
	//         {
	//            bufferedOutputStream->write(b, 0, bytesRead);
	//         }
	//         bufferedOutputStream->close();
	//
	//
	//         zipEntry = zipInputStream->getNextEntry();
	//      }
	//
	//      bufferedInputStream->close();
	//      zipInputStream->close();
	//   }
	//   catch (IOException e)
	//   {
	//      e->printStackTrace();
	//      return;
	//   }
	//
	//   deleteStatusText();
}

void FileUtils::deleteFileFromCache(const string& fileName)
{ //===============================================================================================

	//   File* file = new File(cacheDir + getFileName);
	//
	//   if (file->exists() == true)
	//   {
	//      file->
	//      delete(
	//      )
	//      ;
	//   }
}

bool FileUtils::checkIfFileExistsInCache(const string& fileName)
{ //===============================================================================================

	//   File* file = new File(cacheDir + getFileName);
	//
	//   return file->exists();

	return true;
}

long long FileUtils::getFileSizeInCache(const string& fileName)
{ //===============================================================================================


	//   if (checkIfFileExistsInCache(getFileName) == true)
	//   {
	//      return FileUtils::sizeOf(new File(cacheDir + getFileName));
	//   }
	//   else
	//   {
	return -1;
	//   }
}

long long FileUtils::getFileSizeOnServer(const string& fileName)
{ //===============================================================================================

	//   URL* fileURL = nullptr;
	//
	//   try
	//   {
	//      fileURL = new URL(bigDataURL + getFileName);
	//   }
	//   catch (MalformedURLException e1)
	//   {
	//      e1->printStackTrace();
	//   }
	//
	//
	//   string fileSizeString = "";
	//
	//
	//   //setStatusText("Connecting to asset server...");
	//
	//
	//   try
	//   {
	//      fileSizeString = fileURL->openConnection().getHeaderField("Content-Length");
	//   }
	//   catch (exception& ex)
	//   {
	//      //setStatusText("Timed out, retrying...");
	//   }
	//
	//
	//   if (fileSizeString != "")
	//   {
	//      long long size = -1;
	//      try
	//      {
	//         size = StringConverterHelper::fromString<long long>(fileSizeString);
	//      }
	//      catch (NumberFormatException ex)
	//      {
	//         ex->printStackTrace();
	//         return -1;
	//      }
	//      return size;
	//   }
	//
	//   //deleteStatusText();

	return -1;
}

void FileUtils::downloadAndDecompressZIPFileIfDifferentFromServer(const string& fileName, const string& niceName)
{ //===============================================================================================


	//   long long serverSize = getFileSizeOnServer(getFileName);
	//   long long localSize = getFileSizeInCache(getFileName);
	//
	//   log.debug(string("") + getFileName + string(" size on server: ") + to_string(serverSize));
	//   log.debug(string("") + getFileName + string(" size in cache: ") + to_string(localSize));
	//
	//   if (localSize != serverSize && serverSize > 16)
	//   {
	//      deleteFileFromCache(getFileName);
	//      downloadFileToCacheWithProgressListener(getFileName, niceName);
	//      decompressZipInCache(getFileName, niceName);
	//      deleteStatusText();
	//   }
}

void FileUtils::downloadFileIfDifferentFromServer(const string& fileName, const string& niceName)
{ //===============================================================================================


	//   long long serverSize = getFileSizeOnServer(getFileName);
	//   long long localSize = getFileSizeInCache(getFileName);
	//
	//   log.debug(string("") + getFileName + string(" size on server: ") + to_string(serverSize));
	//   log.debug(string("") + getFileName + string(" size in cache: ") + to_string(localSize));
	//
	//   if (localSize != serverSize && serverSize > 16)
	//   {
	//      deleteFileFromCache(getFileName);
	//      downloadFileToCacheWithProgressListener(getFileName, niceName);
	//      //decompressZipInCache(getFileName,niceName);
	//      deleteStatusText();
	//   }
}

void FileUtils::initCache()
{ //===============================================================================================

	//   log.info("Init FileUtils...");
	//
	//   FileUtils::makeDir(cacheDir);
	//   FileUtils::makeDir(cacheDir + string("l") + slash);
	//
	//   //File initFile = new File(cacheDir+"init");
	//   //if(initFile.exists()==false)
	//   //{
	//   // check filesize of sprites.zip locally
	//   // check filesize of sprites.zip on server
	//   //if different, delete sprites.zip locally, download sprites.zip, decompress.
	//
	//
	//   downloadAndDecompressZIPFileIfDifferentFromServer("sprites.zip", "Sprite Graphics");
	//   downloadAndDecompressZIPFileIfDifferentFromServer("maps.zip", "Background Graphics");
	//   downloadAndDecompressZIPFileIfDifferentFromServer("sounds.zip", "Sound Effects");
	//   downloadAndDecompressZIPFileIfDifferentFromServer("music.zip", "Initial Music Data");
	//   downloadFileIfDifferentFromServer("gameData", "Initial Game Data");
	//
	//   deleteStatusText();
	//   //FileUtils::listFiles(new File(cacheDir),null,true);
	//
	//
	//   //delete("sprites.zip");
	//   //delete("maps.zip");
	//
	//   //			try
	//   //			{
	//   //				initFile.createNewFile();
	//   //			}
	//   //			catch (IOException e1)
	//   //			{
	//   //				e1.printStackTrace();
	//   //			}
	//   //}
	//
	//   log.info("FileUtils Complete.");
}

void FileUtils::downloadBigFileToCacheIfNotExist(const string& fileName)
{ //===============================================================================================

	//
	//   if (FileUtils::getResource(string("") + FileUtils::cacheDir + getFileName) == nullptr)
	//   {
	//      File* outputFile = new File(cacheDir + getFileName);
	//
	//      URL* fileURL = nullptr;
	//
	//      try
	//      {
	//         fileURL = new URL(bigDataURL + getFileName);
	//      }
	//      catch (MalformedURLException e1)
	//      {
	//         e1->printStackTrace();
	//      }
	//
	//
	//      OutputStream* os = nullptr;
	//      InputStream* is = nullptr;
	//
	//      try
	//      {
	//         os = new FileOutputStream(outputFile);
	//         is = fileURL->openStream();
	//
	//         // this line give you the total length of source stream as a String.
	//         // you may want to convert to integer and store this value to
	//         // calculate percentage of the progression.
	//         string fileSizeString = fileURL->openConnection().getHeaderField("Content-Length");
	//
	//
	//         // begin transfer by writing to dcount, not os.
	//         IOUtils::copy(is, os);
	//      }
	//      catch (exception& e)
	//      {
	//         log.error(string("Error downloading file to cache! File: ") + getFileName + string(" Error: ") + e.what());
	//         e.printStackTrace();
	//      }
	//      //JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to the exception 'finally' clause:
	//      finally
	//         {
	//
	//            try
	//            {
	//               if (os != nullptr)
	//               {
	//                  os->close();
	//               }
	//               if (is != nullptr)
	//               {
	//                  is->close();
	//               }
	//            }
	//            catch (IOException e)
	//            {
	//               e->printStackTrace();
	//            }
	//
	//         }
	//   }
}

void FileUtils::downloadSmallFileToCacheIfNotExist(const string& fileName)
{ //===============================================================================================


	//   if (FileUtils::getResource(string("") + FileUtils::cacheDir + getFileName) == nullptr)
	//   {
	//      URL* fileURL = nullptr;
	//
	//      try
	//      {
	//         fileURL = new URL(smallDataURL + getFileName);
	//      }
	//      catch (MalformedURLException e1)
	//      {
	//         e1->printStackTrace();
	//      }
	//
	//      try
	//      {
	//         FileUtils::copyURLToFile(fileURL, new File(string("") + FileUtils::cacheDir + getFileName), 60000, 60000);
	//      }
	//      catch (IOException e1)
	//      {
	//         e1->printStackTrace();
	//      }
	//   }
}

u8* FileUtils::loadByteFileFromCacheOrDownloadIfNotExist(const string& fileName)
{ //===============================================================================================

	//   downloadSmallFileToCacheIfNotExist(getFileName);
	//
	//   return FileUtils::loadByteFile(string("") + FileUtils::cacheDir + getFileName);

	u8* a = new u8;
	return a;
}

int* FileUtils::loadIntFileFromCacheOrDownloadIfNotExist(const string& fileName)
{ //===============================================================================================

	//
	//   downloadSmallFileToCacheIfNotExist(getFileName);
	//
	//   return FileUtils::loadShortIntFile(string("") + FileUtils::cacheDir + getFileName);

	int* a = new int;
	return a;
}

void FileUtils::saveByteArrayToCache(u8* byteArray, const string& md5FileName)
{ //===============================================================================================
	//
	//   File* outputFile = new File(cacheDir + md5FileName);
	//
	//   try
	//   {
	//      FileUtils::writeByteArrayToFile(outputFile, byteArray);
	//   }
	//   catch (IOException e)
	//   {
	//      e->printStackTrace();
	//   }
}

bool FileUtils::doesDidIntroFileExist()
{ //===============================================================================================
	//   File* introCheckFile = new File(FileUtils::cacheDir + string(".didIntro"));
	//   if (introCheckFile->exists())
	//   {
	//      return true;
	//   }
	return false;
}

void FileUtils::writeDidIntroFile()
{ //===============================================================================================
	//   File* introCheckFile = new File(FileUtils::cacheDir + string(".didIntro"));
	//   try
	//   {
	//      introCheckFile->createNewFile();
	//   }
	//   catch (IOException e)
	//   {
	//      e->printStackTrace();
	//   }
}

BobFile::BobFile()
{
}

BobFile::BobFile(const string& s)
{
}

bool BobFile::exists()
{
	return false;
}

int BobFile::length()
{
	return 0;
}

string BobFile::getAbsolutePath()
{
	return "";
}

BobFile* BobFile::createNewFile()
{
	return new BobFile();
}

string BobFile::getName()
{
	return "";
}

void BobFile::deleteFile()
{
}


RandomAccessFile::RandomAccessFile()
{
}

RandomAccessFile::RandomAccessFile(const string& s, const string& mode)
{
}

bool RandomAccessFile::exists()
{
	return false;
}

int RandomAccessFile::length()
{
	return 0;
}

string RandomAccessFile::getAbsolutePath()
{
	return "";
}

RandomAccessFile* RandomAccessFile::createNewFile()
{
	return new RandomAccessFile();
}

string RandomAccessFile::getName()
{
	return "";
}

void RandomAccessFile::deleteFile()
{
}

int RandomAccessFile::readInt()
{
	return 0;
}

void RandomAccessFile::seek(long long i)
{
}

void RandomAccessFile::close()
{
}

