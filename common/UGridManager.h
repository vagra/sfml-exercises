#pragma once
#pragma warning(disable: 26440)

#include "headers.h"
#include <dragon-space/UGrid.h>

#include "Actor.h"
#include "ActorManager.h"
#include "Grid.h"

class Actor;

const sf::Color RECT_COLOR = sf::Color(128, 0, 0, 100);

class UGridManager
{
public:

	static UGridManager& instance() {
		static UGridManager instance;
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
	void drawRects(sf::RenderWindow& window);

	/* private members */

	Grid m_config;
	bool m_show_rects = true;

	UGrid* mp_grid = nullptr;

	vector<unique_ptr<sf::RectangleShape>> rects;
};

