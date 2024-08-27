#pragma once
#include "TitleScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

class SceneManager
{
private:
	TitleScene* m_TitleScene;
	GameScene* m_GameScene;
	GameOverScene* m_GameOverScene;
	void InstantiateGameScene();

	std::vector<Stratagem> LoadStratagems();
public:
	SceneManager();
	~SceneManager();
	Scene* GetNextScenePtr(SceneEnum sceneEnum);
};

