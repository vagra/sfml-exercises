#pragma once

#include "globals.h"
#include "Actor.h"

using namespace std;

const string FONT_OTF = "../assets/fonts/ark-pixel-12px-monospaced-zh_cn.ttf";
const sf::String APP_NAME = L"你好, SFML!";

const int INIT_WIDTH = 1600;
const int INIT_HEIGHT = 800;

static sf::RenderWindow window;

class App
{
public:
	static void run();

	static int width;
	static int height;

private:
	static void onResize();
};

