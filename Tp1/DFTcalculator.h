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
    static void bruteForceAlgorithm(const vector<complejo> & data , vector<complejo> & result , string algorithm){
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

    static void FFTAlgorithm(const vector<complejo> & data , vector<complejo> & result , vector<int> & indexes){

        // Si todavía no llegué al caso base llamo recursivamente
        if(indexes.length() != 1){
            //Creo dos vectores de índices, estos vectores me sirven para no tener que 
            //crear vectores de data nuevos para las llamadas recursivas
            //sino que utilizo el mismo vector data y el vector de índice
            //para obtener el dato que necesito en el caso base.
            //Vector de índices pares
            vector<int> evenIndexes = vector<int>();
            //Vector de índices impares
            vector<int> oddIndexes = vector<int>();
            //Guardo los índices pares e impares en los respectivos vectores
            for(int i = 0 ; i < indexes.length() ; i = i + 2){
                evenIndexes.pushBack(indexes[i]);
                if(i+1 < indexes.length()){
                    oddIndexes.pushBack(indexes[i+1]);
                }
            }
            //Creo dos vectores que almacenarán los resultados de las transformadas
            //de los índices pares e impares.
            vector<complejo> evenResult = vector<complejo>();
            vector<complejo> oddResult = vector<complejo>();
            //Llamo recursivamente para calcular la DFT sobre la sub secuencia
            FFTAlgorithm(data,evenResult,evenIndexes);
            FFTAlgorithm(data,oddResult,oddIndexes);
            //Uno la DFT de ambas sub secuencias
            int N = evenResult.length() + oddResult.length();
            for(int i = 0 ; i < N ; i++){
                double re = cos(2*M_PI*i/N);
                double im = sin(2*M_PI*i/N);
                complejo W(re,im);
                complejo Xk = W*oddResult.getCircular(i) + evenResult.getCircular(i);
                result.pushBack(Xk);
            }    
        }
        else{
            //Obtengo el dato que necesito a partir del vector de índices
            int dataIndex = indexes[0];
            complejo dataComplex = data[dataIndex];
            result.pushBack(dataComplex);
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
        bruteForceAlgorithm(data , result , "dft");
    }

    /**
     * Método el cual permite calcular la anti-transformada discreta de fourier. 
     * Recibe dos parámetros uno con la información y otro donde la escribirá.
     */
    static void calculateIDFT(const vector<complejo> & data , vector<complejo> & result)
    {
        bruteForceAlgorithm(data , result , "idft");
    }
    
    static void calculateFFT(const vector<complejo> & data , vector<complejo> & result){
        vector<int> initIndexes = vector<int>();
        for(int i = 0 ; i < data.length() ; i++){
            initIndexes.pushBack(i);
        }
        FFTAlgorithm(data,result,initIndexes);
    }

};
