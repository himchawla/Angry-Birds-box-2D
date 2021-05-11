#pragma once
#include<box2d/box2d.h>
#include"sprite.h"
class ContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact) {

        //check if fixture A was a ball
        b2BodyUserData bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData.pointer != 0)
            if (reinterpret_cast<sprite*>(bodyUserData.pointer)->Name == "Bird")
            {
                bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
                if (bodyUserData.pointer != 0)
                    if (reinterpret_cast<sprite*>(bodyUserData.pointer)->Name == "Destructable")
                    {
                        reinterpret_cast<sprite*>(bodyUserData.pointer)->destroy();
                    }
            }

        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData.pointer != 0)
            if (reinterpret_cast<sprite*>(bodyUserData.pointer)->Name == "Bird")
            {
                bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
                if (bodyUserData.pointer != 0)
                    if (reinterpret_cast<sprite*>(bodyUserData.pointer)->Name == "Destructable")
                    {
                        reinterpret_cast<sprite*>(bodyUserData.pointer)->destroy();
                    }
            }


       


    }

    void EndContact(b2Contact* contact) {

        //check if fixture A was a ball
        void* bodyUserData = &contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData)
            std::cout << "";
        //check if fixture B was a ball
        bodyUserData = &contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData)
            std::cout << "";

    }
};

