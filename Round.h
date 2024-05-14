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
	int m_PointsFontSize = 60;
	std::vector<Stratagem> m_RandomStratagems;
	RoundTimer m_RoundTimer;
	bool m_Finished;
public:
	Round();
	void SetRandomStratagemsFromStratagemVector(std::vector<Stratagem> p_Stratagems);
	void Input();
	void Update();
	void Draw();
	bool GetFinished() const;
};

