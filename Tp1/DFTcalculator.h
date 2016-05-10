/* 
 * File:   DFTcalculator.cc
 * Author: Diego / Marcelo
 *
 * Created on March 21, 2016, 8:09 PM
 */

#include <cstdlib>
#include "vector.h"
#include "complejo.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

/**
 * Clase DFTcalculator. Esta clase contiene una serie de metodos que permiten
 * calcular la transformada discreta de fourier y la transformada inversa
 * de fourier.
 */
class DFTcalculator
{
    private:
        
        
    /**
     * Metodo privado estatico calculate. Este metodo permite calcular tanto la
     * transformada como la anti transformada de fourier. Es un metodo privado que
     * utiliza la clase.
     */
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
        
    /**
     * Método el cual permite calcular la transformada discreta de fourier. Recibe
     * por parámetro dos vectores uno con la información y otro donde escribirá
     * el resultado.
     */
    static void calculateDFT(const vector<complejo> & data , vector<complejo> & result)
    {
        calculate(data , result , "dft");
    }

    /**
     * Método el cual permite calcular la anti-transformada discreta de fourier. 
     * Recibe dos parámetros uno con la información y otro donde la escribirá.
     */
    static void calculateIDFT(const vector<complejo> & data , vector<complejo> & result)
    {
        calculate(data , result , "idft");
    }

};
