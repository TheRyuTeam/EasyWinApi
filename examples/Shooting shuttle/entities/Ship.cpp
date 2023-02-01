#include "Ship.hpp"

Ship::Ship(const Point2d& pos):
	BMPFigure(pos, Bitmap::fromImage("D:\\Ship.bmp")),
	_baseDamage(1),
	_guns(),
	_lastShot(),
	_cooldown(100)
{
}

std::vector<Bullet*> Ship::shoot()
{
	const auto now = std::chrono::system_clock::now();
	const auto msFromLastShot =
					   std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastShot);

	if (msFromLastShot < _cooldown)
		return {};

	_lastShot = now;

	std::vector<Bullet*> bullets;
	for (const auto& gun : _guns)
		bullets.push_back(gun->generate(pos()));

	return bullets;
}

void Ship::addGun(Gun* gun)
{
	_guns.push_back(gun);
}
