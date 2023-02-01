#pragma once
#include <ewa/ewa.hpp>
#include <Windows.h>

class EWA_API Color
{
public:
	enum Rgb
	{
		IndianRed = RGB(205, 92, 92),
		LightCoral = RGB(240, 128, 128),
		Salmon = RGB(250, 128, 114),
		DarkSalmon = RGB(233, 150, 122),
		LightSalmon = RGB(255, 160, 122),
		Crimson = RGB(220, 20, 60),
		Red = RGB(255, 0, 0),
		FireBrick = RGB(178, 34, 34),
		DarkRed = RGB(139, 0, 0),
		Pink = RGB(255, 192, 203),
		LightPink = RGB(255, 182, 193),
		HotPink = RGB(255, 105, 180),
		DeepPink = RGB(255, 20, 147),
		MediumVioletRed = RGB(199, 21, 133),
		PaleVioletRed = RGB(219, 112, 147),
		Coral = RGB(255, 127, 80),
		Tomato = RGB(255, 99, 71),
		OrangeRed = RGB(255, 69, 0),
		DarkOrange = RGB(255, 140, 0),
		Orange = RGB(255, 165, 0),
		Gold = RGB(255, 215, 0),
		Yellow = RGB(255, 255, 0),
		LightYellow = RGB(255, 255, 224),
		LemonChiffon = RGB(255, 250, 205),
		LightGoldenrodYellow = RGB(250, 250, 210),
		PapayaWhip = RGB(255, 239, 213),
		Moccasin = RGB(255, 228, 181),
		PeachPuff = RGB(255, 218, 185),
		PaleGoldenrod = RGB(238, 232, 170),
		Khaki = RGB(240, 230, 140),
		DarkKhaki = RGB(189, 183, 107),
		Lavender = RGB(230, 230, 250),
		Thistle = RGB(216, 191, 216),
		Plum = RGB(221, 160, 221),
		Violet = RGB(238, 130, 238),
		Orchid = RGB(218, 112, 214),
		Fuchsia = RGB(255, 0, 255),
		Magenta = RGB(255, 0, 255),
		MediumOrchid = RGB(186, 85, 211),
		MediumPurple = RGB(147, 112, 219),
		RebeccaPurple = RGB(102, 51, 153),
		BlueViolet = RGB(138, 43, 226),
		DarkViolet = RGB(148, 0, 211),
		DarkOrchid = RGB(153, 50, 204),
		DarkMagenta = RGB(139, 0, 139),
		Purple = RGB(128, 0, 128),
		Indigo = RGB(75, 0, 130),
		SlateBlue = RGB(106, 90, 205),
		DarkSlateBlue = RGB(72, 61, 139),
		MediumSlateBlue = RGB(123, 104, 238),
		GreenYellow = RGB(173, 255, 47),
		Chartreuse = RGB(127, 255, 0),
		LawnGreen = RGB(124, 252, 0),
		Lime = RGB(0, 255, 0),
		LimeGreen = RGB(50, 205, 50),
		PaleGreen = RGB(152, 251, 152),
		LightGreen = RGB(144, 238, 144),
		MediumSpringGreen = RGB(0, 250, 154),
		SpringGreen = RGB(0, 255, 127),
		MediumSeaGreen = RGB(60, 179, 113),
		SeaGreen = RGB(46, 139, 87),
		ForestGreen = RGB(34, 139, 34),
		Green = RGB(0, 128, 0),
		DarkGreen = RGB(0, 100, 0),
		YellowGreen = RGB(154, 205, 50),
		OliveDrab = RGB(107, 142, 35),
		Olive = RGB(128, 128, 0),
		DarkOliveGreen = RGB(85, 107, 47),
		MediumAquamarine = RGB(102, 205, 170),
		DarkSeaGreen = RGB(143, 188, 139),
		LightSeaGreen = RGB(32, 178, 170),
		DarkCyan = RGB(0, 139, 139),
		Teal = RGB(0, 128, 128),
		Aqua = RGB(0, 255, 255),
		Cyan = RGB(0, 255, 255),
		LightCyan = RGB(224, 255, 255),
		PaleTurquoise = RGB(175, 238, 238),
		Aquamarine = RGB(127, 255, 212),
		Turquoise = RGB(64, 224, 208),
		MediumTurquoise = RGB(72, 209, 204),
		DarkTurquoise = RGB(0, 206, 209),
		CadetBlue = RGB(95, 158, 160),
		SteelBlue = RGB(70, 130, 180),
		LightSteelBlue = RGB(176, 196, 222),
		PowderBlue = RGB(176, 224, 230),
		LightBlue = RGB(173, 216, 230),
		SkyBlue = RGB(135, 206, 235),
		LightSkyBlue = RGB(135, 206, 250),
		DeepSkyBlue = RGB(0, 191, 255),
		DodgerBlue = RGB(30, 144, 255),
		CornflowerBlue = RGB(100, 149, 237),
		RoyalBlue = RGB(65, 105, 225),
		Blue = RGB(0, 0, 255),
		MediumBlue = RGB(0, 0, 205),
		DarkBlue = RGB(0, 0, 139),
		Navy = RGB(0, 0, 128),
		MidnightBlue = RGB(25, 25, 112),
		Cornsilk = RGB(255, 248, 220),
		BlanchedAlmond = RGB(255, 235, 205),
		Bisque = RGB(255, 228, 196),
		NavajoWhite = RGB(255, 222, 173),
		Wheat = RGB(245, 222, 179),
		BurlyWood = RGB(222, 184, 135),
		Tan = RGB(210, 180, 140),
		RosyBrown = RGB(188, 143, 143),
		SandyBrown = RGB(244, 164, 96),
		Goldenrod = RGB(218, 165, 32),
		DarkGoldenrod = RGB(184, 134, 11),
		Peru = RGB(205, 133, 63),
		Chocolate = RGB(210, 105, 30),
		SaddleBrown = RGB(139, 69, 19),
		Sienna = RGB(160, 82, 45),
		Brown = RGB(165, 42, 42),
		Maroon = RGB(128, 0, 0),
		White = RGB(255, 255, 255),
		Snow = RGB(255, 250, 250),
		HoneyDew = RGB(240, 255, 240),
		MintCream = RGB(245, 255, 250),
		Azure = RGB(240, 255, 255),
		AliceBlue = RGB(240, 248, 255),
		GhostWhite = RGB(248, 248, 255),
		WhiteSmoke = RGB(245, 245, 245),
		SeaShell = RGB(255, 245, 238),
		Beige = RGB(245, 245, 220),
		OldLace = RGB(253, 245, 230),
		FloralWhite = RGB(255, 250, 240),
		Ivory = RGB(255, 255, 240),
		AntiqueWhite = RGB(250, 235, 215),
		Linen = RGB(250, 240, 230),
		LavenderBlush = RGB(255, 240, 245),
		MistyRose = RGB(255, 228, 225),
		Gainsboro = RGB(220, 220, 220),
		LightGray = RGB(211, 211, 211),
		Silver = RGB(192, 192, 192),
		DarkGray = RGB(169, 169, 169),
		Gray = RGB(128, 128, 128),
		DimGray = RGB(105, 105, 105),
		LightSlateGray = RGB(119, 136, 153),
		SlateGray = RGB(112, 128, 144),
		DarkSlateGray = RGB(47, 79, 79),
		Black = RGB(0, 0, 0)
	};

	Color(COLORREF color = Rgb::Black);
	explicit Color(int r, int g, int b);

	Color(const Color&) = default;
	Color(Color&&) noexcept = default;

	Color& operator=(const Color&) = default;
	Color& operator=(Color&&) noexcept = default;

	inline COLORREF value() const noexcept;

private:
	COLORREF _rgb;
};

/// @section Color inlines
inline Color::Color(COLORREF color):
	_rgb(color)
{
}

inline Color::Color(int r, int g, int b):
	_rgb(RGB(r, g, b))
{
}

inline COLORREF Color::value() const noexcept
{
	return _rgb;
}

/// @section Color comparison
inline bool operator==(const Color& lhs, const Color& rhs)
{
	return lhs.value() == rhs.value();
}

inline bool operator!=(const Color& lhs, const Color& rhs)
{
	return lhs.value() != rhs.value();
}

inline bool operator>(const Color& lhs, const Color& rhs)
{
	return lhs.value() > rhs.value();
}

inline bool operator>=(const Color& lhs, const Color& rhs)
{
	return lhs.value() >= rhs.value();
}

inline bool operator<(const Color& lhs, const Color& rhs)
{
	return lhs.value() < rhs.value();
}

inline bool operator<=(const Color& lhs, const Color& rhs)
{
	return lhs.value() <= rhs.value();
}