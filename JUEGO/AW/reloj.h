#ifndef RELOJ_H
#define RELOJ_H

#include "objetoanimado.h"

class Reloj : public ObjetoAnimado
{
private:
    //Atributos
    int tiempoPartida=120;

public:
    //Constructor
    Reloj(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath);
    //Métodos
    void actualizarTiempo();
    void movPendundo();
    int getTiempoPartida() const;
    void setTiempoPartida(int value);
};

#endif // RELOJ_H
