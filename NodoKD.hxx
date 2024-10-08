
#ifndef NODOKD_HXX
#define NODOKD_HXX
#include <iostream>
#include <ostream>


template <class T>
class NodoKD {
protected:
    T dato;
    NodoKD* hijoIzq;
    NodoKD* hijoDer;
public:
    NodoKD();
    NodoKD(T val);
    ~NodoKD();
    bool esHoja();
    T obtenerDato();
    void fijarDato(T val);
    NodoKD* obtenerHijoIzq();
    NodoKD* obtenerHijoDer();
    void fijarHijoIzq(NodoKD* izq);
    void fijarHijoDer(NodoKD* der);
    void preOrden();
    void posOrden();
    void inOrden();
};

#include "NodoKD.cxx"
#endif //NODOKD_HXX


