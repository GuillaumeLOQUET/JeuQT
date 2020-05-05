#include <iostream>
#include <QApplication>
#include <QTime>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    // init seed for random generation
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}
