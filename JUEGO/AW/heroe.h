#ifndef HEROE_H
#define HEROE_H

#include "objetoanimado.h"

class Heroe : public ObjetoAnimado
{
private:
    //Atributos
    int vidas=3;
    bool poderDisponible=false;
    int nivelActual=1;
    bool isDead=false;

public:
    //Atributos globales
    float vely=60;
    bool estaSaltando=false;
    bool estaAgachado=false;

    //Constructor
    Heroe(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, int vidas, bool poderDisponible, int nivelActual);
    Heroe(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath);

    //Métodos
    void actualizarPosY();
    void setVidas(int value);
    int getVidas() const;
    bool getIsDead() const;
    void setIsDead(bool value);
    int getNivelActual() const;
    void setNivelActual(int value);
};

#endif // HEROE_H
