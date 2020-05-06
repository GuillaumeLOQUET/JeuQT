//
// Created by Guillaume LOQUET on 14/04/2020.
//
#include <QMainWindow>
#include <QGraphicsView>
#include "RunScene.h"
#include "Launcher.h"

#ifndef JEUQT_MAINWINDOW_H
#define JEUQT_MAINWINDOW_H


class MainWindow : public QMainWindow{
    Q_OBJECT

private:
    RunScene* GameScene ;
    Launcher* menuScene ;
    QGraphicsView* menuView;
    QGraphicsView* playerView;
    QGraphicsView* mainView;


public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() {};
    void buildMenu();

public slots:
    void buildGame();
    void buildMenuView();
    void buildEndGameView();
};


#endif //JEUQT_MAINWINDOW_H
