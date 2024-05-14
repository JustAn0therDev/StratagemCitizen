#pragma once
#include "Scene.h"
#include <vector>
#include "Stratagem.h"
#include "RoundTimer.h"
#include "Round.h"

class GameScene : public virtual Scene
{
private:
	std::vector<Stratagem> m_Stratagems;
	int m_Index;
	int m_FinalPoints;
	Round m_CurrentRound;
	int m_RoundNumber;
	const int m_FontSize = 60;
public:
	GameScene(std::vector<Stratagem> p_Stratagems);
	void SetStratagemVector(std::vector<Stratagem> p_Stratagems);
	void Input();
	void Update();
	void Draw();
	bool GetShouldEndScene() const;
	~GameScene();
};

