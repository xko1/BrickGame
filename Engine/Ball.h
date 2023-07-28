#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "SpriteCodex.h"

class Ball
{
public:
	Ball(Vec2& pos_in, Vec2& vel_in);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	bool WallColision(const RectF& walls);
	void changeX();
	void changeY();
	RectF GetRect() const;
	Vec2 GetVel() const;
	Vec2 GetPos() const;

private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
};