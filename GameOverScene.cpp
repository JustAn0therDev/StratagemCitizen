#include "GameOverScene.h"
#include "raylib.h"
#include "Constants.h"
#include "SceneEnum.h"

void GameOverScene::Input(void)
{
	// Nothing
}

void GameOverScene::Update(void)
{

}

void GameOverScene::Draw(void)
{
	const char* gameOverText = "Game over!";

	Vector2 textPos = GetTextPositionForText(gameOverText);

	DrawText(gameOverText, static_cast<int>(textPos.x), static_cast<int>(textPos.y), m_FontSize, YELLOW);
}

Vector2 GameOverScene::GetTextPositionForText(const char* text) const
{
	int textureSizeX = MeasureText(text, m_FontSize);

	int halfOfWindowHeight = static_cast<int>(WINDOW_HEIGHT / 2);
	int halfOfWindowWidth = static_cast<int>(WINDOW_WIDTH / 2);

	Vector2 pos{};

	pos.x = static_cast<float>(halfOfWindowWidth - textureSizeX / 2);
	pos.y = static_cast<float>(halfOfWindowHeight - m_FontSize / 2);

	return pos;
}

SceneEnum GameOverScene::GetNextScene() const
{
	return SceneEnum::NONE;
}
