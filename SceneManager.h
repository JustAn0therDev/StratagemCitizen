#pragma once
#include "TitleScene.h"
#include "GameScene.h"

class SceneManager
{
private:
	TitleScene* m_TitleScene;
	GameScene* m_GameScene;

public:
	SceneManager();
	Scene* GetNextScenePtr(SceneEnum sceneEnum);
};

