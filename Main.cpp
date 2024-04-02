#include <iostream>
#include "raylib.h"
#include "raymath.h"

const int initialPosY = 260;
const int posYLimit = 40;
const float lerpBy = 0.3f;
bool pressed = false;
bool endingAnimation = false;

void Update(Color& color, float& posY)
{
	if (IsKeyPressed(KEY_UP))
	{
		pressed = true;
	}

	if (pressed)
	{
		if (color.r > 0 && !endingAnimation)
		{
			color.r = (int)Clamp(Lerp(color.r, 0, lerpBy), 0, 255);
			color.g = (int)Clamp(Lerp(color.g, 0, lerpBy), 0, 255);
			posY = Lerp(posY, initialPosY - posYLimit, lerpBy);
		}
		else
		{
			endingAnimation = true;
			color.r = (int)Clamp(Lerp(color.r, 255, lerpBy), 0,255);
			color.g = (int)Clamp(Lerp(color.g, 255, lerpBy), 0, 255);
			posY = ceilf(Lerp(posY, initialPosY, lerpBy));
			if (posY == initialPosY)
			{
				pressed = false;
				endingAnimation = false;
			}
		}
	}
}

int main(void)
{
	InitWindow(800, 600, "Stratagem Citizen");

	Image image = LoadImage("Assets/Arrow Up.png");

	Texture2D arrowTexture = LoadTextureFromImage(image);

	Color color{};
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	float posY = initialPosY;

	while (!WindowShouldClose())
	{
		SetTargetFPS(60);
		DrawFPS(0, 0);
		BeginDrawing();
		ClearBackground(BLACK);

		Update(color, posY);
		
		DrawTexture(arrowTexture, 360, static_cast<int>(posY), color);

		EndDrawing();
	}

	UnloadImage(image);

	return 0;
}