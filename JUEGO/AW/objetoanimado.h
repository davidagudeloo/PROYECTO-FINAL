#ifndef OBJETOANIMADO_H
#define OBJETOANIMADO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QTimer>
#include <QDebug>

class ObjetoAnimado : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    //Atributos
    int posix;
    int posiy;
    int width;
    int height;
    int numFrames; //Atributo para animar a los objetos
    int actualFrame=0;
    QString initialPath;
    QString finalPath;

public:
    //Constructor
    ObjetoAnimado(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath);

    //Métodos
    void animar(ObjetoAnimado * clase);
    QString stringPath(int numFrame, ObjetoAnimado * clase);

};

#endif // OBJETOANIMADO_H
