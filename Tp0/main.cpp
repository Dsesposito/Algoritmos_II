/* 
 * File:   main.cpp
 * Author: diego
 *
 * Created on March 21, 2016, 8:09 PM
 */

#include <cstdlib>
#include "vector.h"
#include "complejo.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include "cmdline.h"

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

void calculate(const vector<complejo> & data , vector<complejo> & result , string algorithm){
    int N = data.length();
    double re = cos(2*M_PI/N);
    double im = sin(2*M_PI/N);
    int sign = 1;
    if(algorithm == "idft"){
        sign = -1;
    }
    for(int i = 0 ; i < N ; i++){
        complejo sum = 0;
        for(int j = 0 ; j < N ; j++){
            complejo aux(re,im);
            aux = aux^(sign*j*i);
            sum = sum + (data[j]*aux);
        }
        if(algorithm == "idft"){
            sum = sum / N;
        }
        result.pushBack(sum);
    }
} 


int main(int argc, char** argv) {
    
    //Creo un vector que almacenará la información leída
    vector<complejo> data = vector<complejo>();
    
    //Leo las opciones con las que me ejecutan el programa
    cmdline cmdl(options);	
    cmdl.parse(argc, argv);
    
    //Leo la información del stream de entrada
    *iss >> data;

    //Calculo la serie
    vector<complejo> result = vector<complejo>(); ;
    calculate(data,result,method);
    
    //Guardo el resultado en el stream de salida
    *oss << result << endl;
    
    return 0;
}

