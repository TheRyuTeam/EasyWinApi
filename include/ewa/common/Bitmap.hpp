#pragma once
#include <Windows.h>
#include <string>

struct Bitmap
{
	size_t width() const noexcept;
	size_t height() const noexcept;

	static Bitmap fromImage(const std::string& filename);

	HBITMAP hBitmap;
	BITMAP bitmap;
};
