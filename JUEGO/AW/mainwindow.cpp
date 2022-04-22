#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::keyPressEvent(QKeyEvent *i)
{ 
    //Mientras el heroe no esté muerto
    if(!heroe->getIsDead()){
        //Puede saltar
        if(i->key() == Qt::Key_W){
            heroe->setEstaSaltando(true);
            heroe->setPixmap(QPixmap(":/Image/heroe/frame_4_delay-0.08s.png").scaled(heroe->getWidth(), heroe->getHeight()));
        }

        //Y si además tiene el poder disponible
        if(heroe->getPoderDisponible()){
            //Puede teletransportarse a la derecha
            if(i->key() == Qt::Key_D){
                timerTeleport->start(50);
                //Mientras no toque al enemigo
                if(heroe->x()+heroe->getWidth()<enemigo->getPosix()){
                    heroe->setPosix(heroe->x()+100);
                }
            }
            //Puede teletransportarse a la izquierda
            else if(i->key() == Qt::Key_A){
                timerTeleport->start(50);
                //Mientras no se salga de la pantalla
                if(heroe->x()>=0){
                    heroe->setPosix(heroe->x()-100);
                }
            }
        }
        //Puede guardar
        if(i->key() == Qt::Key_G){
            archivo->guardarDatos("datos.txt", heroe, reloj);
            actualizarBaseDatos();
            menu();
        }    
    }

    if(i->key() == Qt::Key_M){
        heroe->setNivelActual(1);
        menu();
    }
    //Puede cargar
    if(i->key() == Qt::Key_C){
        myfile.open("datos.txt");
        //Si el archivo existe y está en el menú
        if(myfile && pantallaDeCarga==0){
            //Inicio y Registro
            ui->btIniciarSesion->hide();
            ui->btRegistrarse->hide();
            ui->labelClave->hide();
            ui->labelUsuario->hide();
            ui->lineClave->hide();
            ui->lineUsuario->hide();
            ui->labelUsuarioRepetido->hide();
            pantallaDeCarga=5;
            archivo->setSeQuiereCargar(true);
            archivo->cargarDatos("datos.txt", heroe, reloj);
            //el nivel 1
            if(heroe->getNivelActual()==1){
                borrarObjetos();
                cargarNivel1();
            }
            //o el nivel 2
            else if(heroe->getNivelActual()==2){
                borrarObjetos();
                cargarNivel2();
            }
        }
        myfile.close();
    }
    //Inicializacion
    if(i->key() == Qt::Key_N){
        pantallasCarga();
    }
}
void MainWindow::animarHeroe()
{
    //verificamos si la tecla w fue presionada
    if(heroe->getEstaSaltando()){
        timerHeroe->start(6);
        heroe->actualizarPosY();
        if(heroe->y()+heroe->getHeight() > piso->y()){
            heroe->setPos(heroe->getPosix(),heroe->getPosiy());
            heroe->setVely(60);
            heroe->setEstaSaltando(false);
            timerHeroe->start(50);
        }
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
}

void MainWindow::animarProyectil()
{
    if(heroe->getNivelActual()==1){
        bala[0]->actualizarPosProyectil(heroe);
        ui->lcdVidas->display(heroe->getVidas());
        bala[0]->animar();
    }
    else{
        for(int i=0; i<4;i++){
            bala[i]->actualizarPosProyectil(heroe);
            ui->lcdVidas->display(heroe->getVidas());
            bala[i]->animar();
        }
    }

    //Si el heroe está muerto (cero vidas)
    if(heroe->getIsDead() && heroe->getVidas()==0){
        timerFondo->stop();
        timerHeroe->stop();
        timerEnemigo->stop();
        fondoAux->setImagen(":/Image/imagenes de apoyo/lose.png");
        escena->removeItem(fondoAux);
        escena->addItem(fondoAux);
        timerbala->stop();
        timerSegundos->stop();
    }
}

void MainWindow::animarEnemigo()
{
    enemigo->animar();
    pendulo->movPendulo();//además animamos el movimiento del péndulo
    piso->animar();//además animamos el piso
}

void MainWindow::animarTeleport()
{
    teleport->setPos(heroe->getPosix(),heroe->y());
    teleport->show();
    teleport->animar();
    if(teleport->getActualFrame() == teleport->getNumFrames()-1){
        timerTeleport->stop();
        teleport->hide();
    }
}

void MainWindow::animarPantallaCarga1()
{
    pantallaCarga1->animar();
    if(pantallaCarga1->getActualFrame() == pantallaCarga1->getNumFrames()-1){
        timerPantallaCarga1->stop();
        pantallaDeCarga++;
    }
}

void MainWindow::contarSegundos()
{
    reloj->actualizarTiempo();
    ui->lcdTiempo->display(reloj->getTiempoPartida());
    //Si se acaba el tiempo
    if(reloj->getTiempoPartida()==0){
        //Y está en el nivel 1
        if(heroe->getNivelActual()==1){
            heroe->setNivelActual(2);
            heroe->setPoderDisponible(true);
            heroe->setIsDead(true); //Bloqueo de funciones de botones
            //Se ocultan los lcds
            ui->lcdVidas->hide();
            ui->lcdTiempo->hide();
            timerFondo->stop();
            timerHeroe->stop();
            timerbala->stop();
            timerEnemigo->stop();
            pantallaDeCarga=0;
            pantallasCarga();
        }
        //Y está en el nivel 2
        else if(heroe->getNivelActual()==2){
            timerFondo->stop();
            timerHeroe->stop();
            timerbala->stop();
            timerEnemigo->stop();
            heroe->setIsDead(true); //Bloqueo de funciones de botones
            //Pantalla de victoria
            fondoAux->setImagen(":/Image/imagenes de apoyo/win.png");
            escena->removeItem(fondoAux);
            escena->addItem(fondoAux);
            timerSegundos->stop();
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Escena
    escena = new QGraphicsScene;
    escena->setSceneRect(0,0,ui->graphicsView->width()-2, ui->graphicsView->height()-2);
    ui->graphicsView->setScene(escena);

    ui->labelUsuarioRepetido->hide();

    //Música
    QDesktopServices::openUrl(QUrl("https://youtu.be/kofwOaINByM"));
    QThread::msleep(1000);
    QMainWindow::QWidget::setWindowState(Qt::WindowNoState);

    //Creación de timers
    timerFondo = new QTimer;
    connect(timerFondo, SIGNAL(timeout()), this, SLOT(animarFondo()));
    timerHeroe = new QTimer;
    connect(timerHeroe, SIGNAL(timeout()), this, SLOT(animarHeroe()));
    timerEnemigo = new QTimer;
    connect(timerEnemigo, SIGNAL(timeout()), this, SLOT(animarEnemigo()));
    timerbala = new QTimer;
    connect(timerbala, SIGNAL(timeout()), this, SLOT(animarProyectil()));
    timerSegundos = new QTimer;
    connect(timerSegundos, SIGNAL(timeout()), this, SLOT(contarSegundos()));
    timerTeleport = new QTimer;
    connect(timerTeleport, SIGNAL(timeout()), this, SLOT(animarTeleport()));
    timerPantallaCarga1 = new QTimer;
    connect(timerPantallaCarga1, SIGNAL(timeout()), this, SLOT(animarPantallaCarga1()));

    //Se inicializa la semilla aleatoria
    srand(time(NULL));
    //Archivo para guardado
    archivo = new ArchivoInformacion();
    //Fondo auxiliar
    fondoAux = new ObjetoAnimado("-",0,0,escena->width(),escena->height(),1,"-","-");
    escena->addItem(fondoAux);
    //Heroe auxiliar: se utilizarán únicamente sus atributos para puente entre niveles
    heroeAux = new Heroe("-",0,0,1,1,1,"-","-");

    //Llamado del menú principal
    cargarNivel1(); //Se inicializa una primera vez, para el borrado de memoria
    menu();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete escena;
    delete archivo;
    delete fondoAux;
    delete heroeAux;

    delete fondo;
    delete piso;
    delete heroe;
    delete enemigo;
    delete reloj;
    delete pendulo;
    delete corazon;
    delete teleport;
    for(int i=0; i<4; i++){
        delete bala[i];
    }


    delete timerHeroe;
    delete timerFondo;
    delete timerbala;
    delete timerSegundos;
    delete timerEnemigo;
    delete timerTeleport;
}

void MainWindow::menu()
{
    //Inicio o Registro
    ui->btIniciarSesion->show();
    ui->btRegistrarse->show();
    ui->labelClave->show();
    ui->labelUsuario->show();
    ui->lineClave->show();
    ui->lineUsuario->show();

    pantallaDeCarga=0;
    //Detenemos los timers de la inicialización
    timerbala->stop();
    timerSegundos->stop();
    //Se ocultan los lcds
    ui->lcdVidas->hide();
    ui->lcdTiempo->hide();

    //Creación de objetos
    fondo = new ObjetoAnimado(":/Image/menu/frame_0_delay-0.19s.png",0,0,escena->width(),escena->height(),2,":/Image/menu/frame_","_delay-0.19s.png");

    //Se añaden a la escena
    escena->addItem(fondo);

    //Se activan los timers
    timerFondo->start(200);
}

void MainWindow::pantallasCarga()
{
    if(heroe->getNivelActual()==1){
        if(pantallaDeCarga==0){
            //Inicio y Registro
            ui->btIniciarSesion->hide();
            ui->btRegistrarse->hide();
            ui->labelClave->hide();
            ui->labelUsuario->hide();
            ui->lineClave->hide();
            ui->lineUsuario->hide();
            ui->labelUsuarioRepetido->hide();
            ui->labelNombreUsuario->hide();


            fondoAux->setImagen(":/Image/imagenes de apoyo/pantallahistoria0.png");
            escena->removeItem(fondoAux);
            escena->addItem(fondoAux);
            pantallaDeCarga++;
        }
        else if(pantallaDeCarga==1){
            fondoAux->setImagen(":/Image/imagenes de apoyo/pantallahistoria1.png");
            escena->removeItem(fondoAux);
            escena->addItem(fondoAux);
            pantallaDeCarga++;
        }
        else if(pantallaDeCarga==2){
            pantallaCarga1 = new ObjetoAnimado(":/Image/CargaNivel1/0.gif",0,0,escena->width(),escena->height(),14,":/Image/CargaNivel1/",".gif");
            escena->addItem(pantallaCarga1);
            pantallaCarga1->show();
            timerPantallaCarga1->start(500);
            pantallaDeCarga++;
        }
        else if(pantallaDeCarga==3){

        }
        else if(pantallaDeCarga==4){
            timerPantallaCarga1->stop();
            delete pantallaCarga1;
            pantallaDeCarga++;
            borrarObjetos();
            cargarNivel1();
        }
    }
    else{
        //Se reinicia cuando el tiempo llega a cero
        if(pantallaDeCarga==0){
            ui->labelNombreUsuario->hide();
            fondoAux->setImagen(":/Image/imagenes de apoyo/pantallahistoria2.png");
            escena->removeItem(fondoAux);
            escena->addItem(fondoAux);
            pantallaDeCarga++;
        }
        else if(pantallaDeCarga==1){
            fondoAux->setImagen(":/Image/imagenes de apoyo/pantallahistoria3.png");
            escena->removeItem(fondoAux);
            escena->addItem(fondoAux);
            pantallaDeCarga++;
        }
        else if(pantallaDeCarga==2){
            pantallaCarga1 = new ObjetoAnimado(":/Image/CargaNivel2/0.gif",0,0,escena->width(),escena->height(),14,":/Image/CargaNivel2/",".gif");
            escena->addItem(pantallaCarga1);
            pantallaCarga1->show();
            timerPantallaCarga1->start(500);
            pantallaDeCarga++;
        }
        else if(pantallaDeCarga==3){

        }
        else if(pantallaDeCarga==4){
            timerPantallaCarga1->stop();
            delete pantallaCarga1;
            pantallaDeCarga++;
            heroeAux->setNivelActual(heroe->getNivelActual());
            heroeAux->setVidas(heroe->getVidas());
            borrarObjetos();
            cargarNivel2();
        }
    }
}


void MainWindow::cargarNivel1()
{
    //Creación de objetos
    fondo = new ObjetoAnimado(":/Image/fondo bosque/fondoBosque (0).png",0,0,escena->width(),escena->height(),300,":/Image/fondo bosque/fondoBosque (",").png");
    piso = new ObjetoAnimado(":/Image/piso/frame_0_delay-0.1s.png",0,escena->height()-50,escena->width()-2,50,8,":/Image/piso/frame_","_delay-0.1s.png");
    heroe = new Heroe(":/Image/heroe/frame_0_delay-0.08s.png",0,escena->height()-piso->getHeight()-120,220,120,8,":/Image/heroe/frame_","_delay-0.08s.png");
    enemigo = new Enemigo(":/Image/enemigo1/frame_0_delay-0.08s.png",escena->width()-300,escena->height()-piso->getHeight()-100,300,100,6,":/Image/enemigo1/frame_","_delay-0.08s.png");
    reloj = new Reloj(":/Image/imagenes de apoyo/reloj.png",0,0,150,150,1,"-","-");
    pendulo = new Reloj(":/Image/imagenes de apoyo/pendulo.png",80,70,50,50,1,"-","-",50,35,50,30);
    corazon = new ObjetoAnimado(":/Image/imagenes de apoyo/corazon0.png",310,65,40,40,1,"-","-");
    teleport = new ObjetoAnimado(":/Image/teleport/teleport (11).png",heroe->x(),heroe->y(),heroe->getWidth(),heroe->getHeight(),10,":/Image/teleport/teleport (",").png");
    for(int i=0; i<4; i++){
        bala[i] = new Proyectil(":/Image/Bala/frame_1_delay-0.06s.png",escena->width()-280,escena->height()-piso->getHeight()-50,72,24,30,":/Image/Bala/frame_","_delay-0.06s.png");
    }

    //Se añaden a la escena
    escena->addItem(fondo);
    escena->addItem(piso);
    escena->addItem(heroe);
    escena->addItem(bala[0]);
    escena->addItem(enemigo);
    escena->addItem(reloj);
    escena->addItem(pendulo);
    escena->addItem(corazon);
    escena->addItem(teleport);

    //Se verifica si se desea cargar la partida guardada
    if(archivo->getSeQuiereCargar()){
        archivo->cargarDatos("datos.txt", heroe, reloj);
        archivo->setSeQuiereCargar(false);
    }

    //Se muestran los displays
    ui->lcdVidas->show();
    ui->lcdTiempo->show();
    ui->lcdVidas->display(heroe->getVidas());
    ui->lcdTiempo->display(reloj->getTiempoPartida());

    ui->labelNombreUsuario->show();


    //Se activan los timers
    timerFondo->start(100);
    timerHeroe->start(50);
    timerEnemigo->start(140);
    timerbala->start(10);
    timerSegundos->start(1000);
}

void MainWindow::cargarNivel2()
{
    //Creación de objetos
    fondo = new ObjetoAnimado(":/Image/fondo2/fondoDesierto (0).png",0,0,escena->width(),escena->height(),228,":/Image/fondo2/fondoDesierto (",").png");
    piso = new ObjetoAnimado(":/Image/piso/frame_0_delay-0.1s.png",0,escena->height()-50,escena->width()-2,50,8,":/Image/piso/frame_","_delay-0.1s.png");
    heroe = new Heroe(":/Image/heroe/frame_0_delay-0.08s.png",0,escena->height()-piso->getHeight()-120,220,120,8,":/Image/heroe/frame_","_delay-0.08s.png");
    enemigo = new Enemigo(":/Image/enemigo2/frame_0_delay-0.1s.png",escena->width()-250,escena->height()-piso->getHeight()-200,250,200,5,":/Image/enemigo2/frame_","_delay-0.1s.png");
    reloj = new Reloj(":/Image/imagenes de apoyo/reloj.png",0,0,150,150,1,"-","-");
    pendulo = new Reloj(":/Image/imagenes de apoyo/pendulo.png",80,70,50,50,1,"-","-",50,35,50,30);
    corazon = new ObjetoAnimado(":/Image/imagenes de apoyo/corazon0.png",310,65,40,40,1,"-","-");
    teleport = new ObjetoAnimado(":/Image/teleport/teleport (11).png",heroe->x(),heroe->y(),heroe->getWidth(),heroe->getHeight(),10,":/Image/teleport/teleport (",").png");
    for(int i=0; i<4; i++){
        bala[i] = new Proyectil(":/Image/bala2/frame_0_delay-0.03s.png",escena->width()-280,escena->height()-piso->getHeight()-50,160,180,38,":/Image/bala2/frame_","_delay-0.03s.png");
    }

    heroe->setPoderDisponible(true);

    //Se añaden a la escena
    escena->addItem(fondo);
    escena->addItem(piso);
    escena->addItem(heroe);
    escena->addItem(enemigo);
    escena->addItem(reloj);
    escena->addItem(pendulo);
    escena->addItem(corazon);
    escena->addItem(teleport);
    for(int i=0; i<4; i++){
        escena->addItem(bala[i]);
    }

    //Se verifica si se desea cargar la partida guardada
    if(archivo->getSeQuiereCargar()){
        archivo->cargarDatos("datos.txt", heroe, reloj);
        archivo->setSeQuiereCargar(false);
    }
    else{
        heroe->setNivelActual(heroeAux->getNivelActual());
        heroe->setVidas(heroeAux->getVidas());
    }

    //Se muestran los displays
    ui->lcdVidas->show();
    ui->lcdTiempo->show();
    ui->lcdVidas->display(heroe->getVidas());
    ui->lcdTiempo->display(reloj->getTiempoPartida());

    ui->labelNombreUsuario->show();


    //Se activan los timers
    timerFondo->start(100);//100
    timerHeroe->start(50);
    timerEnemigo->start(140);
    timerbala->start(10);
    timerSegundos->start(1000);
}

void MainWindow::borrarObjetos()
{
    delete fondo;
    delete piso;
    delete heroe;
    delete enemigo;
    delete reloj;
    delete pendulo;
    delete corazon;
    delete teleport;
    for(int i=0; i<4; i++){
        delete bala[i];
    }
}

void MainWindow::on_btRegistrarse_clicked()
{
    ofstream archivoEscritura;
    archivoEscritura.open("Usuarios.txt", ios::app);

    ifstream archivoLectura;
    archivoLectura.open("Usuarios.txt", ios::in);

    QString nombreUsuario= ui->lineUsuario->text();
    QString clave= ui->lineClave->text();

    string nombre_, linea;

    while(!archivoLectura.eof() && !archivoEscritura.eof()){
        getline(archivoLectura,linea);
        for(int i=0; linea[i]!=' '; i++){ //Tomo letra por letra la linea leida
            nombre_=nombre_+linea[i];
        }
        if(nombre_==nombreUsuario.toStdString()){

            ui->labelUsuarioRepetido->setText("EL USUARIO YA EXISTE");

            //verificar pa borrar
            ui->lineUsuario->setText("");
            nombreUsuario="";
            ui->lineClave->setText("");
            clave="";

            archivoLectura.clear();
            archivoLectura.seekg(0, archivoLectura.beg);
        }
        nombre_="";

    }
    if(nombreUsuario!="" && clave!=""){
        //datos usuario actual
        archivo->guardarDatos("datos.txt", heroe, reloj);
        //Base de Datos registro usuarios
        archivoEscritura<<nombreUsuario.toStdString()<<" "<<clave.toStdString()<<"\n"<<"1"<<"\n"<<"3"<<"\n"<<"40"<<"\n";
        archivoEscritura.close();
        archivoLectura.close();
        usuarioClave=nombreUsuario.toStdString()+" "+clave.toStdString();
        pantallasCarga();
    }
}



void MainWindow::on_btIniciarSesion_clicked()
{

    ifstream archivoLectura;
    archivoLectura.open("Usuarios.txt", ios::in);

    QString nombreUsuario= ui->lineUsuario->text();
    QString clave= ui->lineClave->text();

    string nombre_clave=nombreUsuario.toStdString()+' '+clave.toStdString(), linea, datosJuego[3];


    while(!archivoLectura.eof()||nombre_clave.length()>0){
        getline(archivoLectura,linea);//toma el nombre de usuario
        for(int i=0; i<3; i++){
            getline(archivoLectura,datosJuego[i]);
        }
        if(nombre_clave==linea){
            heroe->setNivelActual(stoi(datosJuego[0]));
            heroe->setVidas(stoi(datosJuego[1]));
            reloj->setTiempoPartida(stoi(datosJuego[2]));
            archivo->guardarDatos("datos.txt", heroe, reloj);
            heroe->setNivelActual(1);
            heroe->setVidas(3);
            reloj->setTiempoPartida(40);
            usuarioClave=nombreUsuario.toStdString()+" "+clave.toStdString();
            ui->labelUsuarioRepetido->setText("Ingreso Exitoso :)");
            ui->labelUsuarioRepetido->show();
            ui->labelNombreUsuario->setText(nombreUsuario);
            ui->labelNombreUsuario->show();


            archivoLectura.close();
            break;
        }
        if(nombre_clave!=linea && archivoLectura.eof()){
            ui->labelUsuarioRepetido->setText("USUARIO O CLAVE INCORRECTA");
            ui->labelUsuarioRepetido->show();
            ui->labelNombreUsuario->hide();

            nombre_clave="";

            //verificar pa borrar
            ui->lineUsuario->setText("");
            nombreUsuario="";
            ui->lineClave->setText("");
            clave="";

        }
    }
    archivoLectura.close();
}
void MainWindow::actualizarBaseDatos()
{
    //acá
    ifstream archivoLectura; // tipo de dato que me permite leer un archivo

    string texto;
    string textoActualizado;

    string linea;
    bool seActualizo=false;
    int espacios=0;

    archivoLectura.open("Usuarios.txt",ios::in); // abrimos el archivo en modo lectura


    while(!archivoLectura.eof()){ // mientras no sea el final del archivo
        getline(archivoLectura,linea);
        texto = texto + linea + "\n";
    }

    archivoLectura.close(); // cerramos el archivo

    //-------------------------------------------------------------------------------------
    for(unsigned int i=0;i<texto.length();i++){
        //construye linea a linea
        if(texto[i]!='\n'){
            if(espacios==0 || espacios==4){
                textoActualizado+=texto[i];
                linea=linea+texto[i];
            }
        }
        else{
            if(seActualizo){
                espacios++;
                if(espacios==4){
                    seActualizo=false;
                }
            }
            else{
                textoActualizado+='\n';
            }
            if(linea==usuarioClave){
                textoActualizado+=heroe->getNivelActual()+'0';
                textoActualizado+='\n';
                textoActualizado+=heroe->getVidas()+'0';
                textoActualizado+='\n';
                textoActualizado+=to_string(reloj->getTiempoPartida());
                textoActualizado+='\n';
                seActualizo=true;
                espacios++;
            }
            linea="";
        }
    }
    //-------------------------------------------------------------------------------------
    ofstream archivoEscritura; // tipo de dato que me permite escribir un archivo

    archivoEscritura.open("Usuarios.txt",ios::out); // abrimos el archivo en modo escritura


    archivoEscritura<<textoActualizado;
    archivoEscritura.close();

    //--------------------------------------------------------------------------------------

}

