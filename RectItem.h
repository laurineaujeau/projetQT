//
// Created by lauri on 21/04/2020.
//

#ifndef PROJETQT_RECTITEM_H
#define PROJETQT_RECTITEM_H
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QObject>
#include <QPen>

class RectItem : public QGraphicsRectItem {
    //O_OBJECT;
public:
    RectItem(int x, int y, int width, int height);
};


#endif //PROJETQT_RECTITEM_H
