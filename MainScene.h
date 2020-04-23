//
// Created by lauri on 17/04/2020.
//
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <QPainter>
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
    QGraphicsView * view;
    QList<RectItem*> rectangles;
    RectItem* trou;
    RectItem* arrivee;
    RectItem* finTrou;
    RectItem* hauteurMax;
    RectItem* LimiteMax;
    int etatAvatar;
    int etatPrecedent;
    bool isSaut;

public:
    MainScene();

    void drawBackground(QPainter *painter, const QRectF &rect);

    void keyPressEvent(QKeyEvent * event);

    AvatarItem* getItem(){
        return item;
    }

    int getEtatAvatar(){
        return etatAvatar;
    }
    void setEtatAvatar(int etatAvatar){
        this->etatAvatar=etatAvatar;
    }
    int getEtatPrecedent(){
        return etatPrecedent;
    }
    void setEtatPrecedent(int etatPrecedent){
        this->etatPrecedent=etatPrecedent;
    }
    void keyReleaseEvent(QKeyEvent * event);

    void gravity();

    //virtual ~MainScene();
public slots :
    void update();

};


#endif //PROJETQT_WINDOW_H
