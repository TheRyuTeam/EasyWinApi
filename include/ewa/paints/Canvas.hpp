#pragma once
#include <ewa/common/Pen.hpp>
#include <ewa/common/Brush.hpp>
#include <ewa/common/Point.hpp>
#include <ewa/common/Rect.hpp>
#include <ewa/common/Bitmap.hpp>
#include <vector>
#include <string>


class Figure;

class EWA_API Canvas
{
public:
	explicit Canvas(HDC hdc, const Color& bgColor = Color::White, const Pen& pen = {}, const Brush& brush = {});

	virtual ~Canvas();

	void setHdc(HDC hdc);

	virtual void setPixel(const Point2d& point);

	virtual void line(const Point2d& a, const Point2d& b);
	virtual void rect(const Point2d& a, const Point2d& b);
	virtual void rect(const Rect2d& r);
	virtual void circle(const Point2d& a, double radius);
	virtual void ellipse(double left, double top, double right, double bottom);
	virtual void polyline(const std::vector<Point2d>& vertexes);
	virtual void text(const std::string& text, RECT& rect, int flags = 0);
	virtual void bitmap(const Point2d& pos, const Bitmap& bitmap);

	inline Pen pen() const;
	inline Brush brush() const;
	inline Brush bgBrush() const;

	void setPen(const Pen& pen);
	void setBrush(const Brush& brush);
	void setBgBrush(const Brush& brush);

	void clear(const RECT& rect);

private:
	static HPEN _setPen(HDC hdc, const Pen& pen);
	static HBRUSH _setBrush(HDC hdc, const Brush& brush);

private:
	HDC _hdc;

	Brush _bgBrush;
	HBRUSH _bgBrushPtr;

	Pen _pen;
	HPEN _penPtr;

	Brush _brush;
	HBRUSH _brushPtr;
};

/// @section Canvas inlines
inline Pen Canvas::pen() const
{
	return _pen;
}

inline Brush Canvas::brush() const
{
	return _brush;
}

inline Brush Canvas::bgBrush() const
{
	return _bgBrush;
}
