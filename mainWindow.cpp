//
// Created by lauri on 17/04/2020.
//
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QRectF>
#include <QVector>
#include "mainWindow.h"
//#include "Menu.h"
mainWindow::mainWindow(QWidget *parent): QMainWindow(parent)
{
  /*  this->menu = new Menu();

    QGraphicsView* menuView = new QGraphicsView();
    menuView->setScene(menu);
    menuView->resize(1100, 700);
    menuView->scale(1, 1);
    menuView->setWindowTitle("Menu");
    menuView->show();*/


    this->mainScene = new MainScene();
    AvatarItem* item = this->mainScene->getItem();


    QGraphicsView* avatarView = new QGraphicsView();
    avatarView->setScene(mainScene);
    avatarView->resize(300, 300);
    avatarView->setWindowTitle(item->getDescription());
    avatarView->centerOn(item);
    avatarView->show();


    mainView = new QGraphicsView();
    mainView->setScene(mainScene);
    mainView->scale(1, 1);

    this->setCentralWidget(mainView);
    this->setWindowTitle("Main view");
    this->resize(1000, 600);


   /*QKeyEvent * event;
    mainScene->keyPressEvent(event);
    mainScene->keyReleaseEvent(event);*/
   // cout<<"bouh"<<endl;
}