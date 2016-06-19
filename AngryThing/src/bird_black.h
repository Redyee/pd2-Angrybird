#ifndef BIRD_BLACK_H
#define BIRD_BLACK_H
#include "bird.h"

class bird_black : public Bird
{
public:
    bird_black(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void skill();
private:

};

#endif // BIRD_BLACK_H
