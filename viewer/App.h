#pragma once

#include "globals.h"
#include "../common/FontManager.h"
#include "../common/TextureManager.h"
#include "../common/ActionManager.h"
#include "../common/ActorManager.h"
#include "Hero.h"

const string GUI_FONT = "ark";
constexpr int GUI_FONT_SIZE = 24;
const sf::Color GUI_COLOR = sf::Color::Yellow;
const sf::Color BG_COLOR = sf::Color(69, 86, 103);

const sf::String APP_NAME = L"Animation Viewer";

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

	void changeActor(int actor_id);
	void updateActor(sf::Time elapsed);
	void drawActor();

	void onResize();
	void onKeyboard();

	void changeDirection();
	void changeActor();
	void changeAction();

	int getDirection(bool l, bool u, bool r, bool d) noexcept;
	bool needMove(bool l, bool u, bool r, bool d) noexcept;

	sf::RenderWindow window;
	sf::Text text;

	Hero* actor{};

	int actor_id{};
	int action_id{};
	int direction{};
	bool move{};
};

