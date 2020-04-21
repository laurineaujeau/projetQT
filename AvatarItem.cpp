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
    if(direction=="droite") { // 77=droitea
        int newX = pos.x() - speed;
        this->setPos(newX, pos.y());
    }
    //Déplacement vers le haut
    if(direction=="haut") { //72=haut

       int Y = pos.y();
      // int X = pos.x();
      int hauteur = Y-80;
        cout<< "hello"<< endl;
        cout<< pos.y()<< endl;
      while(int(pos.y())>hauteur){
          cout<< "coucou"<< endl;
          int newY = int(pos.y()) - speed;
          cout<< pos.y()<< endl;
          this->setPos(pos.x(), newY);
      }

    }
    if(direction=="stop") {
            this->setPos(pos.x(), pos.y());
    }

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
