#include "FBFqlBuilder.h"
#include "UT.h"
FBFqlBuilder* FBFqlBuilder::_instance = NULL ;


FBFqlBuilder::FBFqlBuilder()
{
	;
}

FBFqlBuilder* FBFqlBuilder::getInstance()
{
    
 	if(_instance == NULL)
    {
        _instance = new FBFqlBuilder();
        
    }
    return _instance;
}


QString FBFqlBuilder::BuildJoinQuery(QVector <StringPer > multiFql)
{
	QString CompliteJoinFql = "";
	for(int i=0;i<multiFql.size(); i++)
	{
		if(i==0)
		{
			CompliteJoinFql.append("{\""+multiFql.at(i).key+"\":");
			CompliteJoinFql.append("\""+multiFql.at(i).val+"\",");
		}
		else if (i == (multiFql.size()-1))
		{
			CompliteJoinFql.append("\""+multiFql.at(i).key+"\":");
			CompliteJoinFql.append("\""+multiFql.at(i).val+"\"}");
			
		}
		else 
		{
			CompliteJoinFql.append("\""+multiFql.at(i).key+"\":");
			CompliteJoinFql.append("\""+multiFql.at(i).val+"\",");
		}
		
	}

	return CompliteJoinFql;

}