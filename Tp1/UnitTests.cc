/* 
 * File:   UnitTests.cpp
 * Author: Diego / Marcelo
 *
 */


#include <cstdlib>
#include "vector.h"
#include "complex.cc"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>  
#include <cmath>
#include "cmdline.cc"
#include "DFTcalculator.h"
#include <ctime>

using namespace std;

#define OPT_DEFAULT   0
#define OPT_SEEN      1
#define OPT_MANDATORY 2

static string method;
static istream *is = NULL;	
static ostream *os = NULL;	
static fstream ifs; 		
static fstream ofs;


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
	bool TestL2Distance1()
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

	void Calculate(string input, string& output)
	{
		string line = input;
		while(getline(*is,line)){
			vector<complex> data = vector<complex>();
			vector<complex> result = vector<complex>();
			istringstream iss(line);
			iss >> data;
			*os << std::setprecision(2);
			*os << std::fixed;
			if(method == "dft"){
				//Calculo la DFT
				DFTcalculator::calculateDFT(data,result); 
			}
			else if(method == "idft"){
				//Calculo la DFT
				DFTcalculator::calculateiDFT(data,result); 
			}
			else if(method == "fft"){
				//Calculo la FFT
				DFTcalculator::calculateFFT(data,result); 
			}
			else if(method == "ifft"){
				//Calculo la iFFT
				DFTcalculator::calculateiFFT(data,result); 
			}

			std::ostringstream stream;
			stream << result;
			std::string str =  stream.str();
			const char* chr = str.c_str();
			cout << "Ouput:" << str;
			output = stream.str();
		}
	}

};


int main(int argc, char** argv) 
{

}


