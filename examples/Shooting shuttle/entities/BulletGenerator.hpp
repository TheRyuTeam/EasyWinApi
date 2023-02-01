#pragma once
#include "Bullet.hpp"

class Gun
{
public:
	virtual Bullet* generate(const Point2d& pos)
	{
		return new Bullet(pos, size, damage);
	}

	double baseDamage = 1;

	double size = 2;
	double damage = 1;
};

template <class BulletT>
class BulletGenerator: public Gun
{
public:
	Bullet* generate(const Point2d& pos) override
	{
		return new BulletT(pos, size, damage);
	}
};
