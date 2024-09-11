#include "Sistema.h"

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
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

int Sistema::buscar_objeto(string nombre){}

void Sistema::cargarArchivo(){
  cout<<"Comando ejecutado\n";
}

void Sistema::listado(){
  cout<<"Comando ejecutado\n";
}

void Sistema::envolvente(){
  cout<<"Comando ejecutado\n";
}

void Sistema::envolventeObjeto(){
  cout<<"Comando ejecutado\n";
}


void Sistema::descargarObjeto(){
  cout<<"Comando ejecutado\n";
}

void Sistema::guardarObjetoArchivo(){
  cout<<"Comando ejecutado\n";
  
}

void Sistema::v_cercanoObjeto(){
  cout<<"Comando ejecutado\n";
}

void Sistema::v_cercano(){
  cout<<"Comando ejecutado\n";
}

void Sistema::v_cercanos_caja(){
  cout<<"Comando ejecutado\n";
}

void Sistema::ruta_cortaVertices(){
  cout<<"Comando ejecutado\n";
}

void Sistema::ruta_cortaCentro(){
  cout<<"Comando ejecutado\n";
}



void Sistema::ayuda(){

  cout<<"lista de comandos: "<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"cargar nombre_archivo"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"listado"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"envolvente nombre_objeto"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"envolvente"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"descargar nombre_objeto"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"guardar nombre_objeto nombre_archivo"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"v_cercano px py pz nombre_objeto"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"v_cercano px py pz"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"v_cercanos_caja nombre_objeto"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"ruta_corta i1 i2 nombre_objeto"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"ruta_corta_centro i1 nombre_objeto"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"salir"<<endl<<endl;


}

void Sistema::ayudaComando(string comando){
  if (strcmp(comando.c_str(), "cargar") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"cargar nombre_archivo"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"Carga en memoria la información del objeto nombre_objeto contenida en el archivo identificado por nombre_archivo."<<endl;
    cout<<"------------------------------------------------"<<endl;

  } else if (strcmp(comando.c_str(), "listado") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"listado"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"Lista los objetos cargados actualmente en memoria, junto con la información básica de cada uno: cantidad de puntos, de aristas y de caras."<<endl;
    cout<<"------------------------------------------------"<<endl;

  } else if (strcmp(comando.c_str(), "envolvente") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"envolvente nombre_objeto"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<" Calcula la caja envolvente del objeto identificado por nombre_objeto. La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_nombre_objeto, para distinguirla de los demás objetos en memoria"<<endl;
    cout<<"------------------------------------------------"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"envolvente"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<" La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_nombre_objeto, para distinguirla de los demás objetos en memoria. La caja envolvente se agrega como un nuevo objeto en memoria, asignándole automáticamente el nombre env_global, para distinguirla de los demás objetos en memoria"<<endl;
    cout<<"------------------------------------------------"<<endl;


  } else if (strcmp(comando.c_str(), "descargar") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"descargar nombre_objeto"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<" Descarga de la memoria toda la información básica (vértices, aristas, caras) del objeto identificado por nombre_objeto"<<endl;
    cout<<"------------------------------------------------"<<endl;


  } else if (strcmp(comando.c_str(), "guardar") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"guardar nombre_objeto nombre_archivo"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"Escribe en un archivo de texto, identificado por nombre_archivo, la información básica (vértices y caras) del objeto identificado por nombre_objeto"<<endl;
    cout<<"------------------------------------------------"<<endl;


  } else if (strcmp(comando.c_str(), "v_cercano") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"v_cercano px py pz nombre_objeto"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"  Identifica el vértice del objeto nombre_objeto más cercano (en términos de la distancia euclidiana) al punto indicado por las coordenadas px, py y pz. Informa en pantalla el índice del vértice, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra del punto dado"<<endl;
    cout<<"------------------------------------------------"<<endl<<endl;

    cout<<"------------------------------------------------"<<endl;
    cout<<"v_cercano px py pz"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"  Identifica, entre todos los objetos cargados en memoria, el vértice más cercano (en términos de la distancia euclidiana) al punto indicado por las coordenadas px, py y pz. Informa en pantalla el objeto al que pertenece, el índice del vértice, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra del punto dado"<<endl;
    cout<<"------------------------------------------------"<<endl;

  } else if (strcmp(comando.c_str(), "v_cercanos_caja") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"v_cercanos_caja nombre_objeto"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"Identifica los vértices del objeto nombre_objeto más cercanos (en términos de la distancia euclidiana) a los puntos (vértices) que definen la respectiva caja envolvente del objeto. Informa en pantalla, en una tabla, las coordenadas de cada una de las esquinas de la caja envolvente, y para cada una de ellas, el índice del vértice más cercano, los valores actuales de sus coordenadas, y la distancia a la cual se encuentra de la respectiva esquina"<<endl;
    cout<<"------------------------------------------------"<<endl;

  } else if (strcmp(comando.c_str(), "ruta_corta") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"ruta_corta i1 i2 nombre_objeto"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"Identifica los índices de los vértices que conforman la ruta más corta entre los vértices dados para el objeto nombre_objeto. La distancia entre los vértices está medida en términos de la distancia euclidiana. Informa, además, la distancia total de la ruta calculada"<<endl;
    cout<<"------------------------------------------------"<<endl;


  } else if (strcmp((comando).c_str(), "ruta_corta_centro") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"ruta_corta_centro i1 nombre_objeto"<<endl<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<" Identifica los índices de los vértices que conforman la ruta más corta entre el vértice dado y el centro del objeto nombre_objeto. La distancia entre los vértices está medida en términos de la distancia euclidiana. Informa, además, la distancia total de la ruta calculada."<<endl;
    cout<<"------------------------------------------------"<<endl;

  } else if (strcmp((comando).c_str(), "salir") == 0) {
    cout<<"------------------------------------------------"<<endl;
    cout<<"salir"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"Termina la ejecución de la aplicación."<<endl;
    cout<<"------------------------------------------------"<<endl;

  }else {
    cout << "Comando no reconocido\n";
  }

}
