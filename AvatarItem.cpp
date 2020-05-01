//
// Created by lauri on 17/04/2020.
//
#include <QTimer>
#include "AvatarItem.h"
using namespace std;
void AvatarItem::move(string direction) {

    QPointF pos = this->pos();

    //Déplacement  vers la gauche
    if (direction == "gauche") {
        int newX = int(pos.x()) + speed;
        this->setPos(newX, pos.y());
    }

    //Déplacement vers la droite
    if (direction == "droite") {
        int newX = int(pos.x()) - speed;
        this->setPos(newX, pos.y());
    }

    //Déplacement vers le haut
    if (direction == "haut") { //monte tout droit

        int newY = int(pos.y()) - speed*2;
        this->setPos(pos.x(), newY);
    }
    if (direction == "haut+") { // monte legerement afin d'éviter la collision constante avec le sol
        int newY = int(pos.y()) - speed;
        this->setPos(pos.x(), newY);
    }
    if (direction == "sauter") { // monte en diagonale
        int newY = int(pos.y()) - speed*2;
        int newX = int(pos.x()) + 12;
        this->setPos(newX, newY);

    }

    //Déplacement vers le bas
    if (direction == "bas") { //descend en diagonale
        int newY = int(pos.y()) + 4 * 2;
        int newX = int(pos.x()) + 8;
        this->setPos(newX, newY);
    }
    if (direction == "tomber") { // descend tout droit
        int newY = int(pos.y()) + 6;
        this->setPos(pos.x(), newY);
    }

    //Arreter le déplacement
    if (direction == "stop") {
        this->setPos(pos.x(), pos.y());
    }
}