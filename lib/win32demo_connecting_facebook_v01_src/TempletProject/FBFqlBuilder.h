#ifndef FBFQLBUILDER_H
#define FBFQLBUILDER_H
#include <QtGui>
#include "Constants.h"

class FBFqlBuilder
{
public:
	static FBFqlBuilder* getInstance();
	QString BuildJoinQuery(QVector <StringPer > multiFql);
private:
	 static FBFqlBuilder* _instance;
	 FBFqlBuilder();
	~FBFqlBuilder();

};
#endif