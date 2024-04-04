#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Arrow.h"
#include "Stratagem.h"

const int initialPosY = 260;
const int posYLimit = 40;
const float lerpBy = 0.2f;
bool pressed = false;
bool endingAnimation = false;

int main(void)
{
	// TODO (maybe): Option to have all arrows that point to the same direction with the same color

	InitWindow(800, 600, "Stratagem Citizen");

	Color color{};
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	Vector2 stratagemPos{ 100, 60 };
	
	Vector2 arrowOnePos{ 270, 260 };
	Vector2 arrowTwoPos{ 360, 260 };
	Vector2 arrowThreePos{ 450, 260 };
	Vector2 arrowFourPos{ 540, 260 };
	Vector2 arrowFivePos{ 630, 260 };

	Arrow arrow = Arrow("Assets/Arrow Up.png", color, arrowOnePos, KEY_UP);
	Arrow arrow2 = Arrow("Assets/Arrow Right.png", color, arrowTwoPos, KEY_RIGHT);
	Arrow arrow3 = Arrow("Assets/Arrow Down.png", color, arrowThreePos, KEY_DOWN);
	Arrow arrow4 = Arrow("Assets/Arrow Down.png", color, arrowFourPos, KEY_DOWN);
	Arrow arrow5 = Arrow("Assets/Arrow Down.png", color, arrowFivePos, KEY_DOWN);

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

		eagleStratagem.Input();
		eagleStratagem.Update();
		eagleStratagem.Draw();

		if (eagleStratagem.GetFinished())
		{
			break;
		}
		
		EndDrawing();
	}

	eagleStratagem.UnloadResources();

	return 0;
}