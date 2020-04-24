//
// Created by lauri on 24/04/2020.
//

#ifndef PROJETQT_MENU_H
#define PROJETQT_MENU_H

#include <QGraphicsScene>
#include <QPainter>
class Menu : public QGraphicsScene {
private:
    QPixmap background ;
public:
    Menu();

    void drawBackground(QPainter *painter, const QRectF &rect);
};


#endif //PROJETQT_MENU_H
