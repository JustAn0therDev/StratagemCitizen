#pragma once
#include <raylib.h>

class Arrow
{
private:
	const float m_InitialPosY = 260.0f;
	const int m_PosYLimit = 40;
	const float m_LerpBy = 0.3f;

	KeyboardKey m_KeyboardKey;
	Vector2 m_Pos;
	bool m_Interacted = false;
	bool m_EndingAnimation = false;
	Color m_Color;
	Texture2D m_Texture;
	bool m_Pressed = false;

public:
	Arrow(Image p_Image, Color p_Color, Vector2 p_PosY, KeyboardKey p_KeyboardKey);
	void Input();
	void Update();
	void Draw() const;
	bool GetPressed() const;
};

