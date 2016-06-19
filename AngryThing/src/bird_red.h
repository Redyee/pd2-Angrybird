#ifndef BIRD_RED_H
#define BIRD_RED_H
#include "bird.h"

class bird_red : public Bird
{
public:
    bird_red(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void skill();
};

#endif // BIRD_RED_H
