#include <ewa/common/Brush.hpp>

Brush::Brush():
		_style(Style::Hollow),
		_color(Color::Black)
{
}

Brush::Brush(const Color& color):
		_style(Style::Solid),
		_color(color)
{
}

void Brush::setStyle(Style style)
{
	_style = style;
}

void Brush::setColor(const Color& color)
{
	_color = color;
}
