#include "Enemy.hpp"

Enemy::Enemy(const Point2d& pos, double size, double hp, size_t bounty):
	Square(pos, size),
	_initHp(hp),
	_bounty(bounty),
	_hp(hp),
	_hpIndicator(pos.move(1, 1), size - pen().width() * 2, size - pen().width() * 2)
{
	_hpIndicator.setBrush(Brush(Color::AliceBlue + (COLORREF)_initHp * 10));
	_hpIndicator.setPen(Pen(0, 0, Pen::Style::Null));
}

void Enemy::move(double x, double y)
{
	Square::move(x, y);
	_hpIndicator.move(x, y);
}

void Enemy::attack(double damage)
{
	_hp -= damage;
	if (_hp <= 0)
		return;

	const double perc = _hp / _initHp;

	_hpIndicator.setHeight(_hpIndicator.height() * perc);
	_hpIndicator.setWidth(_hpIndicator.width() * perc);
}

void Enemy::drawImpl(Canvas& canvas) const
{
	_hpIndicator.draw(canvas);
	Square::drawImpl(canvas);
}