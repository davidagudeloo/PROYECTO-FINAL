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

    void contarSegundos();

public:
    void keyPressEvent(QKeyEvent * i);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QGraphicsScene * escena;

    //Creación de objetos
    Heroe * heroe;
    ObjetoAnimado * fondo;
    ObjetoAnimado * piso;
    Proyectil * bala;
    Enemigo * enemigo;
    Reloj * reloj;
    Reloj * pendulo;
    ObjetoAnimado * fondoAux;
    ObjetoAnimado * corazon;

    //Creación de timers
    QTimer * timerHeroe;
    QTimer * timerFondo;
    QTimer *timerbala;
    QTimer * timerSegundos;
    QTimer * timerEnemigo;

    //funciones
    void cargarNivel1();
    void cargarNivel2();
    void menu();
};
#endif // MAINWINDOW_H
