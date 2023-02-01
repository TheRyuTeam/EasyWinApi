#pragma once
#include <ewa/widgets/Window.hpp>
#include <ewa/paints/BMPCanvas.hpp>
#include "entities/Ship.hpp"
#include "entities/Button.hpp"
#include "utils/Level.hpp"
#include <map>
#include <thread>

class Game : public Window
{
public:
	explicit Game(Window* parent = nullptr);
	~Game();

	void run();
	void stop();

	void init();

	void drawEvent(DrawEvent* e) override;

	void mouseMoveEvent(MouseMoveEvent* e) override;

	void mousePressedEvent(MousePressedEvent* e) override;

protected:
	void onLose();
	void onWin();

private:
	BMPCanvas _canvas;

	Ship _ship;
	Level* _currentLevel;

	size_t _scores;
	Button _restartBtn;
	std::thread _gameThread;
};