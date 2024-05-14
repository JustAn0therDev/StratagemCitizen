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
		// TODO: The perfect bonus should be applied to the whole round, not to a single stratagem
		int perfectBonus = m_RandomStratagems[m_StratagemIndex].GetMissedAnArrow() ? 0 : m_PerfectBonus;
		m_Points += 20 + perfectBonus;
		m_StratagemIndex++;
		// TODO: Add timer bonus
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
