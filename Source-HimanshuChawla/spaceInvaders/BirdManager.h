// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2019 Media Design School 
// 
//  File Name   :   BirdManager.h
//  Description :   Include for Bird Manager class
//  Author      :   Himanshu Chawla
//  Mail        :   Himanshu.Cha8420@mediadesign.mail.nz 
// 
// Local Include

#include "Bird.h"
#pragma once
class BirdManager
{
public:

	//Constructor
	//Sets asset accorfing to ability
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
			
			if(i == 1)
				temp->init(_world, sf::Vector2f(m_activeBirdPosition.x - 30.0f * i, m_activeBirdPosition.y), sf::Vector2f(0.0f, 0.0f), 1);
			else
				temp->init(_world, sf::Vector2f(m_activeBirdPosition.x - 30.0f, m_activeBirdPosition.y - 30.0f * (i - 1)), sf::Vector2f(0.0f, 0.0f), 1);
			temp->m_ability = _ability[i];
			temp->sp.setPosition(sf::Vector2f(temp->getBody()->GetPosition().x * 4.0f, temp->getBody()->GetPosition().y * 4.0f));
			temp->sp.setRotation(temp->getBody()->GetAngle() * 180 / 3.14f);

			birds.push_back(temp);

			birds[0]->getBody()->SetTransform(b2Vec2(m_activeBirdPosition.x, m_activeBirdPosition.y), 0.0f);
		}
	}

	int getSize()
	{
		return birds.size();
	}


	//update
	//sets current bird to shooting position
	void update(float _dt)
	{
		for (auto bird : birds)
		{
			if (!bird->Shoot())
			{
				bird->getBody()->SetTransform(b2Vec2(m_activeBirdPosition.x, m_activeBirdPosition.y), 0.0f);
				reinterpret_cast<sprite*>(bird)->update();
				break;
			}
		}
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
					//birds[0]->getBody()->SetTransform(b2Vec2(m_activeBirdPosition.x, m_activeBirdPosition.y), 0.0f);
				}
			}
		}

		else;
			
	}

	//draw
	//draws birds
	void draw(sf::RenderWindow& _win)
	{
		for (auto i : birds)
		{
			i->draw(_win);
		}
	}


	//get array
	//returns reference to the array
	std::vector<Bird*>& getArray()
	{
		return birds;
	}

private:

	sf::Vector2f m_activeBirdPosition;
	std::vector<Bird*> birds;


	int numBirds;
};


