#include "heroe.h"

void Heroe::setVidas(int value)
{
    vidas = value;
}

int Heroe::getVidas() const
{
    return vidas;
}

bool Heroe::getIsDead() const
{
    return isDead;
}

void Heroe::setIsDead(bool value)
{
    isDead = value;
}

int Heroe::getNivelActual() const
{
    return nivelActual;
}

void Heroe::setNivelActual(int value)
{
    nivelActual = value;
}

bool Heroe::getPoderDisponible() const
{
    return poderDisponible;
}

void Heroe::setPoderDisponible(bool value)
{
    poderDisponible = value;
}

bool Heroe::getEstaSaltando() const
{
    return estaSaltando;
}

void Heroe::setEstaSaltando(bool value)
{
    estaSaltando = value;
}

void Heroe::setVely(float value)
{
    vely = value;
}

Heroe::Heroe(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath) : ObjetoAnimado(name, posix, posiy, w, h, numFrames, initialPath, finalPath)
{

}

void Heroe::actualizarPosY()
{
    setY(y()-vely*delta+0.5*g*delta*delta); //Ecuación de movimiento
    vely=vely-g*delta;
}

