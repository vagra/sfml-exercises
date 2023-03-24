#include "ActionManager.h"

void ActionManager::loadActions(string png_dir, int row_actions) {
    cout << "from csv load actions to action manager...";

    m_action_sets.clear();

    const string csv_path = fmt::format("{}/{}", png_dir, ACTIONS_CSV);

    rapidcsv::Document csv(csv_path, rapidcsv::LabelParams(0, 0));
    m_names = csv.GetRowNames();
    m_action_names = csv.GetColumnNames();

    for (auto& actor_name : m_names) {
        auto action_set = make_unique<ActionSet>();
        action_set->name = actor_name;
        action_set->actions.clear();
        action_set->names.clear();

        int row = 0;
        int index = 0;
        int start_frame = 0;
        for (auto& action_name : m_action_names) {
            auto action = make_unique<Action>();
            action->name = action_name;
            action->frames = csv.GetCell<int>(action_name, actor_name);
            action->start = start_frame;
            action->row = row;

            index++;
            if (index % row_actions == 0) {
                start_frame = 0;
                row++;
            }
            else {
                start_frame += action->frames;
            }

            action_set->actions[action_name] = move(action);
            action_set->names.push_back(action_name);
        }

        m_action_sets[actor_name] = move(action_set);
    }

    csv.Clear();

    fmt::print("\t{} action sets ready.\n", getCount());

    printList();
}

int ActionManager::getCount() noexcept {
    return narrow_cast<int>(m_action_sets.size());
}

ActionSet* ActionManager::getActionSet(string name)
{
    if (m_action_sets.find(name) != m_action_sets.end()) {
        return m_action_sets[name].get();
    }

    throw runtime_error(
        fmt::format("action set with name of {} not exist.", name)
    );
}

ActionSet* ActionManager::getActionSet(int index) {
    assert(index < m_names.size());
    return getActionSet(m_names.at(index));
}

int ActionManager::getActionSetIndex(string name) {
    auto it = std::find(m_names.begin(), m_names.end(), name);
    if (it == m_names.end()) {
        return -1;
    }
    
    return narrow_cast<int>(distance(m_names.begin(), it));
}

string ActionManager::getActionSetName(int index) {
    assert(index < m_names.size());
    return m_names.at(index);
}

int ActionManager::getActionCount() noexcept {
    return narrow_cast<int>(m_action_names.size());
}

Action* ActionManager::getAction(string action_set_name, string action_name) {
    return getActionSet(action_set_name)->getAction(action_name);
}

Action* ActionManager::getAction(int action_set_index, int action_index) {
    return getActionSet(action_set_index)->getAction(action_index);
}

int ActionManager::getActionIndex(string action_name) {
    auto it = std::find(m_action_names.begin(), m_action_names.end(), action_name);
    if (it == m_action_names.end()) {
        return -1;
    }

    return narrow_cast<int>(distance(m_action_names.begin(), it));
}

string ActionManager::getActionName(int action_index) {
    assert(action_index < m_action_names.size());
    return m_action_names.at(action_index);
}


void ActionManager::printMap() {
    for (auto const& [actor_name, action_set] : m_action_sets) {
        fmt::print("actor {}:\n", actor_name);
        for (auto const& [action_name, action] : action_set->actions) {
            fmt::print("\t{}\t{:4}{:4}{:4}\n",
                action_name, action->frames, action->start, action->row);
        }
    }
}

void ActionManager::printList() {
    for (auto const& actor_name : m_names) {
        fmt::print("actor {}:\n", actor_name);
        for (auto const& action_name : m_action_names) {
            auto const& action = m_action_sets[actor_name]->actions[action_name];
            fmt::print("\t{}\t{:4}{:4}{:4}\n",
                action->name, action->frames, action->start, action->row);
        }
    }
}
