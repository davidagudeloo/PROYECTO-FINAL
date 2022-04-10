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

Reloj::Reloj(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, float posA, float posB, float L, float angulo) : ObjetoAnimado(name, posix, posiy, w, h, numFrames, initialPath, finalPath)
{
    this->posA[0]=posA;
    this->posA[1]=posB;
    this->L=L;
    this->angulo=angulo;

    this->posB[0]=this->posA[0]+L*sin(angulo);
    this->posB[1]=this->posA[1]-L*cos(angulo);

}

void Reloj::actualizarTiempo()
{
    setTiempoPartida(getTiempoPartida()-1);
}

void Reloj::movPendulo()
{
    /*timerpendulo = new QTimer;
    connect(timerpendulo, SIGNAL(timeout()), this, SLOT(animarFondo()));
    float w=sqrt(9.8/L);
    float angulo=this->angulo*cos(w*tiempo/1000);

    //longitud 1m
    setX(x());
    setY(y()-vely*delta+0.5*g*delta*delta);
    vely=vely-g*delta;*/
}







