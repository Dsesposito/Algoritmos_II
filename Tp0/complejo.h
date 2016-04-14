#ifndef COMPLEJO_H
#define COMPLEJO_H

#include <iostream>
/**
 * Clase representativa de un número complejo. Posee algunas de las operaciones más 
 * comunes que se pueden llegar a necesitar para operar con numeros complejos.
 */
class complejo {
    
    //Parte real del número complejo
    double re_;
    
    //Parte imaginaria del número complejo
    double im_;
    
public:
    /**
     * Constructor sin parámetros. Este constructor permite inicializar un 
     * complejo en (0,0).
     */
    complejo();

    /**
     * Constructor. Este constructor permite crear un complejo a partir de 
     * un número real. La parte imaginaria queda inicializada en cero.
     */
    complejo(double);

    /**
     * Constructor. Este constructor permite crear un complejo a partir de 
     * dos números reales. El primero corresponde a la parte real y el 
     * segundo a la parte imaginaria.
     */
    complejo(double,double);

    /**
     * Constructor por copia. Construye un complejo a partir de la copiar de otro.
     */
    complejo(const complejo &);

    /**
     * Sobrecarga operador asignación. Asigna parte real a parte real
     * y parte imaginaría a parte imaginaría.
     */
    complejo const &operator=(complejo const &);

    /**
     * Destructor. Destructor para un numero complejo.
     */
    ~complejo();

    /**
     * Parte real de un complejo. Este método devuelve la parte real de
     * un número complejo
     */
    double re() const;

    /**
     * Parte imaginaria de un complejo. Este método devuelve la parte 
     * imaginaria de un número complejo.
     */
    double im() const;

    /**
     * Módulo de un número complejo. Este método devuelve el modulo de
     * un complejo.
     */
    double abs() const;

    /**
     * Fase de un número complejo. Este método devuelve la fase de un número
     * complejo.
     */
    double phase() const;

    /**
     * Conversor de complejo de forma polar a forma cartesiana. Este método
     * recibe por parámetro el modulo y la fase de un complejo y retorna
     * un número complejo en su forma cartesiana.
     */
    static complejo fromPolarToRectangular(double,double);

    /**
     * Sobrecarga operador suma. Este método suma dos números complejos.
     */
    friend complejo const operator+(complejo const &, complejo const &);

    /**
     * Sobrecarga operador resta. Este método resta dos números complejos.
     */
    friend complejo const operator-(complejo const &, complejo const &);

    /**
     * Sobrecarga operador multiplicación. Este método multiplica dos
     * números complejos.
     */
    friend complejo const operator*(complejo const &, complejo const &);

    /**
     * Sobrecarga operador división. Este método divide un complejo con 
     * un número real.
     */
    friend complejo const operator/(complejo const &, double);
    
    /**
     * Sobrecarga operador potenciación. Este método potencia un número
     * complejo con un numero entero.
     */
    friend complejo const operator^(complejo const &,int);

    /**
     * Sobrecarga operador igual. Este método compara la parte real de un 
     * un complejo con un numero real. Además verifica que la parte 
     * imaginaria del complejo sea cero.
     */
    friend bool operator==(complejo const &, double);

    /**
     * Sobrecarga operador igual. Este método compara dos números complejos.
     * Parte real con parte real y parte imaginaria con parte imaginaria.
     */
    friend bool operator==(complejo const &, complejo const &);

    /**
     * Sobrecarga operador escritura. Este operador escribe un complejo
     * en formato (Re,Img) al flujo de salida.
     */
    friend std::ostream &operator<<(std::ostream &, const complejo &);

    /**
     * Sobrecarga operador lectura. Este operador lee del flujo de entrada
     * un número complejo. Acepta números reales individuales a los cuales
     * se los toma como la parte real del numero complejo que retorna. 
     * En el caso de que reciba al numero complejo como par ordenado
     * devuelve un complejo con la parte real y la parte imaginaria
     * obtenida del flujo de entrada.
     */
    friend std::istream &operator>>(std::istream &, complejo &);
};

#endif
