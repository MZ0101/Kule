#pragma once

#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsEllipseItem>

class Kula : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT
public:

	Kula(void);

	QPointF center;
	QTimer timer;
	float r{ 0 };
	int x_velocity{ 0 };
	int y_velocity{ 0 };

	void get_center();
	void collision();
private slots:
	
	
};
