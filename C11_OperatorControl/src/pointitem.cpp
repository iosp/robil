#include "pointitem.h"
#include <QPainter>
#include <QGraphicsScene>

CPointItem::CPointItem(QPointF p,QGraphicsScene* scene)
	//: QGraphicsItem(parent)
{
	pScene = scene;
	point = p;
	radius = 10;
	PointColor.setRgb(124,143,58);
	PointBrushColor.setRgb(124,143,58,180);
}
CPointItem::CPointItem(QGraphicsScene* scene)
{
	pScene = scene;
	point= QPointF(0,0);
	radius = 10;
	PointColor.setRgb(124,143,58);
	PointBrushColor.setRgb(124,143,58,180);
	
}
CPointItem::~CPointItem()
{
	//delete PressedPoint;
	//delete pScene;
}    
QPainterPath CPointItem::shape()  const 
{
	QPainterPath path;
	path.addEllipse(point.x()-radius/2, point.y()-radius/2, radius, radius);
	return path;
}
QRectF CPointItem::boundingRect()  const
{
    return QRectF(point.x()-radius/2, point.y()-radius/2, radius, radius);
	//return QRectF(0, 0, 950, 1000);
}
void CPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(QPen(PointColor));
	painter->setBrush(QBrush(PointBrushColor));
	painter->drawEllipse(point.x()-radius/2, point.y()-radius/2, radius, radius);
}
QPointF CPointItem::getPoint()
{
	return point;
}
void CPointItem::setPointParam(QPointF p)
{
	point = p;
	pScene->update();
	update();
}
bool CPointItem::isContainPoint(QPointF p)
{
	bool b;
	b = this->boundingRect().contains(p);
	return b;
}
void CPointItem::setRadius(int r)
{
	radius = r;
	pScene->update();
	update();
}

void CPointItem::SetColor(QColor color)
{
	PointColor = color;
	int r,g,b,a;
	PointColor.getRgb(&r,&g,&b,&a);
	PointBrushColor.setRgb(r,g,b,a);
}
