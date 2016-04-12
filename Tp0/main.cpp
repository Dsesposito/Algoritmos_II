/* 
 * File:   main.cpp
 * Author: diego
 *
 * Created on March 21, 2016, 8:09 PM
 */

#include <cstdlib>
#include "DFTcalculator.cc"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include "cmdline.h"
#include "cmdlineConfigurator.cpp"


using namespace std;



int main(int argc, char** argv) {
   
    //Creo un vector que almacenará la información leída
    vector<complejo> data = vector<complejo>();
    
    //Leo las opciones con las que me ejecutan el programa
    cmdline cmdl(cmdlineConfigurator.options);	
    cmdl.parse(argc, argv);
    
    //Leo la información del stream de entrada
    *iss >> data;

    //Calculo la serie
    vector<complejo> result = vector<complejo>(); ;
    if(method = "dft"){
        DFTcalculator.calculateDFT(data,result,method);
    }
    else if(method = "idft"){
        DFTcalculator.calculateIDFT(data,result,method);   
    }
    
    
    //Guardo el resultado en el stream de salida
    *oss << result << endl;

    
    return 0;
}

