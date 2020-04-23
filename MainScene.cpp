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


    this->rectangles.push_back(new RectItem(0,434,233,74)); // premier sol
    this->rectangles.push_back(new RectItem(347,434,467,74));// deuxieme sol
    this->rectangles.push_back(new RectItem(515,355,112,78));//buisson
    this->rectangles.push_back(new RectItem(0,0,1,506)); //cadre gauche
    //this->rectangles.push_back(new RectItem(813,0,1,506));
    for(RectItem* rectangle : rectangles){
        this->addItem(rectangle);
        rectangle->setOpacity(1);
    }
    trou = new RectItem(270,417,50,89);
    this->addItem(trou);
    trou->setOpacity(1);
    arrivee = new RectItem(800,261,13,149);
    this->addItem(arrivee);
    arrivee->setOpacity(1);
    finTrou = new RectItem(234,506,111,1);
    this->addItem(finTrou);
    finTrou->setOpacity(1);
    hauteurMax = new RectItem(0,93,813,1);
    this->addItem(hauteurMax);
    hauteurMax->setOpacity(1);
}
void MainScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}
void MainScene::update() {

    // view update
    QGraphicsView * view = new QGraphicsView();
    view->centerOn(this->item);
    //gravity();
   // this->item->move("bas");
    //this->position = this->position + this->gravity*dt;
   // this->velocity = this->velocity + this->gravity*dt;
    for(RectItem* rectangle : rectangles){
        if (this->item->collidesWithItem(rectangle)){
            //setEtatAvatar(0);
            if (getEtatPrecedent()==1){
                this->item->move("droite");
            }
            else if (getEtatPrecedent()==2){
                this->item->move("gauche");
            }
            /*else if (getEtatPrecedent()==3){
                this->item->move("tomber");
            }
            else if (getEtatPrecedent()==4){
                this->item->move("bas");

            }*/
            /*else if (getEtatPrecedent()==0){
                this->item->move("stop");
            }*/
        }
        //else {
      //      this->item->move("tomber");   traverse le sol
      //  }
    }


    if (this->item->collidesWithItem(trou)){
        this->item->move("tomber");
    }
    if (this->item->collidesWithItem(finTrou)){
       // setEtatPrecedent(0);
        cout<< "perdu"<< endl;
    }
    if (this->item->collidesWithItem(arrivee)){
        //setEtatPrecedent(0);
        cout<< "gagné"<< endl;
    }
    //if (this->item->collidesWithItem(hauteurMax) || this->item->pos().y()<=240){
    if (isSaut){
        //setEtatPrecedent(0);
        //if(this->item->pos().y()<=415){
        //for(int t=0; t<20; t++){
        /*for(RectItem* rectangle : rectangles){

        if (this->item->collidesWithItem(rectangle)){
            isSaut=false;
        }
        this->item->move("bas");
        if (this->item->collidesWithItem(rectangle)){
            isSaut=false;
        }*/
        if(this->item->pos().x()>=0 && this->item->pos().x()<=355) {

        }
        //}
        //}
    cout<<this->item->pos().y()<<endl;

    }
    //etat update
    if (getEtatAvatar()==1){
        this->item->move("gauche");
        setEtatPrecedent(1);
    }
    else if (getEtatAvatar()==2){

        this->item->move("droite");
        setEtatPrecedent(2);
    }
    else if (getEtatAvatar()==3){
        isSaut=true;
        for(int t=0; t<20; t++){
            this->item->move("haut");
        }
        setEtatPrecedent(3);
    }
    else if (getEtatAvatar()==4){
       // for(int t=0; t<20; t++) {
        isSaut=true;
        this->item->move("sauter");
        //}
        setEtatPrecedent(4);

        /*this->position = Point(0,0);
        this->velocity = Vector(2,2);
        this->gravity = Vector(0,-2);
        float previousTime = 0;
        float currentTime = GetCurrentTime();
        while(true){
            previousTime=currentTime;
            currentTime=GetCurrentTime();
            float dt = currentTime-previousTime;
            if(dt>0,15*f){
                dt = 0,15*f;
            }
            update();
        }*/
    }
    else if (getEtatAvatar()==0){
        this->item->move("stop");
        setEtatPrecedent(0);
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
void MainScene::gravity(){

    if (getEtatAvatar()==4){
        this->item->move("bas+");
    }else{
        this->item->move("bas");
    }
}
