#pragma once

#include "globals.h"
#include "Action.h"

class ActionManager {
public:
	static void init();

	static int getCount() noexcept;
	static vector<string>& getNames() noexcept;

	static ActionSet* getActionSet(string name);
	static ActionSet* getActionSet(int index);

	static Action* getAction(string action_set_name, string action_name);
	static Action* getAction(int action_set_index, int action_index);

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