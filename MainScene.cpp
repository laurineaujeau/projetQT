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
#include <QMessageBox>
#include <iostream>
#include <QKeyEvent>
#include "MainScene.h"
using namespace std;
MainScene::MainScene(){
    this->input = new QInputDialog();
    bool ok= false;
    pseudo = this->input->getText(parent,"Bienvenue !", "Pseudo:",QLineEdit::Normal,QString(),&ok); //https://openclassrooms.com/fr/courses/1894236-programmez-avec-le-langage-c/1899971-apprenez-a-utiliser-les-boites-de-dialogue-usuelles

    while(ok && pseudo.isEmpty()){
        this->message->critical(parent,"Bienvenue !", "Veulliez remplir le champ");
        pseudo = this->input->getText(parent,"Bienvenue !", "Pseudo:",QLineEdit::Normal,QString(),&ok);
    }

    if (ok && !pseudo.isEmpty())
    {
        this->message->information(parent, "Bienvenue !", "Bonjour " + pseudo + ", le but du jeu est d'atteindre l'autre bout de la scene, utilisez les flêches pour vous déplacer et la barre espace pour sauter. Bonne Chance !");
        this->background.load("foret.jpg");
        this->setSceneRect(0, 0, this->background.width(), this->background.height());

        this->item = new AvatarItem("Personnage", "personnage.png");
        this->item->setPos(this->width()-810, this->height()/2.1 );
        this->addItem(item);
        partie();
    }else{
        return;
    }

}
void MainScene::partie(){
    if(boite->isEnabled()){
        delete boite;
    }
    delete item;
    //this->item->setPos(this->width()-810, this->height()/2.1 );
    //this->addItem(item);
    /*this->background.load("foret.jpg");
    this->setSceneRect(0, 0, this->background.width(), this->background.height());*/

    this->item = new AvatarItem("Personnage", "personnage.png");
    this->item->setPos(this->width()-810, this->height()/2.1 );
    this->addItem(item);

    this->timer = new QTimer(this);
    this->timer->start(30);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));


    this->rectangles.push_back(new RectItem(0,434,233,74)); // premier sol
    this->rectangles.push_back(new RectItem(350,434,467,74));// deuxieme sol
    this->rectangles.push_back(new RectItem(515,355,112,78));//buisson
    this->rectangles.push_back(new RectItem(0,0,1,506)); //cadre gauche
    for(RectItem* rectangle : rectangles){
        this->addItem(rectangle);
        rectangle->setOpacity(0);
    }
    trou = new RectItem(270,417,48,89);
    this->addItem(trou);
    trou->setOpacity(0);
    arrivee = new RectItem(800,261,13,149);
    this->addItem(arrivee);
    arrivee->setOpacity(0);
    finTrou = new RectItem(234,506,111,1);
    this->addItem(finTrou);
    finTrou->setOpacity(0);
    hauteurMax = new RectItem(0,10,813,1);
    this->addItem(hauteurMax);
    hauteurMax->setOpacity(0);
    LimiteMax = new RectItem(808,0,1,506);
    this->addItem(LimiteMax);
    LimiteMax->setOpacity(0);

    //this->chronometre = new QLCDNumber();
    //this->addItem(chronometre);lo
    //this->chronometre->setPos(1,1);

    this->temps = new QTime();
    this->temps->start();
}
void MainScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

void MainScene::update() {
    //AfficherChrono2();
    // view update

    QGraphicsView * view = this->views().at(getItemID());
    view->centerOn(this->item);

    //Collisions
    for(RectItem* rectangle : rectangles){
        if (this->item->collidesWithItem(rectangle)){

            if (getEtatPrecedent()==1){
                this->item->move("droite");
            }
            else if (getEtatPrecedent()==2){
                this->item->move("gauche");
            }
            else if (getEtatPrecedent()==3 || getEtatPrecedent()==4){
                this->item->move("haut+");
            }
        }
    }


    if (this->item->collidesWithItem(trou)){
        this->item->move("tomber");
    }
    if (this->item->collidesWithItem(finTrou)){
        setEtatAvatar(0);
        disconnect(timer, 0, 0, 0);
        boite = new QWidget();
        QLabel* text =new QLabel();
        text->setText("Perdu !");
        text->setMargin(15);
        text->setAlignment(Qt::AlignCenter);
        bouton1 = new QPushButton("Rejouer");
        bouton2 = new QPushButton("Quitter");

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(text);
        layout->addWidget(bouton1);
        layout->addWidget(bouton2);

        boite->setLayout(layout);
        boite->show();
        //if(bouton1->clicked())

       // quit();
        connect (bouton1, SIGNAL ( clicked ()), this , SLOT (partie()));
        connect (bouton2, SIGNAL ( clicked ()), this , SLOT (quit()));

    }
    if (this->item->collidesWithItem(arrivee)){
        setEtatAvatar(0);
        //this->item->move("tomber"); // c'est le disconnect qui fait arreter le perso
        this->chrono = temps->elapsed();
        AfficherChrono();
        disconnect(timer, 0, 0, 0);
    }
    if (this->item->collidesWithItem(LimiteMax)){
        setEtatAvatar(0);
        this->item->move("tomber");
    }
    if (this->item->collidesWithItem(hauteurMax)){
        if (getEtatPrecedent()==4){
            setEtatPrecedent2(4);
        }
        else{
            setEtatPrecedent2(3);
        }
        setEtatAvatar(0);
        isSaut= false;
        if (getEtatPrecedent2()==4){
            setEtatAvatar(4);
        }
        if (getEtatPrecedent2()==3){
            setEtatAvatar(3);
        }
    }


    //etat update
    if (getEtatAvatar()==0){
        this->item->move("stop");
        setEtatPrecedent(0);
    }
    else if (getEtatAvatar()==1){
        this->item->move("gauche");
        setEtatPrecedent(1);
    }
    else if (getEtatAvatar()==2){
        this->item->move("droite");
        setEtatPrecedent(2);
    }
    else if (getEtatAvatar()==3){
        setEtatPrecedent(3);
    }
    else if (getEtatAvatar()==4){
        setEtatPrecedent(4);

    }
    if (isSaut){
        if (getEtatAvatar()==3){
            this->item->move("haut");
        }
        else if (getEtatAvatar()==4){
            this->item->move("sauter");

        }
    }
    else{
        //cout<<this->item->pos().x()<<endl;
        if(this->item->pos().x()>=0 && this->item->pos().x()<=430) {
            //cout<<"if1"<<endl;
            if(this->item->pos().y()<=235){
                if (getEtatPrecedent()==4){
                    this->item->move("bas");
                }
                else{
                    this->item->move("tomber");
                }
            }
        }
        if(this->item->pos().x()>=600 && this->item->pos().x()<=813) {
            //cout<<"if2"<<endl;
            if(this->item->pos().y()<=235){
                if (getEtatPrecedent()==4){
                    this->item->move("bas");
                }
                else{
                    this->item->move("tomber");
                }
            }
        }
        if(this->item->pos().x()>430 && this->item->pos().x()<600) {
            //cout<<"if3"<<endl;
            if(this->item->pos().y()<=160){
                if (getEtatPrecedent()==4){
                    this->item->move("bas");
                }
                else{
                    this->item->move("tomber");
                }
            }
        }
    }
}


void MainScene::keyPressEvent(QKeyEvent * event){
    if (event->isAutoRepeat()){
        return;
    }
    //Déplacement  vers la gauche
    if(event->key() == Qt::Key_Right) {
        //cout<< "gauche"<< endl;
        setEtatAvatar(1);
    }
    //Déplacement vers la droite
    if(event->key() == Qt::Key_Left) {
        //cout << "droite" << endl;
        setEtatAvatar(2);
    }
    //Déplacement vers le haut
    if(event->key() == Qt::Key_Up) {
        //cout<< "haut"<< endl;
        setEtatAvatar(3);
        isSaut=true;
    }
    //sauter
    if(event->key() == Qt::Key_Space) {
        setEtatAvatar(4);
        isSaut=true;
        //cout<< "sauter"<< endl;
    }
}

void MainScene::keyReleaseEvent(QKeyEvent * event){
    if (event->isAutoRepeat()){
        return;
    }
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        setEtatAvatar(0);
    }
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Space ) {
        isSaut =false;
    }
}

void MainScene::AfficherChrono(){

   int heure = chrono/(60*60*1000);
   int minute = chrono/(60*1000) - heure*60;
   int seconde = chrono/(1000) - minute*60;
   int milliseconde = chrono - seconde*1000;
   if(heure>0){
       cout<<"Votre temps : "<<heure<<"h "<<minute<<"m "<<seconde<<","<<milliseconde<<"s"<<endl;
   }
   else if (minute>0){
       cout<<"Votre temps : "<<minute<<"m "<<seconde<<","<<milliseconde<<"s"<<endl;
   }
   else if (milliseconde<100){
       cout<<"Votre temps : "<<seconde<<",0"<<milliseconde<<"s"<<endl;
   }
   else{
       cout<<"Votre temps : "<<seconde<<","<<milliseconde<<"s"<<endl;
   }
}
void MainScene::AfficherChrono2(){

    int heure = chrono/(60*60*1000);
    int minute = chrono/(60*1000) - heure*60;
    int seconde = chrono/(1000) - minute*60;
    int milliseconde = chrono - seconde*1000;
    if(heure>0){
        //chronometre->addText()
    }
    else if (minute>0){
        cout<<"Votre temps : "<<minute<<"m "<<seconde<<","<<milliseconde<<"s"<<endl;
    }
    else if (milliseconde<100){
        cout<<"Votre temps : "<<seconde<<",0"<<milliseconde<<"s"<<endl;
    }
    else{
        cout<<"Votre temps : "<<seconde<<","<<milliseconde<<"s"<<endl;
    }
}
int MainScene::quit(){
    delete item;
    delete timer;
    //return -1; seg fault apres avoir fermé la page
}