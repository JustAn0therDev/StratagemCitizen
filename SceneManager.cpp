#include "SceneManager.h"
#include "StratagemConfigParser.h"

SceneManager::SceneManager()
{
	StratagemConfigParser stratagemConfigParser("StratagemConfig.txt");
	stratagemConfigParser.ParseStratagems();

	std::vector<Stratagem> stratagems = stratagemConfigParser.GetStratagems();

	m_TitleScene = new TitleScene();
	m_GameScene = new GameScene(stratagems);
}

Scene* SceneManager::GetNextScenePtr(SceneEnum nextScene)
{
	switch (nextScene)
	{
	case SceneEnum::GAME:
		return m_GameScene;
	case SceneEnum::TITLE:
		return m_TitleScene;
	default:
		return nullptr;
	}
}