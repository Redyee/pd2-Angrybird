#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class Bird : public GameItem
{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    virtual void skill(){}
    virtual void collide();
    void setPosition(float x, float y );
    void offsetGravity();
    void setGravity();
    b2Vec2 getLinearVelocity();
    b2Vec2 getPosition();
    void stop();
};

#endif // BIRD_H
