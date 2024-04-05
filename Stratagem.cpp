#include "Stratagem.h"
#include "Constants.h"

Stratagem::Stratagem(const char* p_ImageFileName, Vector2 p_ImagePosition, std::vector<Arrow> p_Arrows, const char* p_Name) : m_Finished(false), m_Index(0)
{
	Image image = LoadImage(p_ImageFileName);
	this->m_Texture = LoadTextureFromImage(image);
	UnloadImage(image);

	this->m_Arrows = p_Arrows;
	this->m_Name = p_Name;
	this->m_ImagePosition = p_ImagePosition;

	m_HalfOfArrowImageWidth = static_cast<float>(ARROW_IMAGE_WIDTH) / 2;
	m_ArrowImageOffset = ARROW_IMAGE_WIDTH + m_HalfOfArrowImageWidth;
	m_InitialPosX = ((static_cast<float>(WINDOW_WIDTH) / 2) - m_HalfOfArrowImageWidth) - m_HalfOfArrowImageWidth * (m_Arrows.size() - 1);
	m_InitialPosY = DEFAULT_ARROW_HEIGHT - m_HalfOfArrowImageWidth;

	this->CalculateArrowPositions();
}

void Stratagem::Input()
{
	if (m_Index == m_Arrows.size())
	{
		m_Finished = true;
		return;
	}

	bool pressedCorrectButton = m_Arrows[m_Index].Input();

	if (pressedCorrectButton)
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
	DrawTexture(m_Texture, static_cast<int>(m_ImagePosition.x), static_cast<int>(m_ImagePosition.y), WHITE);

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

void Stratagem::CalculateArrowPositions()
{
	for (size_t i = 0; i < m_Arrows.size(); i++)
	{
		if (i == 0)
			m_Arrows[i].SetPos({ m_InitialPosX, m_InitialPosY });
		else
			m_Arrows[i].SetPos({ m_InitialPosX + m_ArrowImageOffset * i, m_InitialPosY });
	}
}
