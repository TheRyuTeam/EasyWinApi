#pragma once
#include <ewa/paints/2d/Figure2d.hpp>

class Enemy: public Square
{
public:
	Enemy(const Point2d& pos, double size, double hp, size_t bounty);

	inline bool isAlive() const noexcept;
	inline size_t bounty() const noexcept;

	void move(double x, double y) override;

	void attack(double damage);

	void drawImpl(Canvas& canvas) const override;

private:
	const double _initHp;
	const size_t _bounty;
	double _hp;
	class Rectangle _hpIndicator;
};

inline bool Enemy::isAlive() const noexcept
{
	return _hp > 0;
}

inline size_t Enemy::bounty() const noexcept
{
	return _bounty;
}