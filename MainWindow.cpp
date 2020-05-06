//
// Created by Guillaume LOQUET on 14/04/2020.
//
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QtGui>
#include <iostream>
#include <QThread>
#include "MainWindow.h"
// Construction main window
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    //Load the font
    QFontDatabase test = QFontDatabase();
    test.addApplicationFont("Jeuqt-Regular.ttf");
    // Instantiate scenes
    this->menuScene = new Launcher();
    this->GameScene = new RunScene();

    // load the main menu view
    buildMenuView();


}

void MainWindow::buildGame() {
    disconnect(this->menuScene->getStartButton(),SIGNAL(clicked()),this,SLOT(buildGame()));
    disconnect(this->menuScene->getRestartButton(),SIGNAL(clicked()),this,SLOT(buildGame()));
    disconnect(this->menuScene->getExit(),SIGNAL(clicked()),qApp,SLOT(quit()));
    // Set the view of the game
    this->playerView = new QGraphicsView();
    this->playerView->setScene(GameScene);
    playerView->scale(0.4, 0.4);


    if(this->menuScene->getSceneSwitch()){// If true, set a new view with the all scene
        this->mainView = new QGraphicsView();
        this->mainView->setScene(GameScene);
        mainView->scale(0.1, 0.1);
        mainView->show();
    }

    //
    this->setCentralWidget(playerView);
    this->setWindowTitle("Game");
    this->GameScene->launchGame();// call the launcher of the run

    connect(this->GameScene->getExit(), SIGNAL(clicked()), this, SLOT(buildEndGameView()));

}

void MainWindow::buildMenu() {
    // build the menu view
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
    // Load at the end of the run
    disconnect(this->GameScene->getExit(), SIGNAL(clicked()), this, SLOT(buildEndGameView()));

    buildMenu();
    this->menuScene->endGameView(this->GameScene->getScore());

    connect(this->menuScene->getRestartButton(),SIGNAL(clicked()),this,SLOT(buildGame()));
    connect(this->menuScene->getStartButton(),SIGNAL(clicked()),this,SLOT(buildGame()));
    connect(this->menuScene->getExit(),SIGNAL(clicked()),qApp,SLOT(quit()));

}

void MainWindow::buildMenuView() {
    // load the main menu view
    disconnect(this->menuScene->getRestartButton(),SIGNAL(clicked()),this,SLOT(buildGame()));

    buildMenu();
    this->menuScene->menuView();

    connect(this->menuScene->getStartButton(),SIGNAL(clicked()),this,SLOT(buildGame()));
    connect(this->menuScene->getExit(),SIGNAL(clicked()),qApp,SLOT(quit()));
}







