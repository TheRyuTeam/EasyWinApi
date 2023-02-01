#pragma once
#include <ewa/paints/2d/Drawable.hpp>
#include <ewa/common/Pen.hpp>
#include <ewa/common/Brush.hpp>
#include <ewa/common/Point.hpp>
#include <ewa/common/Size.hpp>
#include <ewa/common/Rect.hpp>
#include <ewa/common/Bitmap.hpp>

class Figure2d: public Drawable
{
public:
	Figure2d(const Point2d& pos):
		_pos(pos)
	{
	}

	SIMPLE_GETTER(pen, _pen)
	SIMPLE_SETTER(setPen, Pen, _pen)

	SIMPLE_GETTER(brush, _brush)
	SIMPLE_SETTER(setBrush, Brush, _brush)

	virtual double width() const = 0;
	virtual double height() const = 0;

	Rect2d rect() const noexcept
	{
		return { _pos.x - width() / 2, _pos.y - height() / 2, _pos.x + width() / 2, _pos.y + height() / 2 };
	}

	void move(double x, double y) override { _pos = { _pos.x + x, _pos.y + y }; }
	void draw(Canvas& canvas) const override;

	virtual Point2d pos() const { return _pos; }
	virtual void setPos(const Point2d& pos) { _pos = pos; }

protected:
	virtual void drawImpl(Canvas& canvas) const = 0;

protected:
	Point2d _pos;

private:
	Pen _pen;
	Brush _brush;
};

class Ellipse: public Figure2d
{
public:
	Ellipse(const Point2d& pos, double xRad, double yRad);
	DEFAULT_COPY_CONSTRUCTABLE_ASSIGNABLE(Ellipse);

	double width() const override { return _xRad * 2; }
	double height() const override { return _yRad * 2; }

	SIMPLE_SETTER(setXRad, double, _xRad)
	SIMPLE_GETTER(xRad, _xRad)

	SIMPLE_SETTER(setYRad, double, _yRad)
	SIMPLE_GETTER(yRad, _yRad)

protected:
	void drawImpl(Canvas& canvas) const override;

protected:
	double _xRad;
	double _yRad;
};

class Circle: public Ellipse
{
public:
	Circle(const Point2d& pos, double rad): Ellipse(pos, rad, rad) {}
};

class Rectangle: public Figure2d
{
public:
	Rectangle(const Point2d& pos, double width, double height);

	bool has(double x, double y) const;

	double width() const override { return _width; }
	double height() const override { return _height; }
	void setHeight(double height) { _height = height; }
	void setWidth(double width) { _width = width; }

protected:
	void drawImpl(Canvas& canvas) const override;

private:
	double _width;
	double _height;
};

class Square: public Rectangle
{
public:
	Square(const Point2d& pos, double size);
};

class BMPFigure: public Figure2d
{
public:
	BMPFigure(const Point2d& pos, const Bitmap& bitmap);

	double width() const override;
	double height() const override;

protected:
	void drawImpl(Canvas& canvas) const override;

private:
	Bitmap _bitmap;
};
