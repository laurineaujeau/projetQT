//
// Created by lauri on 17/04/2020.
//
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QLCDNumber>

#include <QRect>
#include <QLabel>

#ifndef PROJETQT_WINDOW_H
#define PROJETQT_WINDOW_H
#include "AvatarItem.h"
#include "RectItem.h"

using namespace std;
class MainScene: public QGraphicsScene{
    Q_OBJECT;

private :

    QPixmap background ;
    AvatarItem* item;
    QTimer * timer;
    QTime * temps;
    QGraphicsView * view;
    QList<RectItem*> rectangles;
    RectItem* trou;
    RectItem* arrivee;
    RectItem* finTrou;
    RectItem* hauteurMax;
    RectItem* LimiteMax;
    QLCDNumber * chronometre;
    int etatAvatar;
    int etatPrecedent;
    int etatPrecedent2;
    bool isSaut;
    int itemID;
    int chrono;

public:
    MainScene();

    void drawBackground(QPainter *painter, const QRectF &rect);

    void keyPressEvent(QKeyEvent * event);

    void keyReleaseEvent(QKeyEvent * event);

    void AfficherChrono();
    void AfficherChrono2();

    //GETTERS
    AvatarItem* getItem(){
        return item;
    }
    int getEtatAvatar(){
        return etatAvatar;
    }
    int getEtatPrecedent(){
        return etatPrecedent;
    }
    int getEtatPrecedent2(){
        return etatPrecedent2;
    }
    int getItemID(){
        return 0;
    }
    //SETTERS

    void setEtatAvatar(int etatAvatar){
        this->etatAvatar=etatAvatar;
    }
    void setEtatPrecedent(int etatPrecedent){
        this->etatPrecedent=etatPrecedent;
    }
    void setEtatPrecedent2(int etatPrecedent2){
        this->etatPrecedent2=etatPrecedent2;
    }

    //virtual ~MainScene();
public slots :
    void update();

};


#endif //PROJETQT_WINDOW_H
