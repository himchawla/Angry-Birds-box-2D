#include<SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include"sprite.h"
#include "Bird.h" 
#include<math.h>
#include"ContactListener.h"

class TrajectoryRayCastClosestCallback : public b2RayCastCallback
{
public:
	TrajectoryRayCastClosestCallback(b2Body* ignoreBody) : m_hit(false), m_ignoreBody(ignoreBody) {}

	float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
	{
		if (fixture->GetBody() == m_ignoreBody)
			return -1;

		m_hit = true;
		m_point = point;
		m_normal = normal;
		return fraction;
	}

	b2Body* m_ignoreBody;
	bool m_hit;
	b2Vec2 m_point;
	b2Vec2 m_normal;
};


int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML");

	ContactListener m_contactListener;

	sf::Clock dClock;
	b2World* m_world;

	std::vector<sprite*> level;

	window.setFramerateLimit(240);

	//World Setup
	b2Vec2 gravity(0.0f, 9.81f);
	m_world = new b2World(gravity);


	//Ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(240.0f, 100.0f);

	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	//groundBody->GetUserData().data = nullptr;

	std::cout << m_world->GetBodyCount()<<"\n";
	//Ground Fixture

	b2PolygonShape groundBox;
	groundBox.SetAsBox(960.0f, 10.0f);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 1.0f;
	groundBody->CreateFixture(&fixtureDef);
	

	Bird newBox(800.0f, 400.0f);
	newBox.setTexture("Assets/bird.png");
	newBox.init(m_world, sf::Vector2f(50.0f, 95.0f), sf::Vector2f(32.0f, 32.0f), 1);

	sprite *temp = new sprite(0.0f, 0.0f, "Indestructable");
	temp->setTexture("Assets/Block.png");
	temp->sp.setScale(10.0f, 1.0f);
	temp->init(m_world, sf::Vector2f(170.0f, 4.0f), sf::Vector2f(160.0f, 16.0f), 1);
	//
	level.push_back(temp);

	temp = new sprite(0.0f, 0.0f, "Destructable");
	temp->sp.setScale(sf::Vector2f(1.0f, 10.0f));
	temp->setTexture("Assets/Block.png");
	temp->init(m_world, sf::Vector2f(162.5f, 100.0f), sf::Vector2f(16.0f, 160.0f), 1);
	level.push_back(temp);

	temp = new sprite(0.0f, 0.0f, "Destructable");
	temp->sp.setScale(sf::Vector2f(1.0f, 10.0f));
	temp->setTexture("Assets/Block.png");
	temp->init(m_world, sf::Vector2f(175.0f, 100.0f), sf::Vector2f(16.0f, 160.0f), 1);
	level.push_back(temp);

	sprite* rev1 = new sprite(0.0f,0.0f, "Indestructable");
	rev1->sp.setScale(1.0f, 5.0f);
	rev1->setTexture("Assets/block.png");
	rev1->init(m_world, sf::Vector2f(200.0f, 25.0f), sf::Vector2f(16.0f, 80.0f), 0);
	level.push_back(rev1);
	
	sprite* rev2 = new sprite(0.0f, 0.0f, "Indestructable");
	rev2->sp.setScale(4.0f, 4.0f);
	rev2->setTexture("Assets/circle.png");
	rev2->init(m_world, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(32.0f, 32.0f), 1);
	level.push_back(rev2);

//	rev1.getBody()->SetGravityScale(0.0f);
	//rev2.getBody()->SetGravityScale(0.0f);

	b2RevoluteJointDef revoluteJointDef;

	revoluteJointDef.Initialize(rev1->getBody(), rev2->getBody(), rev1->getBody()->GetWorldCenter());

	revoluteJointDef.motorSpeed = 0.0f * 2.0f;
	revoluteJointDef.maxMotorTorque = 1000.0f;
	revoluteJointDef.enableMotor = true;
	
	b2Joint *joint =  m_world->CreateJoint(&revoluteJointDef);

	float timeStep = 1.0f / 60.0f;
	int32 v = 6;
	int32 pos = 2;


	

	float lastTime = 0.0f;
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

		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			window.close();
			main();
		}


		if (1)
		{
			static const double step = 1.0 / 60.0f;
			static double accumulator = 0.0;

			// max frame time to avoid spiral of death

			m_world->Step(step, v, pos);

		}
		m_world->SetContactListener(&m_contactListener);


		//ground.getBody()->SetLinearVelocity(b2Vec2(0.0f,0.0f));

		
		newBox.update(window);
		newBox.draw(window);
		std::vector<sprite*>::iterator it = level.begin();
		while (it != level.end())
		{
			if (!(*it)->alive)
			{
				m_world->DestroyBody((*it)->getBody());
				delete (*it);
				level.erase(it);
				break;
			}
				(*it)->update();
			(*it)->draw(window);
			it++;
		}
		
		window.display();
	
	}

}



void mousePressed()
{

}

