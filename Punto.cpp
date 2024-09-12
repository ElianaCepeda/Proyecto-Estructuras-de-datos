#include "Punto.h"

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

Punto::Punto(int indice,double x, double y, double z){
    this->indice=indice;
    this->x=x;
    this->y=y;
    this->z=z;
/*     this->esta_en_objetos.clear();
    this->esta_en_caras.clear();
    this->esta_en_aristas.clear(); */
}

int Punto::get_indice(){
    return indice;
}

double Punto::get_x(){
    return x;

}

double Punto::get_y(){
    return y;
}

double Punto::get_z(){
    return z;
}

bool Punto::equals(Punto punto){
    bool respuesta=false;
    if(this->indice==punto.indice)
    respuesta=true;

    return respuesta;
}

bool Punto::coordenadas_iguales(double x, double y, double z){
    bool respuesta =false;
    if(this->x==x && this->y==y && this->z==z)
    respuesta=true;

    return respuesta;
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