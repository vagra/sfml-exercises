#pragma once

#include "globals.h"
#include "TextureManager.h"
#include "ActionManager.h"
#include "ActorManager.h"
#include "GridManager.h"
#include "Actor.h"

using namespace std;

const string FONT_OTF = "../assets/fonts/ark-pixel-12px-monospaced-zh_cn.ttf";
const sf::String APP_NAME = L"战斗";
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
	void updateText(sf::Time elapsed);
	void drawText();

	void onResize();
	void onKeyboard();

	sf::RenderWindow window;
	sf::Font font;
	sf::Text text;
};

