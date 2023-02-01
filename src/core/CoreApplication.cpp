#include <ewa/core/CoreApplication.hpp>
#include <ewa/widgets/Window.hpp>
#include <algorithm>
#include <windowsx.h>

HINSTANCE CoreApplication::_hInstance = nullptr;
HINSTANCE CoreApplication::_hPrevInstance = nullptr;
LPSTR CoreApplication::_cmd = nullptr;
int CoreApplication::_nCmdShow = -1;
size_t CoreApplication::_nMaxFps = 60;

std::vector<Window*> CoreApplication::_windows = {};



CoreApplication::CoreApplication(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_hInstance = hInstance;
	_hPrevInstance = hPrevInstance;
	_cmd = lpCmdLine;
	_nCmdShow = nCmdShow;
}

int CoreApplication::exec()
{
	LARGE_INTEGER clock_frequency   { 0 };
	LARGE_INTEGER frame_begin       { 0 };
	LARGE_INTEGER frame_end         { 0 };

	QueryPerformanceFrequency(&clock_frequency);

	MSG msg{};
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return 0;

			DispatchMessage(&msg);
		}
		else
		{
			QueryPerformanceCounter(&frame_end);

			const auto diff = frame_end.QuadPart - frame_begin.QuadPart;
			auto fps = diff ? clock_frequency.QuadPart / diff : 0;

			if (fps < _nMaxFps)
			{
				QueryPerformanceCounter(&frame_begin);

				for (auto& w : _windows)
					PostMessage(w->handle(), WM_PAINT, 0, 0);
			}
		}
	}

	return 0;
}

HINSTANCE CoreApplication::hInstance() noexcept
{
	return _hInstance;
}

HINSTANCE CoreApplication::hPrevInstanceance() noexcept
{
	return _hPrevInstance;
}

LPSTR CoreApplication::cmd() noexcept
{
	return _cmd;
}

int CoreApplication::nCmdShow() noexcept
{
	return _nCmdShow;
}

size_t CoreApplication::nMaxFps() noexcept
{
	return _nMaxFps;
}

void CoreApplication::setNMaxFps(size_t fps) noexcept
{
	_nMaxFps = fps;
}


#define TRACK_EVENT(wmEvent, EventObj)\
case wmEvent:\
{\
    e = new EventObj;\
    break;\
}

LRESULT CoreApplication::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Event* e = nullptr;

	switch (uMsg)
	{
		case WM_CREATE:
		{
			return 0;
		}

		case WM_ERASEBKGND:
		{
			return 1;
		}

			// Mouse clicked
		TRACK_EVENT(WM_LBUTTONDOWN,
					MousePressedEvent(MouseClickEvent::Button::Left, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam))
		TRACK_EVENT(WM_LBUTTONUP,
					MouseReleasedEvent(MouseClickEvent::Button::Left, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam))
		TRACK_EVENT(WM_LBUTTONDBLCLK,
					MouseDbClickEvent(MouseClickEvent::Button::Left, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam))

		TRACK_EVENT(WM_RBUTTONDOWN,
					MousePressedEvent(MouseClickEvent::Button::Right, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam))
		TRACK_EVENT(WM_RBUTTONUP,
					MouseReleasedEvent(MouseClickEvent::Button::Right, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam))
		TRACK_EVENT(WM_RBUTTONDBLCLK,
					MouseDbClickEvent(MouseClickEvent::Button::Right, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam))

			// Mouse move
		TRACK_EVENT(WM_MOUSEMOVE, MouseMoveEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam))

			// Mouse hover
		TRACK_EVENT(WM_MOUSEHOVER, MouseHoverEvent(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))

			// Key click
		TRACK_EVENT(WM_KEYDOWN, KeyPressedEvent(wParam))
		TRACK_EVENT(WM_KEYUP, KeyReleasedEvent(wParam))

		case WM_PAINT:
		{
			e = new DrawEvent();
			break;
		}

		case WM_CLOSE:
		{
			auto c = GetWindowLongPtr(hWnd, GWLP_USERDATA);

			if (dynamic_cast<Window*>((Widget*)c))
			{
				auto it = PP_FIND(_windows, (Window*)c);
				if (it != _windows.end())
					_windows.erase(it);

				if (_windows.empty())
					PostMessage(nullptr, WM_QUIT, 0, 0);

				CloseWindow(hWnd);
			}

			return 0;
		}

		case WM_QUIT:
		{
			PostQuitMessage(0);
			return 0;
		}

		default:
			break;
	}

	if (e)
	{
		auto widget = dynamic_cast<Widget*>((Widget*)GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (widget)
			widget->event(e);

		delete e;

		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
