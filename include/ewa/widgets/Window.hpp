#pragma once
#include <ewa/widgets/Widget.hpp>
#include <Windows.h>
#include <string>

class Window: public Widget
{
public:
	Window(const SIZE& size, const std::string& title, Window* parent = nullptr);

	~Window() override;

private:

	friend class CoreApplication;
};

