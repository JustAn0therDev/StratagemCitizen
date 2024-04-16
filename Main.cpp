#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Arrow.h"
#include "Stratagem.h"
#include "Constants.h"
#include "StratagemConfigParser.h"

const int initialPosY = 260;
const int posYLimit = 40;
const float lerpBy = 0.2f;
bool pressed = false;
bool endingAnimation = false;

int main(void)
{
	// TODO (next thing): Create a parser to check an input file containing all stratagem information (for now there are only three: title, arrow sequence, icon).
	// TODO (maybe): Option to have all arrows that point to the same direction with the same color

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Stratagem Citizen");

	StratagemConfigParser stratagemConfigParser("StratagemConfig.txt");

	stratagemConfigParser.ParseStratagems();

	//Arrow arrow = Arrow("Assets/Arrow Up.png", KEY_UP);
	//Arrow arrow2 = Arrow("Assets/Arrow Right.png", KEY_RIGHT);
	//Arrow arrow3 = Arrow("Assets/Arrow Down.png", KEY_DOWN);
	//Arrow arrow4 = Arrow("Assets/Arrow Down.png", KEY_DOWN);
	//Arrow arrow5 = Arrow("Assets/Arrow Down.png", KEY_DOWN);

	//std::vector<Arrow> arrows;
	//arrows.reserve(5);
	//arrows.emplace_back(arrow);
	//arrows.emplace_back(arrow2);
	//arrows.emplace_back(arrow3);
	//arrows.emplace_back(arrow4);
	//arrows.emplace_back(arrow5);

	//Stratagem eagleStratagem = Stratagem("Eagle 500 KG Bomb", arrows, "Assets/eagle-500kg-bomb.png");

	//Arrow quasarArrow = Arrow("Assets/Arrow Down.png", KEY_DOWN);
	//Arrow quasarArrow2 = Arrow("Assets/Arrow Down.png", KEY_DOWN);
	//Arrow quasarArrow3 = Arrow("Assets/Arrow Up.png", KEY_UP);
	//Arrow quasarArrow4 = Arrow("Assets/Arrow Left.png", KEY_LEFT);
	//Arrow quasarArrow5 = Arrow("Assets/Arrow Right.png", KEY_RIGHT);

	//std::vector<Arrow> quasarArrows;
	//quasarArrows.reserve(5);
	//quasarArrows.emplace_back(quasarArrow);
	//quasarArrows.emplace_back(quasarArrow2);
	//quasarArrows.emplace_back(quasarArrow3);
	//quasarArrows.emplace_back(quasarArrow4);
	//quasarArrows.emplace_back(quasarArrow5);

	//Stratagem quasarCannonStratagem = Stratagem("Quasar Cannon", quasarArrows, "Assets/quasar-cannon.png");

	//Arrow orbital380Arrow = Arrow("Assets/Arrow Right.png", KEY_RIGHT);
	//Arrow orbital380Arrow2 = Arrow("Assets/Arrow Down.png", KEY_DOWN);
	//Arrow orbital380Arrow3 = Arrow("Assets/Arrow Down.png", KEY_DOWN);
	//Arrow orbital380Arrow4 = Arrow("Assets/Arrow Up.png", KEY_UP);
	//Arrow orbital380Arrow5 = Arrow("Assets/Arrow Up.png", KEY_UP);
	//Arrow orbital380Arrow6 = Arrow("Assets/Arrow Left.png", KEY_LEFT);
	//Arrow orbital380Arrow7 = Arrow("Assets/Arrow Down.png", KEY_DOWN);
	//Arrow orbital380Arrow8 = Arrow("Assets/Arrow Down.png", KEY_DOWN);
	//Arrow orbital380Arrow9 = Arrow("Assets/Arrow Down.png", KEY_DOWN);

	//std::vector<Arrow> orbital380Arrows;
	//orbital380Arrows.reserve(9);
	//orbital380Arrows.emplace_back(orbital380Arrow);
	//orbital380Arrows.emplace_back(orbital380Arrow2);
	//orbital380Arrows.emplace_back(orbital380Arrow3);
	//orbital380Arrows.emplace_back(orbital380Arrow4);
	//orbital380Arrows.emplace_back(orbital380Arrow5);
	//orbital380Arrows.emplace_back(orbital380Arrow6);
	//orbital380Arrows.emplace_back(orbital380Arrow7);
	//orbital380Arrows.emplace_back(orbital380Arrow8);
	//orbital380Arrows.emplace_back(orbital380Arrow9);

	//Stratagem orbital380Stratagem = Stratagem("Orbital 380Mm He Barrage", orbital380Arrows, "Assets/orbital-380mm-he-barrage.png");

	//std::vector<Stratagem> stratagems;
	//stratagems.emplace_back(eagleStratagem);
	//stratagems.emplace_back(quasarCannonStratagem);
	//stratagems.emplace_back(orbital380Stratagem);
	int index = 0;
	std::vector<Stratagem> stratagems = stratagemConfigParser.GetStratagems();

	while (!WindowShouldClose())
	{
		SetTargetFPS(60);
		DrawFPS(0, 0);
		BeginDrawing();
		ClearBackground(BLACK);

#ifdef _DEBUG
		// NOTES(Ruan): a VERY simple way to debug if things are, in fact, in the middle of the screen
		DrawLine(WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT, GREEN);
		DrawLine(0, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT / 2, GREEN);
#endif

		stratagems[index].Input();
		stratagems[index].Update();
		stratagems[index].Draw();

		if (stratagems[index].GetFinished())
		{
			index++;
		}

		if (index == stratagems.size())
			break;
		
		EndDrawing();
	}

	for (auto& stratagem : stratagems)
	{
		stratagem.UnloadResources();
	}

	return 0;
}