#pragma once
#include <ewa/ewa.hpp>
#include <Windows.h>
#include <vector>

#define WIN_THIS_PTR_I 1798

class Window;

class EWA_API CoreApplication
{
public:
	CoreApplication(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

	int exec();

	static HINSTANCE hInstance() noexcept;
	static HINSTANCE hPrevInstanceance() noexcept;
	static LPSTR cmd() noexcept;
	static int nCmdShow() noexcept;

	static size_t nMaxFps() noexcept;
	static void setNMaxFps(size_t fps) noexcept;

	static LRESULT wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	static HINSTANCE _hInstance;
	static HINSTANCE _hPrevInstance;
	static LPSTR _cmd;
	static int _nCmdShow;

	static size_t _nMaxFps;

	static std::vector<Window*> _windows;

	friend class Window;
};

