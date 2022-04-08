#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::animarHeroe()
{
    heroe->animar(heroe);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //escena
    escena = new QGraphicsScene;
    escena->setSceneRect(0,0,ui->graphicsView->width()-2, ui->graphicsView->height()-2);
    ui->graphicsView->setScene(escena);

    heroe = new ObjetoAnimado(":/Image/imagenes heroe/frame_0_delay-0.08s.png",0,0,100,100,8,":/Image/imagenes heroe/frame_","_delay-0.08s.png");
    escena->addItem(heroe);


    timerHeroe = new QTimer;
    connect(timerHeroe, SIGNAL(timeout()), this, SLOT(animarHeroe()));

    timerHeroe->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

