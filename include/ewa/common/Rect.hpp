#pragma once
#include <Windows.h>
#include <ewa/ewa.hpp>

class Point2d;
class Size2d;

struct EWA_API Rect2d
{
	Point2d toPos() const noexcept;
	Size2d toSize() const noexcept;
	RECT toTagRect() const noexcept;

	operator RECT() const noexcept { return toTagRect(); }

	bool intersect(const Rect2d& other) const noexcept;

	double left;
	double top;
	double right;
	double bottom;
};

