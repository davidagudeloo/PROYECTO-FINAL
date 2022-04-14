#ifndef HEROE_H
#define HEROE_H

#include "objetoanimado.h"

class Heroe : public ObjetoAnimado
{
private:
    //Atributos
    int vidas=3;
    bool poderDisponible=true;//false
    int nivelActual=1;
    bool isDead=false;
    bool estaSaltando=false;

public:
    //Atributos globales
    float vely=60;
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
    bool getPoderDisponible() const;
    void setPoderDisponible(bool value);
    bool getEstaSaltando() const;
    void setEstaSaltando(bool value);
};

#endif // HEROE_H
