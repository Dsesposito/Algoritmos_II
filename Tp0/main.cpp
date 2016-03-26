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

using namespace std;


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
        result.pushFron(sum);
    }
} 


int main(int argc, char** argv) {
    
    //Creo un vector que almacenará la información leída
    vector<complejo> data = vector<complejo>();
    
    //Leo la información del archivo
    ifstream dataFile("Data_red.csv");
    dataFile >> data;

    //Imprimo los datos
    cout << " Datos " << endl << data << endl;
    
    //Calculo la serie
    vector<complejo> result = vector<complejo>(); ;
    calculate(data,result,"dft");
    
    //Imprimo los datos
    cout << " Datos " << endl << data << endl;
    
    //Imprimo la serie
    cout << " Resultado " << endl << result << endl;
    
    vector<complejo> inv = vector<complejo>();
    calculate(result,inv,"idft");
    
    //Imprimo la serie invertida
    cout << " Inverso " << endl << inv << endl;
    return 0;
}

