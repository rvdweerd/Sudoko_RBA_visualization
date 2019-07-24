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
#include <chrono>
#include "SpriteCodex.h"


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	tLeft( Vei2(100,100) )
{
	char sudokoStart[9 * 9] =
	{ '.','.','6','5','.','8','4','.','.','5','2','.','.','.','.','.','.','.','.','8','7','.','.','.','.','3','1','.','.','3','.','1','.','.','8','.','9','.','.','8','6','3','.','.','5','.','5','.','.','9','.','6','.','.','1','3','.','.','.','.','2','5','.','.','.','.','.','.','.','.','7','4','.','.','5','2','.','6','3','.','.' };
	field = Field(sudokoStart);
}

void Game::Go()
{
	
	UpdateModel();
	ComposeFrame();
	
}

void Game::UpdateModel()
{
}

void Game::ComposeFrame()
{
	/*using std::chrono::steady_clock;
	
	float durationSeconds = 0;
	std::chrono::steady_clock::time_point start = steady_clock::now();
	while (durationSeconds < 1.0f)
	{
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<float> runtime = end - start;
		durationSeconds = runtime.count();
	}
	*/
	if (field.SolutionExists(gfx))
	{
		//std::cout << "Sudokidoki! First solution found:" << std::endl;
		//field.Print();
	}
	else
	{
		//std::cout << "No solution found" << std::endl;
	}

	
	
	
}
