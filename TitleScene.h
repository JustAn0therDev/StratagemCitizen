#pragma once
#include "Scene.h"
class TitleScene : public Scene
{
private:
	bool m_ShouldEndScene = false;

public:
	virtual bool GetShouldEndScene() const;
	virtual void Input();
	virtual void Update();
	virtual void Draw();
};

