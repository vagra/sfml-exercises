#pragma once

#include "globals.h"
#include "../common/FontManager.h"
#include "../common/TextureManager.h"
#include "../common/ActionManager.h"
#include "../common/ActorManager.h"
#include "../common/GridManager.h"
#include "Hero.h"

const Text gui_text{
	.font = "ark",
	.size = 24,
	.color = sf::Color::Yellow
};

const sf::Color BG_COLOR = sf::Color(69, 86, 103);

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

	void onResize();
	void onKeyboard();

	sf::RenderWindow window;
	sf::Text text;
};

