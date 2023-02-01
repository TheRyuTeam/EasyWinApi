#pragma once
#include <ewa/common/Color.hpp>

class EWA_API Brush
{
public:
	enum class Style : int
	{
		Solid = BS_SOLID,
		Hollow = BS_HOLLOW,
	};

	Brush();
	Brush(const Color& color);

	Brush(const Brush&) = default;
	Brush(Brush&&) noexcept = default;

	Brush& operator=(const Brush&) = default;
	Brush& operator=(Brush&&) noexcept = default;

	inline Style style() const;

	inline Color color() const;

	void setStyle(Style style);

	void setColor(const Color& color);

private:
	Style _style;
	Color _color;
};

/// @section Brush inlines
inline Brush::Style Brush::style() const
{
	return _style;
}

inline Color Brush::color() const
{
	return _color;
}

/// @section Brush comparison
inline bool operator==(const Brush& lhs, const Brush& rhs)
{
	return lhs.style() == rhs.style() && lhs.color() == rhs.color();
}

inline bool operator!=(const Brush& lhs, const Brush& rhs)
{
	return !(lhs == rhs);
}

/// @section detail
namespace detail
{

inline HBRUSH createHBRUSH(const Brush& brush)
{
	return brush.style() == Brush::Style::Solid
		   ? CreateSolidBrush(brush.color().value())
		   : (HBRUSH)GetStockObject(HOLLOW_BRUSH);
}

}