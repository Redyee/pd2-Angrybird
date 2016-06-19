#include "mycontactlistener.h"

MyContactListener::MyContactListener()
{

}

void MyContactListener::BeginContact(b2Contact *contact){
    std::cout<<"MyContact Begin"<<std::endl;
}

void MyContactListener::EndContact(b2Contact *contact){
    std::cout<<"MyContact End"<<std::endl;
}
