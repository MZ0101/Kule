#include "Kula.h"

Kula::Kula(void)
{
	this->setRect(0,0,4,4);
	this->r = this->rect().width()/2;
	this->m = std::rand() % 5 + 1;
	this->x_velocity = ((std::rand() % 5 -2) + 1);
	//this->y_velocity = (std::rand() % 5  -3);
	
	this->setFlag(QGraphicsEllipseItem::ItemIsSelectable, true);
	
	
}

void Kula::get_center()
{
	this->center.setX(this->pos().x() - this->r);
	this->center.setY(this->pos().y() - this->r);
}


void Kula::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		this->setBrush(QBrush(Qt::red));
		this->m = 100;
	}
}