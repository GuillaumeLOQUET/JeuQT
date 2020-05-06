//
// Created by Guillaume LOQUET on 20/04/2020.
//

#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>
#include "Launcher.h"
#include "MainWindow.h"
#include <iostream>
#include <fstream>

Launcher::Launcher() {
    // build all of menu elements
    this->background.load("menu/fondMenu.png");
    this->setSceneRect(0, 0, background.width(), background.height());

    resultLabel = new QLabel();
    resultLabel->setStyleSheet("background-image:url(menu/backgroundResult.png);"
                               "background-color: transparent;");
    resultLabel->setFont(QFontDatabase().font("Jeuqt","regular",40));
    resultLabel->setGeometry(150 ,50  ,700,300);
    resultLabel->setAlignment(Qt::AlignCenter);
    result = addWidget(resultLabel);

    startButton = new QPushButton("Start");
    startButton->setFont(QFontDatabase().font("Jeuqt","regular",70));
    startButton->setStyleSheet("background-image:url(menu/buttonStart.png);"
                               "background-color: transparent;");

    startButton->setGeometry(400 ,100  ,400,100);
    start = addWidget(startButton);

    exitButton = new QPushButton("Quit");
    exitButton->setFont(QFontDatabase().font("Jeuqt","regular",70));
    exitButton->setStyleSheet("background-image:url(menu/quitButton.png);"
                               "background-color: transparent;");
    exitButton->setGeometry(400 ,300  ,400,100);
    exit = addWidget(exitButton);

    sceneSwitchButton = new QPushButton("View Scene Off");
    sceneSwitchButton->setFont(QFontDatabase().font("Jeuqt","regular",22));
    sceneSwitchButton->setStyleSheet("background-image:url(menu/switchScene.png);"
                              "background-color: transparent;");
    sceneSwitchButton->setGeometry(0 ,200  ,200,50);
    sceneswtch = addWidget(sceneSwitchButton);

    restartButton = new QPushButton("Restart");
    restartButton->setFont(QFontDatabase().font("Jeuqt","regular",70));
    restartButton->setStyleSheet("background-image:url(menu/buttonStart.png);"
                               "background-color: transparent;");

    restartButton->setGeometry(50 ,400  ,400,100);
    restart = addWidget(restartButton);

    backButton = new QPushButton("Back");
    backButton->setFont(QFontDatabase().font("Jeuqt","regular",70));
    backButton->setStyleSheet("background-image:url(menu/quitButton.png);"
                                 "background-color: transparent;");

    backButton->setGeometry(500 ,400  ,400,100);
    back = addWidget(backButton);



}


// View
void Launcher::menuView() {
    //Main Menu
    disconnect(this->backButton, SIGNAL(clicked()),this,SLOT(menuView()));

    startButton->setVisible(true);
    exitButton->setVisible(true);
    sceneSwitchButton->setVisible(true);
    backButton->setVisible(false);
    restartButton->setVisible(false);
    resultLabel->setVisible(false);

    connect(this->sceneSwitchButton, SIGNAL(clicked()),this,SLOT(changeSceneSwitch()));
}

void Launcher::endGameView(int score) {
    // View at the end of the run
    disconnect(this->sceneSwitchButton, SIGNAL(clicked()),this,SLOT(changeSceneSwitch()));

    startButton->setVisible(false);
    exitButton->setVisible(false);
    sceneSwitchButton->setVisible(false);
    backButton->setVisible(true);
    restartButton->setVisible(true);
    resultLabel->setVisible(true);

    // Get the last score
    std::ifstream tmp("score.txt");

    std::string mot;
    tmp >> mot;
    int lastscore = atoi(mot.c_str());

    // Print the result according to the score
    if(lastscore == 0){
        QString text = "Congratulation\nYou are the first champion\nYou finished in : " + QString::number(score/1000)+":"+QString::number(score/100%10) ;
        resultLabel->setText(text);

        // Write the new score in the .txt
        std::ofstream flux("score.txt");
        if(flux){
            flux << score;
        }
    }else if(lastscore > score){
        QString text = "Congratulation\nYou are the new champion\nYou finished in : " + QString::number(score/1000)+":"+QString::number(score/100%10) ;
        resultLabel->setText(text);

        // Write the new score in the .txt
        std::ofstream flux("score.txt");
        if(flux){
            flux << score;
        }
    }else {
        QString text = "Well Done\nYou finished in : " + QString::number(score/1000)+":"+QString::number(score/100%10) + "\nThe score to beat is : " + QString::number(lastscore/1000)+":"+QString::number(lastscore/100%10);
        resultLabel->setText(text);
    }


    connect(this->backButton, SIGNAL(clicked()),this,SLOT(menuView()));
}

void Launcher::ScoreView() {
// Not implemented
}

void Launcher::changeSceneSwitch() {
    if(this->sceneSwitch){
        this->sceneSwitch = false ;
        sceneSwitchButton->setText("View Scene Off");
    }else{
        this->sceneSwitch = true ;
        sceneSwitchButton->setText("View Scene On");
    }
}

void Launcher::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

//getters
bool Launcher::getSceneSwitch() {
    return this->sceneSwitch;
}






