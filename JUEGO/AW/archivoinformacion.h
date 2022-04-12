#ifndef ARCHIVOINFORMACION_H
#define ARCHIVOINFORMACION_H
#include <stdlib.h> // libreria estandar. para el exit por ejemplo
#include <fstream> // flujo de entrada y salida hacia archivos
#include <string.h> // trabajar con strings
#include <stdlib.h> // libreria estandar. para el exit por ejemplo
#include <heroe.h>
#include <reloj.h>
#include <fstream>

using namespace std;


class ArchivoInformacion
{

public:
    bool seQuiereCargar=false;
    ArchivoInformacion();
    void leerDatos(string texto, Heroe * heroe, Reloj * reloj);
    void escribirDatos(string name, Heroe * heroe, Reloj * reloj);


};

#endif // ARCHIVOINFORMACION_H
