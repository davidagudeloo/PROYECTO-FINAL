#ifndef HEROE_H
#define HEROE_H

#include "objetoanimado.h"

class Heroe : public ObjetoAnimado
{
private:
    //Atributos
    int vidas=3;
    bool poderDisponible=false;
    int nivelActual=1;

public:
    //Atributos globales
    float vely=40;
    bool estaSaltando=false;

    //Constructor
    Heroe(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, int vidas, bool poderDisponible, int nivelActual);
    Heroe(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath);

    //Métodos
    void actualizarPosY();
};

#endif // HEROE_H
