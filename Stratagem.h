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
	std::vector<Arrow> m_Arrows; // TODO: Maybe make pointers out of it?
	const char* m_Name;
	bool m_Finished;
	int m_Index;
	float m_HalfOfArrowImageWidth;
	float m_ArrowImageOffset;
	float m_InitialPosX;
	float m_InitialPosY;

public:
	Stratagem(const char* p_ImageFileName, std::vector<Arrow> p_Arrows, const char* p_Name);
	void LoadStratagemImageTexture(const char* p_ImageFileName);
	void Input();
	void Update();
	void Draw();
	bool GetFinished() const;
	void UnloadResources();
	void CalculateArrowPositions();
};

