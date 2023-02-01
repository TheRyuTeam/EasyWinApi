#include <ewa/paints/Canvas.hpp>
#include <cmath>

Canvas::Canvas(HDC hdc, const Color& bgColor, const Pen& pen, const Brush& brush):
	_hdc(hdc),
	_bgBrush(bgColor),
	_bgBrushPtr(detail::createHBRUSH(_bgBrush)),
	_pen(pen),
	_penPtr(_setPen(_hdc, _pen)),
	_brush(brush),
	_brushPtr(_setBrush(_hdc, _brush))
{
}

Canvas::~Canvas()
{
	DeleteObject(_penPtr);
	DeleteObject(_brushPtr);
}

void Canvas::setHdc(HDC hdc)
{
	_hdc = hdc;
}

void Canvas::setPixel(const Point2d& point)
{
	if (_pen.style() != Pen::Style::Null)
	{
		SetPixel(_hdc, dtoi(point.y), dtoi(point.y), _pen.color().value());
	}
}

void Canvas::line(const Point2d& a, const Point2d& b)
{
	MoveToEx(_hdc, dtoi(a.x), dtoi(a.y), nullptr);
	LineTo(_hdc, dtoi(b.x), dtoi(b.y));
}

void Canvas::rect(const Point2d& a, const Point2d& b)
{
	Rectangle(_hdc, dtoi(a.x), dtoi(a.y), dtoi(b.x), dtoi(b.y));
}

void Canvas::rect(const Rect2d& r)
{
	rect({ r.left, r.top }, { r.right, r.bottom });
}
void Canvas::circle(const Point2d& a, double radius)
{
	ellipse(a.x - radius, a.y - radius, a.x + radius, a.y + radius);
}

void Canvas::ellipse(double left, double top, double right, double bottom)
{
	Ellipse(_hdc, dtoi(left), dtoi(top), dtoi(right), dtoi(bottom));
}

void Canvas::polyline(const std::vector<Point2d>& vertexes)
{
	std::vector<POINT> vtx;
	vtx.reserve(vertexes.size());

	for (const auto& vertex : vertexes)
		vtx.push_back({ dtoi(vertex.x), dtoi(vertex.y) });

	Polygon(_hdc, vtx.data(), static_cast<int>(vtx.size()));
}

void Canvas::text(const std::string& text, RECT& rect, int flags)
{
	DrawText(_hdc, text.c_str(), static_cast<int>(text.size()), &rect, flags);
}

void Canvas::bitmap(const Point2d& pos, const Bitmap& bitmap)
{
	auto hdcMem = CreateCompatibleDC(_hdc);
	auto oldBitmap = SelectObject(hdcMem, bitmap.hBitmap);

	BitBlt(_hdc, pos.x - bitmap.width() / 2, pos.y - bitmap.height() / 2, bitmap.width(), bitmap.height(),
		   hdcMem,
		   0, 0, SRCCOPY);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);
}

void Canvas::setPen(const Pen& pen)
{
	if (_pen != pen)
	{
		_pen = pen;
		DeleteObject(_penPtr);

		_penPtr = _setPen(_hdc, _pen);
	}
}

void Canvas::setBrush(const Brush& brush)
{
	if (_brush != brush)
	{
		_brush = brush;
		DeleteObject(_brushPtr);

		_brushPtr = _setBrush(_hdc, _brush);
	}
}

void Canvas::setBgBrush(const Brush& brush)
{
	if (_bgBrush != brush)
	{
		_bgBrush = brush;
		DeleteObject(_bgBrushPtr);

		_brushPtr = _setBrush(_hdc, _brush);
	}
}

void Canvas::clear(const RECT& rect)
{
	FillRect(_hdc, &rect, _bgBrushPtr);
}

HPEN Canvas::_setPen(HDC hdc, const Pen& pen)
{
	HPEN hPen = detail::createHPEN(pen);

	SelectObject(hdc, hPen);

	return hPen;
}

HBRUSH Canvas::_setBrush(HDC hdc, const Brush& brush)
{
	HBRUSH hBrush = detail::createHBRUSH(brush);

	SelectObject(hdc, hBrush);

	return hBrush;
}