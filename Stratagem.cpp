#include "Stratagem.h"
#include "Constants.h"
#include <string>

Stratagem::Stratagem(const char* p_Name, std::vector<Arrow> p_Arrows, const char* p_ImageFileName) : m_ImagePosition({ 200, 100 }), m_Finished(false), m_Index(0), m_MissedAnArrow(false)
{
	LoadStratagemImageTexture(p_ImageFileName);
	m_Arrows = p_Arrows;
	m_Name = std::string(p_Name);

	CalculateArrowPositions();
}

void Stratagem::LoadStratagemImageTexture(const char* p_ImageFileName)
{
	Image image = LoadImage(p_ImageFileName);

	// Images are always resized since I don't have control over the assets.
	// In an ideal scenario, the assets would all be the same size
	ImageResize(&image, STRATAGEM_IMAGE_WIDTH_LIMIT, STRATAGEM_IMAGE_HEIGHT_LIMIT);

	this->m_Texture = LoadTextureFromImage(image);
	UnloadImage(image);
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
	else if (m_Arrows[m_Index].GetMissed())
	{
		m_MissedAnArrow = true;
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
	DrawTextureEx(m_Texture, m_ImagePosition, 0, 0.5f, WHITE);
	int textSize = MeasureText(m_Name.c_str(), m_FontSize);

	int halfWindowHeight = static_cast<int>(WINDOW_HEIGHT / 2);
	int halfWindowWidth = static_cast<int>(WINDOW_WIDTH / 2);

	int namePosX = halfWindowWidth - static_cast<int>(textSize / 2);
	int namePosY = halfWindowHeight + 100;

	DrawText(m_Name.c_str(), namePosX, namePosY, m_FontSize, YELLOW);

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
	m_HalfOfArrowImageWidth = static_cast<float>(ARROW_IMAGE_WIDTH) / 2;
	m_ArrowImageOffset = ARROW_IMAGE_WIDTH + m_HalfOfArrowImageWidth;
	
	float arrowBlockSize = (m_ArrowImageOffset * m_Arrows.size()) - m_ArrowImageOffset;

	m_InitialPosX = static_cast<float>(WINDOW_WIDTH / 2) - arrowBlockSize / 2;
	
	m_InitialPosY = DEFAULT_ARROW_HEIGHT - m_HalfOfArrowImageWidth;

	for (size_t i = 0; i < m_Arrows.size(); i++)
	{
		m_Arrows[i].SetPos({ m_InitialPosX + m_ArrowImageOffset * i, m_InitialPosY });
	}
}

bool Stratagem::GetMissedAnArrow() const
{
	return m_MissedAnArrow;
}

const Vector2 Stratagem::GetImagePosition() const
{
	return m_ImagePosition;
}

const Texture2D Stratagem::GetTexture() const
{
	return m_Texture;
}
