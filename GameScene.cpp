#include "GameScene.h"
#include "Constants.h"
#include "RoundTimer.h"
#include <raylib.h>

GameScene::GameScene(std::vector<Stratagem> p_Stratagems) : m_Index(0)
{
	m_Stratagems = p_Stratagems;
}

void GameScene::SetStratagemVector(std::vector<Stratagem> p_Stratagems)
{
	m_Stratagems = p_Stratagems;
}

void GameScene::Input()
{
	m_Stratagems[m_Index].Input();
}

void GameScene::Update()
{
	m_Stratagems[m_Index].Update();

	if (m_Stratagems[m_Index].GetFinished())
	{
		m_Index++;
		m_RoundTimer.AddTime();
	}

	m_RoundTimer.Update();

	if (m_Index == m_Stratagems.size() || m_RoundTimer.GetIsTimeUp())
		exit(1); // TODO: Temporary, this should not make the program close
}

void GameScene::Draw()
{
#ifdef _DEBUG
	// NOTES(Ruan): a VERY simple way to debug if things are, in fact, in the middle of the screen
	DrawLine(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, GREEN);
	DrawLine(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2, GREEN);
#endif

	m_Stratagems[m_Index].Draw();
	m_RoundTimer.Draw();
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
