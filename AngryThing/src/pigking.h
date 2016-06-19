#ifndef PIGKING_H
#define PIGKING_H

#include <pig.h>

class pigking : public pig
{
public:
    pigking(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // PIGKING_H
