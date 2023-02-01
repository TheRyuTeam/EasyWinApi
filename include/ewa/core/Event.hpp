#pragma once
#include <ewa/ewa.hpp>
#include <type_traits>


class EWA_API Event
{
public:
	enum Type
	{
		Create = 1,
		Draw = 2,
		Close = 4,
		Key = 8,
		Mouse = 16
	};

	virtual ~Event() = default;

	virtual Type type() = 0;
};

class EWA_API DrawEvent: public Event
{
public:
	Type type() override { return Type::Draw; }
};

class EWA_API CloseEvent : public Event
{
public:
	Type type() override { return Type::Close; }
};

class EWA_API KeyEvent : public Event
{
public:
	enum class PressType
	{
		Pressed,
		Released
	};

	explicit KeyEvent(int key, PressType pressType):
			_key(key),
			_pressType(pressType)
	{
	}

	int key() const { return _key; }
	bool pressed() const { return _pressType == PressType::Pressed;  }
	PressType pressType() const { return _pressType; }
	Type type() override { return Type::Key; }

private:
	const int _key;
	const PressType _pressType;
};

class EWA_API KeyPressedEvent : public KeyEvent
{
public:
	explicit KeyPressedEvent(int key) :
			KeyEvent(key, PressType::Pressed)
	{
	}
};

class EWA_API KeyReleasedEvent : public KeyEvent
{
public:
	explicit KeyReleasedEvent(int key) :
			KeyEvent(key, PressType::Released)
	{
	}

};

class EWA_API MouseEvent: public Event
{
public:
	enum class MouseEventType
	{
		Pressed,
		Released,
		DbClick,
		Move,
		Hover
	};

	explicit MouseEvent(MouseEventType met, int x, int y, unsigned long long keys) :
			_met(met),
			_x(x),
			_y(y),
			_keys(keys)
	{
	}

	MouseEventType mouseEventType() const noexcept { return _met; }
	int x() const noexcept { return _x; }
	int y() const noexcept { return _y; }

	unsigned long long keys() const noexcept { return _keys; }
	Type type() override { return Type::Mouse; }

	bool pressed() const noexcept { return _met == MouseEventType::Pressed; }
	bool released() const noexcept { return _met == MouseEventType::Released; }
	bool dbClicked() const noexcept { return _met == MouseEventType::DbClick; }
	bool moved() const noexcept { return _met == MouseEventType::Move; }
	bool hovered() const noexcept { return _met == MouseEventType::Hover; }

private:
	const MouseEventType _met;
	const int _x;
	const int _y;
	const unsigned long long _keys;
};

class EWA_API MouseClickEvent : public MouseEvent
{
public:
	enum class Button: int
	{
		Left,
		Right
	};

	explicit MouseClickEvent(Button btn, MouseEventType met, int x, int y, unsigned long long keys) :
		MouseEvent(met, x, y, keys),
		_btn(btn)
	{
	}

	Button button() const noexcept { return _btn; }
	Type type() override { return Type::Mouse; }

	bool leftButtonPressed() const noexcept { return button() == Button::Left && pressed(); }
	bool leftButtonReleased() const noexcept { return button() == Button::Left && released(); }
	bool leftButtonDBClicked() const noexcept { return button() == Button::Left && dbClicked(); }

	bool rightButtonPressed() const noexcept { return button() == Button::Right && pressed(); }
	bool rightButtonReleased() const noexcept { return button() == Button::Right && released(); }
	bool rightButtonDBClicked() const noexcept { return button() == Button::Right && dbClicked(); }

private:
	const Button _btn;
};

class EWA_API MousePressedEvent : public MouseClickEvent
{
public:
	explicit MousePressedEvent(Button btn, int x, int y, unsigned long long keys) :
		MouseClickEvent(btn, MouseEventType::Pressed, x, y, keys)
	{
	}
};

class EWA_API MouseReleasedEvent : public MouseClickEvent
{
public:
	explicit MouseReleasedEvent(Button btn, int x, int y, unsigned long long keys) :
		MouseClickEvent(btn, MouseEventType::Released, x, y, keys)
	{
	}
};

class EWA_API MouseDbClickEvent : public MouseClickEvent
{
public:
	explicit MouseDbClickEvent(Button btn, int x, int y, unsigned long long keys) :
		MouseClickEvent(btn, MouseEventType::DbClick, x, y, keys)
	{
	}
};

class EWA_API MouseMoveEvent : public MouseEvent
{
public:
	explicit MouseMoveEvent(int x, int y, unsigned long long keys) :
		MouseEvent(MouseEventType::Move, x, y, keys)
	{
	}
};

class EWA_API MouseHoverEvent : public MouseEvent
{
public:
	explicit MouseHoverEvent(int x, int y, unsigned long long keys) :
		MouseEvent(MouseEventType::Hover, x, y, keys)
	{
	}
};