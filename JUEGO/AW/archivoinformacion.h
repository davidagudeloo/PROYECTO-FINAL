#ifndef ARCHIVOINFORMACION_H
#define ARCHIVOINFORMACION_H
#include <stdlib.h> // libreria estandar
#include <fstream> // flujo de entrada y salida hacia archivos
#include <string.h> // trabajar con strings
#include <heroe.h>
#include <reloj.h>

using namespace std;


class ArchivoInformacion
{
private:
    //Atributos
    bool seQuiereCargar=false;

public:
    //Constructor
    ArchivoInformacion();

    //Métodos
    void cargarDatos(string texto, Heroe * heroe, Reloj * reloj);
    void guardarDatos(string name, Heroe * heroe, Reloj * reloj);

    bool getSeQuiereCargar() const;
    void setSeQuiereCargar(bool value);
};

#endif // ARCHIVOINFORMACION_H
