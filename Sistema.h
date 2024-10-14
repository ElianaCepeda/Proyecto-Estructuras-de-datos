#ifndef __SISTEMA__H
#define __SISTEMA__H

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Punto.h"
#include "Linea.h"
#include "Plano.h"
#include "Objeto.h"

using namespace std;


class Sistema{
private:
vector<Punto*> puntos;
vector<Linea*> lineas;
vector<Plano*> planos;
vector<Objeto*> objetos;
Objeto * env_global;
int cant_puntos;
int cant_lineas;
int cant_planos;
int cant_objetos;
 
public:
    Sistema();
    double calcular_distancia(double x, double y, double z, Punto punto);
    int buscar_objeto(string nombre);
    double calcular_minimo(char coordenada);
    double calcular_maximo(char coordenada);
    void cargarArchivo(string nombre);
    void listado();
    void envolvente();
    void envolventeObjeto(string nombreObjeto);
    void descargarObjeto(string nombreObjeto);
    void guardarObjetoArchivo(string nombreObjeto, string nombreArchivo);
    void v_cercanoObjeto(string px, string py, string pz, string nombreObjeto);
    void v_cercano(string px, string py, string pz);
    void v_cercanos_caja(string nombreObjeto);
    void ruta_cortaVertices();
    void ruta_cortaCentro();
    void ayuda();
    void ayudaComando(string comando);
};



#endif
