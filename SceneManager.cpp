#include "SceneManager.h"
#include "StratagemConfigParser.h"

SceneManager::SceneManager()
{
	m_TitleScene = new TitleScene();
	m_GameOverScene = new GameOverScene();

	InstantiateGameScene();
}

SceneManager::~SceneManager()
{
	if (m_TitleScene != nullptr)
	{
		delete m_TitleScene;
	}

	if (m_GameScene != nullptr)
	{
		delete m_GameScene;
	}
}

void SceneManager::InstantiateGameScene()
{
	std::vector<Stratagem> stratagems = LoadStratagems();

	m_GameScene = new GameScene(stratagems);
}

std::vector<Stratagem> SceneManager::LoadStratagems()
{
	StratagemConfigParser stratagemConfigParser("StratagemConfig.txt");
	stratagemConfigParser.ParseStratagems();

	return stratagemConfigParser.GetStratagems();
}

Scene* SceneManager::GetNextScenePtr(SceneEnum nextScene)
{
	switch (nextScene)
	{
	case SceneEnum::GAME:
		InstantiateGameScene();
		return m_GameScene;
	case SceneEnum::TITLE:
		return m_TitleScene;
	case SceneEnum::GAMEOVER:
		return m_GameOverScene;
	default:
		return nullptr;
	}
}