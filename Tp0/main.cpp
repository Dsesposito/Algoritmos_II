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


void calculate(const vector<complejo> & data , vector<complejo> & result , int expSign){
    int N = data.length();
    double re = cos(expSign*2*M_PI/N);
    double im = sin(expSign*2*M_PI/N);
    for(int i = 0 ; i < N ; i++){
        complejo sum = 0;
        for(int j = 0 ; j < N ; j++){
            complejo aux(re,im);
            aux = aux^(j*i);
            sum = sum + (data[j]*aux);
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
    calculate(data,result,-1);
    
    //Imprimo los datos
    cout << " Datos " << endl << data << endl;
    
    //Imprimo la serie
    cout << " Resultado " << endl << result << endl;
    
    vector<complejo> inv = vector<complejo>();
    calculate(result,inv,1);
    
    //Imprimo la serie invertida
    cout << " Inverso " << endl << inv << endl;
    return 0;
}

