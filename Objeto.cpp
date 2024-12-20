#include "Objeto.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

Objeto::Objeto(int indice, string nombre, vector<Punto *> vertices, vector<Linea *> aristas, vector<Plano *> caras, Grafo <Punto* > grafo){
    this->indice=indice;
    this->nombre=nombre;
    this->vertices=vertices;
    this->aristas=aristas;
    this->caras=caras;
    this->arbolPuntos = nullptr;
    this->envolvente=NULL;
    this->grafo= grafo;
}

Objeto::~Objeto(){
    Plano* plano_temporal;
    for(int i=0; i< caras.size(); i++){
        plano_temporal=caras[i];
        delete plano_temporal;
    }
    caras.clear();

    Linea* linea_temporal;
    for(int i=0; i<aristas.size(); i++){
        linea_temporal=aristas[i];
        delete linea_temporal;
    }
    aristas.clear();
    
    Punto* punto_temporal;
    for(int i=0; i<vertices.size(); i++){
        punto_temporal=vertices[i];
        delete punto_temporal;
    }
    vertices.clear();

    delete arbolPuntos;

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

ArbolKD3d<Punto*> *Objeto::get_arbolPuntos(){
    return this->arbolPuntos;
}

void Objeto::set_arbolPuntos(ArbolKD3d<Punto*>  *arbol){
    this->arbolPuntos=arbol;
}

Objeto* Objeto::get_envolvente(){
    return envolvente;
}

void Objeto::set_envolvente(Objeto* envolvente){
    this->envolvente=envolvente;
}

Grafo<Punto *> Objeto::get_grafo(){
    return grafo;
}

void Objeto::set_grafo(Grafo <Punto *> grafo){
    this->grafo=grafo;
}

void Objeto::anadir_vertice(Punto * vertice){
    vertices.push_back(vertice);
    grafo.insertarVertice(vertice);
    arbolPuntos->insertar(vertice);
}
    
void Objeto::anadir_arista(Punto * v1, Punto * v2 ){
    Linea* arista = new Linea(aristas.size(), v1, v2);
    aristas.push_back(arista);
    grafo.insAristaNoDir(v1, v2, arista->get_distancia());
}



double Objeto::calcular_minimo(char coordenada){
    double minimo=0;
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

double Objeto::calcular_maximo(char coordenada){
    double maximo=0;
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

double Objeto::calcula_centroide(char coordenada){
    double centroide=0;
    switch (coordenada)
    {
    case 'x':
        for(int i=0; i<vertices.size(); i++){
            centroide += vertices[i]->get_x();
        }
        break;
    case 'y':
        for(int i=0; i<vertices.size(); i++){
            centroide += vertices[i]->get_y();
        }
        break;
    
    case 'z':
        for(int i=0; i<vertices.size(); i++){
            centroide += vertices[i]->get_z();
        }
        break;
    
    default:
        break;
    }
    
    return centroide/vertices.size();
}


Punto* Objeto::vertice_cercano(double px, double py, double pz){
    Punto* verticeCercano;
    Punto* dato= new Punto(-1,-1, px,py,pz);
    verticeCercano= this->arbolPuntos->buscarNodoInsercion(dato);
    delete dato;
    return verticeCercano;
}


string Objeto::to_string(){
    string cadena="";
    cadena+= nombre + " contiene:\t "+ std::to_string(vertices.size()) + " vertices, " + std::to_string(aristas.size()) + " aristas, " +
    std::to_string(caras.size()) + " caras.\n";
    return cadena;
}

bool Objeto::equals(Objeto objeto){
    bool respuesta=false;
    if(this->indice==objeto.indice)
    respuesta=true;

    return true;
}




