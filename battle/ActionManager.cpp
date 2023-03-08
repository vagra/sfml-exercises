#include "ActionManager.h"

void ActionManager::init() {

    cout << "init action manager:" << endl;

    loadActions();

    cout << "init action manager done." << endl << endl;
}

int ActionManager::getCount() noexcept {
    return narrow_cast<int>(action_sets.size());
}

vector<string>& ActionManager::getNames() noexcept {
    return names;
}

ActionSet* ActionManager::getActionSet(string name)
{
    if (action_sets.find(name) != action_sets.end()) {
        return action_sets[name].get();
    }

    throw runtime_error(
        fmt::format("action set with name of {} not exist.", name)
    );
}

ActionSet* ActionManager::getActionSet(int index)
{
    assert(index < names.size());
    return getActionSet(names.at(index));
}

Action* ActionManager::getAction(string action_set_name, string action_name) {
    return getActionSet(action_set_name)->getAction(action_name);
}

Action* ActionManager::getAction(int action_set_index, int action_index) {
    return getActionSet(action_set_index)->getAction(action_index);
}

int ActionManager::getActionSetIndex(string name) {
    auto it = std::find(names.begin(), names.end(), name);
    if (it == names.end()) {
        return -1;
    }
    else {
        return narrow_cast<int>(distance(names.begin(), it));
    }
}

string ActionManager::getActionSetName(int index) {
    return names.at(index);
}


int ActionManager::getActionCount() noexcept {
    return narrow_cast<int>(action_names.size());
}

vector<string>& ActionManager::getActionNames() noexcept {
    return action_names;
}

int ActionManager::getActionIndex(string action_name) {
    auto it = std::find(action_names.begin(), action_names.end(), action_name);
    if (it == action_names.end()) {
        return -1;
    }
    else {
        return narrow_cast<int>(distance(action_names.begin(), it));
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
        auto action_set = make_unique<ActionSet>();
        action_set->name = actor_name;
        action_set->actions.clear();
        action_set->names.clear();

        int start_frame = 0;
        for (auto& action_name : action_names) {
            auto action = make_unique<Action>();
            action->name = action_name;
            action->frames = csv.GetCell<int>(action_name, actor_name);
            action->start = start_frame;

            start_frame += action->frames;

            action_set->actions[action_name] = move(action);
            action_set->names.push_back(action_name);
        }

        action_sets[actor_name] = move(action_set);
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
            Action* action = action_sets[actor_name]->actions[action_name].get();
            cout << fmt::format("\t{}\t{}\t{}", action->name, action->frames, action->start) << endl;
        }
    }
}
