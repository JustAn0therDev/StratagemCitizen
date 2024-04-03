#include "Arrow.h"
#include "raylib.h"
#include "raymath.h"

Arrow::Arrow(Image p_Image, Color p_Color, Vector2 p_Pos)
{
	this->m_Texture = LoadTextureFromImage(p_Image);
	this->m_Color = p_Color;
	this->m_Pos = p_Pos;
}

void Arrow::Update()
{
	if (IsKeyPressed(KEY_UP))
	{
		m_Interacted = true;
		m_Pressed = true;
	}

	if (m_Interacted)
	{
		if (m_Color.b > 0 && !m_EndingAnimation)
		{
			m_Color.b = (int)Clamp(Lerp(m_Color.b, 0, m_LerpBy), 0, 255);
			m_Color.a = (int)Clamp(Lerp(m_Color.a, 0, m_LerpBy * 0.5f), 0, 255);
			m_Pos.y = Lerp(m_Pos.y, m_InitialPosY - m_PosYLimit, m_LerpBy);
		}
		else
		{
			m_EndingAnimation = true;
			m_Pos.y = ceilf(Lerp(m_Pos.y, m_InitialPosY, m_LerpBy));
			if (m_Pos.y == m_InitialPosY)
			{
				m_Interacted = false;
				m_EndingAnimation = false;
			}
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
