#pragma once

#include "globals.h"
#include "FontManager.h"
#include "TextureManager.h"
#include "ActionManager.h"
#include "ActorManager.h"
#include "GridManager.h"
#include "Actor.h"

using namespace std;

const string GUI_FONT = "ark";
const int GUI_FONT_SIZE = 24;
const sf::Color GUI_COLOR = sf::Color::Yellow;
const sf::Color BG_COLOR = sf::Color(22, 24, 35);

const sf::String APP_NAME = L"战斗";


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

	void onResize();
	void onKeyboard();

	sf::RenderWindow window;
	sf::Text text;
};

