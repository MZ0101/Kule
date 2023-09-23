#include "Kula.h"

Kula::Kula(void)
{
	this->setRect(0,0,5,5);
	this->r = this->rect().width()/2;
    this->x_velocity = (std::rand()%5 +1) - 2;
    this->y_velocity = (std::rand()%5 +1) - 2;
	//this->timer.start(50);

    
}


void Kula::get_center()
{
	this->center.setX(this->pos().x() - this->r);
	this->center.setY(this->pos().y() - this->r);
}

void Kula::collision()
{

    QList<QGraphicsItem*> t = collidingItems(); // prawdopodobnie bardzo niewydajne

    for (QList<QGraphicsItem*>::iterator it = t.begin(); it != t.end(); ++it)
    {
        Kula* sphere = dynamic_cast<Kula*>(*it);

        if (sphere != this)
        {

            this->get_center();
            sphere->get_center();

            qreal deltax = sphere->center.x() - this->center.x();
            qreal deltay = sphere->center.y() - this->center.y();
            
            qreal distance = std::sqrt(deltax * deltax + deltay * deltay);
            //qreal distance = (deltax * deltax + deltay * deltay);
            
            if (distance < (this->r + sphere->r))
            {
                // Kolizja oparta na promieniach!
                qreal overlap = (this->r + sphere->r) - distance;
                
                if (distance)
                {
                    qreal moveX = (deltax / distance) * overlap;
                    qreal moveY = (deltay / distance) * overlap;

                    this->x_velocity = -this->x_velocity;
                    this->y_velocity = -this->y_velocity;
                    sphere->x_velocity = -sphere->x_velocity;
                    sphere->y_velocity = -sphere->y_velocity;
                    if (this->pos().x() > sphere->pos().x())
                    {
                        this->setPos(this->pos().x() + moveX, this->pos().y());
                        sphere->setPos(sphere->pos().x() - moveX, sphere->pos().y());
                        
                    }
                    else
                    {
                        this->setPos(this->pos().x() - moveX, this->pos().y());
                        sphere->setPos(sphere->pos().x() + moveX, sphere->pos().y());
                    }
                    if (this->pos().y() > sphere->pos().y())
                    {
                        this->setPos(this->pos().x() , this->pos().y() + moveY);
                        sphere->setPos(sphere->pos().x() , sphere->pos().y() - moveY);
                    }
                  
                    else
                    {
                        this->setPos(this->pos().x(), this->pos().y() - moveY);
                        sphere->setPos(sphere->pos().x(), sphere->pos().y() + moveY);
                    }
                    //this->collision();
                    
                }
               
            }
        }
    }
}