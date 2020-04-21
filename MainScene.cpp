//
// Created by lauri on 17/04/2020.
//

//#include <QGraphicsScene>
//#include <QGraphicsView>
//#include <QPainter>
//#include <QGraphicsPixmapItem>
//#include <QTimer>
//#include <QVector>
//#include <QPointF>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QLabel>
#include <iostream>
#include <QKeyEvent>
#include "MainScene.h"
using namespace std;
MainScene::MainScene(){

    this->background.load("foret.jpg");
    this->setSceneRect(0, 0, this->background.width(), this->background.height());

    this->timer = new QTimer(this);
    this->timer->start(30);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    this->item = new AvatarItem("Personnage", "personnage.png");
    this->item->setPos(this->width()-810, this->height()/2.1 );
    this->addItem(item);

}
void MainScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}
void MainScene::update() {

    // view update
    view = new QGraphicsView();
    view->centerOn(this->item);
}


void MainScene::keyPressEvent(QKeyEvent * event){

    //Déplacement  vers la gauche
    if(event->key() == Qt::Key_A) { // 75=gauche
        cout<< "gauche"<< endl;
        this->item->move("gauche");
    }
    //Déplacement vers la droite
    if(event->key() == Qt::Key_Z) { // 77=droite
        cout << "droite" << endl;
        this->item->move("droite");
    }
    //Déplacement vers le haut
    if(event->key() == Qt::Key_E) { //72=haut
        cout<< "haut"<< endl;
        this->item->move("haut");
        this->item->move("bas");
    }
    //sauter
    if(event->key() == Qt::Key_R) { //=sauter
        cout<< "sauter"<< endl;

    }
}