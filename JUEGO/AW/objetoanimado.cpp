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


ObjetoAnimado::ObjetoAnimado(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath)
{
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
    //qDebug() << "funciona";
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
