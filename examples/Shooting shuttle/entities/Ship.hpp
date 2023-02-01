#pragma once
#include "BulletGenerator.hpp"
#include <chrono>
#include <vector>

class Ship: public BMPFigure
{
public:
	Ship(const Point2d& pos);

	void addGun(Gun* gun);

	std::vector<Bullet*> shoot();

private:
	double _baseDamage = 8;
	std::vector<Gun*> _guns;
	std::chrono::system_clock::time_point _lastShot;
	std::chrono::milliseconds _cooldown;
};