//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class AssetData
{
protected:
	string name;
	int id = -1;


public:
	AssetData();


	AssetData(int id, const string& name);

	//
	//	
	//	public String toJSON()
	//	{
	//
	//		Gson gson = new Gson();
	//		String json = gson.toJson(this);
	//
	////		ObjectMapper mapper = new ObjectMapper();
	////		String json = "";
	////
	////		try
	////		{
	////			json = mapper.writeValueAsString(this);
	////		}
	////		catch(JsonGenerationException e)
	////		{
	////			e.printStackTrace();
	////		}
	////		catch(JsonMappingException e)
	////		{
	////			e.printStackTrace();
	////		}
	////		catch(IOException e)
	////		{
	////			e.printStackTrace();
	////		}
	//
	//
	//		return json;
	//
	//	}
	//
	//
	//
	//
	//	
	//	public String toBase64ZippedJSON()
	//	{
	//
	//
	//		String json = toJSON();
	//		//System.out.println("json------------------------------");
	//		//System.out.println("length:"+json.length());
	//		//System.out.println(json);
	//
	//		String zip = "";
	//
	//		zip = FileUtils::zipStringToBase64String(json);
	//
	//
	//		//System.out.println("zip------------------------------");
	//		//System.out.println("length:"+zip.length());
	//		//System.out.println(zip);
	//
	//
	//		String b64 = FileUtils::encodeStringToBase64(zip);
	//
	//		//System.out.println("b64------------------------------");
	//		//System.out.println("length:"+b64.length());
	//		//System.out.println(b64);
	//
	//		//String decode64 = decodeBase64String(b64);
	//		//String unzip = unzipBase64StringToString(decode64);
	//		//MapData m2 = gson.fromJson(unzip,MapData.class);
	//		//json = gson.toJson(m2);
	//		//System.out.println("json------------------------------");
	//		//System.out.println("length:"+json.length());
	//		//System.out.println(json);
	//
	//		return b64;
	//
	//
	//	}


	virtual string getName();
	virtual int getID();


	virtual void setName(const string& s);
	virtual void setID(int s);
};

