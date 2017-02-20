#ifndef _GROUP_H_
#define _GROUP_H_
#include <QtGui>

class Group 
{

public:
	Group();
	virtual ~Group();

	QString GetGroupId(){return gid;}
	QString GetGroupNid(){return nid;}
	QString GetGroupName(){return name;}
	QString GetGroupDescription(){return description;}
	QString GetGroupGroupType(){return group_type;}
	QString GetGroupGroupSubtype(){return group_subtype;}
	QString GetGroupRecentNews(){return recent_news;}
	int GetGroupUpdateTime(){return update_time;}
	int GetGroupUpdateTimeCalculated(){return update_time_Calculated;}
	QString GetGroupPrivacy(){return privacy;}
	//void GetGroupLink(){return link;}
	
	
	
	void SetGroupId(QString& _gid){gid = _gid;}
	void SetGroupNid(QString& _nid){nid = _nid;}
	void SetGroupName(QString& _name){name = _name;}
	void SetGroupDescription(QString& _description){description = _description;}
	void SetGroupGroupType(QString& _group_type){group_type = _group_type;}
	void SetGroupGroupSubtype(QString& _group_subtype){group_subtype = _group_subtype;}
	void SetGroupRecentNews(QString& _recent_news){recent_news = _recent_news;}
	void SetGroupUpdateTime(int& _update_time){update_time = _update_time;}
	void SetGroupUpdateTimeCalculated(int& _update_time_Calculated){update_time_Calculated = _update_time_Calculated;}
	void SetGroupPrivacy(QString& _privacy){privacy = _privacy;}
	void SetGroupLink(QString& _link){link = _link;}
	



private:
	QString gid;
	QString	nid;
	QString	name;
	QString	description;
	QString	group_type;
	QString	group_subtype;
	QString	recent_news;
	int	update_time;
	int update_time_Calculated;
	QString	privacy;
	QString link;

};

#endif