#include "Punto.h"

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

Punto::Punto(int indiceGeneral,int indiceObjeto, double x, double y, double z){
    this->indiceGeneral=indiceGeneral;
    this->indiceObjeto= indiceObjeto;
    this->x=x;
    this->y=y;
    this->z=z;
}

Punto::Punto(){
    this->indiceGeneral=-1;
    this->indiceObjeto=-1;
    this->x=0;
    this->y=0;
    this->z=0;
}



Punto& Punto::operator=(const Punto &p)
{
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
}

bool Punto::operator==(const Punto &p) const
{
    return (x == p.x && y == p.y && z==p.z);
}


std::ostream& operator<<(std::ostream &o, const Punto &p)
{
    o <<p.indiceGeneral<< "(" << p.x << "," << p.y << ","<< p.z <<")";
    return o;
}

int Punto::get_indiceGeneral(){
    return indiceGeneral;
}

int Punto::get_indiceObjeto(){
    return indiceObjeto;
}

double Punto::get_x(){
    return x;

}

double Punto::get_y(){
    return y;
}

double Punto::get_z(){
    return z;
}

void Punto::set_x(double x){
    this->x=x;
}


void Punto::set_y(double y){
    this->y=y;
}

void Punto::set_z(double z){
    this->z=z;
}

bool Punto::equals(Punto punto){
    bool respuesta=false;
    if(this->indiceGeneral==punto.indiceGeneral)
    respuesta=true;

    return respuesta;
}

bool Punto::coordenadas_iguales(double x, double y, double z){
    bool respuesta =false;
    if(this->x==x && this->y==y && this->z==z)
    respuesta=true;

    return respuesta;
}
