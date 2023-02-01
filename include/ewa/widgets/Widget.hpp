#pragma once
#include <ewa/core/EventFilter.hpp>
#include <vector>
#include <Windows.h>

class EventFilter;
class Point2d;
class Size2d;
class Rect2d;

class Widget
{
public:
	explicit Widget(Widget* parent);

	virtual ~Widget();

	inline Widget* parent() const noexcept;
	void setParent(Widget* parent);

	Rect2d rect() const;
	Size2d size() const;
	Point2d pos() const;

	Point2d center() const;
	
	virtual void show();
	virtual void resize(const SIZE& size);
	virtual void addChild(Widget* child);
	virtual void removeChild(Widget* child);
	virtual void setEventFilter(EventFilter events);
	virtual void event(Event* e);
	virtual void drawEvent(DrawEvent* e);
	virtual void closeEvent(CloseEvent* e);
	virtual void keyEvent(KeyEvent* e);
	virtual void keyPressedEvent(KeyPressedEvent* e);
	virtual void keyReleasedEvent(KeyReleasedEvent* e);

	virtual void mouseEvent(MouseEvent* e);
	virtual void mousePressedEvent(MousePressedEvent* e);
	virtual void mouseReleasedEvent(MouseReleasedEvent* e);
	virtual void mouseDbClickEvent(MouseDbClickEvent* e);
	virtual void mouseMoveEvent(MouseMoveEvent* e);
	virtual void mouseHoverEvent(MouseHoverEvent* e);

	inline HWND handle() const noexcept;

protected:
	explicit Widget(HWND hWnd, Widget* parent = nullptr);

private:
	HWND _hWnd;
	Widget* _parent;
	std::vector<Widget*> _children;
	EventFilter _eventFilter;
};

inline HWND Widget::handle() const noexcept
{
	return _hWnd;
}

inline Widget* Widget::parent() const noexcept
{
	return _parent;
}
