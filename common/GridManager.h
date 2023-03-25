#pragma once
#pragma warning(disable: 26440)

#include "headers.h"
#include <dragon-space/LGrid.h>

#include "Actor.h"
#include "ActorManager.h"
#include "Grid.h"

class Actor;

const sf::Color LRECT_COLOR = sf::Color(128, 0, 0, 100);
const sf::Color TRECT_COLOR = sf::Color(128, 0, 0, 100);

class GridManager
{
public:

	static GridManager& instance() {
		static GridManager instance;
		return instance;
	}

	/* public methods */

	void init(Grid config, bool show_rects);
	void update();
	void draw(sf::RenderWindow& window);

private:

	/* private methods */

	void initActors();
	void updateActors();
	void drawActors(sf::RenderWindow& window);

	void initRects();
	void updateRects();
	void drawRects(sf::RenderWindow& window);

	void initLRects();
	void initTRects();

	/* private members */

	Grid m_config;
	bool m_show_rects = true;

	LGrid* mp_grid = nullptr;

	vector<unique_ptr<sf::RectangleShape>> lrects;
	vector<unique_ptr<sf::RectangleShape>> trects;
};

