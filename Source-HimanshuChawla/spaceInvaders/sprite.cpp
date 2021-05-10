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
		sp.setTexture(tx);
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
	
	bodyDef.position.Set(position.x, position.y - dim.y);
	m_body = world->CreateBody(&bodyDef);
	dimensions = sf::Vector2f(dim.x/2, dim.y/2);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x, dimensions.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	m_world = world;
	m_fixture = m_body->CreateFixture(&fixtureDef);
	
	m_body->SetEnabled(true);
}

void sprite::update()
{
	sp.setPosition(sf::Vector2f(m_body->GetPosition().x - dimensions.x, m_body->GetPosition().y - dimensions.y));
	sp.setRotation(m_body->GetAngle() * 180 / 3.14f);
}