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

mainWindow::mainWindow(QWidget *parent): QMainWindow(parent){
    //creation de la scene
    this->mainScene = new MainScene();
    AvatarItem* item = this->mainScene->getItem();

    //creation de la fenetre centree sur l'avatar
    QGraphicsView* avatarView = new QGraphicsView();
    avatarView->setScene(mainScene);
    avatarView->resize(300, 300);
    avatarView->setWindowTitle(item->getDescription());
    avatarView->centerOn(item);
    avatarView->show();

    //definitions des proprietes de la scene
    mainView = new QGraphicsView();
    mainView->setScene(mainScene);
    mainView->scale(1, 1);

    this->setCentralWidget(mainView);
    this->setWindowTitle("Main view");
    this->resize(1000, 600);


   /*QKeyEvent * event;
    mainScene->keyPressEvent(event);     //fonctions exécutées automatiquement
    mainScene->keyReleaseEvent(event);*/

}