#pragma once
#include <raylib.h>

class Arrow
{
private:
	float m_InitialPosY = 260.0f;
	float m_PosYLimit = 40.0f;
	float m_LerpBy = 0.3f;

	KeyboardKey m_KeyboardKey;
	Vector2 m_Pos;
	bool m_PressedCorrectButton = false;
	bool m_EndingAnimation = false;
	Color m_Color;
	Texture2D m_Texture;

public:
	Arrow(const char* p_ImageFileName, KeyboardKey p_KeyboardKey);
	bool Input();
	void Update();
	void Draw();
	void UnloadResources();
	Vector2 GetPos() const;
	void SetPos(Vector2 pos);
};

