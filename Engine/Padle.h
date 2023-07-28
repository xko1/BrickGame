#pragma once
#include "Ball.h"
#include "Vec2.h"
#include "Colors.h"
#include "RectF.h"
#include "Keyboard.h"
#include "Graphics.h"
#include <cmath>


class Padle
{
public:
	Padle(Vec2& pos_in, float halfwidth_in, float halfheight_in, Color c);
	void Draw(Graphics& gfx) const;
	bool DoBallCollishion(Ball& ball);
	bool DoWallColishion(const RectF& walls);
	void Update(const Keyboard& kbd, float dt);
	RectF GetRect() const;
	void ResetCooldown();
private:
	static constexpr float wingwidth = 10.0f;
	Color wing = Colors::Red;
	Color c;
	float halfwidth;
	float halfheight;
	float speed = 300.0f;
	Vec2 pos;
	bool Cooldown = true;
	
};