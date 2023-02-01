#include <ewa/common/Rect.hpp>
#include <ewa/common/Point.hpp>
#include <ewa/common/Size.hpp>


Point2d Rect2d::toPos() const noexcept
{
	return toSize().toPos();
}

Size2d Rect2d::toSize() const noexcept
{
	return { right - left, bottom - top };
}

RECT Rect2d::toTagRect() const noexcept
{
	return { dtoi(left), dtoi(top), dtoi(right), dtoi(bottom) };
}

bool Rect2d::intersect(const Rect2d& other) const noexcept
{
	const auto s1 = ( left >= other.left && left <= other.right ) || ( right >= other.left && right <= other.right );
	const auto s2 = ( top >= other.top && top <= other.bottom ) || ( bottom >= other.top && bottom <= other.bottom );
	const auto s3 = ( other.left >= left && other.left <= right ) || ( other.right >= left && other.right <= right );
	const auto s4 = ( other.top >= top && other.top <= bottom ) || ( other.bottom >= top && other.bottom <= bottom );

	return (s1 && s2) || (s3 && s4) || (s1 && s4) || (s3 && s2);
}

