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

	static int getCount();

	static Actor* getActor(string name);
	static Actor* getActor(int index);

	static int getActorID(string name);
	static string getActorName(int index);

	static const vector<string>* getNames();

private:

	static void makeActors();

	static void printMap();
	static void printList();

	static inline unordered_map<string, Actor*> actors;
	static inline vector<string> names;
};

