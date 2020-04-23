//
// Created by lauri on 21/04/2020.
//

#include "RectItem.h"
RectItem::RectItem(int x, int y, int width, int height){
    setRect(x,y,width,height);
    boundingRect();
    QPen pen;
    pen.setColor(Qt::blue);
}