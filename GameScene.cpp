#include "GameScene.h"
#include "Constants.h"
#include "RoundTimer.h"
#include <raylib.h>
#include "Round.h"

// TODO:
// Calculate the round, images and text relative to the window size, not with fixed values, like font sizes, for example.
GameScene::GameScene(std::vector<Stratagem> p_Stratagems) : m_Index(0), m_TotalPoints(0), m_RoundNumber(1), m_ElapsedSeconds(0)
{
	m_Stratagems = p_Stratagems;
	m_CurrentRound.SetRandomStratagemsFromStratagemVector(p_Stratagems);
}

void GameScene::SetStratagemVector(std::vector<Stratagem> p_Stratagems)
{
	m_Stratagems = p_Stratagems;
}

void GameScene::Input(void)
{
	m_CurrentRound.Input();
}

void GameScene::Update(void)
{
	if (m_CurrentRound.GetFinished())
	{
		std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
		m_ElapsedSeconds = currentTime - m_LastTime;

		if (m_ElapsedSeconds.count() < m_EndRoundTimeLimitInSeconds)
		{
			currentTime = std::chrono::system_clock::now();
			m_ElapsedSeconds = currentTime - m_LastTime;
			return;
		}

		m_TotalPoints += m_CurrentRound.GetTotalPoints();
		m_CurrentRound = Round();
		m_CurrentRound.SetRandomStratagemsFromStratagemVector(m_Stratagems);
		m_RoundNumber++;

		m_ElapsedSeconds = m_ElapsedSeconds.zero();
	}
	else
	{
		m_LastTime = std::chrono::system_clock::now();
		m_CurrentRound.Update();
	}
}

void GameScene::Draw(void)
{
	if (!m_CurrentRound.GetFinished())
	{
		m_CurrentRound.Draw();
		DrawCurrentRoundTextOnTopRightCorner();
		DrawCurrentPoints();
	}
	else
	{
		RunRoundEndAnimation();
	}
}

void GameScene::DrawCurrentRoundTextOnTopRightCorner()
{
	char buffer[30] = { 0 };

	sprintf_s(buffer, "Round: %i", m_RoundNumber);
	constexpr int xOffset = 20;
	int textSizeWithSpacingX = MeasureText(buffer, m_FontSize) + xOffset;

	DrawText(buffer, WINDOW_WIDTH - textSizeWithSpacingX, 0, m_FontSize, YELLOW);
}

void GameScene::DrawCurrentPoints()
{
	char buffer[30] = { 0 };

	int totalPointsPlusRound = m_TotalPoints + m_CurrentRound.GetPoints();
	constexpr int xOffset = static_cast<int>(WINDOW_WIDTH / 5);
	constexpr int yOffset = WINDOW_HEIGHT / 4;

	sprintf_s(buffer, "%i", totalPointsPlusRound);
	DrawText(buffer, WINDOW_WIDTH - static_cast<int>(WINDOW_WIDTH / 5), WINDOW_HEIGHT / 4, m_PointsFontSize, YELLOW);
}

bool GameScene::GetShouldEndScene() const
{
	return true;
}

GameScene::~GameScene()
{
	for (auto& stratagem : m_Stratagems)
	{
		stratagem.UnloadResources();
	}
}

void GameScene::RunRoundEndAnimation()
{
	const int initialTextYOffset = 75;

	if (m_ElapsedSeconds.count() < 3.5)
	{
		int roundPoints = POINTS_PER_STRATAGEM * STRATAGEM_AMOUNT_LIMIT;
		DrawRoundPointsText("Round Bonus", roundPoints, 0);

		if (m_ElapsedSeconds.count() > 0.7)
		{
			int timeBonus = m_CurrentRound.GetRoundTimer()->GetRoundTimerBonus();
			DrawRoundPointsText("Time Bonus", timeBonus, initialTextYOffset);
		}

		if (m_ElapsedSeconds.count() > 1.4)
		{
			int perfectBonus = m_CurrentRound.GetPerfectBonus();
			DrawRoundPointsText("Perfect Bonus", perfectBonus, initialTextYOffset * 2);
		}

		if (m_ElapsedSeconds.count() > 2.1)
		{
			const int totalScore = m_CurrentRound.GetTotalPoints();
			DrawRoundPointsText("Total Score", totalScore, initialTextYOffset * 3);
		}
	}
	else
	{
		RunGetReadyAnimation();
	}
}

void GameScene::DrawRoundPointsText(const char* text, const int points, const int pointsPositionYOffset) const
{
	constexpr int sixthWindowWidth = static_cast<int>(WINDOW_WIDTH / 6);
	constexpr int quarterWindowHeight = static_cast<int>(WINDOW_HEIGHT / 4);
	const int pointsPositionX = sixthWindowWidth * 4;
	const int initialPointsLocationY = quarterWindowHeight - static_cast<int>(m_FontSize / 2);

	DrawText(text, sixthWindowWidth, initialPointsLocationY + pointsPositionYOffset, m_FontSize, YELLOW);
	
	char textWithPointsBuffer[7] = { 0 };
	_itoa_s(points, textWithPointsBuffer, 10);

	DrawText(textWithPointsBuffer, pointsPositionX, initialPointsLocationY + pointsPositionYOffset, m_FontSize, YELLOW);
}

void GameScene::RunGetReadyAnimation()
{
	const int getReadyTextSizeX = MeasureText(m_GetReadyText, m_FontSize);

	const int halfWindowWidth = static_cast<int>(WINDOW_WIDTH / 2);
	const int halfWindowHeight = static_cast<int>(WINDOW_HEIGHT / 2);
	
	DrawText(m_GetReadyText, halfWindowWidth - static_cast<int>(getReadyTextSizeX / 2), halfWindowHeight - (m_FontSize / 2), m_FontSize, YELLOW);

	const char* roundText = "Round %i";

	char roundTextBuffer[20] = { 0 };

	sprintf_s(roundTextBuffer, roundText, m_RoundNumber + 1);

	const int roundTextSizeX = MeasureText(roundTextBuffer, m_FontSize);

	const int distanceBetweenGetReadyAndRoundTextsY = 100;

	DrawText(
		roundTextBuffer, 
		halfWindowWidth - static_cast<int>(roundTextSizeX / 2), 
		halfWindowHeight + distanceBetweenGetReadyAndRoundTextsY, 
		m_FontSize, 
		YELLOW);
}