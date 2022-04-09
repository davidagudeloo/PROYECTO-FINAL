#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "objetoanimado.h"

class Proyectil : public ObjetoAnimado
{
private:
    int velInicial; //velocidad inicial del proyectil
    int frecAparicion; //frecuencia de aparicion del proyectil

public:
    //constructor
    Proyectil(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, int velInical, int frecAparicion);

    //Métodos
    void actualizarPosProyectil(); //Cambia el movimiento del proyectil dependiendo del nivel
    void colisionProyectilHeroe();
    void MParabolicoNivel2();
    void MRUnivel1();
};


#endif // PROYECTIL_H
