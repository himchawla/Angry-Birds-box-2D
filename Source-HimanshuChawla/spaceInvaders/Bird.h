#pragma once
#include "sprite.h"
class Bird :
	public sprite
{
public:
	Bird(float x, float y) :sprite(x, y, "Bird") {};
	float m_speed = 60.0f;
	int mass;
	b2Vec2 getTrajectoryPoint(b2Vec2& startingPosition, b2Vec2& startingVelocity, float n, b2World* world);
	void update(float _dT);
	void draw(sf::RenderWindow& win);
	void drawPath(sf::RenderWindow& win);
	void destroy(int time);
	bool CanDO() { return m_canDo; }
	void CanDo(bool _canDo) { m_canDo = _canDo; }

	bool Shoot() { return m_shoot; }
	void Shoot(bool _shoot) { m_shoot = _shoot; }
	

	enum eAbility
	{
		chuck,
		fall,
		none
	}m_ability = fall;
private:
	float m_timer = 0.0f;
	bool m_destroy = false;
	bool m_active = true;
	bool m_canDo = false;
	bool m_shoot = false;

	std::vector<sprite*> m_path;


};

