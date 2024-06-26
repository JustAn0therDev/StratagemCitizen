#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include "Arrow.h"

class Stratagem
{
private:
	Vector2 m_ImagePosition;
	Texture2D m_Texture;
	std::vector<Arrow> m_Arrows;
	std::string m_Name;
	int m_FontSize = 40;
	bool m_Finished;
	int m_Index;
	float m_HalfOfArrowImageWidth;
	float m_ArrowImageOffset;
	float m_InitialPosX;
	float m_InitialPosY;
	bool m_MissedAnArrow;

public:
	Stratagem(const char* p_Name, std::vector<Arrow> p_Arrows, const char* p_ImageFileName);
	void LoadStratagemImageTexture(const char* p_ImageFileName);
	void Input();
	void Update();
	void Draw();
	bool GetFinished() const;
	void UnloadResources();
	void CalculateArrowPositions();
	bool GetMissedAnArrow() const;
	const Vector2 GetImagePosition() const;
	const Texture2D GetTexture() const;
};

