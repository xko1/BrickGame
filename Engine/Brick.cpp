#include "Brick.h"
#include <assert.h>

Brick::Brick(const RectF& rect_in, Color c_in)
	:
	rect(rect_in),
	c(c_in)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect(rect.GetExpanded(-padding), c);
	}
}

bool Brick::DoBallCollision(Ball& ball) const
{
	return !destroyed && rect.IsOverlapping(ball.GetRect());
}

void Brick::ExecuteBallCollision(Ball& ball) 
{
	
	assert(DoBallCollision(ball));
	const Vec2 ballPos = ball.GetPos();
	if (std::signbit(ball.GetVel().x) == std::signbit((ballPos - GetCenter()).x))
	{
		ball.changeY();
	}
	else if (ballPos.x >= rect.left && ballPos.x <= rect.right)
	{
		ball.changeY();
	}
	else
	{
		ball.changeX();
	}
	destroyed = true;
		
	
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}
