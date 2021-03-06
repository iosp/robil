#ifndef POINTITEM_H
#define POINTITEM_H

#include <QGraphicsItem>
#include <QGraphicsScene>

class CPointItem : public QGraphicsItem
{
public:
	CPointItem(QPointF p,QGraphicsScene* scene);
	CPointItem(QGraphicsScene* scene);
	~CPointItem();
	QRectF boundingRect() const;
	QPainterPath shape()  const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	QPointF getPoint();
	void setPointParam(QPointF p);
	bool isContainPoint(QPointF p);
	//CPointItem* getPressedPoint();
	void setRadius(int r);
	void SetColor(QColor color);

private:
	QGraphicsScene* pScene;
	QPointF point;
	float radius;
	QColor PointColor;
	QColor PointBrushColor;
};

#endif // POINTITEM_H
