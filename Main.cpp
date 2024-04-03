#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Arrow.h"

const int initialPosY = 260;
const int posYLimit = 40;
const float lerpBy = 0.2f;
bool pressed = false;
bool endingAnimation = false;

int main(void)
{
	// TODO (maybe): Option to have all arrows that point to the same direction with the same color

	InitWindow(800, 600, "Stratagem Citizen");

	Image arrowUpImage = LoadImage("Assets/Arrow Up.png");
	Image arrowDownImage = LoadImage("Assets/Arrow Down.png");

	Color color{};
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	Vector2 arrowOnePos{ 270, 260 };
	Vector2 arrowTwoPos{ 360, 260 };

	Arrow arrow = Arrow(arrowUpImage, color, arrowOnePos, KEY_UP);
	Arrow arrow2 = Arrow(arrowDownImage, color, arrowTwoPos, KEY_DOWN);

	float posY = initialPosY;

	while (!WindowShouldClose())
	{
		SetTargetFPS(60);
		DrawFPS(0, 0);
		BeginDrawing();
		ClearBackground(BLACK);

		arrow.Input();

		if (arrow.GetPressed())
		{
			arrow2.Input();
			arrow2.Update();
		}

		arrow.Update();
		
		arrow.Draw();
		arrow2.Draw();
		
		EndDrawing();
	}

	UnloadImage(arrowUpImage);
	UnloadImage(arrowDownImage);

	return 0;
}