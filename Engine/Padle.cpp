#include "Padle.h"

Padle::Padle(Vec2& pos_in, float halfwidth_in, float halfheight_in, Color c_in)
{
	pos = pos_in;
	halfwidth = halfwidth_in;
	halfheight = halfheight_in;
	c = c_in;
}

void Padle::Draw(Graphics& gfx) const
{
	RectF rect = GetRect();
	gfx.DrawRect(rect, wing);
	rect.left += wingwidth;
	rect.right -= wingwidth;
	gfx.DrawRect(rect, c);
}

bool Padle::DoBallCollishion(Ball& ball) 
{
	if (!Cooldown)
	{
		const RectF rect = GetRect();
		if (rect.IsOverlapping(ball.GetRect()))
		{
			const Vec2 ballPos = ball.GetPos();
			if (std::signbit(ball.GetVel().x) == std::signbit((ballPos - pos).x))
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
			Cooldown = true;
			return true;

		}
	}
	
	return false;
}

bool Padle::DoWallColishion(const RectF& walls)
{
	const RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
		return true;
	}
	if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
		return true;
	}
	return false;
}

void Padle::Update(const Keyboard& kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt;
	}
}

RectF Padle::GetRect() const
{
	return RectF::FromCenter(pos, halfwidth, halfheight);
}

void Padle::ResetCooldown()
{
	Cooldown = false;
}
