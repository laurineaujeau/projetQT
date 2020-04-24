//
// Created by lauri on 24/04/2020.
//

#include "Menu.h"

Menu::Menu(){

    this->background.load("personnage.jpg");
    this->setSceneRect(0, 0, this->background.width(), this->background.height());
}
void Menu::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}