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

int Sistema::buscar_objeto(string nombre){
  int indice=-1;
  for (int i=0; i<cant_objetos;i++){
    if (objetos[i].get_nombre()==nombre){
        indice=i;
    }
  }
  return indice;
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

  ifstream archivo(nombreArchivo.c_str());
    
  if (!archivo.is_open()) {
      std::cout << "El archivo " <<nombreArchivo<< " no existe o es ilegible" << endl;
  }else{
  
    string linea;
    getline(archivo,linea);
    nombreObjeto=linea;
    if(buscar_objeto(nombreObjeto)!=-1){
      std::cout<<"El objeto "<< nombreObjeto << "ya ha sido cargado en memoria"<< endl;
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
            Punto vertice= Punto(cant_puntos, coordenadas[0],coordenadas[1],coordenadas[2]);
            puntos.push_back(vertice);
            cant_puntos++;
            aux_vertices_objeto.push_back(&vertice);
            contador++; // guardamos los vertices del objeto
          }
        }




        while(getline(archivo, linea)){ // leemos las lineas que tienen los datos de las caras
          if(linea=="-1"){
            fin_archivo=true;
          }else{

            string scantvertice;
            string svertice1;
            string svertice2;
            int indice1=0;
            int indice2=0;
            int indiceInicial=0;
            aux_aristas_cara.clear();

            stringstream input_stringstream(linea);
            getline(input_stringstream, scantvertice, ' '); //leemos la cantidad de vertices que tiene la cara 
            cant_vertices_cara=stoi(scantvertice);
            getline(input_stringstream, svertice1, ' '); // leemos el primer indice 
            indice1=stoi(svertice1);
            indiceInicial=indice1;
            aux_vertices_cara.push_back(aux_vertices_objeto[indice1]); // guardamos en los vertices de la cara

            for(int i=0; i<cant_vertices_cara-1 ; i++){
              getline(input_stringstream, svertice2, ' ');
              indice2=stoi(svertice2);
              aux_vertices_cara.push_back(aux_vertices_objeto[indice2]); // guardamos los vertices de la cara
              Linea arista= Linea(cant_lineas, aux_vertices_objeto[indice1], aux_vertices_objeto[indice2]);
              lineas.push_back(arista);
              cant_lineas++;
              aux_aristas_objeto.push_back(&arista);
              aux_aristas_cara.push_back(&arista);
              indice1=indice2;
            }
            Linea arista= Linea(cant_lineas, aux_vertices_objeto[indice2], aux_vertices_objeto[indiceInicial]);
            lineas.push_back(arista);
            cant_lineas++;
            aux_aristas_objeto.push_back(&arista);
            aux_aristas_cara.push_back(&arista);
            Plano cara=Plano(cant_planos, aux_aristas_cara, aux_vertices_cara);
            planos.push_back(cara);
            cant_planos++;
            aux_caras_objeto.push_back(&cara);
            aux_aristas_cara.clear();
          }

        }

        Objeto objeto = Objeto(cant_objetos, nombreObjeto, aux_vertices_objeto, aux_aristas_objeto, aux_caras_objeto);
        objetos.push_back(objeto);
        cant_objetos++;
        
      }
      catch (exception &e){
        archivo_correcto=false;
      }
    }

    archivo.close();

    if(archivo_correcto){
      std::cout<< "El objeto " <<objetos[cant_objetos-1].get_nombre() << " ha sido cargado exitosamente desde el archivo "<< nombreArchivo<<endl;
    }else{
      std::cout<< "El archivo "<<nombreArchivo<< "no contiene un objeto 3D valido"<<endl;
    }
  }
  
}

void Sistema::listado(){
  std::cout<<"Comando ejecutado\n";
}

void Sistema::envolvente(){
  std::cout<<"Comando ejecutado\n";
}

void Sistema::envolventeObjeto(){
  std::cout<<"Comando ejecutado\n";
}


void Sistema::descargarObjeto(){
  std::cout<<"Comando ejecutado\n";
}

void Sistema::guardarObjetoArchivo(){
  std::cout<<"Comando ejecutado\n";
  
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
