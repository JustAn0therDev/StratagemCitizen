#include "GameScene.h"
#include "Constants.h"
#include "RoundTimer.h"
#include <raylib.h>
#include "Round.h"

GameScene::GameScene(std::vector<Stratagem> p_Stratagems) : m_Index(0), m_FinalPoints(0), m_RoundNumber(1)
{
	m_Stratagems = p_Stratagems;
	m_CurrentRound.SetRandomStratagemsFromStratagemVector(p_Stratagems);
}

void GameScene::SetStratagemVector(std::vector<Stratagem> p_Stratagems)
{
	m_Stratagems = p_Stratagems;
}

void GameScene::Input()
{
	m_CurrentRound.Input();
}

void GameScene::Update()
{
	m_CurrentRound.Update();

	if (m_CurrentRound.GetFinished())
	{
		m_CurrentRound = Round();
		m_CurrentRound.SetRandomStratagemsFromStratagemVector(m_Stratagems);
		m_RoundNumber++;
	}
}

void GameScene::Draw()
{
#ifdef DEBUG
	// NOTES(Ruan): a VERY simple way to debug if things are, in fact, in the middle of the screen
	DrawLine(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, GREEN);
	DrawLine(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2, GREEN);
#endif

	m_CurrentRound.Draw();

	// TODO: The font size (60) should be separated as a constant value
	char buffer[10] = { 0 };
	sprintf_s(buffer, "%i", m_RoundNumber);
	DrawText(buffer, WINDOW_WIDTH - 60, 0, 60, YELLOW);
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
