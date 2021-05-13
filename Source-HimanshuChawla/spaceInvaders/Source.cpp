// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2019 Media Design School 
// 
//  File Name   :   source.cpp
//  Description :   Contains
//  Author      :   Himanshu Chawla
//  Mail        :   Himanshu.Cha8420@mediadesign.mail.nz 
// 

 // Library Include
#include<SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include<math.h>

// Local Include
#include"sprite.h"
#include "BirdManager.h" 
#include "Enemy.h"
#include"ContactListener.h"

sf::ConvexShape* line[3];
bool l = false;
sprite* pull1, * pull2, * pullObj1, * pullObj2;


/*
loadLevel2: Fundtion to load level 1
@Padrameters: &levelVector, &enemyVector, world, &birdmanager
@return: N/A
*/
void loadLevel1(std::vector<sprite*>& level, std::vector<Enemy*>& enemies, b2World* m_world, BirdManager* &_birds)
{
#pragma region Level Geometery

	sprite* temp = new sprite(0.0f, 0.0f, "Indestructable");
	temp->setTexture("Assets/Block.png");
	temp->sp.setScale(30.0f, 1.0f);
	temp->sp.setColor(sf::Color::Color(128, 128, 128, 255));
	temp->init(m_world, sf::Vector2f(170.0f, 200.0f), sf::Vector2f(160.0f, 16.0f), 1);
	//
	level.push_back(temp);

	temp = new sprite(0.0f, 0.0f, "Destructable");
	temp->sp.setScale(sf::Vector2f(2.0f, 10.0f));
	temp->setTexture("Assets/Block.png");
	temp->sp.setColor(sf::Color::Green);
	temp->init(m_world, sf::Vector2f(140.5f, 220.0f), sf::Vector2f(16.0f, 160.0f), 1);
	level.push_back(temp);

	temp = new sprite(0.0f, 0.0f, "Destructable");
	temp->sp.setScale(sf::Vector2f(2.0f, 10.0f));
	temp->setTexture("Assets/Block.png");
	temp->sp.setColor(sf::Color::Green);
	temp->init(m_world, sf::Vector2f(180.5f, 220.0f), sf::Vector2f(16.0f, 160.0f), 1);
	level.push_back(temp);

	temp = new sprite(0.0f, 0.0f, "Destructable");
	temp->sp.setScale(sf::Vector2f(2.0f, 10.0f));
	temp->setTexture("Assets/Block.png");
	temp->sp.setColor(sf::Color::Green);
	temp->init(m_world, sf::Vector2f(220.0f, 220.0f), sf::Vector2f(16.0f, 160.0f), 1);
	level.push_back(temp);

#pragma endregion

#pragma region Joint Objects

	sprite* rev1 = new sprite(0.0f, 0.0f, "Indestructable");
	rev1->sp.setScale(1.0f, 5.0f);
	rev1->setTexture("Assets/block.png");
	rev1->init(m_world, sf::Vector2f(150.0f, 125.0f), sf::Vector2f(16.0f, 80.0f), 0);
	level.push_back(rev1);

	sprite* rev2 = new sprite(0.0f, 0.0f, "Indestructable");
	rev2->sp.setScale(4.0f, 4.0f);
	rev2->setTexture("Assets/circle.png");
	rev2->init(m_world, sf::Vector2f(150.0f, 150.0f), sf::Vector2f(32.0f, 32.0f), 1);
	level.push_back(rev2);

	sprite* motor1 = new sprite(0.0f, 0.0f, "Indestructable");
	motor1->setTexture("Assets/Block.png");
	motor1->sp.setColor(sf::Color::Color(128, 128, 128, 255));

	motor1->sp.setScale(25.0f, 1.0f);
	motor1->init(m_world, sf::Vector2f(320.0f, 160.0f), sf::Vector2f(160.0f, 16.0f), 1);
	motor1->getBody()->SetGravityScale(0.0f);
	//
	level.push_back(motor1);

	sprite* motor2 = new sprite(0.0f, 0.0f, "Indestructable");
	motor2->sp.setScale(1.0f, 5.0f);
	motor2->setTexture("Assets/block.png");
	motor2->init(m_world, sf::Vector2f(320.0f, 160.0f), sf::Vector2f(16.0f, 80.0f), 0);
	level.push_back(motor2);

#pragma endregion

#pragma region Enemies

	Enemy* tempEnemy = new Enemy("");
	tempEnemy->init(m_world, sf::Vector2f(160.5f, 220.0f), sf::Vector2f(16.0f, 160.0f), 1);
	enemies.push_back(tempEnemy);

	tempEnemy = new Enemy("");
	tempEnemy->init(m_world, sf::Vector2f(200.0f, 220.0f), sf::Vector2f(16.0f, 160.0f), 1);
	enemies.push_back(tempEnemy);

	tempEnemy = new Enemy("");
	tempEnemy->init(m_world, sf::Vector2f(180.0f, 180.0f), sf::Vector2f(16.0f, 160.0f), 1);
	enemies.push_back(tempEnemy);

	tempEnemy = new Enemy("");
	tempEnemy->init(m_world, sf::Vector2f(320.0f, 150.0f), sf::Vector2f(16.0f, 160.0f), 1);
	enemies.push_back(tempEnemy);

	tempEnemy = new Enemy("");
	tempEnemy->init(m_world, sf::Vector2f(150.0f, 100.0f), sf::Vector2f(16.0f, 160.0f), 1);
	enemies.push_back(tempEnemy);

#pragma endregion

#pragma region Joints

	b2DistanceJointDef mjd;

	mjd.Initialize(motor2->getBody(), motor1->getBody(), motor2->getBody()->GetWorldCenter(), motor1->getBody()->GetWorldCenter());

	b2Joint* m_joint = m_world->CreateJoint(&mjd);


	b2RevoluteJointDef revoluteJointDef;

	revoluteJointDef.Initialize(rev1->getBody(), rev2->getBody(), rev1->getBody()->GetWorldCenter());

	revoluteJointDef.motorSpeed = 3.14f * 2.0f;
	revoluteJointDef.maxMotorTorque = 1000.0f;
	revoluteJointDef.enableMotor = true;

	b2Joint* joint = m_world->CreateJoint(&revoluteJointDef);

#pragma endregion

#pragma region Birds

	Bird::eAbility abilities[3] = { Bird::none, Bird::chuck, Bird::fall };


	BirdManager* tempBirds = new BirdManager(3, m_world, sf::Vector2f(50.0f, 230.0f), &abilities[0]);
	
	_birds = tempBirds;

#pragma endregion
}



/*
loadLevel2: Fundtion to load level 2
@Padrameters: &levelVector, &enemyVector, world, &birdmanager
@return: N/A
*/
void loadLevel2(std::vector<sprite*>& level, std::vector<Enemy*>& enemies, b2World* m_world, BirdManager*& _birds)
{
#pragma region LevelGeometery

	sprite* temp = new sprite(0.0f, 0.0f, "Indestructable");
	temp->setTexture("Assets/Block.png");
	temp->sp.setScale(30.0f, 1.0f);
	temp->sp.setColor(sf::Color::Color(128, 128, 128, 255));
	temp->init(m_world, sf::Vector2f(170.0f, 200.0f), sf::Vector2f(160.0f, 16.0f), 1);
	//
	level.push_back(temp);

	temp = new sprite(0.0f, 0.0f, "Destructable");
	temp->sp.setScale(sf::Vector2f(2.0f, 10.0f));
	temp->setTexture("Assets/Block.png");
	temp->sp.setColor(sf::Color::Green);
	temp->init(m_world, sf::Vector2f(140.5f, 220.0f), sf::Vector2f(16.0f, 160.0f), 1);
	level.push_back(temp);

	temp = new sprite(0.0f, 0.0f, "Destructable");
	temp->sp.setScale(sf::Vector2f(2.0f, 10.0f));
	temp->setTexture("Assets/Block.png");
	temp->sp.setColor(sf::Color::Green);
	temp->init(m_world, sf::Vector2f(180.5f, 220.0f), sf::Vector2f(16.0f, 160.0f), 1);
	level.push_back(temp);

	temp = new sprite(0.0f, 0.0f, "Destructable");
	temp->sp.setScale(sf::Vector2f(2.0f, 10.0f));
	temp->setTexture("Assets/Block.png");
	temp->sp.setColor(sf::Color::Green);
	temp->init(m_world, sf::Vector2f(220.0f, 220.0f), sf::Vector2f(16.0f, 160.0f), 1);
	level.push_back(temp);

#pragma endregion

#pragma region Joint objects

	pull1 = new sprite(0.0f, 0.0f, "Indestructable");
	pull1->sp.setScale(4.0f, 4.0f);
	pull1->setTexture("Assets/circle.png");
	pull1->init(m_world, sf::Vector2f(150.0f, 70.0f), sf::Vector2f(32.0f, 32.0f), 0);
	level.push_back(pull1);

	pull2 = new sprite(0.0f, 0.0f, "Indestructable");
	pull2->sp.setScale(4.0f, 4.0f);
	pull2->setTexture("Assets/circle.png");
	pull2->init(m_world, sf::Vector2f(250.0f, 70.0f), sf::Vector2f(32.0f, 32.0f), 0);
	level.push_back(pull2);

	pullObj1 = new sprite(0.0f, 0.0f, "Pulley");
	pullObj1->sp.setScale(10.0f, 1.0f);
	pullObj1->setTexture("Assets/block.png");
	pullObj1->sp.setColor(sf::Color::Green);
	pullObj1->init(m_world, sf::Vector2f(150.0f, 125.0f), sf::Vector2f(16.0f, 80.0f), 1, 5000);
	pullObj1->getBody()->SetFixedRotation(true);
	level.push_back(pullObj1);

	pullObj2 = new sprite(0.0f, 0.0f, "Indestructable");
	pullObj2->sp.setScale(10.0f, 1.0f);
	pullObj2->setTexture("Assets/block.png");
	pullObj2->sp.setColor(sf::Color::Color(128, 128, 128, 255));
	pullObj2->init(m_world, sf::Vector2f(250.0f, 125.0f), sf::Vector2f(16.0f, 80.0f), 1);
	pullObj2->getBody()->SetFixedRotation(true);
	level.push_back(pullObj2);


#pragma endregion

#pragma region Pulley

	for (int i = 0; i < 3; i++)
	{
		if(line[i] == nullptr)
		line[i] = new sf::ConvexShape(4);
		line[i]->setOutlineThickness(1.0f);
	}


	line[0]->setPoint(0, sf::Vector2f(pullObj1->getBody()->GetPosition().x, pullObj1->getBody()->GetPosition().y));
	line[0]->setPoint(1, sf::Vector2f(pullObj1->getBody()->GetPosition().x, pullObj1->getBody()->GetPosition().y));
	line[0]->setPoint(2, sf::Vector2f(pull1->getBody()->GetPosition().x, pullObj1->getBody()->GetPosition().y));
	line[0]->setPoint(3, sf::Vector2f(pull1->getBody()->GetPosition().x, pullObj1->getBody()->GetPosition().y));

	line[1]->setPoint(0, sf::Vector2f(pull2->getBody()->GetPosition().x, pull2->getBody()->GetPosition().y));
	line[1]->setPoint(1, sf::Vector2f(pull2->getBody()->GetPosition().x, pull2->getBody()->GetPosition().y));
	line[1]->setPoint(2, sf::Vector2f(pull1->getBody()->GetPosition().x, pull1->getBody()->GetPosition().y));
	line[1]->setPoint(3, sf::Vector2f(pull1->getBody()->GetPosition().x, pull1->getBody()->GetPosition().y));

	line[2]->setPoint(0, sf::Vector2f(pullObj2->getBody()->GetPosition().x, pullObj2->getBody()->GetPosition().y));
	line[2]->setPoint(1, sf::Vector2f(pullObj2->getBody()->GetPosition().x, pullObj2->getBody()->GetPosition().y));
	line[2]->setPoint(2, sf::Vector2f(pull2->getBody()->GetPosition().x, pull2->getBody()->GetPosition().y));
	line[2]->setPoint(3, sf::Vector2f(pull2->getBody()->GetPosition().x, pull2->getBody()->GetPosition().y));

	l = true;

#pragma endregion

#pragma region Joints

	b2PulleyJointDef pulleyJointDef;

	pulleyJointDef.Initialize(pullObj1->getBody(), pullObj2->getBody(), pullObj1->getBody()->GetWorldCenter(), pullObj2->getBody()->GetWorldCenter(), pull1->getBody()->GetWorldCenter() + b2Vec2(0.0f, 40.0f), pull2->getBody()->GetWorldCenter() + b2Vec2(0.0f, 40.0f), 1.0f);

	m_world->CreateJoint(&pulleyJointDef);

#pragma endregion
	
#pragma region Enemies

	Enemy* tempEnemy = new Enemy("");
	tempEnemy->init(m_world, sf::Vector2f(160.5f, 220.0f), sf::Vector2f(16.0f, 160.0f), 1);
	enemies.push_back(tempEnemy);

	tempEnemy = new Enemy("");
	tempEnemy->init(m_world, sf::Vector2f(200.0f, 220.0f), sf::Vector2f(16.0f, 160.0f), 1);
	enemies.push_back(tempEnemy);

	tempEnemy = new Enemy("");
	tempEnemy->init(m_world, sf::Vector2f(180.0f, 180.0f), sf::Vector2f(16.0f, 160.0f), 1);
	enemies.push_back(tempEnemy);

	tempEnemy = new Enemy("");
	tempEnemy->init(m_world, sf::Vector2f(250.0f, 100.0f), sf::Vector2f(16.0f, 160.0f), 1);
	enemies.push_back(tempEnemy);

	tempEnemy = new Enemy("");
	tempEnemy->init(m_world, sf::Vector2f(150.0f, 100.0f), sf::Vector2f(16.0f, 160.0f), 1);
	enemies.push_back(tempEnemy);

#pragma endregion

#pragma region birds

	Bird::eAbility abilities[4] = {Bird::chuck, Bird::none, Bird::chuck, Bird::fall };
	BirdManager* tempBirds = new BirdManager(4, m_world, sf::Vector2f(50.0f, 220.0f), &abilities[0]);
	_birds = tempBirds;

#pragma endregion
}


/*
loadLevel2: Fundtion to load game over/win screen
@Padrameters: &levelVector, &enemyVector, world, &birdmanager
@return: N/A
*/
void loadLevelGameOver(bool win, sf::Text* &_text)
{
	if(_text == nullptr)
		_text = new sf::Text();
	sf::Font* font = new sf::Font();
	font->loadFromFile("Assets/arial.ttf");
	_text->setFont(*font);
	_text->setScale(sf::Vector2f(5.0f, 5.0f));
	_text->setPosition(sf::Vector2f(960.0f, 540.0f));
	if (win)
		_text->setString("You Won");
	else
		_text->setString("You Lost");


}

int main()
{
	//level
	int currLevel = 1;

	//sf window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML");

	//gameover text
	sf::Text* text = nullptr;

	//contact listneser
	ContactListener m_contactListener;

	sf::Clock dClock;

	sf::Clock clock;
	clock.restart();
	//clock

	b2World* m_world;

	std::vector<sprite*> level;		//Level
	std::vector<Enemy*> enemies;	//Enemies
	window.setFramerateLimit(60);

	//World Setup
	b2Vec2 gravity(0.0f, 9.81f);
	m_world = new b2World(gravity);


	//Ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(240.0f, 240.0f);

	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	groundBody->GetUserData().pointer = 0;


	//ground body
	b2PolygonShape groundBox;
	groundBox.SetAsBox(960.0f, 10.0f);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 1.0f;
	groundBody->CreateFixture(&fixtureDef);
	
	BirdManager* bird = nullptr;		//Birds

	
	loadLevel1(level, enemies, m_world, bird);
	
	//initialize pulley lines
	for (int i = 0; i < 3; i++)
	{
		line[i] = nullptr;
	}
	
	//game loop
	while (window.isOpen())
	{
		window.clear();
		float dt = dClock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		//ground.getBody()->SetEnabled(true);
	
		//Reset level
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && text!= nullptr)
		{
			std::vector<sprite*>::iterator it = level.begin();
			while (it != level.end())
			{

				m_world->DestroyBody((*it)->getBody());
				delete (*(it));
				it++;

			}
			level.clear();
			for (auto& i : bird->getArray())
			{
				m_world->DestroyBody((i)->getBody());
				delete (i);
			}
			bird->getArray().clear();
			for (auto& i : enemies)
			{
				m_world->DestroyBody((i)->getBody());
				delete (i);
			}
			enemies.clear();

			delete text;
			text = nullptr;
			loadLevel1(level, enemies, m_world, bird);

		}


		//Set contact listener
		m_world->SetContactListener(&m_contactListener);


#pragma region LevelProgress

		//level 2 load
		if (currLevel == 1 && enemies.size() == 0 && text == nullptr)
		{
			currLevel++;
			std::vector<sprite*>::iterator it = level.begin();
			while (it != level.end())
			{
				
					m_world->DestroyBody((*it)->getBody());
					delete (*(it));
					it++;
			
			}
			level.clear();
			for(auto&i :bird->getArray())
			{

				m_world->DestroyBody((i)->getBody());
				delete (i);
				
			}

			bird->getArray().clear();

			

			loadLevel2(level, enemies, m_world, bird);

		}

		//game won
		if (currLevel == 2 && enemies.size() == 0 && text == nullptr)
		{
			std::vector<sprite*>::iterator it = level.begin();
			while (it != level.end())
			{

				m_world->DestroyBody((*it)->getBody());
				delete (*(it));
				it++;

			}
			level.clear();
			for (auto& i : bird->getArray())
			{

				m_world->DestroyBody((i)->getBody());
				delete (i);

			}
			l = false;
			currLevel = 1;
			bird->getArray().clear();

			for (int i = 0; i < 3; i++)
			{
				delete line[i];
				line[i] = nullptr;
			}
			loadLevelGameOver(true, text);
		}

		//game lost
		if (bird->getSize() == 0 &&enemies.size() > 0 && text == nullptr)
		{
			std::vector<sprite*>::iterator it = level.begin();
			while (it != level.end())
			{

				m_world->DestroyBody((*it)->getBody());
				delete (*(it));
				it++;

			}
			level.clear();
			for (auto& i : bird->getArray())
			{

				m_world->DestroyBody((i)->getBody());
				delete (i);

			}
			bird->getArray().clear();

			for (auto& i : enemies)
			{
				m_world->DestroyBody((i)->getBody());
				delete (i);
			}
			enemies.clear();

			l = false;
			
			if(currLevel == 2)
			for (int i = 0; i < 3; i++)
			{
				delete line[i];
				line[i] = nullptr;
			}

			currLevel = 1;
			loadLevelGameOver(false, text);  
		}

#pragma endregion




	

		

//Pulley Lines
#pragma region Pulley

		if (l)
		{
			line[0]->setPoint(0, sf::Vector2f(pullObj1->getBody()->GetPosition().x * 4.0f, pullObj1->getBody()->GetPosition().y * 4.0f));
			line[0]->setPoint(1, sf::Vector2f(pullObj1->getBody()->GetPosition().x * 4.0f, pullObj1->getBody()->GetPosition().y * 4.0f));
			line[0]->setPoint(2, sf::Vector2f(pull1->getBody()->GetPosition().x * 4.0f, pull1->getBody()->GetPosition().y * 4.0f));
			line[0]->setPoint(3, sf::Vector2f(pull1->getBody()->GetPosition().x * 4.0f, pull1->getBody()->GetPosition().y * 4.0f));

			line[1]->setPoint(0, sf::Vector2f(pull2->getBody()->GetPosition().x * 4.0f, pull2->getBody()->GetPosition().y * 4.0f));
			line[1]->setPoint(1, sf::Vector2f(pull2->getBody()->GetPosition().x * 4.0f, pull2->getBody()->GetPosition().y * 4.0f));
			line[1]->setPoint(2, sf::Vector2f(pull1->getBody()->GetPosition().x * 4.0f, pull1->getBody()->GetPosition().y * 4.0f));
			line[1]->setPoint(3, sf::Vector2f(pull1->getBody()->GetPosition().x * 4.0f, pull1->getBody()->GetPosition().y * 4.0f));

			line[2]->setPoint(0, sf::Vector2f(pullObj2->getBody()->GetPosition().x * 4.0f, pullObj2->getBody()->GetPosition().y * 4.0f));
			line[2]->setPoint(1, sf::Vector2f(pullObj2->getBody()->GetPosition().x * 4.0f, pullObj2->getBody()->GetPosition().y * 4.0f));
			line[2]->setPoint(2, sf::Vector2f(pull2->getBody()->GetPosition().x * 4.0f, pull2->getBody()->GetPosition().y * 4.0f));
			line[2]->setPoint(3, sf::Vector2f(pull2->getBody()->GetPosition().x * 4.0f, pull2->getBody()->GetPosition().y * 4.0f));

			for (int i = 0; i < 3; i++)
			{
				window.draw(*line[i]);
			}
		}
#pragma endregion
		
		//Update and draw birds
		bird->update(dt);
		bird->draw(window);

		//draw game over/win text
		if (text != nullptr)
			window.draw(*text);

		//draw level
		std::vector<sprite*>::iterator it = level.begin();
		while (it != level.end())
		{
			//Destroy level
			if (!(*it)->alive)
			{
				if ((*it)->Name == "Pulley")
				{
					l = false;
				}
				m_world->DestroyBody((*it)->getBody());
				delete (*it);
				
				level.erase(it);

				break;
			}
			(*it)->update();
			(*it)->draw(window);
			it++;
		}

		//Draw enemies
		std::vector<Enemy*>::iterator i = enemies.begin();
		while (i != enemies.end())
		{
			//Destroy enemies
			if (!(*i)->alive)
			{
				m_world->DestroyBody((*i)->getBody());
				delete (*i);

				enemies.erase(i);
				break;
			}
			(*i)->update();
			(*i)->draw(window);
			i++;
		}

		//Step

		float timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 3;
		int32 positionIterations = 1;
		///////////////////////////////////////
		for (int32 i = 0; i < 5; ++i)
		{
			m_world->Step(timeStep, velocityIterations, positionIterations);
		}

		window.display();
	
	}

}
