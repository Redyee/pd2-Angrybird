#ifndef OBSTACLE_ROTATE_H
#define OBSTACLE_ROTATE_H

#include <gameitem.h>
#include <QGraphicsScene>
#include <QTimer>


class obstacle_rotate : public GameItem
{
public:
    obstacle_rotate(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // OBSTACLE_ROTATE_H


