#include "proyectil.h"

Proyectil::Proyectil(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, int velInical, int frecAparicion) : ObjetoAnimado(name, posix, posiy, w, h, numFrames, initialPath, finalPath)
{
    this->velInicial=velInical;
    this->frecAparicion=frecAparicion;

}

void Proyectil::MRUnivel1(Heroe * heroe)
{
    colisionProyectilHeroe(heroe);
    setX(x()-velInicial);
    if(x()<-72){
        setPos(getPosix(), getPosiy()); //Reincia la posicion del proyectil
        velInicial=5;
    }

}

void Proyectil::actualizarPosProyectil(Heroe * heroe)
{
    //if que cambiará la actualizacion del proyectil dependiendo del nivel
    MRUnivel1(heroe);
}

void Proyectil::colisionProyectilHeroe(Heroe * heroe)
{
    if(collidesWithItem(heroe)){
        heroe->setVidas(heroe->getVidas()-1);
        if(heroe->getVidas()<=0){
            heroe->setIsDead(true);
        }
        setPos(getPosix(),getPosiy());
    }
}
