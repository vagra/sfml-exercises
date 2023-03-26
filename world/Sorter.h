#pragma once

#include "globals.h"
#include "../common/ActorManager.h"
#include "Hero.h"

constexpr int ROW_HEIGHT = 10;
constexpr int ROWS = 120;

class Hero;

class Sorter
{
public:

	static Sorter& instance() noexcept {
		static Sorter instance;
		return instance;
	}

	void init();
	void update();
	void draw(sf::RenderWindow& window);

	void move(Hero* hero);

private:
	void removeFrom(Hero* hero, int row);
	void moveTo(Hero* hero, int row);

	int getRow(const Hero* hero);
	int getPrevRow(const Hero* hero);

	void print();

	array<Hero*, ROWS> rows;
};
