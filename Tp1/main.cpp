/* 
 * File:   main.cpp
 * Author: Diego / Marcelo
 *
 * Created on March 21, 2016, 8:09 PM
 */

#include <cstdlib>
#include "vector.h"
#include "complejo.h"
#include <fstream>
#include <iostream>
#include <sstream>  
#include <cmath>
#include "cmdline.h"
#include "DFTcalculator.h"

using namespace std;

#define OPT_DEFAULT   0
#define OPT_SEEN      1
#define OPT_MANDATORY 2


static string method;
static istream *iss = NULL;	
static ostream *oss = NULL;	
static fstream ifs; 		
static fstream ofs;

static void opt_input(string const &arg){
    if (arg == "-") {
        iss = &cin;
    }
    else {
        ifs.open(arg.c_str(), ios::in); 
        iss = &ifs;
    }

    if (!iss->good()) {
        cerr << "cannot open " << arg << "." << endl;
        abort();
    }
}

static void opt_output(string const &arg){
    if (arg == "-") {
        oss = &cout;
    } 
    else {
        ofs.open(arg.c_str(), ios::out);
        oss = &ofs;
    }

    if (!oss->good()) {
        cerr << "cannot open " << arg << "." << endl;
        abort();
    }
}

static void opt_help(string const &arg){
    cout << "cmdline [-m method] [-i file] [-o file]" << endl;
    cout << "The default input output are the standar IO.";
    cout << "The default method is discrete fourier transform.";
    exit(0);
}

static void opt_method(string const &arg){
    method = arg;
}

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "m", "method", "dft", opt_method, OPT_DEFAULT},
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
    
    while(1){
        
        cout << "Ingrese una secuencia de numeros complejos, al finalizar presione enter " << endl;
        
        //Creo un vector que almacenará la información leída
        vector<complejo> data = vector<complejo>();

        //Leo la información del stream de entrada
        string line;
        getline(cin,line);
        
        istringstream iss(line);
        iss >> data;
        cout << endl;
        
        //Calculo la serie
        vector<complejo> result = vector<complejo>();
        
        DFTcalculator::calculateDFT(data,result);
        
        
        //Calculo la serie
        vector<complejo> result_II = vector<complejo>();
        
        DFTcalculator::calculateFFT(data,result_II);
        
        //Guardo el resultado en el stream de salida
        cout << "El resultado es: " << endl << result << endl;
        
        //Guardo el resultado en el stream de salida
        cout << "El resultado es: " << endl << result_II << endl;
    }
    return 0;
}


    /*
    
     * //43228000
    */ 