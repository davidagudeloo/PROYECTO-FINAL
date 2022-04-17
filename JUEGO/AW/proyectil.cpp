#include "proyectil.h"

Proyectil::Proyectil(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath) : ObjetoAnimado(name, posix, posiy, w, h, numFrames, initialPath, finalPath)
{

}

void Proyectil::actualizarPosProyectil(Heroe * heroe)
{
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
        if(heroe->getVidas()>0){
            heroe->setVidas(heroe->getVidas()-1);
        }
        if(heroe->getVidas()<=0){
            heroe->setIsDead(true);
        }
        //Si colisiona, retorna a su posición inicial
        setPos(getPosix(),getPosiy());
    }
}

void Proyectil::MRUnivel1(Heroe * heroe)
{
    colisionProyectilHeroe(heroe);
    setX(x()-velInicial);
    //Si la bala sale de la pantalla
    if(x()< 0 - getWidth()){
        setPos(getPosix(), getPosiy()); //Reincia la posicion del proyectil
        velInicial=(rand()%7+4); //varía de 4 a 11
    }
}

void Proyectil::MParabolicoNivel2(Heroe * heroe)
{
    colisionProyectilHeroe(heroe);
    //Las ecuaciones dependerán de la vel inicial dada por el resorte
    float velx=velResorte*cos(ang);
    float vely=velResorte*sin(ang)-g*delta;
    velResorte=sqrt((velx*velx)+(vely*vely));
    ang=atan2(vely, velx);
    setX(x()-velx*delta);
    setY(y()-vely*delta+0.5*g*delta*delta);
    if(y()>heroe->getPosiy()+200){
        setPos(getPosix(), getPosiy()); //Reincia la posicion del proyectil
        ang=75*(M_PI/180); //pasa el ángulo a grados
        velResorte=velocidadInicialResorte();
    }
}

float Proyectil::velocidadInicialResorte()
{
    float velResorte=0;
    float m=0.01, k=800, y1, y2=1; //y2 es la longitud del resorte (1m), k es la constante elástica, m la masa del proyectil (0.01kg)
    float x = 29+(rand()%(59-29)); //Dará número aleatorios entre 29 y 58(cm).
    x=x/100; //El resorte se comprimirá máximo hasta 0.42m de su longitud
    y1 = y2-x;
    velResorte=sqrt(2*g*y1+(k*pow(x,2))/m);
    return velResorte;
}
