//----------------------------------------------------------------------------------------
//	Copyright © 2007 - 2015 Tangible Software Solutions Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class includes methods to convert multidimensional arrays to C++ vectors.
//----------------------------------------------------------------------------------------




class PotentialTile;

class RectangularVectors
{
public:
	static bool** ReturnRectangularBoolVector(int size1, int size2)
	{
		bool** newVector = new bool*[size1];
		for (int vector1 = 0; vector1 < size1; vector1++)
		{
			newVector[vector1] = new bool[size2];
		}

		return newVector;
	}

	static ArrayList<ArrayList<PotentialTile*>*>* ReturnRectangularPotentialTileVector(int size1, int size2)
	{
		ArrayList<ArrayList<PotentialTile*>*>* newVector = new ArrayList<ArrayList<PotentialTile*>*>(size1);
		for (int vector1 = 0; vector1 < size1; vector1++)
		{
			newVector->add(new ArrayList<PotentialTile*>(size2));
		}

		return newVector;
	}
};

