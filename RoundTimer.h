#pragma once
#include <chrono>

class RoundTimer
{
private:
	std::chrono::system_clock::time_point m_LastTime;
	int m_DrawRectangleWidth;
	int m_UpdateRectangleWidth;
	int m_InitialPosX;
	int m_InitialPosY;
	int m_RoundNumber;
	int m_RectangleHeight;
	int m_MakeRectangleWidthSmallerBy;
	bool m_IsTimeUp;
public:
	RoundTimer();
	void Input();
	void Update();
	void Draw();
	const bool GetIsTimeUp() const;
	// This method adds a few pixels to the rectangle that represents the total time.
	const void AddTime();
	const int GetRoundTimerBonus() const;
	void SetRoundNumber(int p_RoundNumber);
};

