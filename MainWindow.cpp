//
// Created by Guillaume LOQUET on 14/04/2020.
//
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QtGui>
#include <iostream>
#include <QThread>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    QFontDatabase test = QFontDatabase();
    test.addApplicationFont("Jeuqt-Regular.ttf"); //Load the font
    this->menuScene = new Launcher();
    this->mainScene = new MainScene();

    buildMenuView();


}

void MainWindow::buildGame() {
    disconnect(this->menuScene->getStartButton(),SIGNAL(clicked()),this,SLOT(buildGame()));
    disconnect(this->menuScene->getRestartButton(),SIGNAL(clicked()),this,SLOT(buildGame()));
    disconnect(this->menuScene->getExit(),SIGNAL(clicked()),qApp,SLOT(quit()));

    this->playerView = new QGraphicsView();
    this->playerView->setScene(mainScene);
    playerView->scale(0.4, 0.4);


    if(this->menuScene->getSceneSwitch()){
        this->mainView = new QGraphicsView();
        this->mainView->setScene(mainScene);
        mainView->scale(0.1, 0.1);
        mainView->show();
    }


    this->setCentralWidget(playerView);
    this->setWindowTitle("Game");
    this->mainScene->launchGame();
    connect(this->mainScene->getExit(),SIGNAL(clicked()),this,SLOT(buildEndGameView()));

}

void MainWindow::buildMenu() {
    if(menuScene->getSceneSwitch()){
        mainView->close();
        delete mainView ;
    }

    menuView = new QGraphicsView();
    menuView->setScene(menuScene);

    this->setCentralWidget(menuView);
    this->setWindowTitle("Menu");

}

void MainWindow::buildEndGameView() {
    disconnect(this->mainScene->getExit(),SIGNAL(clicked()),this,SLOT(buildEndGameView()));
    buildMenu();
    this->menuScene->endGameView(this->mainScene->getScore());
    connect(this->menuScene->getStartButton(),SIGNAL(clicked()),this,SLOT(buildGame()));
    connect(this->menuScene->getRestartButton(),SIGNAL(clicked()),this,SLOT(buildGame()));
    connect(this->menuScene->getExit(),SIGNAL(clicked()),qApp,SLOT(quit()));

}

void MainWindow::buildMenuView() {
    disconnect(this->mainScene->getExit(),SIGNAL(clicked()),this,SLOT(buildEndGameView()));
    buildMenu();
    this->menuScene->menuView();
    connect(this->menuScene->getStartButton(),SIGNAL(clicked()),this,SLOT(buildGame()));
    connect(this->menuScene->getRestartButton(),SIGNAL(clicked()),this,SLOT(buildGame()));
    connect(this->menuScene->getExit(),SIGNAL(clicked()),qApp,SLOT(quit()));
}







