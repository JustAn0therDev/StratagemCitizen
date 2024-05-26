#include "RoundTimer.h"
#include "Constants.h"
#include <raylib.h>
#include <chrono>
#include <raymath.h>

RoundTimer::RoundTimer() : m_UpdateRectangleWidth(400), m_DrawRectangleWidth(400), m_RectangleHeight(25), m_IsTimeUp(false)
{
	const int halfWindowWidth = WINDOW_WIDTH / 2;
	const int halfWindowHeight = WINDOW_HEIGHT / 2;
	m_InitialPosX = halfWindowWidth - 200;
	m_InitialPosY = halfWindowHeight + 200;
	m_LastTime = std::chrono::system_clock::now();
}

void RoundTimer::Input()
{
	// Nothing for now.
}

void RoundTimer::Update()
{
	// This means that the rectangle is not being drawn anymore.
	if (m_InitialPosX > m_InitialPosX + m_UpdateRectangleWidth) 
	{
		m_IsTimeUp = true;
	}

	std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsedSeconds = currentTime - m_LastTime;

	if (elapsedSeconds.count() > 0.2f)
	{
		m_UpdateRectangleWidth -= 5; // Completely arbitrary number.
		m_LastTime = currentTime;
	}
}

void RoundTimer::Draw()
{
	m_DrawRectangleWidth = static_cast<int>(Lerp(static_cast<float>(m_UpdateRectangleWidth), static_cast<float>(m_DrawRectangleWidth), 0.3f));
	DrawRectangle(m_InitialPosX, m_InitialPosY, m_DrawRectangleWidth, m_RectangleHeight, YELLOW);
}

const bool RoundTimer::GetIsTimeUp() const
{
	return m_IsTimeUp;
}

const void RoundTimer::AddTime()
{
	m_UpdateRectangleWidth += 70;
}

const int RoundTimer::GetRoundTimerBonus() const
{
	return static_cast<int>(m_UpdateRectangleWidth * 0.1);
}