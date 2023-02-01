#pragma once
#include <ewa/ewa.hpp>

struct EWA_API Point2d
{
	inline double distance(const Point2d& other) const noexcept;
	Point2d move(double dx, double dy) const noexcept;

	double x;
	double y;
};

inline double Point2d::distance(const Point2d& other) const noexcept
{
	return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
}

inline Point2d Point2d::move(double dx, double dy) const noexcept
{
	return { x + dx, y + dy };
}
