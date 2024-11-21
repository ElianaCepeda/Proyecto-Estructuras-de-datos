#include "Sistema.h"

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

Sistema::Sistema(){
  puntos.clear();
  lineas.clear();
  planos.clear();
  objetos.clear();
  cant_lineas=0;
  cant_objetos=0;
  cant_planos=0;
  cant_puntos=0;
}

double Sistema::calcular_distancia(double x, double y, double z, Punto punto){
  double distancia;
  distancia= sqrt(pow(x-punto.get_x(),2)+pow(y-punto.get_y(),2)+pow(z-punto.get_z(),2));
  return distancia;
}

int Sistema::buscar_objeto(string nombre){// si encuentra el indice lo devuelve, si no lo encuentra devuelve -1
  int indice=-1;
  for (int i=0; i<objetos.size();i++){
    if (objetos[i]->get_nombre()==nombre){
        indice=i;
    }
  }
  return indice;
}

double Sistema::calcular_minimo(char coordenada){
    double minimo=0;
    switch (coordenada)
    {
    case 'x':
        minimo= puntos[0]->get_x();
        for(int i=1; i<puntos.size(); i++){
            if(puntos[i]->get_x()<minimo)
            minimo=puntos[i]->get_x();
        }
        break;
    case 'y':
        minimo= puntos[0]->get_y();
        for(int i=1; i<puntos.size(); i++){
            if(puntos[i]->get_y()<minimo)
            minimo=puntos[i]->get_y();
        }
        break;
    
    case 'z':
        minimo= puntos[0]->get_z();
        for(int i=1; i<puntos.size(); i++){
            if(puntos[i]->get_z()<minimo)
            minimo=puntos[i]->get_z();
        }
        break;
    
    default:
        break;
    }
    
    return minimo;
    
}

double Sistema::calcular_maximo(char coordenada){
    double maximo=0;
    switch (coordenada)
    {
    case 'x':
        maximo= puntos[0]->get_x();
        for(int i=1; i<puntos.size(); i++){
            if(puntos[i]->get_x()>maximo)
            maximo=puntos[i]->get_x();
        }
        break;
    case 'y':
        maximo= puntos[0]->get_y();
        for(int i=1; i<puntos.size(); i++){
            if(puntos[i]->get_y()>maximo)
            maximo=puntos[i]->get_y();
        }
        break;
    
    case 'z':
        maximo= puntos[0]->get_z();
        for(int i=1; i<puntos.size(); i++){
            if(puntos[i]->get_z()>maximo)
            maximo=puntos[i]->get_z();
        }
        break;
    
    default:
        break;
    }
    
    return maximo;
}

void Sistema::cargarArchivo(string nombreArchivo){
  int cant_vertices_objeto=0;
  int cant_vertices_cara=0;
  string nombreObjeto;
  vector<Punto *> aux_vertices_objeto;
  vector<Punto *> aux_vertices_cara;
  vector<Linea *> aux_aristas_objeto;
  vector<Linea *> aux_aristas_cara;
  vector<Plano *> aux_caras_objeto;
  ArbolKD3d<Punto* > *aux_arbolPuntos= new ArbolKD3d<Punto *>();
  Grafo <Punto* > aux_grafo;
  bool archivo_correcto=true;
  bool fin_archivo=false;
  bool encontrado;

  ifstream archivo(nombreArchivo.c_str());
    
  if (!archivo.is_open()) {
      std::cout << "El archivo " <<nombreArchivo<< " no existe o es ilegible" << endl;
  }else{
  
    string linea;
    getline(archivo,linea);
    nombreObjeto=linea;
    if(buscar_objeto(nombreObjeto)!=-1){
      std::cout<<"El objeto "<< nombreObjeto << " ya ha sido cargado en memoria"<< endl;
    }else{
    
      try{
 
        getline(archivo, linea);
        cant_vertices_objeto=stoi(linea);
        int contador=0;
        while(contador<cant_vertices_objeto){ //recorrer todos los puntos
          getline(archivo, linea);
          string scoordenada;
          double coordenadas[3];
          stringstream input_stringstream(linea);
          while(getline(input_stringstream, scoordenada, ' ')){ // recorre las coordenadas de los puntos
            coordenadas[0]=stod(scoordenada);
            getline(input_stringstream, scoordenada, ' ');
            coordenadas[1]=stod(scoordenada);
            getline(input_stringstream, scoordenada, ' ');
            coordenadas[2]=stod(scoordenada);
            // crea el nuevo punto y lo asigna a los vertices del objeto 
            Punto *vertice = new Punto(cant_puntos, contador, coordenadas[0],coordenadas[1],coordenadas[2]);
            puntos.push_back(vertice);
            aux_vertices_objeto.push_back(vertice);
            aux_arbolPuntos->insertar(vertice);
            aux_grafo.insertarVertice(vertice);
            cant_puntos++;
            contador++; // guardamos los vertices del objeto
          }
        }


        aux_aristas_objeto.clear();

        while(getline(archivo, linea)){ // leemos las lineas que tienen los datos de las caras
          if(stoi(linea)==-1){
            fin_archivo=true;
          }else{

            string scantvertice;
            string svertice1;
            string svertice2;
            int indice1=0;
            int indice2=0;
            int indiceInicial=0;
            aux_aristas_cara.clear();
            aux_vertices_cara.clear();

            stringstream input_stringstream(linea);
            getline(input_stringstream, scantvertice, ' '); //leemos la cantidad de vertices que tiene la cara 
            cant_vertices_cara=stoi(scantvertice);
            getline(input_stringstream, svertice1, ' '); // leemos el primer indice 
            indice1=stoi(svertice1);
            //cout<<"Indice1: "<<indice1<<endl;
            indiceInicial=indice1;
            aux_vertices_cara.push_back(aux_vertices_objeto[indice1]); // guardamos en los vertices de la cara

            //std::cout<<"Cantidad de vertices por cara: "<<cant_vertices_cara<<endl;
            for(int i=0; i<cant_vertices_cara-1 ; i++){
              getline(input_stringstream, svertice2, ' ');
              indice2=stoi(svertice2);
              
              aux_vertices_cara.push_back(aux_vertices_objeto[indice2]); // guardamos los vertices de la cara

              Linea *arista= new Linea(cant_lineas, aux_vertices_objeto[indice1], aux_vertices_objeto[indice2]);
              lineas.push_back(arista);
              aux_aristas_objeto.push_back(arista);
              aux_aristas_cara.push_back(arista);
              aux_grafo.insAristaNoDir(aux_vertices_objeto[indice1], aux_vertices_objeto[indice2],arista->get_distancia());
              cant_lineas++;
              

              indice1=indice2;
              
            }


            Linea *arista= new Linea(cant_lineas, aux_vertices_objeto[indice2], aux_vertices_objeto[indiceInicial]);
            lineas.push_back(arista);
            aux_aristas_objeto.push_back(arista);
            aux_aristas_cara.push_back(arista);
            cant_lineas++;
            


            Plano *cara= new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
            planos.push_back(cara);
            aux_caras_objeto.push_back(cara);
            cant_planos++;
            aux_aristas_cara.clear();
          }

        }


        Objeto *objeto = new Objeto(cant_objetos, nombreObjeto, aux_vertices_objeto, aux_aristas_objeto, aux_caras_objeto, aux_grafo);
        objetos.push_back(objeto);
        objeto->set_arbolPuntos(aux_arbolPuntos);
        cant_objetos++;
        
      }
      catch (exception &e){
        archivo_correcto=false;
      }
      archivo.close();

      if(archivo_correcto && fin_archivo){
        std::cout<< "El objeto " <<nombreObjeto << " ha sido cargado exitosamente desde el archivo "<< nombreArchivo<<endl;
      }else{
        std::cout<< "El archivo "<<nombreArchivo<< " no contiene un objeto 3D valido"<<endl;
      }

    }

    
  }
  
}

void Sistema::listado(){
  if(objetos.size()>0){
    std::cout<< "Hay "<< objetos.size() << " en memoria" << endl;
    for(int i=0; i<objetos.size();i++){
      cout<<objetos[i]->to_string();
    }


  }else{
    std::cout<< "Ningun objeto ha sido cargado en memoria "<< endl;
  }  

}

void Sistema::envolvente(){
  vector<Punto *> aux_vertices_objeto;
  ArbolKD3d<Punto*> * aux_arbol=new ArbolKD3d<Punto*>();
  vector<Linea *> aux_aristas_objeto;
  vector<Plano *> aux_caras_objeto;
  vector<Punto *> aux_vertices_cara0;
  vector<Linea *> aux_aristas_cara0;
  vector<Punto *> aux_vertices_cara1;
  vector<Linea *> aux_aristas_cara1;
  vector<Punto *> aux_vertices_cara2;
  vector<Linea *> aux_aristas_cara2;
  vector<Punto *> aux_vertices_cara3;
  vector<Linea *> aux_aristas_cara3;
  vector<Punto *> aux_vertices_cara4;
  vector<Linea *> aux_aristas_cara4;
  vector<Punto *> aux_vertices_cara5;
  vector<Linea *> aux_aristas_cara5;

  Grafo<Punto *> aux_grafo; 


  if(objetos.size()==0){
    cout<<"Ningun objeto ha sido cargado en memoria"<<endl;
  }else{

    double xmin=calcular_minimo('x');
    double ymin=calcular_minimo('y');
    double zmin=calcular_minimo('z');
    double xmax=calcular_maximo('x');
    double ymax=calcular_maximo('y');
    double zmax=calcular_maximo('z');

    int indice_objeto= buscar_objeto("env_global");
    if(indice_objeto!=-1){
      Objeto *temporal = objetos[indice_objeto];
      objetos.erase(objetos.begin()+indice_objeto);
      delete temporal;
    }
;
   // creamos los puntos del objeto envolvente y los guardamos

    Punto *p0 = new Punto (cant_puntos, 0, xmax, ymax, zmax );//pmax
    puntos.push_back(p0);
    aux_vertices_objeto.push_back(p0); 
    aux_grafo.insertarVertice(p0);
    aux_arbol->insertar(p0);
    cant_puntos++;

    Punto *p1 = new Punto (cant_puntos, 1, xmax, ymin, zmax );
    puntos.push_back(p1 );
    aux_vertices_objeto.push_back(p1 );
    aux_grafo.insertarVertice(p1); 
    aux_arbol->insertar(p1);
    cant_puntos++;

    Punto *p2 = new Punto (cant_puntos, 2, xmin, ymin, zmax );
    puntos.push_back(p2 );
    aux_vertices_objeto.push_back(p2 );
    aux_grafo.insertarVertice(p2);
    aux_arbol->insertar(p2); 
    cant_puntos++;

    Punto *p3 = new Punto (cant_puntos, 3, xmin, ymax, zmax );
    puntos.push_back(p3 );
    aux_vertices_objeto.push_back(p3 );
    aux_grafo.insertarVertice(p3);
    aux_arbol->insertar(p3); 
    cant_puntos++;

    Punto *p4 = new Punto (cant_puntos, 4, xmin, ymax, zmin );
    puntos.push_back(p4 );
    aux_vertices_objeto.push_back(p4 );
    aux_grafo.insertarVertice(p4);
    aux_arbol->insertar(p4); 
    cant_puntos++;

    Punto *p5 = new Punto (cant_puntos, 5, xmax, ymax, zmin );
    puntos.push_back(p5 );
    aux_vertices_objeto.push_back(p5 ); 
    aux_grafo.insertarVertice(p5);
    aux_arbol->insertar(p5);
    cant_puntos++;

    Punto *p6 = new Punto (cant_puntos, 6, xmax, ymin, zmin );
    puntos.push_back(p6 );
    aux_vertices_objeto.push_back(p6 ); 
    aux_grafo.insertarVertice(p6);
    aux_arbol->insertar(p6);
    cant_puntos++;

    Punto *p7 = new Punto (cant_puntos, 7, xmin, ymin, zmin );//pmin
    puntos.push_back(p7 );
    aux_vertices_objeto.push_back(p7 ); 
    aux_grafo.insertarVertice(p7);
    aux_arbol->insertar(p7);
    cant_puntos++;

    // creamos las aristas necesarias 

    Linea *a0 = new Linea(cant_lineas, p0, p1);
    lineas.push_back(a0 );
    aux_aristas_objeto.push_back(a0 );
    aux_grafo.insAristaNoDir(p0, p1, a0->get_distancia());
    cant_lineas++;

    Linea *a1 = new Linea(cant_lineas, p1, p2);
    lineas.push_back(a1 );
    aux_aristas_objeto.push_back(a1 );
    aux_grafo.insAristaNoDir(p1, p2, a1->get_distancia());
    cant_lineas++;

    Linea *a2 = new Linea(cant_lineas, p2, p3);
    lineas.push_back(a2 );
    aux_aristas_objeto.push_back(a2 );
    aux_grafo.insAristaNoDir(p2, p3, a2->get_distancia());
    cant_lineas++;

    Linea *a3 = new Linea(cant_lineas, p3, p0);
    lineas.push_back(a3 );
    aux_aristas_objeto.push_back(a3 );
    aux_grafo.insAristaNoDir(p3, p0, a3->get_distancia());
    cant_lineas++;

    Linea *a4  = new Linea(cant_lineas, p2, p1);
    lineas.push_back(a4);
    aux_aristas_objeto.push_back(a4);
    aux_grafo.insAristaNoDir(p2, p1, a4->get_distancia());
    cant_lineas++;

    Linea *a5 = new Linea(cant_lineas, p1, p6);
    lineas.push_back(a5 );
    aux_aristas_objeto.push_back(a5 );
    aux_grafo.insAristaNoDir(p1, p6, a5->get_distancia());
    cant_lineas++;

    Linea *a6 = new Linea(cant_lineas, p6, p7);
    lineas.push_back(a6 );
    aux_aristas_objeto.push_back(a6 );
    aux_grafo.insAristaNoDir(p6, p7, a6->get_distancia());
    cant_lineas++;

    Linea *a7 = new Linea(cant_lineas, p7, p2);
    lineas.push_back(a7 );
    aux_aristas_objeto.push_back(a7 );
    aux_grafo.insAristaNoDir(p7, p2, a7->get_distancia());
    cant_lineas++;

    Linea *a8 = new Linea(cant_lineas, p6, p1);
    lineas.push_back(a8 );
    aux_aristas_objeto.push_back(a8 );
    aux_grafo.insAristaNoDir(p6, p1, a8->get_distancia());
    cant_lineas++;

    Linea *a9 = new Linea(cant_lineas, p1, p0);
    lineas.push_back(a9 );
    aux_aristas_objeto.push_back(a9 );
    aux_grafo.insAristaNoDir(p1, p0, a9->get_distancia());
    cant_lineas++;

    Linea *a10 = new Linea(cant_lineas, p0, p5);
    lineas.push_back(a10 );
    aux_aristas_objeto.push_back(a10 );
    aux_grafo.insAristaNoDir(p0, p5, a10->get_distancia());
    cant_lineas++;

    Linea *a11 = new Linea(cant_lineas, p5, p6);
    lineas.push_back(a11 );
    aux_aristas_objeto.push_back(a11 );
    aux_grafo.insAristaNoDir(p5, p6, a11->get_distancia());
    cant_lineas++;

    Linea *a12 = new Linea(cant_lineas, p3, p0);
    lineas.push_back(a12 );
    aux_aristas_objeto.push_back(a12 );
    aux_grafo.insAristaNoDir(p3, p0, a12->get_distancia());
    cant_lineas++;

    Linea *a13 = new Linea(cant_lineas, p0, p5);
    lineas.push_back(a13 );
    aux_aristas_objeto.push_back(a13 );
    aux_grafo.insAristaNoDir(p0, p5, a13->get_distancia());
    cant_lineas++;

    Linea *a14 = new Linea(cant_lineas, p5, p4);
    lineas.push_back(a14 );
    aux_aristas_objeto.push_back(a14 );
    aux_grafo.insAristaNoDir(p5, p4, a14->get_distancia());
    cant_lineas++;

    Linea *a15 = new Linea(cant_lineas, p4, p3);
    lineas.push_back(a15 );
    aux_aristas_objeto.push_back(a15 );
    aux_grafo.insAristaNoDir(p4, p3, a15->get_distancia());
    cant_lineas++;

    Linea *a16  = new Linea(cant_lineas, p3, p2);
    lineas.push_back(a16 );
    aux_aristas_objeto.push_back(a16 );
    aux_grafo.insAristaNoDir(p3, p2, a16->get_distancia());
    cant_lineas++;

    Linea *a17 = new Linea(cant_lineas, p2, p7);
    lineas.push_back(a17 );
    aux_aristas_objeto.push_back(a17 );
    aux_grafo.insAristaNoDir(p2, p7, a17->get_distancia());
    cant_lineas++;

    Linea *a18 = new Linea(cant_lineas, p7, p4);
    lineas.push_back(a18 );
    aux_aristas_objeto.push_back(a18 );
    aux_grafo.insAristaNoDir(p7, p4, a18->get_distancia());
    cant_lineas++;

    Linea *a19 = new Linea(cant_lineas, p4, p3);
    lineas.push_back(a19 );
    aux_aristas_objeto.push_back(a19 );
    aux_grafo.insAristaNoDir(p4, p3, a19->get_distancia());
    cant_lineas++;

    Linea *a20 = new Linea(cant_lineas, p7, p6);
    lineas.push_back(a20 );
    aux_aristas_objeto.push_back(a20 );
    aux_grafo.insAristaNoDir(p7, p6, a20->get_distancia());
    cant_lineas++;

    Linea *a21 = new Linea(cant_lineas, p6, p5);
    lineas.push_back(a21 );
    aux_aristas_objeto.push_back(a21 );
    aux_grafo.insAristaNoDir(p6, p5, a21->get_distancia());
    cant_lineas++;

    Linea *a22 = new Linea(cant_lineas, p5, p4);
    lineas.push_back(a22 );
    aux_aristas_objeto.push_back(a22 );
    aux_grafo.insAristaNoDir(p5, p4, a22->get_distancia());
    cant_lineas++;

    Linea *a23 = new Linea(cant_lineas, p4, p7);
    lineas.push_back(a23 );
    aux_aristas_objeto.push_back(a23 );
    aux_grafo.insAristaNoDir(p4, p7, a23->get_distancia());
    cant_lineas++;

    //Creamos las caras
    aux_aristas_cara0.push_back(a0 );
    aux_aristas_cara0.push_back(a1 );
    aux_aristas_cara0.push_back(a2 );
    aux_aristas_cara0.push_back(a3 );
    aux_vertices_cara0.push_back(p0 );
    aux_vertices_cara0.push_back(p1 );
    aux_vertices_cara0.push_back(p2 );
    aux_vertices_cara0.push_back(p3 );
    Plano *c0 =new Plano(cant_planos, aux_aristas_cara0, aux_vertices_cara0);
    planos.push_back(c0 );
    aux_caras_objeto.push_back(c0 );
    cant_planos++;

    aux_aristas_cara1.push_back(a4 );
    aux_aristas_cara1.push_back(a5 );
    aux_aristas_cara1.push_back(a6 );
    aux_aristas_cara1.push_back(a7 );
    aux_vertices_cara1.push_back(p2 );
    aux_vertices_cara1.push_back(p1 );
    aux_vertices_cara1.push_back(p6 );
    aux_vertices_cara1.push_back(p7 );
    Plano *c1 =new Plano(cant_planos, aux_aristas_cara1, aux_vertices_cara1);
    planos.push_back(c1 );
    aux_caras_objeto.push_back(c1 );
    cant_planos++;

    aux_aristas_cara2.push_back(a8 );
    aux_aristas_cara2.push_back(a9 );
    aux_aristas_cara2.push_back(a10 );
    aux_aristas_cara2.push_back(a11 );
    aux_vertices_cara2.push_back(p6 );
    aux_vertices_cara2.push_back(p1 );
    aux_vertices_cara2.push_back(p0 );
    aux_vertices_cara2.push_back(p5 );
    Plano *c2 =new Plano(cant_planos, aux_aristas_cara2, aux_vertices_cara2);
    planos.push_back(c2 );
    aux_caras_objeto.push_back(c2 );
    cant_planos++;
    
    aux_aristas_cara3.push_back(a12 );
    aux_aristas_cara3.push_back(a13 );
    aux_aristas_cara3.push_back(a14 );
    aux_aristas_cara3.push_back(a15 );
    aux_vertices_cara3.push_back(p3 );
    aux_vertices_cara3.push_back(p0 );
    aux_vertices_cara3.push_back(p5 );
    aux_vertices_cara3.push_back(p4 );
    Plano *c3 =new Plano(cant_planos, aux_aristas_cara3, aux_vertices_cara3);
    planos.push_back(c3 );
    aux_caras_objeto.push_back(c3 );
    cant_planos++;

    aux_aristas_cara4.push_back(a16 );
    aux_aristas_cara4.push_back(a17 );
    aux_aristas_cara4.push_back(a18 );
    aux_aristas_cara4.push_back(a19 );
    aux_vertices_cara4.push_back(p3 );
    aux_vertices_cara4.push_back(p2 );
    aux_vertices_cara4.push_back(p7 );
    aux_vertices_cara4.push_back(p4 );
    Plano *c4 =new Plano(cant_planos, aux_aristas_cara4, aux_vertices_cara4);
    planos.push_back(c4 );
    aux_caras_objeto.push_back(c4 );
    cant_planos++;

    aux_aristas_cara5.push_back(a20 );
    aux_aristas_cara5.push_back(a21 );
    aux_aristas_cara5.push_back(a22 );
    aux_aristas_cara5.push_back(a23 );
    aux_vertices_cara5.push_back(p7 );
    aux_vertices_cara5.push_back(p6 );
    aux_vertices_cara5.push_back(p5 );
    aux_vertices_cara5.push_back(p4 );
    Plano *c5 =new Plano(cant_planos, aux_aristas_cara5, aux_vertices_cara5);
    planos.push_back(c5 );
    aux_caras_objeto.push_back(c5 );
    cant_planos++;
  
      
    Objeto *envolvente= new Objeto(cant_objetos, "env_global", aux_vertices_objeto,aux_aristas_objeto,aux_caras_objeto, aux_grafo);
    envolvente->set_arbolPuntos(aux_arbol);
    objetos.push_back(envolvente);
    cant_objetos++;
    envolvente->set_envolvente(envolvente);
    
      

    cout<< "La caja envolvente de los objetos en memoria se ha generado con el nombre env_global y se ha agregado a los objetos en memoria."<<endl;
  }
}

void Sistema::envolventeObjeto(string nombreObjeto){
  int indice_objeto= buscar_objeto(nombreObjeto);
  vector<Punto *> aux_vertices_objeto;
  ArbolKD3d<Punto *> *aux_arbol= new ArbolKD3d<Punto*>();
  vector<Linea *> aux_aristas_objeto;
  vector<Plano *> aux_caras_objeto;
  vector<Punto *> aux_vertices_cara0;
  vector<Linea *> aux_aristas_cara0;
  vector<Punto *> aux_vertices_cara1;
  vector<Linea *> aux_aristas_cara1;
  vector<Punto *> aux_vertices_cara2;
  vector<Linea *> aux_aristas_cara2;
  vector<Punto *> aux_vertices_cara3;
  vector<Linea *> aux_aristas_cara3;
  vector<Punto *> aux_vertices_cara4;
  vector<Linea *> aux_aristas_cara4;
  vector<Punto *> aux_vertices_cara5;
  vector<Linea *> aux_aristas_cara5;

  Grafo <Punto *> aux_grafo;

  if(indice_objeto==-1){
    cout<<"El objeto "<<nombreObjeto<<" no ha sido cargado en memoria"<<endl;
  }else{
    double xmin=objetos[indice_objeto]->calcular_minimo('x');
    double ymin=objetos[indice_objeto]->calcular_minimo('y');
    double zmin=objetos[indice_objeto]->calcular_minimo('z');
    double xmax=objetos[indice_objeto]->calcular_maximo('x');
    double ymax=objetos[indice_objeto]->calcular_maximo('y');
    double zmax=objetos[indice_objeto]->calcular_maximo('z');

    // creamos los puntos del objeto envolvente y los guardamos

    Punto *p0 = new Punto (cant_puntos, 0, xmax, ymax, zmax );//pmax
    puntos.push_back(p0);
    aux_vertices_objeto.push_back(p0); 
    aux_grafo.insertarVertice(p0);
    aux_arbol->insertar(p0);
    cant_puntos++;

    Punto *p1 = new Punto (cant_puntos, 1, xmax, ymin, zmax );
    puntos.push_back(p1 );
    aux_vertices_objeto.push_back(p1 );
    aux_grafo.insertarVertice(p1); 
    aux_arbol->insertar(p1);
    cant_puntos++;

    Punto *p2 = new Punto (cant_puntos, 2, xmin, ymin, zmax );
    puntos.push_back(p2 );
    aux_vertices_objeto.push_back(p2 );
    aux_grafo.insertarVertice(p2);
    aux_arbol->insertar(p2); 
    cant_puntos++;

    Punto *p3 = new Punto (cant_puntos, 3, xmin, ymax, zmax );
    puntos.push_back(p3 );
    aux_vertices_objeto.push_back(p3 );
    aux_grafo.insertarVertice(p3);
    aux_arbol->insertar(p3); 
    cant_puntos++;

    Punto *p4 = new Punto (cant_puntos, 4, xmin, ymax, zmin );
    puntos.push_back(p4 );
    aux_vertices_objeto.push_back(p4 );
    aux_grafo.insertarVertice(p4);
    aux_arbol->insertar(p4); 
    cant_puntos++;

    Punto *p5 = new Punto (cant_puntos, 5, xmax, ymax, zmin );
    puntos.push_back(p5 );
    aux_vertices_objeto.push_back(p5 ); 
    aux_grafo.insertarVertice(p5);
    aux_arbol->insertar(p5);
    cant_puntos++;

    Punto *p6 = new Punto (cant_puntos, 6, xmax, ymin, zmin );
    puntos.push_back(p6 );
    aux_vertices_objeto.push_back(p6 ); 
    aux_grafo.insertarVertice(p6);
    aux_arbol->insertar(p6);
    cant_puntos++;

    Punto *p7 = new Punto (cant_puntos, 7, xmin, ymin, zmin );//pmin
    puntos.push_back(p7 );
    aux_vertices_objeto.push_back(p7 ); 
    aux_grafo.insertarVertice(p7);
    aux_arbol->insertar(p7);
    cant_puntos++;

    // creamos las aristas necesarias 

    Linea *a0 = new Linea(cant_lineas, p0, p1);
    lineas.push_back(a0 );
    aux_aristas_objeto.push_back(a0 );
    aux_grafo.insAristaNoDir(p0, p1, a0->get_distancia());
    cant_lineas++;

    Linea *a1 = new Linea(cant_lineas, p1, p2);
    lineas.push_back(a1 );
    aux_aristas_objeto.push_back(a1 );
    aux_grafo.insAristaNoDir(p1, p2, a1->get_distancia());
    cant_lineas++;

    Linea *a2 = new Linea(cant_lineas, p2, p3);
    lineas.push_back(a2 );
    aux_aristas_objeto.push_back(a2 );
    aux_grafo.insAristaNoDir(p2, p3, a2->get_distancia());
    cant_lineas++;

    Linea *a3 = new Linea(cant_lineas, p3, p0);
    lineas.push_back(a3 );
    aux_aristas_objeto.push_back(a3 );
    aux_grafo.insAristaNoDir(p3, p0, a3->get_distancia());
    cant_lineas++;

    Linea *a4  = new Linea(cant_lineas, p2, p1);
    lineas.push_back(a4);
    aux_aristas_objeto.push_back(a4);
    aux_grafo.insAristaNoDir(p2, p1, a4->get_distancia());
    cant_lineas++;

    Linea *a5 = new Linea(cant_lineas, p1, p6);
    lineas.push_back(a5 );
    aux_aristas_objeto.push_back(a5 );
    aux_grafo.insAristaNoDir(p1, p6, a5->get_distancia());
    cant_lineas++;

    Linea *a6 = new Linea(cant_lineas, p6, p7);
    lineas.push_back(a6 );
    aux_aristas_objeto.push_back(a6 );
    aux_grafo.insAristaNoDir(p6, p7, a6->get_distancia());
    cant_lineas++;

    Linea *a7 = new Linea(cant_lineas, p7, p2);
    lineas.push_back(a7 );
    aux_aristas_objeto.push_back(a7 );
    aux_grafo.insAristaNoDir(p7, p2, a7->get_distancia());
    cant_lineas++;

    Linea *a8 = new Linea(cant_lineas, p6, p1);
    lineas.push_back(a8 );
    aux_aristas_objeto.push_back(a8 );
    aux_grafo.insAristaNoDir(p6, p1, a8->get_distancia());
    cant_lineas++;

    Linea *a9 = new Linea(cant_lineas, p1, p0);
    lineas.push_back(a9 );
    aux_aristas_objeto.push_back(a9 );
    aux_grafo.insAristaNoDir(p1, p0, a9->get_distancia());
    cant_lineas++;

    Linea *a10 = new Linea(cant_lineas, p0, p5);
    lineas.push_back(a10 );
    aux_aristas_objeto.push_back(a10 );
    aux_grafo.insAristaNoDir(p0, p5, a10->get_distancia());
    cant_lineas++;

    Linea *a11 = new Linea(cant_lineas, p5, p6);
    lineas.push_back(a11 );
    aux_aristas_objeto.push_back(a11 );
    aux_grafo.insAristaNoDir(p5, p6, a11->get_distancia());
    cant_lineas++;

    Linea *a12 = new Linea(cant_lineas, p3, p0);
    lineas.push_back(a12 );
    aux_aristas_objeto.push_back(a12 );
    aux_grafo.insAristaNoDir(p3, p0, a12->get_distancia());
    cant_lineas++;

    Linea *a13 = new Linea(cant_lineas, p0, p5);
    lineas.push_back(a13 );
    aux_aristas_objeto.push_back(a13 );
    aux_grafo.insAristaNoDir(p0, p5, a13->get_distancia());
    cant_lineas++;

    Linea *a14 = new Linea(cant_lineas, p5, p4);
    lineas.push_back(a14 );
    aux_aristas_objeto.push_back(a14 );
    aux_grafo.insAristaNoDir(p5, p4, a14->get_distancia());
    cant_lineas++;

    Linea *a15 = new Linea(cant_lineas, p4, p3);
    lineas.push_back(a15 );
    aux_aristas_objeto.push_back(a15 );
    aux_grafo.insAristaNoDir(p4, p3, a15->get_distancia());
    cant_lineas++;

    Linea *a16  = new Linea(cant_lineas, p3, p2);
    lineas.push_back(a16 );
    aux_aristas_objeto.push_back(a16 );
    aux_grafo.insAristaNoDir(p3, p2, a16->get_distancia());
    cant_lineas++;

    Linea *a17 = new Linea(cant_lineas, p2, p7);
    lineas.push_back(a17 );
    aux_aristas_objeto.push_back(a17 );
    aux_grafo.insAristaNoDir(p2, p7, a17->get_distancia());
    cant_lineas++;

    Linea *a18 = new Linea(cant_lineas, p7, p4);
    lineas.push_back(a18 );
    aux_aristas_objeto.push_back(a18 );
    aux_grafo.insAristaNoDir(p7, p4, a18->get_distancia());
    cant_lineas++;

    Linea *a19 = new Linea(cant_lineas, p4, p3);
    lineas.push_back(a19 );
    aux_aristas_objeto.push_back(a19 );
    aux_grafo.insAristaNoDir(p4, p3, a19->get_distancia());
    cant_lineas++;

    Linea *a20 = new Linea(cant_lineas, p7, p6);
    lineas.push_back(a20 );
    aux_aristas_objeto.push_back(a20 );
    aux_grafo.insAristaNoDir(p7, p6, a20->get_distancia());
    cant_lineas++;

    Linea *a21 = new Linea(cant_lineas, p6, p5);
    lineas.push_back(a21 );
    aux_aristas_objeto.push_back(a21 );
    aux_grafo.insAristaNoDir(p6, p5, a21->get_distancia());
    cant_lineas++;

    Linea *a22 = new Linea(cant_lineas, p5, p4);
    lineas.push_back(a22 );
    aux_aristas_objeto.push_back(a22 );
    aux_grafo.insAristaNoDir(p5, p4, a22->get_distancia());
    cant_lineas++;

    Linea *a23 = new Linea(cant_lineas, p4, p7);
    lineas.push_back(a23 );
    aux_aristas_objeto.push_back(a23 );
    aux_grafo.insAristaNoDir(p4, p7, a23->get_distancia());
    cant_lineas++;

    //Creamos las caras
    aux_aristas_cara0.push_back(a0 );
    aux_aristas_cara0.push_back(a1 );
    aux_aristas_cara0.push_back(a2 );
    aux_aristas_cara0.push_back(a3 );
    aux_vertices_cara0.push_back(p0 );
    aux_vertices_cara0.push_back(p1 );
    aux_vertices_cara0.push_back(p2 );
    aux_vertices_cara0.push_back(p3 );
    Plano *c0 =new Plano(cant_planos, aux_aristas_cara0, aux_vertices_cara0);
    planos.push_back(c0 );
    aux_caras_objeto.push_back(c0 );
    cant_planos++;

    aux_aristas_cara1.push_back(a4 );
    aux_aristas_cara1.push_back(a5 );
    aux_aristas_cara1.push_back(a6 );
    aux_aristas_cara1.push_back(a7 );
    aux_vertices_cara1.push_back(p2 );
    aux_vertices_cara1.push_back(p1 );
    aux_vertices_cara1.push_back(p6 );
    aux_vertices_cara1.push_back(p7 );
    Plano *c1 =new Plano(cant_planos, aux_aristas_cara1, aux_vertices_cara1);
    planos.push_back(c1 );
    aux_caras_objeto.push_back(c1 );
    cant_planos++;

    aux_aristas_cara2.push_back(a8 );
    aux_aristas_cara2.push_back(a9 );
    aux_aristas_cara2.push_back(a10 );
    aux_aristas_cara2.push_back(a11 );
    aux_vertices_cara2.push_back(p6 );
    aux_vertices_cara2.push_back(p1 );
    aux_vertices_cara2.push_back(p0 );
    aux_vertices_cara2.push_back(p5 );
    Plano *c2 =new Plano(cant_planos, aux_aristas_cara2, aux_vertices_cara2);
    planos.push_back(c2 );
    aux_caras_objeto.push_back(c2 );
    cant_planos++;
    
    aux_aristas_cara3.push_back(a12 );
    aux_aristas_cara3.push_back(a13 );
    aux_aristas_cara3.push_back(a14 );
    aux_aristas_cara3.push_back(a15 );
    aux_vertices_cara3.push_back(p3 );
    aux_vertices_cara3.push_back(p0 );
    aux_vertices_cara3.push_back(p5 );
    aux_vertices_cara3.push_back(p4 );
    Plano *c3 =new Plano(cant_planos, aux_aristas_cara3, aux_vertices_cara3);
    planos.push_back(c3 );
    aux_caras_objeto.push_back(c3 );
    cant_planos++;

    aux_aristas_cara4.push_back(a16 );
    aux_aristas_cara4.push_back(a17 );
    aux_aristas_cara4.push_back(a18 );
    aux_aristas_cara4.push_back(a19 );
    aux_vertices_cara4.push_back(p3 );
    aux_vertices_cara4.push_back(p2 );
    aux_vertices_cara4.push_back(p7 );
    aux_vertices_cara4.push_back(p4 );
    Plano *c4 =new Plano(cant_planos, aux_aristas_cara4, aux_vertices_cara4);
    planos.push_back(c4 );
    aux_caras_objeto.push_back(c4 );
    cant_planos++;

    aux_aristas_cara5.push_back(a20 );
    aux_aristas_cara5.push_back(a21 );
    aux_aristas_cara5.push_back(a22 );
    aux_aristas_cara5.push_back(a23 );
    aux_vertices_cara5.push_back(p7 );
    aux_vertices_cara5.push_back(p6 );
    aux_vertices_cara5.push_back(p5 );
    aux_vertices_cara5.push_back(p4 );
    Plano *c5 =new Plano(cant_planos, aux_aristas_cara5, aux_vertices_cara5);
    planos.push_back(c5 );
    aux_caras_objeto.push_back(c5 );
    cant_planos++;
    
    Objeto *envolvente= new Objeto(cant_objetos, "env_"+nombreObjeto, aux_vertices_objeto,aux_aristas_objeto,aux_caras_objeto, aux_grafo);
    envolvente->set_arbolPuntos(aux_arbol);
    objetos.push_back(envolvente);
    cant_objetos++;
    objetos[indice_objeto]->set_envolvente(envolvente);
    envolvente->set_envolvente(envolvente);

    cout<< " La caja envolvente del objeto "<< nombreObjeto <<" se ha generado con el nombre env_"<<nombreObjeto<<" y se ha agregado a los objetos en memoria."<<endl;

  }

}

void Sistema::descargarObjeto(string nombreObjeto){ 
  int indiceObjeto= buscar_objeto(nombreObjeto);
  cout<<"indice del objeto a descargar: "<<indiceObjeto<<endl;
  if(indiceObjeto==-1){
    cout<<"El objeto "<<nombreObjeto<<" no ha sido cargado en memoria"<<endl;
  }else{
    Objeto *temporal = objetos[indiceObjeto];
    objetos.erase(objetos.begin()+indiceObjeto);
    delete temporal;
    cout<<"El objeto "<<nombreObjeto<<" ha sido eliminado de la memoria de trabajo\n";
  }
  
}

void Sistema::guardarObjetoArchivo(string nombreObjeto, string nombreArchivo){
  int indice=buscar_objeto(nombreObjeto);
  Objeto* obj_temp= objetos[indice];
  if(indice==-1){
    cout<<"El objeto "<<nombreObjeto<<" no ha sido cargado en memoria."<<endl;
  }else{
    ofstream file (nombreArchivo, std::ofstream::out);
    int cant_vertices_objeto=obj_temp->get_vertices().size();
    int cant_caras_objeto=obj_temp->get_caras().size();
    if(file.is_open()){
      file<<nombreObjeto<<endl;
      file<<cant_vertices_objeto<<endl;
      for(int i=0; i<cant_vertices_objeto;i++){
        file<<obj_temp->get_vertices()[i]->get_x()<<" "<<obj_temp->get_vertices()[i]->get_y()<<" "<<obj_temp->get_vertices()[i]->get_z()<<endl;
      }

      string cara;
      for(int i=0; i<cant_caras_objeto;i++){
        int cant_vertices_cara=obj_temp->get_caras()[i]->get_aristas().size();
        cara.clear();
        cara+= to_string(cant_vertices_cara);
        for(int j=0; j<cant_vertices_cara;j++){
          for(int k=0; k<obj_temp->get_vertices().size();k++){
            if(obj_temp->get_caras()[i]->get_aristas()[j]->get_vertice1()==obj_temp->get_vertices()[k]){
              cara+= " "+ to_string(k);
            }
              
          }
        }

        file<<cara<<endl;
      }
    }
    file<<"-1"<<endl;
    file.close();
    cout<<"La información del objeto "<<nombreObjeto<<" ha sido guardada exitosamente en el archivo "<<nombreArchivo<<endl;

  }

  
}

int Sistema::v_cercanoObjeto(double x, double y, double z, string nombreObjeto)
{
  int indiceObjeto = buscar_objeto(nombreObjeto);
  bool parametros_correctos = true;
  int indice= -1;

  if (indiceObjeto == -1)
  {
    cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria" << endl;
  }
  else
  {
    try
    {
      Objeto *objeto = objetos[indiceObjeto];  
      double menor =0; 
      if (parametros_correctos)
      {
        Punto* verticeCercano;
        
        verticeCercano= objetos[indiceObjeto]->vertice_cercano(x,y,z);
        indice=verticeCercano->get_indiceObjeto();
      }
    }
    catch (exception &e)
    {
      parametros_correctos = false;
      cout << "parametros del punto dado invalidos" << endl;
    }
  }

  return indice;
}

void Sistema::v_cercanoObjeto(string px, string py, string pz, string nombreObjeto)
{
  int indiceObjeto = buscar_objeto(nombreObjeto);
  bool parametros_correctos = true;
  if (indiceObjeto == -1)
  {
    cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria" << endl;
  }
  else
  {
    try
    {
      Objeto *objeto = objetos[indiceObjeto];
      double x = stod(px);
      double y = stod(py);
      double z = stod(pz);
      double menor =0; 
      if (parametros_correctos)
      {
        Punto* verticeCercano;
        
        verticeCercano= objetos[indiceObjeto]->vertice_cercano(x,y,z);
        menor = calcular_distancia(x,y,z,*verticeCercano);
        cout << "El vertice " << verticeCercano->get_indiceObjeto() << " " << *verticeCercano
             << " del objeto " << nombreObjeto << " es el mas cercano al punto ( " << x << " " << y << " " << z << " ), a una distancia de valor " << menor << endl;
      }
    }
    catch (exception &e)
    {
      parametros_correctos = false;
      cout << "parametros del punto dado invalidos" << endl;
    }
  }

}


void Sistema::v_cercano(string px, string py, string pz){
  bool parametros_correctos=true;

   if (objetos.size() == 0)
  {
    cout << "Ningun objeto ha sido cargado en memoria" << endl;
  }
  else
  {
    try
    {
      double x = stod(px);
      double y = stod(py);
      double z = stod(pz);
      if (parametros_correctos)
      {
        Punto* vertice_Objeto=objetos[0]->vertice_cercano(x,y,z);
        double menor=calcular_distancia(x, y, z, *(vertice_Objeto));
        double distancia;
        Punto* vertice_cercano;
        int indice_objeto;
        for (int i = 0; i < objetos.size(); i++)
        {
          vertice_Objeto=objetos[i]->vertice_cercano(x,y,z);
          distancia = calcular_distancia(x, y, z, *(vertice_Objeto));
          if (distancia <= menor)
          {
            menor = distancia;
            vertice_cercano = vertice_Objeto;
            indice_objeto = i;
          }
        
        }
        cout << "El vertice " << vertice_cercano->get_indiceObjeto() << *vertice_cercano
             << " del objeto " << objetos[indice_objeto]->get_nombre() << " es el mas cercano al punto ( " << x << " " << y << " " << z << " ), a una distancia de valor " << menor << endl;
      }
    }
    catch (exception &e)
    {
      parametros_correctos = false;
      cout << "parametros del punto dado invalidos" << endl;
    }
  }

}

void Sistema::v_cercanos_caja(string nombreObjeto){
  int indiceObjeto = buscar_objeto(nombreObjeto);
  bool parametros_correctos = true;

  if (indiceObjeto == -1)
  {
    cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria" << endl;
  }
  else
  {
    Objeto *envolvente = objetos[indiceObjeto]->get_envolvente();
    Objeto *objeto=objetos[indiceObjeto];
    if(envolvente == nullptr){
      envolventeObjeto(nombreObjeto);
      envolvente = objetos[indiceObjeto]->get_envolvente();
    }

    cout<<"Esquina\t\tVertice\t\tDistancia"<<endl;
    for(int i=0; i<envolvente->get_vertices().size();i++){
      double x;
      double y;
      double z;
      x=envolvente->get_vertices()[i]->get_x();
      y=envolvente->get_vertices()[i]->get_y();
      z=envolvente->get_vertices()[i]->get_z();
      double menor=calcular_distancia(x,y,z, *(objeto->get_vertices()[0]));
      double distancia;
      
      Punto* verticeCercano;
      
      verticeCercano= objetos[indiceObjeto]->vertice_cercano(x,y,z);
      menor = calcular_distancia(x,y,z,*verticeCercano);


      cout<<i+1<<" ( "<<x<<" "<<y<<" "<<z<<" )\t"
          <<verticeCercano->get_indiceObjeto()<<*verticeCercano<<"\t"
          <<menor<<endl;
    
    }
  
  }
  
}

void Sistema::ruta_cortaVertices(string i1, string i2, string nombre_objeto){
  bool parametros_correctos =true;
  if (objetos.size() == 0)
  {
    cout << "Ningun objeto ha sido cargado en memoria" << endl;
    parametros_correctos=false;
    return;
  }


  int indice1;
  int indice2;
  int indiceObjeto;
  try
  {
    indice1 = stoi(i1);
    indice2 = stoi(i2);

    if(indice1 == indice2){
      cout<<"Los indices de los vertices dados son iguales \n";
      parametros_correctos=false;
      return;
    }

    indiceObjeto = buscar_objeto(nombre_objeto);
    if(indiceObjeto==-1){
      cout<<"El objeto "<<nombre_objeto<< " no ha sido cargado en memoria\n";
      parametros_correctos= false;
      return;
    }else{
      if((indice1|| indice2)>objetos[indiceObjeto]->get_vertices().size()){
        cout<<"Algunos de los indices de los vertices estan fuera de rango para el objeto "<<nombre_objeto<<endl;
        parametros_correctos=false;
        return;
      }
      if(parametros_correctos){
        vector< vector<unsigned long> > rutas_cortas = objetos[indiceObjeto]->get_grafo().dijkstra(indice1);
        vector<unsigned long> ruta = rutas_cortas[indice2];
       
        
        if(ruta.size()>0){
          cout<< "La ruta mas corta que conecta los vertices "<< indice1<<" " << *objetos[indiceObjeto]->get_vertices()[indice1]
          << " y "<< indice2<<" " << *objetos[indiceObjeto]->get_vertices()[indice2]<<" del objeto "<<nombre_objeto<< " pasa por: ";
          cout<< ruta[0];
        }else{
          cout<< "No existe una ruta entre los vertices "<< indice1<< " y "<< indice2<<" del objeto "<<nombre_objeto<<endl;
        }
        
        for( unsigned int i = 1; i < ruta.size( ); ++i )
          cout << " - "<< ruta[ i ] ;

          cout << " con una longitud de: ";
          double costoTotal = 0.0;
          for( unsigned int k = 0; k < ruta.size( ) - 1; ++k )
            costoTotal += objetos[indiceObjeto]->get_grafo().obtenerCosto( ruta[ k ], ruta[ k + 1 ] );
            cout << costoTotal << std::endl;

      }

    }


    }catch(exception &e){
      cout<<"parametros no validos\n";
    }
  
}


void Sistema::ruta_cortaVertices(int indice1, int indice2, string nombre_objeto){
  bool parametros_correctos =true;
  if (objetos.size() == 0)
  {
    cout << "Ningun objeto ha sido cargado en memoria" << endl;
    parametros_correctos=false;
    return;
  }

    if(indice1 == indice2){
      cout<<"Los indices de los vertices dados son iguales \n";
      parametros_correctos=false;
      return;
    }

    int indiceObjeto = buscar_objeto(nombre_objeto);
   
      if(parametros_correctos){
        vector< vector<unsigned long> > rutas_cortas = objetos[indiceObjeto]->get_grafo().dijkstra(indice1);
        vector<unsigned long> ruta = rutas_cortas[indice2];
       
        if(ruta.size()>0){
          cout<< "La ruta mas corta que conecta el vertice "<< indice1<< " " << *objetos[indiceObjeto]->get_vertices()[indice1]<<" con el centro del objeto "<<nombre_objeto<< " ubicado en "<<indice2 <<" "<< *objetos[indiceObjeto]->get_vertices()[indice2] <<" pasa por: ";
          cout<< ruta[0];
        }else{
          cout<< "No existe una ruta entre los vertices "<< indice1<< " y "<< indice2<<" del objeto "<<nombre_objeto<<endl;
        }
        
        for( unsigned int i = 1; i < ruta.size( ); ++i )
          cout << " - "<< ruta[ i ] ;

          cout << " con una longitud de: ";
          double costoTotal = 0.0;
          for( unsigned int k = 0; k < ruta.size( ) - 1; ++k )
            costoTotal += objetos[indiceObjeto]->get_grafo().obtenerCosto( ruta[ k ], ruta[ k + 1 ] );
            cout << costoTotal << std::endl;


    }
  
}

void Sistema::ruta_cortaCentro(string i1, string nombre_objeto){

  bool parametros_correctos =true;
  if (objetos.size() == 0)
  {
    cout << "Ningun objeto ha sido cargado en memoria" << endl;
    parametros_correctos=false;
    return;
  }

  int indice1;
  int indiceObjeto;
  try
  {
    indice1 = stoi(i1);

    indiceObjeto = buscar_objeto(nombre_objeto);
    if(indiceObjeto==-1){
      cout<<"El objeto "<<nombre_objeto<< " no ha sido cargado en memoria\n";
      parametros_correctos= false;
      return;
    }

    if(parametros_correctos){
      double cen_x = objetos[indiceObjeto]->calcula_centroide('x');
      double cen_y = objetos[indiceObjeto]->calcula_centroide('y');
      double cen_z = objetos[indiceObjeto]->calcula_centroide('z');

      int indice_conexion= v_cercanoObjeto(cen_x, cen_y, cen_z, nombre_objeto);
      vector <Punto *> puntos_objeto =objetos[indiceObjeto]->get_vertices();

      Punto* vertice= new Punto(cant_puntos ,puntos_objeto.size(), cen_x, cen_y, cen_z );
      cant_puntos++;

      objetos[indiceObjeto]->anadir_vertice(vertice);
      objetos[indiceObjeto]->anadir_arista(puntos_objeto[indice_conexion], vertice);

      ruta_cortaVertices(indice1, puntos_objeto.size(), nombre_objeto);

    }







  }catch(exception &e){
    cout<<"Parametros no validos\n";
  }

}



void Sistema::ayuda(){

  std::cout<<"lista de comandos: "<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"cargar nombre_archivo"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"listado"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"envolvente nombre_objeto"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"envolvente"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"descargar nombre_objeto"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"guardar nombre_objeto nombre_archivo"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"v_cercano px py pz nombre_objeto"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"v_cercano px py pz"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"v_cercanos_caja nombre_objeto"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"ruta_corta i1 i2 nombre_objeto"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"ruta_corta_centro i1 nombre_objeto"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"salir"<<endl<<endl;


}

void Sistema::ayudaComando(string comando){
  if (strcmp(comando.c_str(), "cargar") == 0) {
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"cargar nombre_archivo"<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"Carga en memoria la información del objeto nombre_objeto contenida en el archivo identificado por nombre_archivo."<<endl;
    std::cout<<"------------------------------------------------"<<endl;

  } else if (strcmp(comando.c_str(), "listado") == 0) {
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"listado"<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"Lista los objetos cargados actualmente en memoria, junto con la información básica de cada uno: cantidad de puntos, de aristas y de caras."<<endl;
    std::cout<<"------------------------------------------------"<<endl;

  } else if (strcmp(comando.c_str(), "envolvente") == 0) {
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"envolvente nombre_objeto"<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<" Calcula la caja envolvente del objeto identificado por nombre_objeto. La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_nombre_objeto, para distinguirla de los demás objetos en memoria"<<endl;
    std::cout<<"------------------------------------------------"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"envolvente"<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<" La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_nombre_objeto, para distinguirla de los demás objetos en memoria. La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_global, para distinguirla de los demás objetos en memoria"<<endl;
    std::cout<<"------------------------------------------------"<<endl;


  } else if (strcmp(comando.c_str(), "descargar") == 0) {
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"descargar nombre_objeto"<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<" Descarga de la memoria toda la información básica (vértices, aristas, caras) del objeto identificado por nombre_objeto"<<endl;
    std::cout<<"------------------------------------------------"<<endl;


  } else if (strcmp(comando.c_str(), "guardar") == 0) {
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"guardar nombre_objeto nombre_archivo"<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"Escribe en un archivo de texto, identificado por nombre_archivo, la información básica (vértices y caras) del objeto identificado por nombre_objeto"<<endl;
    std::cout<<"------------------------------------------------"<<endl;


  } else if (strcmp(comando.c_str(), "v_cercano") == 0) {
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"v_cercano px py pz nombre_objeto"<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"  Identifica el vértice del objeto nombre_objeto más cercano (en términos de la distancia euclidiana) al punto indicado por las coordenadas px, py y pz. Informa en pantalla el índice del vértice, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra del punto dado"<<endl;
    std::cout<<"------------------------------------------------"<<endl<<endl;

    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"v_cercano px py pz"<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"  Identifica, entre todos los objetos cargados en memoria, el vértice más cercano (en términos de la distancia euclidiana) al punto indicado por las coordenadas px, py y pz. Informa en pantalla el objeto al que pertenece, el índice del vértice, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra del punto dado"<<endl;
    std::cout<<"------------------------------------------------"<<endl;

  } else if (strcmp(comando.c_str(), "v_cercanos_caja") == 0) {
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"v_cercanos_caja nombre_objeto"<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"Identifica los vértices del objeto nombre_objeto más cercanos (en términos de la distancia euclidiana) a los puntos (vértices) que definen la respectiva caja envolvente del objeto. Informa en pantalla, en una tabla, las coordenadas de cada una de las esquinas de la caja envolvente, y para cada una de ellas, el índice del vértice más cercano, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra de la respectiva esquina"<<endl;
    std::cout<<"------------------------------------------------"<<endl;

  } else if (strcmp(comando.c_str(), "ruta_corta") == 0) {
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"ruta_corta i1 i2 nombre_objeto"<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"Identifica los índices de los vértices que conforman la ruta más corta entre los vértices dados para el objeto nombre_objeto. La distancia entre los vértices está medida en términos de la distancia euclidiana. Informa, además, la distancia total de la ruta calculada"<<endl;
    std::cout<<"------------------------------------------------"<<endl;


  } else if (strcmp((comando).c_str(), "ruta_corta_centro") == 0) {
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"ruta_corta_centro i1 nombre_objeto"<<endl<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<" Identifica los índices de los vértices que conforman la ruta más corta entre el vértice dado y el centro del objeto nombre_objeto. La distancia entre los vértices está medida en términos de la distancia euclidiana. Informa, además, la distancia total de la ruta calculada."<<endl;
    std::cout<<"------------------------------------------------"<<endl;

  } else if (strcmp((comando).c_str(), "salir") == 0) {
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"salir"<<endl;
    std::cout<<"------------------------------------------------"<<endl;
    std::cout<<"Termina la ejecución de la aplicación."<<endl;
    std::cout<<"------------------------------------------------"<<endl;

  }else {
    std::cout << "Comando no reconocido\n";
  }

}
