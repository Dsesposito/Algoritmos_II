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

using namespace std;


int main(int argc, char** argv) {
    
	cout << "TP0" << endl;

    //Creo un vector que almacenará la información leída
    vector<complejo> data = vector<complejo>();
    
    //Leo la información del archivo
    ifstream dataFile("Data_red.csv");
    dataFile >> data;

    //Imprimo los datos
    cout << " Datos " << endl << data << endl;
    
    //Calculo la serie
    vector<complejo> result = vector<complejo>(); ;
    DFTcalculator dftcalculator = DFTcalculator();
	dftcalculator.calculateDFT(data,result);
    
    //Imprimo los datos
    cout << " Datos " << endl << data << endl;
    
    //Imprimo la serie
    cout << " Resultado " << endl << result << endl;
    
    vector<complejo> inv = vector<complejo>();
    dftcalculator.calculateIDFT(result,inv);
    
    //Imprimo la serie invertida
    cout << " Inverso " << endl << inv << endl;
    return 0;
}

