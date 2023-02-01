#include "Bullet.hpp"

Bullet::Bullet(const Point2d &pos, double rad, double damage) :
	Circle(pos, rad),
	_damage(damage),
	_xSpeed(0),
	_ySpeed(-5)
{
}