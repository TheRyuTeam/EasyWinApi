#include <ewa/paints/BMPCanvas.hpp>
#include <winuser.h>
#include <memory>
#include <stdexcept>


SIZE getHwndSize(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	return { rect.right - rect.left, rect.bottom - rect.top };
}

HBITMAP createDIBSection(HDC hdc, const BITMAPINFO& bitmapInfo, UINT usage, void** buffer,
						 HANDLE hSection = nullptr, DWORD offset = 0)
{
	HBITMAP bitmap = CreateDIBSection(hdc, &bitmapInfo, usage, buffer, hSection, offset);

	if (!bitmap)
		throw std::runtime_error("Can not create DIB section.");

	return bitmap;
}

BITMAPINFO createBitmapInfo(const SIZE& size)
{
	BITMAPINFO bitmapInfo{};

	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biWidth = size.cx;
	bitmapInfo.bmiHeader.biHeight = -size.cy;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 32;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;

	return bitmapInfo;
}

BMPCanvas::BMPCanvas(HWND window):
	Canvas(nullptr),
	_window(window),
	_hdc(GetDC(_window)),
	_bitmapInfo(createBitmapInfo(getHwndSize(_window))),
	_bitmapBuffer(nullptr),
	_bitmap(createDIBSection(_hdc, _bitmapInfo, DIB_RGB_COLORS, (void**)&_bitmapBuffer)),
	_memoryDc(CreateCompatibleDC(_hdc))
{
	setHdc(_memoryDc);

	SelectObject(_memoryDc, _bitmap);

	clear();
}

BMPCanvas::~BMPCanvas()
{
	DeleteObject(_bitmap);

	DeleteDC(_memoryDc);

	ReleaseDC(_window, _hdc);
}

int BMPCanvas::width() const noexcept
{
	return _bitmapInfo.bmiHeader.biWidth;
}

int BMPCanvas::height() const noexcept
{
	return std::abs(_bitmapInfo.bmiHeader.biHeight);
}

void BMPCanvas::draw()
{
	BitBlt(_hdc, 0, 0, width(), height(), _memoryDc, 0, 0, SRCCOPY);
	ValidateRect(_window, nullptr);
}

void BMPCanvas::clear()
{
	memset(_bitmapBuffer, (int)bgBrush().color().value(), 4ull * width() * height());
}
