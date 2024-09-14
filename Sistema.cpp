#include "Sistema.h"

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
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

int Sistema::calcular_distancia(Punto punto1, Punto punto2){}

int Sistema::buscar_objeto(string nombre){// si encuentra el indice lo devuelve, si no lo encuentra devuelve -1
  int indice=-1;
  for (int i=0; i<objetos.size();i++){
    if (objetos[i]->get_nombre()==nombre){
        indice=i;
    }
  }
  return indice;
}

int Sistema::calcular_minimo(char coordenada){
    int minimo=0;
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

int Sistema::calcular_maximo(char coordenada){
    int maximo=0;
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
            Punto *vertice = new Punto(cant_puntos, coordenadas[0],coordenadas[1],coordenadas[2]);
            puntos.push_back(vertice);
            aux_vertices_objeto.push_back(vertice);
            cant_puntos++;
            contador++; // guardamos los vertices del objeto
          }
        }

     /*    cout<<"Puntos\n";
        for(int i=0; i<cant_puntos;i++){
          std::cout<< "Indice "<<puntos[i]->get_indice()<<endl;
          std::cout<< puntos[i]->get_x()<<" ";
          std::cout<< puntos[i]->get_y()<<" ";
          std::cout<< puntos[i]->get_z()<<" "<<endl;
        }
 */
       /*  cout<<"vertices\n";
        for(int i=0; i<contador;i++){
          std::cout<< "Indice "<<aux_vertices_objeto[i]->get_indice()<<endl;
          std::cout<< aux_vertices_objeto[i]->get_x()<<" ";
          std::cout<< aux_vertices_objeto[i]->get_y()<<" ";
          std::cout<< aux_vertices_objeto[i]->get_z()<<" "<<endl;
        } */



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


             /*  encontrado=false;
              std::cout<<"Indice 1 "<<aux_vertices_objeto[indice1]->get_indice()<<endl;
              std::cout<<"Indice 2 "<<aux_vertices_objeto[indice2]->get_indice()<<endl;
              for(int i=0; i<lineas.size();i++){
                
                if(lineas[i]->vertices_iguales(*aux_vertices_objeto[indice1],*aux_vertices_objeto[indice2])){
                  
                  std::cout<<"la arita se encontró, indice: "<<lineas[i]->get_indice()<<endl;
                  aux_aristas_cara.push_back(lineas[i]);
                  int encontrado2=false;
                  for(int j=0; j< aux_aristas_objeto.size(); j++){
                    if(aux_aristas_objeto[j]->vertices_iguales(*aux_vertices_objeto[indice1],*aux_vertices_objeto[indice2]))
                      encontrado2=true;
                  }
                  if(!encontrado2)
                    aux_aristas_objeto.push_back(lineas[i]);

                  encontrado=true;
                }  
              }  */

              //if(!encontrado){
                Linea *arista= new Linea(cant_lineas, aux_vertices_objeto[indice1], aux_vertices_objeto[indice2]);
                lineas.push_back(arista);
                aux_aristas_objeto.push_back(arista);
                aux_aristas_cara.push_back(arista);
                cant_lineas++;
                
              //}

              indice1=indice2;
              
            }

            /* encontrado=false;
            std::cout<<"Indice 1 "<<aux_vertices_objeto[indice2]->get_indice()<<endl;
            std::cout<<"Indice 2 "<<aux_vertices_objeto[indiceInicial]->get_indice()<<endl;
            for(int i=0; i<lineas.size();i++){
              if(lineas[i]->vertices_iguales(*aux_vertices_objeto[indice2],*aux_vertices_objeto[indiceInicial])){
                //std::cout<<"la arita se encontró, indice: "<<lineas[i]->get_indice()<<endl;
                aux_aristas_cara.push_back(lineas[i]);
                int encontrado2=false;
                for(int j=0; j< aux_aristas_objeto.size(); j++){
                  if(aux_aristas_objeto[j]->vertices_iguales(*aux_vertices_objeto[indice2],*aux_vertices_objeto[indiceInicial]))
                    encontrado2=true;
                }
                if(!encontrado2){
                  aux_aristas_objeto.push_back(lineas[i]);
                }
                encontrado=true;
              }  
            } 

            if(!encontrado){ */
              Linea *arista= new Linea(cant_lineas, aux_vertices_objeto[indice2], aux_vertices_objeto[indiceInicial]);
              lineas.push_back(arista);
              aux_aristas_objeto.push_back(arista);
              aux_aristas_cara.push_back(arista);
              cant_lineas++;
              
            //}


            Plano *cara= new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
            planos.push_back(cara);
            aux_caras_objeto.push_back(cara);
            cant_planos++;
            aux_aristas_cara.clear();
          }

        }

        /* std::cout<<"\n Lineas:\n";
        for(int i=0; i<cant_lineas;i++){
          std::cout<<lineas[i]->get_indice()<< " v1: "<<lineas[i]->get_vertice1()->get_indice() <<" v2: "<<lineas[i]->get_vertice2()->get_indice()<<endl;
        }
        std::cout<<"\n Aristas:\n";
        for(int i=0; i<aux_aristas_objeto.size();i++){
          std::cout<<aux_aristas_objeto[i]->get_indice()<< " v1: "<<aux_aristas_objeto[i]->get_vertice1()->get_indice()<<" v2: "<<aux_aristas_objeto[i]->get_vertice2()->get_indice()<<endl;
        } */

        Objeto *objeto = new Objeto(cant_objetos, nombreObjeto, aux_vertices_objeto, aux_aristas_objeto, aux_caras_objeto);
        objetos.push_back(objeto);
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
  int indice_objeto= buscar_objeto("env_global");
  vector<Punto *> aux_vertices_objeto;
  vector<Linea *> aux_aristas_objeto;
  vector<Plano *> aux_caras_objeto;
  vector<Punto *> aux_vertices_cara;
  vector<Linea *> aux_aristas_cara;

  if(objetos.size()==0){
    cout<<"Ningun objeto ha sido cargado en memoria"<<endl;
  }else{

    double xmin=calcular_minimo('x');
    double ymin=calcular_minimo('y');
    double zmin=calcular_minimo('z');
    double xmax=calcular_maximo('x');
    double ymax=calcular_maximo('y');
    double zmax=calcular_maximo('z');
;
    // creamos los puntos del objeto envolvente y los guardamos

    Punto *p0 = new Punto (cant_puntos, xmax, ymax, zmax );//pmax
    puntos.push_back(p0);
    aux_vertices_objeto.push_back(p0); 
    cant_puntos++;

    Punto *p1 = new Punto (cant_puntos, xmax, ymin, zmax );
    puntos.push_back(p1 );
    aux_vertices_objeto.push_back(p1 ); 
    cant_puntos++;

    Punto *p2 = new Punto (cant_puntos, xmin, ymin, zmax );
    puntos.push_back(p2 );
    aux_vertices_objeto.push_back(p2 ); 
    cant_puntos++;

    Punto *p3 = new Punto (cant_puntos, xmin, ymax, zmax );
    puntos.push_back(p3 );
    aux_vertices_objeto.push_back(p3 ); 
    cant_puntos++;

    Punto *p4 = new Punto (cant_puntos, xmin, ymax, zmin );
    puntos.push_back(p4 );
    aux_vertices_objeto.push_back(p4 ); 
    cant_puntos++;

    Punto *p5 = new Punto (cant_puntos, xmax, ymax, zmin );
    puntos.push_back(p5 );
    aux_vertices_objeto.push_back(p5 ); 
    cant_puntos++;

    Punto *p6 = new Punto (cant_puntos, xmax, ymin, zmin );
    puntos.push_back(p6 );
    aux_vertices_objeto.push_back(p6 ); 
    cant_puntos++;

    Punto *p7 = new Punto (cant_puntos, xmin, ymin, zmin );//pmin
    puntos.push_back(p7 );
    aux_vertices_objeto.push_back(p7 ); 
    cant_puntos++;


    // creamos las aristas necesarias 

    Linea *a0 = new Linea(cant_lineas, p0, p1);
    lineas.push_back(a0 );
    aux_aristas_objeto.push_back(a0 );
    cant_lineas++;

    Linea *a1 = new Linea(cant_lineas, p1, p2);
    lineas.push_back(a1 );
    aux_aristas_objeto.push_back(a1 );
    cant_lineas++;

    Linea *a2 = new Linea(cant_lineas, p2, p3);
    lineas.push_back(a2 );
    aux_aristas_objeto.push_back(a2 );
    cant_lineas++;

    Linea *a3 = new Linea(cant_lineas, p3, p0);
    lineas.push_back(a3 );
    aux_aristas_objeto.push_back(a3 );
    cant_lineas++;

    Linea *a4  = new Linea(cant_lineas, p2, p7);
    lineas.push_back(a4 );
    aux_aristas_objeto.push_back(a4 );
    cant_lineas++;

    Linea *a5 = new Linea(cant_lineas, p7, p6);
    lineas.push_back(a5 );
    aux_aristas_objeto.push_back(a5 );
    cant_lineas++;

    Linea *a6 = new Linea(cant_lineas, p6, p1);
    lineas.push_back(a6 );
    aux_aristas_objeto.push_back(a6 );
    cant_lineas++;

    Linea *a7 = new Linea(cant_lineas, p6, p5);
    lineas.push_back(a7 );
    aux_aristas_objeto.push_back(a7 );
    cant_lineas++;

    Linea *a8 = new Linea(cant_lineas, p5, p0);
    lineas.push_back(a8 );
    aux_aristas_objeto.push_back(a8 );
    cant_lineas++;

    Linea *a9 = new Linea(cant_lineas, p3, p4);
    lineas.push_back(a9 );
    aux_aristas_objeto.push_back(a9 );
    cant_lineas++;

    Linea *a10 = new Linea(cant_lineas, p4, p5);
    lineas.push_back(a10 );
    aux_aristas_objeto.push_back(a10 );
    cant_lineas++;

    Linea *a11 = new Linea(cant_lineas, p4, p7);
    lineas.push_back(a11 );
    aux_aristas_objeto.push_back(a11 );
    cant_lineas++;

    //Creamos las caras

    aux_aristas_cara.push_back(a0 );
    aux_aristas_cara.push_back(a1 );
    aux_aristas_cara.push_back(a2 );
    aux_aristas_cara.push_back(a3 );
    aux_vertices_cara.push_back(p0 );
    aux_vertices_cara.push_back(p1 );
    aux_vertices_cara.push_back(p2 );
    aux_vertices_cara.push_back(p3 );
    Plano *c0 =new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
    planos.push_back(c0 );
    aux_caras_objeto.push_back(c0 );
    cant_planos++;
    aux_aristas_cara.clear();
    aux_vertices_cara.clear();

    aux_aristas_cara.push_back(a1 );
    aux_aristas_cara.push_back(a4 );
    aux_aristas_cara.push_back(a5 );
    aux_aristas_cara.push_back(a6 );
    aux_vertices_cara.push_back(p1 );
    aux_vertices_cara.push_back(p2 );
    aux_vertices_cara.push_back(p7 );
    aux_vertices_cara.push_back(p6 );
    Plano *c1 =new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
    planos.push_back(c1 );
    aux_caras_objeto.push_back(c1 );
    cant_planos++;
    aux_aristas_cara.clear();
    aux_vertices_cara.clear();

    aux_aristas_cara.push_back(a0 );
    aux_aristas_cara.push_back(a6 );
    aux_aristas_cara.push_back(a7 );
    aux_aristas_cara.push_back(a8 );
    aux_vertices_cara.push_back(p0 );
    aux_vertices_cara.push_back(p1 );
    aux_vertices_cara.push_back(p6 );
    aux_vertices_cara.push_back(p5 );
    Plano *c2 =new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
    planos.push_back(c2 );
    aux_caras_objeto.push_back(c2 );
    cant_planos++;
    aux_aristas_cara.clear();
    aux_vertices_cara.clear();

    aux_aristas_cara.push_back(a3 );
    aux_aristas_cara.push_back(a9 );
    aux_aristas_cara.push_back(a10 );
    aux_aristas_cara.push_back(a8 );
    aux_vertices_cara.push_back(p0 );
    aux_vertices_cara.push_back(p3 );
    aux_vertices_cara.push_back(p4 );
    aux_vertices_cara.push_back(p5 );
    Plano *c3 =new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
    planos.push_back(c3 );
    aux_caras_objeto.push_back(c3 );
    cant_planos++;
    aux_aristas_cara.clear();
    aux_vertices_cara.clear();

    aux_aristas_cara.push_back(a2 );
    aux_aristas_cara.push_back(a9 );
    aux_aristas_cara.push_back(a11 );
    aux_aristas_cara.push_back(a4 );
    aux_vertices_cara.push_back(p2 );
    aux_vertices_cara.push_back(p3 );
    aux_vertices_cara.push_back(p4 );
    aux_vertices_cara.push_back(p7 );
    Plano *c4 =new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
    planos.push_back(c4 );
    aux_caras_objeto.push_back(c4 );
    cant_planos++;
    aux_aristas_cara.clear();
    aux_vertices_cara.clear();

    aux_aristas_cara.push_back(a10 );
    aux_aristas_cara.push_back(a7 );
    aux_aristas_cara.push_back(a5 );
    aux_aristas_cara.push_back(a11 );
    aux_vertices_cara.push_back(p4 );
    aux_vertices_cara.push_back(p5 );
    aux_vertices_cara.push_back(p6 );
    aux_vertices_cara.push_back(p7 );
    Plano *c5 =new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
    planos.push_back(c5 );
    aux_caras_objeto.push_back(c5 );
    cant_planos++;
    aux_aristas_cara.clear();
    aux_vertices_cara.clear();
    

    if(indice_objeto!=-1){
      //No esta funcionando bien (no permite cargar luego de borrar)
      Objeto *temporal = objetos[indice_objeto];
      objetos.erase(objetos.begin()+indice_objeto);
      delete temporal;
    }
      
    Objeto *envolvente= new Objeto(cant_objetos, "env_global", aux_vertices_objeto,aux_aristas_objeto,aux_caras_objeto);
    objetos.push_back(envolvente);
    cant_objetos++;
    envolvente->set_envolvente(envolvente);
    
      

    cout<< "La caja envolvente de los objetos en memoria se ha generado con el nombre env_global y se ha agregado a los objetos en memoria."<<endl;
  }
}

void Sistema::envolventeObjeto(string nombreObjeto){
  int indice_objeto= buscar_objeto(nombreObjeto);
  vector<Punto *> aux_vertices_objeto;
  vector<Linea *> aux_aristas_objeto;
  vector<Plano *> aux_caras_objeto;
  vector<Punto *> aux_vertices_cara;
  vector<Linea *> aux_aristas_cara;

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

    Punto *p0 = new Punto (cant_puntos, xmax, ymax, zmax );//pmax
    puntos.push_back(p0);
    aux_vertices_objeto.push_back(p0); 
    cant_puntos++;

    Punto *p1 = new Punto (cant_puntos, xmax, ymin, zmax );
    puntos.push_back(p1 );
    aux_vertices_objeto.push_back(p1 ); 
    cant_puntos++;

    Punto *p2 = new Punto (cant_puntos, xmin, ymin, zmax );
    puntos.push_back(p2 );
    aux_vertices_objeto.push_back(p2 ); 
    cant_puntos++;

    Punto *p3 = new Punto (cant_puntos, xmin, ymax, zmax );
    puntos.push_back(p3 );
    aux_vertices_objeto.push_back(p3 ); 
    cant_puntos++;

    Punto *p4 = new Punto (cant_puntos, xmin, ymax, zmin );
    puntos.push_back(p4 );
    aux_vertices_objeto.push_back(p4 ); 
    cant_puntos++;

    Punto *p5 = new Punto (cant_puntos, xmax, ymax, zmin );
    puntos.push_back(p5 );
    aux_vertices_objeto.push_back(p5 ); 
    cant_puntos++;

    Punto *p6 = new Punto (cant_puntos, xmax, ymin, zmin );
    puntos.push_back(p6 );
    aux_vertices_objeto.push_back(p6 ); 
    cant_puntos++;

    Punto *p7 = new Punto (cant_puntos, xmin, ymin, zmin );//pmin
    puntos.push_back(p7 );
    aux_vertices_objeto.push_back(p7 ); 
    cant_puntos++;

    // creamos las aristas necesarias 

    Linea *a0 = new Linea(cant_lineas, p0, p1);
    lineas.push_back(a0 );
    aux_aristas_objeto.push_back(a0 );
    cant_lineas++;

    Linea *a1 = new Linea(cant_lineas, p1, p2);
    lineas.push_back(a1 );
    aux_aristas_objeto.push_back(a1 );
    cant_lineas++;

    Linea *a2 = new Linea(cant_lineas, p2, p3);
    lineas.push_back(a2 );
    aux_aristas_objeto.push_back(a2 );
    cant_lineas++;

    Linea *a3 = new Linea(cant_lineas, p3, p0);
    lineas.push_back(a3 );
    aux_aristas_objeto.push_back(a3 );
    cant_lineas++;

    Linea *a4  = new Linea(cant_lineas, p2, p7);
    lineas.push_back(a4 );
    aux_aristas_objeto.push_back(a4 );
    cant_lineas++;

    Linea *a5 = new Linea(cant_lineas, p7, p6);
    lineas.push_back(a5 );
    aux_aristas_objeto.push_back(a5 );
    cant_lineas++;

    Linea *a6 = new Linea(cant_lineas, p6, p1);
    lineas.push_back(a6 );
    aux_aristas_objeto.push_back(a6 );
    cant_lineas++;

    Linea *a7 = new Linea(cant_lineas, p6, p5);
    lineas.push_back(a7 );
    aux_aristas_objeto.push_back(a7 );
    cant_lineas++;

    Linea *a8 = new Linea(cant_lineas, p5, p0);
    lineas.push_back(a8 );
    aux_aristas_objeto.push_back(a8 );
    cant_lineas++;

    Linea *a9 = new Linea(cant_lineas, p3, p4);
    lineas.push_back(a9 );
    aux_aristas_objeto.push_back(a9 );
    cant_lineas++;

    Linea *a10 = new Linea(cant_lineas, p4, p5);
    lineas.push_back(a10 );
    aux_aristas_objeto.push_back(a10 );
    cant_lineas++;

    Linea *a11 = new Linea(cant_lineas, p4, p7);
    lineas.push_back(a11 );
    aux_aristas_objeto.push_back(a11 );
    cant_lineas++;

    //Creamos las caras

    aux_aristas_cara.push_back(a0 );
    aux_aristas_cara.push_back(a1 );
    aux_aristas_cara.push_back(a2 );
    aux_aristas_cara.push_back(a3 );
    aux_vertices_cara.push_back(p0 );
    aux_vertices_cara.push_back(p1 );
    aux_vertices_cara.push_back(p2 );
    aux_vertices_cara.push_back(p3 );
    Plano *c0 =new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
    planos.push_back(c0 );
    aux_caras_objeto.push_back(c0 );
    cant_planos++;
    aux_aristas_cara.clear();
    aux_vertices_cara.clear();

    aux_aristas_cara.push_back(a1 );
    aux_aristas_cara.push_back(a4 );
    aux_aristas_cara.push_back(a5 );
    aux_aristas_cara.push_back(a6 );
    aux_vertices_cara.push_back(p1 );
    aux_vertices_cara.push_back(p2 );
    aux_vertices_cara.push_back(p7 );
    aux_vertices_cara.push_back(p6 );
    Plano *c1 =new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
    planos.push_back(c1 );
    aux_caras_objeto.push_back(c1 );
    cant_planos++;
    aux_aristas_cara.clear();
    aux_vertices_cara.clear();

    aux_aristas_cara.push_back(a0 );
    aux_aristas_cara.push_back(a6 );
    aux_aristas_cara.push_back(a7 );
    aux_aristas_cara.push_back(a8 );
    aux_vertices_cara.push_back(p0 );
    aux_vertices_cara.push_back(p1 );
    aux_vertices_cara.push_back(p6 );
    aux_vertices_cara.push_back(p5 );
    Plano *c2 =new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
    planos.push_back(c2 );
    aux_caras_objeto.push_back(c2 );
    cant_planos++;
    aux_aristas_cara.clear();
    aux_vertices_cara.clear();

    aux_aristas_cara.push_back(a3 );
    aux_aristas_cara.push_back(a9 );
    aux_aristas_cara.push_back(a10 );
    aux_aristas_cara.push_back(a8 );
    aux_vertices_cara.push_back(p0 );
    aux_vertices_cara.push_back(p3 );
    aux_vertices_cara.push_back(p4 );
    aux_vertices_cara.push_back(p5 );
    Plano *c3 =new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
    planos.push_back(c3 );
    aux_caras_objeto.push_back(c3 );
    cant_planos++;
    aux_aristas_cara.clear();
    aux_vertices_cara.clear();

    aux_aristas_cara.push_back(a2 );
    aux_aristas_cara.push_back(a9 );
    aux_aristas_cara.push_back(a11 );
    aux_aristas_cara.push_back(a4 );
    aux_vertices_cara.push_back(p2 );
    aux_vertices_cara.push_back(p3 );
    aux_vertices_cara.push_back(p4 );
    aux_vertices_cara.push_back(p7 );
    Plano *c4 =new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
    planos.push_back(c4 );
    aux_caras_objeto.push_back(c4 );
    cant_planos++;
    aux_aristas_cara.clear();
    aux_vertices_cara.clear();

    aux_aristas_cara.push_back(a10 );
    aux_aristas_cara.push_back(a7 );
    aux_aristas_cara.push_back(a5 );
    aux_aristas_cara.push_back(a11 );
    aux_vertices_cara.push_back(p4 );
    aux_vertices_cara.push_back(p5 );
    aux_vertices_cara.push_back(p6 );
    aux_vertices_cara.push_back(p7 );
    Plano *c5 =new Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
    planos.push_back(c5 );
    aux_caras_objeto.push_back(c5 );
    cant_planos++;
    aux_aristas_cara.clear();
    aux_vertices_cara.clear();
    
    Objeto *envolvente= new Objeto(cant_objetos, "env_"+nombreObjeto, aux_vertices_objeto,aux_aristas_objeto,aux_caras_objeto);
    objetos.push_back(envolvente);
    cant_objetos++;
    objetos[indice_objeto]->set_envolvente(envolvente);
    envolvente->set_envolvente(envolvente);

    cout<< " La caja envolvente del objeto "<< nombreObjeto <<" se ha generado con el nombre env_"<<nombreObjeto<<" y se ha agregado a los objetos en memoria."<<endl;

  }

}

void Sistema::descargarObjeto(string nombreObjeto){ //No esta funcionando bien
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
            }
              
          }
        }

        file<<cara<<endl;
      }
    }
    file<<"-1"<<endl;
    file.close();
    cout<<"La informacion del objeto "<<nombreObjeto<<" ha sido guardado esxitosamente en el archivo "<<nombreArchivo<<endl;

  }
  
}

void Sistema::v_cercanoObjeto(){
  std::cout<<"Comando ejecutado\n";
}

void Sistema::v_cercano(){
  std::cout<<"Comando ejecutado\n";
}

void Sistema::v_cercanos_caja(){
  std::cout<<"Comando ejecutado\n";
}

void Sistema::ruta_cortaVertices(){
  std::cout<<"Comando ejecutado\n";
}

void Sistema::ruta_cortaCentro(){
  std::cout<<"Comando ejecutado\n";
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
