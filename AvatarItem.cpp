//
// Created by lauri on 17/04/2020.
//
#include <QTimer>
#include "AvatarItem.h"
using namespace std;
void AvatarItem::move(string direction) {

    QPointF pos = this->pos();
    //Déplacement  vers la gauche
    if(direction=="gauche") {
        int newX = int(pos.x()) + speed;
        this->setPos(newX, pos.y());
    }
    //Déplacement vers la droite
    if(direction=="droite") {
        int newX = int(pos.x()) - speed;
        this->setPos(newX, pos.y());
    }
    //Déplacement vers le haut
    if(direction=="haut") {
        int newY = int(pos.y()) - 31*2;
        this->setPos(pos.x(), newY);
    }
    if(direction=="stop") {
            this->setPos(pos.x(), pos.y());
    }
    if(direction=="bas") {
        //for(int t=0; t<20; t++){
            int newY = int(pos.y()) + 3 *2;
            int newX = int(pos.x()) + 3;
            this->setPos(newX, newY);
       // }
    }

    if(direction=="tomber") {
        int newY = int(pos.y()) + 6;
        this->setPos(pos.x(), newY);
    }
    if(direction=="sauter") {
        //for(int t=0; t<20; t++){
            int newY = int(pos.y()) - 31*2;
            int newX = int(pos.x()) + 31;
            this->setPos(newX, newY);
        //}
    }
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
            updateDt(dt);
        }
    }*/

}
/*void AvatarItem::updateDt(float dt){
    this->position = this->position + this->gravity*dt;
    this->velocity = this->velocity + this->gravity*dt;
}*/
