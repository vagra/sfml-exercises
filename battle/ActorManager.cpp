#include "ActorManager.h"

ActorManager::ActorManager()
{
}

void ActorManager::init() {

    cout << "init actor manager:" << endl;

    makeActors();

    cout << "init actor manager done." << endl << endl;
}

int ActorManager::getCount() {
    return (int)actors.size();
}

const vector<string>* ActorManager::getNames() {
    return &names;
}

Actor* ActorManager::getActor(string name)
{
    if (actors.find(name) != actors.end()) {
        return actors[name];
    }
    else {
        return nullptr;
    }
}

Actor* ActorManager::getActor(int index)
{
    return getActor(names[index]);
}

int ActorManager::getActorID(string name) {
    auto it = std::find(names.begin(), names.end(), name);
    if (it == names.end()) {
        return -1;
    }
    else {
        int dst = (int)distance(names.begin(), it);
        return dst;
    }
}

string ActorManager::getActorName(int index) {
    return names.at(index);
}

void ActorManager::makeActors() {
    cout << "make actors with texture, actions and sprite...";

    actors.clear();
    names.clear();

    for (auto& actor_name : ActionManager::getNames()) {
        Actor* actor = new Actor(actor_name);

        actors[actor_name] = actor;
        names.push_back(actor_name);
    }

    cout << fmt::format("\t{} actors ready.", getCount()) << endl;

    printList();
}


void ActorManager::printMap() {
    for (auto const& [name, actor] : actors) {
        cout << fmt::format("{}  {}",
            actor->id, actor->name) << endl;
    }
}

void ActorManager::printList() {
    for (auto const& name : names) {
        Actor* actor = actors[name];
        cout << fmt::format("{}  {}",
            actor->id, actor->name) << endl;
    }
}


ActorManager::~ActorManager()
{
    for (auto const& [name, pointer] : actors) {
        delete pointer;
    }
}