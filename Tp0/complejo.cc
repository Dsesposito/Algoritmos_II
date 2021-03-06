#include "complejo.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

complejo::complejo() : re_(0), im_(0) {}

complejo::complejo(double r) : re_(r), im_(0){}

complejo::complejo(double r, double i) : re_(r), im_(i){}

complejo::complejo(complejo const &c) : re_(c.re_), im_(c.im_){}

complejo const & complejo::operator=(complejo const &c){
    re_ = c.re_;
    im_ = c.im_;
    return *this;
}

complejo::~complejo() {}

double complejo::re() const {
    return re_;
}

double complejo::im() const {
    return im_;
}

double complejo::abs() const {
    return std::sqrt(re_ * re_ + im_ * im_);
}


double complejo::phase() const {
    return atan(this->im_/this->re_);
}


complejo complejo::fromPolarToRectangular(double mod,double phase){
    double re = mod*cos(phase);
    double im = mod*sin(phase);
    return complejo(re,im);
}

complejo const operator+(complejo const &x, complejo const &y){
    complejo z(x.re_ + y.re_, x.im_ + y.im_);
    return z;
}

complejo const operator-(complejo const &x, complejo const &y){
    complejo r(x.re_ - y.re_, x.im_ - y.im_);
    return r;
}

complejo const operator*(complejo const &x, complejo const &y){
    complejo r(x.re_ * y.re_ - x.im_ * y.im_,
              x.re_ * y.im_ + x.im_ * y.re_);
    return r;
}


complejo const operator/(complejo const &c, double f)
{
	return complejo(c.re_ / f, c.im_ / f);
}

complejo const operator^(complejo const &c , int power){
    
    if(power == 0){
        return complejo(1,0);
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
    
    return complejo::fromPolarToRectangular(module,phase);
}


bool operator== (complejo const &c, double f){
    bool b = (c.im_ != 0 || c.re_ != f) ? false : true;
    return b;
}

bool operator== (complejo const &x, complejo const &y){
    bool b = (x.re_ != y.re_ || x.im_ != y.im_) ? false : true;
    return b;
}

ostream & operator<<(ostream &os, const complejo &c){
    double reAux = ((int)(c.re_*100))/100.0;
    double imAux = ((int)(c.im_*100))/100.0;
    return os << "(" << reAux << "," << imAux << ")";
}

istream & operator>>(istream &is, complejo &c) {
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
