#pragma once
#include <ewa/core/Event.hpp>

class EWA_API EventFilter
{
public:
	EventFilter();
	explicit EventFilter(Event::Type type);

	EventFilter(const EventFilter&) = default;
	EventFilter(EventFilter&&) noexcept = default;

	EventFilter& operator=(const EventFilter&) = default;
	EventFilter& operator=(EventFilter&&) noexcept = default;

	void attend(Event::Type type);
	void ignore(Event::Type type);
	void setEventFilter(Event::Type filter);

	bool check(Event* e) const;

private:
	Event::Type _filter;
};