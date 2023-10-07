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
#include <thread>


#include "Kula.h"


class Kula_01 : public QWidget
{
    Q_OBJECT

public:
    Kula_01(QWidget* parent = nullptr);
    ~Kula_01();

    QGraphicsScene main_scene;
    QGraphicsView main_view;
    QHBoxLayout main_horisontal;
    qreal g{ 0.981 };

    QGroupBox* ball_data = nullptr;
    QVBoxLayout* ball_data_vertical = nullptr;
   
   QPushButton *buttons = nullptr;
   /*/ QPushButton* on_gravity = nullptr;
    QPushButton *turn_gravity = nullptr;*/
    QString for_number_balls;
    QTimer timer_move;
    QTimer timer_spawn;
    int balls_number { 100 };
    int balls_max{ 100 };

    QLabel *number_balls;
    QLabel* gravity_option;
    QList <Kula *> balls_array;

    //void balls_cllision();
    
    void balls_start_spawn();
  
public slots:
    void balls_moving();
    void balls_spawn();
  /*  void on_gravi();
    
    void turn_gravi();*/

    void execute_for_buttons();

};