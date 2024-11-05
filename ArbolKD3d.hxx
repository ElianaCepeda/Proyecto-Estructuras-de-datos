
#ifndef ARBOLKD_H
#define ARBOLKD_H
#include "NodoKD.cxx"
#include "Punto.h"

template <class T>

class ArbolKD3d {
protected:
    NodoKD<T>* raiz;
public:
    ArbolKD3d();
    ArbolKD3d(T dato);
    ~ArbolKD3d();
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

//#include "ArbolKD3d.cxx"
#endif //ARBOLKD_HXX
