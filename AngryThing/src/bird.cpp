#include "bird.h"

Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    offsetGravity();
    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

b2Vec2 Bird::getLinearVelocity()
{
    return g_body->GetLinearVelocity();
}

void Bird::offsetGravity(){
    g_body->SetGravityScale(0.0);
}
void Bird::setGravity(){
    g_body->SetGravityScale(1.0);
}

void Bird::setPosition(float x, float y){
    g_body->SetTransform( b2Vec2( x,y ),g_body->GetAngle() );
}

b2Vec2 Bird::getPosition()
{
    return g_body->GetPosition();
}

void Bird::stop(){
    offsetGravity();
    setLinearVelocity(b2Vec2_zero);
}

void Bird::collide(){
    num_collideA = 1;
}
