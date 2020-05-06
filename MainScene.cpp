//
// Created by Guillaume LOQUET on 14/04/2020.
//
#include "MainScene.h"

#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <string>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QVector>
#include <QRectF>
#include <iostream>
#include <fstream>
#include <QtGui/QFontDatabase>

MainScene::MainScene() {
    // Construction of the game scene elements

    this->background.load("game/fondGame.png");
    this->setSceneRect(0, 0, background.width(), background.height());

    this->runTime = new QTime();
    this->timerUpdate = new QTimer(this);

    this->player = new Player("player/playerUpR.png");
    this->addItem(this->player);

    backgroundTimer = this->addPixmap(QPixmap("game/backgroundtimer.png"));
    textTimer = addText("0");
    textTimer->setFont(QFontDatabase().font("Jeuqt", "regular", 60));


    buildModule(); // construction of all modules

    //construction of buttons
    startButton = new QPushButton("Click here\n to Start");
    exitButton = new QPushButton("Click here\n to continue");
    startButton->setFont(QFontDatabase().font("Jeuqt","regular",100));
    exitButton->setFont(QFontDatabase().font("Jeuqt","regular",100));
    start = addWidget(startButton);
    exit = addWidget(exitButton);
    startButton->setStyleSheet("background-image:url(menu/backgroundResult.png);"
                               "background-color: transparent;");
    startButton->setGeometry(this->width()/2 -400 , this->height()/2-200  ,700,300);
    exitButton->setStyleSheet("background-image:url(menu/backgroundResult.png);"
                              "background-color: transparent;");



}

MainScene::~MainScene() {

    delete this->timerUpdate;

}

void MainScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

void MainScene::launchGame() {

    startButton->setVisible(true);
    exitButton->setVisible(false);

    connect(this->startButton,SIGNAL(clicked()),this,SLOT(startGame()));
}

void MainScene::startGame() {
    disconnect(this->startButton,SIGNAL(clicked()),this,SLOT(startGame()));
    startButton->setVisible(false);


    this->timerUpdate->start(10);

    connect(timerUpdate, SIGNAL(timeout()), this, SLOT(update()));


    this->player->setPos(50, 0 - this->getPlayer()->boundingRect().height());



    this->getPlayer()->getTimeJump()->start();
    this->getPlayer()->getDelayJump()->start();
    this->getPlayer()->setPosBase(this->getPlayer()->pos());

    runTime->start();


}

void MainScene::buildModule() {
    listModule.append(this->addPixmap(QPixmap("module/module2.png")));
    listModule[0]->setPos(0, 1000);
    listModule.append(this->addPixmap(QPixmap("module/module1.png")));
    listModule[1]->setPos(1200, 900);
    listModule.append(this->addPixmap(QPixmap("module/module1.png")));
    listModule[2]->setPos(2000, 700);
    listModule.append(this->addPixmap(QPixmap("module/module3.png")));
    listModule[3]->setPos(2600, 1000);
    listModule.append(this->addPixmap(QPixmap("module/module3.png")));
    listModule[4]->setPos(3400, 1000);
    listModule.append(this->addPixmap(QPixmap("module/module3.png")));
    listModule[5]->setPos(3000, 350);
    listModule.append(this->addPixmap(QPixmap("module/module4.png")));
    listModule[6]->setPos(4200, 700);
    listModule.append(this->addPixmap(QPixmap("module/module1.png")));
    listModule[7]->setPos(5200, 1100);
    listModule.append(this->addPixmap(QPixmap("module/module2.png")));
    listModule[8]->setPos(5800, 850);
    listModule.append(this->addPixmap(QPixmap("module/module1.png")));
    listModule[9]->setPos(6600, 650);
    listModule.append(this->addPixmap(QPixmap("module/module4.png")));
    listModule[10]->setPos(7500, 1000);
    listModule.append(this->addPixmap(QPixmap("module/module4.png")));
    listModule[11]->setPos(8000, 1000);
    listModule.append(this->addPixmap(QPixmap("module/module2.png")));
    listModule[12]->setPos(8500, 900);
    listModule.append(this->addPixmap(QPixmap("module/module3.png")));
    listModule[13]->setPos(9500, 900);
    listModule.append(this->addPixmap(QPixmap("module/module3.png")));
    listModule[14]->setPos(9600, 250);

    finishModule = this->addPixmap(QPixmap("module/exitPanel.png"));
    finishModule->setPos(9700, 900 - this->finishModule->boundingRect().height() + 10);
}

void MainScene::update() {

    // update of the timer
    textTimer->setPlainText(QString::number(runTime->elapsed() / 1000) + ":" + QString::number(runTime->elapsed() / 10 % 100));
    textTimer->setPos(this->views().at(0)->mapToScene(this->views().at(0)->viewport()->rect().topRight().x() - 80, 10));//put the timer in the top right corner of the view
    backgroundTimer->setPos(this->views().at(0)->mapToScene(this->views().at(0)->viewport()->rect().topRight().x()-100,0));//put the background of timer in the top right corner of the view

    QPointF pos = this->player->pos(); // Get the position of the player

    if(this->player->getPressUp() && !this->player->isJump() && !this->getPlayer()->isInAir() && this->getPlayer()->getDelayJump()->elapsed() > 50){ // The player want jump
        this->getPlayer()->getTimeJump()->start();
        this->getPlayer()->setPosBase(pos);
        this->getPlayer()->setJump(true);
        this->getPlayer()->setMoveY(20);
    }else if( !touchModule() && !this->player->isJump() && !this->getPlayer()->isInAir()){ // The player is now in the air
        this->getPlayer()->setInAir(true);
        this->getPlayer()->setPosBase(pos);
        this->getPlayer()->getTimeJump()->start();

    }else if(!this->player->getPressUp() && !this->player->isJump() && !this->getPlayer()->isInAir()){ // the player is on the ground
        this->getPlayer()->setPosBase(pos);
        this->getPlayer()->getTimeJump()->start();
    }

    int timeJump = this->player->getTimeJump()->elapsed() / 10 ; // Get the time since the jump (or falling)

    this->getPlayer()->setPos(pos.x() , this->getPlayer()->getPosBase().y() + 0.3 * timeJump * timeJump - this->getPlayer()->getMoveY() * timeJump);//Move the player in the Y axis(Newton's 2nd law)

    if(touchModule()){ // If because of the move he touches a module the player comeback at the last position
        this->getPlayer()->setPosBase(pos);
        this->getPlayer()->setPos(pos.x() , pos.y());
        if(this->getPlayer()->isJump()){
            this->getPlayer()->getDelayJump()->start();
        }
        this->getPlayer()->setJump(false);
        this->getPlayer()->setInAir(false);

        this->getPlayer()->setMoveY(0);
        this->getPlayer()->getTimeJump()->start();

    }

    this->getPlayer()->setPos(pos.x() +  this->getPlayer()->getMoveX(), this->getPlayer()->pos().y()); //Move the player in the X axis

    if( touchModule() || this->getPlayer()->pos().x() < 0){ // If because of the move he touches a module the player comeback at the last position
        this->getPlayer()->setPos(pos.x() , this->getPlayer()->pos().y());

    }

    if(this->getPlayer()->pos().y() > this->height() ){ // if the player falls he go back at the beginning position
        this->getPlayer()->setInAir(true);
        this->getPlayer()->getTimeJump()->start();
        this->getPlayer()->setJump(false);
        this->getPlayer()->setMoveY(0);
        this->player->setPos(50, 0 - this->getPlayer()->boundingRect().height());

    }

    this->getPlayer()->changeImage(); // Change the appearance of the player

    isWin(); // Look if the player wins

    // Center the view on the player
    QGraphicsView *view = this->views().at(0);
    view->centerOn(this->getPlayer());

}

bool MainScene::touchModule() {
    bool istouch = false ;

    for(QGraphicsPixmapItem* module : listModule){

        if(this->getPlayer()->collidesWithItem(module)){ //if a player touch a module it returns true
            istouch = true ;
        }

    }
    return istouch;
}
void MainScene::isWin(){
    if(this->getPlayer()->collidesWithItem(finishModule)){ // if the player win
        end();
    }
}

void MainScene::end() {

    disconnect(timerUpdate, SIGNAL(timeout()), this, SLOT(update()));

    score = runTime->elapsed();

    exitButton->setGeometry(this->views().at(0)->mapToScene(this->views().at(0)->viewport()->rect().center()).x()-350,this->views().at(0)->mapToScene(this->views().at(0)->viewport()->rect().center()).y()-150,700,300); //Put the button in the center of the view.
    exitButton->setVisible(true);


}


//functions redefined
void MainScene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Z || event->key() == Qt::Key_Up) {
        this->getPlayer()->setPressUp(true);

    }
    if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down){
        this->getPlayer()->setPressDown(true);

    }
    if (event->key() == Qt::Key_Q || event->key() == Qt::Key_Left){
        this->getPlayer()->setPressLeft(true);

    }
    if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right){
        this->getPlayer()->setPressRight(true);

    }

}
void MainScene::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Z || event->key() == Qt::Key_Up) {
        this->getPlayer()->setPressUp(false);

    }
    if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down){
        this->getPlayer()->setPressDown(false);

    }
    if (event->key() == Qt::Key_Q || event->key() == Qt::Key_Left){
        this->getPlayer()->setPressLeft(false);

    }
    if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right){
        this->getPlayer()->setPressRight(false);

    }

}






