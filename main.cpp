#include "Sistema.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

int main()
{
    Sistema sistema;
    string opcion;
    string entrada;
    int numtokes = 0;
    int index = 0;
    bool comandoValido = true;
    bool salir = false;
    string tokenss;
    do
    {
        comandoValido = true;
        cout << "$ ";
        getline(cin, entrada);
        //-------------------------------distribucion de tokens----------------------------------
        char *c_entrada = new char[entrada.size() + 1];
        strcpy(c_entrada, entrada.c_str());

        // Contar los tokens
        char *token = strtok(c_entrada, " ");
        while (token != nullptr)
        {
            numtokes++;
            token = strtok(nullptr, " ");
        }

        // Crear un array para almacenar los tokens
        string *tokens = new string[numtokes];
        strcpy(c_entrada, entrada.c_str());

        token = strtok(c_entrada, " ");
        index = 0; // Resetear el índice para la segunda pasada
        while (token != nullptr)
        {
            tokens[index] = token;
            index++;
            token = strtok(nullptr, " ");
        }
        //--------------------------------final de distribucion de tokens------------------------

        //--------------------------------inicio menu--------------------------------------------
        if (strcmp(tokens[0].c_str(), "ayuda") == 0)
        {
            if (index == 1)
            {
                sistema.ayuda();
            }
            else if (index == 2)
            {
                sistema.ayudaComando(tokens[1]);
            }
        }
        else if (strcmp(tokens[0].c_str(), "cargar") == 0)
        {
            if (index == 2)
            {
                sistema.cargarArchivo(tokens[1]);
            }
            else
            {
                comandoValido = false;
            }
        }
        else if (strcmp(tokens[0].c_str(), "listado") == 0)
        {
            if (index == 1)
            {
                sistema.listado();
            }
            else
            {
                comandoValido = false;
            }
        }
        else if (strcmp(tokens[0].c_str(), "envolvente") == 0)
        {
            if (index == 1)
            {
                sistema.envolvente();
            }
            else if (index == 2)
            {
                sistema.envolventeObjeto(tokens[1]);
            }
            else
            {
                comandoValido = false;
            }
        }
        else if (strcmp(tokens[0].c_str(), "descargar") == 0)
        {
            if (index == 2)
            {
                sistema.descargarObjeto(tokens[1]);
            }
            else
            {
                comandoValido = false;
            }
        }
        else if (strcmp(tokens[0].c_str(), "guardar") == 0)
        {
            if (index == 3)
            {
                sistema.guardarObjetoArchivo(tokens[1], tokens[2]);
            }
            else
            {
                comandoValido = false;
            }
        }
        else if (strcmp(tokens[0].c_str(), "v_cercano") == 0)
        {
            if (index == 5)
            {
                sistema.v_cercanoObjeto(tokens[1],tokens[2],tokens[3],tokens[4]);
            }
            else if (index == 4)
            {
                sistema.v_cercano(tokens[1],tokens[2],tokens[3]);
            }
            else
            {
                comandoValido = false;
            }
        }
        else if (strcmp(tokens[0].c_str(), "v_cercanos_caja") == 0)
        {
            if (index == 2)
            {
                sistema.v_cercanos_caja(tokens[1]);
            }
            else
            {
                comandoValido = false;
            }
        }
        else if (strcmp(tokens[0].c_str(), "ruta_corta") == 0)
        {
            if (index == 4)
            {
                sistema.ruta_cortaVertices();
            }
            else
            {
                comandoValido = false;
            }
        }
        else if (strcmp(tokens[0].c_str(), "ruta_corta_centro") == 0)
        {
            if (index == 3)
            {
                sistema.ruta_cortaCentro();
            }
            else
            {
                comandoValido = false;
            }
        }
        else if (strcmp(tokens[0].c_str(), "salir") == 0)
        {
            salir = true;
        }
        else
        {
            cout << "Comando no reconocido\n";
        }

        if (!comandoValido)
        {
            cout << "\nError en el comando\n";
        }
        //--------------------------------fin menu-----------------------------------------------

        tokenss = tokens[0];

        delete[] c_entrada;
        delete[] tokens;
        numtokes = 0;

    } while (!salir);

    return 0;
}
