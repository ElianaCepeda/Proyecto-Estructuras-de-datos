#include "NodoKD.hxx"

template <class T>
NodoKD<T>::NodoKD() {
    hijoIzq = nullptr;
    hijoDer = nullptr;
}

template <class T>
NodoKD<T>::NodoKD(T val) {
    dato = val;
    hijoIzq = nullptr;
    hijoDer = nullptr;
}

template <class T>
NodoKD<T>::~NodoKD(){
    delete this->hijoDer;
    delete this->hijoIzq;
    this->hijoDer=nullptr;
    this->hijoIzq=nullptr;
}


template <class T>
bool NodoKD<T>::esHoja() {
    return (hijoIzq == nullptr && hijoDer == nullptr);
}

template <class T>
T NodoKD<T>::obtenerDato() {
    return dato;
}

template <class T>
void NodoKD<T>::fijarDato(T val) {
    dato = val;
}

template <class T>
NodoKD<T>* NodoKD<T>::obtenerHijoIzq() {
    return hijoIzq;
}

template <class T>
void NodoKD<T>::fijarHijoIzq(NodoKD<T>* izq) {
    hijoIzq = izq;
}

template <class T>
NodoKD<T>* NodoKD<T>::obtenerHijoDer() {
    return hijoDer;
}

template <class T>
void NodoKD<T>::fijarHijoDer(NodoKD<T>* der) {
    hijoDer = der;
}

template <class T>
void NodoKD<T>::preOrden(){
    std::cout<< * this->dato<<" ";

    if(this->hijoIzq != nullptr)
    this->hijoIzq->preOrden();

    if(this->hijoDer!= nullptr)
    this->hijoDer->preOrden();
}

template <class T>
void NodoKD<T>::posOrden(){
    if(this->hijoIzq!= nullptr)
    this->hijoIzq->posOrden();

    if(this->hijoDer!= nullptr)
    this->hijoDer->posOrden();

    std::cout<< * this->dato<<" ";
    
}

template <class T>
void NodoKD<T>::inOrden(){
    if(this->hijoIzq!= nullptr)
    this->hijoIzq->inOrden();

    std::cout<<  * this->dato<<" ";

    if(this->hijoDer!= nullptr)
    this->hijoDer->inOrden();
    
}