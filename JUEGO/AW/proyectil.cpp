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
    if(x()< -getWidth()){
        setPos(getPosix(), getPosiy()); //Reincia la posicion del proyectil
        velInicial=(rand()%7+4);
    }

}

void Proyectil::actualizarPosProyectil(Heroe * heroe)
{
    //if que cambiará la actualizacion del proyectil dependiendo del nivel
    if(heroe->getNivelActual()==1){
        MRUnivel1(heroe);
    }
    else{
        MParabolicoNivel2(heroe);
    }

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

void Proyectil::MParabolicoNivel2(Heroe * heroe)
{
    colisionProyectilHeroe(heroe);
    float velx=velResorte*cos(ang);
    float vely=velResorte*sin(ang)-g*delta;
    velResorte=sqrt((velx*velx)+(vely*vely));
    ang=atan2(vely, velx);
    setX(x()-velx*delta);
    setY(y()-vely*delta+0.5*g*delta*delta);
    if(y()>heroe->getPosiy()+200){
        setPos(getPosix(), getPosiy()); //Reincia la posicion del proyectil
        ang=45*(M_PI/180); //pasa el ángulo a grados
        velResorte=velocidadInicialResorte();
        qDebug() << velResorte;

    }
}

float Proyectil::velocidadInicialResorte()
{
    float velResorte=0;
    float m=0.01, k=800, y1, y2=1; //y2 es la longitud del resorte (1m), k es la constante elástica, m la masa del proyectil (0.01kg)
    srand(time(NULL));
    float x = 1+(rand()%(50)); //Dará número aleatorios entre 1 y 50.
    x=x/100; //El resorte se comprimirá máximo hasta la mitad (0.5m)
    y1 = y2-x;
    velResorte=sqrt(2*g*y1+(k*pow(x,2))/m);
    qDebug()<<x;

    return velResorte;
}









