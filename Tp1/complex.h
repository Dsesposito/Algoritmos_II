#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>
#include <stdlib.h>

/**
 * Clase representativa de un número complejo. Posee algunas de las operaciones más 
 * comunes que se pueden llegar a necesitar para operar con numeros complejos.
 */
class complex {
    
    //Parte real del número complejo
    double re_;
    
    //Parte imaginaria del número complejo
    double im_;
    
public:
    /**
     * Constructor sin parámetros. Este constructor permite inicializar un 
     * complejo en (0,0).
     */
    complex();

    /**
     * Constructor. Este constructor permite crear un complejo a partir de 
     * un número real. La parte imaginaria queda inicializada en cero.
     */
    complex(double);

    /**
     * Constructor. Este constructor permite crear un complejo a partir de 
     * dos números reales. El primero corresponde a la parte real y el 
     * segundo a la parte imaginaria.
     */
    complex(double,double);

    /**
     * Constructor por copia. Construye un complejo a partir de la copiar de otro.
     */
    complex(const complex &);

    /**
     * Sobrecarga operador asignación. Asigna parte real a parte real
     * y parte imaginaría a parte imaginaría.
     */
    complex const &operator=(complex const &);

    /**
     * Destructor. Destructor para un numero complejo.
     */
    ~complex();

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
     * Setea al complejo como un numero al azar con:
	 * Re perteneciente al intervalo [from;to]
	 * Im perteneciente al intervalo [from;to]
     */
	complex complex::setRandom(double from, double to);


    /**
     * Distancia de un complejo a otro.
     */
	double complex::dist(complex const, complex);

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
    static complex fromPolarToRectangular(double,double);

    /**
     * Sobrecarga operador suma. Este método suma dos números complejos.
     */
    friend complex const operator+(complex const &, complex const &);

    /**
     * Sobrecarga operador resta. Este método resta dos números complejos.
     */
    friend complex const operator-(complex const &, complex const &);

    /**
     * Sobrecarga operador multiplicación. Este método multiplica dos
     * números complejos.
     */
    friend complex const operator*(complex const &, complex const &);

    /**
     * Sobrecarga operador división. Este método divide un complejo con 
     * un número real.
     */
    friend complex const operator/(complex const &, double);
    
    /**
     * Sobrecarga operador potenciación. Este método potencia un número
     * complejo con un numero entero.
     */
    friend complex const operator^(complex const &,int);

    /**
     * Sobrecarga operador igual. Este método compara la parte real de un 
     * un complejo con un numero real. Además verifica que la parte 
     * imaginaria del complejo sea cero.
     */
    friend bool operator==(complex const &, double);

    /**
     * Sobrecarga operador igual. Este método compara dos números complejos.
     * Parte real con parte real y parte imaginaria con parte imaginaria.
     */
    friend bool operator==(complex const &, complex const &);

    /**
     * Sobrecarga operador escritura. Este operador escribe un complejo
     * en formato (Re,Img) al flujo de salida.
     */
    friend std::ostream &operator<<(std::ostream &, const complex &);

    /**
     * Sobrecarga operador lectura. Este operador lee del flujo de entrada
     * un número complejo. Acepta números reales individuales a los cuales
     * se los toma como la parte real del numero complejo que retorna. 
     * En el caso de que reciba al numero complejo como par ordenado
     * devuelve un complejo con la parte real y la parte imaginaria
     * obtenida del flujo de entrada.
     */
    friend std::istream &operator>>(std::istream &, complex &);
};

using namespace std;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

complex::complex() : re_(0), im_(0) {}

complex::complex(double r) : re_(r), im_(0){}

complex::complex(double r, double i) : re_(r), im_(i){}

complex::complex(complex const &c) : re_(c.re_), im_(c.im_){}

complex const & complex::operator=(complex const &c){
    re_ = c.re_;
    im_ = c.im_;
    return *this;
}

complex::~complex() {}

double complex::re() const {
    return re_;
}

double complex::im() const {
    return im_;
}

double complex::abs() const {
    return std::sqrt(re_ * re_ + im_ * im_);
}

complex complex::setRandom(double from, double to)
{
	double re = fRand(from, to);
	double im = fRand(from, to);
	re_ = re;
	im_ = im;
	return complex(re, im);
}


double complex::dist(complex const x, complex const y)
{
	complex r = x-y;
	return r.abs();
}


double complex::phase() const {
    return atan(this->im_/this->re_);
}


complex complex::fromPolarToRectangular(double mod,double phase){
    double re = mod*cos(phase);
    double im = mod*sin(phase);
    return complex(re,im);
}

complex const operator+(complex const &x, complex const &y){
    complex z(x.re_ + y.re_, x.im_ + y.im_);
    return z;
}

complex const operator-(complex const &x, complex const &y){
    complex r(x.re_ - y.re_, x.im_ - y.im_);
    return r;
}

complex const operator*(complex const &x, complex const &y){
    complex r(x.re_ * y.re_ - x.im_ * y.im_,
              x.re_ * y.im_ + x.im_ * y.re_);
    return r;
}


complex const operator/(complex const &c, double f)
{
	return complex(c.re_ / f, c.im_ / f);
}

complex const operator^(complex const &c , int power){
    
    if(power == 0){
        return complex(1,0);
    }
    
    if(power == 1){
        return c;
    }
    
    double module = c.abs();
    double phase = c.phase();
    if(power < 0){
        module = 1/module;
    }

    for(int i = 0; i < power - 1 ; i++){
        module = module*module;
    }
    phase = phase*power;
    
    return complex::fromPolarToRectangular(module,phase);
}


bool operator== (complex const &c, double f){
    bool b = (c.im_ != 0 || c.re_ != f) ? false : true;
    return b;
}

bool operator== (complex const &x, complex const &y){
    bool b = (x.re_ != y.re_ || x.im_ != y.im_) ? false : true;
    return b;
}

ostream & operator<<(ostream &os, const complex &c){
    //double reAux = ((int)(c.re_*100))/100.0;
    //double imAux = ((int)(c.im_*100))/100.0;
    return os << "(" << c.re_ << "," << c.im_ << ")";
}

istream & operator>>(istream &is, complex &c) {
    int good = false;
    int bad  = false;
    double re = 0;
    double im = 0;
    char ch = 0;

    if (is >> ch && ch == '(') {
        if (is >> re && is >> ch && ch == ',' && is >> im && is >> ch
            && ch == ')')
                good = true;
        else
                bad = true;
    } else if (is.good()) {
        is.putback(ch);
        if (is >> re)
                good = true;
        else
                bad = true;
    }

    if (good)
        c.re_ = re, c.im_ = im;
    if (bad)
        is.clear(ios::badbit);

    return is;
}


#endif
