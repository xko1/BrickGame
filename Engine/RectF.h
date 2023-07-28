#pragma once
#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF(float left_in, float right_in, float top_in, float bottom_in);
	RectF(const Vec2& topleft, const Vec2& bottomright);
	RectF(const Vec2& topleft, float width, float height);
	bool IsOverlapping(const RectF& other) const;
	static RectF FromCenter(const Vec2& center, float halfwidth, float halfhieght);
	RectF GetExpanded(float offset) const;
	Vec2 GetCenter() const; 
public:
	float left;
	float right;
	float top;
	float bottom;

};