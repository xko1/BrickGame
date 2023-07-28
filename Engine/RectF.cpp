#include "RectF.h"

RectF::RectF(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
	{
	}

RectF::RectF(const Vec2& topleft, const Vec2& bottomright)
	:
	RectF(topleft.x, bottomright.x, topleft.y, bottomright.y)
{
}

RectF::RectF(const Vec2& topleft, float width, float height)
	:
	RectF(topleft,topleft + Vec2(width,height))
{
}

bool RectF::IsOverlapping(const RectF& other) const
{
	
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

RectF RectF::FromCenter(const Vec2& center, float halfwidth, float halfhieght)
{
	const Vec2 half(halfwidth, halfhieght);
	return RectF(center - half , center + half);
}

RectF RectF::GetExpanded(float offset) const
{
	return RectF(left - offset, right + offset, top - offset, bottom + offset);
}

Vec2 RectF::GetCenter() const
{
	return Vec2((left + right)/ 2.0f, (top + bottom)/2.0f);
}


