//
// Created by lauri on 17/04/2020.
//

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QLabel>
#include <QRect>
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


    this->rectangles.push_back(new RectItem(0,424,233,82));
    this->rectangles.push_back(new RectItem(345,424,463,82));
    this->rectangles.push_back(new RectItem(515,345,112,74));
    for(RectItem* rectangle : rectangles){
        this->addItem(rectangle);
    }
}
void MainScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}
void MainScene::update() {

    // view update
    QGraphicsView * view = new QGraphicsView();
    view->centerOn(this->item);

    //etat update
    if (getEtatAvatar()==1){
        this->item->move("gauche");
    }
    else if (getEtatAvatar()==2){
        this->item->move("droite");
    }
    else if (getEtatAvatar()==3){
        this->item->move("haut");
    }
    else if (getEtatAvatar()==4){
        this->item->move("sauter");
    }
    else if (getEtatAvatar()==0){
        this->item->move("stop");
    }
}


void MainScene::keyPressEvent(QKeyEvent * event){

    //Déplacement  vers la gauche
    if(event->key() == Qt::Key_Right) { // 75=gauche
        cout<< "gauche"<< endl;
        setEtatAvatar(1);

    }
    //Déplacement vers la droite
    if(event->key() == Qt::Key_Left) { // 77=droite
        cout << "droite" << endl;
        setEtatAvatar(2);

    }
    //Déplacement vers le haut
    if(event->key() == Qt::Key_Up) { //72=haut
        cout<< "haut"<< endl;
        setEtatAvatar(3);

    }
    //sauter
    if(event->key() == Qt::Key_Space) { //=sauter
        setEtatAvatar(4);
        cout<< "sauter"<< endl;

    }
}
void MainScene::keyReleaseEvent(QKeyEvent * event){

    if(event->key() == Qt::Key_Left) {
        setEtatAvatar(0);

    }
    if(event->key() == Qt::Key_Right) {
        setEtatAvatar(0);

    }
    if(event->key() == Qt::Key_Up) {
        setEtatAvatar(0);

    }
    if(event->key() == Qt::Key_Space) {
        setEtatAvatar(0);

    }
}

