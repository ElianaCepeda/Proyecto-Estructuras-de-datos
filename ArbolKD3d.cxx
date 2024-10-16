#include "ArbolKD3d.hxx"
#include "Punto.h"
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template <class T>
ArbolKD3d<T>::ArbolKD3d() {
    raiz = nullptr;
}

template <class T>
ArbolKD3d<T>::ArbolKD3d(T dato) {
    raiz = new NodoKD<T>(dato);
}

template <class T>
ArbolKD3d<T>::~ArbolKD3d() {
    delete this->raiz;
    this->raiz=nullptr;
}


template <class T>
NodoKD<T>* ArbolKD3d<T>::obtenerRaiz() {
    return raiz;
}

template <class T>
void ArbolKD3d<T>::fijarRaiz(NodoKD<T>* n_raiz) {
    raiz = n_raiz;
}


template <class T>
bool ArbolKD3d<T>::esVacio() {
    return (raiz == nullptr);
}

template <class T>
void ArbolKD3d<T>::insertar(T val) {
    bool insertado=false;

    if (esVacio()) {
        raiz = new NodoKD<T>(val);
        insertado=true;
    }

    NodoKD<T>* actual = raiz;
    int profundidad = 0;

    while (!insertado) {
        if (actual->obtenerDato() == val) {
            // El punto ya ha sido insertado
            insertado=true;
        }else{
            // Alternar entre las dimensiones: 0 (x), 1 (y), 2 (z)
            int dimension = profundidad % 3;

            switch (dimension){

            case 0:
                
                if (val->get_x() <= actual->obtenerDato()->get_x()) {
                    if (actual->obtenerHijoIzq() == nullptr) {
                        actual->fijarHijoIzq(new NodoKD<T>(val));
                        insertado=true;
                    } else {
                        actual = actual->obtenerHijoIzq();
                    }
                } else {
                    if (actual->obtenerHijoDer() == nullptr) {
                        actual->fijarHijoDer(new NodoKD<T>(val));
                        insertado=true;
                    } else {
                        actual = actual->obtenerHijoDer();
                    }
                }
            
                break;

            case 1:

                if (val->get_y() <= actual->obtenerDato()->get_y()) {
                    if (actual->obtenerHijoIzq() == nullptr) {
                        actual->fijarHijoIzq(new NodoKD<T>(val));
                        insertado=true;
                    } else {
                        actual = actual->obtenerHijoIzq();
                    }
                } else {
                    if (actual->obtenerHijoDer() == nullptr) {
                        actual->fijarHijoDer(new NodoKD<T>(val));
                        insertado=true;
                    } else {
                        actual = actual->obtenerHijoDer();
                    }
                }

                break;

            case 2:

                if (val->get_z() <= actual->obtenerDato()->get_z()) {
                    if (actual->obtenerHijoIzq() == nullptr) {
                        actual->fijarHijoIzq(new NodoKD<T>(val));
                        insertado=true;
                    } else {
                        actual = actual->obtenerHijoIzq();
                    }
                } else {
                    if (actual->obtenerHijoDer() == nullptr) {
                        actual->fijarHijoDer(new NodoKD<T>(val));
                        insertado=true;
                    } else {
                        actual = actual->obtenerHijoDer();
                    }
                }
            
                break;
            
            
            default:
                break;


            
            }

            profundidad++;
        }

        

    }
}


template <class T>
T ArbolKD3d<T>::buscarNodoInsercion(T val){
    bool NodoEncontrado=false;
    T datoCercano;

    if (this->esVacio()) {
        NodoEncontrado=true;
    }

    NodoKD<T>* actual = raiz;
    int profundidad = 0;

    while (!NodoEncontrado) {

        if (*actual->obtenerDato() == *val) {
            NodoEncontrado=true;
            datoCercano=actual->obtenerDato();
        }else{
            // Alternar entre las dimensiones: 0 (x), 1 (y), 2 (z)
            int dimension = profundidad % 3;

            switch (dimension){

            case 0:
                
                if (val->get_x() <= actual->obtenerDato()->get_x()) {
                    if (actual->obtenerHijoIzq() == nullptr) {
                        datoCercano=actual->obtenerDato();
                        NodoEncontrado=true;
                    } else {
                        actual = actual->obtenerHijoIzq();
                    }
                } else {
                    if (actual->obtenerHijoDer() == nullptr) {
                        datoCercano=actual->obtenerDato();
                        NodoEncontrado=true;
                    } else {
                        actual = actual->obtenerHijoDer();
                    }
                }
            
                break;

            case 1:

                if (val->get_y() <= actual->obtenerDato()->get_y()) {
                    if (actual->obtenerHijoIzq() == nullptr) {
                        datoCercano=actual->obtenerDato();
                        NodoEncontrado=true;
                    } else {
                        actual = actual->obtenerHijoIzq();
                    }
                } else {
                    if (actual->obtenerHijoDer() == nullptr) {
                        datoCercano=actual->obtenerDato();
                        NodoEncontrado=true;
                    } else {
                        actual = actual->obtenerHijoDer();
                    }
                }

                break;

            case 2:

                if (val->get_z() <= actual->obtenerDato()->get_z()) {
                    if (actual->obtenerHijoIzq() == nullptr) {
                        datoCercano=actual->obtenerDato();
                        NodoEncontrado=true;
                    } else {
                        actual = actual->obtenerHijoIzq();
                    }
                } else {
                    if (actual->obtenerHijoDer() == nullptr) {
                        datoCercano=actual->obtenerDato();
                        NodoEncontrado=true;
                    } else {
                        actual = actual->obtenerHijoDer();
                    }
                }
            
                break;
            
            
            default:
                break;


            
            }

            profundidad++;
        }

    }

    return datoCercano;
}

template <class T>
void ArbolKD3d<T>::preOrden() {
    if (!this->esVacio())
    raiz->preOrden();
    std::cout<<"\n";
}


template <class T>
void ArbolKD3d<T>::posOrden() {
    if (!this->esVacio())
    raiz->posOrden();
    std::cout<<"\n";
}

template <class T>
void ArbolKD3d<T>::inOrden() {
    if (!this->esVacio())
    raiz->inOrden();
    std::cout<<"\n";
}

template <class T>
void ArbolKD3d<T>::nivelOrden() {
    if (raiz == nullptr) return;

    typename std::queue<NodoKD<T> *> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        NodoKD<T>* actual = cola.front();
        cola.pop();


        cout << actual->obtenerDato()<< " ";


        if (actual->obtenerHijoIzq()) cola.push(actual->obtenerHijoIzq());
        if (actual->obtenerHijoDer()) cola.push(actual->obtenerHijoDer());
    }
}
