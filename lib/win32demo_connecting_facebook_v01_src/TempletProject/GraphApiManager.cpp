#include "GraphApiManager.h"

GraphApiManager* GraphApiManager::_instance = NULL ;

GraphApiManager* GraphApiManager::getInstance()
{
    if(GraphApiManager::_instance == NULL)
    {
        GraphApiManager::_instance = new GraphApiManager();
    }
    return _instance;
}

 

GraphApiManager::GraphApiManager()
{	
	 
	 ;
 	 
}

GraphApiManager::~GraphApiManager()
{	
	 
	 ;
 	 
}

void GraphApiManager::SetUserByName(const QString& key,UserObject* UserOBj)
{
	UserObjectHash.insert(key,UserOBj);
}
UserObject* GraphApiManager::GetUserObjByName(const QString& key)
{
	return UserObjectHash.value(key);
}