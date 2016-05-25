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
#include <assert.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>


using namespace std;

#define OPT_DEFAULT   0
#define OPT_SEEN      1
#define OPT_MANDATORY 2

static string method;
static istream *is = NULL;	
static ostream *os = NULL;	
static fstream ifs; 		
static fstream ofs;


// funci�n auxiliar ltrim
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// funci�n auxiliar rtrim
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// funci�n auxiliar trim
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

static inline std::string ltrimmed(std::string s) {
    ltrim(s);
    return s;
}

static inline std::string rtrimmed(std::string s) {
    rtrim(s);
    return s;
}

static inline std::string trimmed(std::string s) {
    trim(s);
    return s;
}



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
	bool TestFTOfZeroesIsZeroForAllTransforms()
	{
		int NMAX = 10;
		for (int n=0; n<NMAX; n++)
		{
			int m = pow((long double) 2, (int) n);
			cout << m;
			TestFTOfZeroesIsZero("fft", m);
			TestFTOfZeroesIsZero("dft", m);
			TestFTOfZeroesIsZero("ifft", m);
			TestFTOfZeroesIsZero("idft", m);
		}
		return true;
	}

	bool TestFTOfZeroesIsZero(string method="fft", int n=2)
	{
		//para un string de entrada de la forma: 0 0 0 0, el resultado de aplicar la TF (bien sea FFT, iFFT, DFT, iDFT)
		//debe ser un string de la forma (0.00,0.00) (0.00,0.00) (0.00,0.00) (0.00,0.00)
		string input = "";
		for (int i=0; i<n; i++)
		{
			input = input + "0 ";
		}
		trim(input);

		string expectedoutput = "";
		for (int i=0; i<n; i++)
		{
			expectedoutput = expectedoutput + "(0.00,0.00) ";
		}
		trim(expectedoutput);

		string output;
		Calculate(input, output, method);
		trim(output);
		//imprimo data y result.
		cout << "input: " << input << endl;
		cout << "output: " << output << endl;
		assert (output==expectedoutput);
		return true;
	}

	bool TestFTOf11(string method="fft")
	{
		string input ="1 1";
		string expectedoutput = "(2.00,0.00) (0.00,0.00)";
		string output;

		Calculate(input, output, method);
		trim(output);
		//imprimo data y result.
		cout << "input: " << input << endl;
		cout << "output: " << output << endl;
		assert (output==expectedoutput);
		return true;
	}

	bool TestFTOfii(string method="fft")
	{
		string input ="(0,1) (0,1)";
		string expectedoutput = "(0.00,2.00) (-0.00,0.00)";
		string output;

		Calculate(input, output, method);
		trim(output);
		//imprimo data y result.
		cout << "input: " << input << endl;
		cout << "output: " << output << endl;
		assert (output==expectedoutput);
		return true;
	}

	bool TestIFTOf20(string method="ifft")
	{
		string input ="2 0";
		string expectedoutput = "(1.00,0.00) (1.00,0.00)";
		string output;

		Calculate(input, output, method);
		trim(output);
		//imprimo data y result.
		cout << "input: " << input << endl;
		cout << "output: " << output << endl;
		assert (output==expectedoutput);
		return true;
	}

	bool TestIFTOf2i0(string method="ifft")
	{
		string input ="(0.00,2.00) (0.00,0.00)";
		string expectedoutput = "(0.00,1.00) (0.00,1.00)";
		string output;

		Calculate(input, output, method);
		trim(output);
		//imprimo data y result.
		cout << "input: " << input << endl;
		cout << "output: " << output << endl;
		assert (output==expectedoutput);
		return true;
	}


	bool TestFTOfSum(string method="fft")
	{

	}

	bool TestFTOfScalar(string method="fft")
	{

	}

	bool TestFTofIFT(string method="fft")
	{

	}

	bool TestIFTofFT(string method="fft")
	{

	}

	bool TestDual(string method="fft")
	{

	}

	bool TestBessel(string method="fft")
	{

	}

	bool TestParseval(string method="fft")
	{

	}

	void Calculate(string input, string& output, string method="fft")
	{
		string line = input;
		os = &cout;
		//Creo un vector que almacenar� la informaci�n le�da
		vector<complex> data = vector<complex>();
		//Creo un vector que almacenar� el resultado
		vector<complex> result = vector<complex>();
       
		istringstream iss(line);
		iss >> data;
		*os << std::setprecision(2);
		*os << std::fixed;
        
		//Dependiendo que ingreso el usuario hago una cosa u otra
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
		//Imprimo el resultado
		std::ostringstream stream;
		stream << setprecision(2);
		stream << fixed;
		stream << result;
		std::string str =  stream.str();
		const char* chr = str.c_str();
		//cout << "Ouput:" << chr;
		output = chr;

		//imprimo data y result.
		cout << "Longitud vector data: " << data.length() << endl;
		cout << "Longitud vector result: " << result.length() << endl;
		cout << "data: " << data << endl;
		cout << "result: " << result << endl;
	}

};


int main(int argc, char** argv) 
{
	UnitTests* tests = new UnitTests();
	tests->TestFTOfZeroesIsZero();
	tests->TestFTOfZeroesIsZeroForAllTransforms();
	tests->TestFTOf11("fft");
	tests->TestFTOf11("dft");
	tests->TestFTOfii("fft");
	tests->TestFTOfii("dft");
	tests->TestIFTOf20("ifft");
	tests->TestIFTOf20("idft");
	tests->TestIFTOf2i0("ifft");
	tests->TestIFTOf2i0("idft");

	return 0;
}


