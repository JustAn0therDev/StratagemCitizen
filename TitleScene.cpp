#include "raylib.h"
#include "TitleScene.h"
#include "Constants.h"

bool TitleScene::GetShouldEndScene() const
{
	return m_ShouldEndScene;
}

void TitleScene::Input()
{
	if (IsKeyPressed(KEY_ENTER)) {
		m_ShouldEndScene = true;
	}
}

void TitleScene::Update()
{
	// NOTES(Ruan): Nothing for now
}

void TitleScene::Draw()
{
	DrawText("STRATAGEM CITIZEN", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 20, WHITE);
	DrawText("> Press enter to start <", WINDOW_WIDTH / 2, (WINDOW_HEIGHT + 80) / 2, 16, WHITE);
}
