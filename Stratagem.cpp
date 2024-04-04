#include "Stratagem.h"

Stratagem::Stratagem(const char* p_ImageFileName, Vector2 p_ImagePosition, std::vector<Arrow> p_Arrows, const char* p_Name) : m_Finished(false), m_Index(0)
{
	Image image = LoadImage(p_ImageFileName);
	this->m_Texture = LoadTextureFromImage(image);
	UnloadImage(image);

	this->m_Arrows = p_Arrows;
	this->m_Name = p_Name;
	this->m_ImagePosition = p_ImagePosition;
}

void Stratagem::Input()
{
	if (m_Index == m_Arrows.size())
	{
		m_Finished = true;
		return;
	}

	bool interacted = m_Arrows[m_Index].Input();

	if (interacted)
	{
		m_Index++;
	}
}

void Stratagem::Update()
{
	for (auto& arrow : m_Arrows)
	{
		arrow.Update();
	}
}

void Stratagem::Draw()
{
	DrawTexture(m_Texture, m_ImagePosition.x, m_ImagePosition.y, WHITE);

	for (auto& arrow : m_Arrows)
		arrow.Draw();
}

bool Stratagem::GetFinished() const
{
	return m_Finished;
}

void Stratagem::UnloadResources()
{
	for (auto& arrow : m_Arrows)
		arrow.UnloadResources();

	UnloadTexture(m_Texture);
}
