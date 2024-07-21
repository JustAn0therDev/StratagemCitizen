#pragma once
#include "TitleScene.h"
#include "GameScene.h"

class SceneManager
{
private:
	TitleScene* m_TitleScene;
	GameScene* m_GameScene;
	void InstantiateGameScene();

	std::vector<Stratagem> LoadStratagems();

public:
	SceneManager();
	~SceneManager();
	Scene* GetNextScenePtr(SceneEnum sceneEnum);
};

