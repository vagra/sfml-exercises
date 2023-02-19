#pragma once

#include "globals.h"

using namespace std;

struct Action
{
	string name;
	int frames;
	int start;
};

struct ActionSet
{
	string name;
	map<string, Action*> actions;
	vector<string> names;

	Action* getAction(string name);
	Action* getAction(int index);
};

class ActionManager {
public:
	ActionManager();
	~ActionManager();

	static void init();

	static int getCount();

	static ActionSet* getActionSet(string name);
	static ActionSet* getActionSet(int index);

	static int getActionID(string action_name);
	static string getActionName(int action_index);

	static const vector<string>& getNames();

	static const int getActionCount();
	static const vector<string>& getActionNames();

private:

	static void loadActions();

	static inline map<string, ActionSet*> action_sets;
	static inline vector<string> names;
	static inline vector<string> action_names;
};