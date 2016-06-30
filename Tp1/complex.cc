#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "complex.h"

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
    double re = 0;
    double im = 0;
    char ch = 0;

    if (is >> ch && ch == '(') {
        if (is >> re && is >> ch && ch == ',' && is >> im && is >> ch
            && ch == ')')
            good = true;
        else
            good = false;
    } else if (is.good()) {
        is.putback(ch);
        if (is >> re)
            good = true;
        else
            good = false;
    }

    if (good){
        c.re_ = re, c.im_ = im;   
        is.clear(ios::goodbit);
    }
    else if(ch == '\0'){
        is.clear(ios::eofbit);
    }
    else
    {
        is.clear(ios::badbit);
    }

    return is;
}
