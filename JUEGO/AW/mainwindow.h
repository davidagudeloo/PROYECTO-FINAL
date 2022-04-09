#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"
#include <QKeyEvent>
#include "objetoanimado.h"
#include "heroe.h"
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

    //Creación de timers
    QTimer * timerHeroe;
    QTimer * timerFondo;

    //funciones
    void cargarNivel1();




};
#endif // MAINWINDOW_H
