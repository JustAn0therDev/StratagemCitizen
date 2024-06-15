#include "Round.h"
#include <vector>
#include <raylib.h>
#include "Stratagem.h"
#include <string>
#include "RoundTimer.h"
#include "Constants.h"
#include <time.h>

Round::Round() : m_Points(0), m_StratagemIndex(0), m_Finished(false), m_WasRoundPerfect(true) { }

void Round::SetRandomStratagemsFromStratagemVector(std::vector<Stratagem> p_Stratagems)
{
	srand(static_cast<unsigned int>(time(NULL)));
	while (m_RandomStratagems.size() < STRATAGEM_AMOUNT_LIMIT) // For now, the amount of stratagems is not random
	{
		int random_index = static_cast<int>(rand() / ((RAND_MAX + 1u) / p_Stratagems.size()));
		m_RandomStratagems.push_back(p_Stratagems[random_index]);
	}
}

void Round::Input()
{
	if (m_StratagemIndex < m_RandomStratagems.size())
	{
		m_RandomStratagems[m_StratagemIndex].Input();
	}
	
	m_RoundTimer.Input();
}

void Round::Update()
{
	if (m_StratagemIndex < m_RandomStratagems.size())
	{
		m_RandomStratagems[m_StratagemIndex].Update();

		if (m_RandomStratagems[m_StratagemIndex].GetFinished())
		{
			if (m_RandomStratagems[m_StratagemIndex].GetMissedAnArrow())
			{
				m_WasRoundPerfect = false;
			}

			m_Points += POINTS_PER_STRATAGEM;
			m_StratagemIndex++;
			m_RoundTimer.AddTime();
		}
	}

	if (m_StratagemIndex == m_RandomStratagems.size() || m_RoundTimer.GetIsTimeUp())
	{
		m_Finished = true;
	}

	m_RoundTimer.Update();
}

void Round::Draw()
{
	for (size_t i = 0; i < m_RandomStratagems.size(); i++)
	{
		if (m_StratagemIndex == i)
		{
			m_RandomStratagems[i].Draw();
			continue;
		}

		size_t distanceMultiplier = (i + 1 - m_StratagemIndex);
		
		if (m_StratagemIndex < i && distanceMultiplier < m_StratagemIconAmountLimit)
		{
			Vector2 imagePosition = m_RandomStratagems[i].GetImagePosition();
			imagePosition.x += m_DefaultIconSpacingX * distanceMultiplier;
			imagePosition.y += m_DefaultIconSpacingY;
			const Texture2D imageTexture = m_RandomStratagems[i].GetTexture();
			DrawTextureEx(imageTexture, imagePosition, 0, 0.2f, WHITE);
		}
	}

	m_RoundTimer.Draw();
}

bool Round::GetFinished() const
{
	return m_Finished;
}

const int Round::GetPoints() const
{
	return m_Points;
}

const int Round::GetTotalPoints() const
{
	return m_Points + GetPerfectBonus() + m_RoundTimer.GetRoundTimerBonus();
}

const RoundTimer* Round::GetRoundTimer() const
{
	return &m_RoundTimer;
}

const int Round::GetPerfectBonus() const
{
	return m_WasRoundPerfect ? m_PerfectBonus : 0;
}