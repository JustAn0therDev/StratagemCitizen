#include "Arrow.h"
#include "raylib.h"
#include "raymath.h"
#include <string>

Arrow::Arrow(const char* p_ImageFileName, KeyboardKey p_KeyboardKey) : m_PressedCorrectButton(false), m_Pos({ 0 })
{
	Image image = LoadImage(p_ImageFileName);
	this->m_Texture = LoadTextureFromImage(image);
	UnloadImage(image);
	
	this->m_Color = WHITE;
	this->m_KeyboardKey = p_KeyboardKey;
}

bool Arrow::PressedCorrectArrowKey()
{
	bool pressedUpAndWasUp = IsKeyPressed(m_KeyboardKey) && m_KeyboardKey == KEY_UP;
	bool pressedRightAndWasRight = IsKeyPressed(m_KeyboardKey) && m_KeyboardKey == KEY_RIGHT;
	bool pressedLeftAndWasLeft = IsKeyPressed(m_KeyboardKey) && m_KeyboardKey == KEY_LEFT;
	bool pressedDownAndWasDown = IsKeyPressed(m_KeyboardKey) && m_KeyboardKey == KEY_DOWN;

	return pressedUpAndWasUp || pressedDownAndWasDown || pressedLeftAndWasLeft || pressedRightAndWasRight;
}

bool Arrow::Input()
{
	bool pressedCorrectArrowKey = PressedCorrectArrowKey();

	if (pressedCorrectArrowKey)
	{
		m_PressedCorrectButton = true;
	}
	else
	{
		// TODO: Check if the key pressed was an arrow key.
	}

	return m_PressedCorrectButton;
}

void Arrow::Update()
{
	if (m_PressedCorrectButton)
	{
		m_PressedWrongButton = false;
	
		if (m_Color.b > 0)
		{
			m_Color.b = (int)Clamp(Lerp(m_Color.b, 0, m_LerpBy), 0, 255);
			m_Color.a = (int)Clamp(Lerp(m_Color.a, 0, m_LerpBy), 0, 255);
			m_Pos.y = Lerp(m_Pos.y, m_InitialPosY - m_PosYLimit, m_LerpBy);
		}
	}
	
	if (m_PressedWrongButton)
	{
		if (m_Color.b > 0)
		{
			m_Color.b = (int)Clamp(Lerp(m_Color.b, 0, m_LerpBy), 0, 255);
			m_Color.g = (int)Clamp(Lerp(m_Color.g, 0, m_LerpBy), 0, 255);
		}
		else
		{
			m_PressedWrongButton = false;
			m_Color = WHITE;
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

Vector2 Arrow::GetPos() const
{
	return m_Pos;
}

void Arrow::SetPos(Vector2 pos)
{
	m_Pos = pos;
}