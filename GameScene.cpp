#include "GameScene.h"
#include "Constants.h"
#include "RoundTimer.h"
#include <raylib.h>
#include "Round.h"

// TODO:
// Calculate the round, images and text relative to the window size, not with fixed values, like font sizes, for example.
GameScene::GameScene(std::vector<Stratagem> p_Stratagems) : 
	m_Index(0),
	m_TotalPoints(0),
	m_RoundNumber(1),
	m_ElapsedSeconds(0),
	m_StartingGame(true),
	m_LastTime(std::chrono::system_clock::now())
{
	m_Stratagems = p_Stratagems;
	m_CurrentRound.SetRandomStratagemsFromStratagemVector(p_Stratagems);
	m_CurrentRound.SetRoundNumber(m_RoundNumber);
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
	UpdateElapsedSeconds();
	
	if (m_StartingGame)
	{
		if (m_ElapsedSeconds.count() > 3.0)
		{
			m_StartingGame = false;
		}
	}
	else if (m_CurrentRound.GetFinished())
	{
		if (m_ElapsedSeconds.count() < m_EndRoundTimeLimitInSeconds)
		{
			return;
		}

		m_RoundNumber++;
		m_TotalPoints += m_CurrentRound.GetTotalPoints();
		m_CurrentRound = Round();
		m_CurrentRound.SetRandomStratagemsFromStratagemVector(m_Stratagems);
		m_CurrentRound.SetRoundNumber(m_RoundNumber);

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
	if (m_StartingGame)
	{
		RunGetReadyAnimation();
	}
	else if (!m_CurrentRound.GetFinished())
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
	char buffer[30]{};

	sprintf_s(buffer, "Round: %i", m_RoundNumber);
	constexpr int xOffset = 20;
	int textSizeWithSpacingX = MeasureText(buffer, m_FontSize) + xOffset;

	DrawText(buffer, WINDOW_WIDTH - textSizeWithSpacingX, 0, m_FontSize, YELLOW);
}

void GameScene::UpdateElapsedSeconds()
{
	std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
	m_ElapsedSeconds = currentTime - m_LastTime;
}

SceneEnum GameScene::GetNextScene() const
{
	if (m_CurrentRound.GetGameOver()) {
		return SceneEnum::GAMEOVER;
	}

	return SceneEnum::NONE;
}

void GameScene::DrawCurrentPoints()
{
	char buffer[30]{};

	int totalPointsPlusRound = m_TotalPoints + m_CurrentRound.GetPoints();
	constexpr int xOffset = static_cast<int>(WINDOW_WIDTH / 5);
	constexpr int yOffset = static_cast<int>(WINDOW_HEIGHT / 4);

	sprintf_s(buffer, "%i", totalPointsPlusRound);
	DrawText(buffer, WINDOW_WIDTH - static_cast<int>(WINDOW_WIDTH / 5), WINDOW_HEIGHT / 4, m_PointsFontSize, YELLOW);
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
	constexpr int initialTextYOffset = 75;

	if (m_ElapsedSeconds.count() < 3.5)
	{
		DrawRoundPointsText("Round Bonus", ROUND_POINTS, 0);

		if (m_ElapsedSeconds.count() > 0.7)
		{
			const int timeBonus = m_CurrentRound.GetRoundTimer()->GetRoundTimerBonus();
			DrawRoundPointsText("Time Bonus", timeBonus, initialTextYOffset);
		}

		if (m_ElapsedSeconds.count() > 1.4)
		{
			const int perfectBonus = m_CurrentRound.GetPerfectBonus();
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
	constexpr int pointsPositionX = sixthWindowWidth * 4;
	const int initialPointsLocationY = quarterWindowHeight - static_cast<int>(m_FontSize / 2);

	DrawText(text, sixthWindowWidth, initialPointsLocationY + pointsPositionYOffset, m_FontSize, YELLOW);
	
	char textWithPointsBuffer[7]{};
	_itoa_s(points, textWithPointsBuffer, 10);

	DrawText(textWithPointsBuffer, pointsPositionX, initialPointsLocationY + pointsPositionYOffset, m_FontSize, YELLOW);
}

void GameScene::RunGetReadyAnimation()
{
	const int getReadyTextSizeX = MeasureText(m_GetReadyText, m_FontSize);

	constexpr int halfWindowWidth = static_cast<int>(WINDOW_WIDTH / 2);
	constexpr int halfWindowHeight = static_cast<int>(WINDOW_HEIGHT / 2);
	
	DrawText(m_GetReadyText, halfWindowWidth - static_cast<int>(getReadyTextSizeX / 2), halfWindowHeight - (m_FontSize / 2), m_FontSize, YELLOW);

	DrawRoundNumber(halfWindowWidth, halfWindowHeight);
}

void GameScene::DrawRoundNumber(const int halfWindowWidth, const int halfWindowHeight)
{
	const char* roundText = "Round %i";
	char roundTextBuffer[20]{};

	int roundNumber = m_RoundNumber + (m_StartingGame ? 0 : 1);

	sprintf_s(roundTextBuffer, roundText, roundNumber);

	const int roundTextSizeX = MeasureText(roundTextBuffer, m_FontSize);

	constexpr int distanceBetweenGetReadyAndRoundTextsY = 100;

	DrawText(
		roundTextBuffer,
		halfWindowWidth - static_cast<int>(roundTextSizeX / 2),
		halfWindowHeight + distanceBetweenGetReadyAndRoundTextsY,
		m_FontSize,
		YELLOW);
}
