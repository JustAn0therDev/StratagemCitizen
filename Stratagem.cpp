#include "Stratagem.h"
#include "Constants.h"

Stratagem::Stratagem(const char* p_Name, std::vector<Arrow> p_Arrows, const char* p_ImageFileName) : m_ImagePosition({ 200, 100 }), m_Finished(false), m_Index(0)
{
	LoadStratagemImageTexture(p_ImageFileName);
	this->m_Arrows = p_Arrows;
	this->m_Name = p_Name;

	this->CalculateArrowPositions();
}

void Stratagem::LoadStratagemImageTexture(const char* p_ImageFileName)
{
	// TODO(Ruan): For now, I'll resize the images that are too big.
	// In an ideal scenario, the images would always have the same size.
	// This method still contains an inherit problem, that being images that are
	// smaller than the limit.
	Image image = LoadImage(p_ImageFileName);

	if (image.height > STRATAGEM_IMAGE_HEIGHT_LIMIT && image.width > STRATAGEM_IMAGE_WIDTH_LIMIT)
	{
		ImageResize(&image, STRATAGEM_IMAGE_WIDTH_LIMIT, STRATAGEM_IMAGE_HEIGHT_LIMIT);
	}

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
	// FIXME: calculate this better :)
	m_HalfOfArrowImageWidth = static_cast<float>(ARROW_IMAGE_WIDTH) / 2;
	m_ArrowImageOffset = ARROW_IMAGE_WIDTH + m_HalfOfArrowImageWidth;
	m_InitialPosX = ((static_cast<float>(WINDOW_WIDTH) / 2) - m_HalfOfArrowImageWidth) - m_HalfOfArrowImageWidth * m_Arrows.size();
	m_InitialPosY = DEFAULT_ARROW_HEIGHT - m_HalfOfArrowImageWidth;

	for (size_t i = 0; i < m_Arrows.size(); i++)
	{
		m_Arrows[i].SetPos({ m_InitialPosX + m_ArrowImageOffset * i, m_InitialPosY });
	}
}
