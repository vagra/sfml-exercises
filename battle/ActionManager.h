#pragma once

#include "globals.h"

struct Action
{
	string name;
	int frames {};
	int start {};
};

struct ActionSet
{
	string name;
	unordered_map<string, unique_ptr<Action>> actions;
	vector<string> names;

	Action* getAction(string name);
	Action* getAction(int index);
};

class ActionManager {
public:
	static void init();

	static int getCount() noexcept;
	static vector<string>& getNames() noexcept;

	static ActionSet* getActionSet(string name);
	static ActionSet* getActionSet(int index);

	static int getActionSetIndex(string name);
	static string getActionSetName(int index);

	static int getActionCount() noexcept;
	static vector<string>& getActionNames() noexcept;

	static int getActionIndex(string action_name);
	static string getActionName(int action_index);

private:

	static void loadActions();

	static void printMap();
	static void printList();

	static inline unordered_map<string, unique_ptr<ActionSet>> action_sets;
	static inline vector<string> names;
	static inline vector<string> action_names;
};