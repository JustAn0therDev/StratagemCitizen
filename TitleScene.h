#pragma once
#include "Scene.h"
class TitleScene : public Scene
{
private:
	bool m_ShouldEndScene = false;
	const int m_FontSize = 60;
	const int m_SubtitleFontSize = m_FontSize - 20;

public:
	virtual bool GetShouldEndScene() const;
	virtual void Input();
	virtual void Update();
	virtual void Draw();
};

