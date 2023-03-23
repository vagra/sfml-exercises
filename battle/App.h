#pragma once

#include "globals.h"
#include "../common/FontManager.h"
#include "../common/TextureManager.h"
#include "../common/ActionManager.h"
#include "../common/ActorManager.h"
#include "GridManager.h"
#include "Hero.h"

const string GUI_FONT = "ark";
constexpr int GUI_FONT_SIZE = 24;
const sf::Color GUI_COLOR = sf::Color::Yellow;
const sf::Color BG_COLOR = sf::Color(22, 24, 35);

const sf::String APP_NAME = L"战斗";


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

	void onResize();
	void onKeyboard();

	sf::RenderWindow window;
	sf::Text text;
};

