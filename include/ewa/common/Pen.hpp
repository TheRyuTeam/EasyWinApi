#pragma once
#include <ewa/common/Color.hpp>

class EWA_API Pen
{
public:
	enum class Style : int
	{
		Solid = PS_SOLID,
		Dash = PS_DASH,
		Dot = PS_DOT,
		DashDot = PS_DASH,
		DashDotDot = PS_DASHDOTDOT,
		Insideframe = PS_INSIDEFRAME,
		Null = PS_NULL
	};

	using width_t = int;

	Pen(const Color& color = 0, width_t width = 1, Style style = Style::Solid);
	Pen(const Pen&) = default;
	Pen(Pen&&) noexcept = default;

	Pen& operator=(const Pen&) = default;
	Pen& operator=(Pen&&) noexcept = default;

	inline Style style() const;

	inline Color color() const;

	inline width_t width() const;

	void setStyle(Style style);

	void setColor(const Color& color);

	void setWidth(width_t width);

private:
	Style _style;
	Color _color;
	width_t _width;
};

/// @section Pen inlines
inline Pen::Style Pen::style() const
{
	return _style;
}

inline Color Pen::color() const
{
	return _color;
}

inline Pen::width_t Pen::width() const
{
	return _width;
}

/// @section Pen comparison
inline bool operator==(const Pen& lhs, const Pen& rhs)
{
	return lhs.style() == rhs.style() && lhs.color() == rhs.color() && lhs.width() == rhs.width();
}

inline bool operator!=(const Pen& lhs, const Pen& rhs)
{
	return !(lhs == rhs);
}

/// @section detail
namespace detail
{

inline HPEN createHPEN(const Pen& pen)
{
	return CreatePen(static_cast<int>(pen.style()),
					 pen.width(),
					 pen.color().value());
}

}