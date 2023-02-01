#include "ewa/core/CoreApplication.hpp"
#include "Game.hpp"

int WinMain(_In_ HINSTANCE hInstance,
			_In_opt_ HINSTANCE hPrevInstance,
			_In_ LPSTR    lpCmdLine,
			_In_ int       nCmdShow)
{
	CoreApplication app(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	Game game;
	game.show();

	game.run();
	int exec = app.exec();
	game.stop();

	return exec;
}
