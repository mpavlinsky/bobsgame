#ifndef _GRAPHAPIMANAGER_H_
#define _GRAPHAPIMANAGER_H_
#include <QtGui>
#include "UserObject.h"

class GraphApiManager
{

	public:
		virtual ~GraphApiManager();
		static GraphApiManager* getInstance();
		void SetUserByName(const QString& key,UserObject* UserOBj);
		UserObject* GetUserObjByName(const QString& key);


	private:
		static GraphApiManager* _instance;
		GraphApiManager();
 		QHash<QString,UserObject*> UserObjectHash;
		
	


};


#endif
