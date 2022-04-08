#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::keyPressEvent(QKeyEvent *i)
{
    if(i->key() == Qt::Key_W){
        heroe->estaSaltando=true;
        heroe->setPixmap(QPixmap(":/Image/imagenes heroe/frame_4_delay-0.08s.png").scaled(heroe->getWidth(), heroe->getHeight()));

    }
}
void MainWindow::animarHeroe()
{

    if(heroe->estaSaltando){
        timerHeroe->start(6);
        heroe->actualizarPosY();
        if(heroe->y()+heroe->getHeight() > piso->y()){
            heroe->vely=40;
            heroe->estaSaltando=false;
            timerHeroe->start(50);
        }
    }
    else{
        heroe->animar();
    }
}

void MainWindow::animarFondo()
{
    fondo->animar();
    piso->animar();


}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ensayos tamaño de pantalla
    /*QMainWindow::QWidget::setWindowState(Qt::WindowMaximized);
    qDebug() << this->size().width();
    qDebug() << this->size().height();
    ui->graphicsView->setGeometry(0,0,this->size().width(),this->size().height());*/

    //Escena
    escena = new QGraphicsScene;
    escena->setSceneRect(0,0,ui->graphicsView->width()-2, ui->graphicsView->height()-2);
    ui->graphicsView->setScene(escena);

    //Creación de objetos
    fondo = new ObjetoAnimado(":/Image/imagenes fondo bosque/fondoBosque (0).png",0,0,escena->width()-2,escena->height()-2,301,":/Image/imagenes fondo bosque/fondoBosque (",").png");
    escena->addItem(fondo);
    piso = new ObjetoAnimado(":/Image/imagenes piso/frame_0_delay-0.1s.png",0,escena->height()-50,escena->width()-2,50,8,":/Image/imagenes piso/frame_","_delay-0.1s.png");
    escena->addItem(piso);
    heroe = new Heroe(":/Image/imagenes heroe/frame_0_delay-0.08s.png",0,escena->height()-piso->getHeight()-100,100,100,8,":/Image/imagenes heroe/frame_","_delay-0.08s.png");
    escena->addItem(heroe);

    //Creación de timers
    timerFondo = new QTimer;
    connect(timerFondo, SIGNAL(timeout()), this, SLOT(animarFondo()));
    timerFondo->start(100);
    timerHeroe = new QTimer;
    connect(timerHeroe, SIGNAL(timeout()), this, SLOT(animarHeroe()));
    timerHeroe->start(50);

}

MainWindow::~MainWindow()
{
    delete ui;
}

