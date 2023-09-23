#pragma once
#include <QtWidgets/QWidget>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QList>


#include "Kula.h"


class Kula_01 : public QWidget
{
    Q_OBJECT

public:
    Kula_01(QWidget* parent = nullptr);
    ~Kula_01();

    QGraphicsScene main_scene;
    QGraphicsView main_view;

    QGroupBox* ball_data = nullptr;

    QVBoxLayout* ball_data_vertical = nullptr;
    QHBoxLayout main_horisontal;

    Kula ball_1;
    QPushButton* button = nullptr;

    QTimer timer;
    QTimer timer_1;
    int balls_number { 200 };

    QList <Kula *> balls_array;

    //void balls_cllision();

public slots:
    void balls_moving();
    
    void balls_spawn();

};