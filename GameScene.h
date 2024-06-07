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
	int m_TotalPoints;
	int m_PointsFontSize = 60;
	Round m_CurrentRound;
	int m_RoundNumber;
	const int m_FontSize = 60;
	const char* m_GetReadyText = "GET READY";
	std::chrono::system_clock::time_point m_LastTime;
	std::chrono::duration<double> m_ElapsedSeconds;
	const double m_EndRoundTimeLimitInSeconds = 5;

	void DrawRoundPointsText(const char* text, const int points, const int pointsPositionY) const;
public:
	GameScene(std::vector<Stratagem> p_Stratagems);
	void SetStratagemVector(std::vector<Stratagem> p_Stratagems);
	void Input();
	void Update();
	void Draw();
	bool GetShouldEndScene() const;
	void RunRoundEndAnimation();
	void RunGetReadyAnimation();
	~GameScene();
};

