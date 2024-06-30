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
bool TitleScene::GetShouldEndScene() const
{
	return m_ShouldEndScene;
}

void TitleScene::Input()
{
	if (IsKeyPressed(KEY_ENTER)) {
		m_ShouldEndScene = true;
	}

	if (m_SettingsOption.IsHovered() && IsKeyPressed(MOUSE_BUTTON_LEFT))
	{
		// TODO: Change to settings scene.
	}
}

void TitleScene::Update()
{
	m_SettingsOption.SetHovered(
		UiFunctions::IsMouseInsideRectangle(
			m_SettingsOption.GetPosition(),
			m_SettingsOption.GetSizeMax()
		)
	);

	m_StartOption.SetHovered(
		UiFunctions::IsMouseInsideRectangle(
			m_StartOption.GetPosition(),
			m_StartOption.GetSizeMax()
		)
	);
}

void TitleScene::Draw()
{
	DrawTitle();
	DrawSubtitle(&m_StartOption);
	DrawSubtitle(&m_SettingsOption);
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

const void TitleScene::DrawSubtitle(const UiOption* uiOption) const
{
	char buffer[250]{};
	
	if (uiOption->IsHovered())
	{
		sprintf_s(buffer, "> %s <", uiOption->GetText());
	}
	else
	{
		strcpy_s(buffer, uiOption->GetText());
	}

	// TODO: Maybe refactor this later so the position calculation is actually a responsibility of the UiOption class?
	Vector2 originalTextPos = uiOption->GetPosition();

	int bufferTextSizeX = MeasureText(buffer, m_SubtitleFontSize);

	DrawText(buffer,
		static_cast<float>(WINDOW_WIDTH / 2) - static_cast<float>(bufferTextSizeX / 2),
		static_cast<int>(originalTextPos.y),
		m_SubtitleFontSize,
		WHITE);
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
