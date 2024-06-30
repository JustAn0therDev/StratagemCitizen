#include "UiOption.h"
#include "Constants.h"

UiOption::UiOption() : m_Text(""), m_FontSize(0), m_Pos(Vector2{ 0,0 }), m_Hovered(false), m_Selected(false) {}

UiOption::UiOption(std::string text, int fontSize, Vector2 pos) : m_Selected(false), m_Hovered(false)
{
	m_Text = text;
	m_FontSize = fontSize;

	//constexpr float halfWindowWidth = static_cast<float>(WINDOW_WIDTH / 2);
	//constexpr float halfWindowHeight = static_cast<float>(WINDOW_HEIGHT / 2);
	//int textSizeX = MeasureText(m_Text.c_str(), m_FontSize);
	//m_Pos = { halfWindowWidth - static_cast<float>(textSizeX / 2), halfWindowHeight - (WINDOW_HEIGHT / 2)};
	//m_Pos = { halfWindowWidth - static_cast<float>(textSizeX / 2), halfWindowHeight - static_cast<float>(m_FontSize / 2) };
	m_Pos = pos;
}

const Vector2 UiOption::GetSizeMin() const
{
	return Vector2{ 0, 0 };
}

const Vector2 UiOption::GetSizeMax() const // TODO: Rename function to "Get Bounds" or something.
{
	int textSizeX = MeasureText(m_Text.c_str(), m_FontSize);

	Vector2 size = { m_Pos.x + textSizeX, m_Pos.y + m_FontSize };

	return size;
}

const bool UiOption::IsSelected() const
{
	return m_Selected;
}

void UiOption::SetSelected(const bool selected)
{
	m_Selected = selected;
}

const Vector2 UiOption::GetPosition() const
{
	return m_Pos;
}

const bool UiOption::IsHovered() const
{
	return m_Hovered;
}

void UiOption::SetHovered(const bool hovered)
{
	m_Hovered = hovered;
}

const char* UiOption::GetText() const
{
	return m_Text.c_str();
}
