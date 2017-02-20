#ifndef _USEROBJECT_H_
#define _USEROBJECT_H_
#include <QtGui>
#include "Group.h"

class UserObject 
{

public:
	UserObject();
	virtual ~UserObject();

	QString GetUserid(){return id;}
	QString GetUserName(){return name;}
	QString GetUserFirstName(){return first_name;}
	QString GetUserLastName(){return last_name;}
	QString GetUserLink(){return link;}
	QString GetUserUserName(){return username;}
	Group* GetUserGroupByKey(QString& key){return UserGroups.value(key); }
	QHash<QString,Group* > GetUserGroups() {return UserGroups;}

	void SetUserid(QString& _id){id = _id;}
	void SetUserName(QString& _name){  name = _name;}
	void SetUserFirstName(QString& _first_name){  first_name = _first_name;}
	void SetUserLastName(QString& _last_name){  last_name = _last_name;}
	void SetUserLink(QString& _link){  link = _link;}
	void SetUserUserName(QString& _username){  username = _username;}
	void SetUserGroupByKey(QString& key,Group* group) { UserGroups.insert(key,group);}

private:
	QString id;
	QString name;
	QString first_name;
	QString last_name;
	QString link;
	QString username;
	QHash<QString,Group* > UserGroups;


};

#endif

/*
{
    "data": [
        {
            "version": 0,
            "name": "Software Engineer's Group",
            "id": "21704303620"
        },
        {
            "version": 0,
            "name": "C++ Software Developer",
            "id": "186274162277"
        },
        {
            "version": 0,
            "name": "Facebook Forum",
            "id": "4856066025"
        },
        {
            "version": 0,
            "name": "Facebook Forum",
            "id": "58632684926"
        },
        {
            "version": 0,
            "name": "Facebook Users Forum",
            "id": "9006967018"
        },
        {
            "version": 1,
            "name": "05dc05d905d905df 05d405d005d905d805d905d905d6 05d505d405e105d905e005d805e405d505e4 05e905dc 05e905e805d905ea 05d105e805d505da - VELVET",
            "id": "170373909681418"
        },
        {
            "version": 1,
            "name": "Israeli Unity3d developers",
            "id": "117674854958307",
            "unread": 9,
            "bookmark_order": 5
        },
        {
            "version": 1,
            "name": "GameIS (Chat)",
            "id": "140758979305408",
            "unread": 14,
            "bookmark_order": 4
        },
        {
            "version": 1,
            "name": "GameIS",
            "id": "4173160339",
            "unread": 27,
            "bookmark_order": 9
        },
        {
            "version": 1,
            "name": "05d405e405d505e805d505dd",
            "id": "160725573973756",
            "unread": 29,
            "bookmark_order": 2
        },
        {
            "version": 1,
            "name": "05e4\r\n05d505e805d505dd 05d605e705e005d9 05d405e405d905e005d205d505d505d905df",
            "id": "175923872448029",
            "unread": 3,
            "bookmark_order": 1
        },
        {
            "version": 1,
            "name": "05e005e405d205e905d905dd 05db05d305d9 05dc05e805d505e5",
            "id": "155611041157213",
            "bookmark_order": 7
        },
        {
            "version": 0,
            "name": "Irrlicht Engine Users",
            "id": "2217640425"
        },
        {
            "version": 1,
            "name": "Hacker News",
            "id": "114326995294656",
            "unread": 28,
            "bookmark_order": 3
        },
        {
            "version": 0,
            "name": "Computer Programmers",
            "id": "2202505910"
        },
        {
            "version": 0,
            "name": "International Game Developers Association",
            "id": "2225842301"
        },
        {
            "version": 0,
            "name": "Game Development",
            "id": "2204698720"
        },
        {
            "version": 0,
            "name": "GARY NUMAN TO LIVE PERFORMANCE IN ISRAEL",
            "id": "102906996423335"
        },
        {
            "version": 1,
            "name": "05de05e405e805d205e005d905dd 05dc05d705d105e805d905dd 05e905de05e405ea05d705d905dd 05d005e405dc05d905e705e605d905d505ea - 05d505de05e705d305de05d905dd 05d005e405dc05d905e705e\r\n605d905d505ea 05db05d705d505dc-05dc05d105df",
            "id": "105474902826094",
            "unread": 1,
            "bookmark_order": 8
        },
        {
            "version": 0,
            "name": "Hang the DJ",
            "id": "119152254312"
        },
        {
            "version": 0,
            "name": "Join A Startup",
            "id": "2333202493"
        },
        {
            "version": 0,
            "name": "LinQ - 05e705d405d905dc05ea 05d005e005e905d9 05d405d405d905d905d805e7 05d105d905e905e805d005dc",
            "id": "6704249980"
        },
        {
            "version": 0,
            "name": "Web 2.0 (Entrepreneurs)",
            "id": "2208499259"
        },
        {
            "version": 1,
            "name": "Qt by Nokia",
            "id": "39687139470",
            "unread": 16,
            "bookmark_order": 6
        },
        {
            "version": 0,
            "name": "Facebook Developers",
            "id": "2205007948"
        },
        {
            "version": 1,
            "name": "05d905d505e605d005d9 05d405de05d505e205d305d505e005d905dd \"05e405d905e005d205d505d505d905df\" 05d5\"05d605de05df 05d005de05d905ea05d9\" 05dc05d305d505e805d505ea05d905d405dd",
            "id": "12440230188",
            "unread": 43
        }
    ]
}
"id": "557002013",
   "name": "Meir Yanovich",
   "first_name": "Meir",
   "last_name": "Yanovich",
   "link": "http://www.facebook.com/meiryanovich",
   "username": "meiryanovich",
   "birthday": "07/12/1975",
   "location": {
      "id": "106906559341067",
      "name": "Pardes Hanah, Hefa, Israel"
   },
   "work": [
      {
         "employer": {
            "id": "109527032400843",
            "name": "FTS"
         },
         "location": {
            "id": "107093055987618",
            "name": "Herzlia B, Tel Aviv, Israel"
         },
         "position": {
            "id": "155706291153210",
            "name": "cross platform c++/java developer"
         },
         "start_date": "2002-00"
      }
   ],
   "relationship_status": "Married",
   "significant_other": {
      "name": "Maya Yanovich",
      "id": "755290628"
   },
   "website": "http://www.linkedin.com/in/meiryanovich",
   "timezone": 3,
   "locale": "en_US",
   "verified": true,
   "updated_time": "2011-05-18T21:15:36+0000"


*/