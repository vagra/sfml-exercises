#pragma once

#include "globals.h"
#include "TextureManager.h"
#include "ActionManager.h"
#include "ActorManager.h"
#include "Actor.h"

using namespace std;

const string FONT_OTF = "../assets/fonts/ark-pixel-12px-monospaced-zh_cn.ttf";
const sf::String APP_NAME = L"Animation Viewer";
const sf::Color BG_COLOR = sf::Color(69, 86, 103);

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

	void initActor(int actor_id);
	void updateActor(sf::Time elapsed);
	void drawActor();

	void onResize();
	void onKeyboard();

	void changeDirection();
	void changeActor();
	void changeAction();

	int getDirection(bool l, bool u, bool r, bool d);
	bool needMove(bool l, bool u, bool r, bool d);

	sf::RenderWindow window;
	sf::Font font;
	sf::Text text;

	Actor* actor;

	int actor_id;
	int action_id;
	int direction;
	bool move;
};

