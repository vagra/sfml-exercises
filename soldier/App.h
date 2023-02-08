#pragma once

#include "globals.h"
#include "TextureManager.h"
#include "Actor.h"

using namespace std;

const string FONT_OTF = "../assets/fonts/ark-pixel-12px-monospaced-zh_cn.ttf";
const sf::String APP_NAME = L"战士";
const sf::Color BG_COLOR = sf::Color(126, 161, 116);

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

	void onResize();

	sf::RenderWindow window;
	sf::Font font;
	sf::Text text;

	vector<Actor> actors;

};

