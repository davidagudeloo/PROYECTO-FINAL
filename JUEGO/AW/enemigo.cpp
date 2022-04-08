#include "enemigo.h"

Enemigo::Enemigo(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath, int nivelDeDificultad) : ObjetoAnimado(name, posix, posiy, w, h, numFrames, initialPath, finalPath)
{
    this->nivelDeDificultad=nivelDeDificultad;
}

Enemigo::Enemigo(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath) : ObjetoAnimado(name, posix, posiy, w, h, numFrames, initialPath, finalPath)
{

}
