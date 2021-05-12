#pragma once
#include<box2d/box2d.h>
#include"sprite.h"
#include"Enemy.h"
#include"Bird.h"
class ContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact) {

        

       /* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
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
            }*/


       


    }

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
    {

        sprite* s1 = nullptr, * s2 = nullptr;
        //check if fixture A was a ball

        b2BodyUserData bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData.pointer != 0)
            s1 = reinterpret_cast<sprite*>(bodyUserData.pointer);

        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();

        if (bodyUserData.pointer != 0)
            s2 = reinterpret_cast<sprite*>(bodyUserData.pointer);

       
		if (s1 != nullptr && s2 != nullptr)
		{
			{


				if (s1->Name == "Bird")
				{
					if (reinterpret_cast<Bird*>(s1)->Shoot())
						reinterpret_cast<Bird*>(s1)->destroy(3);
					if (s1->getBody()->GetGravityScale() == 0.0f)
						s1->getBody()->SetGravityScale(1.0f);
				
				}

				if (s2->Name == "Bird")
				{
					if (reinterpret_cast<Bird*>(s2)->Shoot())
						reinterpret_cast<Bird*>(s2)->destroy(3);
					if (s2->getBody()->GetGravityScale() == 0.0f)
						s2->getBody()->SetGravityScale(1.0f);

				}
			}
		}

        {
            if (s1 != nullptr)
            {


				if (s1->Name == "Bird")
				{
					if (reinterpret_cast<Bird*>(s1)->Shoot())
						reinterpret_cast<Bird*>(s1)->destroy(20);
					if (s1->getBody()->GetGravityScale() == 0.0f)
						s1->getBody()->SetGravityScale(1.0f);
				}

				if (s1->Name == "Destructable")
				{
					auto force = impulse->normalImpulses[0];
					if (force > s1->health)
						s1->destroy();
					else if (force > 700.0f)
						s1->health -= force;

				}


				if (s1->Name == "Enemy")
				{
					auto force = impulse->normalImpulses[0];
					if (force > reinterpret_cast<Enemy*>(s1)->health)
						s1->destroy();
					else if (force > 700.0f)
						reinterpret_cast<Enemy*>(s1)->health -= force;

				}
            }
            if (s2 != nullptr)
            {

				if (s2->Name == "Enemy")
				{
					auto force = impulse->normalImpulses[0];
					if (force > reinterpret_cast<Enemy*>(s2)->health)
						s2->destroy();
					else if (force > 700.0f)
						reinterpret_cast<Enemy*>(s2)->health -= force;

				}

				if (s2->Name == "Bird")
				{
					if (reinterpret_cast<Bird*>(s2)->Shoot())
						reinterpret_cast<Bird*>(s2)->destroy(20);
					if (s2->getBody()->GetGravityScale() == 0.0f)
						s2->getBody()->SetGravityScale(1.0f);
				}

				if (s2->Name == "Destructable")
				{

					auto force = impulse->normalImpulses[0];


					if (force > s2->health)
						s2->destroy();
					else if (force > 700.0f)

						s2->health -= force;
				}
            
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

