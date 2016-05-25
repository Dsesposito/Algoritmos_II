

class UnitTests
{
private:
	double L2Distance(vector<complex> v1, vector<complex> v2)
	{
		double s = 0;
		for (int i=0; i < v1.length(); i++)
		{
			complex a = (v1[i] - v2[i])*(v1[i] - v2[i]);
			s = s + a.abs();
		}
		return sqrt(s);
	}

public:
	bool TestL2Distance()
	{
				
	}

	bool TestFTOfZeroesIsZero(string algorithm)
	{

	}

	bool TestFTOf11(string algorithm)
	{

	}

	bool TestFTOfii(string algorithm)
	{

	}

	bool TestFTOfSum(string algorithm)
	{

	}

	bool TestFTOfScalar(string algorithm)
	{

	}

	bool TestFTofIFT(string algorithm)
	{

	}

	bool TestIFTofFT(string algorithm)
	{

	}

	bool TestDual(string algorithm)
	{

	}

};