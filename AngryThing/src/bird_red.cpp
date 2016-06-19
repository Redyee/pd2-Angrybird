#include "bird_red.h"

bird_red::bird_red(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird( x,  y,  radius,  timer,  pixmap,  world,  scene)
{

}

void bird_red::skill()
{
    std::cout<<"bird red skill"<<std::endl;
}
