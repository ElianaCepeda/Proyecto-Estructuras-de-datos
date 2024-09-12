#ifndef PUNTO_H
#define PUNTO_H

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

//#include "Linea.h"
//#include "Plano.h"
//#include "Objeto.h"

using namespace std;

class Punto
{
private:
    int indice;
    double x;
    double y;
    double z;
//    vector <Objeto *> esta_en_objetos;
//    vector <Linea *> esta_en_aristas;
//    vector <Plano *> esta_en_caras;
public:
    Punto(int indice,double x, double y, double z);
    double get_x();
    double get_y();
    double get_z();
/*     Objeto * get_esta_en_objetos(int indice);
    vector<Objeto *> get_esta_en_objetos();
    Linea* get_esta_en_aristas(int indice);
    vector<Linea *> get_esta_en_aristas();
    Plano* get_esta_en_caras(int indice);
    vector<Plano *> get_esta_en_caras();
    void anadirObjeto(Objeto * ptrObjeto);
    void anadirArista(Linea * ptrLinea);
    void anadirCara(Plano * ptrPlano); */


};

#endif
