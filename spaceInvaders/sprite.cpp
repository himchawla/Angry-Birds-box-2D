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

sprite::sprite(float x, float y)
{
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

void sprite::init(b2World& world, const sf::Vector2f& position, const sf::Vector2f& dimensions, bool dynamic)
{
	b2BodyDef bodyDef;
	if(dynamic)
		bodyDef.type = b2_dynamicBody;
	
	bodyDef.position.Set(position.x, position.y);
	body = world.CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	fixture = body->CreateFixture(&fixtureDef);
	
	body->SetEnabled(false);
}

void sprite::update()
{
	sp.setPosition(sf::Vector2f(body->GetPosition().x, body->GetPosition().y));
}