#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "objetoanimado.h"

class Enemigo : public ObjetoAnimado
{
private:
    //Atributos
    int nivelDeDificultad;

public:
    //Constructor
    Enemigo(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, int nivelDeDificultad);
    Enemigo(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath);

};

#endif // ENEMIGO_H
