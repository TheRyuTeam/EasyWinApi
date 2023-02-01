#include "Button.hpp"
#include <ewa/paints/Canvas.hpp>

Button::Button(const std::string& text, const Point2d& pos, double width, double height):
		Rectangle(pos, width, height),
		_text(text)
{
}

void Button::drawImpl(Canvas& canvas) const
{
	RECT r = rect();
	Rectangle::drawImpl(canvas);
	canvas.text(_text, r, DT_CENTER | DT_NOCLIP | DT_SINGLELINE | DT_VCENTER);
}