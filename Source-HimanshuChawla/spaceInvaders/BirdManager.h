#include "Bird.h"
#include<stack>
#pragma once
class BirdManager
{
public:
	BirdManager(int _num, b2World* _world, sf::Vector2f _defaultPos, Bird::eAbility* _ability)
	{
		m_activeBirdPosition = _defaultPos;
		
		for (int i = 0; i < _num; i++)
		{
			Bird* temp = new Bird(0.0f, 0.0f);

			switch (_ability[i])
			{
			case Bird::chuck:
			{
				temp->setTexture("Assets/chuck.png");
				temp->sp.setScale(64.0f / temp->sp.getTexture()->getSize().x, 64.0f / temp->sp.getTexture()->getSize().y);
				temp->sp.setOrigin(temp->sp.getTexture()->getSize().x * 0.5f, temp->sp.getTexture()->getSize().y * 0.5f);
			}break;

			case Bird::fall:
			{
				temp->setTexture("Assets/fall.png");
				temp->sp.setScale(64.0f / temp->sp.getTexture()->getSize().x, 64.0f / temp->sp.getTexture()->getSize().y);
				temp->sp.setOrigin(temp->sp.getTexture()->getSize().x * 0.5f, temp->sp.getTexture()->getSize().y * 0.5f);
			}break;

			case Bird::none:
			{
				temp->setTexture("Assets/Bird.png");
				temp->sp.setScale(64.0f / temp->sp.getTexture()->getSize().x, 64.0f / temp->sp.getTexture()->getSize().y);
				temp->sp.setOrigin(temp->sp.getTexture()->getSize().x * 0.5f, temp->sp.getTexture()->getSize().y * 0.5f);
			}break;
			default:
				break;
			}
			
			temp->init(_world, sf::Vector2f(m_activeBirdPosition.x - 20.0f * i, m_activeBirdPosition.y), sf::Vector2f(0.0f, 0.0f), 1);
			temp->m_ability = _ability[i];
			temp->sp.setPosition(sf::Vector2f(temp->getBody()->GetPosition().x * 4.0f, temp->getBody()->GetPosition().y * 4.0f));
			temp->sp.setRotation(temp->getBody()->GetAngle() * 180 / 3.14f);

			birds.push_back(temp);
		}
	}

	void update(float _dt)
	{
		if (birds.size() > 0)
		{
			birds[0]->update(_dt);

			if (!birds[0]->alive)
			{
				birds[0]->getWorld()->DestroyBody(birds[0]->getBody());
				delete birds[0];
				birds.erase(birds.begin());
				if (birds.size() > 0)
				{
					birds[0]->getBody()->SetTransform(b2Vec2(m_activeBirdPosition.x, m_activeBirdPosition.y), 0.0f);
				}
			}
		}

		else; //Game oover code here
			
	}

	void draw(sf::RenderWindow& _win)
	{
		for (auto i : birds)
		{
			i->draw(_win);
		}
	}
private:

	sf::Vector2f m_activeBirdPosition;
	std::vector<Bird*> birds;


	int numBirds;
};


