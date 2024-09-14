#include "Linea.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

Linea::Linea(int indice, Punto* vertice1, Punto* vertice2){
    this->indice=indice;
    this->vertice1=vertice1;
    this->vertice2=vertice2;
    this->calcular_distancia();
/*     this->esta_en_objetos.clear();
    this->esta_en_caras.clear();
 */}

 Linea::~Linea(){
    /* delete vertice1;
    delete vertice2;  */
    cout<<"Linea destruida"<<endl;
 }

int Linea::get_indice(){
    return indice;

}

Punto* Linea::get_vertice1(){
    return vertice1;

}

Punto* Linea::get_vertice2(){
    return vertice2;
}

double Linea::get_distancia(){
    return distancia;
}

bool Linea::equals(Linea linea){
    bool respuesta=false;
    if(this->indice==linea.indice)
    respuesta=true;

    return respuesta;
}

bool Linea::vertices_iguales(Punto vertice1, Punto vertice2){
    bool respuesta=false;

    if((this->vertice1->get_indice()==vertice1.get_indice() && this->vertice2->get_indice()==vertice2.get_indice())|| (this->vertice1->get_indice()==vertice2.get_indice() && this->vertice2->get_indice()==vertice1.get_indice()))
        respuesta =true;

    return respuesta;
}

/* Objeto* Linea::get_esta_en_objetos(int indice){
    return esta_en_objetos[indice];

}

vector<Objeto*> Linea::get_esta_en_objetos(){
    return esta_en_objetos;
}

Plano* Linea::get_esta_en_caras(int indice){
    return esta_en_caras[indice];
}

vector<Plano*> Linea::get_esta_en_caras(){
    return esta_en_caras;
}
 */
void Linea::calcular_distancia(){
    distancia= sqrt(pow(this->vertice1->get_x()- this->vertice2->get_x(),2)+pow(this->vertice1->get_y()- this->vertice2->get_y(),2)+pow(this->vertice1->get_z()- this->vertice2->get_z(),2));

}