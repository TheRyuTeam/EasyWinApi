#include "Level.hpp"
#include <ewa/core/Keyboard.hpp>
#include <ewa/core/AudioPlayer.hpp>
#include <utility>
#include <thread>


void move(std::vector<Figure2d*>& figures, double x, double y)
{
	for (auto& figure : figures)
		figure->move(x, y);
}

Level::Level(BMPCanvas &canvas, Ship &ship,
			 std::function<void()> onWin, std::function<void()> onLose):
	_canvas(canvas),
	_enemies(canvas.width()),
	_bullets(),
	_score(0),
	_speed(1),
	_ship(ship),
	_onWin(std::move(onWin)),
	_onLose(std::move(onLose)),
	_running(false),
	_won(false)
{
}

bool Level::isRunning() const
{
	return _running;
}

void Level::draw()
{
	if (!_running)
		return;

	_enemies.draw(_canvas);

	for (const auto& bullet : _bullets)
	{
		if (bullet)
			bullet->draw(_canvas);
	}

	_ship.draw(_canvas);
}

void Level::loop()
{
	_ship.setPos({ _canvas.width() / 2.0, _canvas.height() - _ship.height() / 2.0 });
	_running = true;
	while (_running)
	{
		if (Keyboard::pressed(VK_SPACE))
		{
			auto bullets = _ship.shoot();
			if (!bullets.empty())
			{
				for (auto& b : bullets)
					_bullets.emplace_back(b);

				AudioPlayer::playAsync("D:\\shoot" + std::to_string(rand() % 3 + 1) + "e.wav");
			}
		}

		const auto rp = Keyboard::pressed(VK_RIGHT);
		const auto lp = Keyboard::pressed(VK_LEFT);
		const auto up = Keyboard::pressed(VK_UP);
		const auto dp = Keyboard::pressed(VK_DOWN);

		double x = 5 * (rp - lp);
		double y = 2 * (dp - up);

		if (rp || lp || up || dp)
		{
			if (x + _ship.rect().left <= 0 || x + _ship.rect().right >= _canvas.width())
				x = 0;

			if (y + _ship.rect().bottom >= _canvas.height() || _ship.rect().top - y <= 0)
				y = 0;

			_ship.move(x, y < 0 ? y / 2 : y);
		}

		if (_enemies.tick(_speed - (y < 0 ? y / 2 : 0), _ship))
		{
			_running = false;
			_onLose();
			return;
		}

		/////
		for (auto it = _bullets.begin(); it != _bullets.end();)
		{
			auto bullet  = it->get();
			bullet->move();

			if (bullet->pos().y <= -300 || ( bullet->pos().x < 0 || bullet->pos().x >= _canvas.width() ))
			{
				it = _bullets.erase(it);
			}
			else if (_enemies.tick(bullet, _score))
			{
				it = _bullets.erase(it);
				AudioPlayer::playAsync("D:\\blockDestroyed" + std::to_string(rand() % 2 + 1) + ".wav");
			}
			else
			{
				++it;
			}
		}

		if (_enemies.empty() || _ship.rect().bottom + 50 < _enemies.top())
		{
			_running = false;
			_onWin();
			return;
		}

		Sleep(10);
	}
}

void Level::stop()
{
	_running = false;
}

bool Level::won() const
{
	return _won;
}

size_t Level::score() const
{
	return _score;
}


