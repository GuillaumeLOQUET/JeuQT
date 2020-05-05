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
    QPixmap background;
    QGraphicsProxyWidget* start ;
    QGraphicsProxyWidget* exit ;
    QGraphicsProxyWidget* sceneswtch ;
    QGraphicsProxyWidget* restart ;
    QGraphicsProxyWidget* back ;
    QGraphicsProxyWidget* result ;
    QPushButton* exitButton ;
    QPushButton* startButton;
    QPushButton* sceneSwitchButton;
    QPushButton* restartButton;
    QPushButton* backButton;
    QLabel* resultLabel ;
    bool sceneSwitch = false ;

public:
    Launcher();
    QPushButton* getExit(){return exitButton;}
    QPushButton* getStartButton(){return startButton;}
    QPushButton* getRestartButton(){return restartButton;}
    void drawBackground(QPainter* painter, const QRectF& rect);
    bool getSceneSwitch();


public slots:
    void changeSceneSwitch();
    void ScoreView();
    void endGameView(int score);
    void menuView();

};


#endif //JEUQT_MENU_H
