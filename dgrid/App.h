#pragma once

#include "globals.h"
#include "../common/FontManager.h"
#include "../common/TextureManager.h"
#include "../common/ActionManager.h"
#include "../common/ActorManager.h"
#include "../common/GridManager.h"
#include "Tank.h"

const Text gui_text{
	.font = "ark",
	.size = 24,
	.color = sf::Color::Yellow
};
const sf::Color BG_COLOR = sf::Color(22, 24, 35);

const sf::String APP_NAME = L"碰撞";

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

	sf::RenderWindow window;
	sf::Text text;
};

