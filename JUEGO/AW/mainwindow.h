#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"
#include <QKeyEvent>
#include "objetoanimado.h"
#include "heroe.h"
#include "proyectil.h"
#include "enemigo.h"
#include "reloj.h"
#include <QTimer>
#include "archivoinformacion.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void animarHeroe();
    void animarFondo();
    void animarProyectil();
    void animarEnemigo();
    void animarTeleport();
    void animarPantallaCarga1();

    void contarSegundos();

public:
    void keyPressEvent(QKeyEvent * i);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    ifstream myfile; //Dato que nos permite verificar si existe un archivo
    int pantallaDeCarga=0;

    Ui::MainWindow *ui;
    QGraphicsScene * escena;


    //Creación de objetos
    Heroe * heroeAux;
    ArchivoInformacion * archivo;
    ObjetoAnimado * pantallaCarga1;

    Heroe * heroe;
    ObjetoAnimado * fondo;
    ObjetoAnimado * piso;
    Proyectil * bala[4];
    Enemigo * enemigo;
    Reloj * reloj;
    Reloj * pendulo;
    ObjetoAnimado * fondoAux;
    ObjetoAnimado * corazon;
    ObjetoAnimado * teleport;


    //Creación de timers
    QTimer * timerHeroe;
    QTimer * timerFondo;
    QTimer * timerbala;
    QTimer * timerSegundos;
    QTimer * timerEnemigo;
    QTimer * timerTeleport;
    QTimer * timerPantallaCarga1;

    //funciones
    void menu();
    void cargarNivel1();
    void cargarNivel2();
    void borrarObjetos(); //Liberará memoria
    void pantallasCarga(); //Transición entre pantallas de carga
};
#endif // MAINWINDOW_H
