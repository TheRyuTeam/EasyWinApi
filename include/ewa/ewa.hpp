#pragma once
#ifdef EWA_STATIC
	#define EWA_API
#else
	#ifdef EWA_EXPORTS
		#define EWA_API __declspec(dllexport)
	#else
		#define EWA_API __declspec(dllimport)
	#endif
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#define PP_ALL(x) (x).begin(), (x).end()
#define PP_FIND(x, y) (std::find(PP_ALL(x), y))
#define PP_HAS(x, y) (PP_FIND((x), (y)) != (x).end())

#define DEFAULT_COPY_CONSTRUCTABLE(Class) \
Class(const Class&) = default;\
Class(Class&&) noexcept = default\

#define DEFAULT_COPY_ASSIGNABLE(Class)\
Class& operator=(const Class&) = default;\
Class& operator=(Class&&) noexcept = default\

#define DEFAULT_COPY_CONSTRUCTABLE_ASSIGNABLE(Class)\
DEFAULT_COPY_CONSTRUCTABLE(Class);\
DEFAULT_COPY_ASSIGNABLE(Class)

#define SIMPLE_GETTER(Name, Member)\
auto Name() const { return Member; }

#define SIMPLE_SETTER(Name, Type, Member)\
void Name(const Type& newValue) { Member = newValue; }

#define SIMPLE_SETTER_GETTER(Getter, Setter, Type, Member)\
SIMPLE_GETTER(Getter, Member)\
SIMPLE_SETTER(Setter, Type, Member)

using byte_t = unsigned char;

#include <cmath>

inline int dtoi(double val)
{
	return static_cast<int>(std::round(val));
}
