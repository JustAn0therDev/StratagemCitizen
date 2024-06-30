#pragma once
#include <raylib.h>
#include <string>
class UiOption
{
private:
	int m_FontSize;
	bool m_Selected;
	bool m_Hovered;
	std::string m_Text;
	Vector2 m_Pos;
public:
	UiOption();
	UiOption(std::string text, int fontSize, Vector2 pos);
	const Vector2 GetSizeMin() const;
	const Vector2 GetRectangleBounds() const;
	const bool IsSelected() const;
	void SetSelected(const bool selected);
	const Vector2 GetPosition() const;
	const bool IsHovered() const;
	void SetHovered(const bool hovered);
	const char* GetText() const;
	void Update();
	void Draw();
	void GetDrawableText(char* buffer, int bufferSize) const;
};

