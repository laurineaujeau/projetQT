//
// Created by lauri on 17/04/2020.
//
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <QPainter>
//#include <QLCDNumber>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QPushButton>
#include <QMainWindow>
#include <QRect>
#include <QLabel>
#include <QString>
#include <QObject>
#include <QWidget>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QTextEdit>
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
    QWidget* parent=0;
    QMessageBox* message;
    RectItem* LimiteMax;
    QString pseudo;
    QInputDialog* input;
    QWidget* boite;
    QPushButton *bouton1;
    QPushButton *bouton2;
    int etatAvatar;
    int etatPrecedent;
    int etatPrecedent2;
    bool isSaut;
    bool isActive;
    //int itemID;
    int chrono;

public:
    //Mise en place de la scene
    MainScene();

    //dessine la scene
    void drawBackground(QPainter *painter, const QRectF &rect);

    //évenement produit à la pression d'une touche clavier
    void keyPressEvent(QKeyEvent * event);

    //évenement produit à la levée d'une touche clavier
    void keyReleaseEvent(QKeyEvent * event);

    //Calcul le score du joueur et l'affiche
    void tempsFinal();

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
    //actualisation régulière de la scene
    void update();

    //lancement du jeu
    void partie();

    //quitter le jeu
    void quit();

};


#endif //PROJETQT_WINDOW_H
