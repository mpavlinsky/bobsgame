#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>


template void NetworkGameSequence::serialize<boost::archive::xml_oarchive>(boost::archive::xml_oarchive &ar, const unsigned int);
template void NetworkGameSequence::serialize<boost::archive::xml_iarchive>(boost::archive::xml_iarchive &ar, const unsigned int);


template <typename Archive>
void NetworkGameSequence::serialize(Archive & ar, const unsigned int version)
{//=========================================================================================================================
	ar & BOOST_SERIALIZATION_NVP(uuid);
	ar & BOOST_SERIALIZATION_NVP(name);
	ar & BOOST_SERIALIZATION_NVP(description);
	ar & BOOST_SERIALIZATION_NVP(importExport_gameUUIDs);

	ar & BOOST_SERIALIZATION_NVP(randomizeSequence);
	ar & BOOST_SERIALIZATION_NVP(endlessMode);
	ar & BOOST_SERIALIZATION_NVP(currentDifficultyName);
	ar & BOOST_SERIALIZATION_NVP(builtInType);


	importExport_games.clear();
	{
		for (int i = 0; i < gameTypes.size(); i++)
		{
			GameType *bp = gameTypes.get(i);
			GameType b;
			b = *bp;
			importExport_games.add(b);
		}
	}
	ar & BOOST_SERIALIZATION_NVP(importExport_games);
	gameTypes.clear();
	for (int i = 0; i<importExport_games.size(); i++)
	{
		GameType b = importExport_games.get(i);
		GameType *bp = new GameType();
		*bp = b;
		gameTypes.add(bp);
	}
	importExport_games.clear();

}
