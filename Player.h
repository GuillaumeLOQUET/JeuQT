//
// Created by Guillaume LOQUET on 14/04/2020.
//

#ifndef JEUQT_PLAYER_H
#define JEUQT_PLAYER_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QWidget>
#include <QTime>
#include <QTimer>


#include "Utils.h"


class Player : public QGraphicsPixmapItem {


private :

    bool pressUp = false; //true if the player press the up key
    bool pressDown = false; //true if the player press the down key
    bool pressLeft = false; //true if the player press the left key
    bool pressRight = false; //true if the player press the right key

    bool jump = false ; //true if the player is in a jump
    bool inAir = true ; //true if the player is in the air
    bool orientation = true ; //true if the player look at the right else left
    bool playerDown = false ; //true if the player is down because of a module

    int xSpeed = 10; // Speed value in X axis

    int speedJump = 0 ; // Value of the speed in Y direction (20 if the player jump else 0)

    QPointF posbase ; //Use to set a point (base of the jump) to get the travel with the gravity
    QTime time_jump; //Time at the beginning of the jump to get the travel with the gravity
    QTime delayJump ; //Time at the end of the jump, to not jump just after.


public:
//Constructor
    Player( QString imageFileName) : QGraphicsPixmapItem(QPixmap(imageFileName)) {}

//Function
    int getMoveX();
    void changeImage(); // Change the appearance of the player according to his movement


//Getters
    int getMoveY() const { return speedJump ;}
    bool isJump() const { return jump; }
    bool isInAir() const { return inAir; }
    bool isDown() const { return playerDown; }
    QTime* getTimeJump() { return &time_jump ;}
    QTime* getDelayJump() { return &delayJump ;}
    QPointF getPosBase() { return posbase ;}

    bool getPressUp();
    bool getPressDown();
    bool getPressLeft();
    bool getPressRight();

//Setters
    void setPressUp(bool x);
    void setPressDown(bool x);
    void setPressLeft(bool x);
    void setPressRight(bool x);

    void setMoveY(int r) { speedJump = r ;}

    void setJump(bool j) {jump = j ;}
    void setInAir(bool j) {inAir = j ;}
    void setPosBase(QPointF po){posbase = po ;};

};


#endif //JEUQT_PLAYER_H
