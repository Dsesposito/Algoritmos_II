

/* 
 * File:   vector.h
 * Author: diego
 *
 * Created on March 21, 2016, 8:56 PM
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

template <class T>
class vector{
    
    private:
        
        int size;
        T* pv;
        
    public:
        
        vector(){
    
        }

        vector(int size_){
            this->pv = new T[size_];
            this->size = size_;
        }

        vector(const vector<T> & cv){
            this->size = cv.size ;
            this->pv = new T[ size ];
            for ( int i = 0; i < this->size; i++ ){
                this->pv[ i ] = cv.pv[ i ];
            }
        }

        ~vector(){
            if(this->pv){
                delete [] this->pv;
            }
        }

        int length() const{
            return this->size;
        }

        vector<T> & operator=(const vector<T> & rigth) {
            if (&rigth != this) 
            { 
                if (this->size != rigth.size) {
                    T * aux; 
                    aux = new T[ rigth.size ];
                    delete [] this->pv; 
                    this->size = rigth.size; 
                    this->pv = aux; 
                    for (int i = 0; i < size; i++){
                        this->pv[i] = rigth.pv[i];
                    }
                    return *this;
                } 
                else 
                {
                    for (int i = 0; i < this->size; i++){
                        this->pv[i] = rigth.pv[i];    
                    }
                    return *this;
                }
            }
            return *this;
        }



        bool operator==(const vector<T> & rigth) const {
            if (this->size != rigth.size)
                return false; // Vectores de diferentes tamaños
            else
                for (int i = 0; i < this->size; i++)
                    if (this->pv[ i ] != rigth.pv[ i ])
                        return false;
            return true; 
        }


        const T & operator[](int subscript) const {
            return this->pv[subscript];
        }
        
        T & operator[](int subscript) {
            return this->pv[subscript];
        }
        
        friend std::istream &operator>>(std::istream & is,vector<T> & vector){
            for(int i = 0 ; is >> vector[i] ; i++);
            return is;
        }

        friend std::ostream &operator<<(std::ostream & os, const vector<T> & vector){
            for(int i = 0 ; i < vector.size ; i++){
                os << vector[i] << endl;
            }
            return os;
        }
};


#endif /* VECTOR_H */

