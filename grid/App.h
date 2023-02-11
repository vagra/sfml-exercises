#pragma once

#include "globals.h"
#include "TextureManager.h"
#include "Actor.h"
#include "UGrid.h"

using namespace std;

const string FONT_OTF = "../assets/fonts/ark-pixel-12px-monospaced-zh_cn.ttf";
const sf::String APP_NAME = L"碰撞";
const sf::Color BG_COLOR = sf::Color(22, 24, 35);

class App
{
public:
	App();

	void run();

private:

	void init();

	void initWindow();
	void initText();
	void initActors();

	void initUGrid();
	void updateUGrid();

	void onResize();

	sf::RenderWindow window;
	sf::Font font;
	sf::Text text;

	vector<Actor> actors;

	UGrid* mp_grid;

};

