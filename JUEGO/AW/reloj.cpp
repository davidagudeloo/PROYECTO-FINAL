#include "reloj.h"

int Reloj::getTiempoPartida() const
{
    return tiempoPartida;
}

void Reloj::setTiempoPartida(int value)
{
    tiempoPartida = value;
}

Reloj::Reloj(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath) : ObjetoAnimado(name, posix, posiy, w, h, numFrames, initialPath, finalPath)
{

}

void Reloj::actualizarTiempo()
{
    setTiempoPartida(getTiempoPartida()-1);
}

void Reloj::movPendundo()
{
    //longitud 1m
    /*setX(x());
    setY(y()-vely*delta+0.5*g*delta*delta);
    vely=vely-g*delta;*/
}
