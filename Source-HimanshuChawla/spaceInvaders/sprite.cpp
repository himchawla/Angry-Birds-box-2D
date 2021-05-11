// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2019 Media Design School 
// 
//  File Name   :	sprite.cpp
//  Description :	Implementation for sprite class
//  Author      :   Himanshu Chawla
//  Mail        :   Himanshu.Cha8420@mediadesign.mail.nz 
// 
 // Implementation 



#include "sprite.h"
#include <stdexcept>

void sprite::setLocation(float x, float y)
{
	sprite::x = x;
	sprite::y = y;
	sp.setPosition(x, y);
}


void sprite::setTexture(std::string t)
{
	tx.loadFromFile(t);
	sp.setOrigin(tx.getSize().x * 0.5f, tx.getSize().y * 0.5f);
	sp.setTexture(tx);
}

sprite::sprite(float x, float y, std::string _name)
{
	Name = _name;
	alive = true;
	setLocation(x, y);

}






void sprite::draw(sf::RenderWindow& win)
{
	if (alive)
	{
		
		win.draw(sp);
	}
}

sf::FloatRect sprite::getRect()
{
	return sf::FloatRect(x, y, w, h);
}

void sprite::option(std::string NAME, float SPEED = 0)
{

	Name = NAME;

	dx = SPEED;

}

void sprite::revive()
{
	alive = true;
}

void sprite::destroy()
{
	alive = false;
}

sprite::~sprite()
{
}

void sprite::init(b2World* world, const sf::Vector2f& position, const sf::Vector2f& dim, bool dynamic)
{
	b2BodyDef bodyDef;
	if(dynamic)
		bodyDef.type = b2_dynamicBody;
	
	bodyDef.position.Set(position.x, position.y);
	m_body = world->CreateBody(&bodyDef);
	dimensions = sf::Vector2f((sp.getTexture()->getSize().x * sp.getScale().x) / 8, (sp.getTexture()->getSize().y * sp.getScale().y) / 8);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x, dimensions.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;


	m_world = world;
	m_fixture = m_body->CreateFixture(&fixtureDef);
	
	//m_body->SetEnabled(true);
	m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

void sprite::update()
{
	if (m_body->IsEnabled())
	{
		sp.setPosition(sf::Vector2f(m_body->GetPosition().x * 4.0f, m_body->GetPosition().y * 4.0f));
		sp.setRotation(m_body->GetAngle() * 180 / 3.14f);
	}
}