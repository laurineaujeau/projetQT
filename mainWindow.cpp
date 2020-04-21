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
mainWindow::mainWindow(QWidget *parent): QMainWindow(parent)
{
    this->mainScene = new MainScene();
    AvatarItem* item = this->mainScene->getItem();

    QGraphicsView* avatarView = new QGraphicsView();
    avatarView->setScene(mainScene);
    //avatarView->scale(0.5, 0.5);
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

    QKeyEvent * event;
    mainScene->keyPressEvent(event);
}