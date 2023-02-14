#pragma once

#include "globals.h"
#include "TextureManager.h"
#include "Actor.h"
#include "LGrid.h"

using namespace std;

const string FONT_OTF = "../assets/fonts/ark-pixel-12px-monospaced-zh_cn.ttf";
const sf::String APP_NAME = L"战士";
const sf::Color BG_COLOR = sf::Color(69, 86, 103);

class App
{
public:
	App();

	void run();

private:

	void init();

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

	sf::RenderWindow window;
	sf::Font font;
	sf::Text text;

	vector<Actor> actors;

	LGrid* mp_grid;

	vector<sf::RectangleShape> lrects;
	vector<sf::RectangleShape> trects;

};

