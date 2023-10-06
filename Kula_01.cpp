#include "Kula_01.h"
#include <QDebug>


Kula_01::Kula_01(QWidget* parent) : QWidget(parent)
{
    this->main_view.setRenderHint(QPainter::Antialiasing);

    this->ball_data_vertical = new QVBoxLayout();
    this->ball_data_vertical->setAlignment(Qt::AlignTop);
    this->buttons = new QPushButton[6];

    QString buttnos_text[] = { "Add ball", "Gravity on", "Gravity off", "Turn gravity" ,"Randomize x velocity", "Randomize y velocity"};

    for (size_t i{ 0 }; i < 6; i++)
    {
        this->buttons[i].setText(buttnos_text[i]);
        this->ball_data_vertical->addWidget(&this->buttons[i]);
    }

    for (size_t i{ 1 }; i < 6; i++)
    {
        QObject::connect(&this->buttons[i], &QPushButton::clicked, this, &Kula_01::execute_for_buttons); 
    }

    // QObject::connect(&this->buttons[0], &QPushButton::clicked,this,&Kula_01::balls_spawn);

    this->for_number_balls = "Balls (max " + QString::number(this->balls_number) + " ): ";

    this->number_balls = new QLabel(this->for_number_balls + "0");
    this->number_balls->setWordWrap(true);
    this->number_balls->setAlignment(Qt::AlignCenter);
    this->number_balls->setFixedHeight(40);
    this->ball_data_vertical->addWidget(this->number_balls);

    this->gravity_option = new QLabel();
    this->gravity_option->setText("Gravity: on");
    this->ball_data_vertical->addWidget(this->gravity_option);

    this->ball_data = new QGroupBox();
    this->ball_data->setTitle("Ball data");

    this->main_scene.setSceneRect(QRect(0, 0, 800, 600));

    this->main_view.setFixedSize(800, 600);
    this->main_view.setScene(&this->main_scene);


    this->main_view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->main_view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->ball_data->setLayout(this->ball_data_vertical);
    this->main_horisontal.addWidget(this->ball_data);
    this->main_horisontal.addWidget(&this->main_view);
    this->setLayout(&this->main_horisontal);

    this->timer.start(35);
    this->timer_spawn.setInterval(150);

    QObject::connect(&this->timer, &QTimer::timeout, this, &Kula_01::balls_moving);
    QObject::connect(&this->buttons[0],&QPushButton::clicked,this,&Kula_01::balls_spawn);

    QObject::connect(&this->buttons[0], &QPushButton::pressed, this, [this]() {

        this->timer_spawn.start();
        QObject::connect(&this->timer_spawn, &QTimer::timeout,this,&Kula_01::balls_spawn);

        });

    QObject::connect(&this->buttons[0], &QPushButton::released, this, [this]() {

        this->timer_spawn.stop();
        QObject::disconnect(&this->timer_spawn, &QTimer::timeout, this, &Kula_01::balls_spawn);
        });
    
    this->balls_start_spawn();
}

void Kula_01::balls_start_spawn()
{
    for (uint j{ 0 }; j < 1; j++)
    {
        for (uint i{ 0 }; i < this->main_scene.width(); i += 4)
        {
            this->balls_array.push_back(new Kula());
            this->balls_array.back()->setPos(this->balls_array.back()->pos().x() + i, this->balls_array.back()->pos().y() +(4 *j));
            this->main_scene.addItem(this->balls_array.back());
        }
    }
    
}

void Kula_01::balls_moving()
{
    for (Kula* kula_1 : this->balls_array)
    {
        kula_1->y_velocity += kula_1->g;
        kula_1->setPos(kula_1->x() + kula_1->x_velocity, kula_1->y() + kula_1->y_velocity);

        for (Kula* kula_2 : this->balls_array)
        {
            if (kula_1 != kula_2)
            {
                kula_1->get_center();
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
                            kula_1->setPos(kula_1->pos().x() - moveX, kula_1->pos().y());
                            kula_2->setPos(kula_2->pos().x() + moveX, kula_2->pos().y());
                        }
                        else
                        {
                            kula_1->setPos(kula_1->pos().x() + moveX, kula_1->pos().y());
                            kula_2->setPos(kula_2->pos().x() - moveX, kula_2->pos().y());
                        }

                        if (deltay > 0)
                        {

                            kula_1->setPos(kula_1->pos().x(), kula_1->pos().y() - moveY);
                            kula_2->setPos(kula_2->pos().x(), kula_2->pos().y() + moveY);
                        }

                        else
                        {


                            kula_1->setPos(kula_1->pos().x(), kula_1->pos().y() + moveY);
                            kula_2->setPos(kula_2->pos().x(), kula_2->pos().y() - moveY);

                        }

                        kula_1->x_velocity = (((kula_1->m - kula_2->m) / (kula_1->m + kula_2->m)) * kula_1->x_velocity + ((2 * kula_2->m) / (kula_1->m + kula_2->m)) * kula_2->x_velocity);
                        kula_2->x_velocity = (((kula_2->m - kula_1->m) / (kula_1->m + kula_2->m)) * kula_2->x_velocity + ((2 * kula_1->m) / (kula_1->m + kula_2->m)) * kula_1->x_velocity);


                        kula_1->y_velocity = (((kula_1->m - kula_2->m) / (kula_1->m + kula_2->m)) * kula_1->y_velocity + ((2 * kula_2->m) / (kula_1->m + kula_2->m)) * kula_2->y_velocity);
                        kula_2->y_velocity = (((kula_2->m - kula_1->m) / (kula_1->m + kula_2->m)) * kula_2->y_velocity + ((2 * kula_1->m) / (kula_1->m + kula_2->m)) * kula_1->y_velocity);
                    }
                }
            }
        }

        if (kula_1->pos().y() <= 0)
        {
                kula_1->y_velocity = -kula_1->y_velocity;
                kula_1->setPos(kula_1->pos().x(), 0);
                
                kula_1->y_velocity *= 0.90;
                kula_1->x_velocity *= 0.95;
        }
        else if (kula_1->pos().y() + 2 * kula_1->r > this->main_scene.height())
        {
            kula_1->y_velocity = -kula_1->y_velocity;

            kula_1->setPos(kula_1->pos().x(), this->main_scene.height() - 2 * kula_1->r);

            kula_1->y_velocity *= 0.8;
            kula_1->x_velocity *= 0.90;
        }

        if (kula_1->pos().x() <= 0 || kula_1->pos().x() + 2 * kula_1->r > this->main_scene.width())
        {
            kula_1->x_velocity = -kula_1->x_velocity;
            kula_1->x_velocity *= 0.90;

            if (kula_1->pos().x() > 400)
            {
                kula_1->setPos(this->main_scene.width() - 2 * kula_1->r, kula_1->y());
            }
            else
            {
                kula_1->setPos(0, kula_1->y());
            }
            kula_1->setPos(kula_1->x() + kula_1->x_velocity, kula_1->y());
        }
    }
}

void Kula_01::balls_spawn()
{

    if (this->balls_number > 0)
    {
        double gravity_end_ball{0.981};

        if (!this->balls_array.empty())
        {
            gravity_end_ball = this->balls_array.back()->g;
           
        }

        this->balls_array.push_back(new Kula());
        this->balls_array.back()->g = gravity_end_ball;
        this->main_scene.addItem(this->balls_array.back());
        
       
        QPointF main_scene_midle = this->main_scene.sceneRect().center();
        
        QPointF ball_position;

        ball_position.setX(main_scene_midle.x() - this->balls_array.back()->boundingRect().width() / 2);
        ball_position.setY(main_scene_midle.y() - this->balls_array.back()->boundingRect().height() / 2);

        this->balls_array.back()->setPos(ball_position);
        this->balls_number--;

        this->number_balls->setText(this->for_number_balls + QString::number(100 - this->balls_number));
    }
}

void Kula_01::execute_for_buttons()
{
    QPushButton* button_clicked = qobject_cast<QPushButton*>(sender());

    if (button_clicked == &this->buttons[1])
    {
        for (Kula* kula_1 : this->balls_array)
        {
            kula_1->g = 0.0981;
            this->gravity_option->setText("Gravity: on");
        }
    }
    else if (button_clicked == &this->buttons[2])
    {
        for (Kula* kula_1 : this->balls_array)
        {
            kula_1->g = 0;
            this->gravity_option->setText("Gravity: off");
        }
    }
    else if(button_clicked == &this->buttons[3])
    {
        for (Kula* kula_1 : this->balls_array)
        {
            kula_1->g = -0.0981;
            this->gravity_option->setText("Gravity: turn");
        }
    }
    else if(button_clicked == &this->buttons[4])
    {
        for (Kula* kula_1 : this->balls_array)
        {
            kula_1->x_velocity = std::rand() % 21 - 10;
            //this->gravity_option->setText("Gravity: off");
        }
    }
    else
    {
        for (Kula* kula_1 : this->balls_array)
        {
            kula_1->y_velocity = std::rand() % 21 - 10;
            //this->gravity_option->setText("Gravity: off");
        }
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
    delete gravity_option;
    delete [] buttons;
   
    delete ball_data_vertical;
    delete ball_data;
}