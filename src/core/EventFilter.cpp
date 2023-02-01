#include "ewa/core/EventFilter.hpp"

EventFilter::EventFilter():
		_filter(static_cast<Event::Type>(31))
{
}

EventFilter::EventFilter(Event::Type type):
		_filter(type)
{
}

void EventFilter::attend(Event::Type type)
{
	_filter = static_cast<Event::Type>(_filter | type);
}

void EventFilter::ignore(Event::Type type)
{
	_filter = static_cast<Event::Type>(_filter & ~type);
}

void EventFilter::setEventFilter(Event::Type filter)
{
	_filter = filter;
}

bool EventFilter::check(Event* e) const
{
	return e && (int)(e->type() & _filter);
}
