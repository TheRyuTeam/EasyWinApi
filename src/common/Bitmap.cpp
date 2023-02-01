#include <ewa/common/Bitmap.hpp>

size_t Bitmap::width() const noexcept
{
	return bitmap.bmWidth;
}

size_t Bitmap::height() const noexcept
{
	return bitmap.bmHeight;
}

Bitmap Bitmap::fromImage(const std::string &filename)
{
	Bitmap bmp{};
	bmp.hBitmap = (HBITMAP)LoadImageA(nullptr, filename.c_str(), IMAGE_BITMAP, 0, 0,
									  LR_DEFAULTCOLOR | LR_LOADFROMFILE);
	GetObject(bmp.hBitmap, sizeof(bmp.bitmap), &bmp.bitmap);

	return bmp;
}


