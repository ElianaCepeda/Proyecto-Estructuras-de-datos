#include "Plano.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;


Plano::Plano(int indice, vector<Linea *> aristas, vector<Punto *> vertices){
    this->indice=indice;
    this->aristas=aristas;
    this->vertices=vertices;
    //this->esta_en_objetos.clear();
}

Plano::~Plano(){
    /* aristas.clear();
    vertices.clear(); */
    cout<<"Plano destruido"<<endl;
}

int Plano::get_idice(){
    return indice;

}

vector<Linea *> Plano::get_aristas(){
    return aristas;
}

Linea* Plano::get_aristas(int indice){
    return aristas[indice];
}

vector<Punto *> Plano::get_vertices(){
    return vertices;
}

Punto* Plano::get_vertices(int indice){
    return vertices[indice];
}

bool Plano::equals(Plano plano){
    bool respuesta=false;
    if(this->indice==plano.indice)
    respuesta=true;

    return true;
}

bool Plano::aristas_iguales(vector< Linea*> aristas){
    bool respuesta=false;
    if(this->aristas==aristas)
    respuesta=true;

    return respuesta;
}

/* void Plano::anadir_Objeto(Objeto* objeto){
    esta_en_objetos.push_back(objeto)
} */
