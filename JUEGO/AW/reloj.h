#ifndef RELOJ_H
#define RELOJ_H

#include "objetoanimado.h"
#include <math.h>

class Reloj : public ObjetoAnimado
{
private:
    //Atributos
    int tiempoPartida=120;


    float posA[2]; //coordenada (x,y) del inicio del péndulo
    float posB[2]; //coordenada (x,y) del final del péndulo
    float L; //largo del pendulo
    float angulo;

public:
    //Constructor
    Reloj(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath);

    //Constructor del pendulo
    Reloj(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, float posA, float posB, float L, float angulo);


    //Métodos
    void actualizarTiempo();
    void movPendulo();
    int getTiempoPartida() const;
    void setTiempoPartida(int value);
};

#endif // RELOJ_H
