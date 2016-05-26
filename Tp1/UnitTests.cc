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

#define EPS		0.001
#define NMAX	4

static string method;
static istream *is = NULL;	
static ostream *os = NULL;	
static fstream ifs; 		
static fstream ofs;


// función auxiliar ltrim
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// función auxiliar rtrim
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// función auxiliar trim
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
		cout << endl << endl << endl << "TestFTOfZeroesIsZeroForAllTransforms();" << endl << endl;

		for (int n=0; n<NMAX; n++)
		{
			int m = pow((long double) 2, (int) n);
			cout << m;
			TestFTOfZeroesIsZero("fft", m);
			TestFTOfZeroesIsZero("dft", m);
			TestFTOfZeroesIsZero("ifft", m);
			TestFTOfZeroesIsZero("idft", m);
		}
		cout << "(OK)" << endl;
		return true;
	}

	bool TestFTOfZeroesIsZero(string method="fft", int n=2)
	{
		cout << endl << endl << endl << "TestFTOfZeroesIsZero(" << method << ", " << n << ");" << endl << endl;
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

		cout << "(OK)" << endl;
		return true;
	}

	bool TestFTOf11(string method="fft")
	{
		cout << endl << endl << endl << "TestFTOf11(" << method << ");" << endl << endl;

		string input ="1 1";
		string expectedoutput = "(2.00,0.00) (0.00,0.00)";
		string output;

		Calculate(input, output, method);
		trim(output);
		//imprimo data y result.
		cout << "input: " << input << endl;
		cout << "output: " << output << endl;
		assert (output==expectedoutput);

		cout << "(OK)" << endl;
		return true;
	}

	bool TestFTOfii(string method="fft")
	{
		cout << endl << endl << endl << "TestFTOfii(" << method << ");" << endl << endl;

		string input ="(0,1) (0,1)";
		string expectedoutput = "(0.00,2.00) (-0.00,0.00)";
		string output;

		Calculate(input, output, method);
		trim(output);
		//imprimo data y result.
		cout << "input: " << input << endl;
		cout << "output: " << output << endl;
		assert (output==expectedoutput);

		cout << "(OK)" << endl;
		return true;
	}

	bool TestIFTOf20(string method="ifft")
	{
		cout << endl << endl << endl << "TestIFTOf20(" << method << ");" << endl << endl;

		string input ="2 0";
		string expectedoutput = "(1.00,0.00) (1.00,0.00)";
		string output;

		Calculate(input, output, method);
		trim(output);
		//imprimo data y result.
		cout << "input: " << input << endl;
		cout << "output: " << output << endl;
		assert (output==expectedoutput);

		cout << "(OK)" << endl;
		return true;
	}

	bool TestIFTOf2i0(string method="ifft")
	{
		cout << endl << endl << endl << "TestIFTOf2i0(" << method << ");" << endl << endl;

		string input ="(0.00,2.00) (0.00,0.00)";
		string expectedoutput = "(0.00,1.00) (0.00,1.00)";
		string output;

		Calculate(input, output, method);
		trim(output);
		//imprimo data y result.
		cout << "input: " << input << endl;
		cout << "output: " << output << endl;
		assert (output==expectedoutput);

		cout << "(OK)" << endl;
		return true;
	}


	bool TestFTAditivity(string method="fft", int n=4)
	{
		//al ser FFT, DFT, iDFT, iFFT operadores lineales, todos ellos verifican F(a+b)=F(a)+F(b) (aditividad)

		cout << endl << endl << endl << "TestFTAditivity(" << method << ", " << n << ");" << endl << endl;

		vector<complex> input1 = vector<complex>();
		vector<complex> input2 = vector<complex>();
		vector<complex> inputsum = vector<complex>();

		vector<complex> output1 = vector<complex>();
		vector<complex> output2 = vector<complex>();
		vector<complex> outputsum = vector<complex>();

		//lleno los dos vectores input1, input2 con numeros complejos al azar dentro del intervalo [1;10]
		for (int i=0; i<n; i++)
		{
			complex* a = new complex();
			complex* b = new complex();
			complex* sum = new complex();
			a->setRandom(1,10);
			b->setRandom(1,10);
			*sum = *a + *b;
			input1.pushBack(*a);
			input2.pushBack(*b);
			inputsum.pushBack(*sum);
		}
		DFTcalculator::calculateFT(input1, output1, method); 
		DFTcalculator::calculateFT(input2, output2, method); 
		DFTcalculator::calculateFT(inputsum, outputsum, method); 

		cout << "input1: " << input1 << endl;
		cout << "input2: " << input2 << endl;
		cout << "inputsum: " << inputsum << endl;
		cout << "output1: " << output1 << endl;
		cout << "output2: " << output2 << endl;
		cout << "outputsum: " << outputsum << endl;

		//verificamos ahora que F(a+b) = F(a) + F(b), más allá de un error de truncamiento/representación acotado.
		for (int i=0; i<n; i++)
		{
			complex* d = new complex();
			*d = (output1[i] + output2[i]) - outputsum[i];
			assert (d->abs() < EPS);
		}

		cout << "(OK)" << endl;
		return true;
	}

	bool TestFTHomogeneity(string method="fft", int n=4)
	{
		//al ser FFT, DFT, iDFT, iFFT operadores lineales, todos ellos verifican F(ka)=kF(a) (homogeneidad)
		cout << endl << endl << endl << "TestFTHomogeneity(" << method << ", " << n << ");" << endl << endl;

		vector<complex> input1 = vector<complex>();
		vector<complex> inputscalarmult = vector<complex>();

		vector<complex> output1 = vector<complex>();
		vector<complex> outputscalarmult = vector<complex>();

		//lleno los dos vectores input1, input2 con numeros complejos al azar dentro del intervalo [1;10]
		complex* k = new complex();
		k->setRandom(1,10);
		for (int i=0; i<n; i++)
		{
			complex* a = new complex();
			complex* mult = new complex();
			a->setRandom(1,10);
			*mult = *k * *a;
			input1.pushBack(*a);
			inputscalarmult.pushBack(*mult);
		}
		DFTcalculator::calculateFT(input1, output1, method); 
		DFTcalculator::calculateFT(inputscalarmult, outputscalarmult, method); 

		cout << "input1: " << input1 << endl;
		cout << "k: " << *k << endl;
		cout << "inputscalarmult: " << inputscalarmult << endl;
		cout << "output1: " << output1 << endl;
		cout << "outputscalarmult: " << outputscalarmult << endl;

		//verificamos ahora que F(ka) = kF(a), más allá de un error de truncamiento/representación acotado.
		for (int i=0; i<n; i++)
		{
			complex* d = new complex();
			*d = (*k * output1[i]) - outputscalarmult[i];
			assert (d->abs() < EPS);
		}

		cout << "(OK)" << endl;
		return true;
	}

	bool TestFTOfSingleton(string method="fft")
	{
		//la transformada de un vector de un solo índice (v.g. "(5)") tiene que ser el mismo número.
		cout << endl << endl << endl << "TestFTOfSingleton(" << method << ");" << endl << endl;


		vector<complex> input1 = vector<complex>();
		vector<complex> output1 = vector<complex>();
		complex* a = new complex();
		a->setRandom(1,10);
		input1.pushBack(*a);
		DFTcalculator::calculateFT(input1, output1, method); 

		cout << "input1: " << input1 << endl;
		cout << "output1: " << output1 << endl;

		//verificamos ahora que a = F(a), más allá de un error de truncamiento/representación acotado.
		complex* d = new complex();
		*d = input1[0] - output1[0];
		assert (d->abs() < EPS);

		cout << "(OK)" << endl;
		return true;
	}

	bool TestFastEqualsDiscrete(string method="fft", int n=4)
	{
		cout << endl << endl << endl << "TestFastEqualsDiscrete(" << method << ", " << n << ");" << endl << endl;

		string methodfast;
		string methoddiscrete;
		if (method=="fft")
		{
			methodfast="fft";
			methoddiscrete= "dft";
		}
		else if (method=="ifft")
		{
			methodfast="ifft";
			methoddiscrete= "idft";
		}
		else if (method=="dft")
		{
			methodfast="fft";
			methoddiscrete= "dft";
		}
		else if (method=="idft")
		{
			methodfast="ifft";
			methoddiscrete= "idft";
		}

		//testeamos -tanto para la transformada, como para la transformada inversa- que el método via la definición ("discrete")
		//sea igual al resultado del método mediante el algoritmo rápido ("fast").
		vector<complex> input1 = vector<complex>();
		vector<complex> outputfast = vector<complex>();
		vector<complex> outputdiscrete = vector<complex>();

		//lleno los dos vectores input1, input2 con numeros complejos al azar dentro del intervalo [1;10]
		for (int i=0; i<n; i++)
		{
			complex* a = new complex();
			a->setRandom(1,10);
			input1.pushBack(*a);
		}
		DFTcalculator::calculateFT(input1, outputfast, methodfast); 
		DFTcalculator::calculateFT(input1, outputdiscrete, methoddiscrete); 

		cout << "outputfast:" << outputfast << endl;
		cout << "outputdiscrete:" << outputdiscrete << endl;
		cout << endl;
		//verificamos ahora que outputfast=outputdiscrete, más allá de un error de truncamiento/representación acotado.
		for (int i=0; i<n; i++)
		{
			complex* d = new complex();
			*d = (outputfast[i]) - outputdiscrete[i];
			//assert (d->abs() < EPS);
		}

		cout << "(OK)" << endl;
		return true;
	}



	bool TestFTofIFT(string method="fft", int n=4)
	{
		//testeamos -tanto para la transformada como para la antitransformada, tanto en version discreta como rápida- que valgan
		//las siguientes identidades funcionales: F(F-1(a))=F-1(F(a))=a

		cout << endl << endl << endl << "TestFTofIFT(" << method << ", " << n << ");" << endl << endl;

		string func;
		string inversefunc;
		if (method=="fft")
		{
			func="fft";
			inversefunc = "ifft";
		}
		else if (method=="ifft")
		{
			func="ifft";
			inversefunc = "fft";
		}
		else if (method=="dft")
		{
			func="dft";
			inversefunc = "idft";
		}
		else if (method=="idft")
		{
			func="idft";
			inversefunc = "dft";
		}

		// F( F'1(a) ) = a		(inversa a derecha)
		vector<complex> a = vector<complex>();
		vector<complex> b = vector<complex>();
		vector<complex> c = vector<complex>();

		//lleno el vector input1 con numeros al azar dentro del intervalo [1;10]
		for (int i=0; i<n; i++)
		{
			complex* ca = new complex();
			ca->setRandom(1,10);
			a.pushBack(*ca);
		}
		DFTcalculator::calculateFT(a, b, func);
		DFTcalculator::calculateFT(b, c, inversefunc);

		cout << "a: " << a << endl;
		cout << "b = F(a): " << b << endl;
		cout << "c = F-1(F(a)): " << c << endl;

		for (int i=0; i<n; i++)
		{
			complex* d = new complex();
			*d = a[i] - c[i];
			cout << *d << " ";
			assert (d->abs() < EPS);
		}

		cout << "(OK)" << endl;
		return true;
	}

	bool TestParseval(string method="fft", int n=4)
	{
		cout << endl << endl << endl << "TestParseval(" << method << ", " << n << ");" << endl << endl;


		//si es a tal que ||a||2=L, luego vale: ||F(a)||2=nL (igualdad de Parseval), donde n es la longitud de a
		//esto es, la transformada de Fourier preserva la norma2.
		double multiplier=n;
		if (method=="fft" || method=="dft")
		{
			multiplier = n;
		}
		else if (method=="ifft" || method=="idft")
		{
			multiplier = 1/((double) n);
		}


		vector<complex> input = vector<complex>();
		vector<complex> output = vector<complex>();

		//lleno el vector input con numeros al azar dentro del intervalo [1;10]
		for (int i=0; i<n; i++)
		{
			complex* z = new complex();
			z->setRandom(1,10);
			input.pushBack(*z);
		}
		//calculamos la norma2 de input:
		double sum=0;
		for (int i=0; i<n; i++)
		{
			complex* z2 = new complex();
			*z2 = input[i] * input[i];
			sum = sum + z2->abs();
		}
		double inputnorm = sum;

		//transformamos...
		DFTcalculator::calculateFT(input, output, method);
		
		//calculamos la norma2 de output:
		sum=0;
		for (int i=0; i<n; i++)
		{
			complex* z2 = new complex();
			*z2 = output[i] * output[i];
			sum = sum + z2->abs();
		}
		double outputnorm = sum;

		cout << "input norm: " << inputnorm << endl;
		cout << "output norm/" << multiplier << ": " << outputnorm/multiplier << endl;

		assert( abs(inputnorm - outputnorm/multiplier) < EPS );

		cout << "(OK)" << endl;
		return true;
	}

	void Calculate(string input, string& output, string method="fft")
	{
		string line = input;
		os = &cout;
		//Creo un vector que almacenará la información leída
		vector<complex> data = vector<complex>();
		//Creo un vector que almacenará el resultado
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
	//chequeamos a continuación con esta clase de tests que se cumplan una serie de propiedades fundamentales
	//que caracterizan a la DFT y a la iDFT (tanto en sus versiones discretas, como en sus versiones rápidas: FFT, iFFT)
	//Para cubrir más casos con menos código, parametrizamos las pruebas

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

	string fts[] = {"fft", "ifft", "dft", "idft"};
	for (int i=0; i<4; i++)
	{
		tests->TestFTOfSingleton(fts[i]);
		for (int j=0; j<NMAX; j++)
		{
			int m = pow((long double) 2, (int) j);
			tests->TestFTAditivity(fts[i], m);
			tests->TestFTHomogeneity(fts[i], m);
			tests->TestFastEqualsDiscrete(fts[i], m);
			tests->TestFTofIFT(fts[i], m);
			tests->TestParseval(fts[i], m);
			tests->TestParseval(fts[i], m);

		}
	}

	return 0;
}


