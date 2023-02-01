#pragma once

class Canvas;

class Drawable
{
public:
	virtual ~Drawable() = default;

	virtual void draw(Canvas& canvas) const = 0;
	virtual void move(double x, double y) = 0;
};