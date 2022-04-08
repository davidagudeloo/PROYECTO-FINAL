#include "objetoanimado.h"

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

void ObjetoAnimado::animar(ObjetoAnimado * clase)
{
    qDebug() << "funciona";
    clase->setPixmap(QPixmap(stringPath(actualFrame, clase)).scaled(clase->width, clase->height));
    clase->actualFrame++;
    if(clase->actualFrame==clase->numFrames){
        clase->actualFrame=0;
    }
}

QString ObjetoAnimado::stringPath(int numFrame, ObjetoAnimado * clase)
{
    QString path = clase->initialPath;
    path += QString::number(numFrame);
    path += clase->finalPath;
    return path;
}
