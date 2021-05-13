// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2019 Media Design School 
// 
//  File Name   :   Bird.h
//  Description :   Implementation for sprite class
//  Author      :   Himanshu Chawla
//  Mail        :   Himanshu.Cha8420@mediadesign.mail.nz 
// 
// Local Include


#include "Bird.h"


b2Vec2 Bird::getTrajectoryPoint(b2Vec2& startingPosition, b2Vec2& startingVelocity, float n, b2World* world)
{
	//velocity and gravity are given per second but we want time step values here
	float t = 1 / 60.0f; // seconds per time step (at 60fps)
	b2Vec2 stepVelocity = t * startingVelocity; // m/s
	b2Vec2 stepGravity = t * t * b2Vec2(0.0f, 9.81f); // m/s/s
	
	return startingPosition + n * stepVelocity + 0.5f * (n * n + n) * stepGravity;
}

//update
void Bird::update(float _dT)
{
	b2Vec2 vel;
	m_timer -= _dT;
	if (m_destroy && m_timer <= 0.0f)
	{
		alive = false;
	}

	//Ability apply
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_shoot && m_active)
	{
		switch (m_ability)
		{
		case Bird::chuck:
		{
			getBody()->SetLinearVelocity(b2Vec2((getBody()->GetLinearVelocity()).x * 5.0f, (getBody()->GetLinearVelocity()).y * 5.0f));
			getBody()->SetGravityScale(0.0f);
			m_ability = none;
		}
			break;
		case Bird::fall:
		{
			getBody()->SetLinearVelocity(b2Vec2(0.0f, 100.0f));
			
			m_ability = none;
		}
		
		case Bird::none:
			break;
		default:
			break;
		}
	}
	
	//path calculation
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !m_shoot)
	{
		
		for (auto i : m_path)
		{
			delete i;

		}
		m_path.clear();

		b2Vec2 position;
		if (abs(sf::Mouse::getPosition().x - sp.getPosition().x) < 64.0f && abs(sf::Mouse::getPosition().y - sp.getPosition().y) < 64.0f)
			m_canDo = true;

		position = getBody()->GetPosition();
		vel = b2Vec2((b2Vec2(sf::Mouse::getPosition().x /4.0f, sf::Mouse::getPosition().y / 4.0f) - getBody()->GetPosition()).x * 3.0f, (b2Vec2(sf::Mouse::getPosition().x/4.0f, sf::Mouse::getPosition().y/4.0f) - getBody()->GetPosition()).y * 3.0f);

		//std::cout << vel.x << " " << vel.y << "\n";

		b2RayCastCallback* raycastCallback = nullptr;
		b2Vec2 lastTP = position;

		vel *= -1.0f;
		if (vel.Length() > m_speed)
		{
			vel.Normalize();
			vel *= m_speed;
		}
		
		if (vel.Length() > 1000.0f)
		{
			std::cout << "whyy";
		}
		if (m_canDo)
		{
			float t = -2 * vel.y / 9.81f;
			//std::cout << t << "\n";
			for (int i = 0; i < (int)((t -  t   * 0.5f) * 60); i += 10)
			{ // three seconds at 60fps
				sprite* temp = new sprite(0.0f, 0.0f, "Path");
				temp->setTexture("Assets/circle.png");
				b2Vec2 trajectoryPosition = getTrajectoryPoint(position, vel, i, getWorld());
				temp->sp.setPosition(trajectoryPosition.x * 4.0f, trajectoryPosition.y * 4.0f);
				m_path.push_back(temp);
			}
			
		}
	}

	//shoot the bird on release
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_canDo && !m_shoot)
	{
		for (auto i : m_path)
		{
			delete i;

		}
		m_path.clear();
		//newBox->getBody()->SetLinearVelocity(b2Vec2(10.0f, newBox->getBody()->GetLinearVelocity().y));
		if (vel.Length() > 5.0f && vel.Length() < 1000.0f)
		{
			m_shoot = true;
			std::cout << vel.Length();
			
			getBody()->SetLinearVelocity(vel);
		}
		else if(vel.Length() > 1000.0f)
		{
			vel = b2Vec2((b2Vec2(sf::Mouse::getPosition().x / 4.0f, sf::Mouse::getPosition().y / 4.0f) - getBody()->GetPosition()).x * 3.0f, (b2Vec2(sf::Mouse::getPosition().x / 4.0f, sf::Mouse::getPosition().y / 4.0f) - getBody()->GetPosition()).y * 3.0f);

			vel *= -1.0f;
			if (vel.Length() > m_speed)
			{
				vel.Normalize();
				vel *= m_speed;
			}

			m_shoot = true;
			std::cout << vel.Length();

			getBody()->SetLinearVelocity(vel);
		}
			m_canDo = false;
	}

	//update sprite pos
	sp.setPosition(sf::Vector2f(getBody()->GetPosition().x * 4.0f, getBody()->GetPosition().y * 4.0f));
	sp.setRotation(getBody()->GetAngle() * 180 / 3.14f);
	

}



void Bird::draw(sf::RenderWindow& win)
{
	if (alive)
	{
		sp.setTexture(tx);
		win.draw(sp);
		drawPath(win);
	}
}


void Bird::drawPath(sf::RenderWindow& win)
{
	for (auto i : m_path)
	{
		i->draw(win);
	}
}

void Bird::destroy(int time)
{
	if (!m_destroy)
	{
		m_destroy = true;
		m_timer = time;
	}
	else if (m_timer > time)
	{
		m_timer = time;
	}

}
