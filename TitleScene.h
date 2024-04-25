#pragma once
#include "Scene.h"
class TitleScene : public virtual Scene
{
private:
	bool m_ShouldEndScene = false;

public:
	bool GetShouldEndScene() const;
	virtual void Input();
	virtual void Update();
	virtual void Draw();
};

