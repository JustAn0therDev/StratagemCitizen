#include "Round.h"
#include <vector>
#include <raylib.h>
#include "Stratagem.h"
#include <string>
#include "RoundTimer.h"
#include "Constants.h"

Round::Round() : m_Points(0), m_StratagemIndex(0), m_Finished(false) { }

void Round::SetRandomStratagemsFromStratagemVector(std::vector<Stratagem> p_Stratagems)
{
	// TODO: get random amount of stratagems?
	m_RandomStratagems = p_Stratagems;
}

void Round::Input()
{
	m_RandomStratagems[m_StratagemIndex].Input();
	m_RoundTimer.Input();
}

void Round::Update()
{
	m_RandomStratagems[m_StratagemIndex].Update();

	if (m_RandomStratagems[m_StratagemIndex].GetFinished())
	{
		int perfectBonus = m_RandomStratagems[m_StratagemIndex].GetMissedAnArrow() ? 0 : m_PerfectBonus;
		m_Points += 20 + perfectBonus;
		m_StratagemIndex++;
		m_RoundTimer.AddTime();
	}

	if (m_StratagemIndex == m_RandomStratagems.size() || m_RoundTimer.GetIsTimeUp())
	{
		m_Finished = true;
	}

	m_RoundTimer.Update();
}

void Round::Draw()
{
	char buffer[10] = {0};
	sprintf_s(buffer, "%i", m_Points);

	DrawText(buffer, WINDOW_WIDTH - static_cast<int>(WINDOW_WIDTH / 3.5f), WINDOW_HEIGHT / 3, m_PointsFontSize, YELLOW);

	for (size_t i = 0; i < m_RandomStratagems.size(); i++)
	{
		if (m_StratagemIndex == i)
		{
			m_RandomStratagems[i].Draw();
			continue;
		}

		int distanceMultiplier = (i + 1 - m_StratagemIndex);
		
		if (m_StratagemIndex < i && distanceMultiplier < 6)
		{
			// TODO: Draw only the stratagem icon
			Vector2 imagePosition = m_RandomStratagems[i].GetImagePosition();
			imagePosition.x += m_DefaultIconSpacing * distanceMultiplier;
			imagePosition.y += m_DefaultIconSpacing;
			const Texture2D imageTexture = m_RandomStratagems[i].GetTexture();
			DrawTextureEx(imageTexture, imagePosition, 0, 0.3f, WHITE);
		}
	}

	m_RoundTimer.Draw();
}

bool Round::GetFinished() const
{
	return m_Finished;
}
