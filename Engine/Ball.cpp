#include "Ball.h"

Ball::Ball(Vec2& pos_in, Vec2& vel_in)
	:
	pos(pos_in),
	vel(vel_in)
{
}

void Ball::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(float dt)
{ 
	pos += vel * dt;
}

bool Ball::WallColision(const RectF& walls)
{
	
	const RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
		changeX();
		return true;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
		changeX();
		return true;
	}
	if (rect.top < walls.top)
	{
		pos.y += walls.top - rect.top;
		changeY();
		return true;
	}
	else if (rect.bottom > walls.bottom)
	{
		pos.y -= rect.bottom - walls.bottom;
		changeY();
		return true;
	}

	return false;
}

void Ball::changeX()
{
	vel.x = -vel.x;
}

void Ball::changeY()
{ 
	vel.y = -vel.y;
}

Vec2 Ball::GetVel() const
{
	return vel;
}

Vec2 Ball::GetPos() const
{
	return pos;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(pos,radius,radius);
}


