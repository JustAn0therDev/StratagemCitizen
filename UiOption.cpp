#include "UiOption.h"
#include "Constants.h"
#include "UiFunctions.h"

UiOption::UiOption() : m_Text(""), m_FontSize(0), m_Pos(Vector2{ 0,0 }), m_Hovered(false), m_Selected(false) {}

UiOption::UiOption(std::string text, int fontSize, Vector2 pos) : m_Selected(false), m_Hovered(false)
{
	m_Text = text;
	m_FontSize = fontSize;
	m_Pos = pos;
}

const Vector2 UiOption::GetSizeMin() const
{
	return Vector2{ 0, 0 };
}

const Vector2 UiOption::GetRectangleBounds() const
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

void UiOption::Update()
{
	m_Hovered = UiFunctions::IsMouseInsideRectangle(GetPosition(), GetRectangleBounds());
}

void UiOption::Draw()
{
	char buffer[MAX_BUFFER_SIZE]{};

	GetDrawableText(buffer, MAX_BUFFER_SIZE);

	int bufferTextSizeX = MeasureText(buffer, m_FontSize);
	
	constexpr float half = 2.0f;

	DrawText(buffer,
		static_cast<int>(WINDOW_WIDTH / half - bufferTextSizeX / half),
		static_cast<int>(m_Pos.y),
		m_FontSize,
		WHITE);
}

void UiOption::GetDrawableText(char* buffer, int bufferSize) const
{
	if (IsHovered())
	{
		sprintf_s(buffer, bufferSize, "> %s <", GetText());
	}
	else
	{
		strcpy_s(buffer, bufferSize, GetText());
	}
}