#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Arrow.h"
#include "Stratagem.h"
#include "Constants.h"
#include "StratagemConfigParser.h"

const int initialPosY = 260;
const int posYLimit = 40;
const float lerpBy = 0.2f;
bool pressed = false;
bool endingAnimation = false;

int main(void)
{
	// TODO (maybe): Option to have all arrows that point to the same direction with the same color

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Stratagem Citizen");

	StratagemConfigParser stratagemConfigParser("StratagemConfig.txt");

	stratagemConfigParser.ParseStratagems();
	int index = 0;
	std::vector<Stratagem> stratagems = stratagemConfigParser.GetStratagems();

	while (!WindowShouldClose())
	{
		SetTargetFPS(60);
		DrawFPS(0, 0);
		BeginDrawing();
		ClearBackground(BLACK);

#ifdef _DEBUG
		// NOTES(Ruan): a VERY simple way to debug if things are, in fact, in the middle of the screen
		DrawLine(WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT, GREEN);
		DrawLine(0, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT / 2, GREEN);
#endif

		stratagems[index].Input();
		stratagems[index].Update();
		stratagems[index].Draw();

		if (stratagems[index].GetFinished())
		{
			index++;
		}

		if (index == stratagems.size())
			break;
		
		EndDrawing();
	}

	for (auto& stratagem : stratagems)
	{
		stratagem.UnloadResources();
	}

	return 0;
}