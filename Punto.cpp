#include "Punto.h"

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

Punto::Punto(int indice,int x, int y, int z){
    this->indice=indice;
    this->x=x;
    this->y=y;
    this->z=z;
/*     this->esta_en_objetos.clear();
    this->esta_en_caras.clear();
    this->esta_en_aristas.clear(); */
}


int Punto::get_x(){
    return x;

}

int Punto::get_y(){
    return y;
}

int Punto::get_z(){
    return z;
}
/* 
Objeto* Punto::get_esta_en_objetos(int indice){
    return esta_en_objetos[indice];

}

vector<Objeto*> Punto::get_esta_en_objetos(){
    return esta_en_objetos;
}

Linea* Punto::get_esta_en_aristas(int indice){
    return esta_en_aristas[indice];
}

vector<Linea*> Punto::get_esta_en_aristas(){
    return esta_en_aristas;
}

Plano* Punto::get_esta_en_caras(int indice){
    return esta_en_caras[indice];
}

vector<Plano*> Punto::get_esta_en_caras(){
    return esta_en_caras;
}

void Punto::anadirObjeto(Objeto* ptrObjeto){
    esta_en_objetos.push_back(ptrObjeto);
}

void Punto::anadirArista(Linea* ptrLinea){
    esta_en_aristas.push_back(ptrLinea);
}

void Punto::anadirCara(Plano* ptrPlano){
    esta_en_caras.push_back(ptrPlano);
} */