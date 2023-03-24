#pragma once

#include "globals.h"
#include "../common/FontManager.h"
#include "../common/TextureManager.h"
#include "../common/ActionManager.h"
#include "../common/ActorManager.h"
#include "Hero.h"

const string GUI_FONT = "ark";
constexpr int GUI_FONT_SIZE = 24;
const sf::Color GUI_COLOR = sf::Color::Yellow;
const sf::Color BG_COLOR = sf::Color(69, 86, 103);

const sf::Color LRECT_COLOR = sf::Color(128, 0, 0, 50);
const sf::Color TRECT_COLOR = sf::Color(128, 0, 0, 50);

const sf::String APP_NAME = L"战士";

class App
{
public:
	void init();
	void run();

private:
	void initWindow();

	void initText();
	void updateText(sf::Time elapsed);
	void drawText();

	void initActors();
	void updateActors(sf::Time elapsed);
	void drawActors();

	void initGrid();
	void updateGrid();

	void initRects();
	void updateRects();
	void drawRects();

	void onResize();
	void onKeyboard();

	void initLRects();
	void initTRects();

	sf::RenderWindow window;
	sf::Text text;

	LGrid* mp_grid = nullptr;

	vector<unique_ptr<sf::RectangleShape>> lrects;
	vector<unique_ptr<sf::RectangleShape>> trects;

	bool m_show_rects = true;
};

