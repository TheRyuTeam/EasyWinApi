#pragma once
#include <ewa/paints/BMPCanvas.hpp>
#include <ewa/paints/2d/Scene2d.hpp>
#include "../entities/Bullet.hpp"
#include "../entities/Enemy.hpp"
#include "../entities/Ship.hpp"
#include <functional>
#include <map>

inline bool circlesTouch(const Figure2d* a, const Figure2d* b)
{
	return std::abs(a->pos().y - b->pos().y) <= (a->height() + b->height()) / 2 &&
		   std::abs(a->pos().x - b->pos().x) <= (a->width() + b->width()) / 2;
}

class EnemyRow
{
public:
	EnemyRow(double y, double width, double hp, double bounty):
		_y(y + 17.5),
		_enemies()
	{
		const double cw2 = width;

		for (size_t j = 0; j < cw2; j += 40)
		{
			auto enemy = new Enemy({ 17.5 + j, y }, 35, 1, 1);
			_enemies.push_back(std::unique_ptr<Enemy>(enemy));
		}
	}

	double y() const
	{
		return _y;
	}

	void draw(Canvas& canvas) const
	{
		for (const auto& enemy : _enemies)
		{
			if (enemy)
				enemy->draw(canvas);
		}
	}

	bool tick(double y, const Ship& ship)
	{
		_y += y;
		for (auto& enemy : _enemies)
		{
			enemy->move(0, y);
			if (circlesTouch(enemy.get(), &ship))
				return true;
		}

		return false;
	}

	bool tick(Bullet* bullet, size_t& score)
	{
		for (auto eit = _enemies.begin(); eit != _enemies.end(); ++eit)
		{
			auto enemy = eit->get();
			if (circlesTouch(bullet, enemy))
			{
				enemy->attack(bullet->damage());
				if (!enemy->isAlive())
				{
					score += (*eit)->bounty();
					_enemies.erase(eit);
				}
				return true;
			}
		}

		return false;
	}

	bool empty() const
	{
		return _enemies.empty();
	}
private:
	double _y;
	std::vector<std::unique_ptr<Enemy>> _enemies;
};

class Enemies
{
public:
	Enemies(int width)
	{
		for (int64_t i = -1200; i < 0; i += 40)
			_enemies.emplace_back(i, width, 1, 1);
	}

	void draw(Canvas& canvas) const
	{
		for (const auto& row : _enemies)
		{
			if (row.y() > 0)
				row.draw(canvas);
		}
	}

	bool tick(double y, const Ship& ship)
	{
		for (auto& row: _enemies)
		{
			if (row.tick(y, ship))
			{
				return true;
			}
		}

		return false;
	}

	double top() const
	{
		return _enemies.front().y() - 35;
	}

	bool tick(Bullet* bullet, size_t& score)
	{
		for (auto eit = _enemies.begin(); eit != _enemies.end(); ++eit)
		{
			if (eit->tick(bullet, score))
			{
				if (eit->empty())
					_enemies.erase(eit);

				return true;
			}
		}

		return false;
	}

	bool empty() const
	{
		return _enemies.empty();
	}

private:
	std::vector<EnemyRow> _enemies;
};

class Level
{
public:
	Level(BMPCanvas& canvas, Ship& ship, std::function<void()> onWin, std::function<void()> onLose);

	void loop();
	void draw();

	bool isRunning() const;
	void stop();
	bool won() const;

	size_t score() const;

private:
	BMPCanvas& _canvas;

	std::vector<std::unique_ptr<Bullet>> _bullets;
	Enemies _enemies;
	size_t _score;
	double _speed;

	Ship& _ship;

	std::function<void()> _onWin;
	std::function<void()> _onLose;
	bool _running;
	bool _won;
};

