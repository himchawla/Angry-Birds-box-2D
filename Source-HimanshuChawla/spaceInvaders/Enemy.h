#pragma once
#include "sprite.h"
class Enemy :
	public sprite
{
public:
	Enemy(std::string name) :sprite(0.0f, 0.0f, "Destructable") {}
	float health = 50000.0f;

};

