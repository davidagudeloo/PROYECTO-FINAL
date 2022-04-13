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

Reloj::Reloj(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, float x, float y, float L, float anguloInicial) : ObjetoAnimado(name, posix, posiy, w, h, numFrames, initialPath, finalPath)
{
    this->posA[0]=x;//inicial
    this->posA[1]=y;
    this->L=L;
    this->anguloInicial=anguloInicial;

    this->posB[0]=this->posA[0]+L*sin(anguloInicial);
    this->posB[1]=this->posA[1]-L*cos(anguloInicial);

}

void Reloj::actualizarTiempo()
{
    setTiempoPartida(getTiempoPartida()-1);
}

void Reloj::movPendulo()
{

    float w=sqrt(9.8/L);
    float angulo=anguloInicial*cos(w*tiempoms/1000);

    posB[0]=posA[0]+L*sin(angulo*(M_PI/180));
    posB[1]=posA[1]+L*cos(angulo*(M_PI/180));
    setPos(posB[0],posB[1]);

    tiempoms+=1000;
}







