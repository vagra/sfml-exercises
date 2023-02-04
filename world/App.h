#pragma once

#include "globals.h"
#include "Actor.h"

using namespace std;

const string FONT_OTF = "../assets/fonts/ark-pixel-12px-monospaced-zh_cn.ttf";
const sf::String APP_NAME = L"你好, SFML!";
const sf::Color BG_COLOR = sf::Color(173, 213, 162);

class App
{
public:
	App();

	void init();
	void run();

private:
	void initWindow();
	void initText();
	void initActors();

	void onResize();

	sf::RenderWindow window;
	sf::Font font;
	sf::Text text;

	vector<Actor> actors;

};

