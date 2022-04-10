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
    //Atributos globales
    float delta=0.08;
    float g =12;

    //Constructor
    ObjetoAnimado(QString name, int posix, int posiy, int w, int h, int numFrames, QString initialPath, QString finalPath);

    //Métodos
    void animar();
    QString stringPath(int numFrame);

    int getWidth() const;
    int getHeight() const;
    int getPosix() const;
    int getPosiy() const;
};

#endif // OBJETOANIMADO_H
