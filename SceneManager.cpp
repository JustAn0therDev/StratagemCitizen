#include "SceneManager.h"
#include "StratagemConfigParser.h"

SceneManager::SceneManager()
{
	m_TitleScene = new TitleScene();

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
	StratagemConfigParser stratagemConfigParser("StratagemConfig.txt");
	stratagemConfigParser.ParseStratagems();

	std::vector<Stratagem> stratagems = stratagemConfigParser.GetStratagems();

	m_GameScene = new GameScene(stratagems);
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
	default:
		return nullptr;
	}
}