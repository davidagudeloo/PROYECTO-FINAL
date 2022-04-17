#include "archivoinformacion.h"

bool ArchivoInformacion::getSeQuiereCargar() const
{
    return seQuiereCargar;
}

void ArchivoInformacion::setSeQuiereCargar(bool value)
{
    seQuiereCargar = value;
}

ArchivoInformacion::ArchivoInformacion()
{
    
}

//Cargar
void ArchivoInformacion::leerDatos(string name, Heroe * heroe, Reloj * reloj)
{
    ifstream archivo; // tipo de dato que me permite leer un archivo
    string linea;
    archivo.open(name,ios::in); // abrimos el archivo en modo lectura

    getline(archivo,linea);
    heroe->setNivelActual(stoi(linea)); //stoi=string to int
    getline(archivo,linea);
    heroe->setVidas(stoi(linea));
    getline(archivo,linea);
    reloj->setTiempoPartida(stoi(linea));

    archivo.close(); // Cerramos el archivo
}

//Guardar
void ArchivoInformacion::escribirDatos(string name, Heroe * heroe, Reloj * reloj)
{
    ofstream archivo; // tipo de dato que me permite escribir un archivo
    archivo.open(name.c_str(),ios::out); // abrimos el archivo en modo escritura

    archivo<<heroe->getNivelActual()<<"\n"<<heroe->getVidas()<<"\n"<<reloj->getTiempoPartida();
    archivo.close();
}
