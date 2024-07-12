#include "raylib.h"
#include "TitleScene.h"
#include "Constants.h"
#include "UiFunctions.h"

TitleScene::TitleScene()
{
	m_StartOption = UiOption(m_StartText, m_SubtitleFontSize, GetSubtitleTextPosition(m_StartText, 1));
	m_SettingsOption = UiOption(m_SettingsText, m_SubtitleFontSize, GetSubtitleTextPosition(m_SettingsText, 2));
}

// TODO: This should not exist. This should return the scene that will be loaded next.
// Be it an object, an enum, anything.
SceneEnum TitleScene::GetNextScene() const
{
	return m_ShouldEndScene ? SceneEnum::GAME : SceneEnum::NONE;
}

void TitleScene::Input(void)
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		if (m_SettingsOption.IsHovered()) {
			// TODO: Change scene to Settings Scene
		}

		if (m_StartOption.IsHovered()) {
			m_ShouldEndScene = true;
		}
	}

	if (IsKeyReleased(KEY_ENTER)) {
		m_ShouldEndScene = true;
	}
}

void TitleScene::Update(void)
{
	m_StartOption.Update();
	m_SettingsOption.Update();
}

void TitleScene::Draw(void)
{
	DrawTitle();
	m_StartOption.Draw();
	m_SettingsOption.Draw();
}

const void TitleScene::DrawTitle() const
{
	const char* titleText = "STRATAGEM CITIZEN";

	constexpr int halfWindowWidth = WINDOW_WIDTH / 2;
	constexpr int halfWindowHeight = WINDOW_HEIGHT / 2;

	int stratagemCitizenTitleSizeX = MeasureText(titleText, m_FontSize);

	DrawText(titleText,
		WINDOW_WIDTH / 2 - (stratagemCitizenTitleSizeX / 2),
		halfWindowHeight - static_cast<int>(m_FontSize / 2),
		m_FontSize, WHITE);
}

const Vector2 TitleScene::GetSubtitleTextPosition(const char* text, int order) const
{
	constexpr int halfWindowWidth = WINDOW_WIDTH / 2;
	constexpr int halfWindowHeight = WINDOW_HEIGHT / 2;

	int textSizeX = MeasureText(text, m_SubtitleFontSize);

	Vector2 pos{};

	pos.x = static_cast<float>(WINDOW_WIDTH / 2) - static_cast<float>(textSizeX / 2);
	
	pos.y = (float)(halfWindowHeight + (m_SubtitleTextOffset * order)) 
			- static_cast<float>(m_SubtitleFontSize / 2);

	return pos;
}
