#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "objetoanimado.h"
#include "heroe.h"
#include "math.h"
#include <cstdlib> //random
#include <time.h>  //para asegurar que se tenga un valor aleatorio

class Proyectil : public ObjetoAnimado
{
private:
    int velInicial; //velocidad inicial del proyectil
    int frecAparicion; //frecuencia de aparicion del proyectil

    float velResorte=40;
    float ang=45*(M_PI/180);
public:
    //constructor
    Proyectil(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, int velInical, int frecAparicion);

    //Métodos
    void actualizarPosProyectil(Heroe * heroe); //Cambia el movimiento del proyectil dependiendo del nivel
    void MRUnivel1(Heroe * heroe);
    void colisionProyectilHeroe(Heroe * heroe);
    void MParabolicoNivel2(Heroe * heroe);//no se ha hecho
};


#endif // PROYECTIL_H
