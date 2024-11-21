#ifndef OBJETO_H
#define OBJETO_H

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Punto.h"
#include "Linea.h"
#include "Plano.h"
#include "ArbolKD3d.cxx"
#include "Grafo.cxx"

using namespace std;

class Objeto
{
private:
int indice;
string nombre;
vector<Punto *> vertices;
vector<Linea *> aristas;
vector<Plano *> caras;
ArbolKD3d <Punto*> *arbolPuntos;
Grafo<Punto *> grafo;
Objeto* envolvente;

public:
    Objeto(int indice, string nombre, vector<Punto *> vertices, vector<Linea *> aristas, vector<Plano *> caras, Grafo<Punto *> grafo);
    ~Objeto();
    int get_indice();
    string get_nombre();
    vector<Punto *> get_vertices();
    Punto* get_vertices(int indice);
    vector<Linea *> get_aristas();
    Linea* get_aristas(int indice);
    vector<Plano *> get_caras();
    Plano* get_caras(int indice);
    ArbolKD3d <Punto*>* get_arbolPuntos();
    void set_arbolPuntos(ArbolKD3d<Punto *> *arbol);
    Objeto* get_envolvente();
    void set_envolvente(Objeto* envolvente);
    Grafo<Punto *> get_grafo();
    void set_grafo(Grafo <Punto *> grafo);

    void anadir_vertice(Punto * vertice);
    void anadir_arista(Punto * v1, Punto * v2 );
    double calcular_minimo(char coordenada);
    double calcular_maximo(char coordenada);

    double calcula_centroide(char coordenada);
    
    Punto* vertice_cercano(double px, double py, double pz);
    string to_string();

    bool equals(Objeto objeto);
};




#endif