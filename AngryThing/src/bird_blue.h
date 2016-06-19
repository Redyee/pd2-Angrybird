#ifndef BIRD_BLUE_H
#define BIRD_BLUE_H

#include <bird.h>
class bird_blue : public Bird
{
public:
    bird_blue(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void skill();
    void setxy_blue(b2Vec2 pos ,b2Vec2 speed );
private:
    Bird *skill_blue1;
    Bird *skill_blue2;
    b2World *world_blue;
    QTimer *timer_blue;
    QGraphicsScene *scene_blue;
    QPixmap *pixmap_blue;
    float x_blue;
    float y_blue;
    b2Vec2 skill_speed;
};

#endif // BIRD_BLUE_H
