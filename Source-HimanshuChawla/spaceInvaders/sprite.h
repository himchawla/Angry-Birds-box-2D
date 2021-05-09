// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2019 Media Design School 
// 
//  File Name   :   sprite.h
//  Description :   Include for sprite class
//  Author      :   Himanshu Chawla
//  Mail        :   Himanshu.Cha8420@mediadesign.mail.nz 
// 
// Local Include


#pragma once

#include<box2d/box2d.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>


class sprite
{
public:
    float x, y, dx, dy, w, h;
    void destroy();
    void revive();
    void setTexture(std::string t);
    sprite(float x, float y);
    std::string Name;
    void setLocation(float, float);
    void draw(sf::RenderWindow& win);
    sf::FloatRect getRect();
    bool alive, dir, moving;
    std::vector<sprite> obj;

    sf::Vector2f dimensions;

    sf::Sprite sp;
    sf::Texture tx;
    virtual void update();
    void option(std::string NAME, float SPEED);
    ~sprite();

	void init(b2World* world, const sf::Vector2f& position, const sf::Vector2f& dim, bool dynamic);



    
    b2Body* getBody() { return m_body; }
    b2Fixture* getFixture() { return m_fixture; }

    b2World* getWorld() { return m_world; }
   
private:
    b2Body* m_body = nullptr;
    b2Fixture* m_fixture = nullptr;
    b2World* m_world;

};
