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
	int m_RectangleHeight;
	bool m_IsTimeUp;
public:
	RoundTimer();
	void Input();
	void Update();
	void Draw();
	const bool GetIsTimeUp() const;
};

