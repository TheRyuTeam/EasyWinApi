#pragma once
#include <ewa/ewa.hpp>

class Point2d;

struct EWA_API Size2d
{
	Point2d toPos() const noexcept;

	double width;
	double height;
};
