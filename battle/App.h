#pragma once

#include "globals.h"
#include "FontManager.h"
#include "TextureManager.h"
#include "ActionManager.h"
#include "ActorManager.h"
#include "GridManager.h"
#include "Actor.h"

const string GUI_FONT = "ark";
constexpr int GUI_FONT_SIZE = 24;
const sf::Color GUI_COLOR = sf::Color::Yellow;
const sf::Color BG_COLOR = sf::Color(22, 24, 35);

const sf::String APP_NAME = L"战斗";


class App
{
public:
	App() = default;

	void init();
	void run();

private:

	void initWindow();

	void initText();
	void updateText(sf::Time elapsed);
	void drawText();

	void onResize();
	void onKeyboard() noexcept;

	sf::RenderWindow window;
	sf::Text text;
};

