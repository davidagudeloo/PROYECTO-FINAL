#ifndef RELOJ_H
#define RELOJ_H

#include "objetoanimado.h"
#include <math.h>

class Reloj : public ObjetoAnimado
{
private:
    //Atributos
    int tiempoPartida=40;


    float posA[2]; //coordenada (x,y) del inicio del péndulo
    float posB[2]; //coordenada (x,y) del final del péndulo
    float L; //largo del pendulo
    float anguloInicial;
    int tiempoms=1000;

public:
    //Constructor
    Reloj(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath);

    //Constructor del pendulo
    Reloj(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, float x, float y, float L, float anguloInicial);


    //Métodos
    void actualizarTiempo();
    void movPendulo();
    int getTiempoPartida() const;
    void setTiempoPartida(int value);
};

#endif // RELOJ_H
