#include <ewa/common/Pen.hpp>

Pen::Pen(const Color& color, width_t width, Style style) :
		_style(style),
		_color(color),
		_width(width)
{
}

void Pen::setStyle(Style style)
{
	_style = style;
}

void Pen::setColor(const Color& color)
{
	_color = color;
}

void Pen::setWidth(width_t width)
{
	_width = width;
}
