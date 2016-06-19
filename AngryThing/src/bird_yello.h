#ifndef BIRD_YELLO_H
#define BIRD_YELLO_H

#include <bird.h>

class bird_yello : public Bird
{
public:
    bird_yello(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void skill();
};

#endif // BIRD_YELLO_H
