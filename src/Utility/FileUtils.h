//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include "BufferedImage.h"
class Logger;



char* textFileRead(string filename);
void* HARDWARE_load_file(string filename);
void HARDWARE_unload_file(void** data_pointer);
long HARDWARE_get_file_size(string filename);


class ConsoleText;

class BobFile
{
public:

	BobFile();
	BobFile(const string& s);
	bool exists();
	int length();
	string getAbsolutePath();
	BobFile* createNewFile();
	string getName();
	void deleteFile();
};

class RandomAccessFile
{
public:

	RandomAccessFile();
	RandomAccessFile(const string& s, const string& mode);
	bool exists();
	int length();
	string getAbsolutePath();
	RandomAccessFile* createNewFile();
	string getName();
	void deleteFile();
	int readInt();
	void seek(long long i);
	void close();
};

class FileUtils
{
public:

	//static FileUtils* fileUtils;

	FileUtils();

	static string removeIllegalFilenameChars(string s);
	//static void fixPath(string &fullname);
	static BufferedImage* readBufferedImageFromFile(BobFile* file);
	static ArrayList<string>* readLines(u8* get_resource_as_stream);
	static void makeDir(const string& cs);
	//static unsigned char* decodeBase64StringToByteArray(const string& cs);
	//static string encodeByteArrayToBase64String(unsigned char const* bytes_to_encode, unsigned int in_len);

	//static u8* getResourceAsStream(const string& filename);//was InputStream
	//static string getResource(const string& filename);//was URL
	static short* oldLoadShortIntFile(const string& filename);
	static short* loadShortIntFile(string filename);
	static string loadTextFileFromExePathAndTrim(string filename);
	static ArrayList<string>* loadTextFileFromExePathIntoVectorOfStringsAndTrim(string filename);
	static u8* loadByteFileFromExePath(string filename);
	static string zipByteArrayToBase64String(const u8* byteArray, unsigned long size);
	static u8* unzipBase64StringToByteArray(const string &zippedBytesAsString, unsigned long &returnLength);
	static string zipStringToBase64String(const string& s);
	static string unzipBase64StringToString(const string& s);
	static string getFileMD5Checksum(const string& filename);
	static u8* getByteArrayFromIntArray(int* intArray);
	static string getByteArrayMD5Checksum(u8* bytes);
	static string getStringMD5(const string& stringToMD5);
	static void saveImage(const string& s, BufferedImage* bufferedImage);


	static string appDataPath;
	//static string slash;

	static string bigDataURL; //for zip files
	static string smallDataURL; //for individual patch files (basically the newest zip file unzipped into dir)

	static Logger log;

	static void writeSessionTokenToCache(long long userID, const string& sessionToken, bool statsAllowed);
	static string readSessionTokenFromCache();
	static void deleteSessionTokenFromCache();
	//virtual void writeCookie(const string& s);
	//virtual ArrayList<string>* readCookies();
	//static void writeBrowserSessionCookieAndRefreshIFrame();
	//static void deleteBrowserSessionCookieAndRefreshIFrame();
	//static void writeBrowserSessionAndRefreshIFrame();

	string downloadingDataNiceName = "";
	ConsoleText* statusConsoleText = nullptr;
	long long downloadingFileSize = 0;

	virtual void setStatusText(const string& text);
	virtual void deleteStatusText();


	//private:
	//   class ProgressListener : public ActionListener
	//   {
	//   private:
	//      FileUtils* outerInstance;
	//
	//   public:
	//      ProgressListener(FileUtils* outerInstance);
	//
	//      virtual void actionPerformed(ActionEvent* e) override;
	//   };
	//
	//
	//public:
	//   class DownloadCountingOutputStream : public CountingOutputStream
	//   {
	//   private:
	//      FileUtils* outerInstance;
	//
	//      ActionListener* listener = nullptr;
	//   public:
	//      DownloadCountingOutputStream(FileUtils* outerInstance, OutputStream* out);
	//      virtual void setListener(ActionListener* listener);
	//
	//   protected:
	//      virtual void afterWrite(int n) throw(IOException) override;
	//   };


public:
	virtual void downloadFileToCacheWithProgressListener(const string& fileName, const string& niceName);
	virtual void decompressZipInCache(const string& fileName, const string& niceName);
	virtual void deleteFileFromCache(const string& fileName);
	static bool checkIfFileExistsInCache(const string& fileName);
	virtual long long getFileSizeInCache(const string& fileName);
	virtual long long getFileSizeOnServer(const string& fileName);
	virtual void downloadAndDecompressZIPFileIfDifferentFromServer(const string& fileName, const string& niceName);
	virtual void downloadFileIfDifferentFromServer(const string& fileName, const string& niceName);
	virtual void initCache();
	static void downloadBigFileToCacheIfNotExist(const string& fileName);
	static void downloadSmallFileToCacheIfNotExist(const string& fileName);
	static u8* loadByteFileFromCacheOrDownloadIfNotExist(const string& fileName);
	static int* loadIntFileFromCacheOrDownloadIfNotExist(const string& fileName);
	static void saveByteArrayToCache(u8* byteArray, const string& md5FileName);
	static bool doesDidIntroFileExist();
	static void writeDidIntroFile();
};

