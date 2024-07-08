#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Arrow.h"
#include "Stratagem.h"
#include "Constants.h"
#include "StratagemConfigParser.h"
#include "TitleScene.h"
#include "GameScene.h"

const int initialPosY = 260;
const int posYLimit = 40;
const float lerpBy = 0.2f;
bool pressed = false;
bool endingAnimation = false;

int main(void)
{
	// MAYBE: Option to have all arrows that point to the same direction with the same color

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Stratagem Citizen");

	TitleScene* titleScene = new TitleScene();

	StratagemConfigParser stratagemConfigParser("StratagemConfig.txt");
	stratagemConfigParser.ParseStratagems();
	std::vector<Stratagem> stratagems = stratagemConfigParser.GetStratagems();

	GameScene* gameScene = new GameScene(stratagems);

	while (!WindowShouldClose())
	{
		SetTargetFPS(60);
#ifdef _DEBUG
		DrawFPS(0, 0);
#endif
		BeginDrawing();
		ClearBackground(BLACK);

		if (titleScene != nullptr) {
			titleScene->Input();
			titleScene->Update();
			titleScene->Draw();

			if (titleScene->GetShouldEndScene()) {
				delete titleScene;
				titleScene = nullptr;
			}
		}
		else
		{
			gameScene->Input();
			gameScene->Update();
			gameScene->Draw();
		}
	
		EndDrawing();
	}

	return 0;
}