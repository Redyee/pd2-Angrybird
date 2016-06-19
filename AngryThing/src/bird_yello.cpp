#include "bird_yello.h"

bird_yello::bird_yello(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird( x,  y,  radius, timer, pixmap,world, scene)
{

}

void bird_yello::skill(){
    setLinearVelocity(b2Vec2(40 , 0));
}
