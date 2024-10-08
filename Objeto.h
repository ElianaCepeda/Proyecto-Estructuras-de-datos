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
#include "ArbolKD3d.hxx"

using namespace std;

class Objeto
{
private:
int indice;
string nombre;
vector<Punto *> vertices;
vector<Linea *> aristas;
vector<Plano *> caras;
ArbolKD <Punto*> *arbolPuntos;
Objeto* envolvente;

public:
    Objeto(int indice, string nombre, vector<Punto *> vertices, vector<Linea *> aristas, vector<Plano *> caras);
    ~Objeto();
    int get_indice();
    string get_nombre();
    vector<Punto *> get_vertices();
    Punto* get_vertices(int indice);
    vector<Linea *> get_aristas();
    Linea* get_aristas(int indice);
    vector<Plano *> get_caras();
    Plano* get_caras(int indice);
    ArbolKD <Punto*>* get_arbolPuntos();
    void set_arbolPuntos(ArbolKD<Punto *> *arbol);
    Objeto* get_envolvente();
    void set_envolvente(Objeto* envolvente);

    int calcular_minimo(char coordenada);
    int calcular_maximo(char coordenada);
    Punto* vertice_cercano(double px, double py, double pz);
    string to_string();

    bool equals(Objeto objeto);
    bool caras_iguales(vector<Plano*> caras);
};




#endif