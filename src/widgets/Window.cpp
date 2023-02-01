#include <ewa/widgets/Window.hpp>
#include <ewa/core/CoreApplication.hpp>
#include <stdexcept>
#include <algorithm>

#define WINDOW_CLASS_NAME "WindowClass"


bool _registered = false;


void registerClass()
{
	WNDCLASS wc{};
	wc.lpfnWndProc = CoreApplication::wndProc;
	wc.hInstance = CoreApplication::hInstance();
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = WINDOW_CLASS_NAME;

	if (!RegisterClass(&wc))
		throw std::runtime_error("Can not register WindowClass");

	_registered = true;
}


HWND createWindow(const SIZE& size, const std::string& title, HWND parent)
{
	if (!_registered)
		registerClass();

	RECT winRect { 0, 0, size.cx, size.cy };

	AdjustWindowRectEx(&winRect, WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME), false, WS_EX_DLGMODALFRAME);

	const auto width = winRect.right - winRect.left;
	const auto height = winRect.bottom - winRect.top;
	const auto x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	const auto y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

	HWND hWnd = CreateWindowEx(
			WS_EX_DLGMODALFRAME, WINDOW_CLASS_NAME, title.c_str(),
			WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME),
			x, y, width, height, parent,
			nullptr, CoreApplication::hInstance(), nullptr
	);

	if (!hWnd)
		throw std::runtime_error("Can not create window.");

	return hWnd;
}



Window::Window(const SIZE& size, const std::string& title, Window* parent):
		Widget(createWindow(size, title, parent ? parent->handle() : nullptr), parent)
{
	SetWindowLongPtr(handle(), GWLP_USERDATA, (LONG_PTR)this);

	CoreApplication::_windows.push_back(this);
	UpdateWindow(handle());
}

Window::~Window()
{
	auto it = PP_FIND(CoreApplication::_windows, this);

	if (it != CoreApplication::_windows.end())
		CoreApplication::_windows.erase(it);
}



