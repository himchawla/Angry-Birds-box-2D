#include "Bird.h"
#include<stack>
#pragma once
class BirdManager
{
public:
	BirdManager(int _num)
	{

	}
private:


	std::stack<Bird*> birds;

	int numBirds;
};

