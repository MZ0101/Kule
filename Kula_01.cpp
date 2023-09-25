#include "Kula_01.h"
#include <QDebug>


Kula_01::Kula_01(QWidget* parent) : QWidget(parent)
{
    this->main_view.setRenderHint(QPainter::Antialiasing);

    this->button = new QPushButton();
    this->button->setText("Add ball");

    this->for_label = "Balls (max " + QString::number(this->balls_number) + " ): ";

    this->number_balls = new QLabel(this->for_label +"0");
    this->number_balls->setWordWrap(true);
   

    this->ball_data_vertical = new QVBoxLayout();
    this->ball_data_vertical->setAlignment(Qt::AlignTop);
    this->ball_data_vertical->addWidget(this->button);
    this->ball_data_vertical->addWidget(this->number_balls);

    this->ball_data = new QGroupBox();
    this->ball_data->setTitle("Ball data");

    this->main_scene.setSceneRect(QRect(0, 0, 800, 600));

    this->main_view.setFixedSize(800, 600);
    this->main_view.setScene(&this->main_scene);
   // this->main_view.setBackgroundBrush(QBrush(Qt::green));

    this->main_view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->main_view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->ball_data->setLayout(this->ball_data_vertical);
    this->main_horisontal.addWidget(this->ball_data);
    this->main_horisontal.addWidget(&this->main_view);
    this->setLayout(&this->main_horisontal);

    this->timer.start(50);
    this->timer_1.start(2000);

    QObject::connect(&this->timer, &QTimer::timeout, this, &Kula_01::balls_moving);

    QObject::connect(this->button, &QPushButton::clicked, this, &Kula_01::balls_spawn);

   //QObject::connect(&this->timer_1, &QTimer::timeout,  this, &Kula_01::balls_spawn);
}

void Kula_01::balls_moving()
{
    for (Kula* kula_1 : this->balls_array)
    {
        //qDebug() << kula_1->pos().y();

        kula_1->setPos(kula_1->x() + kula_1->x_velocity, kula_1->y() + kula_1->y_velocity);

        if (kula_1->pos().y() <= 0 || kula_1->pos().y() + 2 * kula_1->r > this->main_scene.height())
        {
            kula_1->y_velocity = -kula_1->y_velocity;

            if (kula_1->pos().y())
            {
                kula_1->setPos(kula_1->pos().x(), this->main_scene.height() - 2 * kula_1->r);
               // kula_1->y_velocity *= 0.8;
               // kula_1->x_velocity *= 0.99;
               // if (!kula_1->y_velocity) kula_1->g = 0;
                //qDebug() << kula_1->y_velocity;

            }
            else
            {
                kula_1->setPos(kula_1->pos().x(), 0);
               kula_1->setPos(kula_1->x() + kula_1->x_velocity, kula_1->y());
            }


        }
        //if (kula_1->y_velocity != 0 && kula_1->g == 0) kula_1->g = 0.0;


        //kula_1->y_velocity = kula_1->y_velocity + kula_1->g;

        if (kula_1->pos().x() <= 0 || kula_1->pos().x() + 2 * kula_1->r > this->main_scene.width())
        {
            kula_1->x_velocity = -kula_1->x_velocity;
           // kula_1->x_velocity *= 0.95;
            kula_1->setPos(kula_1->x() + kula_1->x_velocity, kula_1->y());
        }


        kula_1->get_center();

        for (Kula* kula_2 : this->balls_array)
        {
            if (kula_1 != kula_2)
            {
                kula_2->get_center();

                qreal deltax = kula_2->center.x() - kula_1->center.x();
                qreal deltay = kula_2->center.y() - kula_1->center.y();


                qreal distance = std::sqrt(deltax * deltax + deltay * deltay);
                // qreal distance = (deltax * deltax + deltay * deltay);

                if (distance < (kula_1->r + kula_2->r))
                {

                    qreal overlap = (kula_1->r + kula_2->r) - distance;

                    if (distance)
                    {
                        qreal moveX = (deltax / distance) * overlap;
                        qreal moveY = (deltay / distance) * overlap;
                        qreal overlap = (kula_1->r + kula_2->r) - distance;
           
                        if (deltax > 0)
                        {
                            kula_1->setPos(kula_1->pos().x() + moveX, kula_1->pos().y());
                            kula_2->setPos(kula_2->pos().x() - moveX, kula_2->pos().y());
                        }
                        else
                        {
                            kula_1->setPos(kula_1->pos().x() - moveX, kula_1->pos().y());
                            kula_2->setPos(kula_2->pos().x() + moveX, kula_2->pos().y());
                        }

                        if (deltay > 0)
                        {
                            kula_1->setPos(kula_1->pos().x(), kula_1->pos().y() + moveY);
                            kula_2->setPos(kula_2->pos().x(), kula_2->pos().y() - moveY);
                        }

                        else
                        {
                            kula_1->setPos(kula_1->pos().x(), kula_1->pos().y() - moveY);
                            kula_2->setPos(kula_2->pos().x(), kula_2->pos().y() + moveY);
                        }

                        /*kula_1->setPos(kula_1->pos().x() - kula_1->x_velocity, kula_1->pos().y() - kula_1->y_velocity);
                        kula_2->setPos(kula_2->pos().x() - kula_2->x_velocity, kula_2->pos().y() - kula_2->y_velocity);*/

                        if (kula_2->x_velocity > 0)
                        {
                            kula_1->x_velocity = (((kula_1->m - kula_2->m) / (kula_1->m + kula_2->m)) * kula_1->x_velocity + ((2 * kula_2->m) / (kula_1->m + kula_2->m)) * kula_2->x_velocity);
                            kula_2->x_velocity = (((kula_2->m - kula_1->m) / (kula_1->m + kula_2->m)) * kula_2->x_velocity + ((2 * kula_1->m) / (kula_1->m + kula_2->m)) * kula_1->x_velocity);
                        }
                        else
                        {
                            kula_1->x_velocity *= -0.99;
                        }

                        if (kula_2->y_velocity > 0 && kula_2->pos().y() != this->main_scene.height() - 2*kula_2->r)
                        {
                            kula_1->y_velocity = (((kula_1->m - kula_2->m) / (kula_1->m + kula_2->m)) * kula_1->y_velocity + ((2 * kula_2->m) / (kula_1->m + kula_2->m)) * kula_2->y_velocity);
                            kula_2->y_velocity = (((kula_2->m - kula_1->m) / (kula_1->m + kula_2->m)) * kula_2->y_velocity + ((2 * kula_1->m) / (kula_1->m + kula_2->m)) * kula_1->y_velocity);
                            
                        }
                        else
                        {
                            kula_1->y_velocity *= -0.99;
                        }

                    }
                }
            }

        }
    }
}


void Kula_01::balls_spawn()
{
    if (this->balls_number > 0)
    {
        this->balls_array.push_back(new Kula());
        this->main_scene.addItem(this->balls_array.back());
        
        QPointF main_scene_midle = this->main_scene.sceneRect().center();
        

        QPointF ball_position;

        ball_position.setX(main_scene_midle.x() - this->balls_array.back()->boundingRect().width() / 2);
        ball_position.setY(main_scene_midle.y() - this->balls_array.back()->boundingRect().height() / 2);

        this->balls_array.back()->setPos(ball_position);
        this->balls_number--;

        this->number_balls->setText(this->for_label + QString::number(100 - this->balls_number));
        
    }
}

Kula_01::~Kula_01()
{
    
    QList<Kula*>::iterator it = this->balls_array.begin();
    while (it != this->balls_array.end())
    {
        Kula* pom = *it;
        it = this->balls_array.erase(it);  
        delete pom;
    }
    delete number_balls;
    delete button;
    delete ball_data_vertical;
    delete ball_data;
}