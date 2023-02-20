#include "ActionManager.h"

Action* ActionSet::getAction(string name)
{
    if (actions.find(name) != actions.end()) {
        return actions[name];
    }
    else {
        return nullptr;
    }
}

Action* ActionSet::getAction(int index)
{
    return getAction(names[index]);
}


ActionManager::ActionManager()
{
}

void ActionManager::init() {

    cout << "init action manager:" << endl;

    loadActions();

    cout << "init action manager done." << endl << endl;
}

int ActionManager::getCount() {
    return int(action_sets.size());
}

const vector<string>& ActionManager::getNames() {
    return names;
}

ActionSet* ActionManager::getActionSet(string name)
{
    if (action_sets.find(name) != action_sets.end()) {
        return action_sets[name];
    }
    else {
        return nullptr;
    }
}

ActionSet* ActionManager::getActionSet(int index)
{
    return getActionSet(names[index]);
}


int ActionManager::getActionID(string action_name) {
    auto it = std::find(action_names.begin(), action_names.end(), action_name);
    if (it == action_names.end()) {
        return -1;
    }
    else {
        int dst = (int)distance(action_names.begin(), it);
        return dst;
    }
}

string ActionManager::getActionName(int action_index) {
    return action_names.at(action_index);
}


void ActionManager::loadActions() {
    cout << "from csv load actions to action manager...";

    action_sets.clear();

    rapidcsv::Document csv(ACTIONS_CSV, rapidcsv::LabelParams(0, 0));
    names = csv.GetRowNames();
    action_names = csv.GetColumnNames();

    for (auto& actor_name : names) {
        ActionSet* action_set = new ActionSet();
        action_set->name = actor_name;
        action_set->actions.clear();
        action_set->names.clear();

        int start_frame = 0;
        for (auto& action_name : action_names) {
            Action* action = new Action();
            action->name = action_name;
            action->frames = csv.GetCell<int>(action_name, actor_name);
            action->start = start_frame;

            start_frame += action->frames;

            action_set->actions[action_name] = action;
            action_set->names.push_back(action_name);
        }

        action_sets[actor_name] = action_set;
    }

    csv.Clear();

    cout << fmt::format("\t{} action sets ready.", getCount()) << endl;

    printList();
}

void ActionManager::printMap() {
    for (auto const& [actor_name, action_set] : action_sets) {
        cout << fmt::format("actor {}:", actor_name) << endl;
        for (auto const& [action_name, action] : action_set->actions) {
            cout << fmt::format("\t{}\t{}\t{}", action_name, action->frames, action->start) << endl;
        }
    }
}

void ActionManager::printList() {
    for (auto const& actor_name : names) {
        cout << fmt::format("actor {}:", actor_name) << endl;
        for (auto const& action_name : action_names) {
            Action* action = action_sets[actor_name]->actions[action_name];
            cout << fmt::format("\t{}\t{}\t{}", action->name, action->frames, action->start) << endl;
        }
    }
}

const int ActionManager::getActionCount() {
    return (int)action_names.size();
}

const vector<string>& ActionManager::getActionNames() {
    return action_names;
}

ActionManager::~ActionManager()
{
    for (auto const& [name, pointer] : action_sets) {
        delete pointer;
    }
}