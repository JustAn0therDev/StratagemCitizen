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
	// Option to have all arrows that point to the same direction with the same color

	InitWindow(800, 600, "Stratagem Citizen");

	Image image = LoadImage("Assets/Arrow Up.png");

	Color color{};
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	Arrow arrow = Arrow(image, color, { 270, 260 });
	Arrow arrow2 = Arrow(image, color, { 360, 260 });

	float posY = initialPosY;

	while (!WindowShouldClose())
	{
		SetTargetFPS(60);
		DrawFPS(0, 0);
		BeginDrawing();
		ClearBackground(BLACK);

		if (arrow.GetPressed())
		{
			arrow2.Update();
		}

		arrow.Update();
		
		arrow.Draw();
		arrow2.Draw();
		
		EndDrawing();
	}

	UnloadImage(image);

	return 0;
}