#pragma once
#include <vector>
#include "Stratagem.h"
#include "RoundTimer.h"

class Round
{
private:
	int m_Points;
	int m_StratagemIndex;
	int m_PerfectBonus = 100;
	int m_DefaultIconSpacingX = 100;
	int m_DefaultIconSpacingY = 100;
	int m_StratagemIconAmountLimit = 8;
	std::vector<Stratagem> m_RandomStratagems;
	RoundTimer m_RoundTimer;
	bool m_Finished;
	bool m_WasRoundPerfect;
public:
	Round();
	void SetRandomStratagemsFromStratagemVector(std::vector<Stratagem> p_Stratagems);
	void Input();
	void Update();
	void Draw();
	bool GetFinished() const;
	const int GetPoints() const;
	const int GetPerfectBonus() const;
	const int GetTotalPoints() const;
	const RoundTimer* GetRoundTimer() const;
};

