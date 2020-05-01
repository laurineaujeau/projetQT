//
// Created by lauri on 17/04/2020.
//
#include "MainScene.h"

#include <QMainWindow>
#include <QGraphicsView>
#include <QVector>
#include <QRect>
#include <QKeyEvent>
#ifndef PROJETQT_MAINWINDOW_H
#define PROJETQT_MAINWINDOW_H


class mainWindow : public QMainWindow{
    Q_OBJECT

private :
    MainScene* mainScene;
    QGraphicsView* mainView;
    QGraphicsView* menuView;


public:
    mainWindow(QWidget* parent = 0);
    virtual ~mainWindow() {};
};


#endif //PROJETQT_MAINWINDOW_H
