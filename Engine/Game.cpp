/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Brick.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(Vec2(300.0f, 300.0f), Vec2(100.0f, 100.0f)),
	walls(0.0f, float(gfx.ScreenWidth), 0.0f, float(gfx.ScreenHeight)),
	pad(Vec2(400.0f, 500.0f), 75.0f, 15.0f, Colors::White),
	soundPad(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav")
{
	const Color colors[4] = {Colors::Blue,Colors::Red,Colors::Green,Colors::Cyan};
	const Vec2 topleft(40.0f, 40.0f);
	int i = 0;
	for (int y = 0; y < nBricksDown; y++)
	{
		const Color c = colors[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			brick[i] = Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),brickWidth,brickHeight), c);
			i++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	
	ball.Update(dt);
	pad.Update(wnd.kbd, dt);
	pad.DoWallColishion(walls);
	bool colisionHappened = false;
	float curColDist;
	int curColIndex;
	for (int i = 0; i < nBricks; i++)
	{
		if (brick[i].DoBallCollision(ball))
		{
			const float newColDis = (ball.GetPos() - brick[i].GetCenter()).GetLengthSq();
			if (colisionHappened)
			{
				if (newColDis < curColDist)
				{
					curColDist = newColDis;
					curColIndex = i;
				}
			}
			else
			{
				curColDist = newColDis;
				curColIndex = i;
				colisionHappened = true;
			}
			//soundBrick.Play();
			
		}
	}
	if (colisionHappened)
	{
		pad.ResetCooldown();
		brick[curColIndex].ExecuteBallCollision(ball);
	}
	if (ball.WallColision(walls))
	{
		
	}
	if (pad.DoBallCollishion(ball))
	{
		pad.ResetCooldown();
		//soundPad.Play();
	}
}

void Game::ComposeFrame()
{
	ball.Draw(gfx);	
	for (const Brick& b : brick)
	{
		b.Draw(gfx);
	}
	pad.Draw(gfx);
}
