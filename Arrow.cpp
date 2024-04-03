#include "Arrow.h"
#include "raylib.h"
#include "raymath.h"

Arrow::Arrow(Image p_Image, Color p_Color, Vector2 p_Pos, KeyboardKey p_keyboardKey)
{
	this->m_Texture = LoadTextureFromImage(p_Image);
	this->m_Color = p_Color;
	this->m_Pos = p_Pos;
	this->m_KeyboardKey = p_keyboardKey;
}

void Arrow::Input()
{
	if (IsKeyPressed(m_KeyboardKey))
	{
		m_Interacted = true;
		m_Pressed = true;
	}
}

void Arrow::Update()
{
	if (m_Interacted)
	{
		if (m_Color.b > 0)
		{
			m_Color.b = (int)Clamp(Lerp(m_Color.b, 0, m_LerpBy), 0, 255);
			m_Color.a = (int)Clamp(Lerp(m_Color.a, 0, m_LerpBy), 0, 255);
			m_Pos.y = Lerp(m_Pos.y, m_InitialPosY - m_PosYLimit, m_LerpBy);
		}
	}
}

void Arrow::Draw() const
{
	DrawTexture(m_Texture, m_Pos.x, static_cast<int>(m_Pos.y), m_Color);
}

bool Arrow::GetPressed() const
{
	return m_Pressed;
}
