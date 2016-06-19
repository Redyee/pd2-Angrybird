#include "bird_blue.h"

bird_blue::bird_blue(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird( x,  y,  radius, timer,  pixmap, world, scene)
{
    world_blue = world;
    timer_blue = timer;
    scene_blue = scene;

}

void bird_blue::setxy_blue(b2Vec2 pos , b2Vec2 speed){
    x_blue = pos.x;
    y_blue = pos.y;
    skill_speed = speed;
}

void bird_blue::skill(){

    skill_blue1 = new bird_blue( x_blue , y_blue ,0.5f, timer_blue , QPixmap(":/image/angry_black.png").scaled(46.0,46.0) ,world_blue , scene_blue);
    skill_blue1->setGravity();
    skill_blue1->setLinearVelocity(skill_speed + b2Vec2(-0.5 , 0.5));
    skill_blue2 = new bird_blue( x_blue , y_blue ,0.5f, timer_blue , QPixmap(":/image/angry_black.png").scaled(46.0,46.0) ,world_blue , scene_blue);
    skill_blue2->setGravity();
    skill_blue2->setLinearVelocity(skill_speed + b2Vec2(-0.5 , -0.5));
}
