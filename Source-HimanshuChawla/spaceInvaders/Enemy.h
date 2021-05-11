#pragma once
#include "sprite.h"
class Enemy :
	public sprite
{
public:
	Enemy(std::string name) :sprite(0.0f, 0.0f, "Enemy") 
	{
		setTexture("Assets/enemy.png");
		sp.setScale(64.0f / sp.getTexture()->getSize().x, 64.0f / sp.getTexture()->getSize().y);
		sp.setOrigin(sp.getTexture()->getSize().x * 0.5f, sp.getTexture()->getSize().y * 0.5f);
	}
	float health = 10000.0f;

	void update()
	{
		{
			if(health < 5000)

			setTexture("Assets/enemyIn.png");
			sp.setScale(64.0f / sp.getTexture()->getSize().x, 64.0f / sp.getTexture()->getSize().y);
			sp.setOrigin(sp.getTexture()->getSize().x * 0.5f, sp.getTexture()->getSize().y * 0.5f);

			sp.setPosition(sf::Vector2f(getBody()->GetPosition().x * 4.0f, getBody()->GetPosition().y * 4.0f));
			sp.setRotation(getBody()->GetAngle() * 180 / 3.14f);
		}
	}
};

