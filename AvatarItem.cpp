//
// Created by lauri on 17/04/2020.
//
#include <QTimer>
#include "AvatarItem.h"
using namespace std;
void AvatarItem::move(string direction) {

    QPointF pos = this->pos();
    //Déplacement  vers la gauche
    if(direction=="gauche") { // 75=gauche
        int newX = pos.x() + speed;
        this->setPos(newX, pos.y());
    }
    //Déplacement vers la droite
    if(direction=="droite") { // 77=droite
        int newX = pos.x() - speed;
        this->setPos(newX, pos.y());
    }
    //Déplacement vers le haut
    if(direction=="haut") { //72=haut

       int Y = pos.y();
      // int X = pos.x();
       //int hauteur = Y+40;
       //int largeur = X+40;
      // QTimer timer;
     //  QTimer tFinal;
       //tFinal = constantTime(1000);
      // timer.start(1000);
       // QTimer :: singleShot ( 1000 ,this , SLOT ( quit()));
       //while (timer.isActive()){
      // while (timer.setInterval(1000)){
               int newY = pos.y() - 15;
               this->setPos(pos.x(), newY);
      //     }
      // }


    }
    /*if(direction=="bas") {
        for(int t=0; t<100; t++) {
            int newY = pos.y() + 60;
            this->setPos(pos.x(), newY);
        }
    }*/

}
void AvatarItem::updateD(int X,int Y,int hauteur,int largeur){
    QPointF pos = this->pos();
    if ( pos.y() == hauteur && pos.x() == largeur){
        hauteur = Y;
        largeur = X+80;
    }
    if ( pos.y() < hauteur && pos.x() < largeur){
        this->setPos(pos.x()+5,pos.y()+5);
    }
    if ( pos.y() > hauteur && pos.x() < largeur){
        this->setPos(pos.x()+5,pos.y()-5);
    }
}
