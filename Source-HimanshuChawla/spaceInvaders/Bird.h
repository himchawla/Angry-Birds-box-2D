#pragma once
#include "sprite.h"
class Bird :
	public sprite
{
public:
	Bird(float x, float y) :sprite(x, y) {};
	int speed;
	int mass;
	b2Vec2 getTrajectoryPoint(b2Vec2& startingPosition, b2Vec2& startingVelocity, float n, b2World* world);
	void update();
	bool CanDO() { return m_canDo; }
	void CanDo(bool _canDo) { m_canDo = _canDo; }

	bool Shoot() { return m_shoot; }
	void Shoot(bool _shoot) { m_shoot = _shoot; }
	
	enum eAbility
	{
		chuck,
		none
	}m_ability;
private:
	bool m_canDo = false;
	bool m_shoot = false;

	std::vector<sprite*> m_path;


};

