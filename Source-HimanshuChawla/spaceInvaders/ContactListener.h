#pragma once
#include<box2d/box2d.h>
#include"sprite.h"
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2019 Media Design School 
// 
//  File Name   :   ContactListener.h
//  Description :   Include for sprite class
//  Author      :   Himanshu Chawla
//  Mail        :   Himanshu.Cha8420@mediadesign.mail.nz 
// 


//Local includes
#include"Enemy.h"
#include"Bird.h"

class ContactListener : public b2ContactListener
{
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{

		sprite* s1 = nullptr, * s2 = nullptr;
	
		//assign sprites
		b2BodyUserData bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData.pointer != 0)
			s1 = reinterpret_cast<sprite*>(bodyUserData.pointer);

		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserData.pointer != 0)
			s2 = reinterpret_cast<sprite*>(bodyUserData.pointer);

		//Destroy birds 5 seconds after hitting anything
		if (s1 != nullptr && s2 != nullptr)
		{
			if (s1->Name == "Bird")
			{
				if (reinterpret_cast<Bird*>(s1)->Shoot())
					reinterpret_cast<Bird*>(s1)->destroy(5);
				if (s1->getBody()->GetGravityScale() == 0.0f)
					s1->getBody()->SetGravityScale(1.0f);
			}

			if (s2->Name == "Bird")
			{
				if (reinterpret_cast<Bird*>(s2)->Shoot())
					reinterpret_cast<Bird*>(s2)->destroy(5);
				if (s2->getBody()->GetGravityScale() == 0.0f)
					s2->getBody()->SetGravityScale(1.0f);
			}
		}


		if (s1 != nullptr)
		{	//Destroy birds 5 seconds after launch if not hitting anything
			if (s1->Name == "Bird")
			{
				if (reinterpret_cast<Bird*>(s1)->Shoot())
					reinterpret_cast<Bird*>(s1)->destroy(5);
				if (s1->getBody()->GetGravityScale() == 0.0f)
					s1->getBody()->SetGravityScale(1.0f);
			}

			//Destroy objects if impact is greater than health
			if (s1->Name == "Destructable" || s1->Name == "Pulley")
			{
				auto force = impulse->normalImpulses[0];
				if (force > s1->health)
					s1->destroy();
				else if (force > 700.0f)
					s1->health -= force;
			}

			//Destroy enemies if impact is greater than health
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
			//Destroy enemy if impact is greater than health
			if (s2->Name == "Enemy")
			{
				auto force = impulse->normalImpulses[0];
				if (force > reinterpret_cast<Enemy*>(s2)->health)
					s2->destroy();
				else if (force > 700.0f)
					reinterpret_cast<Enemy*>(s2)->health -= force;
			}

			//Destroy birds 5 seconds after launch if not hitting anything
			if (s2->Name == "Bird")
			{
				if (reinterpret_cast<Bird*>(s2)->Shoot())
					reinterpret_cast<Bird*>(s2)->destroy(5);
				if (s2->getBody()->GetGravityScale() == 0.0f)
					s2->getBody()->SetGravityScale(1.0f);
			}

			//Destroy objects if impact is greater than health
			if (s2->Name == "Destructable" || s2->Name == "Pulley")
			{
				auto force = impulse->normalImpulses[0];
				if (force > s2->health)
					s2->destroy();
				else if (force > 700.0f)
					s2->health -= force;
			}

		}

	}
};

