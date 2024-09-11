#ifndef LINEA_H
#define LINEA_H

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Punto.h"
/* #include "Plano.h"
#include "Objeto.h"
 */
using namespace std;

class Linea
{
private:
    int indice;
    Punto* vertice1;
    Punto* vertice2;
    double distancia;
/*     vector<Objeto*> esta_en_objetos;
    vector<Plano*> esta_en_caras;
 */    void calcular_distancia();
public:
    Linea(int indice, Punto* vertice1, Punto* vertice2);
    Linea();
    int get_indice();
    Punto* get_vertice1();
    Punto* get_vertice2();
    double get_distancia();
/*     Objeto* get_esta_en_objetos(int indice);
    vector<Objeto*> get_esta_en_objetos();
    Plano* get_esta_en_caras(int indice);
    vector<Plano*> get_esta_en_caras();
 */
};


#endif