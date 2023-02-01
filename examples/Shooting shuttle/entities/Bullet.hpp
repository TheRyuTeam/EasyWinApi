#pragma once
#include <ewa/paints/2d/Figure2d.hpp>

class Bullet: public Circle
{
public:
	Bullet(const Point2d &pos, double rad, double damage);

	virtual inline void move();
	void move(double x, double y) override
	{
		Circle::move(x, y);
	}

	inline double damage() const noexcept;

protected:
	double _damage;

	double _xSpeed;
	double _ySpeed;
};

inline void Bullet::move()
{
	move(_xSpeed, _ySpeed);
}

inline double Bullet::damage() const noexcept
{
	return _damage;
}

class Bullet2: public Bullet
{
public:
	using Bullet::Bullet;

	void move() override
	{
		Bullet::move(_ySpeed / 2, _ySpeed / 2);
	}
};

class Bullet3: public Bullet
{
public:
	using Bullet::Bullet;

	void move() override
	{
		Bullet::move(- _ySpeed / 2, _ySpeed / 2);
	}
};

class Bullet41: public Bullet
{
public:
	Bullet41(const Point2d& point, double size, double damage):
		Bullet(point, size, damage),
		_start(point)
	{
	}

	void move() override
	{
		Bullet::move(3 * width() * std::sin((pos().y - _start.y) / 10), _ySpeed);
	}

protected:
	const Point2d _start;
};

class Bullet42: public Bullet
{
public:
	Bullet42(const Point2d& point, double size, double damage):
			Bullet(point, size, damage),
			_start(point)
	{
	}

	void move() override
	{
		Bullet::move(-3 * width() * std::sin((pos().y - _start.y) / 10), _ySpeed);
	}

protected:
	const Point2d _start;
};

class Bullet51: public Bullet
{
public:
	Bullet51(const Point2d& point, double size, double damage):
		Bullet(point, size, damage),
		_start(point)
	{
	}

	void move() override
	{
		Bullet::move(3 * width() * std::cos((pos().y - _start.y) / 10), _ySpeed);
	}

protected:
	const Point2d _start;
};

class Bullet52: public Bullet
{
public:
	Bullet52(const Point2d& point, double size, double damage):
			Bullet(point, size, damage),
			_start(point)
	{
	}

	void move() override
	{
		Bullet::move(- 3 * width() * std::cos((pos().y - _start.y) / 10), _ySpeed);
	}

protected:
	const Point2d _start;
};