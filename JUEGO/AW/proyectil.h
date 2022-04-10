#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "objetoanimado.h"
#include "heroe.h"

class Proyectil : public ObjetoAnimado
{
private:
    int velInicial; //velocidad inicial del proyectil
    int frecAparicion; //frecuencia de aparicion del proyectil

public:
    //constructor
    Proyectil(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, int velInical, int frecAparicion);

    //Métodos
    void actualizarPosProyectil(Heroe * heroe); //Cambia el movimiento del proyectil dependiendo del nivel
    void MRUnivel1(Heroe * heroe);
    void colisionProyectilHeroe(Heroe * heroe);
    void MParabolicoNivel2();//no se ha hecho
};


#endif // PROYECTIL_H
