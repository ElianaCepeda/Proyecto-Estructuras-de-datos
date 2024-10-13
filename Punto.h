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
    int indiceGeneral;
    int indiceObjeto;
    double x;
    double y;
    double z;

public:
    Punto(int indiceGeneral, int indiceObjeto,double x, double y, double z);
    Punto();
    Punto& operator=(const Punto &p);
    bool operator==(const Punto &p) const;
    friend std::ostream& operator<<(std::ostream &o, const Punto &p);
    int get_indiceGeneral();
    int get_indiceObjeto();
    double get_x();
    double get_y();
    double get_z();
    void set_x(double x);
    void set_y(double y);
    void set_z(double z);
    bool coordenadas_iguales(double x, double y, double z);
 


};

#endif
