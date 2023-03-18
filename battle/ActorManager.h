#pragma once

#include "globals.h"
#include "Actor.h"

class ActorManager
{
public:
	static void init();
	static void update(sf::Time elapsed);
	static void draw(sf::RenderWindow& window);

	static int getCount() noexcept;
	static int genID() noexcept;
	static Actor* getActor(int index) noexcept;
	
	static const vector<unique_ptr<Actor>>& getActors() noexcept;

	static void setRegion(int width, int height) noexcept;
	static bool atFront(const Actor* actor1, const Actor* actor2);
	static void attack(Actor* actor1, Actor* actor2);

private:

	static void makeActors();

	static void print();

	static int inline counter = -1;

	static inline vector<unique_ptr<Actor>> actors;
};