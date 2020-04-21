//
// Created by lauri on 17/04/2020.
//

#ifndef PROJETQT_PLANEITEM_H
#define PROJETQT_PLANEITEM_H
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <string>
using namespace std;
class AvatarItem : public QGraphicsPixmapItem  {

private :
    QString description;
    int speed;
    QKeyEvent * event;
    QTimer * timer;


public:

    AvatarItem(QString description, QString imageFileName) : QGraphicsPixmapItem(QPixmap(imageFileName)), description(description) {
        this->speed = 20;
    }

    void move(string direction);



    //GETTERS
    int getSpeed(){
        return speed;
    }
    QString getDescription() {
        return this->description;
    }

    //SETTERS
    void setDescription(QString description){
        this->description = description;
    }
    void setSpeed(int speed) {
        this->speed = speed;
    }
public slots :
    void updateD(int X,int Y,int hauteur,int largeur);

};




#endif //PROJETQT_PLANEITEM_H
