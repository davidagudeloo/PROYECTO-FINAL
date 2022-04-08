#include "heroe.h"

Heroe::Heroe(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, int vidas, bool poderDisponible, int nivelActual) : ObjetoAnimado(name, posix, posiy, w, h, numFrames, initialPath, finalPath)
{
    this->vidas=vidas;
    this->poderDisponible=poderDisponible;
    this->nivelActual=nivelActual;
}
Heroe::Heroe(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath) : ObjetoAnimado(name, posix, posiy, w, h, numFrames, initialPath, finalPath)
{

}

void Heroe::actualizarPosY()
{
    setY(y()-vely*delta+0.5*g*delta*delta);
    vely=vely-g*delta;

}

