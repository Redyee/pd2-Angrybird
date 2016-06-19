#include "bird_black.h"

bird_black::bird_black(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird( x,  y,  radius,  timer,  pixmap,  world,  scene)
{

}

//bigger and weighter
void bird_black::skill()
{
    setLinearVelocity( b2Vec2(0, -30) );
}
