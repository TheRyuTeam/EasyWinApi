#include <ewa/common/Size.hpp>
#include <ewa/common/Point.hpp>

Point2d Size2d::toPos() const noexcept
{
	return { width / 2, height / 2 };
}
