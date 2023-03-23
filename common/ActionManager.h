#pragma once

#include "headers.h"
#include <rapidcsv/rapidcsv.h>

#include "Action.h"

const string ACTIONS_CSV = "actions.csv";

class ActionManager
{
public:
	static ActionManager& instance() noexcept {
		static ActionManager instance;
		return instance;
	}

	void loadActions(string png_dir);

	int getCount() noexcept;
	ActionSet* getActionSet(string name);
	ActionSet* getActionSet(int index);
	int getActionSetIndex(string name);
	string getActionSetName(int index);

	int getActionCount() noexcept;
	Action* getAction(string action_set_name, string action_name);
	Action* getAction(int action_set_index, int action_index);
	int getActionIndex(string action_name);
	string getActionName(int action_index);

	const vector<string>& names = m_names;
	const vector<string>& action_names = m_action_names;

private:
	void printMap();
	void printList();

	unordered_map<string, unique_ptr<ActionSet>> m_action_sets;
	vector<string> m_names;
	vector<string> m_action_names;
};
