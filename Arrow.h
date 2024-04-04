#pragma once
#include <raylib.h>

class Arrow
{
private:
	/*const */float m_InitialPosY = 260.0f;
	/*const */float m_PosYLimit = 40.0f;
	/*const */float m_LerpBy = 0.3f;

	KeyboardKey m_KeyboardKey;
	Vector2 m_Pos;
	bool m_PressedCorrectButton = false;
	bool m_EndingAnimation = false;
	Color m_Color;
	Texture2D m_Texture;

public:
	Arrow(const char* p_FileName, Color p_Color, Vector2 p_Pos, KeyboardKey p_KeyboardKey);
	bool Input();
	void Update();
	void Draw();
	void UnloadResources();
};

