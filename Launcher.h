//
// Created by Guillaume LOQUET on 20/04/2020.
//

#ifndef JEUQT_MENU_H
#define JEUQT_MENU_H
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QAbstractButton>
#include <QPixmap>
#include <QtWidgets/QLabel>


class Launcher  : public QGraphicsScene {
Q_OBJECT

private :
    QPixmap background; // Background of the menu
    // Graphics widgets link to a widget
    QGraphicsProxyWidget* start ;
    QGraphicsProxyWidget* exit ;
    QGraphicsProxyWidget* sceneswtch ;
    QGraphicsProxyWidget* restart ;
    QGraphicsProxyWidget* back ;
    QGraphicsProxyWidget* result ;
    QGraphicsProxyWidget* tutorialL ;
    QGraphicsProxyWidget* tutorialB ;
    // Menu's widgets
    QPushButton* exitButton ;
    QPushButton* startButton;
    QPushButton* sceneSwitchButton;
    QPushButton* restartButton;
    QPushButton* backButton;
    QPushButton* tutorialButton;
    QLabel* resultLabel ;
    QLabel* tutorialLabel ;

    bool sceneSwitch = false ;// true -> show the all scene

public:
    //Constructor
    Launcher();
    //Getters
    QPushButton* getExit(){return exitButton;}
    QPushButton* getStartButton(){return startButton;}
    QPushButton* getRestartButton(){return restartButton;}
    //functions
    void drawBackground(QPainter* painter, const QRectF& rect);
    bool getSceneSwitch();

//Slots
public slots:
    void changeSceneSwitch();
    void ScoreView();
    void endGameView(int score);
    void menuView();
    void tutorialView();

};


#endif //JEUQT_MENU_H
