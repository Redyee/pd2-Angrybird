#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H


#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>

class MyContactListener : public b2ContactListener
{
public:
    MyContactListener();
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
};

#endif // MYCONTACTLISTENER_H
