#pragma once

#include "globals.h"
#include "Actor.h"

using namespace std;

class ActorManager
{
public:
	ActorManager();
	~ActorManager();

	static void init();

	static void update(sf::Time elapsed);

	static void draw(sf::RenderWindow& window);

	static int getCount();

	static int genID();

	static Actor* getActor(int index);

	static inline vector<Actor*> actors;

private:

	static void makeActors();

	static void print();

	static int inline counter = 0;
};

