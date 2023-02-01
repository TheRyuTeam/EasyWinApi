#include <ewa/paints/2d/Figure2d.hpp>
#include <ewa/paints/Canvas.hpp>
#include <ewa/core/CoreApplication.hpp>

void Figure2d::draw(Canvas &canvas) const
{
	const auto pen = canvas.pen();
	const auto brush = canvas.brush();

	canvas.setPen(_pen);
	canvas.setBrush(_brush);

	drawImpl(canvas);

	canvas.setBrush(brush);
	canvas.setPen(pen);
}

Ellipse::Ellipse(const Point2d &pos, double xRad, double yRad):
	Figure2d(pos),
	_xRad(xRad),
	_yRad(yRad)
{
}

void Ellipse::drawImpl(Canvas &canvas) const
{
	canvas.ellipse(_pos.x - _xRad, _pos.y - _yRad, _pos.x + _xRad, _pos.y + _yRad);
}

Rectangle::Rectangle(const Point2d& pos, double width, double height):
	Figure2d(pos),
	_width(width),
	_height(height)
{
}

void Rectangle::drawImpl(Canvas &canvas) const
{
	canvas.rect({ _pos.x - _width / 2, _pos.y - _height / 2 },
				{ _pos.x + _width / 2, _pos.y + _height / 2 });
}

bool Rectangle::has(double x, double y) const
{
	return std::abs(_pos.x - x) <= _width / 2 && std::abs(_pos.y - y) <=  _height / 2;
}

Square::Square(const Point2d& pos, double size):
	Rectangle(pos, size, size)
{
}

BMPFigure::BMPFigure(const Point2d& pos, const Bitmap& bitmap):
	Figure2d(pos),
	_bitmap(bitmap)
{
}


double BMPFigure::width() const
{
	return _bitmap.bitmap.bmWidth;
}

double BMPFigure::height() const
{
	return _bitmap.bitmap.bmHeight;
}

void BMPFigure::drawImpl(Canvas &canvas) const
{
	canvas.bitmap(_pos, _bitmap);
}


