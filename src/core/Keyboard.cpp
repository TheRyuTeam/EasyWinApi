#include <ewa/core/Keyboard.hpp>
#include <Windows.h>

bool Keyboard::pressed(int key)
{
	return GetAsyncKeyState(key);
}
