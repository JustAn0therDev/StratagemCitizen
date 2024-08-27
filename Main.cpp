#include <stdlib.h>
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Arrow.h"
#include "Stratagem.h"
#include "Constants.h"
#include "StratagemConfigParser.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneManager.h"

int main(void)
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Stratagem Citizen");

	SceneManager sceneManager;

	Scene* scene = sceneManager.GetNextScenePtr(SceneEnum::TITLE);

	while (!WindowShouldClose())
	{
		SetTargetFPS(60);
#ifdef _DEBUG
		DrawFPS(0, 0);
#endif
		BeginDrawing();
		ClearBackground(BLACK);

		if (scene != nullptr) {
			scene->Input();
			scene->Update();
			scene->Draw();

			Scene* nextScenePtr = sceneManager.GetNextScenePtr(scene->GetNextScene());

			if (nextScenePtr) 
			{
				scene = nextScenePtr;
			}
		}
	
		EndDrawing();
	}

	return 0;
}