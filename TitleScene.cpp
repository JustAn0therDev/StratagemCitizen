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
	const int halfWindowWidth = WINDOW_WIDTH / 2;
	const int halfWindowHeight = WINDOW_HEIGHT / 2;

	int stratagemCitizenTitleSizeX = MeasureText("STRATAGEM CITIZEN", m_FontSize);
	int pressEnterToStartSizeX = MeasureText("> Press enter to start <", m_FontSize - 20);

	DrawText("STRATAGEM CITIZEN", WINDOW_WIDTH / 2 - (stratagemCitizenTitleSizeX / 2), halfWindowHeight - static_cast<int>(m_FontSize / 2), m_FontSize, WHITE);

	DrawText("> Press enter to start <", WINDOW_WIDTH / 2 - (pressEnterToStartSizeX / 2), (halfWindowHeight + 80) - static_cast<int>((m_SubtitleFontSize) / 2), m_SubtitleFontSize, WHITE);
}
