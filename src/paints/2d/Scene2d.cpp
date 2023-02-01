#include <ewa/paints/2d/Scene2d.hpp>
#include <ewa/paints/2d/Figure2d.hpp>
#include <algorithm>

Scene2d::Scene2d(const Rect2d &rect):
	_rect(rect),
	_figures()
{
}

void Scene2d::addFigure(Figure2d* figure, size_t layer)
{
	if (!figure)
		return;

	auto it = std::find_if(_figures.begin(), _figures.end(), [&](const SceneFigure& el)
	{
		return figure == el.figure;
	});

	if (it != _figures.end())
	{
		it->layer = layer;
		sortByLayers();
		return;
	}

	_figures.push_back(SceneFigure{ figure, layer, _rect.intersect(figure->rect()) });
	sortByLayers();
}

void Scene2d::removeFigure(const Figure2d* figure)
{
	auto it = std::find_if(_figures.begin(), _figures.end(), [&](const SceneFigure& el)
	{
		return figure == el.figure;
	});

	if (it != _figures.end())
	{
		_figures.erase(it);
		sortByLayers();
	}
}

void Scene2d::draw(Canvas &canvas) const
{
	for (auto& sceneFigure : _figures)
	{
		if (sceneFigure.draw)
			sceneFigure.figure->draw(canvas);
	}
}

void Scene2d::move(double x, double y)
{
	for (auto& sceneFigure : _figures)
	{
		sceneFigure.figure->move(x, y);
		sceneFigure.draw = _rect.intersect(sceneFigure.figure->rect());
	}
}

void Scene2d::clear()
{
	_figures.clear();
}

void Scene2d::sortByLayers()
{
	std::sort(_figures.begin(), _figures.end(), [](const SceneFigure& a, const SceneFigure& b){
		return a.layer > b.layer;
	});
}
