#pragma once
#include "Scene.h"
#include "raylib.h"
#include "UiOption.h"
class TitleScene : public Scene
{
private:
	bool m_ShouldEndScene = false;
	const int m_FontSize = 40;
	const int m_SubtitleTextOffset = 80;
	const int m_SubtitleFontSize = m_FontSize - 20;
	const char* m_StartText = "Start";
	const char* m_SettingsText = "Settings";
	UiOption m_StartOption;
	UiOption m_SettingsOption;
public:
	TitleScene();
	virtual SceneEnum GetNextScene() const;
	virtual void Input(void);
	virtual void Update(void);
	virtual void Draw(void);

	const Vector2 GetSubtitleTextPosition(const char* text, int order) const;
	const void DrawTitle() const;
};

