#pragma once

#include "globals.h"
#include "ActorManager.h"
#include "LGrid.h"

const sf::Color LRECT_COLOR = sf::Color(128, 0, 0, 50);
const sf::Color TRECT_COLOR = sf::Color(128, 0, 0, 50);

class GridManager
{
public:
	static void init();
	static void init(bool show_rects);
	static void update();
	static void draw(sf::RenderWindow& window);

private:
	static void initActors();
	static void updateActors();
	static void drawActors(sf::RenderWindow& window);

	static void initRects();
	static void updateRects();
	static void drawRects(sf::RenderWindow& window);

	static void initLRects();
	static void initTRects();

	static inline LGrid* mp_grid = lgrid_create(
		LCELL_WIDTH, LCELL_HEIGHT, TCELL_WIDTH, TCELL_HEIGHT,
		0.f, 0.f, GRID_WIDTH, GRID_HEIGHT
	);

	static inline vector<unique_ptr<sf::RectangleShape>> lrects;
	static inline vector<unique_ptr<sf::RectangleShape>> trects;

	static inline bool m_show_rects = true;
};

