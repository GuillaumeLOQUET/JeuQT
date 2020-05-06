//
// Created by Guillaume LOQUET on 14/04/2020.
//

#ifndef JEUQT_RUNSCENE_H
#define JEUQT_RUNSCENE_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QRect>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>

#include "Player.h"

class RunScene : public QGraphicsScene{
    Q_OBJECT

private :
    QPixmap background; // Background of the game
    QTimer* timerUpdate; // Timer use to update the game
    QTime* runTime; // Time of the run
    Player* player; // player
    QList<QGraphicsPixmapItem*> listModule ; //List of the module in the game
    QGraphicsPixmapItem* finishModule ; // End/Exit module
    QGraphicsPixmapItem* backgroundTimer ; // Background of the textTimer

    int score; // Score at the end of the run

    QGraphicsTextItem* textTimer ; // Graphics textTimer linked to runTime
    QGraphicsProxyWidget* start ; // Graphics widget linked startButton
    QPushButton* startButton; // Button to begin the run
    QGraphicsProxyWidget* exit ; // Graphics widget linked startButton
    QPushButton* exitButton ; // Button to go at the menu of end run




public:
    // Constructor
    RunScene();
    virtual ~RunScene();

    //functions redefined
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void drawBackground(QPainter* painter, const QRectF& rect);

    // Getters
    Player* getPlayer(){return player;}
    QPushButton* getExit(){return exitButton;}
    int getScore(){ return score;}

    //function
    void buildModule();// Construction of all modules
    bool touchModule(); // return true if the player touch a module
    void launchGame();
    void isWin();

//slots
public slots :
    void startGame();
    void update();
    void end();

};


#endif //JEUQT_RUNSCENE_H
