#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::keyPressEvent(QKeyEvent *i)
{
    if(!heroe->getIsDead()){
        if(i->key() == Qt::Key_W){
            heroe->estaSaltando=true;
            heroe->setPixmap(QPixmap(":/Image/heroe/frame_4_delay-0.08s.png").scaled(heroe->getWidth(), heroe->getHeight()));
        }
        if(i->key() == Qt::Key_S){
            heroe->estaAgachado=true;
            heroe->setPixmap(QPixmap(":/Image/heroe/frame_2_delay-0.08s.png").scaled(heroe->getWidth(), heroe->getHeight()));

        }
    }

    if(i->key() == Qt::Key_I){
        cargarNivel1();
    }
}
void MainWindow::animarHeroe()
{
    //verificamos si la tecla w fue presionada
    if(heroe->estaSaltando){
        timerHeroe->start(6);
        heroe->actualizarPosY();
        if(heroe->y()+heroe->getHeight() > piso->y()){
            heroe->setPos(heroe->getPosix(),heroe->getPosiy());
            heroe->vely=60;
            heroe->estaSaltando=false;
            timerHeroe->start(50);
        }
    }
    else if(heroe->estaAgachado){
        heroe->setPos(heroe->getPosix(),heroe->getPosiy()+80);
        timerHeroe->start(1000);
        heroe->estaAgachado=false;

    }
    //animación por defecto
    else{
        timerHeroe->start(50);
        heroe->setPos(heroe->getPosix(),heroe->getPosiy());
        heroe->animar();
    }
}

void MainWindow::animarFondo()
{

    fondo->animar();
    piso->animar();

}

void MainWindow::animarProyectil()
{


    bala->actualizarPosProyectil(heroe);
    ui->lcdVidas->display(heroe->getVidas());
    bala->animar();
    if(heroe->getIsDead()){
        timerFondo->stop();
        timerHeroe->stop();
        timerbala->stop();
        timerEnemigo->stop();
        timerSegundos->stop();
        fondoAux = new ObjetoAnimado(":/Image/imagenes de apoyo/lose.gif",0,0,escena->width(),escena->height(),1,":/Image/fondo bosque/fondoBosque (",").png");
        escena->addItem(fondoAux);
    }
}

void MainWindow::animarEnemigo()
{
    pendulo->movPendulo();

    enemigo->animar();
}

void MainWindow::contarSegundos()
{

    reloj->actualizarTiempo();
    ui->lcdTiempo->display(reloj->getTiempoPartida());
    if(reloj->getTiempoPartida()<=0){
        cargarNivel2();
        heroe->setNivelActual(2);
    }

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

    //Creación de timers
    timerFondo = new QTimer;
    connect(timerFondo, SIGNAL(timeout()), this, SLOT(animarFondo()));
    timerHeroe = new QTimer;
    connect(timerHeroe, SIGNAL(timeout()), this, SLOT(animarHeroe()));
    timerEnemigo = new QTimer;
    connect(timerEnemigo, SIGNAL(timeout()), this, SLOT(animarEnemigo()));
    timerbala = new QTimer;
    connect(timerbala, SIGNAL(timeout()), this, SLOT(animarProyectil())); //Movimiento de la bala
    timerSegundos = new QTimer;
    connect(timerSegundos, SIGNAL(timeout()), this, SLOT(contarSegundos())); //Movimiento de la bala

    srand(time(NULL)); //inicializo la semilla aleatoria
    menu();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cargarNivel1()
{
    //Creación de objetos
    fondo = new ObjetoAnimado(":/Image/fondo bosque/fondoBosque (0).png",0,0,escena->width(),escena->height(),300,":/Image/fondo bosque/fondoBosque (",").png");
    escena->addItem(fondo);
    piso = new ObjetoAnimado(":/Image/piso/frame_0_delay-0.1s.png",0,escena->height()-50,escena->width()-2,50,8,":/Image/piso/frame_","_delay-0.1s.png");
    heroe = new Heroe(":/Image/heroe/frame_0_delay-0.08s.png",0,escena->height()-piso->getHeight()-120,220,120,8,":/Image/heroe/frame_","_delay-0.08s.png");
    escena->addItem(heroe);
    escena->addItem(piso);

    bala = new Proyectil(":/Image/Bala/frame_1_delay-0.06s.png",escena->width()-280,escena->height()-piso->getHeight()-50,72,24,30,":/Image/Bala/frame_","_delay-0.06s.png",4,0);
    escena->addItem(bala);
    enemigo = new Enemigo(":/Image/enemigo1/frame_0_delay-0.08s.png",escena->width()-300,escena->height()-piso->getHeight()-100,300,100,6,":/Image/enemigo1/frame_","_delay-0.08s.png");
    escena->addItem(enemigo);
    reloj = new Reloj(":/Image/imagenes de apoyo/reloj.png",0,0,150,150,1,"-","-");
    escena->addItem(reloj);
    pendulo = new Reloj(":/Image/imagenes de apoyo/pendulo.png",80,70,50,50,1,"-","-",50,35,50,30);
    escena->addItem(pendulo);
    corazon = new ObjetoAnimado(":/Image/imagenes de apoyo/corazon0.png",310,65,40,40,1,"-","-");
    escena->addItem(corazon);

    ui->lcdVidas->show();
    ui->lcdTiempo->show();
    ui->lcdVidas->display(heroe->getVidas());
    ui->lcdTiempo->display(reloj->getTiempoPartida());



    timerFondo->start(100);//100
    timerHeroe->start(50);
    timerEnemigo->start(140);
    timerbala->start(10);//10 para nivel 1
    timerSegundos->start(1000);


}
void MainWindow::cargarNivel2()
{
    //Creación de objetos
    fondo = new ObjetoAnimado(":/Image/fondo2/fondoDesierto (0).png",0,0,escena->width(),escena->height(),228,":/Image/fondo2/fondoDesierto (",").png");
    escena->addItem(fondo);
    piso = new ObjetoAnimado(":/Image/piso/frame_0_delay-0.1s.png",0,escena->height()-50,escena->width()-2,50,8,":/Image/piso/frame_","_delay-0.1s.png");
    heroe = new Heroe(":/Image/heroe/frame_0_delay-0.08s.png",0,escena->height()-piso->getHeight()-120,220,120,8,":/Image/heroe/frame_","_delay-0.08s.png");
    escena->addItem(heroe);
    escena->addItem(piso);

    bala = new Proyectil(":/Image/Bala/frame_1_delay-0.06s.png",escena->width()-280,escena->height()-piso->getHeight()-50,72,24,30,":/Image/Bala/frame_","_delay-0.06s.png",4,0);
    escena->addItem(bala);
    enemigo = new Enemigo(":/Image/enemigo2/frame_0_delay-0.1s.png",escena->width()-250,escena->height()-piso->getHeight()-200,250,200,5,":/Image/enemigo2/frame_","_delay-0.1s.png");
    escena->addItem(enemigo);
    reloj = new Reloj(":/Image/imagenes de apoyo/reloj.png",0,0,150,150,1,"-","-");
    escena->addItem(reloj);
    pendulo = new Reloj(":/Image/imagenes de apoyo/pendulo.png",80,70,50,50,1,"-","-",50,35,50,30);
    escena->addItem(pendulo);
    corazon = new ObjetoAnimado(":/Image/imagenes de apoyo/corazon0.png",310,65,40,40,1,"-","-");
    escena->addItem(corazon);

    ui->lcdVidas->show();
    ui->lcdTiempo->show();
    ui->lcdVidas->display(heroe->getVidas());
    ui->lcdTiempo->display(reloj->getTiempoPartida());



    timerFondo->start(100);//100
    timerHeroe->start(50);
    timerEnemigo->start(140);
    timerbala->start(10);
    timerSegundos->start(1000);


}

void MainWindow::menu()
{
    ui->lcdVidas->hide();
    ui->lcdTiempo->hide();
    fondo = new ObjetoAnimado(":/Image/menu/frame_0_delay-0.19s.png",0,0,escena->width(),escena->height(),2,":/Image/menu/frame_","_delay-0.19s.png");
    escena->addItem(fondo);
    piso = new ObjetoAnimado(":/Image/menu/titulo menu0.png",240,400,434,113,1,":/Image/menu/titulo menu",".png");
    escena->addItem(piso);
    timerFondo->start(200);

}


