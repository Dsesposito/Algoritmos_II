/* 
 * File:   DFTcalculator.cc
 * Author: Diego / Marcelo
 *
 * Created on March 21, 2016, 8:09 PM
 */

#include <cstdlib>
#include "vector.h"
#include "complex.h"
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
    static void bruteForceAlgorithm(const vector<complex> & data , vector<complex> & result , string algorithm){
        int N = data.length();
        int sign = 1;
        if(algorithm == "idft"){
            sign = -1;
        }
        for(int i = 0 ; i < N ; i++){
            complex sum = 0;
            for(int j = 0 ; j < N ; j++){
                double re = cos(2*M_PI*j*i*sign/N);
                double im = sin(2*M_PI*j*i*sign/N);
                complex W = complex(re,im);
                sum = sum + (data[j]*W);
            }
            if(algorithm == "idft"){
                sum = sum / N;
            }
            result.pushBack(sum);
        }
    } 

    static void FFTAlgorithm(const vector<complex>& data , vector<complex>& result , vector<int>& indexes, string algorithm){

        int sign = 1;
        if(algorithm == "ifft"){
            sign = -1;
        }
        
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
                oddIndexes.pushBack(indexes[i+1]);
                
            }
            //Creo dos vectores que almacenarán los resultados de las transformadas
            //de los índices pares e impares.
            vector<complex> evenResult = vector<complex>();
            vector<complex> oddResult = vector<complex>();
            //Llamo recursivamente para calcular la DFT sobre la sub secuencia
            FFTAlgorithm(data,evenResult,evenIndexes,algorithm);
            FFTAlgorithm(data,oddResult,oddIndexes,algorithm);
            //Uno la DFT de ambas sub secuencias
            int N = evenResult.length() + oddResult.length();
            for(int i = 0 ; i < N ; i++){
                double re = cos(sign*2*M_PI*i/N);
                double im = sin(sign*2*M_PI*i/N);
                complex W(re,im);
                complex Xk = W*oddResult.getCircular(i) + evenResult.getCircular(i);
                result.pushBack(Xk);
            }    
        }
        else{
            //Obtengo el dato que necesito a partir del vector de índices
            int dataIndex = indexes[0];
            complex dataComplex = data[dataIndex];
            result.pushBack(dataComplex);
        }
        
        //CUando terminan todas las llamadas recursivas, si era idft divido por N
        if(algorithm == "ifft" && result.length() == data.length()){
            result = result/result.length();
        }
    }  

    static void fillMinPower2(vector<complex>& data){
        //Si el largo no es potencia de 2 completo con ceros
        int dataLength = data.length();

		double l1 = log((double) dataLength);
		double base = 2;
		double l2 = log(base);

        if(dataLength & (dataLength - 1)){
            int nearest = pow(2, ceil( l1 / l2 ) );
            for(int i = dataLength ; i < nearest ; i++){
                complex complexZero = complex();
                data.pushBack(complexZero);   
            }
        }
    }
    


	public:

		/**
     * Método el cual permite calcular la transformada discreta de fourier. Recibe
     * por parámetro dos vectores uno con la información y otro donde escribirá
     * el resultado.
     */
    static void calculateDFT(const vector<complex>& data , vector<complex>& result)
    {
        bruteForceAlgorithm(data , result , "dft");
    }

    /**
     * Método el cual permite calcular la anti-transformada discreta de fourier. 
     * Recibe dos parámetros uno con la información y otro donde la escribirá.
     */
    static void calculateiDFT(const vector<complex>& data , vector<complex>& result)
    {
        bruteForceAlgorithm(data , result , "idft");
    }
    
    
    static void calculateFFT(vector<complex>& data , vector<complex>& result){
        DFTcalculator::fillMinPower2(data);
        vector<int> initIndexes = vector<int>();
        for(int i = 0 ; i < data.length() ; i++){
            initIndexes.pushBack(i);
        }
        FFTAlgorithm(data,result,initIndexes,"fft");
    }
    
        
    static void calculateiFFT(vector<complex>& data , vector<complex>& result){
        DFTcalculator::fillMinPower2(data);
        vector<int> initIndexes = vector<int>();
        for(int i = 0 ; i < data.length() ; i++){
            initIndexes.pushBack(i);
        }
        FFTAlgorithm(data,result,initIndexes,"ifft");
    }

};
