#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Arrow.h"
#include "Stratagem.h"
#include "Constants.h"

const int initialPosY = 260;
const int posYLimit = 40;
const float lerpBy = 0.2f;
bool pressed = false;
bool endingAnimation = false;

int main(void)
{
	// TODO (maybe): Option to have all arrows that point to the same direction with the same color

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Stratagem Citizen");

	float halfOfArrowImageWidth = static_cast<float>(ARROW_IMAGE_WIDTH) / 2;
	float arrowImageOffset = ARROW_IMAGE_WIDTH + halfOfArrowImageWidth;
	float initialPosX = (static_cast<float>(WINDOW_WIDTH) / 2) - halfOfArrowImageWidth;
	float initialPosY = DEFAULT_ARROW_HEIGHT - halfOfArrowImageWidth;

	Vector2 stratagemPos{ 100, 60 };
	
	Arrow arrow = Arrow("Assets/Arrow Up.png", KEY_UP);
	Arrow arrow2 = Arrow("Assets/Arrow Right.png", KEY_RIGHT);
	Arrow arrow3 = Arrow("Assets/Arrow Down.png", KEY_DOWN);
	Arrow arrow4 = Arrow("Assets/Arrow Down.png", KEY_DOWN);
	Arrow arrow5 = Arrow("Assets/Arrow Down.png", KEY_DOWN);

	std::vector<Arrow> arrows;
	arrows.reserve(5);
	arrows.emplace_back(arrow);
	arrows.emplace_back(arrow2);
	arrows.emplace_back(arrow3);
	arrows.emplace_back(arrow4);
	arrows.emplace_back(arrow5);

	Stratagem eagleStratagem = Stratagem("Assets/eagle500.png", stratagemPos, arrows, "Eagle 500 KG Bomb");

	float posY = initialPosY;

	while (!WindowShouldClose())
	{
		SetTargetFPS(60);
		DrawFPS(0, 0);
		BeginDrawing();
		ClearBackground(BLACK);

		// NOTES(Ruan): a VERY simple way to debug if things are, in fact, in the middle of the screen
		DrawLine(WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT, GREEN);
		DrawLine(0, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT / 2, GREEN);

		eagleStratagem.Input();
		eagleStratagem.Update();
		eagleStratagem.Draw();

		if (eagleStratagem.GetFinished())
		{
			//break;
		}
		
		EndDrawing();
	}

	eagleStratagem.UnloadResources();

	return 0;
}