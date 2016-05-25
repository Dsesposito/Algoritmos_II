/* 
 * File:   main.cpp
 * Author: Diego / Marcelo
 *
 * Created on March 21, 2016, 8:09 PM
 */

#include <cstdlib>
#include "vector.h"
#include "complex.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>  
#include <cmath>
#include "cmdline.h"
#include "DFTcalculator.h"
#include <ctime>
//#include "libs/plog/Log.h"

using namespace std;

#define OPT_DEFAULT   0
#define OPT_SEEN      1
#define OPT_MANDATORY 2


static string method;
static istream *is = NULL;	
static ostream *os = NULL;	
static fstream ifs; 		
static fstream ofs;

static void opt_input(string const &arg){
    if (arg == "-") {
        is = &cin;
    }
    else {
        ifs.open(arg.c_str(), ios::in); 
        is = &ifs;
    }

    if (!is->good()) {
        cerr << "cannot open " << arg << "." << endl;
        abort();
    }
}

static void opt_output(string const &arg){
    if (arg == "-") {
        os = &cout;
    } 
    else {
        ofs.open(arg.c_str(), ios::out);
        os = &ofs;
    }

    if (!os->good()) {
        cerr << "cannot open " << arg << "." << endl;
        abort();
    }
}

static void opt_help(string const &arg){
    cout << "cmdline [-m \"dft\" \"idft\" \"fft\" \"ifft\"] [-i file] [-o file]" << endl;
    cout << "The default input output are the standard IO.";
    cout << "The default method is the discrete fast fourier transform (fft).";
    exit(0);
}

static void opt_method(string const &arg){
    method = arg;
}

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "m", "method", "fft", opt_method, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

/**
 * Función main. El programa espera por comando que le configuren el stream de entrada
 * de donde tomará los datos para calcular la transformada discreta de fourier. 
 * Además necesita que le configuren el stream de salida a donde escribirá los
 * datos obtenidos. 
 */
int main(int argc, char** argv) {
    
    //Leo las opciones con las que me ejecutan el programa
    cmdline cmdl(options);	
    cmdl.parse(argc, argv);
    
    //Leo la información del stream de entrada linea por linea
    string line;
    while(getline(*is,line)){
        
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
        *os << result;


		//imprimo data y result.
		cout << "Longitud vector data: " << data.length() << endl;
		cout << "Longitud vector result: " << result.length() << endl;
		cout << "data: " << data << endl;
		cout << "result: " << result << endl;

    }
    return 0;
}


    /*
    
     * //43228000
    */ 