#pragma once
#include <ewa/paints/Canvas.hpp>

class EWA_API BMPCanvas : public Canvas
{
public:
	BMPCanvas(HWND window);

	~BMPCanvas();

	int width() const noexcept;

	int height() const noexcept;

	void draw();

	void clear();

private:
	HWND _window;
	HDC _hdc;

	BITMAPINFO _bitmapInfo;
	byte_t* _bitmapBuffer;
	HBITMAP _bitmap;

	HDC _memoryDc;
};
