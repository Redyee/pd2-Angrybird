#ifndef WOOD_H
#define WOOD_H


#include <gameitem.h>
#include <QGraphicsScene>
#include <QTimer>


class Wood : public GameItem
{
public:
    Wood(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void collide(){}

};

#endif // WOOD_H
