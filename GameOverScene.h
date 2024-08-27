#pragma once
#include "Scene.h"
#include "raylib.h"
class GameOverScene : public virtual Scene
{
private:
	int m_FontSize = 50;
public:
	void Input(void);
	void Update(void);
	void Draw(void);
	SceneEnum GetNextScene() const;
	Vector2 GetTextPositionForText(const char* text) const;
};