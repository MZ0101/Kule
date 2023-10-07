#pragma once

#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>

class Kula : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT
public:
	Kula();
	QPointF center;
	QTimer timer;
	qreal r{ 0 };
	qreal m{ 1 };
	
	qreal x_velocity{ 0.0 };
	qreal y_velocity{ 0.0};
	//qreal g = { 0.981 };

	void get_center();
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


private slots:
	
	
};
