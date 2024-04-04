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

public:
	Stratagem(const char* p_ImageFileName, Vector2 p_ImagePosition, std::vector<Arrow> p_Arrows, const char* p_Name);
	void Input();
	void Update();
	void Draw();
	bool GetFinished() const;
	void UnloadResources();
};

