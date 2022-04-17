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
    int velInicial; //velocidad inicial del proyectil NIVEL 1
    float velResorte=40; //velocidad inicial del proyectil NIVEL 2
    float ang=45*(M_PI/180); //Se convierte de radianes a grados

public:
    //constructor
    Proyectil(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath);

    //Métodos
    void actualizarPosProyectil(Heroe * heroe); //Cambia el movimiento del proyectil dependiendo del nivel
    void colisionProyectilHeroe(Heroe * heroe); //Verifica la colisión entre el proyectil y el héroe
    void MRUnivel1(Heroe * heroe);
    void MParabolicoNivel2(Heroe * heroe);
    float velocidadInicialResorte();
};


#endif // PROYECTIL_H
