#include "obstacle_rotate.h"

obstacle_rotate::obstacle_rotate(float x, float y, float w, float h, QTimer *timer , QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_size = QSize(w,h);

    // Create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.userData = this;  //unknown
    bodyDef.fixedRotation = true;
    bodyDef.angularVelocity = 7.0;
    bodyDef.gravityScale = 0.0f; //ignore gravity
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h);
    g_body->CreateFixture(&bodyBox,9.0f);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}
