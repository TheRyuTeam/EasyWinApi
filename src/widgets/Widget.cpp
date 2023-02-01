#include <ewa/widgets/Widget.hpp>
#include <ewa/core/CoreApplication.hpp>
#include <ewa/common/Point.hpp>
#include <ewa/common/Size.hpp>
#include <ewa/common/Rect.hpp>
#include <algorithm>

Widget::Widget(Widget* parent):
		Widget(nullptr, parent)
{
}

Widget::~Widget()
{
	if (_parent)
		_parent->removeChild(this);
}

Rect2d Widget::rect() const
{
	RECT rect;
	GetClientRect(_hWnd, &rect);

	return { (double)rect.left, (double)rect.top, (double)rect.right, (double)rect.bottom };
}

Size2d Widget::size() const
{
	return rect().toSize();
}

Point2d Widget::pos() const
{
	return rect().toPos();
}

Point2d Widget::center() const
{
	return pos();
}

void Widget::show()
{
	ShowWindow(_hWnd, CoreApplication::nCmdShow());
}

void Widget::resize(const SIZE& size)
{
	SetWindowPos(_hWnd, nullptr, 0, 0, size.cx, size.cy, SWP_NOMOVE | SWP_NOZORDER);
}

void Widget::addChild(Widget* child)
{
	if (child && !PP_HAS(_children, child))
		_children.push_back(child);
}

void Widget::removeChild(Widget* child)
{
	const auto unused = std::remove(PP_ALL(_children), child);
}

void Widget::setParent(Widget* parent)
{
	_parent = parent;
	if (_parent)
	{
		_parent->addChild(this);
		SetParent(_hWnd, _parent->_hWnd);
	}
	else
	{
		SetParent(_hWnd, nullptr);
	}
}

void Widget::setEventFilter(EventFilter events)
{
	_eventFilter = events;
}

void Widget::event(Event* e)
{
	if (!_eventFilter.check(e))
		return;

	switch (e->type())
	{
		case Event::Type::Draw:
			drawEvent((DrawEvent*)e);
			break;

		case Event::Type::Close:
			closeEvent((CloseEvent*)e);
			break;

		case Event::Type::Key:
			keyEvent((KeyEvent*)e);
			break;

		case Event::Type::Mouse:
			mouseEvent((MouseEvent*)e);
			break;

		default:
			break;
	}
}

void Widget::drawEvent(DrawEvent* e)
{
	if (!e)
		return;

	for (auto& child : _children)
		child->drawEvent(e);
}

void Widget::closeEvent(CloseEvent* e)
{
}

void Widget::keyEvent(KeyEvent* e)
{
	if (e->pressed())
		keyPressedEvent((KeyPressedEvent*)e);
	else
		keyReleasedEvent((KeyReleasedEvent*)e);

	for (auto& child : _children)
		child->keyEvent(e);
}

void Widget::keyPressedEvent(KeyPressedEvent* e)
{
}

void Widget::keyReleasedEvent(KeyReleasedEvent* e)
{
}

void Widget::mouseEvent(MouseEvent* e)
{
	switch (e->mouseEventType())
	{
		case MouseEvent::MouseEventType::Pressed:
			mousePressedEvent((MousePressedEvent*)e);
			break;

		case MouseEvent::MouseEventType::Released:
			mouseReleasedEvent((MouseReleasedEvent*)e);
			break;

		case MouseEvent::MouseEventType::DbClick:
			mouseDbClickEvent((MouseDbClickEvent*)e);
			break;

		case MouseEvent::MouseEventType::Move:
			mouseMoveEvent((MouseMoveEvent*)e);
			break;

		case MouseEvent::MouseEventType::Hover:
			mouseHoverEvent((MouseHoverEvent*)e);
			break;

		default:
			break;
	}

	for (auto& child : _children)
		child->mouseEvent(e);
}

void Widget::mousePressedEvent(MousePressedEvent* e)
{
}

void Widget::mouseReleasedEvent(MouseReleasedEvent* e)
{
}

void Widget::mouseDbClickEvent(MouseDbClickEvent* e)
{
}

void Widget::mouseMoveEvent(MouseMoveEvent* e)
{
}

void Widget::mouseHoverEvent(MouseHoverEvent* e)
{
}

Widget::Widget(HWND hWnd, Widget* parent):
		_hWnd(hWnd),
		_parent(nullptr),
		_children(),
		_eventFilter()
{
	setParent(parent);
}


