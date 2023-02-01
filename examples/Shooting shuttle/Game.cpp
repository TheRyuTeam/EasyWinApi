#include "Game.hpp"
#include <ewa/core/AudioPlayer.hpp>
#include "entities/Bullet.hpp"


Game::Game(Window* parent):
	Window({ 960, 640 }, "RWA", parent),
	_canvas(handle()),
	_ship(center()),
	_scores(0),
	_restartBtn("Again", center(), 150, 50),
	_gameThread()
{
	_ship.addGun(new BulletGenerator<Bullet>());
	_ship.addGun(new BulletGenerator<Bullet2>());
	_ship.addGun(new BulletGenerator<Bullet3>());
	_ship.addGun(new BulletGenerator<Bullet41>());
	_ship.addGun(new BulletGenerator<Bullet42>());
	_ship.addGun(new BulletGenerator<Bullet51>());
	_ship.addGun(new BulletGenerator<Bullet52>());

	init();
}

void Game::run()
{
	if (_currentLevel)
		_currentLevel->stop();

	if (_gameThread.joinable())
		_gameThread.join();

	_gameThread = std::thread([this](){
		_currentLevel->loop();
	});
}

void Game::init()
{
	_currentLevel = new Level(_canvas, _ship, [this]()
	{
		onWin();
	}, [this]()
	{
		onLose();
	});

}

void Game::drawEvent(DrawEvent* e)
{
	_canvas.clear();
	if (_currentLevel->isRunning())
	{
		_currentLevel->draw();
	}
	else
	{
		RECT r = rect().toTagRect();
		_canvas.text("You Win! Scores: " + std::to_string(_scores), r, DT_CENTER | DT_NOCLIP);
		_restartBtn.draw(_canvas);
	}

	_canvas.draw();
}

void Game::mouseMoveEvent(MouseMoveEvent* e)
{
	static auto pc = GetCursor();

	if (!_currentLevel->isRunning())
	{
		if (_restartBtn.has(e->x(), e->y()))
			SetCursor(LoadCursor(nullptr, IDC_HAND));
		else
			SetCursor(pc);
	}
}

void Game::mousePressedEvent(MousePressedEvent* e)
{
	if (!_currentLevel->isRunning() &&
		e->leftButtonPressed() &&
		_restartBtn.has(e->x(), e->y()))
	{
		init();
		run();
	}
}

void Game::onLose()
{
	_scores = _currentLevel->score();
	AudioPlayer::play("D:\\loosee.wav");
}

void Game::onWin()
{
	_scores = _currentLevel->score();
	AudioPlayer::play("D:\\win.wav");
}

void Game::stop()
{
	_currentLevel->stop();
}

Game::~Game()
{
	_currentLevel->stop();
	_gameThread.join();
}
