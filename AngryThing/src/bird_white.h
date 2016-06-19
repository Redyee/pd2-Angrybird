#ifndef BIRD_WHITE_H
#define BIRD_WHITE_H

#include <bird.h>
class bird_white : public Bird
{
public:
    bird_white(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void skill();

};

#endif // BIRD_WHITE_H
