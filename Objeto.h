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

using namespace std;

class Objeto
{
private:
int indice;
string nombre;
vector<Punto *> vertices;
vector<Linea *> aristas;
vector<Plano *> caras;
Objeto* envolvente;

public:
    Objeto(int indice, string nombre, vector<Punto *> vertices, vector<Linea *> aristas, vector<Plano *> caras);
    int get_indice();
    string get_nombre();
    vector<Punto *> get_vertices();
    Punto* get_vertices(int indice);
    vector<Linea *> get_aristas();
    Linea* get_aristas(int indice);
    vector<Plano *> get_caras();
    Plano* get_caras(int indice);
    Objeto* get_envolvente();
    void set_envolvente(Objeto* envolvente);

    int calcular_minimo(char coordenada);
    int calcular_maximo(char coordenada);
};




#endif