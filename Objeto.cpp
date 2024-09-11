#include "Objeto.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

Objeto::Objeto(int indice, string nombre, vector<Punto *> vertices, vector<Linea *> aristas, vector<Plano *> caras){
    this->indice=indice;
    this->nombre=nombre;
    this->vertices=vertices;
    this->aristas=aristas;
    this->caras=caras;
    this->envolvente=NULL;
}

int Objeto::get_indice(){
    return indice;
}

string Objeto::get_nombre(){
    return nombre;
}

vector<Punto *> Objeto::get_vertices(){
    return vertices;
}

Punto* Objeto::get_vertices(int indice){
    return vertices[indice];
}

vector<Linea *> Objeto::get_aristas(){
    return aristas;
}

Linea* Objeto::get_aristas(int indice){
    return aristas[indice];
}

vector<Plano *> Objeto::get_caras(){
    return caras;
}

Plano* Objeto::get_caras(int indice){
    return caras[indice];
}

Objeto* Objeto::get_envolvente(){
    return envolvente;
}

void Objeto::set_envolvente(Objeto* envolvente){
    this->envolvente=envolvente;
}


int Objeto::calcular_minimo(char coordenada){
    int minimo=0;
    switch (coordenada)
    {
    case 'x':
        minimo= vertices[0]->get_x();
        for(int i=1; i<vertices.size(); i++){
            if(vertices[i]->get_x()<minimo)
            minimo=vertices[i]->get_x();
        }
        break;
    case 'y':
        minimo= vertices[0]->get_y();
        for(int i=1; i<vertices.size(); i++){
            if(vertices[i]->get_y()<minimo)
            minimo=vertices[i]->get_y();
        }
        break;
    
    case 'z':
        minimo= vertices[0]->get_z();
        for(int i=1; i<vertices.size(); i++){
            if(vertices[i]->get_z()<minimo)
            minimo=vertices[i]->get_z();
        }
        break;
    
    default:
        break;
    }
    
    return minimo;
    
}

int Objeto::calcular_maximo(char coordenada){
    int maximo=0;
    switch (coordenada)
    {
    case 'x':
        maximo= vertices[0]->get_x();
        for(int i=1; i<vertices.size(); i++){
            if(vertices[i]->get_x()>maximo)
            maximo=vertices[i]->get_x();
        }
        break;
    case 'y':
        maximo= vertices[0]->get_y();
        for(int i=1; i<vertices.size(); i++){
            if(vertices[i]->get_y()>maximo)
            maximo=vertices[i]->get_y();
        }
        break;
    
    case 'z':
        maximo= vertices[0]->get_z();
        for(int i=1; i<vertices.size(); i++){
            if(vertices[i]->get_z()>maximo)
            maximo=vertices[i]->get_z();
        }
        break;
    
    default:
        break;
    }
    
    return maximo;
}

