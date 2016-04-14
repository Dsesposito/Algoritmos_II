

/* 
 * File:   vector.h
 * Author: Diego / Marcelo
 *
 * Created on March 21, 2016, 8:56 PM
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;


/**
 * Clase vector. Permite almacenar un arreglo de datos. Contiene una serie de 
 * de métodos que permiten agregar, quitar y leer los distintos elementos almacenados
 * en el vector. Además la clase esta templetizada, permitiendo así crear vectores
 * de cualquier tipo.
 */
template <class T>
class vector{
    
    private:
        //Tamaño del vector
        int size;
        //Cantidad de espacio en memoria del vector
        int capacity;
        //Puntero a la primera posición del vector
        T* pv;
        
    public:
        
        /**
         * Constructor sin parámetros. Inicializa un vector en cero. Además no
         * crea la memoria para el vector.
         */
        vector(){
            this->pv = NULL;
            this->size = 0;
            this->capacity = 0;
        }

        /**
         * Constructor. Inicializa un vector vacío. A diferencia del constructor
         * sin parámetros, este crea la memoria para el vector de acuerdo al
         * parámetro size_. 
         */
        vector(int size_){
            this->pv = new T[size_];
            this->size = size_;
            this->capacity = size_;
        }

        /**
         * Constructor copia. Inicializa un vector a partir de otro pasado
         * por parámetro.
         */
        vector(const vector<T> & cv){
            this->size = cv.size ;
            this->capacity = cv.capacity;
            T* cp = new T[ size ];
            for ( int i = 0; i < this->size; i++ ){
                cp[ i ] = cv.pv[ i ];
            }
            if(this->pv){
                delete[] this->pv;
            }
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
                this->capacity = 2;
            }
            else{
                if(this->capacity == this->size){
                    T* aux = this->pv;
                    this->pv = new T[this->capacity*2];
                    this->capacity = this->capacity*2;
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


        /**
         * Operador comparación. Compara el contenido del vector pasado por
         * parámetro con el vector sobre el cual se ejecuto el operador. En el
         * caso que todos los elementos coincidan devuelve true. 
         */
        bool operator==(const vector<T> & rigth) const {
            if (this->size != rigth.size)
                return false; // Vectores de diferentes tamaños
            else
                for (int i = 0; i < this->size; i++)
                    if (this->pv[ i ] != rigth.pv[ i ])
                        return false;
            return true; 
        }

        /**
         * Operador indexación constante. Permite obtener el objeto almacenado en una
         * determinada posición del vector.
         */
        const T & operator[](int index) const {
            if(index >= this->size){
                cerr << "Indice incorrecto en const operator[]" << endl;
                abort();
            }
            return this->pv[index];
        }
        
        /**
         * Operador indexación. Permite asignarle un valor a una determinada
         * posición del vector.
         */
        T & operator[](int index) {
            if(index >= this->size){
                cout << "Indice incorrecto en operator[]" << endl;
                abort();
            }
            return this->pv[index];
        }
        
        /**
         * Operador lectura. Permite leer de un stream de entrada un conjunto
         * de objetos del tipo T, almacenándolos en un vector.
         */
        friend std::istream &operator>>(std::istream & is,vector<T> & vector){
            T aux;
            for(int i = 0 ; is >> aux ; i++){
                vector.pushBack(aux);
            }
            return is;
        }

        /**
         * Operador escritura. Permite escribir en un stream de salida el vector
         * del cual se llamo.
         */
        friend std::ostream &operator<<(std::ostream & os, const vector<T> & vector){
            for(int i = 0 ; i < vector.size ; i++){
                os << vector[i] << endl;
            }
            return os;
        }
};


#endif /* VECTOR_H */

