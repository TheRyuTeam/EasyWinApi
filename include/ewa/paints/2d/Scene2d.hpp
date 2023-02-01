#pragma once
#include <ewa/paints/2d/Drawable.hpp>
#include <ewa/common/Rect.hpp>
#include <cctype>
#include <memory>
#include <vector>

class Figure2d;

class Scene2d: public Drawable
{
public:
	struct SceneFigure
	{
		Figure2d* figure;
		size_t layer;
		bool draw;
	};

	explicit Scene2d(const Rect2d& rect);

	inline Rect2d rect() const noexcept;
	inline void setRect(const Rect2d& rect) noexcept;

	void clear();

	void move(double x, double y) override;

	void addFigure(Figure2d* figure, size_t layer);
	void removeFigure(const Figure2d* figure);

	void draw(Canvas& canvas) const override;

private:
	void sortByLayers();

private:
	Rect2d _rect;
	std::vector<SceneFigure> _figures;
};

inline Rect2d Scene2d::rect() const noexcept
{
	return _rect;
}

inline void Scene2d::setRect(const Rect2d &rect) noexcept
{
	_rect = rect;
}