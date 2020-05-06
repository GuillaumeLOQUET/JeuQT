//
// Created by Guillaume LOQUET on 14/04/2020.
//

#include "Player.h"
#include <QWidget>
#include <QPointF>
#include <QTime>

//Functions
void Player::changeImage() {
    // get the orientation of the player
    if(this->pressLeft && !this->pressRight){
        orientation = false ;
    }else if(!this->pressLeft && this->pressRight){
        orientation = true ;
    }
    // the bounding rectangle of the player is != if the player is up or down, we need to change the position
    this->setPos(this->pos().x(), this->pos().y() + this->boundingRect().height());

    if(!this->orientation){
        if(this->pressDown){
            this->setPixmap(QPixmap("player/playerDownL.png"));
            this->setPos(this->pos().x(), this->pos().y() - this->boundingRect().height());
        }else{
            this->setPixmap(QPixmap("player/playerUpL.png"));
            this->setPos(this->pos().x(), this->pos().y() - this->boundingRect().height());
            if(this->collidingItems().size() != 0){ //If a module is above the player
                this->setPos(this->pos().x(), this->pos().y() + this->boundingRect().height());
                this->setPixmap(QPixmap("player/playerDownL.png"));
                this->setPos(this->pos().x(), this->pos().y() - this->boundingRect().height());
                playerDown = true ;
            }else {
                playerDown = false ;
            }
        }
    }else {
        if(this->pressDown){
            this->setPixmap(QPixmap("player/playerDownR.png"));
            this->setPos(this->pos().x(), this->pos().y() - this->boundingRect().height());
        }else{
            this->setPixmap(QPixmap("player/playerUpR.png"));
            this->setPos(this->pos().x(), this->pos().y() - this->boundingRect().height());
            if(this->collidingItems().size() != 0){ //If a module is above the player
                this->setPos(this->pos().x(), this->pos().y() + this->boundingRect().height());
                this->setPixmap(QPixmap("player/playerDownR.png"));
                this->setPos(this->pos().x(), this->pos().y() - this->boundingRect().height());
                playerDown = true ;
            }else {
                playerDown = false ;
            }
        }
    }

}

int Player::getMoveX() {

    if(this->pressLeft && !this->pressRight){
        if(this->pressDown || playerDown){
            return (int)(-xSpeed*3/4) ;
        }else{
            return -xSpeed ;
        }
    }else if(!this->pressLeft && this->pressRight){
        if(this->pressDown || playerDown){
            return (int)(xSpeed*3/4) ;
        }else{
            return xSpeed ;
        }
    }else{
        return 0 ;
    }
}


//Getters

bool Player::getPressUp() {
    return this->pressUp;
}

bool Player::getPressDown() {
    return this->pressDown;
}

bool Player::getPressLeft() {
    return this->pressLeft;
}

bool Player::getPressRight() {
    return this->pressRight;
}



//Setters

void Player::setPressUp(bool x) {
    pressUp = x ;
}

void Player::setPressDown(bool x) {
    pressDown = x ;
}

void Player::setPressLeft(bool x) {
    pressLeft = x ;
}

void Player::setPressRight(bool x) {
    pressRight = x ;
}






