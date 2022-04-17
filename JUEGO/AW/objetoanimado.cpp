#include "objetoanimado.h"

int ObjetoAnimado::getWidth() const
{
    return width;
}

int ObjetoAnimado::getHeight() const
{
    return height;
}

int ObjetoAnimado::getPosix() const
{
    return posix;
}

int ObjetoAnimado::getPosiy() const
{
    return posiy;
}


int ObjetoAnimado::getNumFrames() const
{
    return numFrames;
}

int ObjetoAnimado::getActualFrame() const
{
    return actualFrame;
}

void ObjetoAnimado::setPosix(int value)
{
    posix = value;
}

void ObjetoAnimado::setPosiy(int value)
{
    posiy = value;
}

ObjetoAnimado::ObjetoAnimado(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath)
{
    this->name=name;
    setPixmap(QPixmap(name).scaled(w,h));
    this->posix=posix;
    this->posiy=posiy;
    setPos(posix,posiy);
    this->width=w;
    this->height=h;
    this->numFrames=numFrames;
    this->initialPath=initialPath;
    this->finalPath=finalPath;
}

void ObjetoAnimado::animar()
{
    setPixmap(QPixmap(stringPath(actualFrame)).scaled(width, height));
    actualFrame++;
    if(actualFrame==numFrames){
        actualFrame=0;
    }
}

QString ObjetoAnimado::stringPath(int numFrame)
{
    QString path = initialPath;
    path += QString::number(numFrame);
    path += finalPath;
    return path;
}

void ObjetoAnimado::setImagen(QString name)
{
    setPixmap(QPixmap(name).scaled(getWidth(),getHeight()));
}
