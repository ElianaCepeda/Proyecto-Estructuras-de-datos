
#ifndef ARBOLKD_H
#define ARBOLKD_H
#include "NodoKD.hxx"
#include "Punto.h"

template <class T>

class ArbolKD {
protected:
    NodoKD<T>* raiz;
public:
    ArbolKD();
    ArbolKD(T dato);
    ~ArbolKD();
    T datoRaiz();
    NodoKD<T>* obtenerRaiz();
    void fijarRaiz(NodoKD<T>* n_raiz);
    bool esVacio();
    void insertar(T dato);
    T buscarNodoInsercion(T dato);
    void preOrden();
    void inOrden();
    void posOrden();
    void nivelOrden();
};

#include "ArbolKD3d.cxx"
#endif //ARBOLKD_HXX
