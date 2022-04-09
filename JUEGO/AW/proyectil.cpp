#include "proyectil.h"

Proyectil::Proyectil(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, int velInical, int frecAparicion) : ObjetoAnimado(name, posix, posiy, w, h, numFrames, initialPath, finalPath)
{
    this->velInicial=velInical;
    this->frecAparicion=frecAparicion;

}

void Proyectil::MRUnivel1()
{
    setX(x()-velInicial);
    if(x()<-72){
        setPos(700,300); //Reincia la posicion del proyectil
        velInicial=3;
    }
}

void Proyectil::actualizarPosProyectil()
{
    //if que cambiará la actualizacion del proyectil dependiendo del nivel
    MRUnivel1();
}
