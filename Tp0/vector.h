

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
        int memSize;
        T* pv;
        
    public:
        
        /**
         * Constructor sin parametros. Inicializa un vector en cero. Ademas no
         * crea la memoria para el vector.
         */
        vector(){
            this->pv = NULL;
            this->size = 0;
            this->memSize = 0;
        }

        /**
         * Constructor. Inicializa un vector vacio. A diferencia del constructor
         * sin parametros, este crea la memoria para el vector de acuerdo al
         * parametro size_. 
         */
        vector(int size_){
            this->pv = new T[size_];
            this->size = size_;
            this->memSize = size_;
        }

        /**
         * Constructor copia. Inicializa un vector a partir de otro pasado
         * por parámetro.
         */
        vector(const vector<T> & cv){
            this->size = cv.size ;
            this->memSize = cv.memSize;
            T* cp = new T[ size ];
            for ( int i = 0; i < this->size; i++ ){
                cp[ i ] = cv.pv[ i ];
            }
            delete[] this->pv;
            this->pv = cp;
        }

        /**
         * Destructor de vector. borra la memoria creada para el vector.
         */
        ~vector(){
            if(this->pv){
                delete [] this->pv;
            }
        }

        /**
         * Largo del vector. Este método devuelve el largo del vector.
         */
        int length() const{
            return this->size;
        }

        /**
         * Inserta un elemento al vector. Este método inserta al final del vector 
         * un elemento. Para agregar el elemento primero verifica que tenga
         * memoria, en caso de no tener crea memoria con capacidad igual al
         * doble de la que tenía.
         */
        void pushBack(T & elem){
            if(this->size == 0){
                this->pv = new T[2];
                this->memSize = 2;
            }
            else{
                if(this->memSize == this->size){
                    T* aux = this->pv;
                    this->pv = new T[this->memSize*2];
                    this->memSize = this->memSize*2;
                    for(int i = 0 ; i < this->size ; i++){
                        this->pv[i] = aux[i];
                    }
                    delete[] aux;
                }
            }
            this->pv[this->size] = elem;
            this->size++;
        }
        
        /**
         * Operador asignación. Este operador copia los elementos del vector
         * pasado por parámetro al objeto sobre el cual se ejecuto.
         */
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


        const T & operator[](int index) const {
            if(index >= this->size){
                cerr << "Indice incorrecto en const operator[]" << endl;
                abort();
            }
            return this->pv[index];
        }
        
        T & operator[](int index) {
            if(index >= this->size){
                cout << "Indice incorrecto en operator[]" << endl;
                abort();
            }
            return this->pv[index];
        }
        
        friend std::istream &operator>>(std::istream & is,vector<T> & vector){
            T aux;
            for(int i = 0 ; is >> aux ; i++){
                vector.pushBack(aux);
            }
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

