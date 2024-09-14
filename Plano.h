#ifndef __PLANO__H
#define __PLANO__H

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
//#include "Objeto.h"
#include "Punto.h"
#include "Linea.h"

using namespace std;


class Plano
{
private:
int indice;
vector<Linea *> aristas;
vector<Punto *> vertices;
//vector<Objeto *> esta_en_objetos;

public:
    Plano(int indice, vector<Linea *> aristas, vector<Punto *> vertices);
    ~Plano();
    int get_idice();
    vector<Linea *> get_aristas();
    Linea* get_aristas(int indice);
    vector<Punto *> get_vertices();
    Punto* get_vertices(int indice);
    bool equals(Plano plano);
    bool aristas_iguales(vector< Linea*> aristas);

    //void anadir_Objeto(Objeto* objeto);
};


#endif