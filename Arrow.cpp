#include "Arrow.h"
#include "raylib.h"
#include "raymath.h"
#include <string>

Arrow::Arrow(const char* p_ImageFileName, Color p_Color, Vector2 p_Pos, KeyboardKey p_KeyboardKey) : m_EndingAnimation(false), m_PressedCorrectButton(false)
{
	Image image = LoadImage(p_ImageFileName);
	this->m_Texture = LoadTextureFromImage(image);
	UnloadImage(image);
	
	this->m_Color = p_Color;
	this->m_Pos = p_Pos;
	this->m_KeyboardKey = p_KeyboardKey;
}

bool Arrow::Input()
{
	if (IsKeyPressed(m_KeyboardKey))
	{
		m_PressedCorrectButton = true;
	}

	return m_PressedCorrectButton;
}

void Arrow::Update()
{
	if (m_PressedCorrectButton)
	{
		if (m_Color.b > 0)
		{
			m_Color.b = (int)Clamp(Lerp(m_Color.b, 0, m_LerpBy), 0, 255);
			m_Color.a = (int)Clamp(Lerp(m_Color.a, 0, m_LerpBy), 0, 255);
			m_Pos.y = Lerp(m_Pos.y, m_InitialPosY - m_PosYLimit, m_LerpBy);
		}
	}
}

void Arrow::Draw()
{
	DrawTexture(m_Texture, static_cast<int>(m_Pos.x), static_cast<int>(m_Pos.y), m_Color);
}

void Arrow::UnloadResources()
{
	UnloadTexture(m_Texture);
}
