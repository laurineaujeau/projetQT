//
// Created by lauri on 24/04/2020.
//
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QRectF>
#include <QPixmap>
#include <iostream>
#include "Menu.h"
using namespace std;
Menu::Menu(){
    this->background.load("personnage.png");
    this->setSceneRect(0, 0, this->background.width(), this->background.height());
}
void Menu::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}