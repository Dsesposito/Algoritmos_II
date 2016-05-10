/* 
 * File:   DFTcalculator.cc
 * Author: diego / marce
 *
 * Created on March 21, 2016, 8:09 PM
 */

#include <cstdlib>
#include "vector.h"
#include "complejo.cc"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

class DFTcalculator
{
    private:
    static void calculate(const vector<complejo> & data , vector<complejo> & result , string algorithm){
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


    public:
    static void calculateDFT(const vector<complejo> & data , vector<complejo> & result)
    {
        calculate(data , result , "dft");
    }

    static void calculateIDFT(const vector<complejo> & data , vector<complejo> & result)
    {
        calculate(data , result , "idft");
    }

};
