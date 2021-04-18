#include<SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include"sprite.h"


b2Vec2 getTrajectoryPoint(b2Vec2& startingPosition, b2Vec2& startingVelocity, float n, b2World* world)
{
	//velocity and gravity are given per second but we want time step values here
	float t = 1 / 60.0f; // seconds per time step (at 60fps)
	b2Vec2 stepVelocity = t * startingVelocity; // m/s
	b2Vec2 stepGravity = t * t * b2Vec2(0.0f, 9.81f); // m/s/s

	return startingPosition + n * stepVelocity + 0.5f * (n * n + n) * stepGravity;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML");

	sf::Clock dClock;
	std::unique_ptr<b2World> m_world;

	//World Setup
	b2Vec2 gravity(0.0f, 9.81f);
	m_world = std::make_unique<b2World>(gravity);

	//Ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(960.0f, 400.0f);

	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	std::cout << m_world->GetBodyCount()<<"\n";
	//Ground Fixture

	b2PolygonShape groundBox;
	groundBox.SetAsBox(960.0f, 10.0f);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 1.0f;
	groundBody->CreateFixture(&fixtureDef);
	

	sprite newBox(20.0f, 20.0f);
	newBox.init(*m_world, sf::Vector2f(50.0f, 14.0f), sf::Vector2f(150.0f, 150.0f), 1);
	newBox.setTexture("Assets/Warrior.png");

	sprite ground(0.0f, 0.0f);
	ground.init(*m_world, sf::Vector2f(20.0f, 500.0f), sf::Vector2f(150.0f, 15.0f), 0);
	ground.setTexture("Assets/Grass block.png");
	ground.sp.setScale(150.0f/ 64.0f, 15.0f/64.0f);

	float timeStep = 1.0f / 60.0f;
	int32 vel = 6;
	int32 pos = 2;

	std::vector<sprite*> path;


	//Game Loop
	while (window.isOpen())
	{
		window.clear();
		float dt = dClock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

			newBox.getBody()->SetEnabled(true);
			ground.getBody()->SetEnabled(true);
			
			if (path.size() < 10)
			{
				for (int i = 0; i < 900; i+=5)
				{ // three seconds at 60fps
					sprite* temp = new sprite(0.0f, 0.0f);
					temp->setTexture("Assets/circle.png");

					b2Vec2 vel = b2Vec2(50.0f, -50.0f);
					b2Vec2 pos = newBox.getBody()->GetPosition();
					b2Vec2 trajectoryPosition = getTrajectoryPoint(pos, vel, i, m_world.get());
					temp->sp.setPosition(trajectoryPosition.x, trajectoryPosition.y);
					path.push_back(temp);
				}
			}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			//newBox.getBody()->SetLinearVelocity(b2Vec2(10.0f, newBox.getBody()->GetLinearVelocity().y));
			newBox.getBody()->SetLinearVelocity(b2Vec2(50.0f, -50.0f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			for (auto i : path)
			{
				delete i;

			}
			path.clear();

//			newBox.getBody()->SetLinearVelocity(b2Vec2(-50.0f, -50.0f));
			//newBox.getBody()->SetLinearVelocity(b2Vec2(10.0f, newBox.getBody()->GetLinearVelocity().y));
		}

		if(1)
		{
			static const double step = 1.0 / 60.0f;
			static double accumulator = 0.0;

			// max frame time to avoid spiral of death
			
			m_world->Step(step, vel, pos);

		}		

		ground.getBody()->SetLinearVelocity(b2Vec2(0.0f,0.0f));
		
		for (auto i : path)
		{
			i->draw(window);
		}

		ground.update();
		ground.draw(window);
		newBox.update();
		newBox.draw(window);
		window.display();
	}
	
}

void mousePressed()
{

}

