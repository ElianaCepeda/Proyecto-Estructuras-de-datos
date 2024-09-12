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
vector<Punto> puntos;
vector<Linea> lineas;
vector<Plano> planos;
vector<Objeto> objetos;
int cant_puntos;
int cant_lineas;
int cant_planos;
int cant_objetos;
 
public:
    Sistema();
    int calcular_distancia(Punto punto1, Punto punto2);
    int buscar_objeto(string nombre);
    void cargarArchivo(string nombre);
    void listado();
    void envolvente();
    void envolventeObjeto();
    void descargarObjeto();
    void guardarObjetoArchivo();
    void v_cercanoObjeto();
    void v_cercano();
    void v_cercanos_caja();
    void ruta_cortaVertices();
    void ruta_cortaCentro();
    void ayuda();
    void ayudaComando(string comando);
};



#endif
