#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QTime>
#include "mainWindow.h"
using namespace std;
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    mainWindow* fenetre=new mainWindow();
    fenetre->show();

    return app.exec();
}
