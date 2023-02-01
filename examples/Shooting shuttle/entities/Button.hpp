#pragma once
#include <ewa/paints/2d/Figure2d.hpp>

class Button: public Rectangle
{
public:
	Button(const std::string& text, const Point2d& pos, double width, double height);

protected:
	void drawImpl(Canvas& canvas) const override;

private:
	std::string _text;
};