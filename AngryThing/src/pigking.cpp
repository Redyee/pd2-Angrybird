#include "pigking.h"

pigking::pigking(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :    pig( x, y,  radius, timer, pixmap, world, scene)
{

}
