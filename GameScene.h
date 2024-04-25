#pragma once
#include "Scene.h"
#include <vector>
#include "Stratagem.h"

class GameScene : public virtual Scene
{
private:
	std::vector<Stratagem> m_Stratagems;
	int m_Index;

public:
	GameScene(std::vector<Stratagem> p_Stratagems);
	void SetStratagemVector(std::vector<Stratagem> p_Stratagems);
	virtual void Input();
	virtual void Update();
	virtual void Draw();
	~GameScene();
};

